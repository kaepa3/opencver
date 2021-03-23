package main

import (
	"fmt"
	"os"

	"gocv.io/x/gocv"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Println("arg err")
		return
	}
	src := gocv.IMRead("../../image/sample.jpg", gocv.IMReadColor)
	dst := gocv.NewMat()
	gocv.CvtColor(src, &dst, gocv.ColorRGBAToGray)

	helloWnd := gocv.NewWindow("hello")
	helloWnd.IMShow(dst)
	gocv.WaitKey(0)

	return

}
