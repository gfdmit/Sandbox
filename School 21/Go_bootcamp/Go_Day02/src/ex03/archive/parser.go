package archive

import (
	"flag"
	"fmt"
	"os"
)

func ParseInput(dir *string, args []string) error {
	flag.StringVar(dir, "a", ".", "define directory for archive")

	flag.Parse()
	info, err := os.Stat(*dir)
	if os.IsNotExist(err) || os.IsPermission(err) {
		return err
	}
	if !info.IsDir() {
		return fmt.Errorf("error: this is not directory")
	}
	return nil
}
