// This file is safe to edit. Once it exists it will not be overwritten

package restapi

import (
	"crypto/tls"
	"crypto/x509"
	"fmt"
	"log"
	"net/http"
	"os"
	"swagger/ex02/candy_server/ask_cow"
	"swagger/ex02/candy_server/restapi/operations"

	"github.com/go-openapi/errors"
	"github.com/go-openapi/runtime"
	"github.com/go-openapi/runtime/middleware"
	"github.com/go-openapi/runtime/security"
)

//go:generate swagger generate server --target ..\..\candy_server --name CandyServer --spec ..\..\candy_api_auth.yaml --principal interface{}

func configureFlags(api *operations.CandyServerAPI) {
	// api.CommandLineOptionsGroups = []swag.CommandLineOptionsGroup{ ... }
}

func configureAPI(api *operations.CandyServerAPI) http.Handler {
	// configure the api here
	api.ServeError = errors.ServeError

	// Set your custom logger if needed. Default one is log.Printf
	// Expected interface func(string, ...interface{})
	//
	// Example:
	// api.Logger = log.Printf

	api.UseSwaggerUI()
	// To continue using redoc as your UI, uncomment the following line
	// api.UseRedoc()

	api.JSONConsumer = runtime.JSONConsumer()

	api.JSONProducer = runtime.JSONProducer()

	// Applies when the "x-token" header is set
	// if api.MtlsAuthAuth == nil {
	// 	api.MtlsAuthAuth = func(token string) (interface{}, error) {
	// 		return nil, errors.NotImplemented("api key auth (mtlsAuth) x-token from header param [x-token] has not yet been implemented")
	// 	}
	// }

	api.MtlsAuthAuth = func(token string) (interface{}, error) {
		if token == "abcdefuvwxyz" {
			prin := string(token)
			return &prin, nil
		}
		// api.Logger("Access attempt with incorrect api key auth: %s", token)
		return nil, errors.New(401, "incorrect api key auth")
	}

	// Set your custom authorizer if needed. Default one is security.Authorized()
	// Expected interface runtime.Authorizer
	//
	// Example:
	api.APIAuthorizer = security.Authorized()

	// if api.BuyCandyHandler == nil {
	api.BuyCandyHandler = operations.BuyCandyHandlerFunc(BuyCandyAuth)
	// (func(params operations.BuyCandyParams, principal interface{}) middleware.Responder {
	// 		return middleware.NotImplemented("operation operations.BuyCandy has not yet been implemented")
	// 	})
	// }

	api.PreServerShutdown = func() {}

	api.ServerShutdown = func() {}

	return setupGlobalMiddleware(api.Serve(setupMiddlewares))
}

// The TLS configuration before HTTPS server starts.
func configureTLS(tlsConfig *tls.Config) {
	tlsConfig.ClientAuth = tls.RequireAndVerifyClientCert
	tlsConfig.ClientCAs = loadCA()
	// Make all necessary changes to the TLS configuration here.
}

// As soon as server is initialized but not run yet, this function will be called.
// If you need to modify a config, store server instance to stop it individually later, this is the place.
// This function can be called multiple times, depending on the number of serving schemes.
// scheme value will be set accordingly: "http", "https" or "unix".
func configureServer(s *http.Server, scheme, addr string) {
}

// The middleware configuration is for the handler executors. These do not apply to the swagger.json document.
// The middleware executes after routing but before authentication, binding and validation.
func setupMiddlewares(handler http.Handler) http.Handler {
	return handler
}

// The middleware configuration happens before anything, this middleware also applies to serving the swagger.json document.
// So this is a good place to plug in a panic handling middleware, logging and metrics.
func setupGlobalMiddleware(handler http.Handler) http.Handler {
	return handler
}

func BuyCandyAuth(params operations.BuyCandyParams, principal interface{}) middleware.Responder {
	if principal == nil {
		return middleware.Error(401, "Unauthorized: Invalid client authentication")
	}
	// if

	return BuyCandyFunc(params)
}

func BuyCandyFunc(params operations.BuyCandyParams) middleware.Responder {
	candy_map := map[string]int64{"CE": 10, "AA": 15, "NT": 17, "DE": 21, "YR": 23}

	candy_price := candy_map[*params.Order.CandyType]
	candy_count := *params.Order.CandyCount
	money := *params.Order.Money
	total_price := candy_price * candy_count
	change := money - total_price

	if candy_price <= 0 {
		return operations.NewBuyCandyBadRequest().WithPayload(&operations.BuyCandyBadRequestBody{Error: "Invalid candy type"})
	}

	if money < 0 || candy_count < 0 {
		var strerr string
		if money < 0 && candy_count < 0 {
			strerr = "Money and Candy count"
		} else if money < 0 {
			strerr = "Money"
		} else {
			strerr = "Candy count"
		}
		return operations.NewBuyCandyBadRequest().WithPayload(&operations.BuyCandyBadRequestBody{Error: strerr + " must be non-negative"})
	}

	if change < 0 {
		needed := 0 - change
		return operations.NewBuyCandyPaymentRequired().WithPayload(&operations.BuyCandyPaymentRequiredBody{Error: fmt.Sprintf("You need %d more money!", needed)})
	}
	valThanks := ask_cow.AskCow("Thank you")
	return operations.NewBuyCandyCreated().WithPayload(&operations.BuyCandyCreatedBody{Change: &change, Thanks: &valThanks})
}

func loadCA() *x509.CertPool {
	certPool := x509.NewCertPool()
	part_to_CA := "../../../../EX01/certs/minica.pem"

	caCert, err := os.ReadFile(part_to_CA)
	if err != nil {
		log.Fatalf("Error loading CA file: %v", err)
	}
	certPool.AppendCertsFromPEM(caCert)
	return certPool
}

// func isValidCert(cert string) bool {
// 	return cert == ""
// }
