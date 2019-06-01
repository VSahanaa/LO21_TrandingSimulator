#ifndef TAB_MACD_H
#define TAB_MACD_H

#include <QWidget>

namespace Ui {
class tab_MACD;
}

class tab_MACD : public QWidget
{
    Q_OBJECT

public:
    explicit tab_MACD(QWidget *parent = nullptr);
    ~tab_MACD();

private:
    Ui::tab_MACD *ui;
};

#endif // TAB_MACD_H
