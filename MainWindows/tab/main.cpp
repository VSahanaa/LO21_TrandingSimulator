#include "tab.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TAB w;
    w.show();

    return a.exec();
}
