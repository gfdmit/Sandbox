package tests

import (
	"stats/statistic"
	"testing"
)

func TestSD(t *testing.T) {
	t.Run("Testing SD", func(t *testing.T) {
		var stat statistic.Statistic
		stat.SetNumbers([]int{1, 5, 3, 21, -7})
		sd := stat.FindSD()
		var testSD float32 = 9.156419
		if sd != testSD {
			t.Errorf("My SD = %.2f; True SD = %.2f;\n", sd, testSD)
		}
	})
}
