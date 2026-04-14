package main

import (
	"fmt"
	"stats/menu"
	"stats/statistic"
)

func main() {
	fmt.Println("Menu:")
	fmt.Println("1. Mean")
	fmt.Println("2. Median")
	fmt.Println("3. Mode")
	fmt.Println("4. SD (Standard Deviation)")
	fmt.Print("Enter which statistics items you would like to see (e.g. 134): ")
	var menu menu.Menu
	var stat statistic.Statistic

	err := menu.ParseMenu()
	if err != nil {
		fmt.Println("Error:", err)
		return
	}

	err = stat.ParseNumbers()
	if err != nil {
		fmt.Println("Error:", err)
		return
	}

	if menu.Mean {
		fmt.Printf("Mean: %.2f\n", stat.FindMean())
	}
	if menu.Median {
		fmt.Printf("Median: %.2f\n", stat.FindMedian())
	}
	if menu.Mode {
		fmt.Println("Mode:", stat.FindMode())
	}
	if menu.SD {
		fmt.Printf("SD: %.2f\n", stat.FindSD())
	}
}
