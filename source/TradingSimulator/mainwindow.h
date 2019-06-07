#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "configuration.h"
#include "simulationtab.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_newSimulation_button_clicked();
    void addSimulation();
private:
    Ui::MainWindow *ui;
    Configuration* configuration;
    SimulationTab* simulationTabs;
};

#endif // MAINWINDOW_H
