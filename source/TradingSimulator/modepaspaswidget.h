#ifndef MODEPASPASWIDGET_H
#define MODEPASPASWIDGET_H

#include <QWidget>

namespace Ui {
class ModePasPaswidget;
}

class ModePasPaswidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModePasPaswidget(QWidget *parent = nullptr);
    ~ModePasPaswidget();

private:
    Ui::ModePasPaswidget *ui;
};

#endif // MODEPASPASWIDGET_H
