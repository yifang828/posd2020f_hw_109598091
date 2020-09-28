#include "../src/ellipse.h"

TEST(Shapes, EllipseArea){
    Ellipse ellipse(4.000, 3.712);
    ASSERT_EQ(46.646, ellipse.area());
}

TEST(Shapes, EllipsePerimeter){
    Ellipse ellipse1(4.000, 3.712);
    Ellipse ellipse2(5.556, 3.002);
    ASSERT_NEAR(24.475, ellipse1.perimeter(), 0.01);
    ASSERT_NEAR(29.078, ellipse2.perimeter(),0.01);
}

TEST(Shapes, EllipseInfo){
    Ellipse ellipse(4.000, 3.712);
    ASSERT_EQ("Ellipse (4.000, 3.712)", ellipse.info());
}

TEST(Shapes, NotEllipse){
    try{
        Ellipse (1, 1);
        Ellipse (0, -1);
        Ellipse (1, -1);
        Ellipse (-1, -1);
        Ellipse (2, 3);
    }catch(std::string e){
        ASSERT_EQ("This is not an ellipse!", e);
    }
    ASSERT_NO_THROW(Ellipse(1, 1));
}