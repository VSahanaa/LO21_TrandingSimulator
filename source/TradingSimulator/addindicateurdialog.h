#ifndef ADDINDICATEURDIALOG_H
#define ADDINDICATEURDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "Core_Devises/trading.h"

namespace Ui {
    class AddIndicateurDialog;
}

class AddIndicateurDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddIndicateurDialog(QString indicateur, EvolutionCours* evolutionCours, QWidget *parent = nullptr);
    ~AddIndicateurDialog();

private slots:
    void on_AddIndicateurDialog_accepted();

private:
    Ui::AddIndicateurDialog *ui;
    QString indicateur;
    EvolutionCours* evolutionCours;
};

#endif // ADDINDICATEURDIALOG_H
