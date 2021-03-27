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

	gocv.PutText(&src, "Hello World", center, gocv.FontHersheyTriplex, 0.8, color.RGBA{255, 200, 200, 0}, 2)

	srcWnd := gocv.NewWindow("src")
	srcWnd.IMShow(src)
	gocv.WaitKey(0)

}
