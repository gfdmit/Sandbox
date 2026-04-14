package main

import (
	"api"
	"log"
	sa "save_anomaly"
	"time"
)

func main() {
	db, err := sa.ConnectDataBase()
	if err != nil {
		log.Fatalf("%v", err)
	}
	if err = sa.SaveAnomaly(db,
		&api.DataEntry{SessionId: "1", Frequency: 2.2, TimeSession: time.Now().UTC().Format(time.RFC3339)}); err != nil {
		log.Fatalf("Failed to save anomally: %v", err)
	}
	// fmt.Println(db.Create(&DataEntry{UUID: 3, Frequency: 31.1}))
}
