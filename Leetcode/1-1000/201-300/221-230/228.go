package main

import (
	"fmt"
	"strconv"
)

func summaryRanges(nums []int) []string {
	if len(nums) == 0 {
		return nil
	} else if len(nums) == 1 {
		return []string{strconv.Itoa(nums[0])}
	}
	var (
		result []string
		start  int = nums[0]
	)
	for i := 0; i != len(nums)-1; i++ {
		if nums[i+1]-nums[i] != 1 {
			if start == nums[i] {
				result = append(result, strconv.Itoa(start))
				start = nums[i+1]
			} else {
				result = append(result, strconv.Itoa(start)+"->"+strconv.Itoa(nums[i]))
				start = nums[i+1]
			}
		}
	}
	if nums[len(nums)-1]-nums[len(nums)-2] == 1 {
		result = append(result, strconv.Itoa(start)+"->"+strconv.Itoa(nums[len(nums)-1]))
	} else {
		result = append(result, strconv.Itoa(start))
	}
	return result
}

func main() {
	fmt.Println(summaryRanges([]int{-1}))
}
