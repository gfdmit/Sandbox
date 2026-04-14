package tests

import (
	"stats/statistic"
	"testing"
)

func TestMedian(t *testing.T) {
	t.Run("Testing Median", func(t *testing.T) {
		var stat statistic.Statistic
		stat.SetNumbers([]int{1, 5, 3, 21, -7})
		median := stat.FindMedian()
		var testMedian float32 = 3
		if median != testMedian {
			t.Errorf("My median = %.2f; True median = %.2f;\n", median, testMedian)
		}
	})
}
