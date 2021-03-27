package main

import (
	"fmt"

	"gocv.io/x/gocv"
)

func main() {
	src := gocv.IMRead("../../images/sample.jpg", gocv.IMReadGrayScale)
	if src.Empty() {
		fmt.Println("img error")
		return
	}

	dst := gocv.NewMat()
	gocv.EqualizeHist(src, &dst)

	srcWnd := gocv.NewWindow("src")
	srcWnd.IMShow(src)
	dstWnd := gocv.NewWindow("dst")
	dstWnd.IMShow(dst)
	gocv.WaitKey(0)

}
