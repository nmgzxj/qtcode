#ifndef USERFILE_H
#define USERFILE_H
#include <QString>
#include <QFile>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QThread>
#include <QSqlRecord>
#include <QSqlError>
#define strItemDelimeter "||"
#define COL_NUM 42
#include "xmlconfigreader.h"
#include "report.h"
#include <QDir>
#include <QList>
#include <QMutex>
#include <QTextCodec>

class UserFile: public QObject
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
    void printMessage();
    void setFileName(QString fileName);
    int getCol_num(QString name);
    Ui::Report *report;
    bool isFinsh = false;
    bool processPersonMobile(QList<QString> line);
    bool processPersonFixed(QList<QString> line);
    void processLine(QList<QString> line);
    bool processUnitMobile(QList<QString> line);
    bool processUnitFixed(QList<QString> line);
    bool processTradeMobile(QList<QString> line);
    bool processTradeFixed(QList<QString> line);

    void savePersonMobileOwnerNameNotReg(QList<QString> line);
    void savePersonMobileOwnerTypeNotReg(QList<QString> line);
    void savePersonMobileOwnerNumNotReg(QList<QString> line);
    void savePersonMobileOwnerAddNotReg(QList<QString> line);
    void savePersonMobileOwnerNameNumNotReg(QList<QString> line);
    void savePersonMobileOwnerNameAddNotReg(QList<QString> line);
    void savePersonMobileOwnerNumAddNotReg(QList<QString> line);
    void savePersonMobileOwnerNameNumAddNotReg(QList<QString> line);
    void saveAllNotReg(QList<QString> line);

    void saveUnitFixedOwnerNotReg(QList<QString> line);
    void saveUnitFixedAgentNotReg(QList<QString> line);
    void saveUnitFixedUnitNotReg(QList<QString> line);
    void saveUnitFixedOwnerAgentNotReg(QList<QString> line);
    void saveUnitFixedOwnerUnitNotReg(QList<QString> line);
    void saveUnitFixedAgentUnitNotReg(QList<QString> line);
    void saveUnitFixedOwnerAgentUnitAddNotReg(QList<QString> line);

    void saveTradeMobileAgentNotReg(QList<QString> line);
    void saveTradeMobileUnitNotReg(QList<QString> line);
    void saveTradeMobileLiableNotReg(QList<QString> line);
    void saveTradeMobileAgentUnitNotReg(QList<QString> line);
    void saveTradeMobileLiableAgentNotReg(QList<QString> line);
    void saveTradeMobileLiableUnitNotReg(QList<QString> line);
    void saveTradeMobileLiableAgentUnitAddNotReg(QList<QString> line);
    void saveTradeFixedAgentNotReg(QList<QString> line);
    void saveTradeFixedUnitNotReg(QList<QString> line);
    void saveTradeFixedAgentUnitNotReg(QList<QString> line);

signals:
    void message(const QString& info);
    void progress(int present);
public slots:
    void run();
private:
//    QString col_name[42];
//    QString col_data[42];
    volatile bool stopped;
    int m_runCount;
    int m_runCount2;
    bool m_isStop;
    QString fileName;
    QMutex m_stopMutex;
    XMLConfigReader *xmlConfig;
    QMap<QString,int> col_name_map;
    QMap<QString,int>::iterator it;
};

#endif // USERFILE_H
