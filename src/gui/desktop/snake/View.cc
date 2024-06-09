
#include "View.h"

#include "ui_View.h"

namespace s21 {

View::View(SnakeController *s_c, TetrisController *t_c, QWidget *parent)
    : QMainWindow(parent),
      ui_(new Ui::View),
      current_game_(CurrentGame::kNone),
      action_(UserAction::kNoSig),
      s_data_(nullptr),
      t_data_(nullptr),
      snake_controller_(s_c),
      tetris_controller_(t_c) {
  ui_->setupUi(this);
  move(1000, 300);
  setWindowTitle("Snake Game");
  ui_->stackedWidget->setCurrentIndex(1);
  tetris_controller_->SetModelDataDefault();
  t_data_ = &tetris_controller_->GetModelData();
  snake_controller_->SetModelDataDefault();
  s_data_ = &snake_controller_->GetModelData();
  m_timer_ = new QTimer(this);
  connect(m_timer_, &QTimer::timeout, this, &View::UpdateAll);
}

View::~View() {
  if (m_timer_ != nullptr) delete m_timer_;
  delete ui_;
}

void View::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  switch (key) {
    case Qt::Key_Left:
      action_ = UserAction::kLeft;
      break;
    case Qt::Key_Right:
      action_ = UserAction::kRight;
      break;
    case Qt::Key_Up:
      action_ = UserAction::kUp;
      break;
    case Qt::Key_Down:
      action_ = UserAction::kDown;
      break;
    case Qt::Key_Enter:
      action_ = UserAction::kEnterBtn;
      break;
    case Qt::Key_Tab:
      action_ = UserAction::kTabBtn;
      break;
    case Qt::Key_Space:
      action_ = UserAction::kSpaceBtn;
      break;
    case Qt::Key_Escape:
      action_ = UserAction::kEscBtn;
      break;
    default:
      break;
  }
}

void View::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);
  if (current_game_ == CurrentGame::kSnake) {
    if (s_data_->game_status != GameState::kGameOver &&
        s_data_->game_status != GameState::kExit) {
      if (s_data_->game_status == GameState::kStart) {
        StartWindowRendering(ui_->SnakeInfoLabel);
      } else if (s_data_->game_status == GameState::kPause) {
        PauseWindowRendering(ui_->SnakeInfoLabel);
      } else {
        ui_->SnakeInfoLabel->setText("");
        SnakeGameRendering();
      }
    } else {
      ClearField();
      GameOver(s_data_->is_victory, s_data_->level, s_data_->curr_score);
    }
  } else if (current_game_ == CurrentGame::kTetris) {
    if (t_data_->t_game_status != GameState::kGameOver &&
        t_data_->t_game_status != GameState::kExit) {
      if (t_data_->t_game_status == GameState::kStart) {
        StartWindowRendering(ui_->TetrisInfoLabel);
      } else if (t_data_->t_game_status == GameState::kPause) {
        PauseWindowRendering(ui_->TetrisInfoLabel);
      } else {
        ui_->TetrisInfoLabel->setText("");
        TetrisGameRendering();
      }
    } else {
      ClearField();
      GameOver(false, t_data_->t_level, t_data_->t_score);
    }
  }
}

void View::ClearField() {
  QPainter painter(this);
  painter.eraseRect(rect());
  painter.end();
}

void View::GameOver(bool is_victory, int level, int score) {
  // current_game_ = CurrentGame::kNone;
  m_timer_->stop();
  ui_->stackedWidget->setCurrentIndex(0);
  if (is_victory) {
    ui_->GameStatus->setText("YOU WON!!!");
  } else {
    ui_->GameStatus->setText("GAME OVER!");
  }
  ui_->MenuCurrScore->setText(QString::number(score));
  ui_->MenuBestScore->setText(QString::number(level));
}

void View::UpdateAll() {
  if (current_game_ == CurrentGame::kSnake) {
    UpdateSnakeModel();
  } else if (current_game_ == CurrentGame::kTetris) {
    UpdateTetrisModel();
  }
  repaint();
}

void View::on_playAgain_clicked() {
  if (current_game_ == CurrentGame::kTetris) {
    tetris_controller_->SetModelDataDefault();
    t_data_ = &tetris_controller_->GetModelData();
    ui_->stackedWidget->setCurrentIndex(3);
    m_timer_->start(10);
  } else if (current_game_ == CurrentGame::kSnake) {
    snake_controller_->SetModelDataDefault();
    s_data_ = &snake_controller_->GetModelData();
    ui_->stackedWidget->setCurrentIndex(2);
    m_timer_->start(10);
  } else if (current_game_ == CurrentGame::kNone) {
    ui_->stackedWidget->setCurrentIndex(1);
  }
}

void View::on_start_snake_btn_clicked() {
  current_game_ = CurrentGame::kSnake;
  snake_controller_->SetModelDataDefault();
  s_data_ = &snake_controller_->GetModelData();
  ui_->stackedWidget->setCurrentIndex(2);
  m_timer_->start(10);
}

void View::on_start_tetris_btn_clicked() {
  current_game_ = CurrentGame::kTetris;
  tetris_controller_->SetModelDataDefault();
  t_data_ = &tetris_controller_->GetModelData();
  ui_->stackedWidget->setCurrentIndex(3);
  m_timer_->start(10);
}

void View::on_exit_btn_clicked() { close(); }

void View::on_closeGame_clicked() {
  current_game_ = CurrentGame::kNone;
  ui_->stackedWidget->setCurrentIndex(1);
}

void View::UpdateSnakeModel() {
  snake_controller_->UpdateModelData(action_);
  s_data_ = &snake_controller_->GetModelData();
  action_ = UserAction::kNoSig;
  ui_->CurrScore->setText(QString::number(s_data_->curr_score));
  ui_->CurrLevel->setText(QString::number(s_data_->level));
  ui_->BestScore->setText(QString::number(s_data_->best_score));
  if (s_data_->game_status == GameState::kGameOver ||
      s_data_->game_status == GameState::kExit) {
    m_timer_->stop();
  }
}

void View::UpdateTetrisModel() {
  tetris_controller_->UpdateModelData(action_);
  t_data_ = &tetris_controller_->GetModelData();
  action_ = UserAction::kNoSig;
  ui_->tetris_curr_score->setText(QString::number(t_data_->t_score));
  ui_->tetris_curr_level->setText(QString::number(t_data_->t_level));
  ui_->tetris_best_score->setText(QString::number(t_data_->t_best_score));
  if (t_data_->t_game_status == GameState::kGameOver ||
      t_data_->t_game_status == GameState::kExit) {
    m_timer_->stop();
  }
}

void View::SnakeGameRendering() {
  QPainter qp(this);
  QImage apple("images/apple.png");

  QRectF appleRect(s_data_->fruit_coord.x * GameSizes::kDotSize,
                   s_data_->fruit_coord.y * GameSizes::kDotSize,
                   GameSizes::kDotSize, GameSizes::kDotSize);
  QImage head("images/snake_head3.png");

  QRectF head_rect(s_data_->snake_coord[0].x * GameSizes::kDotSize,
                   s_data_->snake_coord[0].y * GameSizes::kDotSize,
                   GameSizes::kDotSize, GameSizes::kDotSize);

  QTransform transform;
  int rot = 0;
  if (s_data_->direction == Direction::kDown) {
    rot = 180;
  } else if (s_data_->direction != Direction::kUp) {
    rot = (s_data_->direction == Direction::kLeft ? -90 : 90);
  }
  head = head.transformed(transform.rotate(rot));

  qp.drawImage(appleRect, apple);

  for (std::size_t i = 0; i < s_data_->snake_coord.size(); ++i) {
    qp.setBrush(QColor(148, 195, 76));
    qp.setPen(QColor(148, 195, 76));
    if (i == 0) {
      qp.drawImage(head_rect, head);
    } else {
      qp.drawRect(s_data_->snake_coord[i].x * GameSizes::kDotSize,
                  s_data_->snake_coord[i].y * GameSizes::kDotSize,
                  GameSizes::kDotSize - 1, GameSizes::kDotSize - 1);
    }
  }
  qp.end();
}

void View::TetrisGameRendering() {
  QPainter qp(this);

  qp.setBrush(QColor(90, 90, 90));
  qp.setPen(QColor(0, 0, 0));

  // current tetromino projection
  qp.setBrush(kColors[0]);
  for (const auto &item : t_data_->t_projection.GetCoords()) {
    qp.drawRect((item.x) * GameSizes::kDotSize,
                (item.y - 1) * GameSizes::kDotSize, GameSizes::kDotSize - 1,
                GameSizes::kDotSize - 1);
  }

  qp.setBrush(QColor(148, 195, 76));
  //  qp.setPen(QColor(0, 0, 0));
  // current tetromino
  for (const auto &item : t_data_->t_curr.GetCoords()) {
    qp.setBrush(kColors[(int)t_data_->t_curr.GetShape()]);
    qp.drawRect(item.x * GameSizes::kDotSize,
                (item.y - 1) * GameSizes::kDotSize, GameSizes::kDotSize - 1,
                GameSizes::kDotSize - 1);
  }

  // next tetromino
  for (const auto &item : t_data_->t_next.GetCoords()) {
    qp.setBrush(kColors[(int)t_data_->t_next.GetShape()]);
    qp.drawRect((item.x + 8) * GameSizes::kDotSize,
                (item.y + 2) * GameSizes::kDotSize, GameSizes::kDotSize - 1,
                GameSizes::kDotSize - 1);
  }

  // board
  for (int i = 0; i < GameSizes::kFieldHeight; ++i) {
    for (int j = 0; j < GameSizes::kFieldWidth; ++j) {
      if (t_data_->t_field_[i][j].first) {
        qp.setBrush(kColors[(int)t_data_->t_field_[i][j].second]);
        qp.drawRect(j * GameSizes::kDotSize, i * GameSizes::kDotSize,
                    GameSizes::kDotSize - 1, GameSizes::kDotSize - 1);
      }
    }
  }
  qp.end();
}

void View::StartWindowRendering(QLabel *p_label) {
  p_label->setText("Press space to start");
  p_label->setStyleSheet("border: none;");
}

void View::PauseWindowRendering(QLabel *p_label) {
  p_label->setText(
      "Game on pause.<br> Press Tab to continue<br> or Esc to exit");
}

}  // namespace s21
