
#include "BaseView.h"

namespace s21 {

void BaseView::GameFieldRendering(Choose curr_game, int level, int score,
                                  int record) {
  // Window borders
  DrawBox(0, 0, GameSizes::kWindowHeight, GameSizes::kWindowWidth);
  // Game field borders
  DrawBox(0, 0, GameSizes::kFieldHeight + 1, GameSizes::kFieldWidth + 1);
  // Верхний правый угол
  mvaddch(0, GameSizes::kFieldWidth + 1, ACS_TTEE);
  // Нижний правый угол
  mvaddch(GameSizes::kFieldHeight + 1, GameSizes::kFieldWidth + 1, ACS_BTEE);

  int side_panel_h = 1;
  if (curr_game == Choose::kTetris) {
    side_panel_h = GameSizes::kSidePanelHeight;
    // next tetromino
    DrawBox(1, GameSizes::kFieldWidth + 2, side_panel_h,
            GameSizes::kWindowWidth - 1);
    mvprintw(1, GameSizes::kFieldWidth + 3, "Next");
    side_panel_h += 1;
  }

  // level
  DrawBox(side_panel_h, GameSizes::kFieldWidth + 2, side_panel_h + 2,
          GameSizes::kWindowWidth - 1);
  mvprintw(side_panel_h, GameSizes::kFieldWidth + 3, "Level");
  mvprintw(side_panel_h + 1, GameSizes::kFieldWidth + 8, "%d", level);
  side_panel_h += 3;

  // score
  DrawBox(side_panel_h, GameSizes::kFieldWidth + 2, side_panel_h + 2,
          GameSizes::kWindowWidth - 1);
  mvprintw(side_panel_h, GameSizes::kFieldWidth + 3, "Score");
  mvprintw(side_panel_h + 1,
           GameSizes::kFieldWidth + 9 -
               static_cast<int>(std::to_string(score).length()),
           "%d", score);
  side_panel_h += 3;

  // record
  DrawBox(side_panel_h, GameSizes::kFieldWidth + 2, side_panel_h + 2,
          GameSizes::kWindowWidth - 1);
  mvprintw(side_panel_h, GameSizes::kFieldWidth + 3, "Record");
  mvprintw(side_panel_h + 1,
           GameSizes::kFieldWidth + 9 -
               static_cast<int>(std::to_string(record).length()),
           "%d", record);
}

void BaseView::GameResultRendering(bool is_victory, int level, int score) {
  clear();
  DrawBox(0, 0, GameSizes::kWindowHeight, GameSizes::kWindowWidth);
  if (is_victory) {
    mvprintw(2, GameSizes::kWindowWidth / 2 - 4, "YOU WIN!");
  } else {
    mvprintw(2, GameSizes::kWindowWidth / 2 - 5, "GAME OVER!");
  }
  mvprintw(4, GameSizes::kWindowWidth / 2 - 7, "Your score: %d", score);
  mvprintw(6, GameSizes::kWindowWidth / 2 - 7, "Your level: %d", level);
  mvprintw(8, GameSizes::kWindowWidth / 2 - 6, "Press any key");
  mvprintw(9, GameSizes::kWindowWidth / 2 - 5, "to continue");
  nodelay(stdscr, FALSE);
  getch();
}

void BaseView::DrawBox(int topLeftY, int topLeftX, int bottomRightY,
                       int bottomRightX) {
  // Borders
  for (int i = topLeftY; i <= bottomRightY; ++i) {
    mvaddch(i, topLeftX, ACS_VLINE);      // left
    mvaddch(i, bottomRightX, ACS_VLINE);  // right
  }
  for (int i = topLeftX; i <= bottomRightX; ++i) {
    mvaddch(topLeftY, i, ACS_HLINE);      // up
    mvaddch(bottomRightY, i, ACS_HLINE);  // down
  }
  // corners
  mvaddch(topLeftY, topLeftX, ACS_ULCORNER);
  mvaddch(topLeftY, bottomRightX, ACS_URCORNER);
  mvaddch(bottomRightY, topLeftX, ACS_LLCORNER);
  mvaddch(bottomRightY, bottomRightX, ACS_LRCORNER);
}

UserAction BaseView::GetAction() {
  UserAction action = UserAction::kNoSig;
  int key = getch();
  switch (key) {
    case KEY_LEFT:
      action = UserAction::kLeft;
      break;
    case KEY_RIGHT:
      action = UserAction::kRight;
      break;
    case KEY_UP:
      action = UserAction::kUp;
      break;
    case KEY_DOWN:
      action = UserAction::kDown;
      break;
    case 13:  // Enter
      action = UserAction::kEnterBtn;
      break;
    case 9:  // Left tab
      action = UserAction::kTabBtn;
      break;
    case 32:  // Space
      action = UserAction::kSpaceBtn;
      break;
    case 27:  // ESC key
      action = UserAction::kEscBtn;
      break;
    default:
      break;
  }
  nodelay(stdscr, TRUE);
  return action;
}

void BaseView::PauseRendering(int level, int score) {
  clear();
  DrawBox(0, 0, GameSizes::kWindowHeight, GameSizes::kWindowWidth);

  mvprintw(5, GameSizes::kWindowWidth / 2 - 10, "The game is on pause");
  mvprintw(8, GameSizes::kWindowWidth / 2 - 7, "Your score:  %d", score);
  mvprintw(10, GameSizes::kWindowWidth / 2 - 7, "Your level:  %d", level);

  mvprintw(12, GameSizes::kWindowWidth / 2 - 10, "Press Tab to continue");
  mvprintw(13, GameSizes::kWindowWidth / 2 - 7, "or Esc to exit");
  nodelay(stdscr, FALSE);
}

void BaseView::StartGameRendering() {
  clear();
  DrawBox(0, 0, GameSizes::kWindowHeight, GameSizes::kWindowWidth);
  mvprintw(9, GameSizes::kWindowWidth / 2 - 6, "Press spase");
  mvprintw(10, GameSizes::kWindowWidth / 2 - 7, "to start game");
  mvprintw(11, GameSizes::kWindowWidth / 2 - 7, "Or Esc to exit");
  nodelay(stdscr, FALSE);
}

void BaseView::MenuRendering(std::size_t &selectedItem) {
  clear();

  int start_y = 10;
  int start_x = GameSizes::kWindowWidth / 2;

  DrawBox(0, 0, GameSizes::kWindowHeight, GameSizes::kWindowWidth);
  mvprintw(start_y - 4, start_x - 4, "Game Menu");

  std::vector<std::string> choices = {"Snake", "Tetris", "Exit"};

  for (std::size_t i = 0; i < choices.size(); ++i) {
    if (i == selectedItem) {
      attron(A_REVERSE);
      mvprintw(++start_y + i, start_x - (int)choices[i].length() / 2, "%s",
               choices[i].c_str());
      attroff(A_REVERSE);
    } else {
      mvprintw(++start_y + i, start_x - (int)choices[i].length() / 2, "%s",
               choices[i].c_str());
    }
  }

  refresh();
}

Choose BaseView::InitMenu() {
  Choose ret_val = Choose::kMenu;
  std::size_t selectedItem = 0;

  MenuRendering(selectedItem);

  int ch = 0;
  nodelay(stdscr, FALSE);
  while ((ch = getch()) != '\n') {
    switch (ch) {
      case KEY_UP:
        selectedItem =
            (selectedItem == 0) ? (selectedItem) : (selectedItem - 1);
        break;
      case KEY_DOWN:
        selectedItem =
            (selectedItem == 2) ? (selectedItem) : (selectedItem + 1);
        break;
    }
    MenuRendering(selectedItem);
  }

  if (selectedItem == 0) {
    ret_val = Choose::kSnake;
  } else if (selectedItem == 1) {
    ret_val = Choose::kTetris;
  } else if (selectedItem == 2) {
    ret_val = Choose::kExit;
  }
  return ret_val;
}

}  // namespace s21
