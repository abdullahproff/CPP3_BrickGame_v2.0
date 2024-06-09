
#include <gtest/gtest.h>

#include <thread>

#include "../brick_game/tetris/TetrisModel.h"

class TetrisGameTest : public ::testing::Test {
 protected:
  s21::TetrisModel tetris_model_;
  s21::TetrisGameData *tetris_game_data_;
};

TEST_F(TetrisGameTest, MoveLeft) {
  tetris_model_.SetGameDataDefault();
  tetris_game_data_ = &tetris_model_.GetTetrisGameData();
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
  tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

  auto tmp_coords = tetris_game_data_->t_curr.GetCoords();

  tetris_model_.UpdateModelData(s21::UserAction::kLeft);
  tetris_model_.UpdateModelData(s21::UserAction::kLeft);

  for (size_t i = 0; i < tmp_coords.size(); i++) {
    EXPECT_EQ(tmp_coords[i].x - 2, tetris_game_data_->t_curr.GetCoords()[i].x);
  }

  tetris_model_.UpdateModelData(s21::UserAction::kEscBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kExit);
}

TEST_F(TetrisGameTest, MoveRight) {
  tetris_model_.SetGameDataDefault();
  tetris_game_data_ = &tetris_model_.GetTetrisGameData();
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
  tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

  tetris_model_.UpdateModelData(s21::UserAction::kRight);
  tetris_model_.UpdateModelData(s21::UserAction::kRight);
  tetris_model_.UpdateModelData(s21::UserAction::kRight);

  tetris_model_.UpdateModelData(s21::UserAction::kEscBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kExit);
}

TEST_F(TetrisGameTest, MoveDown) {
  tetris_model_.SetGameDataDefault();
  tetris_game_data_ = &tetris_model_.GetTetrisGameData();
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
  tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

  tetris_model_.UpdateModelData(s21::UserAction::kDown);
  tetris_model_.UpdateModelData(s21::UserAction::kDown);
  tetris_model_.UpdateModelData(s21::UserAction::kDown);

  tetris_model_.UpdateModelData(s21::UserAction::kEscBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kExit);
}

TEST_F(TetrisGameTest, Rotate) {
  tetris_model_.SetGameDataDefault();
  tetris_game_data_ = &tetris_model_.GetTetrisGameData();
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
  tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

  tetris_model_.UpdateModelData(s21::UserAction::kUp);
  tetris_model_.UpdateModelData(s21::UserAction::kUp);
  tetris_model_.UpdateModelData(s21::UserAction::kUp);

  tetris_model_.UpdateModelData(s21::UserAction::kEscBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kExit);
}

TEST_F(TetrisGameTest, Drop) {
  tetris_model_.SetGameDataDefault();
  tetris_game_data_ = &tetris_model_.GetTetrisGameData();
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
  tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);

  tetris_model_.UpdateModelData(s21::UserAction::kEscBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kExit);
}

TEST_F(TetrisGameTest, Collide) {
  tetris_model_.SetGameDataDefault();
  tetris_game_data_ = &tetris_model_.GetTetrisGameData();
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
  tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

  for (int i = 0; i < 20; i++) {
    tetris_model_.UpdateModelData(s21::UserAction::kDown);
  }

  tetris_model_.UpdateModelData(s21::UserAction::kEscBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kExit);
}

TEST_F(TetrisGameTest, SetAndCancelPause) {
  tetris_model_.SetGameDataDefault();
  tetris_game_data_ = &tetris_model_.GetTetrisGameData();
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
  tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

  tetris_model_.UpdateModelData(s21::UserAction::kTabBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kPause);

  tetris_model_.UpdateModelData(s21::UserAction::kTabBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

  tetris_model_.UpdateModelData(s21::UserAction::kEscBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kExit);
}

TEST_F(TetrisGameTest, GameOver) {
  tetris_model_.SetGameDataDefault();
  tetris_game_data_ = &tetris_model_.GetTetrisGameData();
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
  tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

  while (tetris_game_data_->t_game_status != s21::GameState::kGameOver) {
    tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  }

  tetris_model_.UpdateModelData(s21::UserAction::kEscBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kExit);
}

TEST_F(TetrisGameTest, AutoMovingDown) {
  tetris_model_.SetGameDataDefault();
  tetris_game_data_ = &tetris_model_.GetTetrisGameData();
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
  tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

  auto tmp_coords = tetris_game_data_->t_curr.GetCoords();

  std::this_thread::sleep_for(std::chrono::milliseconds(510));
  tetris_model_.UpdateModelData(s21::UserAction::kNoSig);

  for (size_t i = 0; i < tmp_coords.size(); i++) {
    EXPECT_EQ(tmp_coords[i].y + 1, tetris_game_data_->t_curr.GetCoords()[i].y);
  }

  tetris_model_.UpdateModelData(s21::UserAction::kEscBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kExit);
}

TEST_F(TetrisGameTest, ClearOneLine) {
  tetris_model_.SetGameDataDefault();
  tetris_game_data_ = &tetris_model_.GetTetrisGameData();
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
  tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

  for (int i = 19; i < 20; ++i) {  // filling 1 lines
    for (int j = 0; j < 10; ++j) {
      tetris_game_data_->t_field_[i][j].first = true;
    }
  }

  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_score, 100);

  tetris_model_.UpdateModelData(s21::UserAction::kEscBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kExit);
}

TEST_F(TetrisGameTest, ClearTwoLines) {
  tetris_model_.SetGameDataDefault();
  tetris_game_data_ = &tetris_model_.GetTetrisGameData();
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
  tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

  for (int i = 18; i < 20; ++i) {  // filling 2 lines
    for (int j = 0; j < 10; ++j) {
      tetris_game_data_->t_field_[i][j].first = true;
    }
  }

  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_score, 300);

  tetris_model_.UpdateModelData(s21::UserAction::kEscBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kExit);
}

TEST_F(TetrisGameTest, ClearThreeLines) {
  tetris_model_.SetGameDataDefault();
  tetris_game_data_ = &tetris_model_.GetTetrisGameData();
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
  tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

  for (int i = 17; i < 20; ++i) {  // filling 3 lines
    for (int j = 0; j < 10; ++j) {
      tetris_game_data_->t_field_[i][j].first = true;
    }
  }

  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_score, 700);

  tetris_model_.UpdateModelData(s21::UserAction::kEscBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kExit);
}

TEST_F(TetrisGameTest, ClearFourLines) {
  tetris_model_.SetGameDataDefault();
  tetris_game_data_ = &tetris_model_.GetTetrisGameData();
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
  tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

  for (int i = 16; i < 20; ++i) {  // filling 4 lines
    for (int j = 0; j < 10; ++j) {
      tetris_game_data_->t_field_[i][j].first = true;
    }
  }

  tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(tetris_game_data_->t_score, 1500);

  tetris_model_.UpdateModelData(s21::UserAction::kEscBtn);
  EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kExit);
}
