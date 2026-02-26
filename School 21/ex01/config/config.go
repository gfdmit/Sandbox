package config

import (
	"fmt"
	"time"

	"github.com/ilyakaznacheev/cleanenv"
	"github.com/joho/godotenv"
)

type Config struct {
	Postgres
	HTTPServer
	Cookie
}

type Postgres struct {
	Username   string `env:"POSTGRES_USER"`
	Password   string `env:"POSTGRES_PASSWORD"`
	Host       string `env:"POSTGRES_HOST"`
	Port       string `env:"POSTGRES_PORT"`
	DB         string `env:"POSTGRES_DB"`
	Migrations string `env:"POSTGRES_MIGRATIONS"`
}

type HTTPServer struct {
	BindAddress     string        `env:"BIND_ADDRESS" env-default:"localhost"`
	BindPort        string        `env:"BIND_PORT" env-default:"8080"`
	ShutdownTimeout time.Duration `env:"SHUTDOWN_TIMEOUT" env-default:"5s"`
	ReadTimeout     time.Duration `env:"READ_TIMEOUT" env-default:"5s"`
	WriteTimeout    time.Duration `env:"WRITE_TIMEOUT" env-default:"5s"`
}

type Cookie struct {
	SecretKey string `env:"SECRET_KEY"`
}

func New(env string) (*Config, error) {
	conf := &Config{}

	if err := godotenv.Overload(env); err != nil {
		return nil, fmt.Errorf("godotenv.Overload: %v", err)
	}

	if err := cleanenv.ReadEnv(conf); err != nil {
		return nil, fmt.Errorf("cleanenv.Readenv: %v", err)
	}

	return conf, nil
}
