#pragma once
#include <gtest/gtest.h>
#include "C:\Users\vatsl\source\repos\calc\calc\calc.h";
#include "pch.h"

// Тест функции ParsingAnExample
TEST(ParsingAnExampleTest, BasicExpressions) {
    EXPECT_EQ(ParsingAnExample("2+2"), std::vector<std::string>({ "2", "+", "2" }));
    EXPECT_EQ(ParsingAnExample("sin(3)"), std::vector<std::string>({ "sin(3)" }));
    EXPECT_EQ(ParsingAnExample("3+4*5"), std::vector<std::string>({ "3", "+", "4", "*", "5" }));
    EXPECT_EQ(ParsingAnExample("sqrt(16) - 4"), std::vector<std::string>({ "sqrt(16)", "-", "4" }));
}

// Тест функции StringToFloat
TEST(StringToFloatTest, ValidInputs) {
    EXPECT_FLOAT_EQ(StringToFloat("3.14"), float(3.14));
    EXPECT_FLOAT_EQ(StringToFloat("sin(3.14)"), float(sin(3.14)));
    EXPECT_FLOAT_EQ(StringToFloat("sqrt(16)"), float(4.0));
    EXPECT_FLOAT_EQ(StringToFloat("(2.5)"), float(2.5));
}

TEST(StringToFloatTest, InvalidInputs) {
    EXPECT_THROW(StringToFloat("abc"), std::invalid_argument);
    EXPECT_THROW(StringToFloat("123abc"), std::invalid_argument);
    EXPECT_THROW(StringToFloat("sin()"), std::invalid_argument);
}

// Тест функции Calculate
TEST(CalculateTest, BasicOperations) {
    EXPECT_FLOAT_EQ(Calculate(2, 2, "+"), 4);
    EXPECT_FLOAT_EQ(Calculate(5, 3, "-"), 2);
    EXPECT_FLOAT_EQ(Calculate(3, 4, "*"), 12);
    EXPECT_FLOAT_EQ(Calculate(10, 2, "/"), 5);
    EXPECT_FLOAT_EQ(Calculate(2, 3, "^"), double(pow(2, 3)));
}

TEST(CalculateTest, DivisionByZero) {
    EXPECT_THROW(Calculate(5, 0, "/"), std::invalid_argument);
}

// Тест функции EvaluateExpression
TEST(EvaluateExpressionTest, SimpleExpressions) {
    EXPECT_FLOAT_EQ(EvaluateExpression({ "2", "+", "2" }), 4);
    EXPECT_FLOAT_EQ(EvaluateExpression({ "3", "*", "4" }), 12);
    EXPECT_FLOAT_EQ(EvaluateExpression({ "10", "/", "2" }), 5);
    EXPECT_FLOAT_EQ(EvaluateExpression({ "2", "^", "3" }), 8);
}

TEST(EvaluateExpressionTest, ComplexExpressions) {
    EXPECT_FLOAT_EQ(EvaluateExpression({ "sin(3.14)", "+", "1" }), float(sin(3.14) + 1));
    EXPECT_FLOAT_EQ(EvaluateExpression({ "sqrt(16)", "-", "4" }), 0);
    EXPECT_FLOAT_EQ(EvaluateExpression({ "2", "*", "sqrt(4)" }), 4);
}

TEST(EvaluateExpressionTest, InvalidExpressions) {
    EXPECT_THROW(EvaluateExpression({ "2", "+" }), std::runtime_error);
    EXPECT_THROW(EvaluateExpression({ "+" }), std::runtime_error);
    EXPECT_THROW(EvaluateExpression({ "2", "/", "0" }), std::invalid_argument);
}
