
#include "TetrisConsoleView.h"

namespace s21 {

TetrisConsoleView::TetrisConsoleView(TetrisController *c) : controller_(c) {
  t_data_ = &controller_->GetModelData();
  t_action_ = UserAction::kNoSig;
}

void TetrisConsoleView::Start() {
  nodelay(stdscr, TRUE);
  controller_->SetModelDataDefault();
  t_data_ = &controller_->GetModelData();

  TetrisMainLoop();

  if (t_data_->t_game_status == GameState::kGameOver ||
      t_data_->t_game_status == GameState::kExit) {
    GameResultRendering(false, t_data_->t_level, t_data_->t_score);
  }
}

void TetrisConsoleView::TetrisMainLoop() {
  while (t_data_->t_game_status != GameState::kGameOver &&
         t_data_->t_game_status != GameState::kExit) {
    if (t_data_->is_modified) {
      Rendering();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    t_action_ = GetAction();
    ModelConnect();
  }
}

void TetrisConsoleView::Rendering() {
  if (t_data_->t_game_status == GameState::kStart) {
    StartGameRendering();
  } else if (t_data_->t_game_status == GameState::kPause) {
    PauseRendering(t_data_->t_level, t_data_->t_score);
  } else {
    GameRendering();
  }
}

void TetrisConsoleView::ModelConnect() {
  controller_->UpdateModelData(t_action_);
  TetrisGameData tmp_data = controller_->GetModelData();
  t_action_ = UserAction::kNoSig;
}

void TetrisConsoleView::GameRendering() {
  clear();
  GameFieldRendering(Choose::kTetris, t_data_->t_level, t_data_->t_score,
                     t_data_->t_best_score);

  // current tetromino projection
  for (const auto &item : t_data_->t_projection.GetCoords()) {
    attron(COLOR_PAIR(8));
    mvprintw(item.y, item.x + 1, ".");
    attroff(COLOR_PAIR(8));
  }

  // current tetromino
  for (const auto &item : t_data_->t_curr.GetCoords()) {
    attron(COLOR_PAIR((short)t_data_->t_curr.GetShape()));
    mvprintw(item.y, item.x + 1, ".");
    attroff(COLOR_PAIR((short)t_data_->t_curr.GetShape()));
  }

  // next tetromino
  for (const auto &item : t_data_->t_next.GetCoords()) {
    attron(COLOR_PAIR((short)t_data_->t_next.GetShape()));
    mvprintw(item.y + 1, item.x + 11, ".");
    attroff(COLOR_PAIR((short)t_data_->t_next.GetShape()));
  }

  // board
  for (int i = 0; i < GameSizes::kFieldHeight; ++i) {
    for (int j = 0; j < GameSizes::kFieldWidth; ++j) {
      attron(COLOR_PAIR(t_data_->t_field_[i][j].second));
      if (t_data_->t_field_[i][j].first) mvprintw(i + 1, j + 1, ".");
      attroff(COLOR_PAIR(t_data_->t_field_[i][j].second));
    }
  }
}

}  // namespace s21
