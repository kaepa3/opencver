package main

import (
	"fmt"
	"image"
	"os"
	"strconv"

	"gocv.io/x/gocv"
)

func cvt(mat gocv.Mat, dst *gocv.Mat) {
	gocv.Flip(mat, dst, 1)
}

func main() {
	if len(os.Args) < 2 {
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
	width := float64(src.Cols()) * scaleW
	height := float64(src.Rows()) * scaleH

	dst := gocv.NewMat()
	size := image.Point{int(width), int(height)}
	gocv.Resize(src, &dst, size, 0, 0, gocv.InterpolationDefault)

	srcWnd := gocv.NewWindow("src")
	srcWnd.IMShow(src)
	dstWnd := gocv.NewWindow("dst")
	dstWnd.IMShow(dst)

	gocv.WaitKey(0)

}
