﻿#ifndef USERDB_H
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
#include "report.h"

class UserDb: public QObject
{
    Q_OBJECT
public:
    UserDb();
    ~UserDb();
    bool insertDb(QString filename);
    bool createTable();
    bool fileIsExists(QString filename);
    void printMessage();
    void start();
    void stop();
    QList<QString> readTable(QString sql);
    void printData(QString table);
    QString filename;
    void createReport();
    bool countData();
    void processLine(QString line);
    void savePersonMobileOwnerNameNotReg(QString line);
    void savePersonMobileOwnerTypeNotReg(QString line);
    void savePersonMobileOwnerNumNotReg(QString line);
    void savePersonMobileOwnerAddNotReg(QString line);
    void savePersonMobileOwnerNameNumNotReg(QString line);
    void savePersonMobileOwnerNameAddNotReg(QString line);
    void savePersonMobileOwnerNumAddNotReg(QString line);
    void savePersonMobileOwnerNameNumAddNotReg(QString line);
    void savePeronMobileOwnerTyteNok(QString line);
    void savePeronMobileOwnerNameNok(QString line);
    void savePeronMobileOwnerNumNok(QString line);
    void savePeronMobileOwnerAddNok(QString line);
    void savePeronMobileOwnerNameNumNok(QString line);
    void savePeronMobileOwnerNameAddNok(QString line);
    void savePeronMobileOwnerNumAddNok(QString line);
    void savePeronMobileOwnerNameNumAddNok(QString line);
    void savePersonFixedOk(QString line);
    void saveAllNotReg(QString line);
    void saveAllNok(QString line);
    void saveAbnormal(QString line);
    void saveFieldAbnormal(QString line);
    void saveAllOk(QString line);
    void saveWaitData(QString line);
    void savePersonMobileOk(QString line);
    void savePersonFixedOwnerNameNotReg(QString line);
    void savePersonFixedOwnerTypeNotReg(QString line);
    void savePersonFixedOwnerNumNotReg(QString line);
    void savePersonFixedOwnerAddNotReg(QString line);
    void savePersonFixedOwnerNameNumNotReg(QString line);
    void savePersonFixedOwnerNameAddNotReg(QString line);
    void savePersonFixedOwnerNumAddNotReg(QString line);
    void savePersonFixedOwnerNameNumAddNotReg(QString line);
    void savePersonFixedOwnerTypeNok(QString line);
    void savePersonFixedOwnerNameNok(QString line);
    void savePersonFixedOwnerNumNok(QString line);
    void savePersonFixedOwnerAddNok(QString line);
    void savePersonFixedOwnerNameNumNok(QString line);
    void savePersonFixedOwnerNameAddNok(QString line);
    void savePersonFixedOwnerNumAddNok(QString line);
    void savePersonFixedOwnerNameNumAddNok(QString line);
    void savePeronMobileAgentNotReg(QString line);
    void savePersonFixedAgentNotReg(QString line);
    void savePeronMobileAgentNok(QString line);
    void savePersonFixedAgentNok(QString line);
    void saveUnitMobileOk(QString line);
    void saveUnitMobileOwnerNotReg(QString line);
    void saveUnitMobileAgentNotReg(QString line);
    void saveUnitMobileUnitNotReg(QString line);
    void saveUnitMobileOwnerUnitNotReg(QString line);
    void saveUnitMobileAgentUnitNotReg(QString line);
    void saveUnitMobileOwnerAgentUnitNotReg(QString line);
    void saveUnitMobileOwnerNok(QString line);
    void saveUnitMobileAgentNok(QString line);
    void saveUnitMobileUnitNok(QString line);
    void saveUnitMobileOwnerAgentNok(QString line);
    void saveUnitMobileOwnerUnitNok(QString line);
    void saveUnitMobileAgentUnitNok(QString line);
    void saveUnitMobileOwnerAgentUnitNok(QString line);
    void saveUnitFixedOk(QString line);
    void saveUnitFixedOwnerNotReg(QString line);
    void saveUnitFixedAgentNotReg(QString line);
    void saveUnitFixedUnitNotReg(QString line);
    void saveUnitFixedOwnerAgentNotReg(QString line);
    void saveUnitFixedOwnerUnitNotReg(QString line);
    void saveUnitFixedAgentUnitNotReg(QString line);
    void saveUnitFixedOwnerAgentUnitNotReg(QString line);
    void saveUnitFixedAgentNok(QString line);
    void saveUnitFixedUnitNok(QString line);
    void saveUnitFixedAgentUnitNok(QString line);
    void saveTradeMobileOk(QString line);
    void saveTradeMobileAgentNotReg(QString line);
    void saveTradeMobileUnitNotReg(QString line);
    void saveTradeMobileLiableNotReg(QString line);
    void saveTradeMobileAgentUnitNotReg(QString line);
    void saveTradeMobileLiableAgentNotReg(QString line);
    void saveTradeMobileLiableUnitNotReg(QString line);
    void saveTradeMobileLiableAgentUnitNotReg(QString line);
    void saveTradeMobileAgentNok(QString line);
    void saveTradeMobileAgentUnitNok(QString line);
    void saveTradeMobileLiableAgentNok(QString line);
    void saveTradeMobileLiableAgentUnitNok(QString line);
    void saveTradeMobileUnitNok(QString line);
    void saveTradeMobileLiableNok(QString line);
    void saveTradeMobileLiableUnitNok(QString line);
    void saveTradeFixedOk(QString line);
    void saveTradeFixedAgentNotReg(QString line);
    void saveTradeFixedUnitNotReg(QString line);
    void saveTradeFixedAgentUnitNotReg(QString line);
    void saveTradeFixedAgentNok(QString line);
    void saveTradeFixedAgentUnitNok(QString line);
    void saveTradeFixedUnitNok(QString line);
    void savePersonMobileOneCard(QString line);
private:
    QString getColName(QString name);
    int getColNum(QString name);
    QString getCol(QString name);
    QMap<QString,int> col_name_map;
    XMLConfigReader *xmlConfig;
    volatile bool stopped;
    Report* report;
    void writeFile(QString filename, QString line);
    QString delimeter;
    QMap<QString,QString> userType;
signals:
    void message(const QString& info);
    void progress(int present);
public slots:
    void run();

};

#endif // USERDB_H
