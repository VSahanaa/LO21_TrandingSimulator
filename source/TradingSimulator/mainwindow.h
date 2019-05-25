#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeMode(int mode);
    QWidget *getWidget(int num);

private slots:

signals:
    void closed();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *eve) {emit closed(); eve->accept();}
};

#endif // MAINWINDOW_H
