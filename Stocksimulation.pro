QT += core gui charts  # Ensure 'charts' is added here
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StockSimulation
TEMPLATE = app

# Add your source files
SOURCES += \
    candlestickchartwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    stock.cpp \
    stockchartwidget.cpp \
    stockmarketmodel.cpp

# Add your header files
HEADERS += \
    candlestickchartwindow.h \
    mainwindow.h \
    stock.h \
    stockchartwidget.h \
    stockmarketmodel.h

# Add your UI files
FORMS += \
    mainwindow.ui

# Set C++17 as the required standard
CONFIG += c++17

# Optional: Disable deprecated APIs if you're using Qt 6
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Deployment paths (optional, depending on your target platform)
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
