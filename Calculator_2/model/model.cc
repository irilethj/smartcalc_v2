#include "model.h"

namespace s21 {

bool Model::IsDigit(char sym) {
  return (((sym >= 48) && (sym <= 57)) || (sym == 46));
}

bool Model::UnaryOper(std::string str, size_t index) {
  size_t i = index;
  bool unary = (str[i] == '-' || str[i] == '+');
  bool next_number = ((str[i + 1] >= 48) && (str[i + 1] <= 57));
  return (unary && next_number);
}

void Model::AddNumber(size_t i) {
  bool next_number = IsDigit(expr_pars_[i + 1]);
  pol_notation_ += expr_pars_[i];
  if (!next_number) {
    pol_notation_ += ' ';
  }
}

void Model::AddOperator(char oper_) {
  pol_notation_ += oper_;
  pol_notation_ += ' ';
}

int Model::OperPriority(char c) {
  int res = 0;
  bool function =
      ((c == 's') || (c == 'c') || (c == 't') || (c == 'S') || (c == 'C') ||
       (c == 'T') || (c == 'q') || (c == 'l') || (c == 'L'));
  if (c == '(' || c == ')') {
    res = 6;
  } else if (c == '+' || c == '-') {
    res = 2;
  } else if (c == '*' || c == '/' || c == 'm') {
    res = 3;
  } else if (c == '^') {
    res = 4;
  } else if (function) {
    res = 5;
  }
  return res;
}

// добавляет оператор в стек при переводе на польку
void Model::PushOperator(char oper_) {
  Operator curr_oper;
  curr_oper.oper = oper_;
  curr_oper.prior = OperPriority(oper_);
  if ((oper_ != ')') && ((curr_oper.prior > stack_oper_.top().prior) ||
                         (stack_oper_.top().oper == '('))) {
    stack_oper_.push(curr_oper);
  } else if (oper_ == ')') {
    while (stack_oper_.top().oper != '(') {
      AddOperator(stack_oper_.top().oper);
      stack_oper_.pop();
    }
    stack_oper_.pop();
  } else {
    while ((curr_oper.prior <= stack_oper_.top().prior) &&
           (stack_oper_.top().oper != '(')) {
      AddOperator(stack_oper_.top().oper);
      stack_oper_.pop();
    }
    stack_oper_.push(curr_oper);
  }
}

void Model::Conversion() {
  Operator bottom;
  stack_oper_.push(bottom);
  bool num = false;
  bool unary = false;
  for (size_t i = 0; i < expr_pars_.size(); ++i) {
    num = IsDigit(expr_pars_[i]);
    unary = UnaryOper(expr_pars_, i);
    if (num || unary) {
      AddNumber(i);
    } else if (expr_pars_[i] != ' ') {
      PushOperator(expr_pars_[i]);
    }
  }
  while (stack_oper_.top().prior != 0) {
    AddOperator(stack_oper_.top().oper);
    stack_oper_.pop();
  }
}

// добавляет число или унарный оператор по символьно в стек символов, преобразут
// в double и добавляет в стек чисел
void Model::PushNum(size_t* i) {
  bool num = true;
  while (num) {
    calc_stack_.sym_stack += pol_notation_[*i];
    ++(*i);
    num = IsDigit(pol_notation_[*i]);
  }
  calc_stack_.num_stack.push(std::stod(calc_stack_.sym_stack));
  calc_stack_.sym_stack.clear();
}

bool Model::Function(char func) {
  return ((func == 's') || (func == 'c') || (func == 't') || (func == 'S') ||
          (func == 'C') || (func == 'T') || (func == 'q') || (func == 'l') ||
          (func == 'L'));
}

double Model::CalcFunc(double operand, char func) {
  double res = 0;
  if (func == 's') {
    res = sin(operand);
  } else if (func == 'c') {
    res = cos(operand);
  } else if (func == 't') {
    res = tan(operand);
  } else if (func == 'S') {
    res = asin(operand);
  } else if (func == 'C') {
    res = acos(operand);
  } else if (func == 'T') {
    res = atan(operand);
  } else if (func == 'q') {
    res = sqrt(operand);
  } else if (func == 'l') {
    res = log(operand);
  } else if (func == 'L') {
    res = log10(operand);
  }
  return res;
}

double Model::PerformOperation(double operand_a, double operand_b, char oper_) {
  double res = 0;
  if (oper_ == '+') {
    res = operand_a + operand_b;
  } else if (oper_ == '-') {
    res = operand_a - operand_b;
  } else if (oper_ == '*') {
    res = operand_a * operand_b;
  } else if (oper_ == '/') {
    res = operand_a / operand_b;
  } else if (oper_ == 'm') {
    res = fmod(operand_a, operand_b);
  } else if (oper_ == '^') {
    res = pow(operand_a, operand_b);
  }
  return res;
}

// вычисляет выражение
double Model::CalcExpr(char oper_) {
  bool function = Function(oper_);
  double a = 0;
  double b = 0;
  double res_ = 0;
  if (function) {
    if (!calc_stack_.num_stack.empty()) {
      a = calc_stack_.num_stack.top();
      calc_stack_.num_stack.pop();
      res_ = CalcFunc(a, oper_);
    }
  } else {
    if (!calc_stack_.num_stack.empty()) {
      b = calc_stack_.num_stack.top();
      calc_stack_.num_stack.pop();
    }
    if (!calc_stack_.num_stack.empty()) {
      a = calc_stack_.num_stack.top();
      calc_stack_.num_stack.pop();
      res_ = PerformOperation(a, b, oper_);
    }
  }
  return res_;
}

void Model::Calc() {
  size_t i = 0;
  bool num = false;
  bool unary = false;
  while (i < pol_notation_.size()) {
    num = IsDigit(pol_notation_[i]);
    unary = UnaryOper(pol_notation_, i);
    if (num || unary) {
      PushNum(&i);
    } else if (pol_notation_[i] != ' ') {
      calc_stack_.num_stack.push(CalcExpr(pol_notation_[i]));
      ++i;
    } else {
      ++i;
    }
  }
  answer_ = calc_stack_.num_stack.top();
  calc_stack_.num_stack.pop();
}

void Model::ENotation(char next_sym) {
  std::string replase = "* 10 ^ ";
  replase += next_sym;
  expr_pars_ += replase;
}

bool Model::UnaryPars(size_t index) {
  bool res = false;
  size_t i = index;
  if (!i && PlusOrMinus(change_func_[i])) {
    res = true;
  } else if (i) {
    bool oper_ = (OperAndOpenParent(change_func_[i - 1]) ||
                  PlusOrMinus(change_func_[i - 1]));
    if (oper_ && PlusOrMinus(change_func_[i])) {
      res = true;
    }
  }
  return res;
}

void Model::Parser() {
  bool num = false;
  bool next_num = false;
  bool unary = false;
  for (size_t i = 0; i < change_func_.size(); ++i) {
    num = IsDigit(change_func_[i]);
    next_num = IsDigit(change_func_[i + 1]);
    unary = UnaryPars(i);
    if (change_func_[i] == 'e') {
      ENotation(change_func_[i + 1]);
      ++i;
    } else {
      expr_pars_ += change_func_[i];
      if (num && !next_num) {
        expr_pars_ += ' ';
      } else if ((change_func_[i] == 'm') && PlusOrMinus(change_func_[i + 1])) {
        expr_pars_ += ' ';
        ++i;
      } else if (!num && !unary) {
        expr_pars_ += ' ';
      } else if (unary) {
        expr_pars_ += "1 * ";
      }
    }
  }
}

int Model::ChangeFunc(size_t* i) {
  int res = 0;
  char sym = expr_infix_[*i];
  char next_sym = expr_infix_[*i + 1];
  if (sym == 'm') {
    res = 'm';
    *i += 2;
  } else if (sym == 's' && next_sym == 'i') {
    res = 's';
    *i += 2;
  } else if (sym == 'c') {
    res = 'c';
    *i += 2;
  } else if (sym == 't') {
    res = 't';
    *i += 2;
  } else if (sym == 's' && next_sym == 'q') {
    res = 'q';
    *i += 3;
  } else if (sym == 'a' && next_sym == 's') {
    res = 'S';
    *i += 3;
  } else if (sym == 'a' && next_sym == 'c') {
    res = 'C';
    *i += 3;
  } else if (sym == 'a' && next_sym == 't') {
    res = 'T';
    *i += 3;
  } else if (sym == 'l' && next_sym == 'n') {
    res = 'l';
    *i += 1;
  } else if (sym == 'l' && next_sym == 'o') {
    res = 'L';
    *i += 2;
  }
  return res;
}

void Model::Change() {
  int changed = 0;
  for (size_t i = 0; i < expr_infix_size_; ++i) {
    changed = ChangeFunc(&i);
    if (expr_infix_[i] == 'X') {
      change_func_ += x_;
    } else if (!changed) {
      change_func_ += expr_infix_[i];
    } else {
      change_func_ += changed;
    }
  }
}

bool Model::CheckOperAndOpenOrClosePar(size_t i) {
  char sym = expr_infix_[i];
  bool res = true;
  if (i && (sym == '*' || sym == '/' || sym == '^') &&
      ((expr_infix_[i - 1] == '(') || (expr_infix_[i + 1] == ')'))) {
    res = false;
  } else if (i && (sym == 'm') &&
             ((expr_infix_[i - 1] == '(') || (expr_infix_[i + 3] == ')'))) {
    res = false;
  }

  return res;
}

bool Model::CheckFuncAndOpenPar(size_t i) {
  bool res = true;
  char sym = expr_infix_[i];
  char next_sym = expr_infix_[i + 1];
  if (((sym == 's' && next_sym == 'i') || (sym == 'c' && next_sym == 'o') ||
       (sym == 't' && next_sym == 'a') || (sym == 'l' && next_sym == 'o')) &&
      (expr_infix_[i + 3] != '(')) {
    res = false;
  } else if ((sym == 'l' && next_sym == 'n') && (expr_infix_[i + 2] != '(')) {
    res = false;
  } else if ((sym == 's' && next_sym == 'q') && (expr_infix_[i + 4] != '(')) {
    res = false;
  }
  return res;
}

bool Model::WrongPlusOrMinusAndParent() {
  if (std::regex_search(expr_infix_, reg_plus_minus_)) {
    return false;
  }
  return true;
}

bool Model::SingleOper(char oper_) {
  return (oper_ == '*' || oper_ == '/' || oper_ == '-' || oper_ == '+' ||
          oper_ == '(' || oper_ == 'd' || oper_ == '^' || oper_ == 't' ||
          oper_ == 'n' || oper_ == 's' || oper_ == 'g');
}

bool Model::OperAndClosingParent(char oper_) {
  return (oper_ == '*' || oper_ == '/' || oper_ == 'm' || oper_ == '^' ||
          oper_ == ')');
}

bool Model::OperAndOpenParent(char oper_) {
  return (oper_ == '*' || oper_ == '/' || oper_ == '^' || oper_ == '(');
}

bool Model::PlusOrMinus(char oper_) { return (oper_ == '+' || oper_ == '-'); }

bool Model::NumberOrFunction(char sym) {
  return (IsDigit(sym) || Function(sym));
}

bool Model::Operators(char oper_) {
  return (oper_ == '*' || oper_ == '/' || oper_ == 'm' || oper_ == '^');
}

bool Model::AfterTheNumber(char symbol) {
  bool res = false;
  if (IsDigit(symbol)) {
    res = true;
  } else if ((Operators(symbol) || PlusOrMinus(symbol) || symbol == 'e')) {
    res = true;
  } else if ((symbol == ')') || (symbol == ' ')) {
    res = true;
  }
  return res;
}

bool Model::ValidityCheck(const std::string& expr_infix) {
  expr_infix_ = expr_infix;
  expr_infix_size_ = expr_infix_.size();
  expr_infix_ += "     ";
  if (!Validator()) {
    return false;
  }
  return true;
}

bool Model::CheckENotation(size_t i) {
  bool res = true;
  if (!i) {
    res = false;
  } else if (i && (!IsDigit(expr_infix_[i - 1]))) {
    res = false;
  } else if ((!IsDigit(expr_infix_[i + 1])) &&
             (!PlusOrMinus(expr_infix_[i + 1]))) {
    res = false;
  } else if ((PlusOrMinus(expr_infix_[i + 1])) &&
             (!IsDigit(expr_infix_[i + 2]))) {
    res = false;
  }
  return res;
}

bool Model::AnotherValidator(size_t i) {
  bool res = true;
  if ((expr_infix_[i] == 'e') && (!CheckENotation(i))) {
    res = false;
  } else if (Operators(expr_infix_[i]) && PlusOrMinus(expr_infix_[i + 1]) &&
             !NumberOrFunction(expr_infix_[i + 2])) {
    res = false;
  } else if (SingleOper(expr_infix_[i]) && (expr_infix_[i + 1] == ' ')) {
    res = false;
  } else if ((expr_infix_[i] == '(') && (expr_infix_[i + 1] == ')')) {
    res = false;
  } else if (expr_infix_[i] == '!') {
    res = false;
  } else if (Operators(expr_infix_[i]) && Operators(expr_infix_[i + 1])) {
    res = false;
  } else if (expr_infix_[i] == '.' && expr_infix_[i + 1] == '.') {
    res = false;
  } else if (expr_infix_[i] == 'f') {
    res = false;
  } else if ((expr_infix_[i] == 'n') && (expr_infix_[i + 1] == 'a')) {
    res = false;
  }
  return res;
}

bool Model::Validator() {
  bool res = true;
  int open_par = 0;
  int clos_par = 0;
  if (!WrongPlusOrMinusAndParent()) {
    return false;
  }
  for (size_t i = 0; i < expr_infix_size_; ++i) {
    if (expr_infix_[i] == '(') {
      ++open_par;
    } else if (expr_infix_[i] == ')') {
      ++clos_par;
    }
    if ((expr_infix_[i] == ')') && (clos_par > open_par)) {
      res = false;
    } else if (!CheckFuncAndOpenPar(i)) {
      res = false;
    } else if (!CheckOperAndOpenOrClosePar(i)) {
      res = false;
    } else if (!i && OperAndClosingParent(expr_infix_[i])) {
      res = false;
    } else if (!i && PlusOrMinus(expr_infix_[i]) &&
               (!NumberOrFunction(expr_infix_[i + 1]) &&
                expr_infix_[i + 1] != '(')) {
      res = false;
    } else if (IsDigit(expr_infix_[i]) && !AfterTheNumber(expr_infix_[i + 1])) {
      res = false;
    } else if (PlusOrMinus(expr_infix_[i]) &&
               OperAndClosingParent(expr_infix_[i + 1])) {
      res = false;
    } else if (!AnotherValidator(i)) {
      res = false;
    }
  }
  if (open_par != clos_par) {
    res = false;
  }
  return res;
}

double Model::CalculateAnswer(const std::string& x) {
  x_ = x;
  Change();
  Parser();
  Conversion();
  Calc();
  DeleteData();
  return answer_;
}

void Model::DeleteData() {
  change_func_.clear();
  expr_pars_.clear();
  pol_notation_.clear();
  calc_stack_.sym_stack.clear();
}
}  // namespace s21
