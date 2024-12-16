package tailor

import (
	"math"

	utils "numerical-methods/internal/utils"
)

func Tabulate(a float64, b float64, n int, d int, table *[]utils.Pair) {
	var h = (b - a) / float64(d*n)
	for i := 0; i <= n*d; i++ {
		var x = a + float64(i)*h
		*table = append(*table, *utils.NewPair(x, Tailor(x)))
	}
}

func Tailor(x float64) float64 {
	var (
		term    float64 = x
		counter int
		sum     float64
	)
	for math.Abs(term) > utils.EPS {
		sum += term
		q := -1 * math.Pow(x, 2) * float64((2*counter + 1))
		q /= float64(2*counter+2) * float64(2*counter+3) * float64(2*counter+3)
		term *= q
		counter++
	}
	return sum + term
}

func RealTableTailor(d int, tableTailor []utils.Pair) []utils.Pair {
	var realTableTailor = make([]utils.Pair, len(tableTailor)/d+len(tableTailor)%d)
	for i := 0; i < len(tableTailor); i += d {
		realTableTailor[i/d] = tableTailor[i]
	}
	return realTableTailor
}
