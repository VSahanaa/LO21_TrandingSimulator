#-------------------------------------------------
#
# Project created by QtCreator 2019-05-11T00:24:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts

TARGET = TradingSimulator
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
        Core_Devises/trading.cpp \
        Core_Devises/indicateur.cpp \
        Controller/transaction.cpp \
        Controller/strategie.cpp \
        Controller/simulation.cpp \
        UI/evolutionviewer.cpp \
        UI/welcome.cpp \
        adddevise_dialog.cpp \
        configuration.cpp \
        main.cpp \
        mainwindow.cpp \
        tradinginterface.cpp

HEADERS += \
        Core_Devises/trading.h \
        Controller/transaction.h\
        Controller/strategie.h \
        Controller/simulation.h \
        UI/evolutionviewer.h \
        UI/welcome.h \
        adddevise_dialog.h \
        configuration.h \
        mainwindow.h \
        tradinginterface.h

FORMS += \
        UI/welcome.ui \
        UI/info.ui \
        adddevise_dialog.ui \
        configuration.ui \
        mainwindow.ui \
        tradinginterface.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
