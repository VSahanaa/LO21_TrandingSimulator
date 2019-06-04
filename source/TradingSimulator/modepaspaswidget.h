#ifndef MODEPASPASWIDGET_H
#define MODEPASPASWIDGET_H
#include "Controller/simulation.h"
#include <QWidget>

namespace Ui {
    class ModePasPaswidget;
}

class ModePasPaswidget : public QWidget {
    Q_OBJECT
public:
    explicit ModePasPaswidget(ModePas_Pas* modePas_Pas, QWidget *parent = nullptr);
    ~ModePasPaswidget();
private slots:
    void updateData();
    void updateCurrentCours(CoursOHLCV* cours);
    void on_goBack_clicked();

    void on_comboBox_timer_currentIndexChanged(const QString &arg1);

private:
    Ui::ModePasPaswidget *ui;
    ModePas_Pas* modePas_Pas;
    TransactionManager* transactionManager;
};

#endif // MODEPASPASWIDGET_H
