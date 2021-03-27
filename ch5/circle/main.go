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
		fmt.Errorf("img error")
	}

	img := gocv.NewMatWithSizeFromScalar(gocv.Scalar{150, 150, 150, 150}, 400, 400, gocv.MatTypeCV8UC3)
	gocv.Circle(&img, image.Pt(200, 200), 80, color.RGBA{255, 0, 0, 0}, 2)

	imgWnd := gocv.NewWindow("img")
	imgWnd.IMShow(img)
	gocv.WaitKey(0)

}
