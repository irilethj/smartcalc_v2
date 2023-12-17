#include <iostream>

#include "Calculator_2/controller/controller.h"
#include "gtest/gtest.h"

using namespace s21;

TEST(calculator, sum) {
  double result = 0;
  double ans = 10;
  class Controller P;
  const std::string exp = "5+5";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("");
  }
  EXPECT_EQ(result, ans);
}

TEST(calculator, sub) {
  double result = 0;
  double ans = 10;
  class Controller P;
  const std::string exp = "20-10";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("");
  }
  EXPECT_EQ(result, ans);
}

TEST(calculator, arithmetic_1) {
  double result = 0;
  double ans = 20;
  class Controller P;
  const std::string exp = "150/10+5*2/2";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("");
  }
  EXPECT_EQ(result, ans);
}

TEST(calculator, arithmetic_2) {
  double result = 0;
  double ans = 9;
  class Controller P;
  const std::string exp = "5+5-2*3/6";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("");
  }
  EXPECT_EQ(result, ans);
}

TEST(calculator, arithmetic_3) {
  double result = 0;
  double ans = 50;
  class Controller P;
  const std::string exp = "X+X";
  const std::string x = "25";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer(x);
  }
  EXPECT_EQ(result, ans);
}

TEST(calculator, func_1) {
  double result = 0;
  double ans = 0.36235775447667423;
  class Controller P;
  const std::string exp = "cos(10mod2.2)";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("");
  }
  EXPECT_NEAR(result, ans, 1e-7);
}

TEST(calculator, func_2) {
  double result = 0;
  double ans = 1.5174271293851465;
  class Controller P;
  const std::string exp = "sqrt(ln(10))";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("");
  }
  EXPECT_NEAR(result, ans, 1e-7);
}

TEST(calculator, func_3) {
  double result = 0;
  double ans = 0.9271065634143647;
  class Controller P;
  const std::string exp = "atan(10)+sin(10)";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("");
  }
  EXPECT_NEAR(result, ans, 1e-7);
}

TEST(calculator, func_4) {
  double result = 0;
  double ans = 1.570796326;
  class Controller P;
  const std::string exp = "asin(1)";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("");
  }
  EXPECT_NEAR(result, ans, 1e-7);
}

TEST(calculator, arithmetic_4) {
  double result = 0;
  double ans = 210;
  class Controller P;
  const std::string exp = "10-20*(-10)";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("");
  }
  EXPECT_EQ(result, ans);
}

TEST(calculator, func_5) {
  double result = 0;
  double ans = -132.377067006;
  class Controller P;
  const std::string exp =
      "1-sin(1)-sin(1)+sin(1)-cos(1)+tan(1)-(cos(1)-cos(1))-sqrt(1)-2^2/"
      "(4+1-1*23*5/4/6)/((cos(1)+cos(2))/(1+2+3))/7";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("");
  }
  EXPECT_NEAR(result, ans, 1e-7);
}

TEST(calculator, func_6) {
  double result = 0;
  double ans = 20.998589057;
  class Controller P;
  const std::string exp = "ln(35)*5-log(6)+sqrt(16)";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("");
  }
  EXPECT_NEAR(result, ans, 1e-7);
}

TEST(calculator, func_7) {
  double result = 0;
  double ans = 2.35619449;
  class Controller P;
  const std::string exp = "acos(10mod3)+asin(1)+atan(1)";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("");
  }
  EXPECT_NEAR(result, ans, 1e-7);
}

TEST(calculator, func_8_X) {
  double result = 0;
  double ans = 2.35619449;
  class Controller P;
  const std::string exp = "acos(10modX)+asin(1)+atan(1)";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("3");
  }
  EXPECT_NEAR(result, ans, 1e-7);
}

TEST(calculator, func_9) {
  double result = 0;
  double ans = 1.94939;
  class Controller P;
  const std::string exp = "log(89)";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("");
  }
  EXPECT_NEAR(result, ans, 1e-7);
}

TEST(calculator, validator_1) {
  bool ans = false;
  class Controller P;
  const std::string exp = ")+9*(435)";
  bool result = P.ValidateExpression(exp);
  EXPECT_EQ(result, ans);
}

TEST(calculator, e_notation_1) {
  double result = 0;
  double ans = 1;
  class Controller P;
  const std::string exp = "65e+3/65-999";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("");
  }
  EXPECT_EQ(result, ans);
}

TEST(calculator, e_notation_2) {
  double result = 0;
  double ans = 59;
  class Controller P;
  const std::string exp = "65e-3*1000-6";
  if (P.ValidateExpression(exp)) {
    result = P.SetAnswer("");
  }
  EXPECT_EQ(result, ans);
}

TEST(calculator, validator_2) {
  bool ans = false;
  class Controller P;
  const std::string exp = "mod 9 - 3 * sin5";
  bool result = P.ValidateExpression(exp);
  EXPECT_EQ(result, ans);
}

TEST(calculator, validator_3) {
  bool ans = false;
  class Controller P;
  const std::string exp = "* 7 + 1 * 2";
  bool result = P.ValidateExpression(exp);
  EXPECT_EQ(result, ans);
}

TEST(calculator, validator_4) {
  bool ans = false;
  class Controller P;
  const std::string exp = "/ 4 + 2 * 3";
  bool result = P.ValidateExpression(exp);
  EXPECT_EQ(result, ans);
}

TEST(calculator, validator_5) {
  bool ans = false;
  class Controller P;
  const std::string exp = "- * 5 + 3";
  bool result = P.ValidateExpression(exp);
  EXPECT_EQ(result, ans);
}

TEST(calculator, validator_6) {
  bool ans = false;
  class Controller P;
  const std::string exp = "+ mod 56 - 2";
  bool result = P.ValidateExpression(exp);
  EXPECT_EQ(result, ans);
}

TEST(calculator, validator_7) {
  bool ans = false;
  class Controller P;
  const std::string exp = "7** + 6";
  bool result = P.ValidateExpression(exp);
  EXPECT_EQ(result, ans);
}

TEST(calculator, validator_8) {
  bool ans = false;
  class Controller P;
  const std::string exp = "6^/";
  bool result = P.ValidateExpression(exp);
  EXPECT_EQ(result, ans);
}

TEST(calculator, validator_9) {
  bool ans = false;
  class Controller P;
  const std::string exp = "6^-*";
  bool result = P.ValidateExpression(exp);
  EXPECT_EQ(result, ans);
}

TEST(calculator, validator_10) {
  bool ans = false;
  class Controller P;
  const std::string exp = "98(78)";
  bool result = P.ValidateExpression(exp);
  EXPECT_EQ(result, ans);
}

TEST(calculator, validator_11) {
  bool ans = false;
  class Controller P;
  const std::string exp = "error!";
  bool result = P.ValidateExpression(exp);
  EXPECT_EQ(result, ans);
}

TEST(calculator, validator_12) {
  bool ans = false;
  class Controller P;
  const std::string exp = "nan+5";
  bool result = P.ValidateExpression(exp);
  EXPECT_EQ(result, ans);
}

TEST(calculator, validator_13) {
  bool ans = false;
  class Controller P;
  const std::string exp = "inf+8";
  bool result = P.ValidateExpression(exp);
  EXPECT_EQ(result, ans);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}