#include "controller.h"
namespace s21 {

bool Controller::ValidateExpression(const std::string& expr_infix) {
  return model_math_.ValidityCheck(expr_infix);
}

double Controller::SetAnswer(const std::string& x) {
  return model_math_.CalculateAnswer(x);
}
}  // namespace s21
