#ifndef MODEAUTOWIDGET_H
#define MODEAUTOWIDGET_H

#include <QWidget>

namespace Ui {
class ModeAutowidget;
}

class ModeAutowidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModeAutowidget(QWidget *parent = nullptr);
    ~ModeAutowidget();

private:
    Ui::ModeAutowidget *ui;
};

#endif // MODEAUTOWIDGET_H
