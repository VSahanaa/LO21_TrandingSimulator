#ifndef MODEMANUELWIDGET_H
#define MODEMANUELWIDGET_H

#include <QWidget>

namespace Ui {
class modeManuelWidget;
}

class modeManuelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit modeManuelWidget(QWidget *parent = nullptr);
    ~modeManuelWidget();

private:
    Ui::modeManuelWidget *ui;
};

#endif // MODEMANUELWIDGET_H
