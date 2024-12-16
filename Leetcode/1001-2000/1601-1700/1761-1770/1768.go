package main

import "fmt"

func mergeAlternately(word1 string, word2 string) string {
	var (
		lenWord1  = len(word1)
		lenWord2  = len(word2)
		maxLength = max(lenWord1, lenWord2)
		merged    string
	)
	for i := 0; i != maxLength; i++ {
		if lenWord1 > i {
			merged += string(word1[i])
		}
		if lenWord2 > i {
			merged += string(word2[i])
		}
	}
	return merged
}

func main() {
	fmt.Println(mergeAlternately("ab", "pqrs"))
}
