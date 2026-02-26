package main

import (
	"fmt"
	"sync"
	"time"
)

func sleepSort(arr []int) <-chan int {
	out := make(chan int, len(arr))

	var wg sync.WaitGroup
	wg.Add(len(arr))

	for _, num := range arr {
		go func() {
			defer wg.Done()
			time.Sleep(time.Duration(num) * time.Second)
			out <- num
		}()
	}
	wg.Wait()
	close(out)

	return out
}

func main() {
	arr := []int{3, 5, 1, 2, 6, 9, 7, 4, 8}

	result := sleepSort(arr)

	for num := range result {
		fmt.Println(num)
	}
}
