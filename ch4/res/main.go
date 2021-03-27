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
	if len(os.Args) < 3 {
		fmt.Errorf("arg size error")
	}
	scaleW, err := strconv.ParseFloat(os.Args[1], 64)
	if err != nil {
		fmt.Errorf("arg1 error")
	}
	scaleH, err := strconv.ParseFloat(os.Args[2], 64)
	if err != nil {
		fmt.Errorf("arg2 error")
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
