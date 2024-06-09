
#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_COMMON_BASEMODEL_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_COMMON_BASEMODEL_H_

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>

#include "Constants.h"
namespace s21 {

class BaseModel {
 public:
  static long long GetCurrTime() {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    return ms.count();
  }

  static void SaveScore(int score, const std::string &file_name) {
    std::ofstream file(file_name);
    if (file.is_open()) {
      file << score;
      file.close();
    }
  }

  static int LoadScore(const std::string &file_name) {
    int score = 0;
    std::ifstream file(file_name);
    if (file.is_open()) {
      file >> score;
      file.close();
    }
    return score;
  }
};

}  // namespace s21
#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_COMMON_BASEMODEL_H_
