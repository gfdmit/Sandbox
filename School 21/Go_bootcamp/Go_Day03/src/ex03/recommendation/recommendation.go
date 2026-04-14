package recommendation

import (
	"elastic/ex01/db"
	"encoding/json"
	"fmt"
	"net/http"
	"strconv"
)

const (
	geoSortQueryTemplate = `{
"sort": [
    {
      "_geo_distance": {
        "location": {
          "lat": %s,
          "lon": %s
        },
        "order": "asc",
        "unit": "km",
        "mode": "min",
        "distance_type": "arc",
        "ignore_unmapped": true
      }
    }
  ]
}`
)

type ElasticsearchClient db.ES

type Recommender interface {
	db.Store
	GetRecommendations(query string, size int) ([]db.Place, error)
}

type RecommendationResponse struct {
	Name   string     `json:"name"`
	Places []db.Place `json:"places"`
}

func ClosestHandler(recommender Recommender) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		defaultSize := 3
		var response interface{}

		latitude := r.URL.Query().Get("lat")
		longitude := r.URL.Query().Get("lon")
		validationMessage, err := validateGeoCoordinates(latitude, longitude)
		if err == nil {
			query := fmt.Sprintf(geoSortQueryTemplate, latitude, longitude)
			places, err := recommender.GetRecommendations(query, defaultSize)
			if err != nil {
				fmt.Println("Error fetching recommendations:", err)
				response = err
			} else {
				response = RecommendationResponse{
					Name:   "Recommendation",
					Places: places,
				}
			}
		} else {
			response = validationMessage
		}

		w.Header().Set("Content-Type", "application/json")
		if err := json.NewEncoder(w).Encode(response); err != nil {
			fmt.Println("Error encoding response:", err)
		}
	}
}

func validateGeoCoordinates(latitude, longitude string) (string, error) {
	var validationErrors string

	_, err := strconv.ParseFloat(latitude, 64)
	if err != nil {
		validationErrors += fmt.Sprintf("Invalid 'lat' value: %s ", latitude)
	}

	_, err = strconv.ParseFloat(longitude, 64)
	if err != nil {
		validationErrors += fmt.Sprintf("Invalid 'lon' value: %s", longitude)
	}

	if validationErrors != "" {
		return validationErrors, fmt.Errorf("invalid geo coordinates")
	}

	return "", nil
}
