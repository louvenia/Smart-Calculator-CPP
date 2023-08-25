#include "s21_credit_calculator.h"

namespace s21 {
credit::credit() noexcept
    : amount(), interest_rate(), term(), type_credit(), status(true) {}

/**
 * @brief Функция проверяет и устанавливает входящие значения
 * @details Если статус изменился на false(ошибка при проверке), то расчет не
 * проводится
 */
void credit::set_data_credit(const struct data_credit& input_values) {
  amount = input_values.amount;
  term = input_values.term;
  interest_rate = input_values.interest_rate;
  type_credit = input_values.type_credit;

  if (input_values.type_term == 0) {
    term = term * 12;
  }
  if (amount <= 0 || term <= 0 || interest_rate <= 0) {
    status = false;
  }
  result_values.status = status;
}

/**
 * @brief Функция вызывает либо аннуитетный, либо дифференциальный расчет
 * @details Зависит от входящего значения type_credit. Возвращает структуру
 * данных в качестве результата
 *
 * @return struct
 */
struct result_credit credit::credit_calculate() {
  if (status) {
    if (type_credit) {
      annuity_calc();
    } else {
      differentiated_calc();
    }
  }
  return result_values;
}

/**
 * @brief Функция проводит расчет по аннуитетному типу
 * @details Когда ежемесячный платеж постоянный на всем периоде
 */
void credit::annuity_calc() {
  double monthly_payment = 0.0, interest_period = 0.0,
         monthly_interest_rate = 0.0;
  interest_period = term * (-1);
  monthly_interest_rate = interest_rate / (100 * 12);
  monthly_payment =
      amount * (monthly_interest_rate /
                (1 - pow((1 + monthly_interest_rate), interest_period)));
  result_values.monthly_payment = monthly_payment;
  result_values.total_payment = monthly_payment * term;
  result_values.overpayment = result_values.total_payment - amount;
}

/**
 * @brief Функция проводит расчет по дифференциальному типу
 * @details Когда ежемесячный платеж постепенно уменьшается к концу срока
 * кредитования
 */
void credit::differentiated_calc() {
  double monthly_interest_rate = 0.0, monthly_payment_h = 0.0,
         monthly_overpayment = 0.0, monthly_payment = 0.0,
         monthly_payment1 = 0.0, total_payment = 0.0, overpayment = 0.0;
  monthly_payment_h = amount / term;
  monthly_interest_rate = interest_rate / (100 * 12);
  double balance = amount;
  double count_period = term;
  while (count_period) {
    monthly_overpayment = balance * monthly_interest_rate;
    if (count_period == term) {
      monthly_payment = monthly_payment_h + monthly_overpayment;
    } else if (count_period == 1) {
      monthly_payment1 = monthly_payment_h + monthly_overpayment;
    }
    overpayment += monthly_overpayment;
    balance -= monthly_payment_h;
    count_period--;
  }
  total_payment = amount + overpayment;
  result_values.monthly_payment = monthly_payment;
  result_values.total_payment = total_payment;
  result_values.overpayment = overpayment;
  result_values.monthly_payment1 = monthly_payment1;
}
}  // namespace s21
