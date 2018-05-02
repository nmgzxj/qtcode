#include "testsignal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestSignal w;
    w.show();

    return a.exec();
}
