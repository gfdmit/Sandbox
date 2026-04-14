package save_anomaly

import (
	"api"
	// _ "api"
	"log"

	"gorm.io/driver/postgres"
	"gorm.io/gorm"
)

// type DE api.DataEntry

type DataEntry struct {
	ID        uint `gorm:"primarykey"`
	UUID      string
	Frequency float64
	Timestamp string `gorm:"default:CURRENT_TIMESTAMP"`
}

func ConnectDataBase() (*gorm.DB, error) {
	dsn := "host=localhost user=postgres password=1234 dbname=postgres port=5432 sslmode=disable"
	db, err := gorm.Open(postgres.Open(dsn))
	if err != nil {
		log.Printf("Failed to connect database")
		return nil, err
	}
	err = db.AutoMigrate(&DataEntry{})
	if err != nil {
		log.Printf("Failed to futomigrate")
		return nil, err
	}
	return db, err
}

func SaveAnomaly(db *gorm.DB, de *api.DataEntry) error {
	err := db.Create(&DataEntry{
		UUID:      de.SessionId,
		Frequency: de.Frequency,
		Timestamp: de.TimeSession,
	}).Error
	return err
}
