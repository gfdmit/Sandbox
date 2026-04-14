// Пакет ex00 предоставляет функции для вычисления минимального количества монет, для набора определенной
// суммы из монет представленный номиналов
package coins

import (
	"fmt"
	"math"
	"sort"
)

func MinCoins(val int, coins []int) []int {
	res := make([]int, 0)
	i := len(coins) - 1
	for i >= 0 {
		for val >= coins[i] {
			val -= coins[i]
			res = append(res, coins[i])
		}
		i -= 1
	}
	return res
}

// deleteDuplicates принимает отсортированный срез номиналов монет и удаляет дубликаты, путём создания нового среза.
//
// Пример использования:
//
//	coins := []int{1, 1, 3, 3, 5, 7}
//	result := deleteDuplicates(coins)
//	fmt.Println(result) // Вывод: [1, 3, 5, 7]
func deleteDuplicates(coins []int) []int {
	set := make([]int, 0)
	for i := range coins {
		if i != 0 {
			if coins[i] != coins[i-1] {
				set = append(set, coins[i-1])
			}
		}
	}
	set = append(set, coins[len(coins)-1])
	return set
}

// validate принимает срез номиналов монет, если сред пустой, возвращает ошибку, которая обрабатывается в MinCoins2.
// После сортирует его в порядке возрастания и удаляет дубликаты, в функции deleteDuplicates.
//
// Пример использования:
//
//	coins := []int{5, 1, 3, 3, 7, 1}
//	result := validate(coins)
//	fmt.Println(result) // Вывод: [1, 3, 5, 7]
func validate(coins []int) ([]int, error) {
	if len(coins) == 0 {
		return nil, fmt.Errorf("slice is empty")
	}
	sort.Slice(coins, func(i, j int) bool {
		return coins[i] < coins[j]
	})
	coins = deleteDuplicates(coins)
	return coins, nil
}

// Функция minCoins2 определяет минимальное количество монет, необходимое для набора указанной суммы.
// В отличие от базовой версии minCoins, данная функция основана на алгоритме динамического программирования
// и всегда находит самый оптимальный вариант. Также она корректно обрабатывает случаи, когда массив номиналов монет
// содержит повторяющиеся значения или не отсортирован. Если массив номиналов пуст, функция возвращает пустой срез.
// Если же ответ найти нельзя, функция так же возвращает пустой срез.
//
// Алгоритм работает корректно благодаря следующим шагам:
// 1. Удалению дубликатов из массива номиналов.
// 2. Сортировке массива для упрощения дальнейших вычислений.
//
// Пример использования:
//
//	coins := []int{1, 3, 4, 7, 13, 15}
//	result := minCoins2(23, coins)
//	fmt.Println(result) // Результат: [15, 4, 4]
//
// Для генерации документации по этой функции можно воспользоваться командой:
//
// godoc -http=:6060
// если godoc не установлен, установите его командой:
// go install golang.org/x/tools/cmd/godoc@latest
//
// После этого откройте браузер и перейдите по адресу http://localhost:6060/pkg/moneybag/ex00/, чтобы просмотреть документацию.
func MinCoins2(val int, coins []int) []int {
	coins, err := validate(coins)
	if err != nil {
		return []int{}
	}

	res := make([]int, val+1)
	coin_used := make([]int, val+1)
	target := make([]int, 0)
	for i := range res {
		res[i] = math.MaxInt - 1
	}
	res[0] = 0
	for i := range coins {
		for j := range res {
			if coins[i] <= j {
				if res[j] >= res[j-coins[i]]+1 {
					coin_used[j] = coins[i]
					res[j] = res[j-coins[i]] + 1
				}
			}
		}
	}
	if res[len(res)-1] == math.MaxInt-1 {
		return []int{}
	}
	for val != 0 {
		target = append(target, coin_used[val])
		val -= target[len(target)-1]
	}
	return target
}
