#include "view.h"

#include "ui_view.h"
namespace s21 {
View::View(QWidget *parent) : QMainWindow(parent), ui(new Ui::View) {
  ui->setupUi(this);
  connect(ui->zero_x, SIGNAL(clicked()), this, SLOT(digits_numbers_x()));
  connect(ui->one_x, SIGNAL(clicked()), this, SLOT(digits_numbers_x()));
  connect(ui->two_x, SIGNAL(clicked()), this, SLOT(digits_numbers_x()));
  connect(ui->three_x, SIGNAL(clicked()), this, SLOT(digits_numbers_x()));
  connect(ui->four_x, SIGNAL(clicked()), this, SLOT(digits_numbers_x()));
  connect(ui->five_x, SIGNAL(clicked()), this, SLOT(digits_numbers_x()));
  connect(ui->six_x, SIGNAL(clicked()), this, SLOT(digits_numbers_x()));
  connect(ui->seven_x, SIGNAL(clicked()), this, SLOT(digits_numbers_x()));
  connect(ui->eight_x, SIGNAL(clicked()), this, SLOT(digits_numbers_x()));
  connect(ui->nine_x, SIGNAL(clicked()), this, SLOT(digits_numbers_x()));

  connect(ui->zero, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->one, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->two, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->three, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->four, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->five, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->six, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->seven, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->eight, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->nine, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->add, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->sub, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->mul, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->division, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->root, SIGNAL(clicked()), this, SLOT(digits_func()));
  connect(ui->degree, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(digits_func()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(digits_func()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(digits_func()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(digits_func()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(digits_func()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(digits_func()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(digits_func()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(digits_func()));
  connect(ui->bracket_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->bracket_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->variable_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->e_notation, SIGNAL(clicked()), this, SLOT(digits_numbers()));
}

View::~View() { delete ui; }

void View::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString input = ui->result_show->text();
  if (input == "0") {
    ui->result_show->clear();
  }
  QString newlabel = ui->result_show->text() + button->text();
  ui->result_show->setText(newlabel);
}

void View::digits_func() {
  QPushButton *button = (QPushButton *)sender();
  QString input = ui->result_show->text();
  if (input == "0") {
    ui->result_show->clear();
  }
  QString newlabel = ui->result_show->text() + button->text() + "(";
  ui->result_show->setText(newlabel);
}

void View::digits_numbers_x() {
  QPushButton *button_x = (QPushButton *)sender();
  QString newlabel_x = ui->input_x->text() + button_x->text();
  ui->input_x->setText(newlabel_x);
}

void View::on_delete_2_clicked() {
  ui->result_show->setText("0");
  ui->input_x->setText("");
}

void View::on_dot_clicked() {
  if (last_symbol_is_a_number_(kRegLastChar)) {
    QString str_last_match = last_substring_(kRegForDot);
    qDebug() << str_last_match;
    if (!str_last_match.contains('.')) {
      ui->result_show->setText(ui->result_show->text() + '.');
    }
  }
}

QString View::last_substring_(QString const &str_reg) {
  QString input_str = ui->result_show->text();
  QRegularExpression reg_(str_reg);
  QRegularExpressionMatchIterator i = reg_.globalMatch(input_str);
  QRegularExpressionMatch last_match;
  while (i.hasNext()) {
    last_match = i.next();
  }
  return last_match.captured();
}

bool View::last_symbol_is_a_number_(QString const &str_reg) {
  QString input_str = ui->result_show->text();
  QRegularExpression reg_(str_reg);
  QChar last_char = input_str.back();
  QRegularExpressionMatch match = reg_.match(QString(last_char));
  return match.hasMatch();
}

void View::on_backspace_clicked() {
  QString input_str = ui->result_show->text();
  QString str_last_match = last_substring_(kRegForBackspace);
  for (int i = 0; i < str_last_match.size(); ++i) {
    if (str_last_match.size() == input_str.size()) {
      ui->result_show->setText("0");
    } else {
      ui->result_show->backspace();
    }
  }
}

void View::on_backspace_x_clicked() {
  QString input_str = ui->input_x->text();
  if (input_str.size() == 1) {
    ui->input_x->setText("");
  } else if (input_str.size() > 1) {
    ui->input_x->backspace();
  }
}

void View::on_equals_clicked() {
  std::string expression_ = ui->result_show->text().toStdString();
  std::string x_value = ui->input_x->text().toStdString();
  if (!(controller_.ValidateExpression(expression_))) {
    ui->result_show->setText("error!");
  } else if ((ui->result_show->text().contains('X')) &&
             (ui->input_x->text() == "")) {
    graph_ = new Graph;
    graph_->show();
    graph_->Graphics(controller_, expression_);
  } else {
    ui->result_show->setText(
        QString::number(controller_.SetAnswer(x_value), 'g', 16));
  }
}

void View::on_dot_x_clicked() {
  if (ui->input_x->text() == "") {
    ui->input_x->setText("0.");
  } else if (!ui->input_x->text().contains('.')) {
    ui->input_x->setText(ui->input_x->text() + '.');
  }
}
}  // namespace s21
