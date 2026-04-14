package main

import (
	"bytes"
	"context"
	"elastic/ex00/datajson"
	"elastic/ex00/reader"
	"encoding/csv"
	"encoding/json"
	"flag"
	"fmt"
	"io"
	"net/http"
	"os"
	"runtime"
	"strings"
	"time"

	"github.com/elastic/go-elasticsearch/v8"
	"github.com/elastic/go-elasticsearch/v8/esutil"
)

type LocationData datajson.Body

var (
	indexName, jsonFilePath, csvFilePath string
	workerCount, bufferSize              int
)

func main() {
	initializeFlags()
	execute()
}

func initializeFlags() {
	flag.StringVar(&jsonFilePath, "json", "schema.json", "path to JSON file")
	flag.StringVar(&csvFilePath, "csv", "../../materials/data.csv", "path to CSV file")
	flag.Parse()
}

func execute() {
	workerCount = runtime.NumCPU()
	bufferSize = int(5e+6)

	jsonContent, err := reader.ReadFile(jsonFilePath)
	if err != nil {
		fmt.Println(err)
	}
	if err = setupElasticsearch(jsonContent); err != nil {
		fmt.Println(err)
		return
	}
}

func setupElasticsearch(jsonData string) error {
	esClient, err := elasticsearch.NewDefaultClient()
	if err != nil {
		return err
	}
	indexName = "locations"

	bulkIndexer, err := esutil.NewBulkIndexer(esutil.BulkIndexerConfig{
		Index:         indexName,
		Client:        esClient,
		NumWorkers:    workerCount,
		FlushBytes:    bufferSize,
		FlushInterval: 10 * time.Second,
	})
	if err != nil {
		return err
	}
	response, err := esClient.Indices.Create(indexName, esClient.Indices.Create.WithBody(strings.NewReader(jsonData)))
	if err != nil {
		return err
	}
	response.Body.Close()
	if err = processCSV(&bulkIndexer); err != nil {
		return err
	}
	if err = bulkIndexer.Close(context.Background()); err != nil {
		return err
	}
	err = updateMaxResultWindow()
	if err != nil {
		return err
	}
	return nil
}

func processCSV(indexer *esutil.BulkIndexer) error {
	csvFile, err := os.Open(csvFilePath)
	if err != nil {
		return err
	}
	defer csvFile.Close()
	csvReader := csv.NewReader(csvFile)
	csvReader.Comma = '\t'

	for i := 0; ; i++ {
		record, err := csvReader.Read()

		if err == io.EOF {
			break
		}
		if err != nil {
			return err
		}
		if i == 0 || len(record) != 6 {
			continue
		}
		location := LocationData{
			Id:      record[0],
			Name:    record[1],
			Address: record[2],
			Phone:   record[3],

			Map: datajson.Geolocation{
				Lon: fmt.Sprint(record[4]),
				Lat: fmt.Sprint(record[5]),
			},
		}

		jsonData, err := json.Marshal(location)
		if err != nil {
			continue
		}
		err = (*indexer).Add(
			context.Background(),
			esutil.BulkIndexerItem{
				Action:     "index",
				DocumentID: location.Id,
				Body:       bytes.NewReader(jsonData),
			},
		)
		if err != nil {
			return err
		}

	}
	return err
}

func updateMaxResultWindow() error {
	url := "http://localhost:9200/places/_settings"
	jsonPayload := []byte(`{
	"index": {"max_result_window": 20000}
	}`)
	request, err := http.NewRequest("PUT", url, bytes.NewBuffer(jsonPayload))
	if err != nil {
		return err
	}
	request.Header.Set("Content-Type", "application/json")
	client := http.Client{}
	response, err := client.Do(request)
	if err != nil {
		return err
	}
	fmt.Println(response.Status)

	return nil
}
