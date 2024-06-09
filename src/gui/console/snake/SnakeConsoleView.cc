
#include "SnakeConsoleView.h"

namespace s21 {

SnakeConsoleView::SnakeConsoleView(SnakeController* c)
    : action_(UserAction::kNoSig), data_(), controller_(c) {}

void SnakeConsoleView::Start() {
  nodelay(stdscr, TRUE);
  controller_->SetModelDataDefault();
  data_ = &controller_->GetModelData();
  SnakeMainLoop();

  if (data_->game_status == GameState::kGameOver ||
      data_->game_status == GameState::kExit) {
    GameResultRendering(data_->is_victory, data_->level, data_->curr_score);
  }
}

void SnakeConsoleView::SnakeMainLoop() {
  while (data_->game_status != GameState::kGameOver &&
         data_->game_status != GameState::kExit) {
    if (data_->is_modified) {
      Rendering();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    action_ = GetAction();
    ModelConnect();
  }
}

void SnakeConsoleView::Rendering() {
  if (data_->game_status == GameState::kStart) {
    StartGameRendering();
  } else if (data_->game_status == GameState::kPause) {
    PauseRendering(data_->level, data_->curr_score);
  } else {
    GameRendering();
  }
}

void SnakeConsoleView::ModelConnect() {
  controller_->UpdateModelData(action_);
  data_ = &controller_->GetModelData();
  action_ = UserAction::kNoSig;
}

void SnakeConsoleView::GameRendering() {
  clear();
  // Fruit
  attron(COLOR_PAIR(1));
  mvprintw(data_->fruit_coord.y + 1, data_->fruit_coord.x + 1, "%c", ACS_PI);
  attroff(COLOR_PAIR(1));

  // Snake
  attron(COLOR_PAIR(2));
  for (const auto& i : data_->snake_coord) {
    mvprintw(i.y + 1, i.x + 1, "%c", 'S');
  }
  attroff(COLOR_PAIR(2));

  // Game field && Side menu data
  GameFieldRendering(Choose::kSnake, data_->level, data_->curr_score,
                     data_->best_score);
  refresh();
}

}  // namespace s21
