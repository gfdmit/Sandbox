package main

import (
	"bufio"
	c "calculate"
	"flag"
	"fmt"
	"log"
	"os"
	"strconv"
	"sync"
)

func main() {

	k := *flag.Float64("k", 1, "")
	flag.Parse()

	pool := sync.Pool{
		New: func() interface{} {
			return &c.Stats{}
		},
	}

	stats := pool.Get().(*c.Stats)
	defer pool.Put(stats)
	fmt.Println("Enter 'exit' to finish process")

	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		input := scanner.Text()
		if input == "exit" {
			break
		}

		val, err := strconv.ParseFloat(input, 64)
		if err != nil {
			log.Printf("Incorrect value: %s", input)
			continue
		}

		stats.Calculate(val)
		fmt.Printf("Proccessed: %d, Mean=%.4f, Std=%.4f\n", stats.Count, stats.Mean, stats.STD)

		if stats.SendData(val, k) {
			fmt.Printf("Anomaly detected: %f\n", val)
		}
	}

}

// func (s *Stats) Calculate(val float64) {
// 	s.Count++
// 	delta := val - s.Mean
// 	s.Mean = s.Mean + delta/float64(s.Count)
// 	delta2 := val - s.Mean
// 	s.M2 = s.M2 + delta*delta2
// 	if s.Count > 1 {
// 		s.STD = math.Sqrt(s.M2 / float64(s.Count))
// 	}
// }
