package stat

import (
	"errors"
	"flag"
	"fmt"
)

var ErrNoFlag = errors.New("no flag")

type Flags struct {
	Lines   bool
	Symbols bool
	Words   bool
}

func ParseInput(flags *Flags, args []string) error {
	flag.BoolVar(&flags.Lines, "l", false, "Include lines")
	flag.BoolVar(&flags.Symbols, "m", false, "Include symbols")
	flag.BoolVar(&flags.Words, "w", false, "Include words")

	flag.Parse()

	if !flags.Lines && !flags.Symbols && !flags.Words {
		flags.Words = true
		return ErrNoFlag
	} else if (flags.Lines && flags.Symbols || flags.Lines && flags.Words || flags.Symbols && flags.Words) == (flags.Lines || flags.Symbols || flags.Words) {
		return fmt.Errorf("error: too many flags")
	}

	return nil
}
