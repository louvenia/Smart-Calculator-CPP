#include "mainwindow.h"

#include "./ui_mainwindow.h"

namespace s21 {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  movie_successfully = new QMovie(":/successfully.gif");
  movie_failed = new QMovie(":/failed.gif");

  ui->stackedWidget->setCurrentIndex(0);
  ui->page_1lb->setChecked(true);

  ui->graphic->setInteraction(QCP::iRangeZoom, true);
  ui->graphic->setInteraction(QCP::iRangeDrag, true);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(input_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(input_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(input_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(input_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(input_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(input_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(input_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(input_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(input_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(input_numbers()));
  connect(ui->add_x, SIGNAL(clicked()), this, SLOT(input_numbers()));
  connect(ui->right_bracket, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->left_bracket, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->plus, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->minus, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->multiplication, SIGNAL(clicked()), this,
          SLOT(input_operations()));
  connect(ui->division, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->exp, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->lg, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->dot, SIGNAL(clicked()), this, SLOT(input_operations()));
  connect(ui->AC, SIGNAL(clicked()), this, SLOT(all_clean()));
  connect(ui->one_delete, SIGNAL(clicked()), this, SLOT(one_delete()));
  connect(ui->equals, SIGNAL(clicked()), this, SLOT(result_after_equals()));

  connect(ui->make_graphic, SIGNAL(clicked()), this, SLOT(make_graphic()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
    result_after_equals();
  } else if (e->key() == Qt::Key_Escape) {
    this->close();
  }
}

void MainWindow::input_operations() {
  QPushButton *button = (QPushButton *)sender();
  QString string;
  string = (ui->result_show->text() + button->text());
  ui->result_show->setText(string);
}

void MainWindow::input_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString string;
  string = (ui->result_show->text() + button->text());
  ui->result_show->setText(string);
}

void MainWindow::result_after_equals() {
  std::pair<std::string, bool> result_status = s21::controller::calculate(
      ui->result_show->text().toStdString(), ui->added_x->text().toStdString());
  if (result_status.second) {
    ui->result_show->setText(QString::fromStdString(result_status.first));
    gif_successfully();
  } else {
    gif_failed();
  }
}

void MainWindow::make_graphic() {
  s21::data_graph input_values = {
      ui->function->text().toStdString(),
      ui->min_x->text().toDouble(),
      ui->max_x->text().toDouble(),
      ui->min_y->text().toDouble(),
      ui->max_y->text().toDouble(),
      (std::size_t)ui->graphic->axisRect()->width()};

  s21::result_graph result = s21::controller::graph_calculate(input_values);

  if (result.status) {
    gif_successfully();
    X = QVector<double>(result.X.begin(), result.X.end());
    Y = QVector<double>(result.Y.begin(), result.Y.end());
    ui->graphic->clearGraphs();
    ui->graphic->xAxis->setRange(ui->min_x->text().toDouble(),
                                 ui->max_x->text().toDouble());
    ui->graphic->yAxis->setRange(ui->min_y->text().toDouble(),
                                 ui->max_y->text().toDouble());
    ui->graphic->addGraph();
    ui->graphic->graph(0)->data().clear();
    ui->graphic->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->graphic->graph(0)->setPen(QColor(237, 0, 168, 189));
    ui->graphic->graph(0)->setBrush(QColor(237, 0, 168, 189));
    ui->graphic->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssCross, 1));
    ui->graphic->graph(0)->setData(X, Y);
    ui->graphic->replot();
    X.clear();
    Y.clear();
  } else {
    gif_failed();
  }
}

void MainWindow::on_calculate_credit_clicked() {
  s21::data_credit input_values = {
      ui->amount->text().toDouble(), ui->term->text().toInt(),
      ui->interest_rate->text().toDouble(), ui->type_term->currentIndex(),
      ui->annu->isChecked()};

  s21::result_credit result = s21::controller::credit_calculate(input_values);

  if (result.status) {
    if (ui->annu->isChecked()) {
      ui->monthly_payment->setText(
          QString::number(result.monthly_payment, 'f', 7));
    } else {
      QString text =
          QString("%1 %2 %3")
              .arg(QString::number(result.monthly_payment, 'f', 7), "...",
                   QString::number(result.monthly_payment1, 'f', 7));
      ui->monthly_payment->setText(text);
    }
    ui->overpayment->setText(QString::number(result.overpayment, 'f', 7));
    ui->total_payment->setText(QString::number(result.total_payment, 'f', 7));
    gif_successfully();
  } else {
    gif_failed();
  }
}

void MainWindow::on_calculate_deposit_clicked() {
  s21::data_deposit input_values = {
      ui->deposit->text().toDouble(),
      ui->term_deposit->text().toInt(),
      ui->interest_rate_deposit->text().toDouble(),
      ui->tax->text().toDouble(),
      ui->type_payments->currentIndex(),
      ui->replenishment->text().toDouble(),
      ui->type_replenishment->currentIndex(),
      ui->withdrawal->text().toDouble(),
      ui->type_withdrawal->currentIndex(),
      ui->minimum_balance->text().toDouble(),
      ui->capitalization->isChecked(),
      ui->type_term_deposit->currentIndex()};

  s21::result_deposit result = s21::controller::deposit_calculate(input_values);

  if (result.status) {
    ui->accrued_interest->setText(
        QString::number(result.accrued_interest, 'f', 7));
    ui->tax_amount->setText(QString::number(result.tax_amount, 'f', 7));
    ui->deposit_amount->setText(QString::number(result.deposit_amount, 'f', 7));
    gif_successfully();
  } else {
    gif_failed();
  }
}

void MainWindow::gif_successfully() {
  movie_failed->stop();
  ui->label_output_message->setText("This is right");
  ui->label_gif->setMovie(movie_successfully);
  movie_successfully->start();
}

void MainWindow::gif_failed() {
  movie_successfully->stop();
  ui->label_output_message->setText("Invalid input data");
  ui->label_gif->setMovie(movie_failed);
  movie_failed->start();
}

void MainWindow::one_delete() {
  QString text = ui->result_show->text();
  text.chop(1);
  if (text.isEmpty()) {
    text = "";
  }
  ui->result_show->setText(text);
}

void MainWindow::all_clean() { ui->result_show->setText(""); }

void MainWindow::on_clear_graphic_clicked() {
  ui->function->setText("");
  ui->min_x->setText("");
  ui->min_y->setText("");
  ui->max_x->setText("");
  ui->max_y->setText("");
}

void MainWindow::on_clear_credit_clicked() {
  ui->amount->setText("");
  ui->interest_rate->setText("");
  ui->term->setText("");
  ui->monthly_payment->setText("");
  ui->overpayment->setText("");
  ui->total_payment->setText("");
}

void MainWindow::on_clear_deposit_clicked() {
  ui->deposit->setText("");
  ui->interest_rate_deposit->setText("");
  ui->term_deposit->setText("");
  ui->tax->setText("");
  ui->replenishment->setText("");
  ui->withdrawal->setText("");
  ui->minimum_balance->setText("");
  ui->accrued_interest->setText("");
  ui->tax_amount->setText("");
  ui->deposit_amount->setText("");
}

void MainWindow::on_page_1lb_clicked(bool checked) {
  if (checked) {
    ui->stackedWidget->setCurrentIndex(0);
  }
}

void MainWindow::on_page_2lb_clicked(bool checked) {
  if (checked) {
    ui->stackedWidget->setCurrentIndex(1);
  }
}

void MainWindow::on_page_3lb_clicked(bool checked) {
  if (checked) {
    ui->stackedWidget->setCurrentIndex(2);
  }
}

void MainWindow::on_page_4lb_clicked(bool checked) {
  if (checked) {
    ui->stackedWidget->setCurrentIndex(3);
  }
}
}  // namespace s21
