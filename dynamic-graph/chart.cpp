#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QTime>
#include <QDebug>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axisX(new QValueAxis),
    m_step(0),
    m_x(5),
    m_y(1)
{
    qsrand((uint) QTime::currentTime().msec());

    connect(&m_timer, &QTimer::timeout, this, &Chart::handleTimeout);
    m_timer.setInterval(300);

    m_series = new QLineSeries(this);
    *m_series << QPointF(1, 5) << QPointF(3.5, 18) << QPointF(4.8, 7.5) << QPointF(10, 2.5);
    QAreaSeries *series = new QAreaSeries(m_series);

    QPen pen(Qt::green);
    QBrush brush(QColor(100,0,255,128));
    pen.setWidth(3);

    m_series->setPen(pen);
    series->setBrush(brush);
    m_series->append(m_x, m_y);

    addSeries(series);
    addSeries(m_series);

    legend()->hide();

    m_axisX->setTickCount(5);
    qDebug() << "1";
    addAxis(m_axisX, Qt::AlignBottom);
    series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisX);

    auto axisY = new QValueAxis;
    axisY->setTickCount(10);
    axisY->setMinorTickCount(5);
    axisY->setMinorGridLineVisible(false);
    qDebug() << "1";
    addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    m_series->attachAxis(axisY);

    qDebug() << "2";
    QPen axisPen(Qt::darkGray);
    axisPen.setWidth(2);
    m_axisX->setLinePen(axisPen);
    axisY->setLinePen(axisPen);

    m_axisX->setRange(-30, 30);

    qDebug() << "3";
    yMax = 10;
    yMin = -5;

    //axisX()->setRange(0, 10);
    //axisY()->setRange(yMin, yMax);
    qDebug() << "4";
    connect(m_series, &QLineSeries::pointAdded, [=](int index){
        qreal y = m_series->at(index).y();

        if(y< yMin || y > yMax){
            if(y < yMin)
            yMin = y;
            if(y> yMax)
            yMax = y;
            qDebug() << "5";
            //axisY()->setRange(yMin-20, yMax+20);
        }

    });
    qDebug() << "6";
    /*for(int i=1000; i<1200; ++i)
    {
        qreal y = (m_axis->max() - m_axis->min()) / i;
        m_x += y*100;
        m_y = 50*(qrand() % 5 - 2.5);
        m_series->append(m_x, m_y);
    }*/
}

Chart::~Chart()
{

}

void Chart::handleTimeout()
{
    qreal x = plotArea().width() / m_axisX->tickCount();
    scroll(x, 0);
    if (m_axisX->max() > m_x)
        m_timer.stop();
}

void Chart::startFlight()
{
    m_timer.start();
}
