.PHONY: dirs clean ut_main2

all: dirs ut_main
# all: dirs geo

geo: src/main.cpp $(SRC) $(TEST)
	g++ src/main.cpp -o bin/geo

ut_main: test/ut_main.cpp $(SRC) $(TEST)
	g++ test/ut_main.cpp src/shape.cpp -o bin/ut_main -lgtest -lpthread

TEST: test/ut_rectangle.h test/ut_ellipse.h test/ut_twoDimension.h test/ut_triangle.h \
	test/ut_compound_shape.h test/ut_iterator.h test/ut_utility.h test/ut_visitor.h

SRC: src/rectangle.h src/ellipse.h src/two_dimensional_coordinate.h src/triangle.h \
	src/compound_shape.h src/iterator.h src/null_iterator.h src/shape_iterator.h src/utility.h src/visitor.h\
	src/area_visitor.h src/info_visitor.h

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -rf ./bin ./obj