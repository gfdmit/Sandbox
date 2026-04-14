package main

import (
	"errors"
	"fmt"
	"log"
	"unsafe"
)

func getElement(arr []int, idx int) (int, error) {
	if len(arr) == 0 {
		return 0, errors.New("empty slice")
	} else if idx < 0 {
		return 0, errors.New("negative index")
	} else if len(arr) <= idx {
		return 0, errors.New("index is out of bounds")
	}
	ptrFirst := unsafe.Pointer(&arr[0])

	ptrIndex := unsafe.Pointer(uintptr(ptrFirst) + uintptr(idx)*unsafe.Sizeof(arr[0]))

	return *(*int)(ptrIndex), nil
}

func main() {
	arr := []int{1, 2, 3, 4, 5}
	idx := 3
	num, err := getElement(arr, idx)
	if err != nil {
		log.Fatalf("error in getElement: %v", err)
	}
	fmt.Println(num)
}
