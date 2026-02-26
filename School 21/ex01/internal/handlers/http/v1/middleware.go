package v1

import (
	"net/http"

	"golang.org/x/time/rate"
)

var limiter = rate.NewLimiter(rate.Limit(100), 100)

func RateLimitMiddleware(next http.HandlerFunc) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		if !limiter.Allow() {
			http.Error(w, "Too many requests", http.StatusTooManyRequests)
			return
		}
		next.ServeHTTP(w, r)
	}
}
