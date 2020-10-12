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

        // shapeV.push_back(r34);
        // shapeV.push_back(e22);
        // cs1 = new CompoundShape("cs1", & shapes);
        // t345 = new Triangle(3, 4, 5);
    }
    void TearDown()override{
        delete r34;
        delete e22;
        delete cs1;
        // delete &shapeV;
    }
    Shape * r34;
    Shape * e22;
    Shape * cs1;
    // std::vector<Shape*> shapeV;
};

TEST_F(CompoundShapeTest, AddShapeToCompoundShape){
    std::vector<Shape*> shapeV;
    shapeV.push_back(r34);
    shapeV.push_back(e22);
    CompoundShape cs("cs", & shapeV);

    ASSERT_EQ(2, cs._shape.size());
}

TEST_F(CompoundShapeTest, NoShapeInCompoundShape){
    std::vector<Shape*> shapeV;
    try{
        CompoundShape cs("cs", & shapeV);
        FAIL();
    }catch(std::string e){
        ASSERT_EQ("This is not a compound shape!",e);
    }
}
TEST_F(CompoundShapeTest, CompoundShapeDefault){
    // std::vector<Shape*> shapeV;
    // shapeV.push_back(r34);
    // CompoundShape cs("cs", & shapeV);
    // for(Shape * shapePtr : cs._shape){ 
    //     ASSERT_EQ("transparent", shapePtr->color());
    // }
    std::vector<Shape*> shapeV;
    shapeV.push_back(r34);
    Shape * s = new CompoundShape("s", &shapeV);
    ASSERT_EQ("transparent", s->color());
}

TEST_F(CompoundShapeTest, CompoundShapeArea){
    std::vector<Shape*> shapeV;
    shapeV.push_back(r34);
    shapeV.push_back(e22);
    CompoundShape cs("cs", & shapeV);
    ASSERT_NEAR(24.566, cs.area(),0.01);
}

TEST_F(CompoundShapeTest, CompoundShapePerimeter){
    std::vector<Shape*> shapeV;
    shapeV.push_back(r34);
    shapeV.push_back(e22);
    CompoundShape cs("cs", & shapeV);
    ASSERT_NEAR(26.566, cs.perimeter(),0.01);
}

TEST_F(CompoundShapeTest, CompoundShapeInfo){
    std::vector<Shape*> shapeV;
    shapeV.push_back(r34);
    shapeV.push_back(e22);
    CompoundShape cs("cs", & shapeV);
    ASSERT_EQ("Compound Shape {Rectangle (3.000, 4.000), Ellipse (2.000, 2.000)}", cs.info());
}

TEST_F(CompoundShapeTest, CompoundShapeAddSape){
    std::vector<Shape*> shapeV;
    shapeV.push_back(r34);
    shapeV.push_back(e22);
    CompoundShape cs("cs", & shapeV);
    
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    Triangle triangle("t",triangleVector);
    cs.addShape(&triangle);

    ASSERT_EQ(3, cs._shape.size());
}

TEST_F(CompoundShapeTest, GetById){
    std::vector<Shape*> shapeV;
    shapeV.push_back(r34);
    shapeV.push_back(e22);
    CompoundShape cs("cs", & shapeV);
    ASSERT_EQ("e22", cs.getShapeById("e22")->id());
    try{
        cs.getShapeById("r22");
        FAIL();
    }catch(std::string e){
        ASSERT_EQ("Expected get shape but shape not found", e);
    }
}

TEST_F(CompoundShapeTest, deleteShapeById){
    std::vector<Shape*> shapeV;
    shapeV.push_back(r34);
    shapeV.push_back(e22);
    CompoundShape cs("cs", & shapeV);
    cs.deleteShapeById("e22");
    ASSERT_EQ(1, cs._shape.size());
    try{
        cs.deleteShapeById("e22");
        FAIL();
    }catch(std::string e){
        ASSERT_EQ("Expected delete shape but shape not found", e);
    }
}