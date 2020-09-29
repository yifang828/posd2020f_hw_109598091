#include "../src/shape.h"
#include "../src/sort.h"

class SortTest : public ::testing::Test{
  protected:
    void SetUp() override{
        std::vector<TwoDimensionalCoordinate*> triangleVector;
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
        
        t345 = new Triangle(triangleVector);
        r22 = new Rectangle(2, 2);
        r34 = new Rectangle(3, 4);
    }

    void TearDown() override{
        delete t345;
        delete r22;
        delete r34;
    }

    Shape * t345;
    Shape * r22;
    Shape * r34;
};

 TEST_F(SortTest, quickSortAreaAsc){
    std::array<Shape *, 3> shapes = {t345, r22, r34};
    int n = sizeof(shapes)/sizeof(shapes[0]);
    quickSort(shapes.begin(), shapes.end(), areaAscendingCompare);
    ASSERT_EQ(4, shapes[0]->area());
    ASSERT_EQ(6, shapes[1]->area());
    ASSERT_EQ(12, shapes[2]->area());
 }

 TEST_F(SortTest, quickSortAreaDesc){
    std::array<Shape *, 3> shapes = {t345, r22, r34};
    int n = sizeof(shapes)/sizeof(shapes[0]);
    quickSort(shapes.begin(), shapes.end(), areaDescendingCompare);
    ASSERT_EQ(12, shapes[0]->area());
    ASSERT_EQ(6, shapes[1]->area());
    ASSERT_EQ(4, shapes[2]->area());
 }

 TEST_F(SortTest, quickSortPerimeterAsc){
    std::array<Shape *, 3>shapes = {t345, r22, r34};
    int n = sizeof(shapes)/sizeof(shapes[0]);
    quickSort(shapes.begin(), shapes.end(), perimeterAscendingCompare);
    ASSERT_EQ(8, shapes[0]->perimeter());
    ASSERT_EQ(12, shapes[1]->perimeter());
    ASSERT_EQ(14, shapes[2]->perimeter());
 }

 TEST_F(SortTest, quickSortPerimeterDesc){
    std::array<Shape *, 3> shapes = {t345, r22, r34};
    int n = sizeof(shapes)/sizeof(shapes[0]);
    quickSort(shapes.begin(), shapes.end(), perimeterDescendingCompare);
    ASSERT_EQ(14, shapes[0]->perimeter());
    ASSERT_EQ(12, shapes[1]->perimeter());
    ASSERT_EQ(8, shapes[2]->perimeter());
 }

TEST_F(SortTest, quickSortWithObjAsc){
    std::array<Shape *, 3>shapes = {t345, r22, r34};
    int n = sizeof(shapes)/sizeof(shapes[0]);
    AscendingCompare ascCompare("area");
    quickSort(shapes.begin(), shapes.end(), ascCompare);
    ASSERT_EQ(4, shapes[0]->area());
    ASSERT_EQ(6, shapes[1]->area());
    ASSERT_EQ(12, shapes[2]->area());

    AscendingCompare ascCompare2("perimeter");
    quickSort(shapes.begin(), shapes.end(), ascCompare2);
    ASSERT_EQ(8, shapes[0]->perimeter());
    ASSERT_EQ(12, shapes[1]->perimeter());
    ASSERT_EQ(14, shapes[2]->perimeter());
}

TEST_F(SortTest, quickSortWithObjDesc){
    std::array<Shape *, 3>shapes = {t345, r22, r34};
    int n = sizeof(shapes)/sizeof(shapes[0]);
    DescendingCompare desceCompare("area");
    quickSort(shapes.begin(), shapes.end(), desceCompare);
    ASSERT_EQ(12, shapes[0]->area());
    ASSERT_EQ(6, shapes[1]->area());
    ASSERT_EQ(4, shapes[2]->area());

    DescendingCompare desceCompare2("perimeter");
    quickSort(shapes.begin(), shapes.end(), desceCompare2);
    ASSERT_EQ(14, shapes[0]->perimeter());
    ASSERT_EQ(12, shapes[1]->perimeter());
    ASSERT_EQ(8, shapes[2]->perimeter());
}