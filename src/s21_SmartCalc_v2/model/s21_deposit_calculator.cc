#include "s21_deposit_calculator.h"

namespace s21 {
deposit::deposit() noexcept
    : deposit_amount(),
      interest_rate(),
      tax(),
      replenishment(),
      withdrawal(),
      minimum_balance(),
      term(),
      type_payments(),
      type_replenishment(),
      type_withdrawal(),
      capitalization(),
      status(true) {}

/**
 * @brief Функция проверяет и устанавливает входящие значения
 * @details Если статус изменился на false(ошибка при проверке), то расчет не
 * проводится
 */
void deposit::set_data_deposit(const struct data_deposit &input_values) {
  deposit_amount = input_values.deposit_amount;
  term = input_values.term;
  interest_rate = input_values.interest_rate;
  tax = input_values.tax;
  type_payments = input_values.type_payments;
  replenishment = input_values.replenishment;
  type_replenishment = input_values.type_replenishment;
  withdrawal = input_values.withdrawal;
  type_withdrawal = input_values.type_withdrawal;
  minimum_balance = input_values.minimum_balance;
  capitalization = input_values.capitalization;

  if (input_values.type_term == 0) {
    term = term * 12;
  }
  if (deposit_amount <= 0 || term <= 0 || interest_rate <= 0 || tax < 0 ||
      replenishment < 0 || withdrawal < 0 || minimum_balance < 0) {
    status = false;
  }
  result_values.status = status;
}

/**
 * @brief Функция проводит депозитный расчет
 * @details Сначала определяется тип периодичности выплат, затем проводится
 * расчет периода в днях или в месяцах, период налога, вверхнее значение
 * является сроком размещения, если выплата проводится к концу срока, иначе 1,
 * так как нижним значением определяется переодичность, как год, количество
 * дней, недель, месяцев, кварталов и полгодий в году. В зависимости от того,
 * что включена ли капитализация, конечная сумма на вкладе может быть увеличена
 * на количество начисленных процентов.
 *
 * @return struct
 */
struct result_deposit deposit::deposit_calc() {
  if (status == false) {
    result_values = {0, 0, 0, false};
    return result_values;
  }
  double accrued_interest = 0.0, tax_amount = 0.0, finall_amount = 0.0,
         upper_value = 0.0, lower_value = 0.0, upper_value_rem = 0.0,
         lower_value_rem = 0.0;
  int period_n = 0, period_rem = 0, tax_period = 0, tax_period_rem = 0;
  if (type_payments == 0) {  // Каждый день
    for (int numbers = 0, count_years = 0; term > 0;
         term--, numbers++, count_years++) {
      if (count_years == 12) {
        count_years = 0;
        numbers = 0;
      }
      period_n += kdays[numbers];
    }
    tax_period = period_n / 365;
    upper_value = 1.0, lower_value = 365.0;  // по умолчанию в 1 месяце 30 дней
  } else if (type_payments == 1) {  // Каждую неделю
    period_n = term * 4, upper_value = 1.0,
    lower_value = 48.0;  // общее количество месяцев, по умолчанию, в 1 месяце 4
                         // недели, в 1 году 48 недели
    tax_period = period_n / 48;
  } else if (type_payments == 2) {  // Раз в месяц
    period_n = term, upper_value = 1.0, lower_value = 12.0;
    tax_period = period_n / 12;
  } else if (type_payments == 3) {  // Раз в квартал
    period_n = term / 3, upper_value = 1.0, lower_value = 4.0;
    if (term % 3 != 0) {
      period_rem = term - (period_n * 3), upper_value_rem = 1.0,
      lower_value_rem = 12.0;
    }
    tax_period = period_n / 4;
  } else if (type_payments == 4) {  // Раз в полгода
    period_n = term / 6, upper_value = 1.0, lower_value = 2.0;
    if (term % 6 != 0) {
      period_rem = term - (period_n * 6), upper_value_rem = 1.0,
      lower_value_rem = 12.0;
    }
    tax_period = period_n / 2;
  } else if (type_payments == 5) {  // Раз в год
    period_n = term / 12, upper_value = 1.0, lower_value = 1.0;
    if (term % 12 != 0) {
      period_rem = term - (period_n * 12), upper_value_rem = 1.0,
      lower_value_rem = 12.0;
    }
    tax_period = period_n;
  } else if (type_payments == 6) {  // В конце срока
    period_n = 1, upper_value = term, lower_value = 12.0;
    tax_period = period_n;
  }
  calculation_deposit(period_n, &accrued_interest, &tax_amount, upper_value,
                      lower_value, tax_period);
  calculation_deposit(period_rem, &accrued_interest, &tax_amount,
                      upper_value_rem, lower_value_rem, tax_period_rem);
  if (capitalization) {
    finall_amount = deposit_amount + accrued_interest;
  } else {
    finall_amount = deposit_amount;
  }
  result_values.accrued_interest = accrued_interest;
  result_values.tax_amount = tax_amount;
  result_values.deposit_amount = finall_amount;
  return result_values;
}

/**
 * @brief Функция рассчитывает начисленные проценты и сумму на вкладе
 * @details В зависимости от периодичности выплат определяется накопленная сумма
 * засчет процентной ставки
 */
void deposit::calculation_deposit(int period_type, double *accrued_interest,
                                  double *tax_amount, double upper_value,
                                  double lower_value, int tax_period) {
  double days_deposit = 0.0, sum_deposit = 0.0;
  int status_tax = 0;
  while (period_type) {
    if (deposit_amount > 0) {
      if (capitalization) {
        sum_deposit = deposit_amount + *accrued_interest;
      } else {
        sum_deposit = deposit_amount;
      }
      days_deposit =
          (sum_deposit * (interest_rate * 0.01 * upper_value / lower_value));
      *accrued_interest += days_deposit;
      int int_period = period_type;
      replenishment_op(int_period);
      withdrawal_op(int_period);
    }
    period_type--;
  }
  if (tax_period >= 1 && status_tax == 0) {
    calc_tax_amount(accrued_interest, tax_amount, tax_period, &status_tax);
  }
}

/**
 * @brief Функция рассчитывает размер НДФЛ
 * @details ключевая ставка ЦБ на 1ое января расчетного года 7.5% из этого
 * расчитывается сумма необлагаемого дохода и сравнивается с доходом по вкладам
 */
void deposit::calc_tax_amount(double *accrued_interest, double *tax_amount,
                              int tax_period, int *status_tax) {
  double tax_free_income = 0.0;
  if (!tax) {
    tax = 0.13;
  }
  tax_free_income = 0.075 * 1000000;
  if (*accrued_interest > tax_free_income) {
    for (double tax_year = 0.0; tax_period > 0; tax_period--) {
      tax_year = (*accrued_interest - tax_free_income) * tax;
      *tax_amount += tax_year;
    }
  }
  *status_tax = 1;
}

/**
 * @brief Функция пополняет вклад на определенную сумму с заданной
 * периодичностью
 * @details type_replenishment == 0 (разовое), 1 (раз в месяц), 2 (раз в 2
 * месяца), 3 (раз в квартал), 4 (раз в полгода) и 5 (раз в год)
 */
void deposit::replenishment_op(int int_period) {
  if (type_replenishment < 6) {
    if (type_replenishment == 0) {  // Разовое
      deposit_amount += replenishment;
      type_replenishment = 6;
    }
    if (type_replenishment == 1) {  // Раз в месяц
      deposit_amount += replenishment;
    }
    if (type_replenishment == 2 && int_period % 2 == 0) {  // Раз в 2 месяца
      deposit_amount += replenishment;
    }
    if (type_replenishment == 3 && int_period % 3 == 0) {  // Раз в квартал
      deposit_amount += replenishment;
    }
    if (type_replenishment == 4 && int_period % 6 == 0) {  // Раз в полгода
      deposit_amount += replenishment;
    }
    if (type_replenishment == 5 && int_period % 12 == 0) {  // Раз в год
      deposit_amount += replenishment;
    }
  }
}

/**
 * @brief Функция производит частичное снятие из вклада на определенную сумму с
 * заданной периодичностью
 * @details type_withdrawal == 0 (разовое), 1 (раз в месяц), 2 (раз в 2 месяца),
 * 3 (раз в квартал), 4 (раз в полгода) и 5 (раз в год)
 */
void deposit::withdrawal_op(int int_period) {
  if (type_withdrawal < 6 && (deposit_amount - withdrawal) >= minimum_balance) {
    if (type_withdrawal == 0) {  // Разовое
      deposit_amount -= withdrawal;
      type_withdrawal = 6;
    }
    if (type_withdrawal == 1) {  // Раз в месяц
      deposit_amount -= withdrawal;
    }
    if (type_withdrawal == 2 && int_period % 2 == 0) {  // Раз в 2 месяца
      deposit_amount -= withdrawal;
    }
    if (type_withdrawal == 3 && int_period % 3 == 0) {  // Раз в квартал
      deposit_amount -= withdrawal;
    }
    if (type_withdrawal == 4 && int_period % 6 == 0) {  // Раз в полгода
      deposit_amount -= withdrawal;
    }
    if (type_withdrawal == 5 && int_period % 12 == 0) {  // Раз в год
      deposit_amount -= withdrawal;
    }
  }
}

}  // namespace s21
