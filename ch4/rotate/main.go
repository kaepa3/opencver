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
	angle, err := strconv.ParseFloat(os.Args[1], 64)
	if err != nil {
		fmt.Errorf("arg error")
	}

	src := gocv.IMRead("../../images/sample.jpg", gocv.IMReadColor)
	if src.Empty() {
		fmt.Errorf("img error")
	}
	center := image.Point{src.Cols() / 2, src.Rows() / 2}

	affine := gocv.GetRotationMatrix2D(center, angle, 1.0)
	dst := gocv.NewMat()
	size := src.Size()
	fmt.Println(size)

	gocv.WarpAffine(src, &dst, affine, image.Point{size[1], size[0]})

	srcWnd := gocv.NewWindow("src")
	srcWnd.IMShow(src)
	dstWnd := gocv.NewWindow("dst")
	dstWnd.IMShow(dst)

	gocv.WaitKey(0)

}
