#ifndef TAB_RSI_H
#define TAB_RSI_H

#include <QWidget>

namespace Ui {
class tab_RSI;
}

class tab_RSI : public QWidget
{
    Q_OBJECT

public:
    explicit tab_RSI(QWidget *parent = nullptr);
    ~tab_RSI();

private:
    Ui::tab_RSI *ui;
};

#endif // TAB_RSI_H
