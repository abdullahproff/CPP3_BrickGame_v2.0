
#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_COMMON_CONSTANTS_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_COMMON_CONSTANTS_H_

#include <iostream>
#include <vector>

namespace s21 {

namespace GameSizes {
constexpr int kDotSize = 30;
constexpr int kFieldWidth = 10;
constexpr int kFieldHeight = 20;
constexpr int kSidePanelHeight = 5;
constexpr int kWindowWidth = 22;
constexpr int kWindowHeight = 21;
static constexpr int kIntervalMs[] = {500, 420, 340, 260, 230,
                                      200, 180, 160, 140, 125};
}  // namespace GameSizes

enum class GameState {
  kStart,
  kSpawn,
  kMoving,
  kCollide,
  kPause,
  kExit,
  kGameOver
};

enum class UserAction {
  kNoSig = 0,
  kLeft,      // 1
  kRight,     // 2
  kDown,      // 3
  kUp,        // 4
  kSpaceBtn,  // 5
  kEnterBtn,  // 6
  kEscBtn,    // 7
  kTabBtn     // 8
};

struct Coordinates {
  Coordinates() : x(0), y(0) {}
  Coordinates(int x_, int y_) : x(x_), y(y_) {}
  bool operator==(const Coordinates &other) const {
    return (x == other.x && y == other.y);
  }
  int x;
  int y;
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_COMMON_CONSTANTS_H_
