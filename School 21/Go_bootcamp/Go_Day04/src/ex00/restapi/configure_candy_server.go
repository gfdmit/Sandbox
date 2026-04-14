// This file is safe to edit. Once it exists it will not be overwritten

package restapi

import (
	"crypto/tls"
	"fmt"
	"net/http"

	"github.com/go-openapi/errors"
	"github.com/go-openapi/runtime"
	"github.com/go-openapi/runtime/middleware"

	"swagger/ex00/restapi/operations"
)

//go:generate swagger generate server --target ..\..\EX00 --name CandyServer --spec ..\candy_api.yaml --principal interface{}

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

	// if api.BuyCandyHandler == nil {
	api.BuyCandyHandler = operations.BuyCandyHandlerFunc(BuyCandyFunc)
	// }

	api.PreServerShutdown = func() {}

	api.ServerShutdown = func() {}

	return setupGlobalMiddleware(api.Serve(setupMiddlewares))
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
	valThanks := "Thank you"
	return operations.NewBuyCandyCreated().WithPayload(&operations.BuyCandyCreatedBody{Change: &change, Thanks: &valThanks})
}

// The TLS configuration before HTTPS server starts.
func configureTLS(tlsConfig *tls.Config) {
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
