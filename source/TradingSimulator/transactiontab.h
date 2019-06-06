#ifndef TRANSACTIONTAB_H
#define TRANSACTIONTAB_H
#include "transaction.h"
#include <QTableView>

namespace Ui {
class TransactionTab;
}

class TransactionTab : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionTab(QWidget *parent = 0,TransactionManager& tm);
    ~TransactionTab();

private:
    Ui::TransactionTab *ui;
    TransactionManager& TransactionM;
    QTableView *Tab;
  
//public slots:
  //  void myslot1();//ajoter et enlever dynamiquement
};

#endif // TRANSACTIONTAB_H
