#ifndef USERDB_H
#define USERDB_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDir>
#include <QTextCodec>
#include <QTime>
#include "userfile.h"
#define strItemDelimeter "||"


class UserDb: public QObject
{
public:
    UserDb();
    void run();
    bool insertDb(QString filename);
    bool createTable();
    bool fileIsExists(QString filename);
private:
    QSqlDatabase db1;
    UserFile* userFile;
    void connDb();
    int getCol_num(QString name);
    QMap<QString,int> col_name_map;
    XMLConfigReader *xmlConfig;
};

#endif // USERDB_H
