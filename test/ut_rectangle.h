#include "../src/rectangle.h"

TEST(Shapes, RectangleArea){
    Rectangle rectangle("r",3, 4.5);
    ASSERT_EQ(13.5, rectangle.area());
}

TEST(Shapes, RectanglePerimeter){
    Rectangle rectangle("r",3, 4.5);
    ASSERT_EQ(15, rectangle.perimeter());
}

TEST(Shapes, RectangleInfo){
    Rectangle rectangle("r",3, 4.5);
    ASSERT_EQ("Rectangle (3.000, 4.500)", rectangle.info());
}

TEST(Shapes, NotRectangle){
    try 
    {
        Rectangle ("r01",0, 1);
        Rectangle ("r20",2, 0);
        Rectangle ("r-12",-1, 2);
        Rectangle ("r2-1",2, -1);
    }catch(std::string e)
    {   
        ASSERT_EQ("This is not a rectangle!", e);
    }
    ASSERT_NO_THROW(Rectangle("r11",1, 1));
}

TEST(Shapes, RectangleType){
    Rectangle rectangle("r", 3, 4);
    ASSERT_EQ("Rectangle", rectangle.type());
}