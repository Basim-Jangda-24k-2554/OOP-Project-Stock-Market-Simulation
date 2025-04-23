// candlestickchartwindow.h
#pragma once

#include <QMainWindow>
#include <QtCharts>

QT_USE_NAMESPACE

    class CandlestickChartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CandlestickChartWindow(const QString& stockName, QWidget *parent = nullptr);

private:
    QChartView *chartView;
    QCandlestickSeries *candlestickSeries;

    void setupChart(const QString& stockName);
};
