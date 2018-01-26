#ifndef GENCODE_H
#define GENCODE_H

#include <QString>
#include <QTextCodec>
#include <QDir>

class GenCode
{
public:
    GenCode();
    void test();
    QString loadXml(QString filename);
    void genSql();
};

#endif // GENCODE_H
