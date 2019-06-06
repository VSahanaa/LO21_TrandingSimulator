#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    tabs = new QTabWidget(this);
    tabs->setTabsClosable(true);
    tabs->setMovable(true);
    tabs->addTab(new QWidget(tabs), QIcon("://icons/+.jpeg"), "");
    QObject::connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(newtab(int)));
    QObject::connect(tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closetab(int)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_newSimulation_button_clicked() {
    configuration = new Configuration(this);
    configuration->setModal(true);
    configuration->exec();
    //add new Simulation
    Simulation* newSimulation = configuration->getSimulation();
    MainInterface* newSimulationWidget = new MainInterface(newSimulation, tabs);
    tabs->addTab(newSimulationWidget, newSimulation->getNom());
    delete configuration;
}

void MainWindow::newtab(int index) {
    if (index == tabs->count() -1) {
        //add new simulation

    }
}

void MainWindow::closetab(int index) {
    tabs->removeTab(index);
}
