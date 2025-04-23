#ifndef STOCK_H
#define STOCK_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QVector>
#include <QPair>

class Stock : public QObject
{
    Q_OBJECT
public:
    explicit Stock(const QString &symbol, const QString &name, double initialPrice, QObject *parent = nullptr);

    // Data structure for candlestick data
    struct CandleData {
        QDateTime timestamp;
        double open;
        double high;
        double low;
        double close;
    };

    // Getters
    QString symbol() const { return m_symbol; }
    QString name() const { return m_name; }
    double currentPrice() const { return m_currentPrice; }
    double initialPrice() const { return m_initialPrice; }
    double percentChange() const;

    // Access to history data
    const QVector<QPair<QDateTime, double>>& getPriceHistory() const { return m_priceHistory; }
    QVector<CandleData> getCandleData() const { return m_candleData; }

    // Candle settings
    void setCandleDuration(int seconds) { m_candleDuration = seconds; }

public slots:
    void updatePrice();

signals:
    void priceChanged(const QString &symbol, double newPrice, double percentChange);

private:
    void updateCandleData();

    QString m_symbol;
    QString m_name;
    double m_initialPrice;
    double m_currentPrice;
    double m_volatility;  // Controls price fluctuation

    // For storing price history
    QVector<QPair<QDateTime, double>> m_priceHistory;

    // For candlestick data
    QVector<CandleData> m_candleData;
    CandleData m_currentCandle;
    QDateTime m_candleStart;
    int m_candleDuration = 60; // Default 60 seconds per candle
};

#endif // STOCK_H
