#include "../src/triangle.h"

TEST(Shapes, TrianglePerimeter){
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(2.5, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 5.5));
    Triangle triangle("t",triangleVector);
    
    ASSERT_EQ(14.042, triangle.perimeter());
}

TEST(Shapes, triangleArea){
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(2.5, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 5.5));
    Triangle triangle("t",triangleVector);
    
    ASSERT_NEAR(6.875, triangle.area(), 0.01);
}

TEST(Shapes, triangleInfo){
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(2.5, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 5.5));
    Triangle triangle("t",triangleVector);

    ASSERT_EQ("Triangle ([0.000, 0.000], [2.500, 0.000], [0.000, 5.500])", triangle.info());
}

TEST(Shapes, notTriangle){
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(5,0));
    triangleVector.push_back(new TwoDimensionalCoordinate(2,5));
    triangleVector.push_back(new TwoDimensionalCoordinate(5,0));
    triangleVector.push_back(new TwoDimensionalCoordinate(6,0));
    try{
        Triangle triangle("t",triangleVector);
    }catch(std::string e){
        ASSERT_EQ("This is not a triangle!", e);
    }
    std::vector<TwoDimensionalCoordinate*> triangleVector2;
    triangleVector2.push_back(new TwoDimensionalCoordinate(2,5));
    triangleVector2.push_back(new TwoDimensionalCoordinate(5,0));
    triangleVector2.push_back(new TwoDimensionalCoordinate(6,0));
    Triangle triangle2("t",triangleVector2);
    ASSERT_NO_THROW(triangle2);

}