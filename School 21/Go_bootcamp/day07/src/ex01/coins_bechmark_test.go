package benchmark

import (
	ex00 "moneybag/ex00"
	"testing"
)

func BenchmarkMinCoins(b *testing.B) {
	coins := []int{1, 5, 9, 11, 45, 93, 112, 534, 993}
	for i := 0; i < b.N; i++ {
		ex00.MinCoins(1000000, coins)
	}
}

func BenchmarkMinCoins2(b *testing.B) {
	coins := []int{1, 5, 9, 11, 45, 93, 112, 534, 993}
	for i := 0; i < b.N; i++ {
		ex00.MinCoins2(1000000, coins)
	}
}
