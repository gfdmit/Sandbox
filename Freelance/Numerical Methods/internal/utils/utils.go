package utils

const EPS = 1e-9

type Pair struct {
	X float64
	Y float64
}

func NewPair(x float64, y float64) *Pair {
	return &Pair{x, y}
}
