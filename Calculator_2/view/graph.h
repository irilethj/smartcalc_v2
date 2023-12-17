#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include <QWidget>

#include "../controller/controller.h"
#define LIMIT 1000000

namespace Ui {
class Graph;
}

namespace s21 {

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  void Graphics(Controller &controller, std::string func_graph);
  ~Graph();

 private slots:
  void on_build_graphics_clicked();

 private:
  double x_start_, x_end_, y_start_, y_end_, step_, X_;
  QVector<double> x, y;
  Ui::Graph *ui;
  Controller controller_;
};
}  // namespace s21

#endif  // GRAPH_H
