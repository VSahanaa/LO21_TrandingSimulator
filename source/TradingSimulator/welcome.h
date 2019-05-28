#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "UI/mainwindow.h"
//#include "/Core_Devises/trading.h"
//#include "/UI/evolutionviewer.h"

enum {
    Home = 0,
    MainManu,
    Simu,
    Display
};
enum {
    simuM = 0,
    simuA,
    simuS,
    cdStk
};

namespace Ui {
class Welcome;
}

class Welcome : public QWidget
{
    Q_OBJECT
    QApplication *app = nullptr;
    //EvolutionCours *evolution = nullptr;
    //EvolutionViewer *view = nullptr;
    MainWindow tSimu;

public:
    explicit Welcome(QApplication *ap,QWidget *parent = nullptr);

    ~Welcome();

private slots:
    void on_Continue_clicked();

    void on_About_clicked();

    void on_Quit_clicked();

    void on_Simulation_clicked();

    void on_Candlestick_clicked();

    void on_Manuel_clicked();

    void on_Step_clicked();

    void on_Auto_clicked();

    void on_Back_clicked();

    void on_filePath_clicked();

    void on_dispaly_dialog_accepted();

    void on_dispaly_dialog_rejected();

private:
    Ui::Welcome *ui;
};

namespace Ui {
class Info;
}

class Info : public QDialog
{
    Q_OBJECT

public:
    explicit Info(QWidget *parent = nullptr);
    ~Info();

private:
    Ui::Info *ui;
};

#endif // WELCOME_H
