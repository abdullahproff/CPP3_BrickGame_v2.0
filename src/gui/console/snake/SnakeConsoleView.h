

#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_CONSOLE_SNAKECONSOLEVIEW_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_CONSOLE_SNAKECONSOLEVIEW_H_

#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "../../controller/SnakeController.h"
#include "../common/BaseView.h"

namespace s21 {

class SnakeConsoleView : public BaseView {
 public:
  explicit SnakeConsoleView(SnakeController *c);
  ~SnakeConsoleView() = default;

  void Start() override;

 private:
  void Rendering();
  void SnakeMainLoop();
  void ModelConnect();
  void GameRendering();

  UserAction action_{};
  SnakeGameData *data_;
  SnakeController *controller_;
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_GUI_CONSOLE_SNAKECONSOLEVIEW_H_
