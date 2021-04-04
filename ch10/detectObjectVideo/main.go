package main

import (
	"fmt"
	"image/color"
	"os"

	"gocv.io/x/gocv"
)

func main() {
	xmpPath := "haarcascade_frontalface_default.xml"
	var camera *gocv.VideoCapture
	var err error
	if len(os.Args) > 1 {
		camera, err = gocv.OpenVideoCapture(os.Args[1])
	} else {
		deviceID := 0
		camera, err = gocv.OpenVideoCapture(deviceID)
	}
	if err != nil {
		fmt.Println(err)
		return
	}
	if !camera.IsOpened() {
		fmt.Println("not open")
		return
	}
	defer camera.Close()

	objDetector := gocv.NewCascadeClassifier()
	defer objDetector.Close()
	objDetector.Load(xmpPath)

	// loop
	src := gocv.NewMat()
	cvtImg := gocv.NewMat()
	equalize := gocv.NewMat()

	srcWindow := gocv.NewWindow("src")
	srcWindow.SetWindowProperty(gocv.WindowPropertyAutosize, gocv.WindowAutosize)
	for {
		camera.Read(&src)
		if src.Empty() {
			break
		}
		gocv.CvtColor(src, &cvtImg, gocv.ColorRGBAToGray)
		gocv.EqualizeHist(cvtImg, &equalize)
		objs := objDetector.DetectMultiScale(equalize)
		for _, v := range objs {
			gocv.Rectangle(&src, v, color.RGBA{255, 0, 0, 0}, 2)
		}
		srcWindow.IMShow(src)
		if gocv.WaitKey(1) >= 0 {
			break
		}
	}

}
