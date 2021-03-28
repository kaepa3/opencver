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
	gocv.Laplacian(src, &dst, 0, 1, 1, 0, gocv.BorderConstant)
	display(&src, &dst)

}
func display(src, dst *gocv.Mat) {
	srcWnd := gocv.NewWindow("src")
	srcWnd.IMShow(*src)
	dstWnd := gocv.NewWindow("dst")
	dstWnd.IMShow(*dst)
	gocv.WaitKey(0)

}
func checkSize(v1, v2 int) bool {

	return v1 < 0 || v2 < 0 || v1%2 == 0 || v2%2 == 0
}
