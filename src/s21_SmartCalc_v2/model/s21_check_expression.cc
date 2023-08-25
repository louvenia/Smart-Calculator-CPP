#include "s21_check_expression.h"

namespace s21 {
check::check(std::string text)
    : expression(std::move(text)), length_exp(expression.size()), status(true) {
  if (!expression.empty()) {
    checking();
  } else {
    status = false;
  }
}

void check::set_size() noexcept { length_exp = expression.size(); }

size_t check::get_size() noexcept {
  set_size();
  return length_exp;
}

std::string check::get_expression() const noexcept { return expression; }

bool check::get_status() const noexcept { return status; }

/**
 * @brief Функция контролирует статус при проверках
 * @details Если статус изменился на false(ошибка при проверке), то не проходят
 * следующие проверки
 *
 * @return bool
 */
void check::checking() {
  if (status) {
    status = check_length_exp();
  }
  if (status) {
    status = contains_number();
  }
  if (status) {
    status = conversion_string();
  }
  if (status) {
    change_string();
    status = check_brackets();
  }
  if (status) {
    status = position_operators();
  }
  if (status) {
    status = check_dot();
  }
}

/**
 * @brief Функция определяет согласованность длины введенной строки с условием
 * (до 255 символов)
 * @details Функция возвращает true, когда длина строки удовлетворяет условию,
 * иначе false
 *
 * @return bool
 */
bool check::check_length_exp() const noexcept {
  bool status_le = true;
  if (length_exp >= 255) {
    status_le = false;
  }
  return status_le;
}

/**
 * @brief Функция определяет содержание чисел в выражении
 * @details Функция возвращает true, когда выражение содержит числа, иначе false
 *
 * @return bool
 */
bool check::contains_number() const noexcept {
  bool status_cn = false;
  int count_number = 0;
  for (auto it_exp = expression.begin(); it_exp != expression.end(); ++it_exp) {
    if (isdigit(*it_exp) || *it_exp == 'x') {
      count_number += 1;
    }
    if (count_number != 0) {
      status_cn = true;
    }
  }
  return status_cn;
}

/**
 * @brief Функция проверяет и конвертирует введенное выражение в выражение,
 * которое применяется в дальнейших операция
 * @details Переписываются значения чисел, математических операций, ln(l),
 * lg(L), cos(c), sin(s), tan(t), mod(%), acos(C), asin(S), atan(T), sqrt(q) и
 * возвращается true, если символы не удовлетворяют критерям, то возвращается
 * false
 *
 * @return bool
 */
bool check::conversion_string() {
  bool status_conversion = true;
  int flag = 0;
  std::string new_string;
  for (auto it_exp = expression.begin(), it_ns = new_string.begin();
       it_exp != expression.end() && flag != 2; ++it_exp, ++it_ns) {
    flag = 0;
    auto it_aft = it_exp;
    ++it_aft;
    if (check_n_o(*it_exp) && status) {
      new_string.push_back(*it_exp);
    } else if (*it_exp == 'l' && *it_aft == 'n' && flag != 1) {
      new_string.push_back('l');
      ++it_exp;
    } else if (*it_exp == 'l' && *it_aft == 'g' && flag != 1) {
      new_string.push_back('L');
      ++it_exp;
    } else if (*it_exp == 'c' && *it_aft == 'o' && *(++it_aft) == 's' &&
               flag != 1) {
      new_string.push_back('c');
      it_exp += 2;
    } else if (*it_exp == 's' && *it_aft == 'i' && *(++it_aft) == 'n' &&
               flag != 1) {
      new_string.push_back('s');
      it_exp += 2;
    } else if (*it_exp == 't' && *it_aft == 'a' && *(++it_aft) == 'n' &&
               flag != 1) {
      new_string.push_back('t');
      it_exp += 2;
    } else if (*it_exp == 'm' && *(++it_exp) == 'o' && *(++it_exp) == 'd' &&
               flag != 1) {
      new_string.push_back('%');
    } else if (*it_exp == 'a' && *it_aft == 'c' && *(++it_aft) == 'o' &&
               *(++it_aft) == 's' && flag != 1) {
      new_string.push_back('C');
      it_exp += 3;
    } else if (*it_exp == 'a' && *it_aft == 's' && *(++it_aft) == 'i' &&
               *(++it_aft) == 'n' && flag != 1) {
      new_string.push_back('S');
      it_exp += 3;
    } else if (*it_exp == 'a' && *it_aft == 't' && *(++it_aft) == 'a' &&
               *(++it_aft) == 'n' && flag != 1) {
      new_string.push_back('T');
      it_exp += 3;
    } else if (*it_exp == 's' && *it_aft == 'q' && *(++it_aft) == 'r' &&
               *(++it_aft) == 't' && flag != 1) {
      new_string.push_back('q');
      it_exp += 3;
    } else if (*it_exp == ' ' && flag != 1) {
      --it_ns;
      flag = 1;
    } else if (flag != 1) {
      status_conversion = false;
      flag = 2;
    }
  }
  expression = new_string;
  return status_conversion;
}

/**
 * @brief Функция изменяет (адаптирует) выражение, для дальнейших проверок и
 * расчетов
 * @details Если символ является числом, точкой, x, а следующий символ это
 * выражение с открывающейся скобки, функция или х, то между числом (х) и
 * выражением ставиться умножение (*), если в начале выражения стоит унарный
 * минус или плюс, то минус заменяется на ~, а плюс убирается, если после
 * функциии(выражения) или бинарного оператора стоит унарный минус или плюс, то
 * происходит идентичная замена, если подрят идут два минуса, то они заменяются
 * на плюс
 */
void check::change_string() {
  std::string new_string;
  std::string dot_x_rbracket = ".x)";
  auto it_begin = expression.begin();
  for (auto it_exp = expression.begin(), it_ns = new_string.begin();
       it_exp != expression.end(); ++it_exp, ++it_ns) {
    auto it_aft = it_exp;
    ++it_aft;
    if (((isdigit(*it_exp) ||
          (dot_x_rbracket.find(*it_exp) != std::string::npos)) &&
         fun_expression(*it_aft)) ||
        ((dot_x_rbracket.find(*it_exp) != std::string::npos &&
          *it_exp != '.') &&
         isdigit(*it_aft))) {
      new_string.push_back(*it_exp);
      new_string.push_back('*');
      new_string.push_back(*(++it_exp));
    } else if (it_exp == it_begin && (*it_exp == '-' || *it_exp == '+')) {
      if (*it_exp == '-') {
        new_string.push_back('~');
      } else if (*it_exp == '+') {
        new_string.push_back(*(++it_exp));
      }
    } else if ((check_open_o(*it_exp) ||
                (check_binary(*it_exp) && *it_exp != '-')) &&
               (*it_aft == '-' || *it_aft == '+')) {
      new_string.push_back(*it_exp);
      ++it_exp;
      if (*it_exp == '-') {
        new_string.push_back('~');
      } else if (*it_exp == '+') {
        new_string.push_back(*(++it_exp));
      }
    } else if (*it_exp == '-' && *it_aft == '-') {
      new_string.push_back('+');
      ++it_exp;
    } else {
      new_string.push_back(*it_exp);
    }
  }
  expression = new_string;
}

/**
 * @brief Функция определяет состояние скобок
 * @details Функция возвращает true, когда выражение не пустое и количество
 * скобок скомпенсированно, если выражение пустое или количество открывающей
 * скобки не компенсируется количеством закрывающей скобки, то возвращается
 * false
 * @return bool
 */
int check::check_brackets() const noexcept {
  int bracket_count = 0, flag = 0;
  for (auto it_exp = expression.begin();
       it_exp != expression.end() && flag == 0; ++it_exp) {
    if (*it_exp == '(') {
      bracket_count += 1;
      auto it_aft = it_exp;
      ++it_aft;
      if (it_aft != expression.end()) {
        if (check_empty_brackets(*it_aft) && flag == 0) {
          bracket_count = 10;
          flag = 1;
        }
      }
    } else if (*it_exp == ')') {
      bracket_count -= 1;
    }
    if (bracket_count < 0 && flag == 0) {
      flag = 1;
    }
  }
  return !bracket_count;
}

/**
 * @brief Функция определяет позицию операторов
 * @details Возвращает false, когда оператор находится в начале выражения (и это
 * не унарный минус), оператор находится в конце выражения, в выражении
 * присутствуют три оператора подряд, после функций, открывающей скобки и
 * возведения в степень находится математический оператор (и это не унарный
 * минус), перед закрывающей скобкой находится математический оператор,
 * псевдобинарный оператор, после функций пустота или бинарный оператор
 * @return bool
 */
bool check::position_operators() noexcept {
  bool status_binary = true;
  auto it_exp = expression.begin();
  if (check_binary(*it_exp)) {
    status_binary = false;
  }
  set_size();
  if (length_exp > 0) {
    auto it_end = expression.end();
    --it_end;
    if (check_binary(*it_end)) {
      status_binary = false;
    }
  }
  if (three_operators()) {
    status_binary = false;
  }
  for (it_exp = expression.begin();
       it_exp != expression.end() && status_binary != false; ++it_exp) {
    auto it_end = it_exp;
    if (++it_end != expression.end()) {
      if (check_open_o(*it_exp) && check_binary(*it_end)) {
        status_binary = false;
      }
    }
    auto it_pre = it_exp;
    if (it_exp != expression.begin()) {
      if (check_binary(*(--it_pre)) && *it_exp == ')') {
        status_binary = false;
      }
    }
    auto it_aft = it_exp;
    if (false_binary(*it_exp, *(++it_aft))) {
      status_binary = false;
    }
    if (empty_after_op(*it_exp, *it_aft)) {
      status_binary = false;
    }
    if (binary_after_op(*it_exp, *it_aft)) {
      status_binary = false;
    }
  }
  return status_binary;
}

/**
 * @brief Функция определяет корректное расположение точки
 * @details Возвращается false, когда повторяется комбинация точка и число без
 * мат.операций, точек больше, чем 1, и точка без числа
 * @return bool
 */
bool check::check_dot() const noexcept {
  bool status_dot = true;
  int flag_dot = 0, dot = 0;
  for (auto it_exp = expression.begin();
       it_exp != expression.end() && status_dot != false; ++it_exp) {
    if (flag_dot == 1 && dot == 1 && *it_exp == '.') {
      status_dot = false;
    }
    if (isdigit(*it_exp)) {
      flag_dot = 1;
    }
    if (*it_exp == '.' && flag_dot == 1) {
      dot += 1;
    }
    if (*it_exp == '.' && flag_dot != 1) {
      status_dot = false;
    }
    if (dot > 1) {
      status_dot = false;
    }
    if (!isdigit(*it_exp) && *it_exp != '.') {
      flag_dot = 0;
      dot = 0;
    }
  }
  return status_dot;
}

/**
 * @brief Функция определяет является ли символ числом или математической
 * операцией
 * @details Если символ является числом или операцией, то возвращается true,
 * если нет, то false
 *
 * @return bool
 */
bool check::check_n_o(char symbol) const noexcept {
  bool status_n_o = false;
  std::string numbers_operations = ".+-*/()x^eE3";
  if (isdigit(symbol) ||
      (numbers_operations.find(symbol) != std::string::npos)) {
    status_n_o = true;
  }
  return status_n_o;
}

/**
 * @brief Функция определяет функции, левую скобку (выражения в скобках) и x
 * @details Если символ является функцией, скобкой или x, то возвращается true,
 * если нет, то false Функция find() возвращает позицию символа в строке, если
 * символ не найден то возвращается std::string::npos
 * @return bool
 */
bool check::fun_expression(char symbol) const noexcept {
  bool status_fe = false;
  std::string bracket_x = "(x";
  if (priority_calculation(symbol) ||
      (bracket_x.find(symbol) != std::string::npos)) {
    status_fe = true;
  }
  return status_fe;
}

/**
 * @brief Функция определяет является ли символ функцией
 * @details Если символ является cos(acos), sin(asin), tan(atan), ln, lg и sqrt,
 * то возвращается true, если нет, то false Функция find() возвращает позицию
 * символа в строке, если символ не найден то возвращается std::string::npos
 * @return bool
 */
bool check::priority_calculation(char symbol) const noexcept {
  int status_pc = false;
  std::string functions = "cCsStTlLq";
  if (functions.find(symbol) != std::string::npos) {
    status_pc = true;
  }
  return status_pc;
}

/**
 * @brief Функция определяет являются ли скобки пустыми
 * @details Функция возвращает true, когда после левой скобки находится
 * закрывающая скобка, иначе false
 *
 * @return bool
 */
bool check::check_empty_brackets(char symbol) const noexcept {
  bool status_eb = false;
  if (symbol == ')') {
    status_eb = true;
  }
  return status_eb;
}

/**
 * @brief Функция определяет наличие бинарных операторов
 * @details Функция возвращает true, когда определено наличие бинарного
 * оператора, иначе false
 *
 * @return bool
 */
bool check::check_binary(char symbol) const noexcept {
  int status_binary = false;
  std::string binary = "+-*/%^";
  if (binary.find(symbol) != std::string::npos) {
    status_binary = true;
  }
  return status_binary;
}

/**
 * @brief Функция определяет три оператора, расположенных подряд
 * @details Возвращается true, если счетчик операторов будет равен 3, иначе
 * false
 *
 * @return bool
 */
bool check::three_operators() const noexcept {
  bool status_triple = false;
  int operators_counter = 0;
  for (auto it_exp = expression.begin();
       it_exp != expression.end() && status_triple != true; ++it_exp) {
    if (check_binary(*it_exp)) {
      operators_counter += 1;
    } else {
      operators_counter = 0;
    }
    if (operators_counter == 3) {
      status_triple = true;
    }
  }
  return status_triple;
}

/**
 * @brief Функция определяет открывающую операцию, как открывающая скобка,
 * функции или возведение в степень
 * @details Возвращается true, если символ соответствует условию, иначе false
 *
 * @return bool
 */
bool check::check_open_o(char symbol) const noexcept {
  bool status_open = false;
  if (check_math_o(symbol) || symbol == '(') {
    status_open = true;
  }
  return status_open;
}

/**
 * @brief Функция определяет является ли символ функцией или возведением в
 * степень
 * @details Возвращается true, если символ соответствует условию, иначе false
 *
 * @return bool
 */
bool check::check_math_o(char symbol) const noexcept {
  bool status_mo = false;
  if (priority_calculation(symbol) || symbol == '^') {
    status_mo = true;
  }
  return status_mo;
}

/**
 * @brief Функция определяет наличие подряд идущих бинарных операторов
 * @details Если последющий символ является ~, то это - от унарного минуса,
 * возвращается false, так как это не является ошибкой, но если расположены
 * подряд бинарные операторы, то возвращается true
 * @return bool
 */
bool check::false_binary(char symbol, char aft_symbol) const noexcept {
  bool status_in_binary = false;
  if ((symbol == '~' && check_binary(aft_symbol)) ||
      (check_binary(symbol) && check_binary(aft_symbol))) {
    status_in_binary = true;
  }
  return status_in_binary;
}

/**
 * @brief Функция определяет корректность выражения с функцией
 * @details Если текущий символ является функцией или возведением в степень,
 * а последующий символ не является числом, унарным минусом, x, открывающей
 * скобкой и такой же функцией или возведением в степень, то возвращается true
 * (то есть после функции нет ничего подходящего), иначе false
 * @return bool
 */
bool check::empty_after_op(char symbol, char aft_symbol) const noexcept {
  bool status_na = false;
  std::string operators_as = "~x(";
  if (check_math_o(symbol) &&
      (!isdigit(aft_symbol) &&
       (operators_as.find(aft_symbol) == std::string::npos) &&
       check_math_o(aft_symbol) != true)) {
    status_na = true;
  }
  return status_na;
}

/**
 * @brief Функция определяет корректность выражения с функцией
 * @details Если текущим символом является функция, открывающая скобка и
 * возведением в степень, а последющим символом является какой-либо бинарный
 * оператор, то возвращается true, иначе false
 * @return bool
 */
bool check::binary_after_op(char symbol, char aft_symbol) const noexcept {
  int status_ba = false;
  if (check_open_o(symbol) && check_binary(aft_symbol)) {
    status_ba = true;
  }
  return status_ba;
}
}  // namespace s21
