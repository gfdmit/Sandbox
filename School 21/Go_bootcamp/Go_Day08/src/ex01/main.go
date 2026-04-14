package main

import "fmt"

type UnknownPlant struct {
	FlowerType string
	LeafType   string
	Color      int `color_scheme:"rgb"`
}

type AnotherUnknownPlant struct {
	FlowerColor int
	LeafType    string
	Height      int `unit:"inches"`
}

type Plant interface {
	Describe() string
}

func (up UnknownPlant) Describe() string {
	description := fmt.Sprintf("FlowerType:%s\nLeafType:%s\nColor(color_scheme=rgb):%d",
		up.FlowerType, up.LeafType, up.Color)
	return description
}

func (aup AnotherUnknownPlant) Describe() string {
	description := fmt.Sprintf("FlowerColor:%d\nLeafType:%s\nHeight(unit=inches):%d",
		aup.FlowerColor, aup.LeafType, aup.Height)
	return description
}

func describePlant(plant Plant) {
	description := plant.Describe()
	fmt.Println(description)
}

func main() {
	up := &UnknownPlant{
		FlowerType: "Ромашка",
		LeafType:   "Лепесток",
		Color:      255,
	}
	describePlant(up)
	aup := &AnotherUnknownPlant{
		FlowerColor: 10,
		LeafType:    "lanceolate",
		Height:      15,
	}
	describePlant(aup)
}
