package reader

import (
	"io"
	"os"
)

func ReadFile(path string) (string, error) {
	file, err := os.Open(path)
	if err != nil {
		return "", err
	}
	defer file.Close()

	var data string
	buffer := make([]byte, 1024)

	for {
		bytesRead, err := file.Read(buffer)
		data += string(buffer[:bytesRead])

		if err != nil {
			if err == io.EOF {
				break
			}
			return data, err
		}
	}

	return data, nil
}
