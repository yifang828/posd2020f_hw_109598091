.PHONY: dirs clean

all: dirs ut_main ut_main2

ut_main: test/ut_main.cpp test/ut_rectangle.h src/rectangle.h src/ellipse.h test/ut_ellipse.h

ut_main2: test/ut_twoDimension.h src/twoDimensionalCoordinate.h test/ut_triangle.h src/triangle.h
	g++ test/ut_main.cpp -o bin/ut_main -lgtest -lpthread

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*