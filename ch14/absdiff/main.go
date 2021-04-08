package main

import (
	"fmt"

	"gocv.io/x/gocv"
)

func main() {
	src := make([]gocv.Mat, 2)
	src[0] = gocv.IMRead("../../images/sample.jpg", gocv.IMReadGrayScale)
	src[1] = gocv.IMRead("../../images/sample.jpg", gocv.IMReadGrayScale)
	//src[1] = gocv.IMRead("../../images/empty.jpg", gocv.IMReadGrayScale)
	if src[0].Empty() || src[1].Empty() {
		fmt.Println("img error")
		return
	}
	dst := gocv.NewMat()
	gocv.AbsDiff(src[0], src[1], &dst)

	r := dst.Sum()
	fmt.Println(r)

	dstWindow := gocv.NewWindow("dst")

	dstWindow.IMShow(dst)
	gocv.WaitKey(0)

}
