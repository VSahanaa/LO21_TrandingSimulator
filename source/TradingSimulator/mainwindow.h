#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "maininterface.h"

namespace Ui {
    class MainWindow;
    class SimulationTab;
}

class SimulationTab: public QTabWidget{
    Q_OBJECT
public:
    SimulationTab(QWidget* parent);
signals:
    void closeWindow_request();
private slots:
    void newTab();
    void closeTab(int index);
    void setTabName(QString nom) {
        qDebug() << nom;
        setTabText(currentIndex(), nom);}
};


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void stop();
private slots:
    void send_stop() {emit stop();}
private:
    Ui::MainWindow *ui;
    SimulationTab* simulationTabs;
};

#endif // MAINWINDOW_H
