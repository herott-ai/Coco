#include "newbee.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Newbee w;
    w.show();
    return a.exec();
}
