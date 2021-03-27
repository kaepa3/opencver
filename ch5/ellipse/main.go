package main

import (
	"fmt"
	"image"
	"image/color"

	"gocv.io/x/gocv"
)

func main() {
	src := gocv.IMRead("../../images/sample.jpg", gocv.IMReadColor)
	if src.Empty() {
		fmt.Println("img error")
		return
	}
	center := image.Point{src.Cols() / 2, src.Rows() / 2}
	size := src.Size()

	gocv.Ellipse(&src, center, image.Pt(size[1]/2, size[0]/2), 0, 0, 360, color.RGBA{255, 0, 0, 0}, 3)

	srcWnd := gocv.NewWindow("src")
	srcWnd.IMShow(src)
	gocv.WaitKey(0)

}
