package archive

import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"log"
	"os"
	"strings"
	"sync"
	"time"
)

func Archiver(dir string, files []string) {
	var wg sync.WaitGroup
	for _, file := range files {
		wg.Add(1)
		go func(f string) {
			defer wg.Done()
			makeArchive(dir, f)
		}(file)
	}
	wg.Wait()
}

func makeArchive(dir, file string) {
	outFile, err := os.Create(fmt.Sprintf("%s/%s_%d.tar.gz", dir, strings.SplitN(file, ".", 2)[0], time.Now().Unix()))
	if err != nil {
		log.Fatalln(err)
	}
	defer outFile.Close()

	gz := gzip.NewWriter(outFile)
	defer gz.Close()

	tarWriter := tar.NewWriter(gz)
	defer tarWriter.Close()

	inFile, err := os.Open(file)
	if err != nil {
		log.Fatalln(err)
	}
	defer inFile.Close()

	fileInfo, err := inFile.Stat()
	if err != nil {
		log.Fatalln(err)
	}

	header, err := tar.FileInfoHeader(fileInfo, "")
	if err != nil {
		log.Fatalln(err)
	}

	if err := tarWriter.WriteHeader(header); err != nil {
		log.Fatalln(err)
	}

	if _, err := io.Copy(tarWriter, inFile); err != nil {
		log.Fatalln(err)
	}
}
