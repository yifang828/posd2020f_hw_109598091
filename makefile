.PHONY: dirs clean ut_main2

all: dirs ut_main2

ut_main: test/ut_main.cpp test/ut_rectangle.h src/rectangle.h src/ellipse.h test/ut_ellipse.h

ut_main2: ut_main test/ut_twoDimension.h src/two_dimensional_coordinate.h test/ut_triangle.h src/triangle.h
	g++ test/ut_main.cpp -o bin/ut_main -lgtest -lpthread

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -rf ./bin ./obj

# run:
# 	./bin/ut_main --gtest_output=xml:output.xml