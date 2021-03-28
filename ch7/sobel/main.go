package main

import (
	"fmt"

	"gocv.io/x/gocv"
)

func main() {
	src := gocv.IMRead("../../images/sample.jpg", gocv.IMReadColor)
	if src.Empty() {
		fmt.Println("img error")
		return
	}

	dst := gocv.NewMat()
	gocv.Sobel(src, &dst, -1, 0, 1, 3, 1, 0, gocv.BorderConstant)
	display(&src, &dst)

}
func display(src, dst *gocv.Mat) {
	srcWnd := gocv.NewWindow("src")
	srcWnd.IMShow(*src)
	dstWnd := gocv.NewWindow("dst")
	dstWnd.IMShow(*dst)
	gocv.WaitKey(0)

}
