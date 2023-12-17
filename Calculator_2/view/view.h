#ifndef VIEW_H
#define VIEW_H

#include <graph.h>

#include <QDoubleValidator>
#include <QMainWindow>
#include <QRegularExpression>
#include <QtDebug>

#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

 private slots:
  void digits_numbers();
  void digits_func();
  void digits_numbers_x();
  QString last_substring_(QString const &str_reg);
  bool last_symbol_is_a_number_(QString const &str_reg);
  void on_dot_clicked();
  void on_delete_2_clicked();
  void on_backspace_clicked();
  void on_backspace_x_clicked();
  void on_equals_clicked();
  void on_dot_x_clicked();

 private:
  QString const kRegLastChar = "[0-9]";
  QString const kRegForDot = "[0-9.]+";
  QString const kRegForBackspace =
      "(0|1|2|3|4|5|6|7|8|9|\\.|\\(|\\)|\\/"
      "|\\*|\\-|\\+|\\^|X|sin|asin|acos|atan|sqrt|ln|cos|mod|tan|log)";
  Controller controller_;
  Ui::View *ui;
  std::string x_value_ = " ";
  Graph *graph_;
};
}  // namespace s21
#endif  // VIEW_H
