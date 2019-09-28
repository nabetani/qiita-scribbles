package marshaljsonf64

import (
	"encoding/json"
	"fmt"
	"log"
	"reflect"
	"strconv"
	"strings"
)

func MarshalJSONF64(o interface{}, t reflect.Type) ([]byte, error) {
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
