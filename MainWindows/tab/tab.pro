#-------------------------------------------------
#
# Project created by QtCreator 2019-06-02T01:16:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tab
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        tab.cpp\
        ../mainwindow_modeauto.cpp \
        ../mainwindow_modemanuel.cpp \
        ../mainwindow_modepas.cpp \
        ../tab_coursohlcv.cpp \
        ../tab_ema.cpp \
        ../tab_macd.cpp \
        ../tab_rsi.cpp\
        ../tab_transaction.cpp

HEADERS += \
        tab.h \
        ../mainwindow_modeauto.h \
        ../mainwindow_modemanuel.h \
        ../mainwindow_modepas.h \
        ../tab_coursohlcv.h \
        ../tab_ema.h \
        ../tab_macd.h\
        ../tab_rsi.h\
        ../tab_transaction.h
FORMS += \
        tab.ui \
        ../mainwindow_modeauto.ui \
        ../mainwindow_modemanuel.ui \
        ../mainwindow_modepas.ui \
        ../tab_coursohlcv.ui \
        ../tab_ema.ui \
        ../tab_macd.ui \
        ../tab_rsi.ui\
        ../tab_transaction.ui
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
