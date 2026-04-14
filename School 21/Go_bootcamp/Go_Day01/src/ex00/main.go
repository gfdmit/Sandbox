package main

import (
	reader "comparator/ex00/reader"
	recipes "comparator/ex00/recipes"
	"encoding/json"
	"encoding/xml"
	"fmt"
	"os"
	"path/filepath"
)

func main() {
	if len(os.Args) != 3 || os.Args[1] != "-f" {
		fmt.Println("error: input format: ./executable -f [filename]")
		return
	}
	data, err := reader.ReadDB(os.Args[2])
	if err != nil {
		fmt.Println(err)
		return
	}
	if filepath.Ext(os.Args[2]) == ".xml" {
		PrintDB(data, "json")
	} else {
		PrintDB(data, "xml")
	}
}

func PrintDB(recipes recipes.Recipes, format string) {
	var data []byte
	var err error
	if format == "json" {
		data, err = json.MarshalIndent(recipes, "", "    ")
	} else {
		data, err = xml.MarshalIndent(recipes, "", "    ")
	}
	if err == nil {
		fmt.Println(string(data))
	} else {
		fmt.Println("error in marshaling data")
	}
}
