#ifndef TAB_EMA_H
#define TAB_EMA_H

#include <QWidget>

namespace Ui {
class tab_EMA;
}

class tab_EMA : public QWidget
{
    Q_OBJECT

public:
    explicit tab_EMA(QWidget *parent = nullptr);
    ~tab_EMA();

private:
    Ui::tab_EMA *ui;
};

#endif // TAB_EMA_H
