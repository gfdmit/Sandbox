package coins

import "testing"

func TestMinCoins2Greedy(t *testing.T) {
	val := 13
	coins := []int{1, 5, 10}
	expected := []int{10, 1, 1, 1}
	actual := MinCoins2(val, coins)

	if len(expected) != len(actual) {
		t.Errorf("Result was incorrect, expected len: %d, actual len: %d.", len(expected), len(actual))
	}
	for i := range actual {
		if actual[i] != expected[i] {
			t.Errorf("Result was incorrect, got: %d, want: %d.", actual[i], expected[i])
		}
	}
}

func TestMinCoins2DynamicMax(t *testing.T) {
	val := 13
	coins := []int{2, 5, 10}
	expected := []int{5, 2, 2, 2, 2}
	actual := MinCoins2(val, coins)

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

func TestMinCoins2DynamicNotMax(t *testing.T) {
	val := 7
	coins := []int{1, 3, 4, 5, 10}
	expected := []int{4, 3}
	actual := MinCoins2(val, coins)

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

func TestMinCoins2Empty(t *testing.T) {
	val := 7
	coins := []int{}
	expected := []int{}
	actual := MinCoins2(val, coins)

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

func TestMinCoins2Imposible(t *testing.T) {
	val := 7
	coins := []int{9, 10, 11}
	expected := []int{}
	actual := MinCoins2(val, coins)

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

func TestMinCoins2Duplicated(t *testing.T) {
	val := 7
	coins := []int{1, 1, 1, 3, 5}
	expected := []int{5, 1, 1}
	actual := MinCoins2(val, coins)

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

func TestMinCoins2Unsorted(t *testing.T) {
	val := 14
	coins := []int{3, 2, 8, 5, 1}
	expected := []int{8, 5, 1}
	actual := MinCoins2(val, coins)

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

func TestMinCoins2UnsortedDuplacated(t *testing.T) {
	val := 14
	coins := []int{3, 8, 2, 1, 8, 5, 1}
	expected := []int{8, 5, 1}
	actual := MinCoins2(val, coins)

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

func TestMinCoins2Large1(t *testing.T) {
	val := 1334
	coins := []int{2, 5, 19}
	expected := []int{19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 2, 2}
	actual := MinCoins2(val, coins)

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

func TestMinCoins2Large2(t *testing.T) {
	val := 1334
	coins := []int{2, 5, 19}
	expected := []int{19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 2, 2}
	actual := MinCoins2(val, coins)

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

func TestMinCoins2Large3(t *testing.T) {
	val := 1334
	coins := []int{2, 5, 19}
	expected := []int{19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 2, 2}
	actual := MinCoins2(val, coins)

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

func TestMinCoins2Large4(t *testing.T) {
	val := 1334
	coins := []int{2, 5, 19}
	expected := []int{19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 2, 2}
	actual := MinCoins2(val, coins)

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

func TestMinCoins2Large5(t *testing.T) {
	val := 1334
	coins := []int{2, 5, 19}
	expected := []int{19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 2, 2}
	actual := MinCoins2(val, coins)

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
