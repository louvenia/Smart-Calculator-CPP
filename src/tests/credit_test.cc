#include <gtest/gtest.h>

#include "../s21_SmartCalc_v2/model/s21_credit_calculator.h"

// ------------------Test function annuity_calc---------------------------

TEST(credit_test, annuity_credit_1) {
  s21::credit some_credit;
  s21::data_credit input_values = {10000.0, 12, 7.0, 1, true};
  some_credit.set_data_credit(input_values);
  s21::result_credit result = some_credit.credit_calculate();

  EXPECT_NEAR(result.monthly_payment, 865.27, 2);
  EXPECT_NEAR(result.overpayment, 383.24, 2);
  EXPECT_NEAR(result.total_payment, 10383.24, 2);
}

TEST(credit_test, annuity_credit_2) {
  s21::credit some_credit;
  s21::data_credit input_values = {150000.0, 15, 9.0, 1, true};
  some_credit.set_data_credit(input_values);
  s21::result_credit result = some_credit.credit_calculate();

  EXPECT_NEAR(result.monthly_payment, 10610.46, 2);
  EXPECT_NEAR(result.overpayment, 9156.90, 2);
  EXPECT_NEAR(result.total_payment, 159156.90, 2);
}

TEST(credit_test, annuity_credit_3) {
  s21::credit some_credit;
  s21::data_credit input_values = {1500000.0, 18, 6.0, 1, true};
  some_credit.set_data_credit(input_values);
  s21::result_credit result = some_credit.credit_calculate();

  EXPECT_NEAR(result.monthly_payment, 87347.60, 2);
  EXPECT_NEAR(result.overpayment, 72256.80, 2);
  EXPECT_NEAR(result.total_payment, 1572256.80, 2);
}

TEST(credit_test, annuity_credit_4) {
  s21::credit some_credit;
  s21::data_credit input_values = {10000.0, 1, 7.0, 0, true};
  some_credit.set_data_credit(input_values);
  s21::result_credit result = some_credit.credit_calculate();

  EXPECT_NEAR(result.monthly_payment, 865.27, 2);
  EXPECT_NEAR(result.overpayment, 383.24, 2);
  EXPECT_NEAR(result.total_payment, 10383.24, 2);
}

TEST(credit_test, annuity_credit_5) {
  s21::credit some_credit;
  s21::data_credit input_values = {1000000000.0, 10, 10.0, 0, true};
  some_credit.set_data_credit(input_values);
  s21::result_credit result = some_credit.credit_calculate();

  EXPECT_NEAR(result.monthly_payment, 13215073.69, 2);
  EXPECT_NEAR(result.overpayment, 585808842.80, 2);
  EXPECT_NEAR(result.total_payment, 1585808842.80, 2);
}

TEST(credit_test, annuity_credit_6) {
  s21::credit some_credit;
  s21::data_credit input_values = {1000000000000.0, 50, 50.0, 0, true};
  some_credit.set_data_credit(input_values);
  s21::result_credit result = some_credit.credit_calculate();

  EXPECT_NEAR(result.monthly_payment, 41666666667.63, 2);
  EXPECT_NEAR(result.overpayment, 24000000000578.00, 2);
  EXPECT_NEAR(result.total_payment, 25000000000578.00, 2);
}

TEST(credit_test, annuity_credit_7) {
  s21::credit some_credit;
  s21::data_credit input_values = {-1000.0, 50, 50.0, 0, true};
  some_credit.set_data_credit(input_values);
  s21::result_credit result = some_credit.credit_calculate();

  EXPECT_EQ(result.monthly_payment, 0);
  EXPECT_EQ(result.overpayment, 0);
  EXPECT_EQ(result.total_payment, 0);
}

// ------------------Test function differentiated_calc--------------------

TEST(credit_test, differentiated_credit_1) {
  s21::credit some_credit;
  s21::data_credit input_values = {10000.0, 12, 7.0, 1, false};
  some_credit.set_data_credit(input_values);
  s21::result_credit result = some_credit.credit_calculate();

  EXPECT_NEAR(result.monthly_payment, 891.67, 2);
  EXPECT_NEAR(result.monthly_payment1, 838.19, 2);
  EXPECT_NEAR(result.overpayment, 379.17, 2);
  EXPECT_NEAR(result.total_payment, 10379.17, 2);
}

TEST(credit_test, differentiated_credit_2) {
  s21::credit some_credit;
  s21::data_credit input_values = {150000.0, 15, 9.0, 1, false};
  some_credit.set_data_credit(input_values);
  s21::result_credit result = some_credit.credit_calculate();

  EXPECT_NEAR(result.monthly_payment, 11125.00, 2);
  EXPECT_NEAR(result.monthly_payment1, 10075.00, 2);
  EXPECT_NEAR(result.overpayment, 9000.00, 2);
  EXPECT_NEAR(result.total_payment, 159000.00, 2);
}

TEST(credit_test, differentiated_credit_3) {
  s21::credit some_credit;
  s21::data_credit input_values = {1500000.0, 18, 6.0, 1, false};
  some_credit.set_data_credit(input_values);
  s21::result_credit result = some_credit.credit_calculate();

  EXPECT_NEAR(result.monthly_payment, 90833.33, 2);
  EXPECT_NEAR(result.monthly_payment1, 83750.00, 2);
  EXPECT_NEAR(result.overpayment, 71250.00, 2);
  EXPECT_NEAR(result.total_payment, 1571250.00, 2);
}

TEST(credit_test, differentiated_credit_4) {
  s21::credit some_credit;
  s21::data_credit input_values = {10000.0, 1, 7.0, 0, false};
  some_credit.set_data_credit(input_values);
  s21::result_credit result = some_credit.credit_calculate();

  EXPECT_NEAR(result.monthly_payment, 891.67, 2);
  EXPECT_NEAR(result.monthly_payment1, 838.19, 2);
  EXPECT_NEAR(result.overpayment, 379.17, 2);
  EXPECT_NEAR(result.total_payment, 10379.17, 2);
}

TEST(credit_test, differentiated_credit_5) {
  s21::credit some_credit;
  s21::data_credit input_values = {12345678910.0, 50, 999.0, 0, false};
  some_credit.set_data_credit(input_values);
  s21::result_credit result = some_credit.credit_calculate();

  EXPECT_NEAR(result.monthly_payment, 10298353824.09, 2);
  EXPECT_NEAR(result.monthly_payment1, 37705761.00, 2);
  EXPECT_NEAR(result.overpayment, 3088472196618.79, 2);
  EXPECT_NEAR(result.total_payment, 3100817875528.79, 2);
}

TEST(credit_test, differentiated_credit_6) {
  s21::credit some_credit;
  s21::data_credit input_values = {10000000000000.0, 50, 999.0, 0, false};
  some_credit.set_data_credit(input_values);
  s21::result_credit result = some_credit.credit_calculate();

  EXPECT_NEAR(result.monthly_payment, 8341666666666.67, 2);
  EXPECT_NEAR(result.monthly_payment1, 30541666666.67, 2);
  EXPECT_NEAR(result.overpayment, 2501662500000000.00, 2);
  EXPECT_NEAR(result.total_payment, 2511662500000000.00, 2);
}

TEST(credit_test, differentiated_credit_7) {
  s21::credit some_credit;
  s21::data_credit input_values = {10000000000000.0, -50, -999.0, 0, false};
  some_credit.set_data_credit(input_values);
  s21::result_credit result = some_credit.credit_calculate();

  EXPECT_EQ(result.monthly_payment, 0);
  EXPECT_EQ(result.monthly_payment1, 0);
  EXPECT_EQ(result.overpayment, 0);
  EXPECT_EQ(result.total_payment, 0);
}
