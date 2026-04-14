package main

import (
	"crypto/tls"
	"crypto/x509"
	"flag"
	"fmt"
	"log"
	"net/http"
	"os"
	"swagger/ex01/candy_client/client"
	"swagger/ex01/candy_client/client/operations"

	httptransport "github.com/go-openapi/runtime/client"
	"github.com/go-openapi/strfmt"
)

var (
	vCC, vM int64
	vCT     string
)

func init() {
	flag.StringVar(&vCT, "k", "AA", "Candy type")
	flag.Int64Var(&vCC, "c", 2, "Count candy")
	flag.Int64Var(&vM, "m", 50, "Money")
	flag.Parse()
}

func main() {

	caCert, err := os.ReadFile("../certs/minica.pem")
	if err != nil {
		log.Fatalf("Error loading CA file: %v", err)
	}
	caCertPool := x509.NewCertPool()
	caCertPool.AppendCertsFromPEM(caCert)

	cliernCert, err := tls.LoadX509KeyPair("../certs/client.crt", "../certs/client.key")
	if err != nil {
		log.Fatalf("Error loading files: %v", err)
	}

	tlsConfig := &tls.Config{
		Certificates:       []tls.Certificate{cliernCert},
		RootCAs:            caCertPool,
		InsecureSkipVerify: false,
	}

	cfg := client.DefaultTransportConfig().WithHost(client.DefaultHost + ":3333")

	transport := httptransport.New(cfg.Host, cfg.BasePath, cfg.Schemes)
	transport.Transport = &http.Transport{TLSClientConfig: tlsConfig}

	client := operations.New(transport, strfmt.Default)
	params := operations.NewBuyCandyParams()
	params.Order = operations.BuyCandyBody{
		CandyCount: &vCC,
		CandyType:  &vCT,
		Money:      &vM,
	}

	auth := httptransport.APIKeyAuth("x-token", "header", "abcdefuvwxyz")

	res, err := client.BuyCandy(params, auth)
	if err != nil {
		switch e := err.(type) {
		case *operations.BuyCandyBadRequest:
			fmt.Println(e.GetPayload().Error)

		case *operations.BuyCandyPaymentRequired:
			fmt.Println(e.GetPayload().Error)

		default:
			fmt.Println("Unkown error")
		}
	} else {
		r := res.GetPayload()
		fmt.Printf("%s! Your change is %d\n", *r.Thanks, *r.Change)
	}

}
