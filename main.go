package main

// #include "sysinfo.h"
import "C"
import "fmt"

var print = fmt.Println

func main(){
	var uptime uint32 = C.getUptime()
	print("The system uptime is",uptime)

}