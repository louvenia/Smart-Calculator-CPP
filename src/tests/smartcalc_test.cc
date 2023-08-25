#include <gtest/gtest.h>

#include "../s21_SmartCalc_v2/model/s21_smartcalc.h"

TEST(smartcalc_test, empty_expression) {
  std::string exp, x;
  s21::smartcalc expression(exp, x);

  EXPECT_FALSE(expression.get_status());
}

TEST(smartcalc_test, empty_x) {
  std::string exp = "1+2x", x;
  s21::smartcalc expression(exp, x);

  EXPECT_FALSE(expression.get_status());
}

// ----------Test function binary_operation---------------

TEST(smartcalc_test, simple_addition) {
  std::string exp = "1+2", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 3, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_addition_add_x) {
  std::string exp = "1+x", x = "99";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 100, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_subtraction) {
  std::string exp = "1-2", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), -1, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_subtraction_add_x) {
  std::string exp = "101-x", x = "1";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 100, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_multiplication) {
  std::string exp = "2*2", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 4, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_multiplication_add_x) {
  std::string exp = "2*x", x = "(99+1)";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 200, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_division) {
  std::string exp = "4/2", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 2, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_division_add_x) {
  std::string exp = "4/x", x = "(1+99)";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 0.04, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, division_zero_add_x) {
  std::string exp = "4/x", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_FALSE(expression.get_status());
}

TEST(smartcalc_test, simple_mod) {
  std::string exp = "4mod3", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 1, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_mod_add_x) {
  std::string exp = "4modx", x = "(100-95)";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 4, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, mod_zero) {
  std::string exp = "4mod0", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_FALSE(expression.get_status());
}

TEST(smartcalc_test, simple_exponentiation) {
  std::string exp = "4^2", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 16, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_exponentiation_add_x) {
  std::string exp = "4^x", x = "(10 - 2)";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 65536, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

// ----------Test function functions_operation---------------

TEST(smartcalc_test, simple_cos) {
  std::string exp = "cos(1)", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), cos(1), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_cos_add_x) {
  std::string exp = "cos(x)", x = "2-3";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), cos(-1), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_cos_add_x_u_minus) {
  std::string exp = "cos(x)", x = "-3-2";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), cos(-5), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_cos_add_x_without_brackets) {
  std::string exp = "cosx", x = "-3-2";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), cos(-3) - 2, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_sin) {
  std::string exp = "sin(0)", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), sin(0), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_sin_add_x) {
  std::string exp = "sin(x)", x = "2-3";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), sin(-1), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_sin_add_x_u_minus) {
  std::string exp = "sin(x)", x = "-3-2";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), sin(-5), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_sin_add_x_without_brackets) {
  std::string exp = "sinx", x = "-3-2";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), sin(-3) - 2, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_tan) {
  std::string exp = "tan(0)", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), tan(0), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_tan_add_x) {
  std::string exp = "tan(x)", x = "2-3";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), tan(-1), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_tan_add_x_u_minus) {
  std::string exp = "tan(x)", x = "-3-2";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), tan(-5), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_tan_add_x_without_brackets) {
  std::string exp = "tanx", x = "-3-2";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), tan(-3) - 2, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_acos) {
  std::string exp = "acos(0)", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), acos(0), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_acos_add_x) {
  std::string exp = "acos(x)", x = "99-101";
  s21::smartcalc expression(exp, x);

  EXPECT_FALSE(expression.get_status());
}

TEST(smartcalc_test, simple_acos_add_x_without_brackets) {
  std::string exp = "acosx", x = "1-2";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), acos(1) - 2, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_asin) {
  std::string exp = "asin(0)", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), asin(0), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_asin_add_x) {
  std::string exp = "asin(x)", x = "99-101";
  s21::smartcalc expression(exp, x);

  EXPECT_FALSE(expression.get_status());
}

TEST(smartcalc_test, simple_asin_add_x_without_brackets) {
  std::string exp = "asinx", x = "1-2";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), asin(1) - 2, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_atan) {
  std::string exp = "atan(0)", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), atan(0), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_atan_add_x) {
  std::string exp = "atan(x)", x = "99-101";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), atan(99 - 101), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_atan_add_x_without_brackets) {
  std::string exp = "atanx", x = "1-2";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), atan(1) - 2, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_ln) {
  std::string exp = "ln(123)", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), log(123), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_ln_add_x) {
  std::string exp = "ln(x)", x = "1+2+3";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), log(1 + 2 + 3), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_ln_add_x_zero) {
  std::string exp = "ln(x)", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_FALSE(expression.get_status());
}

TEST(smartcalc_test, simple_ln_add_x_without_brackets) {
  std::string exp = "lnx", x = "1+2+3";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), log(1) + 2 + 3, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_lg) {
  std::string exp = "lg(123)", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), log10(123), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_lg_add_x) {
  std::string exp = "lg(x)", x = "1+2+3";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), log10(1 + 2 + 3), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_lg_add_x_zero) {
  std::string exp = "lg(x)", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_FALSE(expression.get_status());
}

TEST(smartcalc_test, simple_lg_add_x_without_brackets) {
  std::string exp = "lgx", x = "1+2+3";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), log10(1) + 2 + 3, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_sqrt) {
  std::string exp = "sqrt(16)", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), sqrt(16), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_sqrt_add_x) {
  std::string exp = "sqrt(x)", x = "600/6+3";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), sqrt(600 / 6 + 3), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_sqrt_add_x_without_brackets) {
  std::string exp = "sqrtx", x = "600/6+3";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), sqrt(600) / 6 + 3, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_sqrt_less_zero) {
  std::string exp = "sqrt-100", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_FALSE(expression.get_status());
}

TEST(smartcalc_test, simple_number_dot_fun) {
  std::string exp = "5.cos(x)", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 5 * cos(0), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, simple_fun_dot_number) {
  std::string exp = "cos(x).5", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_FALSE(expression.get_status());
}

// ----------Test exponential expression---------------

TEST(smartcalc_test, exponential_expression_1) {
  s21::smartcalc expression("1E7", "0");

  EXPECT_NEAR(expression.get_result(), 1e+07, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, exponential_expression_2) {
  s21::smartcalc expression("1E007", "0");

  EXPECT_NEAR(expression.get_result(), 1e+07, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, exponential_expression_3) {
  s21::smartcalc expression("1E+7", "0");

  EXPECT_NEAR(expression.get_result(), 1e+07, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, exponential_expression_4) {
  s21::smartcalc expression("1E-7", "0");

  EXPECT_NEAR(expression.get_result(), 1e-07, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, exponential_expression_4_1) {
  s21::smartcalc expression("1E-007", "0");

  EXPECT_NEAR(expression.get_result(), 1e-07, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, exponential_expression_5) {
  s21::smartcalc expression("1e7", "0");

  EXPECT_NEAR(expression.get_result(), 1e+07, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, exponential_expression_6) {
  s21::smartcalc expression("1e007", "0");

  EXPECT_NEAR(expression.get_result(), 1e+07, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, exponential_expression_7) {
  s21::smartcalc expression("1e+7", "0");

  EXPECT_NEAR(expression.get_result(), 1e+07, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, exponential_expression_8) {
  s21::smartcalc expression("1e-7", "0");

  EXPECT_NEAR(expression.get_result(), 1e-07, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, exponential_expression_9) {
  s21::smartcalc expression("cos(1E7)", "0");

  EXPECT_NEAR(expression.get_result(), cos(1e+07), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, exponential_expression_10) {
  s21::smartcalc expression("(1e-9 * 2)^2+1E11", "0");

  EXPECT_NEAR(expression.get_result(), pow((1e-9 * 2), 2) + 1e+11, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, exponential_expression_11) {
  s21::smartcalc expression("33e-4+1e-5*sin(157e-2)/7e-7+123e+4", "0");

  EXPECT_NEAR(expression.get_result(),
              33e-4 + 1e-5 * sin(157e-2) / 7e-7 + 123e+4, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

// ----------Test complex expressions---------------

TEST(smartcalc_test, complex_expression_with_exponentiations) {
  std::string exp = "-1^2", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), pow(1, 2) * -1, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_with_exponentiations_1) {
  std::string exp = "(-1)^2", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), pow(1, 2), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_with_exponentiations_2) {
  std::string exp = "x^x", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), pow(0, 0), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_1) {
  std::string exp = "-12-13^2*13-16+7", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), -12 - pow(13, 2) * 13 - 16 + 7, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_with_u_minus_sin) {
  std::string exp = "sin-1", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), sin(-1), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_with_u_minus_sin_1) {
  std::string exp = "-sin(x)", x = "-1";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), -sin(-1), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_with_exponentiations_3) {
  std::string exp = "2^2^3", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 256, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_with_exponentiations_4) {
  std::string exp = "1-2^2^3", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), -255, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_with_exponentiations_5) {
  std::string exp = "1+2^2^3*x/(x+21)", x = "2";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 1 + pow(2, pow(2, 3)) * 2 / (2 + 21),
              1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_with_exponentiations_6) {
  std::string exp = "(1+2)*4*cos(x*7-2)+sin(2*x)", x = "2";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(),
              (1 + 2) * 4 * cos(2 * 7 - 2) + sin(2 * 2), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_with_exponentiations_7) {
  std::string exp = "-sqrt(x^lg(5-x))+ln(55/(2+x))", x = "2";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 1.4412238480371777, 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_with_exponentiations_8) {
  std::string exp = "2^3^2", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 512, 1e-7);
}

TEST(smartcalc_test, complex_expression_with_exponentiations_9) {
  std::string exp = "+-+1", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_FALSE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_with_exponentiations_10) {
  std::string exp = "100.235+x-(x+10)", x = "100";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), 100.235 + 100 - (100 + 10), 1e-7);
  EXPECT_TRUE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_with_exponentiations_11) {
  std::string exp = "22+-+1", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_FALSE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_with_exponentiations_12) {
  std::string exp = "22*-+1", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_FALSE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_with_exponentiations_13) {
  std::string exp = "-(3)*(-x-(7*(-(-(-(--7))))))", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_FALSE(expression.get_status());
}

TEST(smartcalc_test, complex_expression_with_exponentiations_14) {
  std::string exp = "-2^-2", x = "0";
  s21::smartcalc expression(exp, x);

  EXPECT_NEAR(expression.get_result(), pow(2, -2) * (-1), 1e-7);
  EXPECT_TRUE(expression.get_status());
}
