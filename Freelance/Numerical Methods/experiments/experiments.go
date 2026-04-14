package experiments

import (
	"numerical-methods/internal/plotter"
	"numerical-methods/internal/polynom"
	"numerical-methods/internal/tailor"
	"numerical-methods/internal/utils"
	"strconv"
)

func ExperimentFirst(file string, a float64, b float64, n int, d int) error {
	var (
		tableTailor  []utils.Pair
		tablePolynom []utils.Pair
	)
	tailor.Tabulate(a, b, n, d, &tableTailor)
	polynom.CreatePolynom(d, tableTailor, &tablePolynom)
	err := plotter.PlotData(file, tableTailor, tablePolynom)
	if err != nil {
		return err
	}
	return nil
}

func ExperimentSecond(dir string, a float64, b float64, d int) error {
	knots := []int{5, 8, 13, 20, 40}
	for i, knot := range knots {
		file := dir + "Plot" + strconv.Itoa(i) + ".png"
		err := ExperimentFirst(file, a, b, knot, d)
		if err != nil {
			return err
		}
	}
	return nil
}

func ExperimentThird(file string, a float64, b float64) error {
	var errors []utils.Pair
	for i := 10; i <= 50; i++ {
		var (
			tableTailor  []utils.Pair
			tablePolynom []utils.Pair
			maxErr       float64
		)
		tailor.Tabulate(a, b, i, 10, &tableTailor)
		polynom.CreatePolynom(10, tableTailor, &tablePolynom)
		for j, elem := range tableTailor {
			if maxErr < elem.Y-tablePolynom[j].Y {
				maxErr = elem.Y - tablePolynom[j].Y
			}
		}
		errors = append(errors, *utils.NewPair(float64(i), maxErr))
	}
	if err := plotter.Plot(file, errors); err != nil {
		return err
	}
	return nil
}
