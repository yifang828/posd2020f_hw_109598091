#include <list>
#include "../src/shape.h"
#include "../src/rectangle.h"
#include "../src/ellipse.h"
#include "../src/compound_shape.h"
#include "../src/iterator.h"

class IteratorTest: public ::testing::Test{
protected:
    void SetUp()override{
        r34 = new Rectangle("r34",3, 4);
        e22 = new Ellipse("e22",2, 2);
        r11 = new Rectangle("r11", 1, 1);
        
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
        delete inner;
        delete outer;
    }
    Shape * r34;
    Shape * e22;
    Shape * r11;
    Shape * inner;
    Shape * outer;
};

TEST_F(IteratorTest, CompoundShapeIterator){
    Iterator* it = inner->createIterator();
    ASSERT_EQ(12, it->currentItem()->area());
    it->next();
    ASSERT_EQ(12.566, it->currentItem()->area());
        it->next();
        ASSERT_TRUE(it->isDone());
    try{
        it->next();
        FAIL();
    }catch(std::string e){
        ASSERT_EQ("Moving past the end!", e);
    }
}
TEST_F(IteratorTest, NullIterator){
    try{
        r34->createIterator()->currentItem();
        FAIL();
    }catch(std::string e){
        ASSERT_EQ("No child member!", e);
    }
}