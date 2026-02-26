package main

import (
	"fmt"
	"sync"
)

func multiplex(channels ...chan interface{}) chan interface{} {
	out := make(chan interface{})
	wg := sync.WaitGroup{}

	for _, channel := range channels {
		wg.Add(1)
		go func(channel chan interface{}) {
			defer wg.Done()
			for val := range channel {
				out <- val
			}
		}(channel)
	}

	go func() {
		wg.Wait()
		close(out)
	}()
	return out
}

func main() {
	channel1 := make(chan interface{})
	channel2 := make(chan interface{})
	channel3 := make(chan interface{})

	go func() {
		defer close(channel1)
		for i := 1; i <= 5; i++ {
			channel1 <- i
		}
	}()

	go func() {
		defer close(channel2)
		for i := 6; i <= 10; i++ {
			channel2 <- i
		}
	}()

	go func() {
		defer close(channel3)
		for i := 11; i <= 15; i++ {
			channel3 <- i
		}
	}()

	out := multiplex(channel1, channel2, channel3)

	for elem := range out {
		fmt.Println(elem)
	}
}
