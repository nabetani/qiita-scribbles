package main

import (
	"encoding/json"
	"fmt"
	"log"
	"reflect"
	"strconv"
	"strings"
)

type Hoge struct {
	Foo uint32
	Bar uint64
	Baz float32
	Qux float64
}

type Fuga struct {
	Hoge
	Piyo string
}

func marshalJSONF64(o interface{}, t reflect.Type) ([]byte, error) {
	numf := t.NumField()
	oval := reflect.ValueOf(o).Elem()
	log.Println(oval)
	items := []string{}
	for n := 0; n < numf; n++ {
		f := t.Field(n)
		v := oval.FieldByName(f.Name).Interface()
		log.Println(f.Name, f.Type, f.Type.Kind())
		if f.Type.Kind() == reflect.Float32 {
			s := strconv.FormatFloat(float64(v.(float32)), 'f', -1, 64)
			items = append(items, fmt.Sprintf("%q:%s", f.Name, s))
		} else {
			j, err := json.Marshal(v)
			if err != nil {
				return nil, err
			}
			log.Println("j=", j)
			items = append(items, fmt.Sprintf("%q:%s", f.Name, j))
		}
	}
	return []byte("{" + strings.Join(items, ",") + "}"), nil
}

func (h Hoge) MarshalJSON() ([]byte, error) {
	s, err := marshalJSONF64(&h, reflect.TypeOf(h))
	return s, err
}

func (f Fuga) MarshalJSON() ([]byte, error) {
	s, err := marshalJSONF64(&f, reflect.TypeOf(f))
	return s, err
}

func main() {
	fuga := Fuga{
		Hoge: Hoge{
			Foo: 0xf1000000,
			Bar: 0xf1000000,
			Baz: 0xf1000000,
			Qux: 0xf1000000,
		},
		Piyo: "piyo",
	}
	j, err := json.Marshal(&fuga)
	log.Println("err:", err)
	fmt.Println(string(j))
}
