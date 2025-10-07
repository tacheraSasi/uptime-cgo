package main

// #include "sysinfo.h"
// #include <stdlib.h>
import "C"
import (
	"fmt"
	"runtime"
	"strings"
	"unsafe"
)

var print = fmt.Println

func main() {
	goos := runtime.GOOS
	var osName string

	// Map Go OS names to C function expected names
	switch goos {
	case "darwin":
		osName = "MAC"
	case "linux":
		osName = "LINUX"
	default:
		print("Unsupported OS:", goos)
		return
	}

	cOsName := C.CString(osName)
	defer C.free(unsafe.Pointer(cOsName))

	uptimePtr := C.get_uptime(cOsName)
	if uptimePtr != nil {
		uptime := C.GoString(uptimePtr)
		C.free(unsafe.Pointer(uptimePtr))
		print("The system uptime is:", strings.TrimSpace(uptime))
	} else {
		print("Failed to get uptime")
	}
}
