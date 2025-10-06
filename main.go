package main

// #include "sysinfo.h"
import "C"
import "fmt"

var print = fmt.Println

func main(){
	uptime := C.get_uptime()
	print("The system uptime is",uptime)

}