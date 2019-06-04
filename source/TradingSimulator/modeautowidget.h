#ifndef MODEAUTOWIDGET_H
#define MODEAUTOWIDGET_H
#include "Controller/simulation.h"
#include <QWidget>

namespace Ui {
    class ModeAutowidget;
}

class ModeAutowidget : public QWidget {
    Q_OBJECT
public:
    explicit ModeAutowidget(ModeAutomatique* modeAutomatique, QWidget *parent = nullptr);
    ~ModeAutowidget();
private slots:
    void updateData();
    void on_comboBox_timer_currentIndexChanged(int index);

private:
    Ui::ModeAutowidget *ui;
    ModeAutomatique* modeAutomatique;
    TransactionManager* transactionManager;
};

#endif // MODEAUTOWIDGET_H
