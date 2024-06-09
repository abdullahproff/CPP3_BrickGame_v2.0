
#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKEMODEL_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKEMODEL_H_

#include <fstream>
#include <iostream>
#include <random>

#include "../common/BaseModel.h"

namespace s21 {

enum class Direction { kUp, kDown, kRight, kLeft };

struct SnakeGameData {
  Coordinates fruit_coord;
  std::vector<Coordinates> snake_coord;
  Direction direction;
  bool is_victory;
  GameState game_status;
  int curr_score;
  int best_score;
  int level;

  bool is_modified;

  SnakeGameData()
      : fruit_coord(),
        snake_coord(),
        direction(Direction::kUp),
        is_victory(false),
        game_status(GameState::kStart),
        curr_score(0),
        best_score(0),
        level(1),
        is_modified(true) {}

  bool operator==(const SnakeGameData& other) const {
    return curr_score == other.curr_score && game_status == other.game_status &&
           fruit_coord == other.fruit_coord && snake_coord == other.snake_coord;
  }
  bool operator!=(const SnakeGameData& other) const {
    return !(*this == other);
  }
};

class SnakeModel : public BaseModel {
 public:
  SnakeModel();
  ~SnakeModel();

  void UpdateData(UserAction action);

  void SetGameDataDefault();
  SnakeGameData& GetModelData();

  using Action = void (SnakeModel::*)();

  const Action kSnakeActionTable[7][9] = {
      // kStart
      {nullptr, nullptr, nullptr, nullptr, nullptr, &SnakeModel::StartGame,
       &SnakeModel::StartGame, &SnakeModel::ExitGame, nullptr},
      // kSpawn
      {&SnakeModel::Spawn, &SnakeModel::Spawn, &SnakeModel::Spawn,
       &SnakeModel::Spawn, &SnakeModel::Spawn, &SnakeModel::Spawn,
       &SnakeModel::Spawn, &SnakeModel::Spawn, &SnakeModel::Spawn},
      // kMoving,
      {nullptr, &SnakeModel::MoveHeadLeft, &SnakeModel::MoveHeadRight,
       &SnakeModel::MoveHeadDown, &SnakeModel::MoveHeadUp,
       &SnakeModel::SetPause, nullptr, &SnakeModel::ExitGame,
       &SnakeModel::SetPause},
      // kCollide,
      {&SnakeModel::Collide, &SnakeModel::Collide, &SnakeModel::Collide,
       &SnakeModel::Collide, &SnakeModel::Collide, &SnakeModel::Collide,
       &SnakeModel::Collide, &SnakeModel::Collide, &SnakeModel::Collide},
      // kPause,
      {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
       &SnakeModel::CancelPause, &SnakeModel::ExitGame,
       &SnakeModel::CancelPause},
      // kExit,
      {&SnakeModel::ExitGame, &SnakeModel::ExitGame, &SnakeModel::ExitGame,
       &SnakeModel::ExitGame, &SnakeModel::ExitGame, &SnakeModel::ExitGame,
       &SnakeModel::ExitGame, &SnakeModel::ExitGame, &SnakeModel::ExitGame},
      // kGameOver
      {&SnakeModel::GameOver, &SnakeModel::GameOver, &SnakeModel::GameOver,
       &SnakeModel::GameOver, &SnakeModel::GameOver, &SnakeModel::GameOver,
       &SnakeModel::GameOver, &SnakeModel::GameOver, &SnakeModel::GameOver}};

 private:
  SnakeGameData s_data_;
  long long last_moving_time_{};
  long long curr_time_{};
  long long curr_delay_{};

  void UpdateFruitPos();
  void MoveSnake();
  void CheckSnakeLife();
  void CheckSnakeEating();

  // FSM ACTION METHODS
  void MoveHeadLeft();
  void MoveHeadRight();
  void MoveHeadDown();
  void MoveHeadUp();
  void Spawn();
  void SetPause();
  void CancelPause();
  void ExitGame();
  void Collide();
  void StartGame();
  void GameOver();
  void MoveSnakeBody();

};  // class SnakeModel

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKEMODEL_H_
