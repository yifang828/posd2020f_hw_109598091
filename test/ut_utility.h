#include <list>
#include "../src/shape.h"
#include "../src/rectangle.h"
#include "../src/ellipse.h"
#include "../src/compound_shape.h"
#include "../src/utility.h"

class UtilityTest: public::testing::Test{
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

TEST_F(UtilityTest, getShapeById){
    Shape * shape = getShapeById(inner, "e22");
    ASSERT_EQ("Ellipse (2.000, 2.000)", shape->info());
    try{
        getShapeById(inner, "r00");
        FAIL();
    }catch(std::string e){
        ASSERT_EQ("Expected get shape but shape not found", e);
    }
    try{
        getShapeById(r34, "r34");
        FAIL();
    }catch(std::string e){
        ASSERT_EQ("Only compound shape can get shape!", e);
    }
}

TEST_F(UtilityTest, getShapeByIdInTree){
    Shape * shape = getShapeById(outer, "e22");
    ASSERT_EQ("Ellipse (2.000, 2.000)", shape->info());
}

TEST_F(UtilityTest, AreaFilter){
    std::deque<Shape*> shapes = filterShape(outer, AreaFilter(10,0));
    ASSERT_EQ(1, shapes.size());
    std::deque<Shape*>::iterator itr = shapes.begin();
    ASSERT_EQ("Rectangle (1.000, 1.000)", (*itr)->info());
}

TEST_F(UtilityTest, OnlyCompoundShapeCanFilt){
    try{
        std::deque<Shape*> shapes = filterShape(r34, AreaFilter(10,0));
        FAIL();
    }catch(std::string e){
        ASSERT_EQ("Only compound shape can filter shape!", e);
    }
}

TEST_F(UtilityTest, PerimeterFilter){
    std::deque<Shape*> shapes = filterShape(outer, PerimeterFilter(10,0));
    ASSERT_EQ(1, shapes.size());
    std::deque<Shape*> shapes2 = filterShape(outer, PerimeterFilter(20,0));
    ASSERT_EQ(3, shapes2.size());
}

TEST_F(UtilityTest, ColorFilter){
    std::deque<Shape*> shapes = filterShape(outer, ColorFilter("white"));
    ASSERT_EQ(3, shapes.size());
}

TEST_F(UtilityTest, TypeFilter){
    std::deque<Shape*> shapes = filterShape(outer, TypeFilter("Rectangle"));
    ASSERT_EQ(2, shapes.size());
    std::deque<Shape*> shapes2 = filterShape(outer, TypeFilter("Compound Shape"));
    ASSERT_EQ(1, shapes2.size());
}