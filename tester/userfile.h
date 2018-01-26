#ifndef USERFILE_H
#define USERFILE_H
#include <QString>
#include <QFile>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QThread>
#define strItemDelimeter "||"
#define COL_NUM 42

class UserFile: public QThread
{
public:
    UserFile();
    void stop();
    bool writeLog(QString msg);
    bool insertDb(QString filename);
    bool fileIsExists(QString filename);
    bool readRule();
    bool analysisData(QList<QList<QString>> list);
    bool writeFile(QString filename,QList<QString> list);
    bool createTable();
    QList<QString> readTable(QString sql);
    QList<QList<QString>> insertList(QString filename);
protected:
     void run();
private:
    QString col_name[42];
    QString col_data[42];

    volatile bool stopped;

};

#endif // USERFILE_H
