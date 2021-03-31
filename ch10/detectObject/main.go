package main

import (
	"fmt"
	"image/color"

	"gocv.io/x/gocv"
)

func main() {
	path := "../../images/face.png"
	xmpPath := "haarcascade_frontalface_default.xml"
	src := gocv.IMRead(path, gocv.IMReadColor)
	if src.Empty() {
		fmt.Println("img error")
		return
	}

	gray := gocv.NewMat()
	gocv.CvtColor(src, &gray, gocv.ColorRGBToGray)
	equalize := gocv.NewMat()
	gocv.EqualizeHist(gray, &equalize)

	objDetector := gocv.NewCascadeClassifier()
	defer objDetector.Close()
	objDetector.Load(xmpPath)

	objs := objDetector.DetectMultiScale(equalize)

	dst := gocv.NewMat()
	src.CopyTo(&dst)
	for _, v := range objs {
		gocv.Rectangle(&dst, v, color.RGBA{255, 255, 0, 0}, 2)
	}

	srcWindow := gocv.NewWindow("src")
	srcWindow.SetWindowProperty(gocv.WindowPropertyAutosize, gocv.WindowAutosize)

	dstWindow := gocv.NewWindow("dst")

	srcWindow.IMShow(src)
	dstWindow.IMShow(dst)
	gocv.WaitKey(0)

}
