package main

import (
	"gocv.io/x/gocv"
)

func cvt(mat gocv.Mat, dst *gocv.Mat) {
	gocv.Flip(mat, dst, 1)
}

func main() {
	src := gocv.IMRead("../../images/sample.jpg", gocv.IMReadColor)
	dst := gocv.NewMat()
	cvt(src, &dst)

	srcWnd := gocv.NewWindow("src")
	srcWnd.IMShow(src)
	dstWnd := gocv.NewWindow("dst")
	dstWnd.IMShow(dst)

	gocv.WaitKey(0)

}
