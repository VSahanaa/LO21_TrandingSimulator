#include "transactiontab.h"
#include "ui_transactiontab.h"

#include <QStandardItemModel>
#include <QString>


TransactionTab::TransactionTab(QWidget *parent,TransactionManager& tm) :
    QWidget(parent),TransactionM(tm),
    ui(new Ui::TransactionTab)
{
    ui->setupUi(this);
    Tab=new QTableView;
    QStandardItemModel* model=new QStandardItemModel();
    Tab->setModel(model);
    int i=0;
    QString montant,montantd,cotation,catationd,mon,cot;
  
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal,"Date");
    model->setHeaderData(1,Qt::Horizontal,"Montant Base");
    model->setHeaderData(2,Qt::Horizontal,"Montant Cotation");
    //model->setHeaderData(3,Qt::Horizontal,"ROI");
    
    for(TransactionManager::iterator it=tm.head();it->hasNext();++it){
        Transaction &trans=*it;
        
        montant=QString::number(trans.getMontantBase());
        montantd=QString::number(trans.differenceBase());
        cotation=QString::number(trans.getMontantContrepartie());
        catationd=QString::number(trans.differenceContrepartie());
        mon=montant+"("+montantd+")";
        cot=cotation+"("+catationd+")";
        
        model->setItem(i,0,new QStandardItem(trans.getDate()));
        model->setItem(i,1,new QStandardItem(mon));
        model->setItem(i,2,new QStandardItem(cot));
        //model->setItem(i,3,new QStandardItem());
        
        i++;
        
        
    }
    
    
    
}

TransactionTab::~TransactionTab()
{
    delete ui;
}

/*void TransactionTab::myslot1(){
    Tab->setModel(NULL);
    Tab->setModel(modle);
}*/
