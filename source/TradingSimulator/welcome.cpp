#include "welcome.h"
#include "ui_welcome.h"
#include "ui_info.h"

Welcome::Welcome(QApplication *ap, QWidget *parent) :
    QWidget(parent),
    app(ap),
    ui(new Ui::Welcome)
{
    ui->setupUi(this);
    connect(&tSimu, SIGNAL(closed()), this, SLOT(show()));
    this->setFixedSize(360, 360);
    ui->Candlestick->setIcon(QIcon(":/TradingSimulator/evolutionCours/icons/display.png"));
    ui->Candlestick->setIconSize(QSize(100,100));
    ui->Simulation->setIcon(QIcon(":/TradingSimulator/evolutionCours/icons/trading.png"));
    ui->Simulation->setIconSize(QSize(100,100));
    ui->Quit->setIcon(QIcon(":/TradingSimulator/evolutionCours/icons/quit.png"));
    ui->Quit->setIconSize(QSize(100,100));
    ui->Manuel->setIcon(QIcon(":/TradingSimulator/evolutionCours/icons/manuel.png"));
    ui->Manuel->setIconSize(QSize(100,100));
    ui->Step->setIcon(QIcon(":/TradingSimulator/evolutionCours/icons/step.png"));
    ui->Step->setIconSize(QSize(100,100));
    ui->Auto->setIcon(QIcon(":/TradingSimulator/evolutionCours/icons/auto.png"));
    ui->Auto->setIconSize(QSize(100,100));
    ui->Back->setIcon(QIcon(":/TradingSimulator/evolutionCours/icons/back.png"));
    ui->Back->setIconSize(QSize(100,100));
    ui->Currency1->addItems({"USD", "BTC"});
    ui->Currency2->addItems({"USD", "BTC"});
}

Welcome::~Welcome()
{
    delete ui;
}

// Page 0
void Welcome::on_Continue_clicked()
{
    ui->stackedWidget->setCurrentIndex(MainManu);
}

void Welcome::on_About_clicked()
{
    Info info;
    info.setModal(false);
    info.exec();
}

//Page 1
void Welcome::on_Quit_clicked()
{
    app->quit();
}

void Welcome::on_Simulation_clicked()
{
    ui->stackedWidget->setCurrentIndex(Simu);
}

void Welcome::on_Candlestick_clicked()
{
    ui->stackedWidget->setCurrentIndex(Display);
}

//Page 2
void Welcome::on_Manuel_clicked()
{
    tSimu.show();
    tSimu.changeMode(simuM);
    hide();
}

void Welcome::on_Step_clicked()
{
    tSimu.show();
    tSimu.changeMode(simuS);
    hide();
}

void Welcome::on_Auto_clicked()
{
    tSimu.show();
    tSimu.changeMode(simuA);
    hide();
}

void Welcome::on_Back_clicked()
{
    ui->stackedWidget->setCurrentIndex(MainManu);
}

//Page 3
void Welcome::on_filePath_clicked()
{
    QFileDialog fdlg;
    ui->linePath->setText(fdlg.getOpenFileName(this, tr("Choose csv file"),
                                               ":/",
                                               "Document files (*.csv)"));
}

void Welcome::on_dispaly_dialog_accepted()
{
    QString name, fPath = ui->linePath->text();
    QFile check(fPath);
    if (!check.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Error", "Invalid file path");
    }
    else
    {
        //name.append(ui->Currency1->currentText());
        //name.append("_");
        //name.append(ui->Currency2->currentText());
        //evolution = new EvolutionCours(fPath);
        //view = new EvolutionViewer(*evolution);
        //view->setname(name);
        tSimu.show();
        tSimu.changeMode(cdStk);
        hide();
    }
}

void Welcome::on_dispaly_dialog_rejected()
{
    ui->stackedWidget->setCurrentIndex(MainManu);
}

/* Class Info */
Info::Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
}

Info::~Info()
{
    delete ui;
}






