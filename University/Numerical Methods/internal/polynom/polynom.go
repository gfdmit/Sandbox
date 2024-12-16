package polynom

import (
	"numerical-methods/internal/tailor"
	"numerical-methods/internal/utils"
)

func CreatePolynom(d int, tableTailor []utils.Pair, tablePolynom *[]utils.Pair) {
	var (
		realTableTailor    = tailor.RealTableTailor(d, tableTailor)
		dividedDifferences = FindDividedDifferences(realTableTailor)
	)
	for i := range len(tableTailor) {
		*tablePolynom = append(*tablePolynom, *utils.NewPair(tableTailor[i].X, NewtonPolynomialInterpolation(tableTailor[i].X, d, tableTailor, dividedDifferences)))
	}
}

func FindDividedDifferences(tableTailor []utils.Pair) []float64 {
	var dividedDifferences = make([]float64, len(tableTailor))
	for i := range tableTailor {
		dividedDifferences[i] = tableTailor[i].Y
	}
	for i := 1; i < len(tableTailor); i++ {
		old := dividedDifferences[i-1]
		for j := i; j != len(tableTailor); j++ {
			now := dividedDifferences[j]
			dividedDifferences[j] = (dividedDifferences[j] - old) / (tableTailor[j].X - tableTailor[j-i].X)
			old = now
		}
	}
	return dividedDifferences
}

func NewtonPolynomialInterpolation(x float64, d int, tableTailor []utils.Pair, dividedDifferences []float64) float64 {
	var (
		sum  float64
		term float64 = 1
	)
	for i := range len(tableTailor)/d + len(tableTailor)%d {
		sum += dividedDifferences[i] * term
		term *= x - tableTailor[i*d].X
	}
	return sum
}
