#ifndef TAB_TRANSACTION_H
#define TAB_TRANSACTION_H

#include <QWidget>

namespace Ui {
class tab_transaction;
}

class tab_transaction : public QWidget
{
    Q_OBJECT

public:
    explicit tab_transaction(QWidget *parent = nullptr);
    ~tab_transaction();

private:
    Ui::tab_transaction *ui;
};

#endif // TAB_TRANSACTION_H
