package main

import (
	find "filesystem/ex00/find"
	"fmt"
	"os"
	"strings"
)

func main() {
	var flags find.Flags
	err := find.ParseInput(&flags, os.Args)
	if err != nil {
		fmt.Println(err)
		return
	}
	output, err := find.Finder(os.Args[len(os.Args)-1], flags)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(strings.Join(output, "\n"))
}
