package main

import "fmt"

func containsDuplicate(nums []int) bool {
	var dup map[int]bool = make(map[int]bool, len(nums))
	for _, i := range nums {
		if dup[i] {
			return true
		} else {
			dup[i] = true
		}
	}
	return false
}

func main() {
	fmt.Println(containsDuplicate([]int{1, 2, 3, 1}))
}
