#ifndef SRC_S21_CALC_CONTROLLER_H
#define SRC_S21_CALC_CONTROLLER_H

#include "./../model/model.h"

namespace s21 {
class CalcController {
 public:
  CalcController() = default;
  ~CalcController() = default;

  long double Calculate(std::string s_, std::string x_) { 
    expression_.Calculate(s_, x_); }
    

 private:
  CalcModel expression_;

};  // CalcController

}  // namespace s21

#endif  // SRC_S21_CALC_CONTROLLER_H