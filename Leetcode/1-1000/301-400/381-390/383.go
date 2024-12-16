package main

import (
	"fmt"
)

func canConstruct(ransomNote string, magazine string) bool {
	if len(ransomNote) > len(magazine) {
		return false
	}
	var hashNote map[rune]int = make(map[rune]int, len(magazine))
	for _, elem := range magazine {
		hashNote[elem]++
	}
	for _, elem := range ransomNote {
		if hashNote[elem] != 0 {
			hashNote[elem]--
		} else {
			return false
		}
	}
	return true
}

func main() {
	var (
		ransomNote = "a"
		magazine   = "ab"
	)
	fmt.Println(canConstruct(ransomNote, magazine))
}
