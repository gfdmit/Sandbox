package reader

import (
	"comparator/ex00/recipes"
	"fmt"
	"os"
	"path/filepath"
)

type DBReader interface {
	ReadRecipes(file string) (recipes.Recipes, error)
}

func readFromFile(filename string) ([]byte, error) {
	data, err := os.ReadFile(filename)
	if err != nil {
		return nil, err
	}
	return data, nil
}

func ReadDB(filename string) (recipes.Recipes, error) {
	var dbReader DBReader
	ext := filepath.Ext(filename)
	if ext == ".xml" {
		dbReader = &XmlReader{}
	} else if ext == ".json" {
		dbReader = &JsonReader{}
	} else {
		return recipes.Recipes{}, fmt.Errorf("error: incorrect file extension")
	}
	data, err := dbReader.ReadRecipes(filename)
	if err != nil {
		return recipes.Recipes{}, err
	}
	return data, nil
}
