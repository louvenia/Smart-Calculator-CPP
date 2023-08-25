#include "controller.h"

namespace s21 {
std::pair<std::string, bool> controller::calculate(
    const std::string& expression, const std::string& x) {
  s21::smartcalc exp(expression, x);
  std::string result = std::to_string(exp.get_result());
  std::pair<std::string, bool> result_status = {result, exp.get_status()};
  return result_status;
}

result_graph controller::graph_calculate(
    const struct data_graph& input_values) {
  s21::graph some_expression;
  some_expression.set_data_graph(input_values);
  result_graph result = {};
  result = some_expression.get_result();
  return result;
}

result_credit controller::credit_calculate(
    const struct data_credit& input_values) {
  s21::credit some_credit;
  some_credit.set_data_credit(input_values);
  result_credit result = {};
  result = some_credit.credit_calculate();
  return result;
}

result_deposit controller::deposit_calculate(
    const struct data_deposit& input_values) {
  s21::deposit some_deposit;
  some_deposit.set_data_deposit(input_values);
  result_deposit result = {};
  result = some_deposit.deposit_calc();
  return result;
}
}  // namespace s21
