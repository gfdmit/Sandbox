package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {

	ret := 0

	for i := 0; i != 100000; i++ {
		rand.New(rand.NewSource(time.Now().UnixNano()))
		random := rand.Intn(100000)
		ret++
		if random%100 >= 55 {
			i++
		}
	}
	fmt.Println(float32(ret) / 100000)
}
