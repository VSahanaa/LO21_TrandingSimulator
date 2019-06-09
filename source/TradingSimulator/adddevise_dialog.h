#ifndef ADDDEVISE_DIALOG_H
#define ADDDEVISE_DIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "Core_Devises/trading.h"

namespace Ui {
    class AddDevise_Dialog;
}

class AddDevise_Dialog : public QDialog {
    Q_OBJECT
public:
    explicit AddDevise_Dialog(QWidget *parent = nullptr);
    ~AddDevise_Dialog();
    const Devise* getNewDevise() const {return newDevise;}
private slots:
    void on_AddDevise_Dialog_accepted();

private:
    Ui::AddDevise_Dialog *ui;
    const Devise* newDevise = nullptr;
};

#endif // ADDDEVISE_DIALOG_H
