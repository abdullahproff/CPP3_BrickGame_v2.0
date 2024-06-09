
#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_TETRIS_CONSOLE_TETRISCONSOLEVIEW_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_TETRIS_CONSOLE_TETRISCONSOLEVIEW_H_

#include "../../controller/TetrisController.h"
#include "../common/BaseView.h"

namespace s21 {

class TetrisConsoleView : public BaseView {
 public:
  explicit TetrisConsoleView(TetrisController *c = nullptr);
  void Start() override;

 private:
  UserAction t_action_;

  TetrisGameData *t_data_;
  TetrisController *controller_;
  void TetrisMainLoop();
  void ModelConnect();
  void GameRendering();
  void Rendering();
};

}  // namespace s21
#endif  // CPP3_BRICKGAME_V2_0_1_SRC_GUI_TETRIS_CONSOLE_TETRISCONSOLEVIEW_H_
