#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "evolutionviewer.h"

enum {
    simuM = 0,
    simuA,
    simuS,
    cdStk
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    EvolutionCours *cours;
    EvolutionViewer *view;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeMode(int mode);

private slots:

    void on_csLabel_currentRowChanged(int currentRow);

signals:
    void closed();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *eve) {emit closed(); eve->accept();}
    //void wheelEvent(QWheelEvent *eve) {qDebug()<<eve->delta();}
};

#endif // MAINWINDOW_H
