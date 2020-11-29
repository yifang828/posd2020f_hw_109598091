#include "../src/shape_builder.h"
#include <cmath>

TEST(ShapeBuilderTest, build_triangle){
    ShapeBuilder sb;
    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[0]->info());
}

TEST(ShapeBuilderTest, build_rectangle){
    ShapeBuilder sb;
    sb.buildRectangle(3, 4);
    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Rectangle (3.000, 4.000)", results[0]->info());
}

TEST(ShapeBuilderTest, build_ellipse){
    ShapeBuilder sb;
    sb.buildEllipse(2, 2);
    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Ellipse (2.000, 2.000)", results[0]->info());
}

TEST(ShapeBuilderTest, build_compoundShape){
    ShapeBuilder sb;
    sb.buildCompoundShapeBegin();
    sb.buildRectangle(3, 4);
    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    sb.buildCompoundShapeEnd();
    std::deque<Shape*> result = sb.getResult();
    
    ASSERT_EQ(1, result.size());
    ASSERT_EQ(18, result[0]->area());
}

TEST(ShapeBuilder, build_forest){
    ShapeBuilder sb;
    sb.buildRectangle(5, 5);
    sb.buildCompoundShapeBegin();
    sb.buildRectangle(3, 4);
    sb.buildCompoundShapeBegin();
    sb.buildRectangle(2, 2);
    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    sb.buildCompoundShapeEnd();
    sb.buildCompoundShapeEnd();
    sb.buildTriangle(0, 1, 1, 0, 0, 0);
    std::deque<Shape*> result = sb.getResult();

    ASSERT_EQ(3, result.size());
    ASSERT_EQ(25, result[0]->area());
    ASSERT_EQ(22, result[1]->area());
    ASSERT_NEAR(0.5, result[2]->area(), 0.001);
}

TEST(ShapeBuilder, build_compoundshape_with_empty_compoundshape){
    ShapeBuilder sb;
    sb.buildCompoundShapeBegin();
    sb.buildCompoundShapeBegin();
    sb.buildCompoundShapeEnd();
    sb.buildCompoundShapeBegin();
    sb.buildCompoundShapeEnd();
    sb.buildCompoundShapeEnd();
    std::deque<Shape*> result = sb.getResult();

    ASSERT_EQ(1, result.size());
}