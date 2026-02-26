#ifndef SRC_S21_CALC_MODEL_H
#define SRC_S21_CALC_MODEL_H

#include <string>

namespace s21 {
class CalcModel {
 public:
  CalcModel() = default;
  ~CalcModel() = default;

    long double Calculate(std::string s_, std::string x_);
};
}  // namespace s21

#endif  // SRC_S21_CALC_MODEL_H