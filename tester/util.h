#ifndef UTIL_H
#define UTIL_H
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QJsonDocument>
#include "qdom.h"
//#include <QtXml/QDomDocument>
#include <QDateTime>


class Util
{
public:
    Util();
    enum DateTimeType{Time,Date,DateTime};
    QString getDateTime(DateTimeType type);
    QString getDateTime();
private:
    QDomDocument doc;
    bool docRead();
    bool docWrite();
};

#endif // UTIL_H
