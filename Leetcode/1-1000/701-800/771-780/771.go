package main

func numJewelsInStones(jewels string, stones string) int {
	var counter int
	for _, i := range jewels {
		for _, j := range stones {
			if i == j {
				counter++
			}
		}
	}
	return counter
}

func main() {
	println(numJewelsInStones("aA", "aAAbbbb"))
}
