package plotter

import (
	"image/color"
	"math"
	"numerical-methods/internal/utils"
	"os"

	"gonum.org/v1/plot"
	"gonum.org/v1/plot/plotter"
)

func PlotData(file string, tableTailor []utils.Pair, tablePolynom []utils.Pair) error {
	errors := make([]utils.Pair, len(tableTailor))
	for i, elem := range tableTailor {
		errors[i].X = elem.X
		errors[i].Y = math.Abs(elem.Y - tablePolynom[i].Y)
	}
	if err := Plot(file, errors); err != nil {
		return err
	}
	return nil
}

func Plot(file string, errors []utils.Pair) error {
	f, err := os.Create(file)
	if err != nil {
		return err
	}
	p := plot.New()
	pxys := make(plotter.XYs, len(errors))
	for i, elem := range errors {
		pxys[i].X = elem.X
		pxys[i].Y = elem.Y
	}
	l, s, err := plotter.NewLinePoints(pxys)
	l.Color = color.RGBA{255, 0, 0, 255}
	if err != nil {
		return err
	}
	p.Add(s, l)

	wt, err := p.WriterTo(512, 512, "png")
	if err != nil {
		return err
	}
	_, err = wt.WriteTo(f)
	if err != nil {
		return err
	}
	if err = f.Close(); err != nil {
		return err
	}
	return nil
}
