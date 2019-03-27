#include "report.h"
#include <QString>
#include <QStandardItemModel>
#include <QStringList>

Report::Report(QWidget *parent)
    :QTableWidget (parent)
{
//    QTableWidget *tableWidget = new QTableWidget;
//    //ui->setupUi(this);
//    init();
    this->setWindowTitle("测试结果");
    this->resize(900, 750);
    this->setRowCount(120);
    this->setColumnCount(3);
    QStringList header;
    header.append("统计项");
    header.append("值");
    header.append("说明");
    this->setHorizontalHeaderLabels(header);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //this->resizeColumnsToContents();
    this->setColumnWidth(0,400);
    this->setColumnWidth(1,100);
    this->setColumnWidth(2,400);
}

void Report::init(){
    qDebug()<<"init Report vars";
    personMobileOwnerNameNotReg = 0;//个人移动用户-机主姓名未登记
    personMobileOwnerTypeNotReg = 0;//个人移动用户-机主证件类型未登记
    personMobileOwnerNumNotReg = 0;//个人移动用户机-主证件号码未登记
    personMobileOwnerAddNotReg = 0;//个人移动用户-机主证件地址未登记
    personMobileOwnerNameNumNotReg = 0;//个人移动用户-机主姓名证件号码未登记
    personMobileOwnerNameAddNotReg = 0;//个人移动用户-机主姓名证件地址未登记
    personMobileOwnerNumAddNotReg = 0;//个人移动用户-机主证件号码地址未登记
    personMobileOwnerNameNumAddNotReg = 0;//个人移动用户-机主姓名证件号码地址未登记
    personMobileAgentNotReg = 0;

    personFixedOwnerNameNotReg = 0;//个人固话用户-机主姓名未登记
    personFixedOwnerTypeNotReg = 0;//个人固话用户-机主证件类型未登记
    personFixedOwnerNumNotReg = 0;//个人固话用户-机主证件号码未登记
    personFixedOwnerAddNotReg = 0;//个人固话用户-机主证件地址未登记
    personFixedOwnerNameNumNotReg = 0;//个人固话用户-机主姓名证件号码未登记
    personFixedOwnerNameAddNotReg = 0;//个人固话用户-机主姓名证件地址未登记
    personFixedOwnerNumAddNotReg = 0;//个人固话用户-机主证件号码地址未登记
    personFixedOwnerNameNumAddNotReg = 0;//个人固话用户-机主姓名证件号码地址未登记
    personFixedAgentNotReg = 0;

    unitMobileOwnerNotReg = 0;//单位移动用户-使用人信息未登记
    unitMobileAgentNotReg = 0;//单位移动用户-经办人信息未登记
    unitMobileUnitNotReg = 0;//单位移动用户-单位信息未登记
    unitMobileOwnerAgentNotReg = 0;//单位移动用户-使用人经办人信息未登记
    unitMobileOwnerUnitNotReg = 0;//单位移动用户-使用人单位信息未登记
    unitMobileAgentUnitNotReg = 0;//单位移动用户-经办人单位信息未登记
    unitMobileOwnerAgentUnitNotReg = 0;

    unitFixedAgentNotReg = 0;//单位固话用户-经办人信息未登记
    unitFixedUnitNotReg = 0;//单位固话用户-单位信息未登记
    unitFixedAgentUnitNotReg = 0;//单位固话用户-经办人单位信息未登记

    tradeMobileAgentNotReg = 0;//行业移动应用-单位信息未登记
    tradeMobileUnitNotReg = 0;//行业移动应用-单位信息未登记
    tradeMobileLiableNotReg = 0;//行业移动应用-单位信息未登记
    tradeMobileAgentUnitNotReg = 0;//行业移动应用-单位信息未登记
    tradeMobileLiableAgentNotReg = 0;//行业移动应用-单位信息未登记
    tradeMobileLiableUnitNotReg = 0;//行业移动应用-单位信息未登记
    tradeMobileLiableAgentUnitNotReg = 0;

    tradeFixedAgentNotReg = 0;//行业移动应用-单位信息未登记
    tradeFixedUnitNotReg = 0;//行业移动应用-单位信息未登记
    tradeFixedAgentUnitNotReg = 0;//行业移动应用-单位信息未登记
    tradeFixedLiableNotReg = 0;
    tradeFixedAgentLiableNotReg = 0;
    tradeFixedLiableUnitNotReg = 0;
    tradeFixedAgentLiableUnitNotReg = 0;

    allData = 0;
    allNotReg = 0;
    allNok = 0;
    formatNok = 0;
    fieldNok = 0;
    allOk = 0;

    personMobileOk = 0;
    personMobileOwnerTypeNok = 0;
    personMobileOwnerNameNok = 0;
    personMobileOwnerNumNok = 0;
    personMobileOwnerAddNok = 0;
    personMobileOwnerNameNumNok = 0;
    personMobileOwnerNameAddNok = 0;
    personMobileOwnerNumAddNok = 0;
    personMobileOwnerNameNumAddNok = 0;
    personMobileAgentNok = 0;

    personFixedOk = 0;
    personFixedOwnerTypeNok = 0;
    personFixedOwnerNameNok = 0;
    personFixedOwnerNumNok = 0;
    personFixedOwnerAddNok = 0;
    personFixedOwnerNameNumNok = 0;
    personFixedOwnerNameAddNok = 0;
    personFixedOwnerNumAddNok = 0;
    personFixedOwnerNameNumAddNok = 0;
    personFixedAgentNok = 0;

    unitMobileOk = 0;
    unitMobileOwnerNok = 0;
    unitMobileOwnerUnitNok = 0;
    unitMobileAgentNok = 0;
    unitMobileUnitNok = 0;
    unitMobileOwnerAgentNok = 0;
    unitMobileAgentUnitNok = 0;
    unitMobileOwnerAgentUnitNok = 0;

    unitFixedOk = 0;
    unitFixedAgentNok = 0;
    unitFixedUnitNok = 0;
    unitFixedAgentUnitNok = 0;

    tradeMobileOk = 0;
    tradeMobileAgentNok = 0;
    tradeMobileAgentUnitNok = 0;
    tradeMobileLiableAgentNok = 0;
    tradeMobileLiableAgentUnitNok = 0;
    tradeMobileUnitNok = 0;
    tradeMobileLiableNok = 0;
    tradeMobileLiableUnitNok = 0;

    tradeFixedOk = 0;
    tradeFixedAgentNok = 0;
    tradeFixedUnitNok = 0;
    tradeFixedAgentUnitNok = 0;
    tradeFixedLiableNok = 0;
    tradeFixedAgentLiableNok = 0;
    tradeFixedLiableUnitNok = 0;
    tradeFixedAgentLiableUnitNok = 0;

    personMobileOneCard= 0;
    leaveNet = 0;
    nonRealName = 0;

    errMultiName = 0;
    errFiveNumber = 0;
    errCardCount = 0;
    onecardFiveNumber = 0;

    personMobileTotal = 0;
    personMobileNotReg = 0;
    personMobileNok = 0;
    personFixedTotal = 0;
    personFixedNotReg = 0;
    personFixedNok = 0;
    unitMobileTotal = 0;
    unitMobileNotReg = 0;
    unitMobileNok = 0;
    unitFixedTotal = 0;
    unitFixedNotReg = 0;
    unitFixedNok = 0;
    tradeMobileTotal = 0;
    tradeMobileNotReg = 0;
    tradeMobileNok = 0;
    tradeFixedTotal = 0;
    tradeFixedNotReg = 0;
    tradeFixedNok = 0;
}

void Report::setTableValue(QString path){
    //输出统计报表
    QFile report1(path+"report2.csv");
    report1.open(QFile::Append);
    QTextStream out1(&report1);
    out1.setCodec("GBK");
    //out1<<QStringLiteral("用户类型,用户总数,未登记数,不合规数,一证五卡违规证件数,一证五卡违规开卡数,异常记录,一证五号不合规")<<endl;
    //out1<<QStringLiteral("个人移动,")<<personMobileTotal<<","<<personMobileNotReg<<","<<personMobileNok+personMobileOneCard<<",-,-,-,-"<<endl;
    //out1<<QStringLiteral("个人固话,")<<personFixedTotal<<","<<personFixedNotReg<<","<<personFixedNok+personFixedOneCard<<",-,-,-,-"<<endl;
    //out1<<QStringLiteral("单位移动,")<<unitMobileTotal<<","<<unitMobileNotReg<<","<<unitMobileNok+unitMobileOneCard<<",-,-,-"<<endl;
    //out1<<QStringLiteral("单位固话,")<<unitFixedTotal<<","<<unitFixedNotReg<<","<<unitFixedNok+unitFixedOneCard<<",-,-,-,-"<<endl;
    //out1<<QStringLiteral("行业移动,")<<tradeMobileTotal<<","<<tradeMobileNotReg<<","<<tradeMobileNok+tradeMobileOneCard<<",-,-,-,-"<<endl;
    //out1<<QStringLiteral("行业固话,")<<tradeFixedTotal<<","<<tradeFixedNotReg<<","<<tradeFixedNok+tradeFixedOneCard<<",-,-,-,-"<<endl;
    //out1<<QStringLiteral("总计,")<<personMobileTotal+personFixedTotal+unitMobileTotal+unitFixedTotal+tradeMobileTotal+tradeFixedTotal<<",";
    //out1<<personMobileNotReg+personFixedNotReg+unitMobileNotReg+unitFixedNotReg+tradeMobileNotReg+tradeFixedNotReg<<",";
    //out1<<personMobileNok+personFixedNok+unitMobileNok+unitFixedNok+tradeMobileNok+tradeFixedNok+personMobileOneCard+personFixedOneCard+unitMobileOneCard+unitFixedOneCard+tradeMobileOneCard+tradeFixedOneCard<<","<<errFiveNumber<<","<<errCardCount<<",";
    //out1<<formatNok+fieldNok<<","<<this->onecardFiveNumber<<","<<endl;
    out1<<QStringLiteral("用户类型,用户总数,未登记数,不合规数,一证五卡违规证件数,一证五卡违规开卡数,异常记录")<<endl;
    out1<<QStringLiteral("个人移动,")<<personMobileTotal<<","<<personMobileNotReg<<","<<personMobileNok+personMobileOneCard<<",-,-,-"<<endl;
    out1<<QStringLiteral("个人固话,")<<personFixedTotal<<","<<personFixedNotReg<<","<<personFixedNok+personFixedOneCard<<",-,-,-"<<endl;
    out1<<QStringLiteral("单位移动,")<<unitMobileTotal<<","<<unitMobileNotReg<<","<<unitMobileNok+unitMobileOneCard<<",-,-"<<endl;
    out1<<QStringLiteral("单位固话,")<<unitFixedTotal<<","<<unitFixedNotReg<<","<<unitFixedNok+unitFixedOneCard<<",-,-,-"<<endl;
    out1<<QStringLiteral("行业移动,")<<tradeMobileTotal<<","<<tradeMobileNotReg<<","<<tradeMobileNok+tradeMobileOneCard<<",-,-,-"<<endl;
    out1<<QStringLiteral("行业固话,")<<tradeFixedTotal<<","<<tradeFixedNotReg<<","<<tradeFixedNok+tradeFixedOneCard<<",-,-,-"<<endl;
    out1<<QStringLiteral("总计,")<<personMobileTotal+personFixedTotal+unitMobileTotal+unitFixedTotal+tradeMobileTotal+tradeFixedTotal<<",";
    out1<<personMobileNotReg+personFixedNotReg+unitMobileNotReg+unitFixedNotReg+tradeMobileNotReg+tradeFixedNotReg<<",";
    out1<<personMobileNok+personFixedNok+unitMobileNok+unitFixedNok+tradeMobileNok+tradeFixedNok+personMobileOneCard+personFixedOneCard+unitMobileOneCard+unitFixedOneCard+tradeMobileOneCard+tradeFixedOneCard<<","<<errFiveNumber<<","<<errCardCount<<",";
    out1<<formatNok+fieldNok<<","<<endl;
    report1.close();

    QFile file(path+"report1.csv");
    file.open(QFile::Append);
    QTextStream out(&file);
    out.setCodec("GBK");
    out<<QStringLiteral("统计项,数字")<<endl;
    int i=0;
    this->setItem(i, 0, new QTableWidgetItem("总量"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->allData, 10)));
    this->setItem(i, 2, new QTableWidgetItem("全部数据行数"));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;

    this->setItem(i, 0, new QTableWidgetItem("全量未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->allNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;

    this->setItem(i, 0, new QTableWidgetItem("全量不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->allNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;

    this->setItem(i, 0, new QTableWidgetItem("格式异常数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->formatNok)));
    this->setItem(i, 2, new QTableWidgetItem("列数不符"));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;

    this->setItem(i, 0, new QTableWidgetItem("字段异常数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->fieldNok)));
    this->setItem(i, 2, new QTableWidgetItem("时间等格式异常"));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("离网"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->leaveNet,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("非实名停机"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->nonRealName,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("全量合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->allOk,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-形式合规数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOk,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件类型未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerTypeNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件号码未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNumNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名&证件号码未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameNumNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名&证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件号码&证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNumAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名&证件号码&证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameNumAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-经办人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileAgentNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件类型校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerTypeNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件号码校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNumNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名&证件号码校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameNumNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名&证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件号码&证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNumAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名&证件号码&证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameNumAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-经办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;

    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-形式合规数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOk,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件类型未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerTypeNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件号码未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNumNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名&证件号码未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameNumNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名&证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件号码&证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNumAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名&证件号码&证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameNumAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-经办人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedAgentNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件类型校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerTypeNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件号码校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNumNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名&证件号码校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameNumNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名&证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件号码&证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNumAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名&证件号码&证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameNumAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-经办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-形式合规数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOk,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-经办人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileAgentNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人&经办人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerAgentNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-经办人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileAgentUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人&经办人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerAgentUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-经办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人&经办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-经办人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileAgentUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人&经办人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerAgentUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话用户-形式合规数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedOk,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话用户-经办人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedAgentNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话用户-单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话用户-经办人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedAgentUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话用户-经办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话用户-单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话用户-经办人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedAgentUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-形式合规数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileOk,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-经办人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileAgentNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-经办人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileAgentUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人&经办人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableAgentNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人&经办人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableAgentUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-经办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-经办人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileAgentUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人&经办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人&经办人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableAgentUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-形式合规数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedOk,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-责任人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedLiableNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人&责任人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentLiableNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-责任人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedLiableUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人&责任人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentLiableUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-责任人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedLiableNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人&责任人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentLiableNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-责任人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedLiableUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人&责任人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentLiableUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动一证多名不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOneCard,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话一证多名不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOneCard,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动一证多名不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOneCard,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话一证多名不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedOneCard,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动一证多名不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileOneCard,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话一证多名不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedOneCard,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("一证多名证件数"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->errMultiName,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("一证五号不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->onecardFiveNumber,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("一证五卡证件数"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->errFiveNumber,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("违规卡数"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->errCardCount,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;

    file.close();
}
Report::~Report()
{
   // delete ui;
}
