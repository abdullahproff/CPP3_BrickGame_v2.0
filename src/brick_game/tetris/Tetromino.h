
#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETROMINO_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETROMINO_H_

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

#include "../common/Constants.h"

namespace s21 {

enum struct TetroShape {
  NoShape,
  ZShape,
  SShape,
  LineShape,
  TShape,
  SquareShape,
  LShape,
  MirroredLShape
};

namespace TetroCoords {
static constexpr int coordsTable[8][4][2] = {
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},     // NoShape
    {{0, -1}, {0, 0}, {-1, 0}, {-1, 1}},  // ZShape
    {{0, -1}, {0, 0}, {1, 0}, {1, 1}},    // SShape
    {{0, -1}, {0, 0}, {0, 1}, {0, 2}},    // LineShape
    {{-1, 0}, {0, 0}, {1, 0}, {0, 1}},    // TShape
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}},     // SquareShape
    {{-1, -1}, {0, -1}, {0, 0}, {0, 1}},  // LShape
    {{1, -1}, {0, -1}, {0, 0}, {0, 1}}    // MirroredLShape
};
};

class Tetromino {
 public:
  Tetromino();
  Tetromino(const Tetromino &other);
  Tetromino &operator=(const Tetromino &other);

  std::vector<Coordinates> GetCoords() { return t_coords_; }

  bool operator==(const Tetromino &other) const {
    return shape_ == other.shape_ && t_coords_ == other.t_coords_;
  }
  bool operator!=(const Tetromino &other) const { return !(*this == other); }

  void SetShape(TetroShape s);
  void SetRandomShape();

  TetroShape GetShape() { return shape_; }
  void Rotate();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

  int GetMinX();
  int GetMaxX();
  int GetMinY();
  int GetMaxY();

 private:
  TetroShape shape_;
  std::vector<Coordinates> t_coords_;
};

}  // namespace s21
#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETROMINO_H_
