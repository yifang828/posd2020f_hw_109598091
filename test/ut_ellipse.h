#include "../src/ellipse.h"

TEST(Shapes, EllipseArea){
    Ellipse ellipse(3.712, 4.000);
    ASSERT_EQ(46.646, ellipse.area());
}

TEST(Shapes, EllipsePerimeter){
    Ellipse ellipse1(3.712, 4.000);
    Ellipse ellipse2(5.556, 3.002);
    ASSERT_NEAR(24.475, ellipse1.perimeter(), 0.001);
    ASSERT_NEAR(29.078, ellipse2.perimeter(),0.001);
}

TEST(Shapes, EllipseInfo){
    Ellipse ellipse(3.712, 4.000);
    ASSERT_EQ("Ellipse (3.712, 4.000)", ellipse.info());
}

TEST(Shapes, NotEllipse){
    try{
        Ellipse (1, 1);
        Ellipse (0, -1);
        Ellipse (1, -1);
        Ellipse (-1, -1);
    }catch(std::string e){
        ASSERT_EQ("This is not a ellipse!", e);
    }
    ASSERT_NO_THROW(Ellipse(1, 1));
}