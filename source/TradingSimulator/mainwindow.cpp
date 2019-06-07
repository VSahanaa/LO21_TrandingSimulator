#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    simulationTabs = new SimulationTab(this);
    ui->mainInterfaceLayout->addWidget(simulationTabs);
    QObject::connect(simulationTabs, SIGNAL(newSimulationSignal()), this, SLOT(newtab()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_newSimulation_button_clicked() {
    configuration = new Configuration(this);
    configuration->setModal(true);
    configuration->exec();
    //add new Simulation
    simulationTabs->addSimulation(configuration->getSimulation());
    delete configuration;
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}

void MainWindow::addSimulation() {
    ui->stackedWidget->setCurrentWidget(ui->landingPage);
}

