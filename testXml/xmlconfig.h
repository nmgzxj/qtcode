#ifndef XMLCONFIG_H
#define XMLCONFIG_H
#include <QString>
#include <QList>
#include <QStringList>

class XmlConfig
{
public:
    XmlConfig();
    QList<QStringList> readAutoid();
};

#endif // XMLCONFIG_H
