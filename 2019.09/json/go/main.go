package main

import (
	"encoding/json"
	"fmt"
)

type Hoge struct {
	Foo float32
	Bar float64
}

func main() {
	hoge := Hoge{Foo: 0xa0000000, Bar: 0xa0000000}
	j, _ := json.Marshal(hoge)
	fmt.Println(string(j))
}
