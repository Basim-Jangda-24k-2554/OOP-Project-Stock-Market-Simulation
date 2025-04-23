#include "stock.h"
#include <QRandomGenerator>

Stock::Stock(const QString &symbol, const QString &name, double initialPrice, QObject *parent)
    : QObject(parent)
    , m_symbol(symbol)
    , m_name(name)
    , m_initialPrice(initialPrice)
    , m_currentPrice(initialPrice)
    , m_volatility(0.02)  // 2% volatility by default
{
    // Store initial price in history
    m_priceHistory.append(qMakePair(QDateTime::currentDateTime(), initialPrice));
}

double Stock::percentChange() const
{
    return ((m_currentPrice - m_initialPrice) / m_initialPrice) * 100.0;
}

void Stock::updatePrice()
{
    // Simple random walk algorithm
    double changePercent = (QRandomGenerator::global()->generateDouble() - 0.5) * m_volatility;
    m_currentPrice *= (1 + changePercent);

    // Store price in history
    m_priceHistory.append(qMakePair(QDateTime::currentDateTime(), m_currentPrice));

    // Limit history size to 100 points
    while (m_priceHistory.size() > 100) {
        m_priceHistory.removeFirst();
    }

    // Update candle data
    updateCandleData();

    // Emit signal with new price
    emit priceChanged(m_symbol, m_currentPrice, percentChange());
}

void Stock::updateCandleData()
{
    QDateTime now = QDateTime::currentDateTime();

    // If we don't have a candle yet or the current candle is complete
    if (m_candleStart.isNull() || m_candleStart.secsTo(now) >= m_candleDuration) {
        // Close the current candle if it exists
        if (!m_candleStart.isNull()) {
            m_currentCandle.close = m_currentPrice;
            m_candleData.append(m_currentCandle);

            // Limit history size to 100 candles
            while (m_candleData.size() > 100) {
                m_candleData.removeFirst();
            }
        }

        // Start a new candle
        m_candleStart = now;
        m_currentCandle.timestamp = now;
        m_currentCandle.open = m_currentPrice;
        m_currentCandle.high = m_currentPrice;
        m_currentCandle.low = m_currentPrice;
        m_currentCandle.close = m_currentPrice;
    } else {
        // Update current candle
        m_currentCandle.high = qMax(m_currentCandle.high, m_currentPrice);
        m_currentCandle.low = qMin(m_currentCandle.low, m_currentPrice);
        m_currentCandle.close = m_currentPrice;
    }
}
