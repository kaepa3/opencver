package main

import (
	"fmt"
	"image"
	"os"
	"strconv"

	"gocv.io/x/gocv"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Println("arg error")
		return
	}
	ksize, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Println("value error")
		return
	}

	src := gocv.IMRead("../../images/sample.jpg", gocv.IMReadColor)
	if src.Empty() {
		fmt.Println("img error")
		return
	}

	dst := gocv.NewMat()
	gocv.Blur(src, &dst, image.Pt(ksize, ksize))

	srcWnd := gocv.NewWindow("src")
	srcWnd.IMShow(src)
	dstWnd := gocv.NewWindow("dst")
	dstWnd.IMShow(dst)
	gocv.WaitKey(0)

}
