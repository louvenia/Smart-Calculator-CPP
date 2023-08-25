#ifndef SRC_MODEL_S21_GRAPHIC_H
#define SRC_MODEL_S21_GRAPHIC_H

#include <string>
#include <vector>

#include "s21_smartcalc.h"

namespace s21 {
struct result_graph {
  std::vector<double> X = {};
  std::vector<double> Y = {};
  bool status;
};

struct data_graph {
  std::string expression;
  double min_x;
  double max_x;
  double min_y;
  double max_y;
  std::size_t count;
};
}  // namespace s21

namespace s21 {
class graph {
 public:
  graph() noexcept;
  [[nodiscard]] struct result_graph get_result() const noexcept;
  void set_data_graph(const struct data_graph& input_values);

 private:
  std::string expression, message;
  double x_begin, x_end, y_begin, y_end;
  std::size_t count_d;
  bool status;

  void check_values();
  void range_function();

  result_graph output_values{};
};
}  // namespace s21

#endif  // SRC_MODEL_S21_GRAPHIC_H
