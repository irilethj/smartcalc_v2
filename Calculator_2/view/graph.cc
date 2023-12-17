#include "graph.h"

#include "ui_graph.h"
namespace s21 {

Graph::Graph(QWidget* parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
}

Graph::~Graph() { delete ui; }

void Graph::Graphics(Controller& controller, std::string func_graph) {
  controller_ = controller;
  ui->func_graph_->setText(QString::fromStdString(func_graph));
  y_start_ = ui->y_min->text().toDouble();
  y_end_ = ui->y_max->text().toDouble();
  x_start_ = ui->x_min->text().toDouble();
  x_end_ = ui->x_max->text().toDouble();
  if (x_start_ < -LIMIT) x_start_ = -LIMIT;
  if (x_end_ > LIMIT) x_end_ = LIMIT;

  step_ = (x_end_ - x_start_) / 10000;
  ui->widget->xAxis->setRange(x_start_, x_end_);
  ui->widget->yAxis->setRange(y_start_, y_end_);
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");

  x.clear();
  y.clear();

  ui->widget->clearPlottables();
  ui->widget->clearGraphs();
  for (X_ = x_start_; X_ <= x_end_ && step_ != 0; X_ += step_) {
    x.push_back(X_);
    y.push_back(controller.SetAnswer(std::to_string(X_)));
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

void Graph::on_build_graphics_clicked() {
  std::string func_graph = ui->func_graph_->text().toStdString();
  Graphics(controller_, func_graph);
}
}  // namespace s21
