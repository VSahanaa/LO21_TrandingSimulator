#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "indicateur.h"
#include <QMessageBox> //pour les informations critiques

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonRetourMenu_clicked();

    void on_pushButton_Sauv_clicked();

    void on_pushButton_Param_clicked();

    void on_pushButton_curseur_clicked();

    void on_pushButton_indicateur_clicked();

    void on_pushButton_tabCours_clicked();

    void on_pushButton_nouvelletransaction_clicked();

    void on_pushButton_annuler_clicked();

    void on_pushButton_tabTransaction_clicked();

    void on_pushButton_avancer_clicked();

    void on_pushButton_reculer_clicked();

    void on_pushButton_defiler_clicked();

    void on_pushButton_pause_clicked();

    void on_pushButton_Lire_2_clicked();

    void on_pushButton_modifier_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QDialog::Indicateur* dialog_ind;
};

#endif // MAINWINDOW_H
