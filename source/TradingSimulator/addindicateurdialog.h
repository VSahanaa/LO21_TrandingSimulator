#ifndef ADDINDICATEURDIALOG_H
#define ADDINDICATEURDIALOG_H

#include <QDialog>

namespace Ui {
class AddIndicateurDialog;
}

class AddIndicateurDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddIndicateurDialog(QWidget *parent = nullptr);
    ~AddIndicateurDialog();

private:
    Ui::AddIndicateurDialog *ui;
};

#endif // ADDINDICATEURDIALOG_H
