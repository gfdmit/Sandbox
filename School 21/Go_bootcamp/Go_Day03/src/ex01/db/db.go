package db

import (
	"context"
	"elastic/ex00/datajson"
	"encoding/json"
	"fmt"
	"io"
	"strings"

	"github.com/elastic/go-elasticsearch/v8"
	"github.com/elastic/go-elasticsearch/v8/esapi"
)

const (
	searchAllPit = `{
	"size" : %d,
	"from" : %d,
	"track_total_hits": true,
	"query" : { "match_all" : {} },
	"pit": { "id": "%s", "keep_alive": "1m" }
	}
	`
)

type Place datajson.Body

type Store interface {
	GetPlaces(limit int, offset int) ([]Place, int, error)
}

type ES struct {
	client *elasticsearch.Client
}

func CreateDefaultES() (*ES, error) {
	client, err := elasticsearch.NewDefaultClient()
	if err != nil {
		return nil, err
	}
	return &ES{client: client}, nil
}

func (es *ES) GetPlaces(limit int, offset int) ([]Place, int, error) {
	pitRes, err := es.client.OpenPointInTime([]string{"places"}, "1m")
	if err != nil {
		return nil, 0, err
	}
	defer pitRes.Body.Close()

	var pitData map[string]interface{}
	if err := json.NewDecoder(pitRes.Body).Decode(&pitData); err != nil {
		return nil, 0, err
	}
	pitID := pitData["id"].(string)

	searchRes, err := es.client.Search(
		es.client.Search.WithContext(context.Background()),
		es.client.Search.WithBody(es.buildQuery(limit, offset, pitID)),
		es.client.Search.WithSort("_doc:asc"),
	)
	if err != nil {
		return nil, 0, err
	}
	defer searchRes.Body.Close()

	if searchRes.IsError() {
		return ErrorLog(searchRes)
	}

	var result struct {
		Hits struct {
			Total struct {
				Value int
			}
			Hits []struct {
				Source Place `json:"_source"`
			}
		}
	}
	if err := json.NewDecoder(searchRes.Body).Decode(&result); err != nil {
		return nil, 0, err
	}

	places := make([]Place, len(result.Hits.Hits))
	for i, hit := range result.Hits.Hits {
		places[i] = hit.Source
	}
	return places, result.Hits.Total.Value, nil
}

func (es *ES) buildQuery(limit int, offset int, pitID string) io.Reader {
	var query strings.Builder
	query.WriteString(fmt.Sprintf(searchAllPit, limit, offset, pitID))
	return strings.NewReader(query.String())
}

func ErrorLog(res *esapi.Response) ([]Place, int, error) {
	var errorData map[string]interface{}
	if err := json.NewDecoder(res.Body).Decode(&errorData); err != nil {
		return nil, 0, err
	}
	return nil, 0, fmt.Errorf("[%s] %s: %s", res.Status(),
		errorData["error"].(map[string]interface{})["type"],
		errorData["error"].(map[string]interface{})["reason"])
}

func (es *ES) GetRecommendations(query string, size int) ([]Place, error) {
	searchRes, err := es.client.Search(
		es.client.Search.WithIndex("places"),
		es.client.Search.WithBody(strings.NewReader(query)),
		es.client.Search.WithContext(context.Background()),
		es.client.Search.WithSize(size),
	)
	if err != nil {
		return nil, err
	}
	defer searchRes.Body.Close()

	if searchRes.IsError() {
		_, _, err := ErrorLog(searchRes)
		return nil, err
	}

	var result struct {
		Hits struct {
			Hits []struct {
				Source Place `json:"_source"`
			}
		}
	}
	if err := json.NewDecoder(searchRes.Body).Decode(&result); err != nil {
		return nil, err
	}

	places := make([]Place, len(result.Hits.Hits))
	for i, hit := range result.Hits.Hits {
		places[i] = hit.Source
	}
	return places, nil
}
