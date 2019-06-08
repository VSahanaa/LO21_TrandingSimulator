#include "mainwindow.h"
#include "ui_mainwindow.h"

SimulationTab::SimulationTab(QWidget* parent): QTabWidget (parent) {
    QTabBar* tabBar = this->tabBar();
    tabBar->setTabsClosable(true);
    tabBar->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
    tabBar->setMovable(true);
    setDocumentMode(true);
    setElideMode(Qt::ElideRight);
    MainInterface* mainInterface = new MainInterface();
    connect(mainInterface, SIGNAL(giveName(QString)), this, SLOT(setTabName(QString)));
    this->addTab(mainInterface, "New Simulation");            // first Tab

    this->addTab(new QPushButton(),"");                             //new Tab button
    QPushButton* newTabButton = new QPushButton(QIcon("://icons/add.png"), "");
    tabBar->setTabButton(1, QTabBar::RightSide, newTabButton);

    //connect signals
    connect(newTabButton, SIGNAL(clicked()), this, SLOT(newTab()));
    connect(tabBar, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    qDebug() << this->count();
}

void SimulationTab::newTab() {
    MainInterface* mainInterface = new MainInterface(this);
    connect(mainInterface, SIGNAL(giveName(QString)), this, SLOT(setTabName(QString)));
    this->insertTab(count()-1, mainInterface, "New Simulation");
    this->setCurrentIndex(count() -2);
}

void SimulationTab::closeTab(int index) {
    delete widget(index);
    if(count() == 1) {
        emit closeWindow_request();
    }
    qDebug()<< count();
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    simulationTabs = new SimulationTab(this);
    connect(simulationTabs, SIGNAL(closeWindow_request()), this, SLOT(send_stop()));
    ui->mainLayout->addWidget(simulationTabs);
}

MainWindow::~MainWindow() {
    delete ui;
}


