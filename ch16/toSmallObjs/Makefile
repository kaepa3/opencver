COMPILER  = g++
INCLUDES = -I/usr/local/include/opencv4
LIBS = -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_photo -lopencv_features2d -lopencv_objdetect
main: main.cpp
	$(COMPILER) -std=c++17 main.cpp ../../common/createCosMat.cpp ../../common/mulMatWtbl.cpp $(INCLUDES) $(LIBS) -o main 

clean:
	rm -f *.o main
