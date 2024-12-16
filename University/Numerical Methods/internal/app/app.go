package app

import (
	"numerical-methods/experiments"
)

func Run() error {
	var (
		a, b float64
		n, d int
	)
	// fmt.Print("Введите начало отрезка: ")
	// fmt.Scan(&a)
	// fmt.Print("Введите конец отрезка: ")
	// fmt.Scan(&b)
	// fmt.Print("Введите количество иттераций: ")
	// fmt.Scan(&n)
	a, b = 0, 5
	n, d = 10, 2
	if err := experiments.ExperimentFirst("plots/experiment1/Plot.png", a, b, n, d); err != nil {
		return err
	}
	if err := experiments.ExperimentSecond("plots/experiment2/", a, b, d); err != nil {
		return err
	}
	if err := experiments.ExperimentThird("plots/experiment3/Plot.png", a, b); err != nil {
		return err
	}
	return nil
}
