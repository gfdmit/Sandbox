package present

import (
	"container/heap"
	"errors"
)

type Present struct {
	Value int
	Size  int
}

type PresentHeap []Present

func (p PresentHeap) Len() int {
	return len(p)
}

func (p PresentHeap) Less(i, j int) bool {
	if p[i].Value == p[j].Value {
		return p[i].Size < p[j].Size
	} else {
		return p[i].Value > p[j].Value
	}
}

func (p PresentHeap) Swap(i, j int) {
	p[i], p[j] = p[j], p[i]
}

func (p *PresentHeap) Push(present any) {
	*p = append(*p, present.(Present))
}

func (p *PresentHeap) Pop() any {
	old := *p
	n := len(old)
	present := old[n-1]
	*p = old[0 : n-1]
	return present
}

func GetNCoolestPresents(presents []Present, n int) ([]Present, error) {
	if n < 0 || n > len(presents) {
		return nil, errors.New("n is incorrect")
	}

	coolestPresents := []Present{}
	presCopy := make([]Present, len(presents))
	copy(presCopy, presents)
	presHeap := PresentHeap(presCopy)

	heap.Init(&presHeap)
	for range n {
		coolestPresents = append(coolestPresents, heap.Pop(&presHeap).(Present))
	}
	return coolestPresents, nil
}

func GrabPresents(presents []Present, capacity int) ([]Present, error) {
	if capacity < 0 {
		return nil, errors.New("capacity cannot be negative")
	}
	for _, present := range presents {
		if present.Size < 0 {
			return nil, errors.New("present size cannot be negative")
		}
	}

	matrix := make([][]int, len(presents)+1)
	for i := range matrix {
		matrix[i] = make([]int, capacity+1)
	}

	for i := 1; i <= len(presents); i++ {
		for j := 1; j <= capacity; j++ {
			if j >= presents[i-1].Size {
				matrix[i][j] = max(matrix[i-1][j], matrix[i-1][j-presents[i-1].Size]+presents[i-1].Value)
			} else {
				matrix[i][j] = matrix[i-1][j]
			}
		}
	}

	fittedPresents := []Present{}
	i, j := len(presents), capacity
	for i > 0 && j > 0 {
		if matrix[i][j] != matrix[i-1][j] {
			fittedPresents = append(fittedPresents, presents[i-1])
			j -= presents[i-1].Size
		}
		i--
	}

	return fittedPresents, nil
}
