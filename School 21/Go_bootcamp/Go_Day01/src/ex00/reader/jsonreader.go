package reader

import (
	"comparator/ex00/recipes"
	"encoding/json"
	"fmt"
)

type JsonReader struct {
	recipes recipes.Recipes
}

func (db *JsonReader) ReadRecipes(filename string) (recipes.Recipes, error) {
	data, err := readFromFile(filename)
	if err != nil {
		return db.recipes, fmt.Errorf("error while reading the file: %v", err)
	}
	if err = json.Unmarshal(data, &db.recipes); err != nil {
		return db.recipes, fmt.Errorf("error while unmarshaling file: %v", err)
	}
	return db.recipes, nil
}
