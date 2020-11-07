#include <list>
#include "../src/shape.h"
#include "../src/rectangle.h"
#include "../src/ellipse.h"
#include "../src/compound_shape.h"
#include "../src/visitor.h"
#include "../src/area_visitor.h"
#include "../src/info_visitor.h"

class VisitorTest: public::testing::Test{
protected:
    void SetUp()override{
        r34 = new Rectangle("r34",3, 4);
        e22 = new Ellipse("e22",2, 2);
        r11 = new Rectangle("r11", 1, 1);
        std::vector<TwoDimensionalCoordinate*> triangleVector;
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
        t345 = new Triangle("t345",triangleVector);
        
        std::list<Shape*> shapesInner;
        shapesInner.push_back(r34);
        shapesInner.push_back(e22);
        inner = new CompoundShape("inner", shapesInner);
        
        std::list<Shape*> shapesOuter;
        shapesOuter.push_back(r11);
        shapesOuter.push_back(inner);
        outer = new CompoundShape("outer", shapesOuter);
    }
    void TearDown()override{
        delete r34;
        delete e22;
        delete r11;
        delete t345;
        delete inner;
        delete outer;
    }
    Shape * r34;
    Shape * e22;
    Shape * r11;
    Shape * t345;
    Shape * inner;
    Shape * outer;
};

TEST_F(VisitorTest, RectangleAreaVisitor){
    AreaVisitor * v = new AreaVisitor();
    r34->accept(v);
    ASSERT_EQ(12, v->area());
}

TEST_F(VisitorTest, EllipseAreaVisitor){
    AreaVisitor * v = new AreaVisitor();
    e22->accept(v);
    ASSERT_NEAR(12.566, v->area(), 0.001);
}

TEST_F(VisitorTest, TriangleAreaVisitor){
    AreaVisitor * v = new AreaVisitor();
    t345->accept(v);
    ASSERT_EQ(6, v->area());
}

TEST_F(VisitorTest, CompoundShapeAreaVisitor){
    AreaVisitor * v = new AreaVisitor();
    inner->accept(v);
    ASSERT_NEAR(24.566, v->area(),0.001);
}

TEST_F(VisitorTest, EllipseInfoVisitor){
    InfoVisitor * v = new InfoVisitor();
    e22->accept(v);
    ASSERT_EQ("Ellipse (2.000, 2.000)", v->info());
}

TEST_F(VisitorTest, TriangleInfoVisitor){
    InfoVisitor * v = new InfoVisitor();
    t345->accept(v);
    ASSERT_EQ("Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])", v->info());
}

TEST_F(VisitorTest, RectangleInfoVisitor){
    InfoVisitor * v = new InfoVisitor();
    r34->accept(v);
    ASSERT_EQ("Rectangle (3.000, 4.000)", v->info());
}

TEST_F(VisitorTest, CompoundShapeInfoVisitor){
    InfoVisitor * v = new InfoVisitor();
    inner->accept(v);
    ASSERT_EQ("Compound Shape {Rectangle (3.000, 4.000), Ellipse (2.000, 2.000)}", v->info());
}