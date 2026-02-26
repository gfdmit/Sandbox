package coins

import "testing"

func TestMinCoinsGreedy(t *testing.T) {
	val := 13
	coins := []int{1, 5, 10}
	expected := []int{10, 1, 1, 1}
	actual := MinCoins(val, coins)

	if len(expected) != len(actual) {
		t.Errorf("Result was incorrect, expected len: %d, actual len: %d.", len(expected), len(actual))
	}
	for i := range actual {
		if actual[i] != expected[i] {
			t.Errorf("Result was incorrect, got: %d, want: %d.", actual[i], expected[i])
		}
	}
}

func TestMinCoinsDynamicMax(t *testing.T) {
	val := 13
	coins := []int{2, 5, 10}
	expected := []int{5, 2, 2, 2, 2}
	actual := MinCoins(val, coins)

	if len(expected) != len(actual) {
		t.Errorf("Result was incorrect, expected len: %d, actual len: %d.", len(expected), len(actual))
	} else {
		for i := range actual {
			if actual[i] != expected[i] {
				t.Errorf("Result was incorrect, got: %d, want: %d.", actual[i], expected[i])
			}
		}
	}
}

func TestMinCoinsDynamicNotMax(t *testing.T) {
	val := 7
	coins := []int{1, 3, 4, 5, 10}
	expected := []int{4, 3}
	actual := MinCoins(val, coins)

	if len(expected) != len(actual) {
		t.Errorf("Result was incorrect, expected len: %d, actual len: %d.", len(expected), len(actual))
	} else {
		for i := range actual {
			if actual[i] != expected[i] {
				t.Errorf("Result was incorrect, got: %d, want: %d.", actual[i], expected[i])
			}
		}
	}
}
