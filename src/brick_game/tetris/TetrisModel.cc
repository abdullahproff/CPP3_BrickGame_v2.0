
#include "TetrisModel.h"

namespace s21 {

TetrisModel::TetrisModel() {
  t_data_.t_field_.resize(
      GameSizes::kFieldHeight,
      std::vector<std::pair<bool, int>>(GameSizes::kFieldWidth, {false, 0}));
  SetGameDataDefault();
  t_data_.t_best_score = LoadScore("TetrisScore.txt");
}

TetrisModel::~TetrisModel() {
  SaveScore(t_data_.t_best_score, "TetrisScore.txt");
  t_data_.t_field_.clear();
}

void TetrisModel::SetGameDataDefault() {
  t_data_.t_score = 0;
  t_data_.t_level = 1;
  t_data_.t_game_status = GameState::kStart;
  t_data_.t_curr.SetRandomShape();
  t_data_.t_next.SetRandomShape();
  t_data_.t_projection = t_data_.t_curr;
  InitializeBoard();
  SetProjection();
  last_moving_time_ = GetCurrTime();
  curr_delay_ = GameSizes::kIntervalMs[0];
}

void TetrisModel::UpdateModelData(UserAction act) {
  t_data_.is_modified = false;
  TetrisGameData data_cast = t_data_;

  long long curr_time = last_moving_time_;
  if (t_data_.t_game_status != GameState::kPause) {
    curr_time = GetCurrTime();
  }

  Action func = kTetrisActionTable[static_cast<int>(t_data_.t_game_status)]
                                  [static_cast<int>(act)];
  if (func) {
    (this->*func)();
  }

  if (t_data_.t_game_status == GameState::kMoving) {
    if (curr_time - last_moving_time_ > curr_delay_) {
      last_moving_time_ = curr_time;
      if (CheckCollide()) UpdateBoard();
      MoveTetrominoDown();
    }
    UpdateLevel();
  }

  if (t_data_ != data_cast) {
    t_data_.is_modified = true;
  }
}

void TetrisModel::PlacePiece() {
  for (const auto& coord : t_data_.t_curr.GetCoords()) {
    int x = coord.x;
    int y = coord.y;
    t_data_.t_field_[y - 1][x].first = true;
    t_data_.t_field_[y - 1][x].second =
        static_cast<int>(t_data_.t_curr.GetShape());
  }
}

void TetrisModel::InitializeBoard() {
  t_data_.t_field_.resize(
      GameSizes::kFieldHeight,
      std::vector<std::pair<bool, int>>(GameSizes::kFieldWidth, {false, 0}));
  for (int i = 0; i < GameSizes::kFieldHeight; ++i) {
    for (int j = 0; j < GameSizes::kFieldWidth; ++j) {
      t_data_.t_field_[i][j].first = false;
      t_data_.t_field_[i][j].second = static_cast<int>(TetroShape::NoShape);
    }
  }
}

int TetrisModel::ClearLines() {
  int count_lines = 0;

  for (int i = 0; i < GameSizes::kFieldHeight; ++i) {
    bool lineFilled = true;
    for (int j = 0; j < GameSizes::kFieldWidth; ++j) {
      if (!t_data_.t_field_[i][j].first) {
        lineFilled = false;
        break;
      }
    }
    if (lineFilled) {
      t_data_.t_field_.erase(t_data_.t_field_.begin() + i);
      t_data_.t_field_.insert(t_data_.t_field_.begin(),
                              std::vector<std::pair<bool, int>>(
                                  GameSizes::kFieldWidth, {false, 0}));
      count_lines++;
    }
  }
  return count_lines;
}

void TetrisModel::SetProjection() {
  t_data_.t_projection = t_data_.t_curr;
  while (TryToMove(t_data_.t_projection, UserAction::kDown)) {
    t_data_.t_projection.MoveDown();
  }
}

bool TetrisModel::TryToMove(Tetromino& t, UserAction dir) {
  bool can_move = true;
  for (const auto& coord : t.GetCoords()) {
    switch (dir) {
      case UserAction::kDown:
        if (coord.y == GameSizes::kFieldHeight ||
            t_data_.t_field_[coord.y][coord.x].first) {
          can_move = false;
        }
        break;
      case UserAction::kLeft:
        if (coord.x < 1 || t_data_.t_field_[coord.y - 1][coord.x - 1].first) {
          can_move = false;
        }
        break;
      case UserAction::kRight:
        if (coord.x == GameSizes::kFieldWidth - 1 ||
            t_data_.t_field_[coord.y - 1][coord.x + 1].first) {
          can_move = false;
        }
        break;
      default:
        break;
    }
    if (!can_move) break;
  }
  return can_move;
}

void TetrisModel::UpdatePlayerResults(int completed_lines) {
  if (completed_lines == 1) {
    t_data_.t_score += 100;
  } else if (completed_lines == 2) {
    t_data_.t_score += 300;
  } else if (completed_lines == 3) {
    t_data_.t_score += 700;
  } else if (completed_lines == 4) {
    t_data_.t_score += 1500;
  }
  t_data_.t_best_score = std::max(t_data_.t_best_score, t_data_.t_score);
  UpdateLevel();
}

void TetrisModel::UpdateBoard() {
  PlacePiece();
  int completed_lines = ClearLines();
  UpdatePlayerResults(completed_lines);
  SpawnNewTetromino();
}

void TetrisModel::UpdateLevel() {
  if (t_data_.t_level < 10 && t_data_.t_score > 600) {
    t_data_.t_level = t_data_.t_score / 600;
  }
  curr_delay_ = GameSizes::kIntervalMs[t_data_.t_level - 1];
}

void TetrisModel::MoveTetrominoLeft() {
  if (TryToMove(t_data_.t_curr, UserAction::kLeft)) {
    t_data_.t_curr.MoveLeft();
    SetProjection();
  }
}

void TetrisModel::MoveTetrominoRight() {
  if (TryToMove(t_data_.t_curr, UserAction::kRight)) {
    t_data_.t_curr.MoveRight();
    SetProjection();
  }
}

void TetrisModel::MoveTetrominoDown() {
  if (TryToMove(t_data_.t_curr, UserAction::kDown)) {
    t_data_.t_curr.MoveDown();
    SetProjection();
  }
}

void TetrisModel::DropTetromino() {
  t_data_.t_curr = t_data_.t_projection;
  UpdateBoard();
}

void TetrisModel::RotateTetromino() {
  auto tmp_tetromino = t_data_.t_curr;
  t_data_.t_curr.Rotate();
  bool can_rotate = true;
  for (const auto& coord : t_data_.t_curr.GetCoords()) {
    if (t_data_.t_field_[coord.y - 1][coord.x].first) {
      can_rotate = false;
      break;
    }
  }
  if (!can_rotate) {
    t_data_.t_curr = tmp_tetromino;
  }
  SetProjection();
}

void TetrisModel::SpawnNewTetromino() {
  t_data_.t_game_status = GameState::kMoving;
  t_data_.t_curr = t_data_.t_next;
  t_data_.t_next.SetRandomShape();
  t_data_.t_projection = t_data_.t_curr;
  SetProjection();
  if (CheckCollide()) t_data_.t_game_status = GameState::kGameOver;
}

void TetrisModel::SetPause() { t_data_.t_game_status = GameState::kPause; }

void TetrisModel::CancelPause() { t_data_.t_game_status = GameState::kMoving; }

void TetrisModel::ExitGame() { t_data_.t_game_status = GameState::kExit; }

void TetrisModel::Collide() {
  t_data_.t_game_status = GameState::kSpawn;
  UpdateBoard();
}

void TetrisModel::StartGame() {
  SetGameDataDefault();
  t_data_.t_game_status = GameState::kSpawn;
}

void TetrisModel::GameOver() { t_data_.t_game_status = GameState::kExit; }

bool TetrisModel::CheckCollide() {
  bool is_collide = false;
  for (const auto& coord : t_data_.t_curr.GetCoords()) {
    if (coord.y == GameSizes::kFieldHeight) {  // down board
      is_collide = true;
      break;
    }
    if (t_data_.t_field_[coord.y][coord.x].first) {  // other tetrominos
      is_collide = true;
      break;
    }
  }
  return is_collide;
}

}  // namespace s21
