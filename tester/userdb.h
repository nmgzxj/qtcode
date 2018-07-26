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
    void connDb();
};

#endif // USERDB_H
