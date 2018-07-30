#include "util.h"

Util::Util()
{

}

QString Util::getDateTime(DateTimeType type)
{
    QDateTime datetime = QDateTime::currentDateTime();
    QString date = datetime.toString("yyyy-MM-dd");
    QString time = datetime.toString("hh:mm");
    QString dateAndTime = datetime.toString("yyyy-MM-dd dddd hh:mm");
    if(type == Date)return date;
    else if(type == Time)return time;
    else return dateAndTime;
}

QString Util::getDateTime()
{
    DateTimeType type = DateTime;
    QDateTime datetime = QDateTime::currentDateTime();
    QString date = datetime.toString("yyyy-MM-dd");
    QString time = datetime.toString("hh:mm");
    QString dateAndTime = datetime.toString("yyyy-MM-dd dddd hh:mm");
    if(type == Date)return date;
    else if(type == Time)return time;
    else return dateAndTime;
}

//读取 XML 文档
bool Util::docRead()
{
    QFile file("data.xml");
    if(!file.open(QIODevice::ReadOnly))
            return false;
    if(!doc.setContent(&file)){
        file.close();
        return false;
    }
    file.close();
    return true;
}

//写入 XML 文档
bool Util::docWrite()
{
    QFile file("data.xml");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
            return false;
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
    return true;
}
