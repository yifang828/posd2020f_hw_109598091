#include "../src/terminal.h"

class TerminalTest : public ::testing::Test{
protected:
    Terminal * successT1;
    Terminal * successT2;

    Terminal * invalidT1;
    Terminal * invalidT2;
    Terminal * invalidT3;
    Terminal * invalidT4;
    
    Terminal * validT1;
    Terminal * validT2;
    
    void SetUp() override{
        successT1 = new Terminal("Rectangle (2, 2) Rectangle (1, 1) area inc");
        successT2 = new Terminal("Ellipse (4, 3) Rectangle (1, 1) Triangle ([0,0], [3,0], [0,4]) area dec");
        
        invalidT1 = new Terminal("Rectangle (3.7, 4.2) Ellipse (4, 3) area");
        invalidT2 = new Terminal("Rectangle (3.7, 4.2) Ellipse (4, 3) inc");
        invalidT3 = new Terminal("area inc");
        invalidT4 = new Terminal("Rectangle (0, 0) Ellipse (-1, -1) area inc");//TODO

        validT1 = new Terminal("Rectangle (2, 2) Rectangle (1, 1) Ellipse$%^&(1, 1) area inc");//TODO
        validT2 = new Terminal("Rectangle (2, 2) Rectangle (1, 1) Ellipse (-1, -1) area inc");//TODO
    }
    void TearDown() override{
        delete successT1;
        delete successT2;

        delete invalidT1;
        delete invalidT2;
        delete invalidT3;
        delete invalidT4;

        delete validT1;
        delete validT2;
    }

};

TEST_F(TerminalTest, showResult){
    ASSERT_EQ("1.000\n4.000", successT1->showResult());
    ASSERT_EQ("37.699\n6.000\n1.000", successT2->showResult());
}

TEST_F(TerminalTest, invalidForm){
    try{
        invalidT1->showResult();
        FAIL();
        invalidT2->showResult();
        FAIL();
        invalidT3->showResult();
        FAIL();
        invalidT4->showResult();//TODO
        FAIL();
    }catch(std::string e){
        ASSERT_EQ("invalid input", e);
    }
}

TEST_F(TerminalTest, ignoreInvalidForm){//TODO
    ASSERT_EQ("1.000\n4.000", validT1->showResult());
    ASSERT_EQ("1.000\n4.000", validT2->showResult());
}