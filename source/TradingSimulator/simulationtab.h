#ifndef SIMULATIONTAB_H
#define SIMULATIONTAB_H

#include <QWidget>
#include <QTabWidget>
#include <QTabBar>
#include <QPushButton>
#include "maininterface.h"
namespace Ui {
    class SimulationTab;
}

class SimulationTab: public QTabWidget{
    Q_OBJECT
    QTabBar* tabBar;
    QPushButton* addButton;
public:
    explicit SimulationTab(QWidget* parent = nullptr);
    void addSimulation(Simulation* simulation);
signals:
    void newSimulationSignal();
private slots:
    void newSimulationRequest() {emit newSimulationSignal();}
    void closeTab(int index) {this->removeTab(index);}
};


#endif // SIMULATIONTAB_H
