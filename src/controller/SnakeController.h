
#ifndef CPP3_BRICKGAME_V2_0_1_SRC_CONTROLLER_SNAKECONTROLLER_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_CONTROLLER_SNAKECONTROLLER_H_

#include "../brick_game/snake/SnakeModel.h"

namespace s21 {

class SnakeController {
 public:
  SnakeController(SnakeModel *model) : model_(model) {}
  ~SnakeController() = default;

  void UpdateModelData(UserAction action = UserAction::kUp) {
    model_->UpdateData(action);
  }

  void SetModelDataDefault() { model_->SetGameDataDefault(); }
  SnakeGameData &GetModelData() { return model_->GetModelData(); }

 private:
  SnakeModel *model_;
};

}  // namespace s21
#endif  // CPP3_BRICKGAME_V2_0_1_SRC_CONTROLLER_SNAKECONTROLLER_H_
