#ifndef INFO_H
#define INFO_H

#include <QDialog>
#include "ui_info.h"
namespace Ui {
    class Info;
}

class Info : public QDialog {
    Q_OBJECT
public:
    explicit Info(QWidget *parent = nullptr) : QDialog(parent), ui(new Ui::Info) {
        ui->setupUi(this);
        this->setWindowTitle("About");
    }
    ~Info() {
        delete ui;
    }

private:
    Ui::Info *ui;
};

#endif // INFO_H
