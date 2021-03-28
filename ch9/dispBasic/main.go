package main

import (
	"fmt"
	"os"

	"gocv.io/x/gocv"
)

func main() {
	deviceID := 0
	var camera *gocv.VideoCapture
	var err error
	fmt.Println(len(os.Args))
	if len(os.Args) > 1 {
		camera, err = gocv.OpenVideoCapture(os.Args[1])
	} else {
		camera, err = gocv.OpenVideoCapture(deviceID)
	}
	if err != nil {
		fmt.Println(err)
		return
	}
	defer camera.Close()
	h := camera.Get(gocv.VideoCaptureFrameHeight)
	w := camera.Get(gocv.VideoCaptureFrameWidth)
	fmt.Printf("size -> %f:%f", h, w)

	window := gocv.NewWindow("Face Detect")
	window.SetWindowProperty(gocv.WindowPropertyAutosize, gocv.WindowAutosize)

	src := gocv.NewMat()
	for {
		if camera.Read(&src) {
			window.IMShow(src)
		}
		if gocv.WaitKey(1) >= 0 {
			break
		}
	}

}
