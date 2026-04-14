package main

import (
	"fmt"
	"os"
	"path/filepath"
)

func main() {
	if len(os.Args) != 5 || os.Args[1] != "--old" || os.Args[3] != "--new" {
		fmt.Println("error: input format: ./executable --old [filename1] --new [filename2]")
		return
	}
	old, new := os.Args[2], os.Args[4]
	if filepath.Ext(old) != ".txt" || filepath.Ext(new) != ".txt" {
		fmt.Println("error: wrong file extension")
		return
	}
	diff, err := compareDumps(old, new)
	if err != nil {
		fmt.Println("error:", err)
		return
	}
	fmt.Println(diff)
}
