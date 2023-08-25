#ifndef SRC_MODEL_S21_deposit_CALCULATOR_H
#define SRC_MODEL_S21_deposit_CALCULATOR_H

#include <array>
#include <cmath>
#include <string>

namespace s21 {
struct result_deposit {
  double accrued_interest;
  double tax_amount;
  double deposit_amount;
  bool status;
};

struct data_deposit {
  double deposit_amount;
  int term;
  double interest_rate;
  double tax;
  int type_payments;
  double replenishment;
  int type_replenishment;
  double withdrawal;
  int type_withdrawal;
  double minimum_balance;
  bool capitalization;
  int type_term;
};
}  // namespace s21

namespace s21 {
class deposit {
 public:
  deposit() noexcept;
  const std::array<int, 12> kdays = {31, 28, 31, 30, 31, 30,
                                     31, 31, 30, 31, 30, 31};

  void set_data_deposit(const struct data_deposit &input_values);
  struct result_deposit deposit_calc();

 private:
  double deposit_amount, interest_rate, tax, replenishment, withdrawal,
      minimum_balance;
  int term, type_payments, type_replenishment, type_withdrawal;
  bool capitalization, status;

  void calculation_deposit(int period_type, double *accrued_interest,
                           double *tax_amount, double upper_value,
                           double lower_value, int tax_period);
  void calc_tax_amount(double *accrued_interest, double *tax_amount,
                       int tax_period, int *status_tax);
  void replenishment_op(int int_period);
  void withdrawal_op(int int_period);

  result_deposit result_values{};
};
}  // namespace s21
#endif  // SRC_MODEL_S21_deposit_CALCULATOR_H
