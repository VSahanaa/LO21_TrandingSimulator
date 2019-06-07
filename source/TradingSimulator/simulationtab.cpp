#include "simulationtab.h"

SimulationTab::SimulationTab(QWidget* parent): QTabWidget (parent) {
    tabBar = new QTabBar();
    tabBar->setMovable(true);
    addButton = new QPushButton(QIcon("://icons/+.jpeg"), "",tabBar);
    tabBar->setTabButton(tabBar->count()-1, QTabBar::RightSide, addButton);
    this->setTabBar(tabBar);
    this->setTabsClosable(true);
    QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(newSimulationRequest()));
    QObject::connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(closetab(int)));

}

void SimulationTab::addSimulation(Simulation* simulation) {
    MainInterface* newSimulationWidget = new MainInterface(this);
    this->insertTab(this->count()-1, newSimulationWidget, simulation->getNom());
    this->setCurrentIndex(this->count()-2);
}
