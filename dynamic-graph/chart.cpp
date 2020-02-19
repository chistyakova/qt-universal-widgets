#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QTime>
#include <QDebug>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axis(new QValueAxis),
    m_step(0),
    m_x(5),
    m_y(1)
{
    qsrand((uint) QTime::currentTime().msec());

    connect(&m_timer, &QTimer::timeout, this, &Chart::handleTimeout);
    m_timer.setInterval(300);

    m_series = new QLineSeries(this);

    QPen pen(Qt::red);
    pen.setWidth(3);
    m_series->setPen(pen);
    m_series->append(m_x, m_y);

    addSeries(m_series);
    createDefaultAxes();
    setAxisX(m_axis, m_series);
    m_axis->setTickCount(5);

    yMax = 10;
    yMin = -5;

    axisX()->setRange(0, 10);
    axisY()->setRange(yMin, yMax);

    connect(m_series, &QLineSeries::pointAdded, [=](int index){
        qreal y = m_series->at(index).y();

        if(y< yMin || y > yMax){
            if(y < yMin)
            yMin = y;
            if(y> yMax)
            yMax = y;
            axisY()->setRange(yMin-20, yMax+20);
        }

    });

    for(int i=1000; i<1200; ++i)
    {
        qreal y = (m_axis->max() - m_axis->min()) / i;
        m_x += y*100;
        m_y = 50*(qrand() % 5 - 2.5);
        m_series->append(m_x, m_y);
    }

    m_timer.start();
}

Chart::~Chart()
{

}

void Chart::handleTimeout()
{
    qreal x = plotArea().width() / m_axis->tickCount();
    scroll(x, 0);
    if (m_axis->max() > m_x)
        m_timer.stop();
}
