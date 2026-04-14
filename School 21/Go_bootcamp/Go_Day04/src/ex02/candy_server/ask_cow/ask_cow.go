package ask_cow

/*
#include "stdlib.h"
#include "cow.h"
*/
import "C"

import (
	"unsafe"
)

func AskCow(phrase string) string {

	GOPhrase := "Thank you"
	CPhrase := C.CString(GOPhrase)
	defer C.free(unsafe.Pointer(CPhrase))

	CAnswer := C.ask_cow(CPhrase)
	defer C.free(unsafe.Pointer(CAnswer))
	GOAnswer := C.GoString(CAnswer)
	return GOAnswer
}
