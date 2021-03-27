package main

import (
	"fmt"
	"os"
	"strconv"

	"gocv.io/x/gocv"
)

func cvt(mat gocv.Mat, dst *gocv.Mat) {
	gocv.Flip(mat, dst, 1)
}

func main() {
	if len(os.Args) < 2 {

	}
	flipCode, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Errorf("arg error")
	}
	src := gocv.IMRead("../../images/sample.jpg", gocv.IMReadColor)
	if src.Empty() {
		fmt.Errorf("img error")
	}

	dst := gocv.NewMat()
	gocv.Flip(src, &dst, flipCode)

	srcWnd := gocv.NewWindow("src")
	srcWnd.IMShow(src)
	dstWnd := gocv.NewWindow("dst")
	dstWnd.IMShow(dst)

	gocv.WaitKey(0)

}
