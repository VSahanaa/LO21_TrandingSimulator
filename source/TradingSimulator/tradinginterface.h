#ifndef TRADINGINTERFACE_H
#define TRADINGINTERFACE_H

#include <QWidget>

namespace Ui {
    class TradingInterface;
}

class TradingInterface : public QWidget {
    Q_OBJECT
public:
    explicit TradingInterface(QWidget *parent = nullptr);
    ~TradingInterface();

private:
    Ui::TradingInterface *ui;
};

#endif // TRADINGINTERFACE_H
