package main

import (
	t "algorithms/tree"
	"fmt"
)

func main() {
	tree := t.TreeNode{HasToy: true}
	tree.AddNodes(
		true, false,
		true, true, true, false,
		false, false, true, false, true, true, true, false,
	)

	fmt.Println(t.UnrollGarland(&tree))
}
