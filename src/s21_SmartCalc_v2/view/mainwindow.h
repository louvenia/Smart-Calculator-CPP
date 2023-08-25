#ifndef SRC_VIEW_MAINWINDOW_H
#define SRC_VIEW_MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QMovie>
#include <QVector>

#include "controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void keyPressEvent(QKeyEvent *e);
  void input_operations();
  void input_numbers();
  void result_after_equals();
  void make_graphic();
  void on_calculate_credit_clicked();
  void on_calculate_deposit_clicked();
  void gif_successfully();
  void gif_failed();
  void one_delete();
  void all_clean();
  void on_clear_graphic_clicked();
  void on_clear_credit_clicked();
  void on_clear_deposit_clicked();
  void on_page_1lb_clicked(bool checked);
  void on_page_2lb_clicked(bool checked);
  void on_page_3lb_clicked(bool checked);
  void on_page_4lb_clicked(bool checked);

 private:
  Ui::MainWindow *ui;
  QMovie *movie_failed, *movie_successfully;
  QVector<double> X, Y;
};
}  // namespace s21
#endif  // SRC_VIEW_MAINWINDOW_H
