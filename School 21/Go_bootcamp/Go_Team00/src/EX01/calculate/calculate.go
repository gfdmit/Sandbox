package calculate

import (
	"math"
)

type Stats struct {
	Count int
	Mean  float64
	STD   float64
	M2    float64
}

func (s *Stats) Calculate(val float64) {
	s.Count++
	delta := val - s.Mean
	s.Mean = s.Mean + delta/float64(s.Count)
	delta2 := val - s.Mean
	s.M2 = s.M2 + delta*delta2
	if s.Count > 1 {
		s.STD = math.Sqrt(s.M2 / float64(s.Count))
	}
}

func (s *Stats) SendData(val float64, k float64) bool {
	if s.Count > 50 {
		return math.Abs(val-s.Mean) > s.STD*k
	}
	return false
}
