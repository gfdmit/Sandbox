package main

import (
	"elastic/ex01/db"
	"elastic/ex03/recommendation"
	"fmt"
	"net/http"
)

const (
	recommendEndpoint = "/api/recommend"
	serverAddress     = "localhost:8888"
)

func main() {
	elasticsearchClient, err := db.CreateDefaultES()
	if err != nil {
		fmt.Println("Error creating Elasticsearch client:", err)
		return
	}

	http.HandleFunc(recommendEndpoint, recommendation.ClosestHandler(elasticsearchClient))

	fmt.Println("Server for EX03 is running...")
	if err := http.ListenAndServe(serverAddress, nil); err != nil {
		fmt.Println("Server error:", err)
	}
}
