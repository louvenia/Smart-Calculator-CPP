#include "s21_smartcalc.h"

namespace s21 {

smartcalc::smartcalc(std::string text, std::string text_x)
    : infix(), postfix(), result(), status(true) {
  text = check_text(text);
  if (!text_x.empty()) {
    text_x = check_text(text_x);
  }
  if (status) {
    for (char i : text) {
      infix += i;
    }
    add_x(text_x);
    main_calculation();
  }
  infix = {}, postfix = {};
}

bool smartcalc::get_status() const noexcept { return status; }

double smartcalc::get_result() const noexcept { return result; }

/**
 * @brief Функция проверяет входящие значения и заменяет лексему на
 * соответствующий символ
 *
 * @return std::string
 */
std::string smartcalc::check_text(std::string text) {
  if (status) {
    s21::check expression(text);
    status = expression.get_status();
    text = expression.get_expression();
  }
  return text;
}

/**
 * @brief Функция вставляет вместо найденного x число или выражение в выражении
 * @details Если x найденно, то производится вставка соответствующего выражения
 * x в выражение, иначе статус изменился на false(не найденно x в строке)
 */
void smartcalc::add_x(std::string text_x) {
  for (int i = 0; i < (int)infix.length(); ++i) {
    if (infix[i] == 'x' && !text_x.empty()) {
      infix.replace(i, 1, text_x);
    } else if (infix[i] == 'x' && text_x.empty()) {
      status = false;
    }
  }
}

/**
 * @brief Функция контролирует статус при преобразовании и расчете
 * @details Если статус изменился на false(ошибка при преобразовании в
 * постфиксную запись), то не производится дальнейший расчет
 */
void smartcalc::main_calculation() {
  if (status) {
    generate_postfix();
  }
  if (status) {
    calculation_postfix();
  }
}

/**
 * @brief Функция преобразует инфиксную запись в постфиксную
 */
void smartcalc::generate_postfix() {
  std::stack<char> operators;
  std::string functions = "cstCSTlLq";
  for (int i = 0; i < (int)infix.length() && status; ++i) {
    if (isdigit(infix[i])) {
      add_numbers_postfix(i);
    } else if (infix[i] == '(' ||
               functions.find(infix[i]) != std::string::npos) {
      operators.push(infix[i]);
    } else if (infix[i] == ')') {
      while (!operators.empty()) {
        if (operators.top() != '(') {
          postfix += operators.top();
          operators.pop();
        } else {
          operators.pop();
          break;
        }
      }
    } else if (get_o(infix[i])) {
      int priority_in = 0, priority_st = 0;
      char symbol_st = '\0';
      while (!operators.empty()) {
        symbol_st = operators.top();
        operators.pop();
        priority_in = get_priority(infix[i]);
        priority_st = get_priority(symbol_st);
        if ((symbol_st == '~' && infix[i] == '^') ||
            (symbol_st == '^' && infix[i] == '^') ||
            priority_st < priority_in) {
          operators.push(symbol_st);
          break;
        } else {
          postfix += symbol_st;
        }
      }
      operators.push(infix[i]);
    }
  }
  while (!operators.empty()) {
    postfix += operators.top();
    operators.pop();
  }
}

/**
 * @brief Функция расчитывает постфиксное выражение
 */
void smartcalc::calculation_postfix() {
  std::stack<double> numbers;
  std::string binary = "~+-*/%^", functions = "cCsStTlLq";
  double first_value = 0.0, second_value = 0.0, result_operations = 0.0;

  for (int i = 0; i < (int)postfix.length() && status; ++i) {
    if (isdigit(postfix[i])) {
      add_numbers_stack(i, numbers);
    } else if (binary.find(postfix[i]) != std::string::npos) {
      second_value = numbers.top();
      numbers.pop();
      if (postfix[i] != '~') {
        first_value = numbers.top();
        numbers.pop();
      } else {
        first_value = 0.0;
      }
      result_operations =
          binary_operation(first_value, second_value, postfix[i]);
      numbers.push(result_operations);
    } else if (functions.find(postfix[i]) != std::string::npos) {
      first_value = numbers.top();
      numbers.pop();
      result_operations = functions_operation(first_value, postfix[i]);
      numbers.push(result_operations);
    }
  }
  result = numbers.top();
}

/**
 * @brief Функция вставляет найденное число в постфиксное выражение
 * @details Вставляется не только число, но и идущие после точка и
 * экспоненциальное выражение до встречи какой-либо операции
 */
void smartcalc::add_numbers_postfix(int &i) {
  for (int prev_i = i; isdigit(infix[i]) || infix[i] == '.' ||
                       check_exponential(infix[i], infix[prev_i]);
       ++i) {
    postfix += infix[i];
    prev_i = i;
  }
  --i;
  postfix += ' ';
}

/**
 * @brief Функция определяет операцию из ряда определенных констант kpriority
 * @details Если операция найденна, то возвращается true, иначе false
 *
 * @return bool
 */
bool smartcalc::get_o(char symbol) const noexcept {
  bool status_get = false;
  for (auto it : kpriority_o) {
    if (symbol == it.first) {
      status_get = true;
    }
  }
  return status_get;
}

/**
 * @brief Функция определяет приоритет операции из ряда определенных констант
 * kpriority
 * @details Если операция найденна, то возвращается значение его приоритета,
 * иначе 0
 *
 * @return int
 */
int smartcalc::get_priority(char symbol) const noexcept {
  int priority = 0;
  for (auto it : kpriority_o) {
    if (symbol == it.first) {
      priority = it.second;
    }
  }
  return priority;
}

/**
 * @brief Функция вставляет в stack число, опеределенное из постфиксной записи
 * @details Вставляется не только число, но и идущие после точка и
 * экспоненциальное выражение до встречи какой-либо операции
 */
void smartcalc::add_numbers_stack(int &i, std::stack<double> &numbers) {
  std::string tmp;
  for (int prev_i = i; isdigit(postfix[i]) || postfix[i] == '.' ||
                       check_exponential(postfix[i], postfix[prev_i]);
       ++i) {
    tmp += postfix[i];
    prev_i = i;
  }
  double number = std::stod(tmp);
  numbers.push(number);
}

/**
 * @brief Функция проверяет текущий и предыдущий символ на экспоненциальную
 * запись
 * @details Если текущий символ eE или текущий символ +-, а предыдущий сивол eE,
 * то возвращается true, иначе false
 *
 * @return bool
 */
bool smartcalc::check_exponential(char symbol, char pre_symbol) const noexcept {
  std::string exponential = "eE";
  bool status_ce = false;
  if (exponential.find(symbol) != std::string::npos ||
      ((symbol == '+' || symbol == '-') &&
       exponential.find(pre_symbol) != std::string::npos)) {
    status_ce = true;
  }
  return status_ce;
}

/**
 * @brief Функция проводит расчет бинарных операций
 * @details Если соответствующему символу присуще ограничение на входящее
 * значение и оно удовлетворительно, то функция возвращает false
 *
 * @return double
 */
double smartcalc::binary_operation(double first_value, double second_value,
                                   char symbol) noexcept {
  double result = 0.0;
  if (symbol == '+') {
    result = first_value + second_value;
  } else if (symbol == '-' || symbol == '~') {
    result = first_value - second_value;
  } else if (symbol == '*') {
    result = first_value * second_value;
  } else if (symbol == '/') {
    if (second_value == 0) {
      status = false;
    } else {
      result = first_value / second_value;
    }
  } else if (symbol == '%') {
    if (second_value == 0) {
      status = false;
    } else {
      result = fmod(first_value, second_value);
    }
  } else if (symbol == '^') {
    result = pow(first_value, second_value);
  }
  return result;
}

/**
 * @brief Функция проводит расчет функций
 * @details Если соответствующей функции присуще ограничение на входящее
 * значение и оно удовлетворительно, то функция возвращает false
 *
 * @return double
 */
double smartcalc::functions_operation(double value, char symbol) noexcept {
  double result = 0.0;

  if (symbol == 'c') {
    result = cos(value);
  } else if (symbol == 's') {
    result = sin(value);
  } else if (symbol == 't') {
    result = tan(value);
  } else if (symbol == 'C') {
    if (value < -1 || value > 1) {
      status = false;
    } else {
      result = acos(value);
    }
  } else if (symbol == 'S') {
    if (value < -1 || value > 1) {
      status = false;
    } else {
      result = asin(value);
    }
  } else if (symbol == 'T') {
    result = atan(value);
  } else if (symbol == 'l') {
    if (value <= 0) {
      result = log(value);
      status = false;
    } else {
      result = log(value);
    }
  } else if (symbol == 'L') {
    if (value <= 0) {
      status = false;
    } else {
      result = log10(value);
    }
  } else if (symbol == 'q') {
    if (value < 0) {
      status = false;
    } else {
      result = sqrt(value);
    }
  }
  return result;
}
}  // namespace s21
