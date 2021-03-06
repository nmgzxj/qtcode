﻿#ifndef XMLCONFIGREADER_H
#define XMLCONFIGREADER_H
#include <QString>
#include <QList>
#include <QStringList>
#include <QTextCodec>
#include <QMap>
//QString QCoreApplication::applicationDirPath()


class XMLConfigReader
{
public:
    XMLConfigReader();
    QList<QList<QString>> readAutoid();
    void writeAutoid(QList<QList<QString>>);
    void addAutoid(QString parent, QString item, int offset);
    void updateAutoid(QString parent, QList<QList<QString>> items, int offset);
    void deleteAutoid(QString item);
    QList<QString> readValue(QString var);
    void writeValue(QString menu,QList<QString> value);
    void processFile(QString* inputFilePath, QString* child, QString* var);
    void writeSystemValue(QString dataRange, QString compliantDate, QString onecard2fiveDate, QString randomDateLabel);
    QMap<QString,QString> readSystemValue();
    void writeWorkingpathValue(QString workingpath);
    QMap<QString,QString> readWorkingpathValue();
    void writeDelimiterValue(QString delimiter);
    QString readDelimiterValue();
    void writeItemnumValue(QString itemnum);
    QMap<QString,QString> readItemnumValue();
    void writedivfileValue(QString divfile);
    QMap<QString,QString> readdivfileValue();
    void writeDateformatValue(QString dateformat);
    QMap<QString,QString> readDateformatValue();
    void writeCommonRuleValue(QMap<QString,QString> map);
    QMap<QString,QString> readCommonRuleValue(QList<QString> queryList);
    QMap<QString,QString> readUserType();
    QString PATH;
    void writeUserType(QMap<QString,QString> userTypeList);
};

#endif // XMLCONFIGREADER_H
