package tree

import (
	"github.com/gammazero/deque"
)

type TreeNode struct {
	HasToy bool
	Left   *TreeNode
	Right  *TreeNode
}

func AreToysBalanced(root *TreeNode) bool {
	return root.Left.WeightNode() == root.Right.WeightNode()
}

func UnrollGarland(root *TreeNode) []bool {
	var (
		garland []bool
		layer   int
		node    *TreeNode
		q       deque.Deque[*TreeNode]
	)
	q.PushBack(root)
	for q.Len() != 0 {
		for range q.Len() {
			if layer%2 == 1 {
				node = q.PopFront()
			} else {
				node = q.PopBack()
			}
			if node != nil {
				garland = append(garland, node.HasToy)
				if layer%2 == 0 {
					q.PushFront(node.Right)
					q.PushFront(node.Left)
				} else {
					q.PushBack(node.Left)
					q.PushBack(node.Right)
				}
			}
		}
		layer++
	}
	return garland
}

func (t *TreeNode) WeightNode() int {
	weight := func() int {
		if t.HasToy {
			return 1
		} else {
			return 0
		}
	}()
	if t.Left != nil {
		weight += t.Left.WeightNode()
	}
	if t.Right != nil {
		weight += t.Right.WeightNode()
	}
	return weight
}

func (t *TreeNode) DepthNode() int {
	leftDepth := 1
	rightDepth := 1
	if t.Left != nil {
		leftDepth += t.Left.DepthNode()
	}
	if t.Right != nil {
		rightDepth += t.Right.DepthNode()
	}
	return min(leftDepth, rightDepth)
}

func (t *TreeNode) AddNode(toy bool) {
	if t.Left == nil {
		t.Left = &TreeNode{HasToy: toy}
		return
	} else if t.Right == nil {
		t.Right = &TreeNode{HasToy: toy}
		return
	}
	if t.Left.DepthNode() <= t.Right.DepthNode() {
		t.Left.AddNode(toy)
	} else {
		t.Right.AddNode(toy)
	}
}

func (t *TreeNode) AddNodes(toys ...bool) {
	for _, toy := range toys {
		t.AddNode(toy)
	}
}
