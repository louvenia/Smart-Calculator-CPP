#ifndef SRC_MODEL_S21_SMARTCALC_H_
#define SRC_MODEL_S21_SMARTCALC_H_

#include <cmath>
#include <map>

#include "s21_check_expression.h"

namespace s21 {
class smartcalc {
 public:
  smartcalc(std::string text, std::string text_x);
  [[nodiscard]] bool get_status() const noexcept;
  [[nodiscard]] double get_result() const noexcept;

 private:
  std::string infix;
  std::string postfix;
  double result;
  bool status;
  std::map<char, int> kpriority_o = {
      {'(', 0}, {')', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2},
      {'%', 2}, {'^', 3}, {'c', 3}, {'s', 3}, {'t', 3}, {'C', 3},
      {'S', 3}, {'T', 3}, {'l', 3}, {'L', 3}, {'q', 3}, {'~', 4}};

  std::string check_text(std::string text);
  void add_x(std::string text_x);
  void main_calculation();
  void generate_postfix();
  void calculation_postfix();
  void add_numbers_postfix(int &i);
  [[nodiscard]] bool get_o(char symbol) const noexcept;
  [[nodiscard]] int get_priority(char symbol) const noexcept;
  void add_numbers_stack(int &i, std::stack<double> &numbers);
  bool check_exponential(char sumbol, char pre_symbol) const noexcept;
  double binary_operation(double first_value, double second_value,
                          char symbol) noexcept;
  double functions_operation(double value, char symbol) noexcept;
};
}  // namespace s21

#endif  // SRC_MODEL_S21_SMARTCALC_H_
