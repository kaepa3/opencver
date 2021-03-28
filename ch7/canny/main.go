package main

import (
	"fmt"
	"os"
	"strconv"

	"gocv.io/x/gocv"
)

func main() {
	l := len(os.Args)
	var thresold1, thresold2 float32
	thresold1 = 40.0
	if l > 2 {
		val, err := strconv.ParseFloat(os.Args[1], 64)
		if err != nil {
			fmt.Println("value error")
			return
		}
		thresold1 = float32(val)
	}
	thresold2 = 100.0
	if l > 2 {
		val, err := strconv.ParseFloat(os.Args[2], 64)
		if err != nil {
			fmt.Println("value2 error")
			return
		}
		thresold2 = float32(val)
	}

	src := gocv.IMRead("../../images/sample.jpg", gocv.IMReadColor)
	if src.Empty() {
		fmt.Println("img error")
		return
	}

	dst := gocv.NewMat()
	gocv.Canny(src, &dst, thresold1, thresold2)
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
