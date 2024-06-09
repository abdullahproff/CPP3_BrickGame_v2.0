#include <QApplication>

#include "View.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::SnakeModel s_model;
  s21::SnakeController s_controller(&s_model);
  s21::TetrisModel t_model;
  s21::TetrisController t_controller(&t_model);
  s21::View v(&s_controller, &t_controller);
  v.show();
  return QApplication::exec();
}
