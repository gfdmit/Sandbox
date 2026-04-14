package main

import (
	p "algorithms/present"
	"fmt"
	"log"
)

func main() {
	present := []p.Present{
		{Value: 5, Size: 6},
		{Value: 3, Size: 4},
		{Value: 1, Size: 3},
		{Value: 3, Size: 2},
		{Value: 6, Size: 5},
	}
	coolestPresents, err := p.GrabPresents(present, 16)
	if err != nil {
		log.Fatalln("error:", err)
	}
	fmt.Println(coolestPresents)
}
