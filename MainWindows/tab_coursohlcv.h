#ifndef TAB_COURSOHLCV_H
#define TAB_COURSOHLCV_H

#include <QWidget>

namespace Ui {
class tab_coursOHLCV;
}

class tab_coursOHLCV : public QWidget
{
    Q_OBJECT

public:
    explicit tab_coursOHLCV(QWidget *parent = nullptr);
    ~tab_coursOHLCV();

private:
    Ui::tab_coursOHLCV *ui;
};

#endif // TAB_COURSOHLCV_H
