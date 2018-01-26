#include "gencode.h"
#include <iostream>
#include "util.h"
#include "setup.h"
#include <QDebug>
#include "xmlstreamreader.h"




QString str2qstr(const std::string str)
{
    return QString::fromLocal8Bit(str.data());
}

std::string qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return std::string(cdata);
}

GenCode::GenCode()
{
//    Util::DateTimeType dtt = Util::Date;
    std::cout<<"test\n"<<"\n";
}

void GenCode::test()
{
    std::cout<<"ok\n";//<<Util::getDateTime();
    QString qs  = loadXml(QString("../../../config/config-autoid.xml"));
    qDebug("print %s",qPrintable(qs));
    XmlStreamReader* r = new XmlStreamReader();
    r->readFile(QString("../../../config/config-autoid.xml"));
}

void GenCode::genSql(){
    QString sql = "";

    qDebug("sql is \n%s",qPrintable(sql));
}

QString GenCode::loadXml(QString filename){
    QTextCodec *code = QTextCodec::codecForName("GB2312");//设置文件编码
    QString returnStr;
//    QString filename = "../../../config/config-autoid.xml";
    QTextStream cin(stdin, QIODevice::ReadOnly);
    QTextStream cout(stdout, QIODevice::WriteOnly);
    QTextStream cerr(stderr, QIODevice::WriteOnly);
    cout <<QDir::currentPath()<<endl;
    QFile file(filename);

     if (file.open(QFile::ReadOnly | QFile::Text))
     {
         printf("file is ok.\n");
         QTextStream stream(&file);
         stream.setCodec(code);
         QString line;

//model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());
         do
         {
             line = stream.readLine();

             returnStr += line;
             returnStr += '\n';
         } while (!line.isEmpty());

       file.close();
     }
     else
     {
         printf("file open failed.\n");
     }
     return returnStr;
}
