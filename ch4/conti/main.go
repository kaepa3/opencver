package main

import (
	"fmt"
	"image"
	"os"

	"gocv.io/x/gocv"
)

func cvt(mat gocv.Mat, dst *gocv.Mat) {
	gocv.Flip(mat, dst, 1)
}

func main() {
	if len(os.Args) < 2 {
		fmt.Errorf("arg size error")
	}

	src := gocv.IMRead("../../images/sample.jpg", gocv.IMReadColor)
	if src.Empty() {
		fmt.Errorf("img error")
	}
	srcWnd := gocv.NewWindow("src")
	dstWnd := gocv.NewWindow("dst")
	srcWnd.IMShow(src)
	center := image.Point{src.Cols() / 2, src.Rows() / 2}
	for angle := 0.0; angle < 360; angle += 0.5 {
		affine := gocv.GetRotationMatrix2D(center, angle, 1.0)
		dst := gocv.NewMat()
		gocv.WarpAffine(src, &dst, affine, image.Point{src.Cols(), src.Rows()})

		dstWnd.IMShow(dst)
		if gocv.WaitKey(1) >= 0 {
			break
		}
	}

}
