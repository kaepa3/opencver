package main

import (
	"fmt"
	"image"
	"math"

	"gocv.io/x/gocv"
)

func createCosMat(src gocv.Mat) gocv.Mat {
	s := gocv.Scalar{Val1: 0, Val2: 0, Val3: 0, Val4: 0}
	mat := gocv.NewMatWithSizeFromScalar(s, src.Rows(), src.Cols(), gocv.MatTypeCV8UC1)
	center := image.Pt(mat.Cols()/2, mat.Rows()/2)
	radius := math.Sqrt(math.Pow(float64(center.X), 2) + math.Pow(float64(center.Y), 2))
	for y := 0; y < mat.Rows(); y++ {
		for x := 0; x < mat.Cols(); x++ {
			distance := math.Sqrt(math.Pow(float64(center.X-x), 2) + math.Pow(float64(center.Y-y), 2))
			radian := (distance / radius) * math.Pi
			Y := (math.Cos(radian) + 1/2)
			v := uint8(Y * 255)
			mat.SetUCharAt(y, x, v)
		}
	}
	fmt.Println("finish")
	return mat
}

func mulMask(src, mask gocv.Mat) gocv.Mat {
	src32f := gocv.NewMat()
	src.ConvertTo(&src32f, gocv.MatTypeCV32F)
	mask32f := gocv.NewMat()
	mask.ConvertTo(&mask32f, gocv.MatTypeCV32F)
	mask32f.DivideFloat(255)
	dst32f := gocv.NewMat()
	gocv.Multiply(src32f, mask32f, &dst32f)
	return dst32f
}
func search(mat []gocv.Mat) int {
	cosTable := createCosMat(mat[0])
	srcw := mulMask(mat[0], cosTable)
	dMin := math.MaxFloat64
	pos := math.MaxInt64
	for i := 1; i < len(mat); i++ {
		dst := gocv.NewMat()
		dstw := mulMask(mat[i], cosTable)
		gocv.AbsDiff(srcw, dstw, &dst)
		r := dst.Sum().Val1
		if dMin > r {
			dMin = r
			pos = i
		}
	}
	return pos
}
func main() {
	src := make([]gocv.Mat, 3)
	src[0] = gocv.IMRead("../../images/sample.jpg", gocv.IMReadGrayScale)
	src[1] = gocv.IMRead("../../images/empty.jpg", gocv.IMReadGrayScale)
	src[2] = gocv.IMRead("../../images/sample.jpg", gocv.IMReadGrayScale)

	pos := search(src)
	fmt.Println("------------------")
	fmt.Println(pos)
}
