#include "xmlconfig.h"

#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QDebug>
#include <iostream>

XmlConfig::XmlConfig()
{

}
QList<QStringList> XmlConfig::readAutoid(){
    enum ExitCode
    {
        Success,
        ParseFailure,
        ArgumentError,
        WriteError,
        FileFailure
    };
    QTextStream errorStream(stderr);
    QString inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-autoid.xml";
    QFile inputFile(inputFilePath);
    if (!QFile::exists(inputFilePath))
    {
        errorStream << QString("File %1 does not exist.\n").arg(inputFilePath);
//        return FileFailure;

    } else if (!inputFile.open(QIODevice::ReadOnly)) {
        errorStream << QString(
                       "Failed to open file %1.\n").arg(inputFilePath);
//        return FileFailure;
    }
    QFile outputFile;
    if (!outputFile.open(stdout, QIODevice::WriteOnly))
    {
        errorStream << QString("Failed to open stdout.");
//        return WriteError;
    }

//! [0]
    QXmlStreamReader reader(&inputFile);
    QXmlStreamWriter writer(&outputFile);
    QList<QStringList> rtnList;
    QStringList tempLine;
//! [0]

//! [1]
    while (!reader.atEnd())
    {
        reader.readNext();
        tempLine.clear();
        if (reader.error())
        {
            errorStream << QString(
                           "Error: %1 in file %2 at line %3, column %4.\n").arg(
                               reader.errorString(), inputFilePath,
                               QString::number(reader.lineNumber()),
                               QString::number(reader.columnNumber()));
//            return ParseFailure;
//! [1]

//! [2]
        } else
           // writer.writeCurrentToken(reader);
        if(reader.name()=="sub"){
            qDebug()<<"category="<<reader.attributes().value("category");
            tempLine.append(reader.attributes().value("category").toString());
            //            qDebug()<<"lineNumber="<<reader.lineNumber();
            //            qDebug()<<"name="<<reader.name();
            //            qDebug()<<"text="<<reader.text();
            //            qDebug()<<"tokenString="<<reader.tokenString();
            //            qDebug()<<"qualifiedName="<<reader.qualifiedName();
            qDebug()<<"readElementText"<<reader.readElementText();
            tempLine.append(reader.readElementText());
        }
        rtnList.append(tempLine);
    }
//! [2]
        return rtnList;
//    return Success;
}

