#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include "../model/s21_credit_calculator.h"
#include "../model/s21_deposit_calculator.h"
#include "../model/s21_graph.h"
#include "../model/s21_smartcalc.h"

namespace s21 {
class controller {
 public:
  static std::pair<std::string, bool> calculate(const std::string& expression,
                                                const std::string& x);
  static result_graph graph_calculate(const struct data_graph& input_values);
  static result_credit credit_calculate(const struct data_credit& input_values);
  static result_deposit deposit_calculate(
      const struct data_deposit& input_values);
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H
