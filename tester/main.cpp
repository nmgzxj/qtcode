#include "tester.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tester w;
    w.show();

    return a.exec();
}
