#ifndef MODEMANUELWIDGET_H
#define MODEMANUELWIDGET_H

#include <QWidget>
#include "Controller/simulation.h"

namespace Ui {
    class modeManuelWidget;
}

class modeManuelWidget : public QWidget {
    Q_OBJECT
public:
    explicit modeManuelWidget(ModeManuel* modeManuel, QWidget *parent = nullptr);
    ~modeManuelWidget();
private slots:
    void updateData();
    void updateCoursPicked(CoursOHLCV* cours);
private:
    Ui::modeManuelWidget *ui;
    ModeManuel* modeManuel;
    TransactionManager* transactionManager;
};

#endif // MODEMANUELWIDGET_H
