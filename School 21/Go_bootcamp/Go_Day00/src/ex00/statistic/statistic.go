package statistic

import (
	"bufio"
	"errors"
	"math"
	"os"
	"sort"
	"strconv"
)

type Statistic struct {
	numbers []int
	Mean    float32
	Median  float32
	SD      float32
	Mode    int
}

func (stat *Statistic) ParseNumbers() error {
	var number int
	var err error
	in := bufio.NewScanner(os.Stdin)
	for in.Scan() {
		if in.Err() != nil {
			err = in.Err()
			break
		}
		number, err = strconv.Atoi(in.Text())
		if err != nil {
			break
		}
		stat.numbers = append(stat.numbers, number)
	}
	if len(stat.numbers) == 0 {
		err = errors.New("numbers are empty")
	}
	return err
}

func (stat *Statistic) FindMean() float32 {
	var mean float32
	for _, value := range stat.numbers {
		mean += float32(value)
	}
	stat.Mean = mean / float32(len(stat.numbers))
	return stat.Mean
}

func (stat *Statistic) FindMedian() float32 {
	var median float32
	sort.Ints(stat.numbers)
	length := len(stat.numbers)
	if length%2 == 0 {
		median = float32(stat.numbers[length/2]+stat.numbers[length/2-1]) / 2.0
	} else {
		median = float32(stat.numbers[length/2])
	}
	stat.Median = median
	return stat.Median
}

func (stat *Statistic) FindMode() int {
	var mode int = stat.numbers[0]
	var counter, max int
	sort.Ints(stat.numbers)
	for i := 0; i != len(stat.numbers)-1; i++ {
		if stat.numbers[i] == stat.numbers[i+1] {
			counter++
			if counter > max {
				max = counter
				mode = stat.numbers[i]
			}
		} else {
			counter = 0
		}
	}
	stat.Mode = mode
	return stat.Mode
}

func (stat *Statistic) FindSD() float32 {
	stat.FindMean()
	mean := stat.Mean
	var sum float64
	for _, value := range stat.numbers {
		sum += math.Pow(float64((float32(value) - mean)), 2)
	}
	stat.SD = float32(math.Sqrt(sum / float64(len(stat.numbers))))
	return stat.SD
}

func (stat *Statistic) SetNumbers(numbers []int) {
	stat.numbers = numbers
}
