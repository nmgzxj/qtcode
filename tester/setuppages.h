#ifndef SETUPPAGES_H
#define SETUPPAGES_H
#include <QWidget>
#include <QTableWidget>
#include <QDebug>
#include <QMessageBox>
#include <QList>
#include <QString>
#include <QStringList>
#include <QHash>
#include "xmlconfigreader.h"
#include <QLineEdit>


using namespace std;


class SetupPages
{
public:
    SetupPages();
};


class ColumnPage : public QWidget
{
    Q_OBJECT
public:
    ColumnPage(QWidget *parent = 0);
public slots:
    void add();
    void del();
    void autoidSave();
private:
    QTableWidget *table;
    QList<QList<QString>> autoid;
    void autoidInit();
    XMLConfigReader *xmlConfig;

};

class RulePage : public QWidget
{
public:
    RulePage(QWidget *parent = 0);
};

class SystemPage : public QWidget
{
    Q_OBJECT
public:
    SystemPage(QWidget *parent = 0);
public slots:
    void save();
private:
    QLabel *dataRangeLabel;// = new QLabel(tr("数据范围:"));
    QLineEdit *dataRangeEdit;// = new QLineEdit;
    QLabel *compliantDateLabel;// = new QLabel(tr("合规性检查日期:"));
    QLineEdit *compliantDateEdit;// = new QLineEdit;
    QLabel *onecard2fiveDateLabel;// = new QLabel(tr("一证五号时间节点:"));
    QLineEdit *onecard2fiveDateEdit;// = new QLineEdit;
    QLabel *randomDateLabel;// = new QLabel(tr("随机日期:"));
    QLineEdit *randomDateEdit;// = new QLineEdit;
    QPushButton *saveButton;// = new QPushButton;
    XMLConfigReader *xmlConfig;
    void init();
};

class WorkPathPage : public QWidget
{
    Q_OBJECT
public:
    WorkPathPage(QWidget *parent = 0);
public slots:
    void save();
private:
    QLabel *workPathLabel;// = new QLabel(tr("工作路径:"));
    QLineEdit *workPathEdit;// = new QLineEdit;
    QPushButton *saveButton;// = new QPushButton;
    XMLConfigReader *xmlConfig;
    void init();
};

class DelimiterPage : public QWidget
{
    Q_OBJECT
public:
    DelimiterPage(QWidget *parent = 0);
public slots:
    void save();
private:
    QLabel *delimiterLabel;// = new QLabel(tr("字段间分隔符:"));
    QLineEdit *delimiterEdit;// = new QLineEdit;
    QPushButton *saveButton;// = new QPushButton;
    XMLConfigReader *xmlConfig;
    void init();
};

class ItemnumPage : public QWidget
{
    Q_OBJECT
public:
    ItemnumPage(QWidget *parent = 0);
public slots:
    void save();
private:
    QLabel *itemnumLabel;// = new QLabel(tr("字段个数:"));
    QLineEdit *itemnumEdit;// = new QLineEdit;
    QPushButton *saveButton;// = new QPushButton;
    XMLConfigReader *xmlConfig;
    void init();
};

class DateformatPage : public QWidget
{
    Q_OBJECT
public:
    DateformatPage(QWidget *parent = 0);
public slots:
    void save();
private:
    QLabel *dateformatLabel;// = new QLabel(tr("时间格式:"));
    QLineEdit *dateformatEdit;// = new QLineEdit;
    QPushButton *saveButton;// = new QPushButton;
    XMLConfigReader *xmlConfig;
    void init();
};

class CommonRulePage : public QWidget
{
    Q_OBJECT
public:
    CommonRulePage(QWidget *parent = 0);

public slots:
    void save();
private:
    QLabel *maxlimitLabel;// = new QLabel(tr("重号率阈值:"));
    QLineEdit *maxlimitEdit;// = new QLineEdit;
    QLabel *personNameLen_minLabel;
    QLineEdit *personNameLen_minEdit;
    QLabel *personNameLen_maxLabel;
    QLineEdit *personNameLen_maxEdit;
    QLabel *personNamePermit_charLabel;
    QLineEdit *personNamePermit_charEdit;
    QLabel *personCardtypeTime_intervalLabel;
    QLineEdit *personCardtypeTime_intervalEdit;
    QLabel *personCard_numLen_minLabel;
    QLineEdit *personCard_numLen_minEdit;
    QLabel *personCard_numLen_maxLabel;
    QLineEdit *personCard_numLen_maxEdit;
    QLabel *personCard_addLen_minLabel;
    QLineEdit *personCard_addLen_minEdit;
    QLabel *personCard_addLen_maxLabel;
    QLineEdit *personCard_addLen_maxEdit;

    QLabel *unitNameLen_minLabel;
    QLineEdit *unitNameLen_minEdit;
    QLabel *unitNameLen_maxLabel;
    QLineEdit *unitNameLen_maxEdit;
    QLabel *unitCardtypeTime_intervalLabel;
    QLineEdit *unitCardtypeTime_intervalEdit;
    QLabel *unitCard_numLen_minLabel;
    QLineEdit *unitCard_numLen_minEdit;
    QLabel *unitCard_numLen_maxLabel;
    QLineEdit *unitCard_numLen_maxEdit;
    QLabel *unitCard_addLen_minLabel;
    QLineEdit *unitCard_addLen_minEdit;
    QLabel *unitCard_addLen_maxLabel;
    QLineEdit *unitCard_addLen_maxEdit;


    QPushButton *saveButton;// = new QPushButton;
    XMLConfigReader *xmlConfig;
    void init();
};

class UserTypePage : public QWidget
{
    Q_OBJECT
public:
    UserTypePage(QWidget *parent = 0);
public slots:
    void add();
    void del();
    void valueSave();
private:
    QTableWidget *table;
    QList<QString> value;
    QString currnt_menu;
    XMLConfigReader *xmlConfig;
};

class BizTypePage : public QWidget
{
    Q_OBJECT
public:
    BizTypePage(QWidget *parent = 0);
    BizTypePage(QWidget *parent = 0,QString menu="");
    BizTypePage(QString menu="");
public slots:
    void add();
    void del();
    void valueSave();
private:
    QTableWidget *table;
    QList<QString> value;
    QString currnt_menu;
//    void autoidInit();
    XMLConfigReader *xmlConfig;
};


#endif // SETUPPAGES_H
