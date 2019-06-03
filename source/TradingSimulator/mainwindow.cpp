#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    mainInterface = new QTabWidget(this);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_newSimulation_button_clicked() {
    configuration = new Configuration(this);
    configuration->setModal(true);
    configuration->exec();
    //add new Simulation

}
