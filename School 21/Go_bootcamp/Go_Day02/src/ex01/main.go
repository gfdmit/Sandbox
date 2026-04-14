package main

import (
	"errors"
	stat "filesystem/ex01/stat"
	"fmt"
	"os"
	"strings"
)

func main() {
	var flags stat.Flags
	var start int = 2
	err := stat.ParseInput(&flags, os.Args)
	if errors.Is(err, stat.ErrNoFlag) {
		start = 1
	} else if err != nil {
		fmt.Println(err)
		return
	}
	output := stat.Stater(os.Args[start:], flags)
	fmt.Println(strings.Join(output, "\n"))
}
