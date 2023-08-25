#include <QApplication>
#include <QPixmap>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setOverrideCursor(QCursor(QPixmap(":/cursor.png")));
  s21::MainWindow w;
  w.setWindowTitle("BLACKPINK SMARTCALC");
  w.show();
  return a.exec();
}
