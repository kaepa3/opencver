package main

import (
	"fmt"
	"time"

	"gocv.io/x/gocv"
)

func main() {
	fmt.Println(gocv.Version())
	img := gocv.IMRead("./sample.jpg", 1)
	helloWnd := gocv.NewWindow("hello")

	helloWnd.IMShow(img)
	helloWnd.WaitKey(1)

	time.Sleep(time.Second * 5)

	helloWnd.Close()

}
