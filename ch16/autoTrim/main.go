package main

import (
	"fmt"
	"image"
	"image/color"
	"math"
	"os"

	"github.com/adam-lavrik/go-imath/ix"
	"gocv.io/x/gocv"
)

func cmpHpix1(src gocv.Mat, y int, flg bool) bool {
	delta := 16.0
	for x := 1; x < src.Cols(); x++ {
		p0 := src.GetUCharAt(y, x-1)
		p1 := src.GetUCharAt(y, x)
		p := int(p0) - int(p1)
		diff := math.Abs(float64(p))
		if diff > delta {
			return true
		}
	}
	return false
}

func cmpVpix1(src gocv.Mat, x int) bool {

	delta := 16.0
	for y := 1; y < src.Rows(); y++ {
		p0 := src.GetUCharAt(y-1, x)
		p1 := src.GetUCharAt(y, x)

		diff := math.Abs(float64(int(p0) - int(p1)))
		if diff > delta {
			return true
		}
	}
	return false
}
func cmpHpix2(src gocv.Mat, y int, flg bool) bool {

	delta := 1 << 3
	rLevel := make([]int, 256/delta)
	cmpPct := 0.60

	for x := 1; x < src.Cols()-1; x++ {
		c := src.GetUCharAt(y, x)
		idx := int(c) / delta
		rLevel[idx] = rLevel[idx] + 1
	}
	max := ix.MaxSlice(rLevel)
	pcnt := float64(max) / float64(src.Cols())
	if pcnt > cmpPct {
		return true
	}
	return false
}
func cmpVpix2(src gocv.Mat, x int) bool {
	delta := 1 << 3

	rLevel := make([]int, 256/delta)
	cmpPct := 0.60

	for y := 1; y < src.Rows(); y++ {
		c := src.GetUCharAt(y, x)
		idx := int(c) / delta
		rLevel[idx] = rLevel[idx] + 1
	}
	max := ix.MaxSlice(rLevel)
	pcnt := float64(max) / float64(src.Cols())
	if pcnt > cmpPct {
		return true
	}
	return false
}

func detectEidge(src gocv.Mat, hFn func(gocv.Mat, int, bool) bool, vFn func(gocv.Mat, int) bool) image.Rectangle {
	topPos := 0
	for y := 0; y < src.Rows(); y++ {
		if hFn(src, y, false) {
			topPos = y
			break
		}
	}
	fmt.Println("topPos=", topPos)

	bottomPos := src.Rows() - 1
	for y := src.Rows() - 1; y >= 0; y-- {
		if hFn(src, y, true) {
			bottomPos = y
			break
		}
	}
	fmt.Println("bottomPos=", bottomPos)

	leftPos := 0
	for x := 0; x < src.Cols(); x++ {
		if vFn(src, x) {
			leftPos = x
			break
		}
	}

	rightPos := src.Cols() - 1
	for x := src.Cols() - 1; x >= 0; x-- {
		if vFn(src, x) {
			rightPos = x
			break
		}
	}
	return image.Rect(leftPos, topPos, rightPos, bottomPos)
}

func main() {
	if len(os.Args) < 2 {
		fmt.Println("few args")
		return
	}
	src := gocv.IMRead(os.Args[1], gocv.IMReadColor)
	if src.Empty() {
		fmt.Println("img empty")
		return
	}
	fmt.Println("size=", src.Size())
	gry := gocv.NewMat()
	gocv.CvtColor(src, &gry, gocv.ColorRGBAToGray)
	gocv.IMWrite("gry.jpg", gry)
	rect1 := detectEidge(gry, cmpHpix1, cmpVpix1)
	rect2 := detectEidge(gry, cmpHpix2, cmpVpix2)

	rect := rect1
	if rect1.Size().X > rect2.Size().X {
		rect = rect2
	}
	fmt.Println("rect1=", rect1)
	fmt.Println("rect2=", rect2)

	if rect.Size().X == src.Cols() && rect.Size().Y == src.Rows() {
		fmt.Println("size error")
		return
	}
	fmt.Println("src(0 ,0 ,", src.Cols(), ",", src.Rows(), ")")

	dst := gocv.NewMat()
	src.CopyTo(&dst)
	gocv.Rectangle(&dst, rect, color.RGBA{255, 0, 0, 0}, 2)

	dstWindow := gocv.NewWindow("dst")
	dstWindow.IMShow(dst)
	gocv.WaitKey(0)

}
