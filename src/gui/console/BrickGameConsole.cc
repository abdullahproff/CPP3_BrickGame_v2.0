//
// Created by Raisin Ibben on 14.03.2024.
//

#include "common/BrickGameConsoleView.h"

int main() {
  s21::SnakeModel s_model;
  s21::SnakeController s_controller(&s_model);
  s21::TetrisModel t_model;
  s21::TetrisController t_controller(&t_model);
  s21::BrickGameConsoleView view(&s_controller, &t_controller);
  view.Start();
  return 0;
}
