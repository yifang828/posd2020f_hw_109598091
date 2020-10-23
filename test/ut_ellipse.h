#include "../src/ellipse.h"

TEST(Shapes, EllipseArea){
    Ellipse ellipse("e1",4.000, 3.712);
    ASSERT_EQ(46.646, ellipse.area());
}

TEST(Shapes, EllipsePerimeter){
    Ellipse ellipse1("e1",4.000, 3.712);
    Ellipse ellipse2("e2",5.556, 3.002);
    ASSERT_NEAR(24.475, ellipse1.perimeter(), 0.01);
    ASSERT_NEAR(29.078, ellipse2.perimeter(),0.01);
}

TEST(Shapes, EllipseInfo){
    Ellipse ellipse("e1",4.000, 3.712);
    ASSERT_EQ("Ellipse (4.000, 3.712)", ellipse.info());
}

TEST(Shapes, NotEllipse){
    try{
        Ellipse ("e1",1, 1);
        Ellipse ("e2",0, -1);
        Ellipse ("e3",1, -1);
        Ellipse ("e4",-1, -1);
        Ellipse ("e5",2, 3);
    }catch(std::string e){
        ASSERT_EQ("This is not an ellipse!", e);
    }
    ASSERT_NO_THROW(Ellipse("e6",1, 1));
}

TEST(Shapes, EllipseType){
    Ellipse ellipse("e", 4, 3);
    ASSERT_EQ("Ellipse", ellipse.type());
}