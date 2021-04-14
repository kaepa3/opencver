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
		gocv.CalcHist(src, []int{1}, mask, &hist, []int{256}, []float64{0, 256}, false)
		hists[i] = hist
	}

	f := gocv.CompareHist(hists[0], hists[1], gocv.HistCmpCorrel)
	fmt.Println("Correl:", f)
	f = gocv.CompareHist(hists[0], hists[1], gocv.HistCmpChiSqr)
	fmt.Println("Chisqr:", f)
	f = gocv.CompareHist(hists[0], hists[1], gocv.HistCmpIntersect)
	fmt.Println("Intersect:", f)
	f = gocv.CompareHist(hists[0], hists[1], gocv.HistCmpBhattacharya)
	fmt.Println("Bhattacharaya:", f)
}
