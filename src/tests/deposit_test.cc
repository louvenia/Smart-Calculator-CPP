#include <gtest/gtest.h>

#include "../s21_SmartCalc_v2/model/s21_deposit_calculator.h"

TEST(deposit_test, deposit_calc_1_without_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 24,    8.0, 0.0, 2,     50000.0,
                                    4,        500.0, 1,   0.0, false, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 33748.80, 3);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_EQ(result.deposit_amount, 288000.00);
}

TEST(deposit_test, deposit_calc_1_with_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 24,    8.0, 0.0, 2,    50000.0,
                                    4,        500.0, 1,   0.0, true, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 36039.62, 2);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_NEAR(result.deposit_amount, 324039.62, 2);
}

TEST(deposit_test, deposit_calc_2_without_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 15,  7.0, 4.25, 2,     0.0,
                                    0,        0.0, 0,   0.0,  false, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 8740.38, 10);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_EQ(result.deposit_amount, 100000.00);
}

TEST(deposit_test, deposit_calc_2_with_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 15,  7.0, 4.25, 2,    0.0,
                                    0,        0.0, 0,   0.0,  true, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 9106.04, 11);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_NEAR(result.deposit_amount, 109106.04, 11);
}

TEST(deposit_test, deposit_calc_3_without_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 40,  7.0, 4.25, 3,     0.0,
                                    0,        0.0, 0,   0.0,  false, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 23301.38, 32);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_EQ(result.deposit_amount, 100000.00);
}

TEST(deposit_test, deposit_calc_3_with_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 40,  7.0, 4.25, 3,    0.0,
                                    0,        0.0, 0,   0.0,  true, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 25990.14, 40);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_NEAR(result.deposit_amount, 125990.14, 40);
}

TEST(deposit_test, deposit_calc_4_without_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 12,  7.0, 0.0, 0,     0.0,
                                    0,        0.0, 0,   0.0, false, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 7000.65, 2);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_EQ(result.deposit_amount, 100000.00);
}

TEST(deposit_test, deposit_calc_4_with_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 12,  7.0, 0.0, 0,    0.0,
                                    0,        0.0, 0,   0.0, true, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 7250.03, 2);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_NEAR(result.deposit_amount, 107250.03, 2);
}

TEST(deposit_test, deposit_calc_5_without_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 20,  7.0, 0.0, 0,     0.0,
                                    0,        0.0, 0,   0.0, false, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 11668.37, 9);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_EQ(result.deposit_amount, 100000.00);
}

TEST(deposit_test, deposit_calc_5_with_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 20,  7.0, 0.0, 0,    0.0,
                                    0,        0.0, 0,   0.0, true, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 12373.14, 8);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_NEAR(result.deposit_amount, 112373.14, 8);
}

TEST(deposit_test, deposit_calc_6_without_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 20,  7.0, 0.0, 1,     0.0,
                                    0,        0.0, 0,   0.0, false, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 11666.80, 2);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_EQ(result.deposit_amount, 100000.00);
}

TEST(deposit_test, deposit_calc_6_with_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 20,  7.0, 0.0, 1,    0.0,
                                    0,        0.0, 0,   0.0, true, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 12365.67, 2);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_NEAR(result.deposit_amount, 112365.67, 2);
}

TEST(deposit_test, deposit_calc_7_without_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {1000000.0, 12,  7.0, 0.0, 4,     0.0,
                                    0,         0.0, 0,   0.0, false, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 69999.48, 2);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_EQ(result.deposit_amount, 1000000.00);
}

TEST(deposit_test, deposit_calc_7_with_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {1000000.0, 12,  7.0, 0.0, 4,    0.0,
                                    0,         0.0, 0,   0.0, true, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 71224.38, 2);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_NEAR(result.deposit_amount, 1071224.38, 2);
}

TEST(deposit_test, deposit_calc_8_without_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {1000000.0, 12,  20.0, 0.0, 5,     0.0,
                                    0,         0.0, 0,    0.0, false, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 199998.50, 2);
  EXPECT_NEAR(result.tax_amount, 16249.81, 2);
  EXPECT_EQ(result.deposit_amount, 1000000.00);
}

TEST(deposit_test, deposit_calc_8_with_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {1000000.0, 12,  20.0, 0.0, 5,    0.0,
                                    0,         0.0, 0,    0.0, true, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 199998.50, 2);
  EXPECT_NEAR(result.tax_amount, 16249.81, 2);
  EXPECT_NEAR(result.deposit_amount, 1199998.50, 2);
}

TEST(deposit_test, deposit_calc_9_without_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 20,  7.0, 0.0, 4,     0.0,
                                    0,        0.0, 0,   0.0, false, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 11666.60, 2);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_EQ(result.deposit_amount, 100000.00);
}

TEST(deposit_test, deposit_calc_9_with_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 20,  7.0, 0.0, 4,    0.0,
                                    0,        0.0, 0,   0.0, true, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 12166.99, 3);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_NEAR(result.deposit_amount, 112166.99, 3);
}

TEST(deposit_test, deposit_calc_10_without_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 20,  7.0, 0.0, 5,     0.0,
                                    0,        0.0, 0,   0.0, false, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 11666.62, 2);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_EQ(result.deposit_amount, 100000.00);
}

TEST(deposit_test, deposit_calc_10_with_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 20,  7.0, 0.0, 5,    0.0,
                                    0,        0.0, 0,   0.0, true, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 11993.28, 104);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_NEAR(result.deposit_amount, 111993.28, 104);
}

TEST(deposit_test, deposit_calc_11_without_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 20,  7.0, 0.0, 6,     0.0,
                                    0,        0.0, 0,   0.0, false, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 11666.61, 2);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_EQ(result.deposit_amount, 100000.00);
}

TEST(deposit_test, deposit_calc_11_with_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 20,  7.0, 0.0, 6,    0.0,
                                    0,        0.0, 0,   0.0, true, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 11666.61, 2);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_NEAR(result.deposit_amount, 111666.61, 2);
}

TEST(deposit_test, deposit_calc_12_without_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 12,     7.0, 0.0, 2,     50000.0,
                                    0,        5000.0, 0,   0.0, false, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 9882.38, 6);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_EQ(result.deposit_amount, 145000.00);
}

TEST(deposit_test, deposit_calc_12_with_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 12,     7.0, 0.0, 2,    50000.0,
                                    1,        5000.0, 4,   0.0, true, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 26473.78, 94);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_NEAR(result.deposit_amount, 716473.78, 94);
}

TEST(deposit_test, deposit_calc_13_without_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 12,     7.0, 0.0, 2,     50000.0,
                                    2,        5000.0, 2,   0.0, false, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 16484.31, 35);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_EQ(result.deposit_amount, 370000.00);
}

TEST(deposit_test, deposit_calc_13_with_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 12,     7.0, 0.0, 2,    50000.0,
                                    3,        5000.0, 3,   0.0, true, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 14219.04, 20);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_NEAR(result.deposit_amount, 294219.04, 20);
}

TEST(deposit_test, deposit_calc_14_without_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 12,     7.0, 0.0, 2,     50000.0,
                                    5,        5000.0, 2,   0.0, false, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 9148.84, 10);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_EQ(result.deposit_amount, 120000.00);
}

TEST(deposit_test, deposit_calc_14_with_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 12,     7.0, 0.0, 2,    50000.0,
                                    3,        5000.0, 5,   0.0, true, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 14665.96, 22);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_NEAR(result.deposit_amount, 309665.96, 22);
}

TEST(deposit_test, deposit_calc_15_with_cap) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {100000.0, 1,      7.0, 0.0, 2,    50000.0,
                                    3,        5000.0, 3,   0.0, true, 0};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_NEAR(result.accrued_interest, 14219.04, 20);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_NEAR(result.deposit_amount, 294219.04, 20);
}

TEST(deposit_test, incorrect_value) {
  s21::deposit some_deposit;
  s21::data_deposit input_values = {-100000.0, 12,     7.0, 0.0, 2,    50000.0,
                                    3,         5000.0, 5,   0.0, true, 1};
  some_deposit.set_data_deposit(input_values);
  s21::result_deposit result = some_deposit.deposit_calc();

  EXPECT_EQ(result.accrued_interest, 0);
  EXPECT_EQ(result.tax_amount, 0);
  EXPECT_EQ(result.deposit_amount, 0);
}
