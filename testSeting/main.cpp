#include <QCoreApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSettings *settings = new QSettings (filename,QSettings::IniFormat);
    settings->beginGroup("SerialPort");
    int port = settings->value("port",0).toInt();
    int baudRate = settings->value("baudRate",9600).toInt();
    int dataBits = settings->value("dataBits",8).toInt();
    int parity = settings->value("parity",0).toInt();
    int stopBits = settings->value("stopBits",0).toInt();
    int flowControl = settings->value("flowControl",0).toInt();
    delete settings;    //删除指针，防止内存泄露
    return a.exec();
}
