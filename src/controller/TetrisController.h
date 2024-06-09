
#ifndef CPP3_BRICKGAME_V2_0_1_TETRISCONTROLLER_H
#define CPP3_BRICKGAME_V2_0_1_TETRISCONTROLLER_H

#include "../brick_game/tetris/TetrisModel.h"

namespace s21 {

class TetrisController {
 public:
  explicit TetrisController(TetrisModel *model = nullptr) : model_(model) {}
  ~TetrisController() = default;

  void UpdateModelData(UserAction act = UserAction::kNoSig) {
    model_->UpdateModelData(act);
  }

  void SetModelDataDefault() { model_->SetGameDataDefault(); }
  TetrisGameData &GetModelData() { return model_->GetTetrisGameData(); }

 private:
  TetrisModel *model_;
};

}  // namespace s21
#endif  // CPP3_BRICKGAME_V2_0_1_TETRISCONTROLLER_H
