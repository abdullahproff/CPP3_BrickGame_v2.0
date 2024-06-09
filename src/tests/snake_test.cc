
#include <gtest/gtest.h>

#include <thread>

#include "../brick_game/snake/SnakeModel.h"

class SnakeGameTest : public ::testing::Test {
 protected:
  s21::SnakeModel snake_model_;
  s21::SnakeGameData *snake_game_data_;
};

TEST_F(SnakeGameTest, MoveSnakeUp) {
  snake_model_.SetGameDataDefault();
  snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kUp);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::kUp);
  snake_model_.UpdateData(s21::UserAction::kEscBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kExit);
}

TEST_F(SnakeGameTest, MoveSnakeLeft) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kLeft);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::kLeft);
  snake_model_.UpdateData(s21::UserAction::kEscBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kExit);
}

TEST_F(SnakeGameTest, MoveSnakeRight) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kRight);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::kRight);
  snake_model_.UpdateData(s21::UserAction::kEscBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kExit);
}

TEST_F(SnakeGameTest, MoveSnakeAround) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kRight);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::kRight);
  snake_model_.UpdateData(s21::UserAction::kDown);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::kDown);
  snake_model_.UpdateData(s21::UserAction::kLeft);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::kLeft);
  snake_model_.UpdateData(s21::UserAction::kUp);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::kUp);
  snake_model_.UpdateData(s21::UserAction::kEscBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kExit);
}

TEST_F(SnakeGameTest, AutoMovingUp) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  std::this_thread::sleep_for(std::chrono::milliseconds(510));
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  snake_model_.UpdateData(s21::UserAction::kEscBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kExit);
}

TEST_F(SnakeGameTest, AutoMovingLeft) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kLeft);
  std::this_thread::sleep_for(std::chrono::milliseconds(510));
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  snake_model_.UpdateData(s21::UserAction::kEscBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kExit);
}

TEST_F(SnakeGameTest, AutoMovingRight) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kRight);
  std::this_thread::sleep_for(std::chrono::milliseconds(510));
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  snake_model_.UpdateData(s21::UserAction::kEscBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kExit);
}

TEST_F(SnakeGameTest, AutoMovingDown) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kRight);
  snake_model_.UpdateData(s21::UserAction::kDown);
  std::this_thread::sleep_for(std::chrono::milliseconds(510));
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  snake_model_.UpdateData(s21::UserAction::kEscBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kExit);
}

TEST_F(SnakeGameTest, SetAndCancelPause) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kTabBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kPause);
  snake_model_.UpdateData(s21::UserAction::kTabBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kEscBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kExit);
}

TEST_F(SnakeGameTest, GameOver) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  while (snake_game_data_->game_status != s21::GameState::kGameOver) {
    snake_model_.UpdateData(s21::UserAction::kUp);
  }
}
