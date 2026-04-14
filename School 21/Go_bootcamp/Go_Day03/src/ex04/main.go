package main

import (
	"elastic/ex01/db"
	"elastic/ex03/recommendation"
	"encoding/json"
	"fmt"
	"net/http"
	"time"

	"github.com/dgrijalva/jwt-go"
)

const (
	tokenEndpoint     = `/api/get_token/`
	serverAddress     = `localhost:8888`
	recommendEndpoint = `/api/recommend/`
)

var (
	jwtSecretKey = []byte(`key`)
)

func main() {
	elasticsearchClient, err := db.CreateDefaultES()
	if err != nil {
		fmt.Println("Error creating Elasticsearch client:", err)
		return
	}

	http.HandleFunc(tokenEndpoint, generateTokenHandler())
	http.HandleFunc(recommendEndpoint, authMiddleware(recommendation.ClosestHandler(elasticsearchClient)))

	fmt.Println("Server for EX04 is running...")
	if err := http.ListenAndServe(serverAddress, nil); err != nil {
		fmt.Println("Server error:", err)
	}
}

func generateTokenHandler() http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")

		newToken := jwt.NewWithClaims(jwt.SigningMethodHS256, jwt.MapClaims{
			"admin": true,
			"exp":   time.Now().Add(time.Minute * 10).Unix(),
			"iss":   "linkfenc",
		})

		signedToken, err := newToken.SignedString(jwtSecretKey)
		if err != nil {
			fmt.Println("Error signing token:", err)
			return
		}

		w.Header().Add("Authorization", "Bearer "+signedToken)
		if err := json.NewEncoder(w).Encode(map[string]string{"token": signedToken}); err != nil {
			fmt.Println("Error encoding token:", err)
		}
	}
}

func authMiddleware(next http.HandlerFunc) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		authHeader := r.Header.Get("Authorization")
		if authHeader == "" {
			http.Error(w, "Unauthorized", http.StatusUnauthorized)
			fmt.Println("Authorization header is missing")
			return
		}

		tokenString := authHeader[7:] // Remove "Bearer " prefix
		claims := jwt.MapClaims{}
		parsedToken, err := jwt.ParseWithClaims(tokenString, claims, func(token *jwt.Token) (interface{}, error) {
			return jwtSecretKey, nil
		})

		if err != nil || !parsedToken.Valid {
			http.Error(w, "Unauthorized", http.StatusUnauthorized)
			return
		}

		next.ServeHTTP(w, r)
	}
}
