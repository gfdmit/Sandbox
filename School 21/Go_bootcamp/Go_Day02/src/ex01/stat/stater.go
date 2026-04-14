package stat

import (
	"log"
	"os"
	"strconv"
	"sync"
)

func Stater(files []string, flags Flags) (str []string) {
	var wg sync.WaitGroup
	var mu sync.Mutex
	for _, file := range files {
		wg.Add(1)
		if flags.Lines {
			go func(f string) {
				defer wg.Done()
				countLines(f, &str, &mu)
			}(file)
		} else if flags.Symbols {
			go func(f string) {
				defer wg.Done()
				countSymbols(f, &str, &mu)
			}(file)
		} else {
			go func(f string) {
				defer wg.Done()
				countWords(f, &str, &mu)
			}(file)
		}
	}
	wg.Wait()
	return
}

func countLines(file string, str *[]string, mu *sync.Mutex) {
	var counter int = 1
	data, err := os.ReadFile(file)
	if err != nil {
		log.Fatalln("error: open " + file + ": no such file or directory")
	}
	for _, ch := range data {
		if ch == '\n' {
			counter++
		}
	}
	mu.Lock()
	defer mu.Unlock()
	*str = append(*str, strconv.Itoa(counter)+"\t"+file)
}

func countSymbols(file string, str *[]string, mu *sync.Mutex) {
	var counter int = 1
	data, err := os.ReadFile(file)
	if err != nil {
		log.Fatalln("error: open " + file + ": no such file or directory")
	}
	counter = len(data)
	mu.Lock()
	defer mu.Unlock()
	*str = append(*str, strconv.Itoa(counter)+"\t"+file)
}

func countWords(file string, str *[]string, mu *sync.Mutex) {
	var counter int = 1
	data, err := os.ReadFile(file)
	if err != nil {
		log.Fatalln("error: open " + file + ": no such file or directory")
	}
	for i, ch := range data {
		if ch == ' ' || ch == '\n' && i != len(data)-1 {
			counter++
		}
	}
	mu.Lock()
	defer mu.Unlock()
	*str = append(*str, strconv.Itoa(counter)+"\t"+file)
}
