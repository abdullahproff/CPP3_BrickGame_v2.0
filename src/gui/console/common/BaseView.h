
#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_CONSOLE_COMMON_BASEVIEW_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_CONSOLE_COMMON_BASEVIEW_H_

#include <ncurses.h>

#include <chrono>
#include <cmath>
#include <string>
#include <thread>

#include "../../../brick_game/common/Constants.h"

namespace s21 {

enum class ColorIndex {
  kRed = 100,  // Красный
  kGreen,      // Зеленый
  kCyan,       // Голубой
  kPurple,     // Фиолетовый
  kYellow,     // Желтый
  kOrange,     // Оранжевый
  kBlue,       // Синий
  kGray,       // Серый
};

enum class Choose { kSnake, kTetris, kMenu, kExit };

class BaseView {
 public:
  virtual void Start() = 0;

  static void DrawBox(int topLeftY, int topLeftX, int bottomRightY,
                      int bottomRightX);
  static void GameFieldRendering(Choose curr_game, int level, int score,
                                 int record);
  static void GameResultRendering(bool is_victory, int level, int score);
  static void PauseRendering(int level, int score);
  static void StartGameRendering();
  static UserAction GetAction();

  static Choose InitMenu();
  static void MenuRendering(std::size_t& selectedItem);
};

}  // namespace s21
#endif  // CPP3_BRICKGAME_V2_0_1_SRC_GUI_CONSOLE_COMMON_BASEVIEW_H_
