package main

import (
	"fmt"
	"math/rand"
	"time"
)

func summator(mass []int) float32 {
	var summ float32 = 0
	for _, numb := range mass {
		summ += float32(numb)
	}
	ret := summ / float32(len(mass))
	return ret
}

func main() {

	realMass := []int{
		600, 1196, 1788, 2379, 2965,
		3547, 4126, 4701, 5272, 5840,
		6405, 6966, 7524, 8078, 8630,
		9179, 9724, 10265, 10804, 11340,
		11871, 12399, 12924, 13447, 13966,
		14483, 14996, 15507, 16014, 16517,
		17018, 17516, 18011, 18502, 18991,
		19477, 19960, 20440, 20917, 21392,
		21863, 22332, 22799, 23263, 23724,
		24181, 24637, 25090, 25538, 25985,
		26430, 26872, 27311, 27748, 28182,
		28612, 29040, 29466, 29889, 30309,
		30727, 31143, 31556, 31966, 32374,
		32780, 33184, 33585, 33984, 34380,
		34773, 35165, 35553, 35940, 36324,
		56996, 70942, 80371, 86746, 91052,
		93966, 95936, 97268, 98169, 98777,
		99188, 99466, 99653, 99779, 100044}

	ret := []int{}

	for i := 0; i != 1000000; i++ {
		rand.New(rand.NewSource(time.Now().UnixNano()))
		random := rand.Intn(100000)
		if random < 600 {
			ret = append(ret, 1)
			continue
		}
		for j, number := range realMass {
			if random >= number && random < realMass[j+1] {
				ret = append(ret, j+2)
				break
			}
		}
	}
	fmt.Println(summator(ret))
}
