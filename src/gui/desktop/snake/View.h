
#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_DESKTOP_SNAKEVIEW_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_DESKTOP_SNAKEVIEW_H_

#include <QDebug>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QString>
#include <QTimer>
#include <QWidget>

#include "../../../controller/SnakeController.h"
#include "../../../controller/TetrisController.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

enum class CurrentGame { kNone, kSnake, kTetris };

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(SnakeController *s_c, TetrisController *t_c, QWidget *parent = nullptr);
  ~View();

  const QColor kColors[8] = {
      QColor(147, 147, 147),  // gray
      QColor(255, 0, 0),      // red
      QColor(103, 250, 0),    // green
      QColor(5, 240, 250),    // cyan
      QColor(250, 5, 249),    // purple
      QColor(250, 235, 5),    // yellow
      QColor(250, 124, 5),    // orange
      QColor(5, 20, 250),     // blue
  };

 protected:
  void keyPressEvent(QKeyEvent *) override;
  void paintEvent(QPaintEvent *event) override;

 private slots:
  void on_playAgain_clicked();
  void on_closeGame_clicked();
  void on_start_tetris_btn_clicked();
  void on_start_snake_btn_clicked();
  void on_exit_btn_clicked();

 private:
  QTimer *m_timer_;
  Ui::View *ui_;
  CurrentGame current_game_{};
  UserAction action_{};
  SnakeGameData *s_data_;
  TetrisGameData *t_data_;
  SnakeController *snake_controller_;
  TetrisController *tetris_controller_;

  void ClearField();
  void GameOver(bool is_victory, int level, int score);
  void UpdateAll();
  void UpdateSnakeModel();
  void UpdateTetrisModel();
  void TetrisGameRendering();
  void SnakeGameRendering();
  static void StartWindowRendering(QLabel *p_label);
  static void PauseWindowRendering(QLabel *p_label);
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_GUI_DESKTOP_SNAKEVIEW_H_
