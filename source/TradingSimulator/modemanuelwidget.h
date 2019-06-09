#ifndef MODEMANUELWIDGET_H
#define MODEMANUELWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "Controller/simulation.h"

namespace Ui {
    class modeManuelWidget;
}

class modeManuelWidget : public QWidget {
    Q_OBJECT
    Ui::modeManuelWidget *ui;
    ModeManuel* modeManuel;
    TransactionManager* transactionManager;
    CoursOHLCV* coursPicked;
public:
    explicit modeManuelWidget(ModeManuel* modeManuel, QWidget *parent = nullptr);
    ~modeManuelWidget();
    void updateData();
signals:
    void transactionChanged();
private slots:
    void on_pushButton_achat_clicked();
    void on_pushButton_vente_clicked();
    void on_pushButton_annulerTransaction_clicked();
public slots:
    void setCoursPicked(CoursOHLCV* cours);

};

#endif // MODEMANUELWIDGET_H
