.PHONY: dirs clean ut_main2

# all: dirs ut_main
all: dirs geo

geo: src/main.cpp $(SRC) $(TEST)
	g++ src/main.cpp -o bin/geo

ut_main: test/ut_main.cpp $(SRC) $(TEST)
	g++ test/ut_main.cpp -o bin/ut_main -lgtest -lpthread

TEST: test/ut_rectangle.h test/ut_ellipse.h test/ut_twoDimension.h test/ut_triangle.h test/ut_sort.h test/ut_terminal.h

SRC: src/rectangle.h src/ellipse.h src/two_dimensional_coordinate.h src/triangle.h src/sort.h src/terminal.h

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -rf ./bin ./obj
	# rm output.txt