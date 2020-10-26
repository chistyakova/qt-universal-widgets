#include "mainwindow.hpp"

#include <QLabel>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>

#include "qthelpers/converters.hpp"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  QWidget *central_widget = new QWidget();
  this->setCentralWidget(central_widget);

  QVBoxLayout *layout = new QVBoxLayout();

  for (auto i : QVector<uint64_t>{10, 100, 999, 1024, 10000, 100000, 10000000,
                                  100000000, 1000000000, 10000000000}) {
    layout->addWidget(new QLabel(QString::number(i) + " = " +
                                 qthelpers::Converters::BytesToHuman(i)));
  }
  central_widget->setLayout(layout);
}

MainWindow::~MainWindow()
{
}

