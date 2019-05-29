#ifndef INDICATEUR_H
#define INDICATEUR_H

#include <QDialog>

namespace Ui {
class Indicateur;
}

class Indicateur : public QDialog
{
    Q_OBJECT

public:
    explicit Indicateur(QWidget *parent = nullptr);
    ~Indicateur();

private slots:
    void on_listWidget_itemActivated(QListWidgetItem *item);

    void on_buttonBox_accepted();

    void on_listWidget_indicateurs_itemActivated(QListWidgetItem *item);

    void on_buttonBox_OK_accepted();

    void on_buttonBox_OK_rejected();

private:
    Ui::Indicateur *ui;
};

#endif // INDICATEUR_H
