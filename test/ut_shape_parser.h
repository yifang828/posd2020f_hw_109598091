#include "../src/shape_parser.h"
#include <deque>

TEST(ShapeParserTest, parser_rectangle){
    ShapeParser sp("Rectangle (4.000, 3.000)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Rectangle (4.000, 3.000)", results[0]->info());
}

TEST(ShapeParserTest, parser_triangle){
    ShapeParser sp("Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[0]->info());
}

TEST(ShapeParserTest, parser_Ellipse){
    ShapeParser sp("Ellipse (4.000, 3.000)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Ellipse (4.000, 3.000)", results[0]->info());
}

TEST(ShapeParserTest, parser_shapes){
    ShapeParser sp("Rectangle (3.000, 4.000), Ellipse (4.200, 3.700), Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(3, results.size());

    EXPECT_EQ("Rectangle (3.000, 4.000)", results[0]->info());
    EXPECT_EQ("Ellipse (4.200, 3.700)", results[1]->info());
    EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[2]->info());
}

TEST(ShapeParserTest, parser_ignored_invalid_arguement){
    ShapeParser sp("Rectangle (3.000, 4.000), Ellipse (4.200, 3.700), Ellipse (4.200, 3.700, 12.502), \
        Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(3, results.size());

    EXPECT_EQ("Rectangle (3.000, 4.000)", results[0]->info());
    EXPECT_EQ("Ellipse (4.200, 3.700)", results[1]->info());
    EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[2]->info());
}

TEST(ShapeParserTest, parser_compoundShape){
    ShapeParser sp("CompoundShape {Rectangle (4.000, 3.000), Ellipse (4.000, 3.000)}");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());

    EXPECT_EQ("Compound Shape {Rectangle (4.000, 3.000), Ellipse (4.000, 3.000)}", results[0]->info());
}

TEST(ShapeParserTest, parser_empty_compoundShape){
    ShapeParser sp("CompoundShape {}");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());

    EXPECT_EQ("Compound Shape {}", results[0]->info());
}

TEST(ShapeParserTest, parser_compoundShape_with_empty_compoundShape_and_simple_shapes){
    ShapeParser sp("CompoundShape {Rectangle (4.000, 3.000), Ellipse (4.000, 3.000), CompoundShape {}}");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());

    EXPECT_EQ("Compound Shape {Rectangle (4.000, 3.000), Ellipse (4.000, 3.000), Compound Shape {}}", results[0]->info());
}

TEST(ShapeParserTest, parser_compoundShape_with_simple_shapes_and_empty_compoundShape){
    ShapeParser sp("CompoundShape {Rectangle (4.000, 3.000), Ellipse (4.000, 3.000)}, CompoundShape {}");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(2, results.size());

    EXPECT_EQ("Compound Shape {Rectangle (4.000, 3.000), Ellipse (4.000, 3.000)}", results[0]->info());
    EXPECT_EQ("Compound Shape {}", results[1]->info());
}