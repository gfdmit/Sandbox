package tests

import (
	"stats/statistic"
	"testing"
)

func TestMean(t *testing.T) {
	t.Run("Testing Mean", func(t *testing.T) {
		var stat statistic.Statistic
		stat.SetNumbers([]int{1, 5, 3, 21, -7})
		mean := stat.FindMean()
		var testMean float32 = 4.6
		if mean != testMean {
			t.Errorf("My mean = %.2f; True mean = %.2f;\n", mean, testMean)
		}
	})
}
