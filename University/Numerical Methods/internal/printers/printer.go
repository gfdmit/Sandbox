package printer

import (
	"fmt"
	"numerical-methods/internal/utils"
)

func PrintAllTailor(tableTailor []utils.Pair) {
	for i := 0; i < len(tableTailor); i++ {
		fmt.Printf("x = %.6f, f(x) = %.6f\n", tableTailor[i].X, tableTailor[i].Y)
	}
	fmt.Println(len(tableTailor))
}

func PrintTailor(d int, tableTailor []utils.Pair) {
	for i := 0; i < len(tableTailor); i += d {
		fmt.Printf("x = %.6f, f(x) = %.6f\n", tableTailor[i].X, tableTailor[i].Y)
	}
}

func PrintPolynom(tableTailor []utils.Pair, tablePolynom []utils.Pair) {
	for i, elem := range tableTailor {
		fmt.Printf("x = %.6f, f(x) = %.6f, L(x) = %.6f, e(x) = %.10f\n",
			elem.X, elem.Y, tablePolynom[i].Y, elem.Y-tablePolynom[i].Y)
	}
}
