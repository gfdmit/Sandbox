package main

import (
	"elastic/ex01/db"
	"fmt"
	"html/template"
	"net/http"
	"strconv"
)

const (
	serverAddress = "localhost:8888"
	rootEndpoint  = "/"
)

func main() {
	elasticsearchClient, err := db.CreateDefaultES()
	if err != nil {
		fmt.Println("Error creating Elasticsearch client:", err)
		return
	}

	http.HandleFunc(rootEndpoint, rootHandler(elasticsearchClient))

	fmt.Println("Server for EX01 is running...")
	if err := http.ListenAndServe(serverAddress, nil); err != nil {
		fmt.Println("Server error:", err)
	}
}

func rootHandler(es db.Store) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
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
		}
		tmpl := template.Must(template.ParseFiles("index.html"))
		lastPage := countPages(total, limit)
		tmpl.Execute(w, map[string]interface{}{
			"Places": places,
			"Total":  total,
			"Page":   page,
			"Prev":   page - 1,
			"Next":   page + 1,
			"Last":   lastPage,
		})
	}
}

func countPages(total int, limit int) int {
	if total%limit == 0 {
		return total / limit
	}
	return total/limit + 1
}
