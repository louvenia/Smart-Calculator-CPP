#include <gtest/gtest.h>

#include "../s21_SmartCalc_v2/model/s21_check_expression.h"

TEST(check_test, empty_expression) {
  s21::check expression("");
  EXPECT_FALSE(expression.get_status());
}

TEST(check_test, simple_expression) {
  s21::check expression("1+2");
  EXPECT_EQ(expression.get_size(), 3);
  EXPECT_TRUE(expression.get_status());
}

// ----------Test function check_length_exp ---------------

TEST(check_test, check_length_less_255) {
  s21::check expression(
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1");
  EXPECT_EQ(expression.get_size(), 253);
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_length_equal_255) {
  s21::check expression(
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1");
  EXPECT_EQ(expression.get_size(), 255);
  EXPECT_FALSE(expression.get_status());
}

// ----------Test function conversion_string ---------------

TEST(check_test, check_ln_with_brackets) {
  s21::check expression("ln(1)");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_ln_without_brackets) {
  s21::check expression("ln1");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_lg_with_brackets) {
  s21::check expression("lg(1)");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_lg_without_brackets) {
  s21::check expression("lg1");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_cos_with_brackets) {
  s21::check expression("cos(0)");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_cos_without_brackets) {
  s21::check expression("cos0");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_sin_with_brackets) {
  s21::check expression("sin(90)");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_sin_without_brackets) {
  s21::check expression("sin90");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_tan_with_brackets) {
  s21::check expression("tan(0)");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_tan_without_brackets) {
  s21::check expression("tan0");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_mod) {
  s21::check expression("5mod2");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_acos_with_brackets) {
  s21::check expression("acos(1)");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_acos_without_brackets) {
  s21::check expression("acos1");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_asin_with_brackets) {
  s21::check expression("asin(0)");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_asin_without_brackets) {
  s21::check expression("asin0");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_atan_with_brackets) {
  s21::check expression("atan(0)");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_atan_without_brackets) {
  s21::check expression("atan0");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_sqrt_with_brackets) {
  s21::check expression("16sqrt(2)");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_sqrt_without_brackets) {
  s21::check expression("16sqrt2");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_spaces) {
  s21::check expression("       16     *        2  ");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_wrong_expression) {
  s21::check expression("abcdefg");
  EXPECT_FALSE(expression.get_status());
}

TEST(check_test, check_wrong_expression_1) {
  s21::check expression("aco2");
  EXPECT_FALSE(expression.get_status());
}

TEST(check_test, check_wrong_expression_2) {
  s21::check expression("ln(bla)");
  EXPECT_FALSE(expression.get_status());
}

// ----------Test function change_string ---------------

TEST(check_test, change_string_exp_brackets) {
  s21::check expression("5.(1+2)");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, change_string_exp_x) {
  s21::check expression("5x");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, change_string_close_bracket) {
  s21::check expression("(1+2)sqrt2");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, change_string_close_bracket_1) {
  s21::check expression("(1+2)5");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, change_string_minus) {
  s21::check expression("5--2");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, change_string_u_minus) {
  s21::check expression("-5-2");
  EXPECT_EQ(expression.get_expression(), "~5-2");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, change_string_u_plus) {
  s21::check expression("+5-2");
  EXPECT_EQ(expression.get_expression(), "5-2");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, change_string_u_minus_with_brackets) {
  s21::check expression("5*(-5-2)");
  EXPECT_EQ(expression.get_expression(), "5*(~5-2)");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, change_string_u_plus_with_brackets) {
  s21::check expression("5*(+5-2)");
  EXPECT_EQ(expression.get_expression(), "5*(5-2)");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, change_string_u_minus_with_function) {
  s21::check expression("5*cos-5-2");
  EXPECT_EQ(expression.get_expression(), "5*c~5-2");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, change_string_u_plus_with_function) {
  s21::check expression("5*cos+5-2");
  EXPECT_EQ(expression.get_expression(), "5*c5-2");
  EXPECT_TRUE(expression.get_status());
}

// ----------Test function check_brackets---------------

TEST(check_test, empty_brackets) {
  s21::check expression("5*sin()");
  EXPECT_FALSE(expression.get_status());
}

TEST(check_test, not_empty_brackets) {
  s21::check expression("sin(1+2)");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, left_brackets_great_not_empty) {
  s21::check expression("(((((1+2))))");
  EXPECT_FALSE(expression.get_status());
}

TEST(check_test, left_brackets_less_not_empty) {
  s21::check expression("(((1+2))))");
  EXPECT_FALSE(expression.get_status());
}

// ----------Test function position_operators---------------

TEST(check_test, first_arg_binary) {
  s21::check expression("*5-2");
  EXPECT_FALSE(expression.get_status());
}

TEST(check_test, end_arg_binary) {
  s21::check expression("5-2*");
  EXPECT_FALSE(expression.get_status());
}

TEST(check_test, three_operators) {
  s21::check expression("5/**2");
  EXPECT_FALSE(expression.get_status());
}

TEST(check_test, operation_before_bracket) {
  s21::check expression("(1+)");
  EXPECT_FALSE(expression.get_status());
}

TEST(check_test, false_binary) {
  s21::check expression("(5**2)");
  EXPECT_FALSE(expression.get_status());
}

TEST(check_test, false_binary_u_minus) {
  s21::check expression("(5*-2)");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, number_aft_op) {
  s21::check expression("5sin");
  EXPECT_FALSE(expression.get_status());
}

TEST(check_test, binary_after_function) {
  s21::check expression("sin(*2)");
  EXPECT_FALSE(expression.get_status());
}

// ----------Test function check_dot---------------

TEST(check_test, check_expression_with_dot) {
  s21::check expression("1.2+2.1");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, check_expression_with_many_dot) {
  s21::check expression("1.......2+2.1");
  EXPECT_FALSE(expression.get_status());
}

TEST(check_test, check_expression_with_only_dot) {
  s21::check expression("(2).(3)");
  EXPECT_FALSE(expression.get_status());
}

// ----------Test exponential expression---------------

TEST(check_test, exponential_expression_1) {
  s21::check expression("1E7");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, exponential_expression_2) {
  s21::check expression("1E007");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, exponential_expression_3) {
  s21::check expression("1E+7");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, exponential_expression_4) {
  s21::check expression("1E-7");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, exponential_expression_5) {
  s21::check expression("1e7");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, exponential_expression_6) {
  s21::check expression("1e007");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, exponential_expression_7) {
  s21::check expression("1e+7");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, exponential_expression_8) {
  s21::check expression("1e-7");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, exponential_expression_9) {
  s21::check expression("2.6E3");
  EXPECT_TRUE(expression.get_status());
}

// ----------Test some expression---------------

TEST(check_test, expression_1) {
  s21::check expression("2^cos1");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, expression_2) {
  s21::check expression("abcdef");
  EXPECT_FALSE(expression.get_status());
}

TEST(check_test, expression_3) {
  s21::check expression("100-sin(1)*(lg(100)/5)-ln(8.2)+1");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, expression_4) {
  s21::check expression(
      "(((sin(1)+cos(0)+tan(0)+ln(2.5))   * lg1000)/(asin1 + acos0 + "
      "atan0))^2");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, expression_5) {
  s21::check expression("(cos0^sin1)*tan0");
  EXPECT_TRUE(expression.get_status());
}

TEST(check_test, expression_6) {
  s21::check expression("(((100+333)/4)-(10mod3))--4");
  EXPECT_TRUE(expression.get_status());
}
