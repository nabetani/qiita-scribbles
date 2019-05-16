package main

import (
	"fmt"
	"os"
	"strconv"
)

func fibo(n int) int64 {
	if n <= 1 {
		return 1
	}
	return fibo(n-1) + fibo(n-2)
}

func main() {
	n, _ := strconv.Atoi(os.Args[1])
	fmt.Println(fibo(n))
}
