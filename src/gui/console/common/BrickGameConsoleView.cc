
#include "BrickGameConsoleView.h"

namespace s21 {

BrickGameConsoleView::BrickGameConsoleView(SnakeController *s_c,
                                           TetrisController *t_c)
    : snake_view_(s_c), tetris_view_(t_c) {}

void BrickGameConsoleView::Start() {
  setlocale(LC_ALL, "");
  InitNcurses();
  MainLoop();
}

void BrickGameConsoleView::InitNcurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);

  start_color();
  InitColors();
}

void BrickGameConsoleView::MainLoop() {
  Choose ch = InitMenu();

  while (ch != Choose::kExit) {
    if (ch == Choose::kSnake) {
      snake_view_.Start();
    } else if (ch == Choose::kTetris) {
      tetris_view_.Start();
    }
    ch = InitMenu();
  }

  curs_set(1);
  endwin();
}

void BrickGameConsoleView::InitColors() {
  init_color((short)ColorIndex::kRed, 1000, 0, 0);
  init_color((short)ColorIndex::kGreen, 0, 1000, 0);
  init_color((short)ColorIndex::kCyan, 0, 1000, 1000);
  init_color((short)ColorIndex::kPurple, 1000, 0, 1000);
  init_color((short)ColorIndex::kYellow, 1000, 1000, 0);
  init_color((short)ColorIndex::kOrange, 1000, 500, 0);
  init_color((short)ColorIndex::kBlue, 0, 0, 1000);
  init_color((short)ColorIndex::kGray, 500, 500, 500);

  init_pair(1, (short)ColorIndex::kRed, (short)ColorIndex::kRed);  // Красный
  init_pair(2, (short)ColorIndex::kGreen,
            (short)ColorIndex::kGreen);  // Зеленый
  init_pair(3, (short)ColorIndex::kCyan, (short)ColorIndex::kCyan);  // Голубой
  init_pair(4, (short)ColorIndex::kPurple,
            (short)ColorIndex::kPurple);  // Фиолетовый
  init_pair(5, (short)ColorIndex::kYellow,
            (short)ColorIndex::kYellow);  // Желтый
  init_pair(6, (short)ColorIndex::kOrange,
            (short)ColorIndex::kOrange);  // Оранжевый
  init_pair(7, (short)ColorIndex::kBlue, (short)ColorIndex::kBlue);  // Синий
  init_pair(8, (short)ColorIndex::kGray, (short)ColorIndex::kGray);  // Серый
}

}  // namespace s21
