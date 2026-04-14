package menu

import "fmt"

type Menu struct {
	Mean   bool
	Median bool
	Mode   bool
	SD     bool
}

func (menu *Menu) ParseMenu() error {
	var err bool
	var choice int
	_, er := fmt.Scanf("%d", &choice)
	if er != nil {
		err = true
	}
	if choice < 1 || choice > 9999 {
		err = true
	}
	for choice != 0 && !err {
		switch choice % 10 {
		case 1:
			if menu.Mean {
				err = true
			}
			menu.Mean = true
		case 2:
			if menu.Median {
				err = true
			}
			menu.Median = true
		case 3:
			if menu.Mode {
				err = true
			}
			menu.Mode = true
		case 4:
			if menu.SD {
				err = true
			}
			menu.SD = true
		default:
			err = true
		}
		choice /= 10
	}
	if err {
		return fmt.Errorf("wrong input")
	} else {
		return nil
	}
}
