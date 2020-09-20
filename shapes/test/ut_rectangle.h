#include "../src/rectangle.h"

TEST(Shapes, RectangleArea){
    Rectangle rectangle(3, 4.5);
    ASSERT_EQ(13.5, rectangle.area());
}

TEST(Shapes, RectanglePerimeter){
    Rectangle rectangle(3, 4.5);
    ASSERT_EQ(15, rectangle.perimeter());
}

TEST(Shapes, RectangleInfo){
    Rectangle rectangle(3, 4.5);
    ASSERT_EQ("Rectangle (3.000, 4.500)", rectangle.info());
}

TEST(Shapes, NotRectangle){
    try 
    {
        Rectangle (0, 1);
        Rectangle (2, 0);
        Rectangle (-1, 2);
        Rectangle (2, -1);
    }catch(std::string e)
    {   
        ASSERT_EQ("This is not a rectangle!", e);
    }
    ASSERT_NO_THROW(Rectangle(1, 1));
}