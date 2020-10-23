#include "../src/shape.h"
#include "../src/compound_shape.h"
#include "../src/rectangle.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"

class CompoundShapeTest: public ::testing::Test{
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
        shapesOuter.push_back(inner);
        shapesOuter.push_back(r11);
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

TEST_F(CompoundShapeTest, NoShapeInCompoundShape){
    std::list<Shape*> shapeV;
    try{
        CompoundShape cs("cs", shapeV);
        FAIL();
    }catch(std::string e){
        ASSERT_EQ("This is not a compound shape!",e);
    }
}

TEST_F(CompoundShapeTest, CompoundShapeDefault){
    ASSERT_EQ("transparent", inner->color());
}

TEST_F(CompoundShapeTest, CompoundShapeArea){
    ASSERT_NEAR(24.566, inner->area(),0.01);
}

TEST_F(CompoundShapeTest, CompoundShapePerimeter){
    ASSERT_NEAR(26.566, inner->perimeter(),0.01);
}

TEST_F(CompoundShapeTest, CompoundShapeInfo){
    ASSERT_EQ("Compound Shape {Rectangle (3.000, 4.000), Ellipse (2.000, 2.000)}", inner->info());
}

TEST_F(CompoundShapeTest, CompoundShapeAddSape){
    inner->addShape(t345);
    ASSERT_EQ("Compound Shape {Rectangle (3.000, 4.000), Ellipse (2.000, 2.000), Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])}", inner->info());
}

TEST_F(CompoundShapeTest, GetById){
    ASSERT_EQ("e22", inner->getShapeById("e22")->id());
    try{
        inner->getShapeById("r22");
        FAIL();
    }catch(std::string e){
        ASSERT_EQ("Expected get shape but shape not found", e);
    }
}

TEST_F(CompoundShapeTest, deleteShapeById){
    inner->deleteShapeById("e22");
    ASSERT_EQ("Compound Shape {Rectangle (3.000, 4.000)}", inner->info());
    try{
        inner->deleteShapeById("e22");
        FAIL();
    }catch(std::string e){
        ASSERT_EQ("Expected delete shape but shape not found", e);
    }
}

TEST_F(CompoundShapeTest, FindInTreeCompoundShape){
    std::list<Shape*> shape3;
    shape3.push_back(t345);
    shape3.push_back(outer);
    Shape * cs3 = new CompoundShape("cs3", shape3);
    ASSERT_EQ("Rectangle (3.000, 4.000)", cs3->getShapeById("r34")->info());
    try{
        cs3->getShapeById("r00");
        FAIL();
    }catch (std::string e){
        ASSERT_EQ("Expected get shape but shape not found", e);
    }
}

TEST_F(CompoundShapeTest, DeleteInTreeCompoundShape){
    outer->addShape(t345);
    outer->deleteShapeById("r34");
    ASSERT_EQ("Compound Shape {Compound Shape {Ellipse (2.000, 2.000)}, Rectangle (1.000, 1.000), Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])}", outer->info());
    try{
        outer->deleteShapeById("r00");
        FAIL();
    }catch (std::string e){
        ASSERT_EQ("Expected delete shape but shape not found", e);
    }
}

TEST_F(CompoundShapeTest, CompoundShapeType){
    ASSERT_EQ("Compound Shape", inner->type());
}