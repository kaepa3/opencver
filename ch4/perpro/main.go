package main

import (
	"fmt"
	"image"
	"os"
	"strconv"

	"gocv.io/x/gocv"
)

func cvt(mat gocv.Mat, dst *gocv.Mat) {
	gocv.Flip(mat, dst, 1)
}

func main() {
	if len(os.Args) < 2 {
		fmt.Println("arg size error")
		return
	}
	pattern, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Println(err, err)
		return
	}
	src := gocv.IMRead("../../images/sample.jpg", gocv.IMReadColor)
	if src.Empty() {
		fmt.Println("img error")
		return
	}

	x0 := src.Cols() / 4
	x1 := src.Cols() / 4 * 3
	y0 := src.Rows() / 4
	y1 := src.Rows() / 4 * 3

	srcPoints := []image.Point{
		image.Point{x0, y0},
		image.Point{x0, y1},
		image.Point{x1, y1},
		image.Point{x1, y0},
	}
	var dstPoints []image.Point
	switch pattern {
	case 0:
		xMergin := src.Cols() / 10
		yMergin := src.Rows() / 10
		dstPoints = []image.Point{
			image.Point{x0 + xMergin, y0 + yMergin},
			srcPoints[1],
			srcPoints[2],
			image.Point{x1 + xMergin, y1 + yMergin},
		}
		break
	case 1:
		xMergin := src.Cols() / 8
		yMergin := src.Rows() / 8
		dstPoints = []image.Point{
			srcPoints[0],
			srcPoints[1],
			image.Point{x1 + xMergin, y1 + yMergin},
			image.Point{x1 + xMergin, y0 + yMergin},
		}
		break
	case 2:
		xMergin := src.Cols() / 6
		yMergin := src.Rows() / 6
		dstPoints = []image.Point{
			image.Point{x0 + xMergin, y0 + yMergin},
			srcPoints[1],
			image.Point{x1 + xMergin, y1 + yMergin},
			srcPoints[3],
		}
		break
	case 3:
		dstPoints = []image.Point{
			srcPoints[0],
			srcPoints[1],
			srcPoints[2],
			srcPoints[3],
		}
		break
	}
	fmt.Printf("%v:%v", srcPoints, dstPoints)
	perspectiveMat := gocv.GetPerspectiveTransform(srcPoints, dstPoints)
	size := src.Size()
	dst := gocv.NewMat()
	gocv.WarpPerspective(src, &dst, perspectiveMat, image.Point{size[1], size[0]})

	srcWnd := gocv.NewWindow("src")
	dstWnd := gocv.NewWindow("dst")
	srcWnd.IMShow(src)

	dstWnd.IMShow(dst)
	gocv.WaitKey(0)

}
