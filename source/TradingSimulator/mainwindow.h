#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "trading.h"
#include "evolutionviewer.h"

enum {
    Welcome = 0,
    MainManu,
    Display
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    EvolutionCours *evolution = nullptr;
    EvolutionViewer *view = nullptr;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Show_clicked();

    void on_Funct1_clicked();

    void on_Funct2_clicked();

    void on_Funct3_clicked();

    void on_Funct4_clicked();

    void on_enter_clicked();

    void on_searchFile_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
