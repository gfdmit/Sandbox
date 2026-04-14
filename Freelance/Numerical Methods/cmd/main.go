package main

import (
	"log"
	"numerical-methods/internal/app"
)

func main() {
	if err := app.Run(); err != nil {
		log.Fatal(err)
	}
}
