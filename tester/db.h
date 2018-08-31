#ifndef DB_H
#define DB_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

static QSqlDatabase db;

static void createConnection()
{

    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("localhost");
        db.setDatabaseName(":memory:");

        if(db.open())
        {
            qDebug()<<"数据库连接成功！";
        }
        else
        {
            qDebug()<<"数据库连接错误！";
        }
    }
    QSqlQuery query;

    //创建密码表
    query.exec("create table password(pwd varchar primary key)");
    query.exec("delete password");
    query.exec("insert into password values('1')");
}


//class Db
//{
//public:
//    Db();
//    static QSqlDatabase db;
//    static void createConnection();

//};

//QSqlDatabase Db::db = QSqlDatabase::addDatabase("QSQLITE");
#endif // DB_H
