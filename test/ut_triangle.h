#include "../src/triangle.h"

TEST(Shapes, TrianglePerimeter){
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(2.5, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 5.5));
    Triangle triangle(triangleVector);
    
    ASSERT_EQ(14.042, triangle.perimeter());
}

// TEST(Shapes, calculateEdge){
//     std::vector<TwoDimensionalCoordinate*> point;
//     point.push_back(new TwoDimensionalCoordinate(0, 0));
//     point.push_back(new TwoDimensionalCoordinate(3, 0));
//     Triangle triangle(point);

//     ASSERT_EQ(3, triangle.calculateEdge(point[0], point[1]));
// }

TEST(Shapes, triangleArea){
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(2.5, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 5.5));
    Triangle triangle(triangleVector);
    
    ASSERT_NEAR(6.875, triangle.area(), 0.01);
}

TEST(Shapes, triangleInfo){
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(2.5, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 5.5));
    Triangle triangle(triangleVector);

    ASSERT_EQ("Triangle ([0.000, 0.000], [2.500, 0.000], [0.000, 5.500])", triangle.info());
}

TEST(Shapes, notTriangle){
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(5,0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0,5));
    triangleVector.push_back(new TwoDimensionalCoordinate(5,0));
    try{
        Triangle triangle(triangleVector);
    }catch(std::string e){
        ASSERT_EQ("This is not a triangle!", e);
    }
    triangleVector.pop_back();
    triangleVector.push_back(new TwoDimensionalCoordinate(1,2));
    Triangle triangle2(triangleVector);
    ASSERT_NO_THROW(triangle2);

}