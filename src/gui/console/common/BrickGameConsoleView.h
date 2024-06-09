
#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_CONSOLE_COMMON_BRICKGAMECONSOLEVIEW_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_CONSOLE_COMMON_BRICKGAMECONSOLEVIEW_H_

#include <ncurses.h>

#include "../snake/SnakeConsoleView.h"
#include "../tetris/TetrisConsoleView.h"
#include "BaseView.h"

namespace s21 {

class BrickGameConsoleView : public BaseView {
 public:
  explicit BrickGameConsoleView(SnakeController *s_c = nullptr,
                                TetrisController *t_c = nullptr);
  ~BrickGameConsoleView() = default;

  void Start() override;

 protected:
  static void InitNcurses();

 private:
  void MainLoop();

  SnakeConsoleView snake_view_;
  TetrisConsoleView tetris_view_;
  static void InitColors();
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_GUI_CONSOLE_COMMON_BRICKGAMECONSOLEVIEW_H_
