#ifndef USERDB_H
#define USERDB_H
#include <QDebug>
#include <QFile>
#include <QThread>
#include <QDir>
#include <QTextCodec>
#include <QTime>
#include<QSqlRecord>
//#include "userfile.h"UserDb
#include "xmlconfigreader.h"
#define COL_NUM 42
#include "db.h"

#define strItemDelimeter "||"


class UserDb: public QObject
{
    Q_OBJECT
public:
    UserDb();

    bool insertDb(QString filename);
    bool createTable();
    bool fileIsExists(QString filename);
    void printMessage();
    void start();
    void stop();
    QList<QString> readTable(QString sql);
    void printData(QString table);
private:
    QSqlDatabase db1;
//    UserFile* userFile;
    int getCol_num(QString name);
    QMap<QString,int> col_name_map;
    XMLConfigReader *xmlConfig;
    volatile bool stopped;
    bool m_isStop;
signals:
    void message(const QString& info);
    void progress(int present);
public slots:
    void run();

};

#endif // USERDB_H
