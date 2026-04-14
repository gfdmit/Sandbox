package main

import (
	"calculate"
	"context"
	"fmt"
	"log"

	"api"
	sa "save_anomaly"

	empty "github.com/golang/protobuf/ptypes/empty"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

const (
	address string = "127.0.0.1:8888"
)

func main() {
	conn, err := grpc.NewClient(address, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		log.Fatalf("Failed to connect to server: %v", err)
	}
	defer conn.Close()
	c := api.NewTransmitterServiceClient(conn)

	ctx := context.Background()

	// ctx, cancel := context.WithTimeout(ctx, 5*time.Second)
	// defer cancel()

	stream, err := c.TransmitData(ctx, &empty.Empty{})
	if err != nil {
		log.Fatalf("Error calling TransmitData: %v", err)
	}
	stats := &calculate.Stats{}
	for {
		data, err := stream.Recv()
		if err != nil {
			log.Fatalf("Error receiving data: %v", err)
		}
		fmt.Println(data)
		stats.Calculate(data.Frequency)

		if stats.SendData(data.Frequency, 1) {
			db, err := sa.ConnectDataBase()
			if err != nil {
				log.Fatalf("%v", err)
			}

			if err = sa.SaveAnomaly(db, data); err != nil {
				log.Fatalf("Failed to save anomally: %v", err)
			}

		}
	}
}
