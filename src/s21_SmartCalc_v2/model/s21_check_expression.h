#ifndef SRC_MODEL_S21_CHECK_EXPRESSION_H_
#define SRC_MODEL_S21_CHECK_EXPRESSION_H_

#include <stack>
#include <string>

namespace s21 {
class check {
 public:
  explicit check(std::string text);
  [[nodiscard]] bool get_status() const noexcept;
  [[nodiscard]] size_t get_size() noexcept;
  [[nodiscard]] std::string get_expression() const noexcept;

 private:
  std::string expression;
  size_t length_exp;
  bool status;

  void set_size() noexcept;
  void checking();
  bool check_length_exp() const noexcept;
  bool contains_number() const noexcept;
  bool conversion_string();
  void change_string();
  int check_brackets() const noexcept;
  bool position_operators() noexcept;
  bool check_dot() const noexcept;
  bool check_n_o(char symbol) const noexcept;
  bool fun_expression(char symbol) const noexcept;
  bool priority_calculation(char operation) const noexcept;
  bool check_empty_brackets(char symbol) const noexcept;
  bool check_binary(char symbol) const noexcept;
  bool three_operators() const noexcept;
  bool check_open_o(char symbol) const noexcept;
  bool check_math_o(char symbol) const noexcept;
  bool false_binary(char symbol, char aft_symbol) const noexcept;
  bool empty_after_op(char symbol, char aft_symbol) const noexcept;
  bool binary_after_op(char symbol, char aft_symbol) const noexcept;
};
}  // namespace s21

#endif  // SRC_MODEL_S21_CHECK_EXPRESSION_H_