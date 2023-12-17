#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"
namespace s21 {

class Controller {
 public:
  bool ValidateExpression(const std::string& expr_infix);
  double SetAnswer(const std::string& x);

 private:
  Model model_math_;
};
}  // namespace s21

#endif  // CONTROLLER_H
