package main

import (
	"fmt"
	"image"

	"gocv.io/x/gocv"
)

func main() {
	src1 := gocv.IMRead("../../images/sample.jpg", gocv.IMReadColor)
	src2 := gocv.IMRead("../../images/sample2.jpg", gocv.IMReadColor)
	if src1.Empty() || src2.Empty() {
		fmt.Println("img error")
		return
	}

	dst := gocv.NewMat()
	srcResize := gocv.NewMat()
	gocv.Resize(src2, &srcResize, image.Pt(src1.Size()[1], src1.Size()[0]), 0, 0, gocv.InterpolationNearestNeighbor)

	fmt.Println(src1.Size(), srcResize.Size())
	gocv.Add(src1, srcResize, &dst)

	src1Wnd := gocv.NewWindow("src1")
	src1Wnd.IMShow(src1)
	src2Wnd := gocv.NewWindow("src2")
	src2Wnd.IMShow(src2)
	dstWnd := gocv.NewWindow("dst")
	dstWnd.IMShow(dst)
	gocv.WaitKey(0)

}
