package main

import "C"
import "fmt"

var print = fmt.Println

func main(){
	var uptime uint32 = 100000
	print("The system uptime is",uptime)

}