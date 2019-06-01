#ifndef MAINWINDOW_MODEMANUEL_H
#define MAINWINDOW_MODEMANUEL_H

#include <QMainWindow>

namespace Ui {
class MainWindow_modemanuel;
}

class MainWindow_modemanuel : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_modemanuel(QWidget *parent = nullptr);
    ~MainWindow_modemanuel();

private slots:
    void on_pushButton_retourMenu_clicked();

    void on_pushButton_sauvegarder_clicked();

    void on_pushButton_parametre_clicked();

    void on_pushButton_aide_clicked();

    void on_pushButton_achat_clicked();

    void on_pushButton_vente_clicked();

    void on_pushButton_annulerTransaction_clicked();

    void on_pushButton_tabCoursOHLCV_clicked();

    void on_pushButton_tabTransaction_clicked();

    void on_pushButton_prendreNote_clicked();

    void on_checkBox_RSI_stateChanged(int arg1);

    void on_checkBox_EMA_stateChanged(int arg1);

    void on_checkBox_MACD_stateChanged(int arg1);

    void on_tabWidget_autres_tabCloseRequested(int index);

private:
    Ui::MainWindow_modemanuel *ui;
};

#endif // MAINWINDOW_MODEMANUEL_H
