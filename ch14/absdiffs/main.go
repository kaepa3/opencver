package main

import (
	"fmt"
	"math"

	"gocv.io/x/gocv"
)

func main() {
	src := make([]gocv.Mat, 3)
	src[0] = gocv.IMRead("../../images/sample.jpg", gocv.IMReadGrayScale)
	src[1] = gocv.IMRead("../../images/empty.jpg", gocv.IMReadGrayScale)
	src[2] = gocv.IMRead("../../images/sample.jpg", gocv.IMReadGrayScale)
	for _, v := range src {
		if v.Empty() {
			fmt.Println("img error")
			return
		}
	}
	dst := gocv.NewMat()
	dMin := math.MaxFloat64
	pos := 0
	for i := 1; i < len(src); i++ {
		gocv.AbsDiff(src[0], src[i], &dst)
		sum := dst.Sum().Val1
		fmt.Printf("%d = %f\n", i, sum)
		if dMin > sum {
			dMin = sum
			pos = i
		}
	}
	fmt.Println(pos)
}
