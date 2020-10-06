#include "../src/terminal.h"

class TerminalTest : public ::testing::Test{
protected:
    Terminal * successT1;
    Terminal * successT2;
    Terminal * successT3;

    Terminal * validT1;
    Terminal * validT2;
    
    void SetUp() override{
        successT1 = new Terminal("Rectangle (2, 2) Rectangle (1, 1) area inc");
        successT2 = new Terminal("Ellipse (4, 3) Rectangle (1, 1) Triangle ([0,0], [3,0], [0,4]) area dec");
        successT3 = new Terminal("Rectangle (3.7, 4.2) Ellipse (4, 3) Triangle ([0,0], [-3,0], [0,-4]) perimeter inc");
        
        validT1 = new Terminal("Rectangle (2, 2) Rectangle (1, 1) Ellipse$%^&(1, 1) area inc");
        validT2 = new Terminal("Rectangle (2, 2) Rectangle (1, 1) Ellipse (-1, -1) area inc");
    }
    void TearDown() override{
        delete successT1;
        delete successT2;
        delete successT3;

        delete validT1;
        delete validT2;
    }

};

TEST_F(TerminalTest, showResult){
    ASSERT_EQ("1.000\n4.000", successT1->showResult());
    ASSERT_EQ("37.699\n6.000\n1.000", successT2->showResult());
    ASSERT_EQ("12.000\n15.800\n22.850", successT3->showResult());
}

TEST_F(TerminalTest, invalidForm){
    try {
      Terminal("Rectangle (0, 0) Ellipse (-1, -1) area inc");
      FAIL();
      Terminal("Rectangle (3.7, 4.2) Ellipse (4, 3) area");
      FAIL();
      Terminal("Rectangle (3.7, 4.2) Ellipse (4, 3) inc");
      FAIL();
      Terminal("area inc");
      FAIL();
      Terminal("Rectangle(3.7, 4.2)");
      FAIL();
    }catch(std::string e) {
        ASSERT_EQ("invalid input", e);
    }

}

TEST_F(TerminalTest, ignoreInvalidForm){
    ASSERT_EQ("1.000\n4.000", validT1->showResult());
    ASSERT_EQ("1.000\n4.000", validT2->showResult());
}