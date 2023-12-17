#ifndef MODEL_H
#define MODEL_H

#include <math.h>

#include <iostream>
#include <regex>
#include <stack>
#include <string>

namespace s21 {

typedef struct Operator {
  char oper = '\0';
  int prior = 0;
} Operator;

typedef struct CalcStack {
  std::string sym_stack;
  std::stack<double> num_stack;
} CalcStack;
class Model {
 public:
  double CalculateAnswer(const std::string& x);
  bool ValidityCheck(const std::string& expr_infix);

 private:
  void Conversion();
  void Calc();
  void DeleteData();
  int ChangeFunc(size_t* i);
  void Change();
  void ENotation(char next_sym);
  bool UnaryPars(size_t index);
  void Parser();
  void PushNum(size_t* i);
  bool Function(char func);
  double CalcFunc(double operand, char func);
  double PerformOperation(double operand_a, double operand_b, char oper_);
  double CalcExpr(char oper_);
  bool IsDigit(char sym);
  bool UnaryOper(std::string str, size_t index);
  void AddNumber(size_t i);
  void AddOperator(char oper_);
  int OperPriority(char c);
  void PushOperator(char oper_);
  bool Validator();
  bool AnotherValidator(size_t i);
  bool CheckENotation(size_t i);
  bool AfterTheNumber(char symbol);
  bool CheckOperAndOpenOrClosePar(size_t i);
  bool CheckFuncAndOpenPar(size_t i);
  bool WrongPlusOrMinusAndParent();
  bool SingleOper(char oper_);
  bool OperAndClosingParent(char oper_);
  bool PlusOrMinus(char oper_);
  bool NumberOrFunction(char sym);
  bool Operators(char oper_);
  bool OperAndOpenParent(char oper_);
  size_t expr_infix_size_;
  std::string expr_infix_;
  std::string change_func_;
  std::string expr_pars_;
  std::string pol_notation_;
  std::stack<Operator> stack_oper_;
  CalcStack calc_stack_;
  std::string x_;
  std::regex reg_plus_minus_{
      ("---|\\+\\+\\+|-\\+\\-|\\+\\-\\+|--\\+|\\+\\+\\-|\\(\\+\\-|\\(\\-\\+|\\("
       "\\+\\+|\\(\\--|--\\)|\\+\\+\\)|\\+\\-\\)|-\\+\\)")};
  double answer_;
};
}  // namespace s21

#endif  // MODEL_H
