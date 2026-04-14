package find

import (
	"errors"
	"os"
	"path/filepath"
)

func Finder(path string, flags Flags) (str []string, err error) {
	dir, err := os.ReadDir(path)
	if errors.Is(err, os.ErrPermission) {
		return str, nil
	} else if err != nil {
		return nil, err
	}
	for _, val := range dir {
		info, err := val.Info()
		if err != nil {
			return nil, err
		}
		if val.IsDir() {
			if flags.Directories {
				str = append(str, path+"/"+val.Name())
			}
			req, err := Finder(path+"/"+val.Name(), flags)
			if err != nil {
				return nil, err
			}
			str = append(str, req...)
		} else if info.Mode().IsRegular() {
			if flags.Files && !flags.Ext {
				str = append(str, path+"/"+val.Name())
			} else if flags.Files && flags.ExtStr == filepath.Ext(val.Name()) {
				str = append(str, path+"/"+val.Name())
			}
		} else if s, _ := filepath.EvalSymlinks(path + "/" + val.Name()); flags.SymbLinks {
			if _, errExist := os.Stat(s); errExist == nil {
				str = append(str, path+"/"+val.Name()+" -> "+s)
			} else {
				str = append(str, path+"/"+val.Name()+" -> "+"[broken]")
			}
		}
	}
	return
}
