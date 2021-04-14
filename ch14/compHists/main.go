package main

import (
	"fmt"

	"gocv.io/x/gocv"
)

func main() {
	src := make([]gocv.Mat, 3)
	src[0] = gocv.IMRead("../../images/sample.jpg", gocv.IMReadGrayScale)
	src[1] = gocv.IMRead("../../images/empty.jpg", gocv.IMReadGrayScale)
	src[2] = gocv.IMRead("../../images/sample.jpg", gocv.IMReadGrayScale)

	hists := make([]gocv.Mat, len(src))
	mask := gocv.NewMat()
	for i := 0; i < len(src); i++ {
		hist := gocv.NewMat()
		gocv.CalcHist([]gocv.Mat{src[i]}, []int{0}, mask, &hist, []int{256}, []float64{0, 256}, false)
		hists[i] = hist
	}

	var dMax float32
	dMax = 0
	pos := 0
	for i := 1; i < len(hists); i++ {
		f := gocv.CompareHist(hists[0], hists[i], gocv.HistCmpCorrel)
		fmt.Println("Correl =>", f)
		if dMax < f {
			dMax = f
			pos = i
		}
	}
	fmt.Println("max =>", pos)
}
