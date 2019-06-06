#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "configuration.h"
#include "maininterface.h"

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
    void newtab(int index);
    void closetab(int index);
private:
    Ui::MainWindow *ui;
    Configuration* configuration;
    QTabWidget* tabs;
};

#endif // MAINWINDOW_H
