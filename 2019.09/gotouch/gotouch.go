package gotouch

import (
	"os"
	"syscall"
	"time"
)

func Touch(path string) error {
	now := time.Now().UnixNano()
	const nano = 1000 * 1000 * 1000
	t := syscall.Timespec{Sec: now / nano, Nsec: now % nano}
	ut := []syscall.Timespec{t, t}
	err := syscall.UtimesNano(path, ut)
	if err == nil {
		return nil
	}
	if err != syscall.ENOENT && err != syscall.ERROR_PATH_NOT_FOUND {
		return err
	}
	f, err := os.OpenFile(path, os.O_APPEND|os.O_CREATE, 0644)
	if err != nil {
		return err
	}
	defer f.Close()
	return nil
}
