package main

import (
	"elastic/ex00/datajson"
	"elastic/ex01/db"
	"encoding/json"
	"fmt"
	"net/http"
	"strconv"
)

type Response struct {
	Name     string     `json:"name"`
	Total    int        `json:"total"`
	Places   []db.Place `json:"places"`
	Prevpage int        `json:"prev_page"`
	Nextpage int        `json:"next_page"`
	Lastpage int        `json:"last_page"`
}

const (
	serverAddress  = "localhost:8888"
	placesEndpoint = "/api/places"
)

func main() {
	elasticsearchClient, err := db.CreateDefaultES()
	if err != nil {
		fmt.Println("Error creating Elasticsearch client:", err)
		return
	}

	http.HandleFunc(placesEndpoint, apiHandler(elasticsearchClient))

	fmt.Println("Server for EX02 is running...")
	if err := http.ListenAndServe(serverAddress, nil); err != nil {
		fmt.Println("Server error:", err)
	}
}

func apiHandler(es db.Store) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		var response interface{}

		pageStr := r.URL.Query().Get("page")
		if pageStr == "" {
			pageStr = "1"
		}

		page, _ := strconv.Atoi(pageStr)
		if page < 1 {
			page = 1
		}

		limit := 10
		offset := (page - 1) * limit

		places, total, err := es.GetPlaces(limit, offset)
		if err != nil {
			fmt.Println("Error fetching places:", err)
			response = datajson.Err{
				Err: fmt.Sprintf("Invalid 'page' value: %d", page),
			}
		} else {
			lastPage := countPages(total, limit)
			if page <= lastPage {
				response = Response{
					Name:     "places",
					Places:   places,
					Total:    total,
					Prevpage: page - 1,
					Nextpage: page + 1,
					Lastpage: lastPage,
				}
			} else {
				response = datajson.Err{
					Err: fmt.Sprintf("Invalid 'page' value: %d", page),
				}
			}
		}

		w.Header().Set("Content-Type", "application/json")
		if err := json.NewEncoder(w).Encode(response); err != nil {
			fmt.Println("Error encoding response:", err)
		}
	}
}

func countPages(total int, limit int) int {
	if total%limit == 0 {
		return total / limit
	}
	return total/limit + 1
}
