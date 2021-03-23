package main

import (
	"fmt"

	"gocv.io/x/gocv"
)

func main() {
	fmt.Println(gocv.Version())
	if cap, err := gocv.VideoCaptureFile("./movie.avi"); err == nil {
		frame := cap.Grab(0)
	}

}
