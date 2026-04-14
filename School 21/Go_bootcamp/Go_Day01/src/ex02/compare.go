package main

import (
	"os"
	"strings"
)

func compareDumps(old, new string) (diff string, err error) {
	dumpOld, err := os.ReadFile(old)
	if err != nil {
		return "", err
	}
	dumpNew, err := os.ReadFile(new)
	if err != nil {
		return "", err
	}
	strDumpOld, strDumpNew := strings.Split(string(dumpOld), "\n"), strings.Split(string(dumpNew), "\n")
	smth := unintersection(strDumpOld, strDumpNew, "ADDED")
	smth = append(smth, unintersection(strDumpNew, strDumpOld, "REMOVED")...)
	diff = strings.Join(smth, "\n")
	return
}

func unintersection(s1, s2 []string, changeType string) (uninter []string) {
	hash := make(map[string]bool)
	var changeStr string
	if changeType == "ADDED" {
		changeStr = "ADDED "
	} else {
		changeStr = "REMOVED "
	}
	for _, e := range s1 {
		hash[e] = true
	}
	for _, e := range s2 {
		if !hash[e] {
			uninter = append(uninter, changeStr+e)
			hash[e] = true
		}
	}
	return
}
