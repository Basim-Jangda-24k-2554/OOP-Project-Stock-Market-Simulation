#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDateTime>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include "candlestickchartwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Code for Homepage Live Date Time
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        QString dateTimeStr = QDateTime::currentDateTime().toString("dd MMM yyyy - hh:mm:ss");
        ui->labelDateTime->setText(dateTimeStr);
    });
    timer->start(1000); // update every second

    connect(ui->tableGainers, &QTableView::clicked, this, &MainWindow::onStockClicked);

    // 📊 Insert sample stock row
    QList<double> priceHistory = {101.2, 102.4, 100.5, 103.8, 105.1};
    addStockRow("ABC Corp", 105.1, priceHistory, 0);
    // in your main window .cpp



}


// Slot function


void MainWindow::onStockClicked(const QModelIndex &index)
{
    QString stockName = index.sibling(index.row(), 1).data().toString(); // column 1 = stock name

    auto *chartWindow = new CandlestickChartWindow(stockName, this);
    chartWindow->show();
}

// 📥 FUNCTION: Add one stock to the table with a mini line graph
void MainWindow::addStockRow(const QString &name, double price, QList<double> priceHistory, int row)
{
    ui->tableGainers->insertRow(row);
    ui->tableGainers->setItem(row, 0, new QTableWidgetItem(name));
    ui->tableGainers->setItem(row, 1, new QTableWidgetItem(QString::number(price, 'f', 2)));

    // Create the line series for the price history
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < priceHistory.size(); ++i)
        series->append(i, priceHistory[i]);

    // Create the chart and configure it
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setBackgroundVisible(false);
    chart->setMargins(QMargins(0, 0, 0, 0));
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setVisible(false);
    chart->axes(Qt::Vertical).first()->setVisible(false);

    // Create the chart view and set its properties
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(100, 40);  // Set the size of the chart inside the table cell

    // Add the chart view to the table at the given row and column
    ui->tableGainers->setCellWidget(row, 2, chartView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
