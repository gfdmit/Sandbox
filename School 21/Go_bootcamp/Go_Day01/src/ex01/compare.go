package main

import (
	"comparator/ex00/recipes"
	"strings"
)

func compareRecipes(old, new recipes.Recipes) string {
	diff := strings.Join(compareCake(old, new, "ADDED"), "\n")
	diff += "\n" + strings.Join(compareCake(new, old, "REMOVED"), "\n")
	diff += "\n" + strings.Join(compareTimeChange(old, new), "\n")
	diff += "\n" + strings.Join(compareIngredient(old, new, "ADDED"), "\n")
	diff += "\n" + strings.Join(compareIngredient(new, old, "REMOVED"), "\n")
	diff += "\n" + strings.Join(compareIngredientCount(old, new), "\n")
	diff += "\n" + strings.Join(compareIngredientUnit(old, new, "REMOVED"), "\n")
	diff += strings.Join(compareIngredientUnit(new, old, "ADDED"), "\n")
	return diff
}

func compareCake(s1, s2 recipes.Recipes, changeType string) (diff []string) {
	hash := make(map[string]bool)
	var changeStr string
	if changeType == "ADDED" {
		changeStr = "ADDED cake "
	} else {
		changeStr = "REMOVED cake "
	}
	for _, e := range s1.Cakes {
		hash[e.Name] = true
	}
	for _, e := range s2.Cakes {
		if !hash[e.Name] {
			diff = append(diff, changeStr+"\""+e.Name+"\"")
			hash[e.Name] = true
		}
	}
	return
}

func compareTimeChange(s1, s2 recipes.Recipes) (diff []string) {
	hash := make(map[string]string)
	for _, e := range s1.Cakes {
		hash[e.Name] = e.Time
	}
	for _, e := range s2.Cakes {
		if hash[e.Name] != "" && hash[e.Name] != e.Time {
			diff = append(diff, "CHANGED cooking time for cake  \""+e.Name+"\" - \""+e.Time+"\" instead of \""+hash[e.Name]+"\"")
		}
	}
	return
}

func compareIngredient(s1, s2 recipes.Recipes, changeType string) (diff []string) {
	hash := make(map[string][]recipes.Item)
	var changeStr string
	if changeType == "ADDED" {
		changeStr = "ADDED ingredient "
	} else {
		changeStr = "REMOVED ingredient "
	}
	for _, e := range s1.Cakes {
		hash[e.Name] = append(hash[e.Name], e.Ingredients...)
	}
	for _, e := range s2.Cakes {
		if hash[e.Name] != nil {
			for _, i := range e.Ingredients {
				diff = append(diff, compareIngredientHelper(hash[e.Name], i, e, changeStr)...)
			}
		}
	}
	return
}

func compareIngredientHelper(hash []recipes.Item, i recipes.Item, e recipes.Cake, changeStr string) (diff []string) {
	index := -1
	for ind, v := range hash {
		if v.Name == i.Name {
			index = ind
			break
		}
	}
	if index == -1 {
		diff = append(diff, changeStr+"\""+i.Name+"\""+" for cake  \""+e.Name+"\"")
	}
	return
}

func compareIngredientCount(s1, s2 recipes.Recipes) (diff []string) {
	hash := make(map[string][]recipes.Item)
	var changeStr string = "CHANGED unit "
	for _, e := range s1.Cakes {
		hash[e.Name] = append(hash[e.Name], e.Ingredients...)
	}
	for _, e := range s2.Cakes {
		if hash[e.Name] != nil {
			for _, i := range e.Ingredients {
				diff = append(diff, compareIngredientCountHelper(hash[e.Name], i, e, changeStr)...)
			}
		}
	}
	return
}

func compareIngredientCountHelper(hash []recipes.Item, i recipes.Item, e recipes.Cake, changeStr string) (diff []string) {
	index := -1
	for ind, v := range hash {
		if v.Name == i.Name {
			index = ind
			break
		}
	}
	if index == -1 {
		return
	}
	if hash[index].Unit != i.Unit && i.Unit != "" {
		diff = append(diff, changeStr+"for ingredient \""+i.Name+"\" for cake  \""+e.Name+"\" - \""+i.Unit+"\" instead of \""+hash[index].Unit+"\"")
	} else if hash[index].Count != i.Count {
		diff = append(diff, changeStr+"count for ingredient \""+i.Name+"\" for cake  \""+e.Name+"\" - \""+i.Count+"\" instead of \""+hash[index].Count+"\"")
	}
	return
}

func compareIngredientUnit(s1, s2 recipes.Recipes, changeType string) (diff []string) {
	hash := make(map[string][]recipes.Item)
	var changeStr string
	if changeType == "ADDED" {
		changeStr = "ADDED unit \""
	} else {
		changeStr = "REMOVED unit \""
	}
	for _, e := range s1.Cakes {
		hash[e.Name] = append(hash[e.Name], e.Ingredients...)
	}
	for _, e := range s2.Cakes {
		if hash[e.Name] != nil {
			for _, i := range e.Ingredients {
				diff = append(diff, compareIngredientUnitHelper(hash[e.Name], i, e, changeStr)...)
			}
		}
	}
	return
}

func compareIngredientUnitHelper(hash []recipes.Item, i recipes.Item, e recipes.Cake, changeStr string) (diff []string) {
	index := -1
	for ind, v := range hash {
		if v.Name == i.Name {
			index = ind
			break
		}
	}
	if index == -1 {
		return
	}
	if hash[index].Unit != i.Unit && i.Unit == "" {
		diff = append(diff, changeStr+hash[index].Unit+"\" for ingredient \""+i.Name+"\" for cake  \""+e.Name+"\"")
	}
	return
}
