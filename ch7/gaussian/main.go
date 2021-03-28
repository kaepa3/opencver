package main

import (
	"fmt"
	"image"
	"os"
	"strconv"

	"gocv.io/x/gocv"
)

func main() {
	l := len(os.Args)
	if l < 2 {
		fmt.Println("arg error")
		return
	}
	ksize1, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Println("value error")
		return
	}
	ksize2 := ksize1
	if l > 2 {
		val, err := strconv.Atoi(os.Args[2])
		if err != nil {
			fmt.Println("value2 error")
			return
		}
		ksize2 = val
	}
	if checkSize(ksize1, ksize2) {
		fmt.Println("kernel size error")
		return
	}
	sigma1 := 10.0
	sigma2 := 10.0
	if l > 3 {
		val, err := strconv.ParseFloat(os.Args[3], 32)
		if err != nil {
			fmt.Println("value3 error")
			return
		}
		sigma1 = val
	}
	if l > 4 {
		val, err := strconv.ParseFloat(os.Args[4], 32)
		if err != nil {
			fmt.Println("value3 error")
			return
		}
		sigma2 = val
	}

	src := gocv.IMRead("../../images/sample.jpg", gocv.IMReadColor)
	if src.Empty() {
		fmt.Println("img error")
		return
	}

	dst := gocv.NewMat()
	gocv.GaussianBlur(src, &dst, image.Pt(ksize1, ksize2), sigma1, sigma2, gocv.BorderConstant)
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
