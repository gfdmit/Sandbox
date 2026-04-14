package main

import (
	archive "filesystem/ex03/archive"
	"fmt"
	"os"
)

func main() {
	var dir string
	err := archive.ParseInput(&dir, os.Args)
	if err != nil {
		fmt.Println(err)
		return
	}
	if dir == "." {
		archive.Archiver(dir, os.Args[1:])
	} else {
		archive.Archiver(dir, os.Args[3:])
	}
}
