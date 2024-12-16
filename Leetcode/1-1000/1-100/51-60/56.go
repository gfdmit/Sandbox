package main

import (
	"cmp"
	"fmt"
	"slices"
)

func merge(intervals [][]int) [][]int {
	slices.SortFunc(intervals, func(a, b []int) int {
		return cmp.Compare(a[0], b[0])
	})

	var (
		start_end = []int{intervals[0][0], intervals[0][1]}
		matrix    [][]int
	)

	for i := range intervals[:len(intervals)-1] {
		if intervals[i+1][0] <= start_end[1] {
			start_end[1] = max(start_end[1], intervals[i+1][1])
		} else {
			matrix = append(matrix, start_end)
			start_end = []int{intervals[i+1][0], intervals[i+1][1]}
		}
	}
	matrix = append(matrix, start_end)
	return matrix
}

func main() {
	var matrix = [][]int{{2, 3}, {4, 5}, {6, 7}, {8, 9}}
	fmt.Println(merge(matrix))
}
