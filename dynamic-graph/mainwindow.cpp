#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include "chart.h"

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_chart(0)
    , m_series(0)
{
    ui->setupUi(this);

    m_chart = new Chart;
    QChartView *chartView = new QChartView(m_chart);
    chartView->setMinimumSize(800, 600);
    ui->mainLayout->addWidget(chartView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    m_chart->startFlight();
}
