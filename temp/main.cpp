#include <QCoreApplication>
#include <QDebug>

bool isDigitStr(QString src)
{
    QByteArray ba = src.toLatin1();//QString 转换为 char*
     const char *s = ba.data();

    while(*s && *s>='0' && *s<='9') s++;
    return !(*s);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "It's Works!";

    QString num = "122s23";
    //return num!=null && num.matches("\\d+\\.?\\d*");
    qDebug() << isDigitStr(num);
    return a.exec();
}
