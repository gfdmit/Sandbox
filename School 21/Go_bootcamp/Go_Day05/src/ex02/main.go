package main

import (
	p "algorithms/present"
	"fmt"
	"log"
)

func main() {
	present := []p.Present{
		{Value: 5, Size: 1},
		{Value: 4, Size: 5},
		{Value: 3, Size: 1},
		{Value: 5, Size: 2},
	}
	coolestPresents, err := p.GetNCoolestPresents(present, 2)
	if err != nil {
		log.Fatalln("error:", err)
	}
	fmt.Println(coolestPresents)
}
