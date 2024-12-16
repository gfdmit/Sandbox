package main

import "fmt"

func maxProfit(prices []int) int {
	var (
		profit   int
		cheapest int = 10e5
	)
	for i := 0; i != len(prices); i++ {
		if cheapest > prices[i] {
			cheapest = prices[i]
		} else if prices[i]-cheapest > profit {
			profit = prices[i] - cheapest
		}
	}
	return profit
}

func main() {
	mass := []int{1, 2}
	fmt.Println(maxProfit(mass))
}
