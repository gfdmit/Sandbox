package main

import "fmt"

func isSubsequence(s string, t string) bool {
	var index int
	if len(s) == 0 {
		return true
	}
	for i := range t {
		if s[index] == t[i] {
			index++
		}
		if index == len(s) {
			return true
		}
	}
	return false
}

func main() {
	fmt.Println(isSubsequence("abc", "ahbgdc"))
}
