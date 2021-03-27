package main

import (
	"fmt"
	"os"
	"strconv"

	"gocv.io/x/gocv"
)

func main() {
	src := gocv.IMRead("../../images/sample.jpg", gocv.IMReadGrayScale)
	if src.Empty() {
		fmt.Println("img error")
		return
	}

	dst := gocv.NewMat()
	gocv.EqualizeHist(src, &dst)

	threshold := 60
	if len(os.Args) >= 2 {
		var err error
		threshold, err = strconv.Atoi(os.Args[1])
		if err != nil {
			fmt.Println("arg1 error ")
			return
		}
	}

	max := 255
	if len(os.Args) >= 3 {
		var err error
		max, err = strconv.Atoi(os.Args[2])
		if err != nil {
			fmt.Println("arg1 error ")
			return
		}
	}
	tp := gocv.ThresholdBinary
	if len(os.Args) >= 4 {
		ele, err := strconv.Atoi(os.Args[3])
		if err != nil {
			fmt.Println("arg3 error ")
			return
		}
		switch ele {
		case 0:
			tp = gocv.ThresholdBinary
		case 1:
			tp = gocv.ThresholdBinaryInv
		case 2:
			tp = gocv.ThresholdTrunc
		case 3:
			tp = gocv.ThresholdToZero
		case 4:
			tp = gocv.ThresholdToZeroInv
		}
	}
	fmt.Printf("%d:%d,%v", threshold, max, tp)
	gocv.Threshold(src, &dst, float32(threshold), float32(max), tp)

	srcWnd := gocv.NewWindow("src")
	srcWnd.IMShow(src)
	dstWnd := gocv.NewWindow("dst")
	dstWnd.IMShow(dst)
	gocv.WaitKey(0)

}
