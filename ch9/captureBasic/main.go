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

	window := gocv.NewWindow("Face Detect")
	window.SetWindowProperty(gocv.WindowPropertyAutosize, gocv.WindowAutosize)

	fps := camera.Get(gocv.VideoCaptureFPS)
	if fps < 0.0 {
		fps = 3.0
	}
	fmt.Printf("fps-> %f ,size -> %f:%f\n", fps, h, w)
	fmt.Printf("%s\n", camera.CodecString())

	saver, err := gocv.VideoWriterFile("./hoge.avi", "MJPG", fps, int(w), int(h), true)
	if err != nil {
		fmt.Println(err)
		return
	}
	if !saver.IsOpened() {
		fmt.Println("Unable to open VideoWriterFile")
		return
	}
	defer saver.Close()

	src := gocv.NewMat()
	for {
		if camera.Read(&src) {
			if !src.Empty() {

				window.IMShow(src)
				saver.Write(src)
			}
		}
		if gocv.WaitKey(1) >= 0 {
			break
		}
	}

}
