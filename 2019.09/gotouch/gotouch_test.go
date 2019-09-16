package gotouch

import (
	"io/ioutil"
	"os"
	"syscall"
	"testing"
	"time"
)

func checkTime(t *testing.T, t0, t1, ft time.Time) {
	if ft.Before(t0) {
		t.Errorf("ft(%v) should be after t0(%v)", ft, t0)
	}
	if t1.Before(ft) {
		t.Errorf("t0(%v) should be after ft(%v)", t1, ft)
	}
}

func TestTouchAFileThatDoesNotExist(t *testing.T) {
	target := "foo"
	os.Remove(target)
	defer os.Remove(target)
	t0 := time.Now()
	err := Touch(target)
	t1 := time.Now()
	if err != nil {
		t.Errorf("Touch returns %v, want nil", err)
	}
	fi, err := os.Stat(target)
	if err != nil {
		t.Error("os.Stat failed:", err)
		return
	}
	if fi.Size() != 0 {
		t.Error("touched file should be empty, but the size is ", fi.Size())
	}
	checkTime(t, t0, t1, fi.ModTime())
}

func TestTouchAFileThatExists(t *testing.T) {
	target := "bar"
	contents := []byte("contents\n")
	err := ioutil.WriteFile(target, contents, 0666)
	if err != nil {
		t.Error("file creation failed:", err)
		return
	}
	defer os.Remove(target)
	t0 := time.Now()
	err = Touch(target)
	t1 := time.Now()
	if err != nil {
		t.Errorf("Touch returns %v, want nil", err)
	}
	fi, err := os.Stat(target)
	if err != nil {
		t.Error("os.Stat failed:", err)
		return
	}
	if fi.Size() != int64(len(contents)) {
		t.Errorf("fi.Size()=%v, want %v", fi.Size(), len(contents))
	}
	checkTime(t, t0, t1, fi.ModTime())
}

func TestTouchUntachableFile(t *testing.T) {
	target := "this/file/is/untachable/because/no/such/directory"
	err := Touch(target)
	errno, ok := err.(syscall.Errno)
	if !ok {
		t.Errorf("Touch returns %v(%T), want os.Errno", err, err)
	}
	if errno != syscall.ENOENT {
		t.Errorf("Touch returns %v(%v), want syscall.ENOENT(%v)", errno, int64(errno), int64(syscall.ENOENT))
	}
	defer os.Remove(target)
}
