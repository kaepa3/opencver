package main

import (
	"fmt"

	"gocv.io/x/gocv"
)

func main() {
	src := gocv.IMRead("../../images/sample.jpg", gocv.IMReadColor)
	if src.Empty() {
		fmt.Errorf("img error")
	}
	dst := gocv.NewMat()
	gocv.CvtColor(src, &dst, gocv.ColorRGBToGray)

	srcWnd := gocv.NewWindow("src")
	srcWnd.IMShow(src)
	dstWnd := gocv.NewWindow("dst")
	dstWnd.IMShow(dst)
	gocv.WaitKey(0)

}
