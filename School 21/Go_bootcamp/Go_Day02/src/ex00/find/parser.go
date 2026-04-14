package find

import (
	"flag"
	"fmt"
)

type Flags struct {
	Files       bool
	Directories bool
	SymbLinks   bool
	Ext         bool
	ExtStr      string
}

func ParseInput(flags *Flags, args []string) error {
	flag.BoolVar(&flags.Directories, "d", false, "Include directories")
	flag.BoolVar(&flags.Files, "f", false, "Include files")
	flag.BoolVar(&flags.SymbLinks, "sl", false, "Include symbolic links")
	flag.StringVar(&flags.ExtStr, "ext", "", "Choose extension of files, example: -ext 'go' (work only with -f)")

	flag.Parse()
	for _, arg := range args {
		if arg == "-ext" && !flags.Files {
			return fmt.Errorf("error: -ext work only with -f")
		} else if arg == "-ext" && flags.ExtStr != "" {
			flags.Ext = true
			flags.ExtStr = "." + flags.ExtStr
			break
		} else if arg == "-ext" {
			flags.Ext = true
		}
	}

	if args[len(args)-1][0] != '/' {
		return fmt.Errorf("error: incorrect way to set the directory, usage: ./executable -flags [/dir]")
	}
	if !flags.Directories && !flags.SymbLinks && !flags.Files {
		flags.Directories = true
		flags.Files = true
		flags.SymbLinks = true
	}
	return nil
}
