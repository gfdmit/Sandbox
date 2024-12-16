package main

import (
	"fmt"
)

func canConstruct(ransomNote string, magazine string) bool {
	if len(ransomNote) != len(magazine) {
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
	for _, elem := range hashNote {
		if elem != 0 {
			return false
		}
	}
	return true
}

func main() {
	var (
		ransomNote = "anagram"
		magazine   = "nagaram"
	)
	fmt.Println(canConstruct(ransomNote, magazine))
}
