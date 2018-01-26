#include "threaddialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ThreadDialog *threaddialog = new ThreadDialog;
    threaddialog->exec();
    return app.exec();
}
