package tests

import (
	"stats/statistic"
	"testing"
)

func TestMode(t *testing.T) {
	t.Run("Testing Mode", func(t *testing.T) {
		var stat statistic.Statistic
		stat.SetNumbers([]int{1, 5, 3, 5, 5, 21, 1, -7})
		mode := stat.FindMode()
		testMode := 5
		if mode != testMode {
			t.Errorf("My mode = %d; True mode = %d;\n", mode, testMode)
		}
	})
}
