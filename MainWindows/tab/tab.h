#ifndef TAB_H
#define TAB_H

#include <QMainWindow>

namespace Ui {
class TAB;
}

class TAB : public QMainWindow
{
    Q_OBJECT

public:
    explicit TAB(QWidget *parent = nullptr);
    ~TAB();

private:
    Ui::TAB *ui;
};

#endif // TAB_H
