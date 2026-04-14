package main

import (
	"fmt"
	"io"
	"log"
	"os"
	"os/exec"
	"strings"
)

func main() {
	bytes, err := io.ReadAll(os.Stdin)
	if err != nil {
		fmt.Println(err)
		return
	}

	input := strings.FieldsFunc(string(bytes), func(r rune) bool { return r == ' ' || r == '\n' })
	var argums []string
	argums = append(os.Args[2:], input...)
	cmd := exec.Command(os.Args[1], argums...)
	cmd.Stderr = os.Stderr
	cmd.Stdout = os.Stdout
	err = cmd.Run()
	if err != nil {
		log.Println(cmd, ": invalid command")
		return
	}
}
