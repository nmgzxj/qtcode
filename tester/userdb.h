#ifndef USERDB_H
#define USERDB_H
#include <QDebug>
#include <QFile>
#include <QThread>
#include <QDir>
#include <QTextCodec>
#include <QTime>
#include <QHash>
#include <QMessageBox>
#include <QBuffer>
#include "xmlconfigreader.h"
#define COL_NUM 42
#include "report.h"

class UserDb: public QObject
{
    Q_OBJECT
public:
    UserDb();
    ~UserDb();
    QString mkMutiDir(const QString path);
    bool fileIsExists(QString filename);
    void printMessage();
    void start();
    void stop();
    QString filename;
    Report* report;


private:
    bool isNotReg(QString *str);
    bool isNotReg(QString str);
    bool isPersonTypeNok(QString const & str);
    bool isUnitTypeNok(QString const & str);
    bool isPersonNameNok(QString  const &str);
    bool isUnitNameNok(QString  const &str);
    bool isPersonNumNok(QString  const &str);
    bool isUnitNumNok(QString  const &str);
    bool isPersonAddNok(QString const & str);
    bool isUnitAddNok(QString const & str);

    QString getColName(QString name);
    int getColNum(QString name);
    QString getCol(QString name);
    QMap<QString,int> col_name_map;
    XMLConfigReader *xmlConfig;
    volatile bool stopped;
    void writeFile(QString filename, int count);
    void flushFile();
    QString readValueToString(QString query);
    QList<QString> readValueToList(QList<QString> inList, QString query);
    QString delimeter;
    QMap<QString, QList<QString>> fileBuffer;

    QMap<QString,QString> userType;
    QMap<QString,QString> onecardMultiName;
    QMap<QString,QString> onecardFiveCode;
    bool needAgent(QString idCardNum, QString activeTime);
    int getDateForInt(QString activeTime);

    QString maxlimit;
    QList<QString> bizTypeFixed;
    QList<QString> personType;
    int personNameMin;
    int personNameMax;
    QString personNamePermit;
    int personNumMin;
    int personNumMax;
    QString personIntervalTime;
    int personAddMin;
    int personAddMax;
    QList<QString> unitType;
    int unitNameMin;
    int unitNameMax;
    int unitNumMin;
    int unitNumMax;
    QString unitIntervalTime;
    int unitAddMin;
    int unitAddMax;
    QList<QString> personNameRule;
    QList<QString> unitNameRule;
    QList<QString> numRule;
    QList<QString> addRule;
    QList<QString> nonRealName;
    QList<QString> leaveNet;
    bool makeDir();
    void processPersonFixed();
    void processPersonMobile();
    void processUnitFixed();
    void processUnitMobile();
    void processTradeFixed();
    void processTradeMobile();

    void processOneCardFiveNumber();
    void processOneCardMultiName();
    /* 文件输出路径 */
    QString path;
    bool countData();
    void processLine();
    /* 输出文件 */
    void savePersonMobileOwnerNameNotReg();
    void savePersonMobileOwnerTypeNotReg();
    void savePersonMobileOwnerNumNotReg();
    void savePersonMobileOwnerAddNotReg();
    void savePersonMobileOwnerNameNumNotReg();
    void savePersonMobileOwnerNameAddNotReg();
    void savePersonMobileOwnerNumAddNotReg();
    void savePersonMobileOwnerNameNumAddNotReg();
    void savePersonMobileOwnerTyteNok();
    void savePersonMobileOwnerNameNok();
    void savePersonMobileOwnerNumNok();
    void savePersonMobileOwnerAddNok();
    void savePersonMobileOwnerNameNumNok();
    void savePersonMobileOwnerNameAddNok();
    void savePersonMobileOwnerNumAddNok();
    void savePersonMobileOwnerNameNumAddNok();
    void savePersonFixedOk();
    void saveAllNotReg();
    void saveAllNok();
    void saveAbnormal();
    void saveFieldAbnormal();
    void saveAllOk();
    void saveWaitData();
    void savePersonMobileOk();
    void savePersonFixedOwnerNameNotReg();
    void savePersonFixedOwnerTypeNotReg();
    void savePersonFixedOwnerNumNotReg();
    void savePersonFixedOwnerAddNotReg();
    void savePersonFixedOwnerNameNumNotReg();
    void savePersonFixedOwnerNameAddNotReg();
    void savePersonFixedOwnerNumAddNotReg();
    void savePersonFixedOwnerNameNumAddNotReg();
    void savePersonFixedOwnerTypeNok();
    void savePersonFixedOwnerNameNok();
    void savePersonFixedOwnerNumNok();
    void savePersonFixedOwnerAddNok();
    void savePersonFixedOwnerNameNumNok();
    void savePersonFixedOwnerNameAddNok();
    void savePersonFixedOwnerNumAddNok();
    void savePersonFixedOwnerNameNumAddNok();
    void savePersonMobileAgentNotReg();
    void savePersonFixedAgentNotReg();
    void savePersonMobileAgentNok();
    void savePersonFixedAgentNok();
    void saveUnitMobileOk();
    void saveUnitMobileOwnerNotReg();
    void saveUnitMobileAgentNotReg();
    void saveUnitMobileUnitNotReg();
    void saveUnitMobileOwnerAgentNotReg();
    void saveUnitMobileOwnerUnitNotReg();
    void saveUnitMobileAgentUnitNotReg();
    void saveUnitMobileOwnerAgentUnitNotReg();
    void saveUnitMobileOwnerNok();
    void saveUnitMobileAgentNok();
    void saveUnitMobileUnitNok();
    void saveUnitMobileOwnerAgentNok();
    void saveUnitMobileOwnerUnitNok();
    void saveUnitMobileAgentUnitNok();
    void saveUnitMobileOwnerAgentUnitNok();
    void saveUnitFixedOk();
    void saveUnitFixedOwnerNotReg();
    void saveUnitFixedAgentNotReg();
    void saveUnitFixedUnitNotReg();
    void saveUnitFixedOwnerAgentNotReg();
    void saveUnitFixedOwnerUnitNotReg();
    void saveUnitFixedAgentUnitNotReg();
    void saveUnitFixedOwnerAgentUnitNotReg();
    void saveUnitFixedAgentNok();
    void saveUnitFixedUnitNok();
    void saveUnitFixedAgentUnitNok();
    void saveTradeMobileOk();
    void saveTradeMobileOwnerNotReg();
    void saveTradeMobileAgentNotReg();
    void saveTradeMobileUnitNotReg();
    void saveTradeMobileLiableNotReg();
    void saveTradeMobileAgentUnitNotReg();
    void saveTradeMobileLiableAgentNotReg();
    void saveTradeMobileLiableUnitNotReg();
    void saveTradeMobileLiableAgentUnitNotReg();
    void saveTradeMobileOwnerNok();
    void saveTradeMobileAgentNok();
    void saveTradeMobileAgentUnitNok();
    void saveTradeMobileLiableAgentNok();
    void saveTradeMobileLiableAgentUnitNok();
    void saveTradeMobileUnitNok();
    void saveTradeMobileLiableNok();
    void saveTradeMobileLiableUnitNok();
    void saveTradeFixedOk();
    void saveTradeFixedOwnerNotReg();
    void saveTradeFixedOwnerNok();
    void saveTradeFixedAgentNotReg();
    void saveTradeFixedUnitNotReg();
    void saveTradeFixedLiableNotReg();
    void saveTradeFixedAgentUnitNotReg();
    void saveTradeFixedAgentNok();
    void saveTradeFixedAgentUnitNok();
    void saveTradeFixedUnitNok();
    void saveTradeFixedLiableNok();
    void saveTradeFixedAgentLiableNotReg();
    void saveTradeFixedLiableUnitNotReg();
    void saveTradeFixedAgentLiableUnitNotReg();
    void saveTradeFixedAgentLiableNok();
    void saveTradeFixedLiableUnitNok();
    void saveTradeFixedAgentLiableUnitNok();
    void savePersonMobileOneCard();
    void saveLeaveNet();
    void saveOnecardMultiName();
    void saveOnecardFiveCode();
    void readConfig();

    QList<QString> col;
    QString line  = "";
    void initIndex();
    int ownerNameIndex=0;
    int ownerTypeIndex=0;
    int ownerNumIndex=0;
    int ownerAddIndex=0;
    int agentNameIndex=0;
    int agentTypeIndex=0;
    int agentNumIndex=0;
    int agentAddIndex=0;
    int liableNameIndex=0;
    int liableTypeIndex=0;
    int liableNumIndex=0;
    int liableAddIndex=0;
    int unitNameIndex=0;
    int unitNumIndex=0;
    int unitTypeIndex=0;
    int unitAddIndex=0;
    int msisdnIndex=0;
    int activeTimeIndex=0;
    int codeStatusIndex=0;
    int bizTypeIndex=0;
    int userTypeInex=0;





signals:
    void message(const QString& info);
    void messageWarning(const QString& str);
    void progress(int present);
public slots:
    void run();

};

#endif // USERDB_H
