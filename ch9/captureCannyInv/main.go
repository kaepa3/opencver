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

	if !camera.IsOpened() {
		fmt.Println(err)
		return
	}
	defer camera.Close()

	threshold1 := float32(40.0)
	threshold2 := float32(200.0)

	h := camera.Get(gocv.VideoCaptureFrameHeight)
	w := camera.Get(gocv.VideoCaptureFrameWidth)

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

	srcWindow := gocv.NewWindow("src")
	srcWindow.SetWindowProperty(gocv.WindowPropertyAutosize, gocv.WindowAutosize)
	dstWindow := gocv.NewWindow("dst")
	dstWindow.SetWindowProperty(gocv.WindowPropertyAutosize, gocv.WindowAutosize)

	src := gocv.NewMat()
	dst := gocv.NewMat()
	gray := gocv.NewMat()
	canny := gocv.NewMat()
	for {
		if camera.Read(&src) {
			if !src.Empty() {

				srcWindow.IMShow(src)
				gocv.CvtColor(src, &gray, gocv.ColorRGBToGray)
				gocv.Canny(gray, &canny, threshold1, threshold2)
				gocv.BitwiseNot(canny, &dst)

				dstWindow.IMShow(dst)

				gocv.CvtColor(dst, &dst, gocv.ColorGrayToBGR)
				saver.Write(dst)
			}
		}
		if gocv.WaitKey(1) >= 0 {
			break
		}
	}

}
