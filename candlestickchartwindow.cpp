// candlestickchartwindow.cpp
#include "candlestickchartwindow.h"
#include <QRandomGenerator>

CandlestickChartWindow::CandlestickChartWindow(const QString& stockName, QWidget *parent)
    : QMainWindow(parent)
{
    candlestickSeries = new QCandlestickSeries();
    candlestickSeries->setName(stockName);
    candlestickSeries->setIncreasingColor(Qt::green);
    candlestickSeries->setDecreasingColor(Qt::red);

    setupChart(stockName);

    QChart *chart = new QChart();
    chart->addSeries(candlestickSeries);
    chart->setTitle(stockName + " - Candlestick Chart");
    chart->createDefaultAxes();

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);
    resize(800, 600);
}



void CandlestickChartWindow::setupChart(const QString& stockName)
{
    for (int i = 0; i < 10; ++i) {
        // Use generateDouble() to get a floating-point value between 0.0 and 1.0
        double open = 100.0 + QRandomGenerator::global()->generateDouble() * 100.0;  // Random between 100.0 and 200.0
        double high = open + QRandomGenerator::global()->generateDouble() * 10.0;    // Random high between 5.0 and 15.0
        double low = open - QRandomGenerator::global()->generateDouble() * 10.0;     // Random low between 5.0 and 15.0
        double close = low + QRandomGenerator::global()->generateDouble() * (high - low); // Random close between low and high

        candlestickSeries->append(new QCandlestickSet(open, high, low, close));
    }
}

