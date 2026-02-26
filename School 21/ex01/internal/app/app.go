package app

import (
	"context"
	"fmt"
	"superman/ex01/config"
	v1 "superman/ex01/internal/handlers/http/v1"
	"superman/ex01/internal/httpserver"
	"superman/ex01/internal/repository/postgres"
	"superman/ex01/internal/service"
)

func Run(conf config.Config) error {
	ctx := context.Background()

	repo, err := postgres.New(conf.Postgres)
	if err != nil {
		return fmt.Errorf("error when setting up repository: %v", err)
	}

	service := service.New(repo)

	handler, err := v1.New(conf.Cookie.SecretKey, service)
	if err != nil {
		return fmt.Errorf("error when setting up handler: %v", err)
	}

	httpserver := httpserver.New(conf.HTTPServer, handler)

	return httpserver.Run(ctx)
}
