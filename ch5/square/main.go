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
	x0 := src.Cols() / 4
	x1 := src.Cols() / 4 * 3
	y0 := src.Rows() / 4
	y1 := src.Rows() / 4 * 3

	rect := image.Rect(x0, y0, x1, y1)

	gocv.Rectangle(&src, rect, color.RGBA{0, 0, 255, 0}, 2)

	srcWnd := gocv.NewWindow("src")
	srcWnd.IMShow(src)
	gocv.WaitKey(0)

}
