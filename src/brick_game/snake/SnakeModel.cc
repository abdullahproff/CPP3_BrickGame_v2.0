
#include "SnakeModel.h"

namespace s21 {

SnakeModel::SnakeModel() : s_data_() {
  s_data_.best_score = LoadScore("SnakeScore.txt");
}

SnakeModel::~SnakeModel() {
  SaveScore(s_data_.best_score, "SnakeScore.txt");
  s_data_.snake_coord.clear();
}

void SnakeModel::UpdateData(UserAction action) {
  s_data_.is_modified = false;
  SnakeGameData data_cast = s_data_;

  curr_time_ = last_moving_time_;
  if (s_data_.game_status != GameState::kPause) {
    curr_time_ = GetCurrTime();
  }

  Action func = kSnakeActionTable[static_cast<int>(s_data_.game_status)]
                                 [static_cast<int>(action)];
  if (func) {
    (this->*func)();
  }

  if (s_data_.game_status == GameState::kMoving) {
    if (curr_time_ - last_moving_time_ > curr_delay_) {
      MoveSnake();
    }
  }

  if (s_data_ != data_cast) s_data_.is_modified = true;
}

SnakeGameData& SnakeModel::GetModelData() { return s_data_; }

void SnakeModel::SetGameDataDefault() {
  curr_delay_ = GameSizes::kIntervalMs[0];
  last_moving_time_ = curr_time_ = GetCurrTime();
  s_data_.curr_score = 0;
  s_data_.level = 1;
  s_data_.direction = Direction::kUp;
  s_data_.game_status = GameState::kStart;
  s_data_.snake_coord.clear();
  s_data_.snake_coord.reserve(200);

  s_data_.snake_coord.push_back({5, GameSizes::kFieldHeight / 2});
  s_data_.snake_coord.push_back({5, GameSizes::kFieldHeight / 2 + 1});
  s_data_.snake_coord.push_back({5, GameSizes::kFieldHeight / 2 + 2});
  s_data_.snake_coord.push_back({5, GameSizes::kFieldHeight / 2 + 3});

  UpdateFruitPos();
}

void SnakeModel::UpdateFruitPos() {
  std::random_device rd;
  std::default_random_engine gen(rd());
  std::uniform_int_distribution<int> width_distribution(
      0, GameSizes::kFieldWidth - 1);
  std::uniform_int_distribution<int> height_distribution(
      0, GameSizes::kFieldHeight - 1);

  s_data_.fruit_coord.x = width_distribution(gen);
  s_data_.fruit_coord.y = height_distribution(gen);

  for (const auto& i : s_data_.snake_coord) {
    if (s_data_.fruit_coord.x == i.x && s_data_.fruit_coord.y == i.y)
      UpdateFruitPos();
  }
}

void SnakeModel::MoveSnake() {
  switch (s_data_.direction) {
    case Direction::kUp:
      MoveHeadUp();
      break;
    case Direction::kDown:
      MoveHeadDown();
      break;
    case Direction::kLeft:
      MoveHeadLeft();
      break;
    case Direction::kRight:
      MoveHeadRight();
      break;
  }
}

void SnakeModel::MoveSnakeBody() {
  for (auto i = s_data_.snake_coord.size(); i > 0; --i) {
    s_data_.snake_coord[i] = s_data_.snake_coord[i - 1];
  }
}

void SnakeModel::CheckSnakeLife() {
  for (std::size_t i = 1; i < s_data_.snake_coord.size(); ++i) {
    if (s_data_.snake_coord[0] == s_data_.snake_coord[i]) {
      s_data_.game_status = GameState::kCollide;
    }
  }
  if (s_data_.snake_coord[0].x < 0 ||
      s_data_.snake_coord[0].x >= GameSizes::kFieldWidth) {
    s_data_.game_status = GameState::kCollide;
  }
  if (s_data_.snake_coord[0].y < 0 ||
      s_data_.snake_coord[0].y >= GameSizes::kFieldHeight) {
    s_data_.game_status = GameState::kCollide;
  }
}

void SnakeModel::CheckSnakeEating() {
  if (s_data_.snake_coord[0] == s_data_.fruit_coord) {
    s_data_.snake_coord.push_back({-1, -1});
    s_data_.curr_score++;
    if (s_data_.curr_score % 5 == 0 && s_data_.level < 10) {
      s_data_.level++;
      curr_delay_ = GameSizes::kIntervalMs[s_data_.level - 1];
    }
    if (s_data_.curr_score > s_data_.best_score) {
      s_data_.best_score = s_data_.curr_score;
    }
    if (s_data_.curr_score == 200) {
      s_data_.is_victory = true;
      s_data_.game_status = GameState::kGameOver;
    }
    UpdateFruitPos();
  }
}

void SnakeModel::MoveHeadLeft() {
  if (s_data_.direction == Direction::kRight) return;
  s_data_.direction = Direction::kLeft;
  MoveSnakeBody();
  s_data_.snake_coord[0].x -= 1;

  CheckSnakeEating();
  CheckSnakeLife();
  last_moving_time_ = curr_time_;
}

void SnakeModel::MoveHeadRight() {
  if (s_data_.direction == Direction::kLeft) return;
  s_data_.direction = Direction::kRight;
  MoveSnakeBody();
  s_data_.snake_coord[0].x += 1;
  CheckSnakeEating();
  CheckSnakeLife();
  last_moving_time_ = curr_time_;
}

void SnakeModel::MoveHeadUp() {
  if (s_data_.direction == Direction::kDown) return;
  s_data_.direction = Direction::kUp;
  MoveSnakeBody();
  s_data_.snake_coord[0].y -= 1;
  CheckSnakeEating();
  CheckSnakeLife();
  last_moving_time_ = curr_time_;
}

void SnakeModel::MoveHeadDown() {
  if (s_data_.direction == Direction::kUp) return;
  s_data_.direction = Direction::kDown;
  MoveSnakeBody();
  s_data_.snake_coord[0].y += 1;
  CheckSnakeEating();
  CheckSnakeLife();
  last_moving_time_ = curr_time_;
}

void SnakeModel::Spawn() { s_data_.game_status = GameState::kMoving; }

void SnakeModel::SetPause() { s_data_.game_status = GameState::kPause; }

void SnakeModel::CancelPause() { s_data_.game_status = GameState::kMoving; }

void SnakeModel::ExitGame() { s_data_.game_status = GameState::kExit; }

void SnakeModel::Collide() { s_data_.game_status = GameState::kGameOver; }

void SnakeModel::StartGame() { s_data_.game_status = GameState::kSpawn; }

void SnakeModel::GameOver() { s_data_.game_status = GameState::kExit; }

}  // namespace s21
