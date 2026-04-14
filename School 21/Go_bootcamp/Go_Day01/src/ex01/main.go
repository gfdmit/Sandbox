package main

import (
	"comparator/ex00/reader"
	"fmt"
	"os"
)

func main() {
	if len(os.Args) != 5 || os.Args[1] != "--old" || os.Args[3] != "--new" {
		fmt.Println("error: input format: ./executable --old [filename1] --new [filename2]")
		return
	}
	old, err := reader.ReadDB(os.Args[2])
	if err != nil {
		fmt.Println(err)
		return
	}
	new, err := reader.ReadDB(os.Args[4])
	if err != nil {
		fmt.Println(err)
		return
	}
	diff := compareRecipes(old, new)
	fmt.Println(diff)
}
