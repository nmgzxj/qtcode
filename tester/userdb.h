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
#include "report.h"

#define strItemDelimeter "||"


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
    void processLine(QList<QString> line);
    void savePersonMobileOwnerNameNotReg(QList<QString> line);
    void savePersonMobileOwnerTypeNotReg(QList<QString> line);
    void savePersonMobileOwnerNumNotReg(QList<QString> line);
    void savePersonMobileOwnerAddNotReg(QList<QString> line);
    void savePersonMobileOwnerNameNumNotReg(QList<QString> line);
    void savePersonMobileOwnerNameAddNotReg(QList<QString> line);
    void savePersonMobileOwnerNumAddNotReg(QList<QString> line);
    void savePersonMobileOwnerNameNumAddNotReg(QList<QString> line);
    void savePeronMobileOwnerTyteNok(QList<QString> line);
    void savePeronMobileOwnerNameNok(QList<QString> line);
    void savePeronMobileOwnerNumNok(QList<QString> line);
    void savePeronMobileOwnerAddNok(QList<QString> line);
    void savePeronMobileOwnerNameNumNok(QList<QString> line);
    void savePeronMobileOwnerNameAddNok(QList<QString> line);
    void savePeronMobileOwnerNumAddNok(QList<QString> line);
    void savePeronMobileOwnerNameNumAddNok(QList<QString> line);
    void savePersonFixedOk(QList<QString> line);
    void saveAllNotReg(QList<QString> line);
    void saveAllNok(QList<QString> line);
    void saveAbnormal(QList<QString> line);
    void saveFieldAbnormal(QList<QString> line);
    void saveAllOk(QList<QString> line);
    void saveWaitData(QList<QString> line);
    void savePersonMobileOk(QList<QString> line);
    void savePersonFixedOwnerNameNotReg(QList<QString> line);
    void savePersonFixedOwnerTypeNotReg(QList<QString> line);
    void savePersonFixedOwnerNumNotReg(QList<QString> line);
    void savePersonFixedOwnerAddNotReg(QList<QString> line);
    void savePersonFixedOwnerNameNumNotReg(QList<QString> line);
    void savePersonFixedOwnerNameAddNotReg(QList<QString> line);
    void savePersonFixedOwnerNumAddNotReg(QList<QString> line);
    void savePersonFixedOwnerNameNumAddNotReg(QList<QString> line);
    void savePersonFixedOwnerTypeNok(QList<QString> line);
    void savePersonFixedOwnerNameNok(QList<QString> line);
    void savePersonFixedOwnerNumNok(QList<QString> line);
    void savePersonFixedOwnerAddNok(QList<QString> line);
    void savePersonFixedOwnerNameNumNok(QList<QString> line);
    void savePersonFixedOwnerNameAddNok(QList<QString> line);
    void savePersonFixedOwnerNumAddNok(QList<QString> line);
    void savePersonFixedOwnerNameNumAddNok(QList<QString> line);
    void savePeronMobileAgentNotReg(QList<QString> line);
    void savePersonFixedAgentNotReg(QList<QString> line);
    void savePeronMobileAgentNok(QList<QString> line);
    void savePersonFixedAgentNok(QList<QString> line);
    void saveUnitMobileOk(QList<QString> line);
    void saveUnitMobileOwnerNotReg(QList<QString> line);
    void saveUnitMobileOwnerAgentNotReg(QList<QString> line);
    void saveUnitMobileUnitNotReg(QList<QString> line);
    void saveUnitMobileOwnerUnitNotReg(QList<QString> line);
    void saveUnitMobileAgentUnitNotReg(QList<QString> line);
    void saveUnitMobileOwnerAgentUnitAddNotReg(QList<QString> line);
    void saveUnitMobileOwnerNok(QList<QString> line);
    void saveUnitMobileAgentNok(QList<QString> line);
    void saveUnitMobileUnitNok(QList<QString> line);
    void saveUnitMobileOwnerAgentNok(QList<QString> line);
    void saveUnitMobileOwnerUnitNok(QList<QString> line);
    void saveUnitMobileAgentUnitNok(QList<QString> line);
    void saveUnitMobileOwnerAgentUnitNok(QList<QString> line);
    void saveUnitFixedOk(QList<QString> line);
    void saveUnitFixedOwnerNotReg(QList<QString> line);
    void saveUnitFixedAgentNotReg(QList<QString> line);
    void saveUnitFixedUnitNotReg(QList<QString> line);
    void saveUnitFixedOwnerAgentNotReg(QList<QString> line);
    void saveUnitFixedOwnerUnitNotReg(QList<QString> line);
    void saveUnitFixedAgentUnitNotReg(QList<QString> line);
    void saveUnitFixedOwnerAgentUnitAddNotReg(QList<QString> line);
    void saveUnitFixedAgentNok(QList<QString> line);
    void saveUnitFixedUnitNok(QList<QString> line);
    void saveUnitFixedAgentUnitNok(QList<QString> line);
    void saveTradeMobileOk(QList<QString> line);
    void saveTradeMobileAgentNotReg(QList<QString> line);
    void saveTradeMobileUnitNotReg(QList<QString> line);
    void saveTradeMobileLiableNotReg(QList<QString> line);
    void saveTradeMobileAgentUnitNotReg(QList<QString> line);
    void saveTradeMobileLiableAgentNotReg(QList<QString> line);
    void saveTradeMobileLiableUnitNotReg(QList<QString> line);
    void saveTradeMobileLiableAgentUnitAddNotReg(QList<QString> line);
    void saveTradeMobileAgentNok(QList<QString> line);
    void saveTradeMobileAgentUnitNok(QList<QString> line);
    void saveTradeMobileLiableAgentNok(QList<QString> line);
    void saveTradeMobileLiableAgentUnitAddNok(QList<QString> line);
    void saveTradeMobileUnitNok(QList<QString> line);
    void saveTradeMobileLiableNok(QList<QString> line);
    void saveTradeMobileLiableUnitNok(QList<QString> line);
    void saveTradeFixedOk(QList<QString> line);
    void saveTradeFixedAgentNotReg(QList<QString> line);
    void saveTradeFixedUnitNotReg(QList<QString> line);
    void saveTradeFixedAgentUnitNotReg(QList<QString> line);
    void saveTradeFixedAgentNok(QList<QString> line);
    void saveTradeFixedAgentUnitNok(QList<QString> line);
    void saveTradeFixedUnitNok(QList<QString> line);
    void saveOneCard(QList<QString> line);
private:
    QString getColName(QString name);
    QString getCol(QString name);
    QMap<QString,int> col_name_map;
    XMLConfigReader *xmlConfig;
    volatile bool stopped;
    Report* report;
    void writeFile(QString filename, QList<QString> line);

signals:
    void message(const QString& info);
    void progress(int present);
public slots:
    void run();

};

#endif // USERDB_H
