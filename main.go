package main

// #include "sysinfo.h"
import "C"
import (
	"fmt"
	"runtime"
)

var print = fmt.Println

func main() {
	os := runtime.GOOS
	uptime := C.get_uptime(os)
	print("The system uptime is", uptime)

}
