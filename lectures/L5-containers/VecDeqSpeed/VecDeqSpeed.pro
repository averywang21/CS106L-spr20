TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

SOURCES += main.cpp \
    qcustomplot.cpp \
    graphwindow.cpp

HEADERS += \
    qcustomplot.h \
    graphwindow.h

FORMS += \
    windowform.ui
