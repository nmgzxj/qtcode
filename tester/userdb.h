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

#define MAX_STRING_CONTENT_LENGTH    256
#define MAX_RULE_HASH_NODE           1024

typedef struct strHashNode{
    unsigned long sHashKey;
    char sHashContent[MAX_STRING_CONTENT_LENGTH];
}strHashNode;

#define MAX_NUMBER_LENGTH              22
#define MAX_NAME_LENGTH                24

static const char errType_oneCardFiveNumber =0x40;
static const char errType_oneCardMultiName = 0x60;
static const char id_TypeMask = 0x0f;
//个人移动 个人固话 单位移动 单位固话  行业移动  行业固话
static const char id_personMobile     = 0x01;  //...1
static const char id_personTelephone  = 0x02;   //..1.
static const char id_unitMobile       = 0x05;   //.1.1
static const char id_unitTelephone    = 0x06;   //.11.
static const char id_serviceMobile    = 0x09;   //1..1
static const char id_serviceTelephone = 0x0a;   //1.1.
static const char id_typeknown        = 0x0f;   //1111

static const int MAX_NUMBER_HASH_NODE = 65537;

typedef struct stErrorMultiName
{
    char number[MAX_NUMBER_LENGTH];
    char errflag;//0 normal  0x60 errType_oneCardMultiName
    char reserved;
    char origName[MAX_NAME_LENGTH];
    struct stErrorMultiName *next;
} stErrorMultiName;

typedef struct stErrorFiveNum
{
    char number[MAX_NUMBER_LENGTH];
    char errflag;//0 normal  0x40 errType_oneCardFiveNumber
    char reserved;
    unsigned short err1count; //before checkDay
    unsigned short err2count; //after checkDay
    struct stErrorFiveNum *next;
} stErrorFiveNum;

#define MAX_BCHUNKS 2048
#define MAX_BCHUNKNODES 10000

typedef struct bchunk_t{
  int maxchunks;
  int ncount;
  int nsize;
  char *chunks[MAX_BCHUNKS];
} bchunk_t;

class UserDb: public QObject
{
    Q_OBJECT
public:
    UserDb();
    ~UserDb();
    QString mkMutiDir(const QString path);
    void start(){stopped = false;}
    void stop(){stopped = true;}
    void printMessage();
    QString m_filename;
    Report* report;

private:
    bool isNotReg(QString *str);
    bool isNotReg(QString str);
    bool isPersonTypeNok(QString const & str);
    bool isUnitTypeNok(QString const & str);
    bool isPersonNameNok(QString  const &str);
    bool isUnitNameNok(QString  const &str);
    bool isPersonNumNok(QString  const &numstr,QString  const &typestr);
    bool isUnitNumNok(QString  const &str);
    bool isPersonAddNok(QString const & str);
    bool isUnitAddNok(QString const & str);

    int getColNum(QString name);
    QMap<QString,int> col_name_map;
    XMLConfigReader *xmlConfig;
    volatile bool stopped;
    void writeFile(QString filename, int& count,QString qstr = nullptr);
    void flushFile();
    QString readValueToString(QString query);
    QList<QString> readValueToList(QList<QString> inList, QString query,strHashNode *psHNode,int &psHNodeCount);
    QList<QString> readValueToList1(QList<QString> inList, QString query,strHashNode *psHNode,int &psHNodeCount);
    QString delimeter;
    QMap<QString, QList<QString>> fileBuffer;

    QMap<QString,QString> userType;
    QMap<QString,QString> systemValue;
    bool needAgent(QString typestr,QString idCardNum, QString activeTime);
    int getDateForInt(QString activeTime);

    QString maxlimit;
    QList<QString> bizTypeFixed;
    QList<QString> personType;
    QList<QString> m18personType;
    int cstrHashm18personType;
    int cstrHashpersonType;
    int cstrHashbizTypeFixed;
    int cstrHashunitType;
    strHashNode strHashunitType[MAX_RULE_HASH_NODE],strHashpersonType[MAX_RULE_HASH_NODE],strHashbizTypeFixed[MAX_RULE_HASH_NODE];
    strHashNode strHashm18personType[MAX_RULE_HASH_NODE];
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
    int cstrHashpersonNameRule;
    int cstrHashunitNameRule;
    int cstrHashnumRule;
    int cstrHashaddRule;
    int cstrHashnonRealName;
    int cstrHashleaveNet;
    strHashNode strHashpersonNameRule[MAX_RULE_HASH_NODE],strHashunitNameRule[MAX_RULE_HASH_NODE],strHashnumRule[MAX_RULE_HASH_NODE];
    strHashNode strHashaddRule[MAX_RULE_HASH_NODE],strHashnonRealName[MAX_RULE_HASH_NODE],strHashleaveNet[MAX_RULE_HASH_NODE];
    QList<QString> personNameRule;
    QList<QString> unitNameRule;
    QList<QString> numRule;
    QList<QString> addRule;
    QList<QString> nonRealName;
    QList<QString> leaveNet;
    unsigned long strHash(const char *pstr,const size_t strlen);
    bool makeDir();
    void processPersonFixed();
    void processPersonMobile();
    void processUnitFixed();
    void processUnitMobile();
    void processTradeFixed();
    void processTradeMobile();

    int errFiveNumber;
    int errMultiName;
    int errCardCount;
    stErrorMultiName *m_pstErrMultiName[MAX_NUMBER_HASH_NODE];
    stErrorFiveNum   *m_pstErrFiveName[MAX_NUMBER_HASH_NODE];
    bchunk_t  bErrMulti,bErrFive;
    QString dateFormat;
    char id_TypeChar;
    int activeDate;

    void bchunkInit(bchunk_t *pchunk,int nsize);
    void bchunkFree(bchunk_t *pchunk);
    void *bchunkAllocNode(bchunk_t *pchunk);
    char calculateVerifyCode(const char* m_str);

    void processOneCardFiveNumber();
    void processOneCardMultiName();
    void outputSimpleOneCardFiveNumber();
    void writeOneCardFiveNumberFile();
    void outputSearch(const QString filename,const char* checkline,const int index);
    /* 文件输出路径 */
    QString path;
    bool countData();
    void processLine();
    void processLineoutput();
    void readConfig();

    QList<QString> col;
    QString line  = "";
    void initIndex();
    int ownerNameIndex=0;
    int ownerTypeIndex=0;
    int ownerNumIndex=0;
    int ownerAddIndex=0; //证件地址
    int ownerAdd1Index=0;//通讯地址
    int ownerAdd2Index=0;//装机地址
    int agentNameIndex=0;
    int agentTypeIndex=0;
    int agentNumIndex=0;
    int agentAddIndex=0;
    int agentAdd1Index=0;//通讯地址

    int liableNameIndex=0;
    int liableTypeIndex=0;
    int liableNumIndex=0;
    int liableAddIndex=0;
    int liableAdd1Index=0;//通讯地址

    int unitNameIndex=0;
    int unitNumIndex=0;
    int unitTypeIndex=0;
    int unitAddIndex=0;
    int unitAdd1Index=0;//通讯地址
    int unitAdd2Index=0;//装机地址

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
