package main

import (
	"fmt"
	"log"
	"math/rand"
	"net"
	"time"

	"api"

	"github.com/golang/protobuf/ptypes/empty"
	"github.com/google/uuid"
	"google.golang.org/grpc"
	"google.golang.org/grpc/reflection"
)

const grpcPort = 8888

type server struct {
	api.UnimplementedTransmitterServiceServer
}

func main() {
	fmt.Println("Hi, i run server fo EX00")
	lis, err := net.Listen("tcp", fmt.Sprintf(":%d", grpcPort))
	if err != nil {
		log.Fatalf("failed to listen %v", err)
	}

	s := grpc.NewServer()
	reflection.Register(s)
	api.RegisterTransmitterServiceServer(s, &server{})

	log.Printf("server listening at %v", lis.Addr())

	if err = s.Serve(lis); err != nil {
		log.Fatalf("failed to serve: %v", err)
	}
}

func (s *server) TransmitData(req *empty.Empty, stream api.TransmitterService_TransmitDataServer) error {
	sessionID := uuid.New().String()

	mean := rand.Float64()*20 - 10
	std := rand.Float64()*1.2 + 0.3

	log.Printf("New session started: sessionId=%s, mean=%f, std=%f", sessionID, mean, std)
	rand.NewSource(time.Now().UnixNano())

	for {
		frequency := rand.NormFloat64()*mean + std

		entry := &api.DataEntry{
			SessionId:   sessionID,
			Frequency:   frequency,
			TimeSession: time.Now().UTC().Format(time.RFC3339),
		}

		if err := stream.Send(entry); err != nil {
			log.Printf("Error sending data: %v", err)
			return err
		}
		time.Sleep(time.Second)
	}
	// return nil
}
