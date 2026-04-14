package main

import (
	"log"
	"superman/ex01/config"
	"superman/ex01/internal/app"
)

func main() {
	conf, err := config.New(".env")
	if err != nil {
		log.Fatalf("[SETUP ERROR] error when reading config: %v", err)
	}

	err = app.Run(*conf)
	if err != nil {
		log.Fatalf("[APPLICATION ERROR] error: %v", err)
	}

	log.Println("[SHUTDOWN] service shut down gracefully")
}
