#include "../src/terminal.h"

class TerminalTest : public ::testing::Test
{
protected:
    void SetUp() override{
        successT1 = new Terminal("Rectangle (2, 2) Rectangle (1, 1) area inc");

    }
    void TearDown() override{
        delete successT1;
    }

    Terminal * successT1;
};
TEST_F(TerminalTest, showResult){
    std::cout << successT1->showResult()<<std::endl;
    // ASSERT_EQ("1.000\n4.000", successT1->showResult());
}