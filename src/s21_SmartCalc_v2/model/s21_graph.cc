#include "s21_graph.h"

namespace s21 {
graph::graph() noexcept
    : expression(),
      message(),
      x_begin(),
      x_end(),
      y_begin(),
      y_end(),
      count_d(),
      status(true) {}

struct result_graph graph::get_result() const noexcept {
  return output_values;
}

/**
 * @brief Функция устанавливает входящие значения
 * @details Если статус изменился на false(ошибка при проверке), то расчет не
 * проводится
 */
void graph::set_data_graph(const struct data_graph& input_values) {
  expression = input_values.expression;
  x_begin = input_values.min_x;
  x_end = input_values.max_x;
  y_begin = input_values.min_y;
  y_end = input_values.max_y;
  count_d = input_values.count;

  check_values();
  if (status) {
    range_function();
  }
}

/**
 * @brief Функция проверяет входящие значения
 */
void graph::check_values() {
  s21::check exp(expression);
  status = exp.get_status();
  if (x_begin < -1000000 || x_end > 1000000 || x_begin >= x_end) {
    status = false;
  } else if (y_begin < -1000000 || y_end > 1000000 || y_begin >= y_end) {
    status = false;
  }
  output_values.status = status;
}

/**
 * @brief Функция расчитывает область значений (множество значений переменной y)
 */
void graph::range_function() {
  double x = x_begin;
  double y = 0.0;
  double step = (x_end - x_begin) / count_d;

  for (std::size_t i = 0; i <= count_d && status; ++i) {
    std::string string_x = std::to_string(x);
    s21::smartcalc exp(expression, string_x);
    y = exp.get_result();
    if (exp.get_status()) {
      output_values.X.push_back(x);
      output_values.Y.push_back(y);
    }
    x += step;
  }
}
}  // namespace s21
