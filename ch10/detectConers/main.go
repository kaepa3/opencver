package main

import (
	"fmt"
	"image"
	"image/color"

	"gocv.io/x/gocv"
)

func main() {
	src := gocv.IMRead("../../images/sample.jpg", gocv.IMReadColor)
	if src.Empty() {
		fmt.Println("img error")
		return
	}
	maxConers := 50
	qualityLebel := 0.01
	minDistance := 20.0

	gray := gocv.NewMat()
	gocv.CvtColor(src, &gray, gocv.ColorRGBToGray)
	corners := gocv.NewMat()
	gocv.GoodFeaturesToTrack(gray, &corners, maxConers, qualityLebel, minDistance)

	dst := src.Clone()
	for f := 0; f < corners.Rows(); f++ {
		x := corners.GetFloatAt(f, 0)
		y := corners.GetFloatAt(f, 1)
		gocv.Circle(&dst, image.Pt(int(x), int(y)), 8, color.RGBA{255, 255, 0, 0}, 2)
	}

	srcWindow := gocv.NewWindow("src")
	srcWindow.SetWindowProperty(gocv.WindowPropertyAutosize, gocv.WindowAutosize)

	dstWindow := gocv.NewWindow("dst")

	srcWindow.IMShow(src)
	dstWindow.IMShow(dst)
	gocv.WaitKey(0)

}
