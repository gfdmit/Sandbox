package main

import (
	"context"
	"fmt"
	"io"
	"net/http"
	"os"
	"os/signal"
	"sync"
	"syscall"
)

func crawlWeb(urls <-chan string, ctx context.Context) <-chan string {
	out := make(chan string)
	wg := sync.WaitGroup{}
	sem := make(chan struct{}, 8)

	go func() {
		defer close(out)
		for url := range urls {
			select {
			case <-ctx.Done():
				return
			case sem <- struct{}{}:
				wg.Add(1)
				go func(url string) {
					defer wg.Done()
					defer func() { <-sem }()
					req, err := http.NewRequestWithContext(ctx, "GET", url, nil)
					if err != nil {
						fmt.Printf("Error creating request for %s: %v\n", url, err)
						return
					}
					resp, err := http.DefaultClient.Do(req)
					if err != nil {
						fmt.Printf("Error fetching %s: %v\n", url, err)
						return
					}
					defer resp.Body.Close()

					body, err := io.ReadAll(resp.Body)
					if err != nil {
						fmt.Printf("Error reading body from %s: %v\n", url, err)
						return
					}

					out <- string(body)
				}(url)
			}
		}
		wg.Wait()
	}()

	return out
}

func main() {
	urls := make(chan string)
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	sigChan := make(chan os.Signal, 1)
	signal.Notify(sigChan, syscall.SIGINT, syscall.SIGTERM)
	go func() {
		<-sigChan
		cancel()
	}()

	go func() {
		defer close(urls)
		urls <- "https://example.com"
		urls <- "https://example.org"
		urls <- "https://example.ru"
	}()

	results := crawlWeb(urls, ctx)
	for result := range results {
		fmt.Println(result)
	}
}
