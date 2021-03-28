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
	size := src.Size()

	img := gocv.NewMatWithSizeFromScalar(gocv.Scalar{128, 0, 0, 0}, size[0], size[1], gocv.MatTypeCV8UC3)

	fmt.Println(img.Size(), size)

	gocv.Add(src, img, &dst)

	srcWnd := gocv.NewWindow("src")
	srcWnd.IMShow(src)
	dstWnd := gocv.NewWindow("dst")
	dstWnd.IMShow(dst)
	gocv.WaitKey(0)

}
