#ifndef SRC_MODEL_CREDIT_CALCULATOR_H
#define SRC_MODEL_CREDIT_CALCULATOR_H

#include <cmath>
#include <string>

namespace s21 {
struct result_credit {
  double monthly_payment;
  double monthly_payment1;
  double overpayment;
  double total_payment;
  bool status;
};

struct data_credit {
  double amount;
  int term;
  double interest_rate;
  int type_term;
  bool type_credit;
};
}  // namespace s21

namespace s21 {
class credit {
 public:
  credit() noexcept;
  void set_data_credit(const struct data_credit& input_values);
  struct result_credit credit_calculate();

 private:
  double amount, interest_rate;
  int term;
  bool type_credit, status;

  void annuity_calc();
  void differentiated_calc();

  result_credit result_values{};
};
}  // namespace s21
#endif  // SRC_MODEL_CREDIT_CALCULATOR_H
