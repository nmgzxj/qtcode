﻿#ifndef REPORT_H
#define REPORT_H

#include <QDebug>
#include <QFile>
#include <QTableWidget>

namespace Ui {
class Report;
}

class Report : public QTableWidget
{
    Q_OBJECT

public:
    explicit Report(QWidget *parent = nullptr);
    ~Report();
    void init();
    void setTableValue(QString reportFileName);

    int personMobileOwnerNameNotReg;//个人移动用户-机主姓名未登记
    int personMobileOwnerTypeNotReg;//个人移动用户-机主证件类型未登记
    int personMobileOwnerNumNotReg;//个人移动用户机-主证件号码未登记
    int personMobileOwnerAddNotReg;//个人移动用户-机主证件地址未登记
    int personMobileAgentNotReg;
    int personMobileOwnerNameNumNotReg;//个人移动用户-机主姓名证件号码未登记
    int personMobileOwnerNameAddNotReg;//个人移动用户-机主姓名证件地址未登记
    int personMobileOwnerNumAddNotReg;//个人移动用户-机主证件号码地址未登记
    int personMobileOwnerNameNumAddNotReg;//个人移动用户-机主姓名证件号码地址未登记

    int personFixedOwnerNameNotReg;//个人固话用户-机主姓名未登记
    int personFixedOwnerTypeNotReg;//个人固话用户-机主证件类型未登记
    int personFixedOwnerNumNotReg;//个人固话用户-机主证件号码未登记
    int personFixedOwnerAddNotReg;//个人固话用户-机主证件地址未登记
    int personFixedAgentNotReg;
    int personFixedOwnerNameNumNotReg;//个人固话用户-机主姓名证件号码未登记
    int personFixedOwnerNameAddNotReg;//个人固话用户-机主姓名证件地址未登记
    int personFixedOwnerNumAddNotReg;//个人固话用户-机主证件号码地址未登记
    int personFixedOwnerNameNumAddNotReg;//个人固话用户-机主姓名证件号码地址未登记

    int unitMobileOwnerNotReg;//单位移动用户-使用人信息未登记
    int unitMobileAgentNotReg;//单位移动用户-代办人信息未登记
    int unitMobileUnitNotReg;//单位移动用户-单位信息未登记
    int unitMobileOwnerAgentNotReg;//单位移动用户-使用人代办人信息未登记
    int unitMobileOwnerUnitNotReg;//单位移动用户-使用人单位信息未登记
    int unitMobileAgentUnitNotReg;//单位移动用户-代办人单位信息未登记
    int unitMobileOwnerAgentUnitNotReg;

    int unitFixedAgentNotReg;//单位固话用户-代办人信息未登记
    int unitFixedUnitNotReg;//单位固话用户-单位信息未登记
    int unitFixedAgentUnitNotReg;//单位固话用户-代办人单位信息未登记

    int tradeMobileAgentNotReg;//行业移动用户-单位信息未登记
    int tradeMobileUnitNotReg;//行业移动用户-单位信息不合规
    int tradeMobileLiableNotReg;//行业移动用户-责任人信息未登记
    int tradeMobileAgentUnitNotReg;//行业移动用户-责任人信息未登记
    int tradeMobileLiableAgentNotReg;//
    int tradeMobileLiableUnitNotReg;//
    int tradeMobileLiableAgentUnitNotReg;

    int tradeFixedAgentNotReg;//
    int tradeFixedUnitNotReg;//
    int tradeFixedAgentUnitNotReg;//
    int tradeFixedLiableNotReg;
    int tradeFixedAgentLiableNotReg;
    int tradeFixedLiableUnitNotReg;
    int tradeFixedAgentLiableUnitNotReg;

    int allData;
    int allNotReg;
    int allNok;
    int formatNok;
    int fieldNok;
    int allOk;

    int personMobileOk;
    int personMobileOwnerTypeNok;
    int personMobileOwnerNameNok;
    int personMobileOwnerNumNok;
    int personMobileOwnerAddNok;
    int personMobileAgentNok;
    int personMobileOwnerNameNumNok;
    int personMobileOwnerNameAddNok;
    int personMobileOwnerNumAddNok;
    int personMobileOwnerNameNumAddNok;

    int personFixedOk;
    int personFixedOwnerTypeNok;
    int personFixedOwnerNameNok;
    int personFixedOwnerNumNok;
    int personFixedOwnerAddNok;
    int personFixedAgentNok;
    int personFixedOwnerNameNumNok;
    int personFixedOwnerNameAddNok;
    int personFixedOwnerNumAddNok;
    int personFixedOwnerNameNumAddNok;

    int unitMobileOk;
    int unitMobileOwnerNok;
    int unitMobileOwnerUnitNok;
    int unitMobileAgentNok;
    int unitMobileUnitNok;
    int unitMobileOwnerAgentNok;
    int unitMobileAgentUnitNok;
    int unitMobileOwnerAgentUnitNok;

    int unitFixedOk;
    int unitFixedAgentNok;
    int unitFixedUnitNok;
    int unitFixedAgentUnitNok;

    int tradeMobileOk;
    int tradeMobileAgentNok;
    int tradeMobileAgentUnitNok;
    int tradeMobileLiableAgentNok;
    int tradeMobileLiableAgentUnitNok;
    int tradeMobileUnitNok;
    int tradeMobileLiableNok;
    int tradeMobileLiableUnitNok;

    int tradeFixedOk;
    int tradeFixedAgentNok;
    int tradeFixedUnitNok;
    int tradeFixedLiableNok;
    int tradeFixedAgentUnitNok;
    int tradeFixedAgentLiableNok;
    int tradeFixedLiableUnitNok;
    int tradeFixedAgentLiableUnitNok;

    int personMobileOneCard = 0;
    int leaveNet = 0;
    int personFixedOneCard = 0;
    int unitMobileOneCard = 0;
    int unitFixedOneCard = 0;
    int tradeMobileOneCard = 0;
    int tradeFixedOneCard = 0;
    int nonRealName = 0;

    int errMultiName = 0;
    int errFiveNumber = 0;
    int errCardCount = 0;
    int onecardFiveNumber = 0;

    int personMobileTotal = 0;
    int personMobileNotReg = 0;
    int personMobileNok = 0;
    int personFixedTotal = 0;
    int personFixedNotReg = 0;
    int personFixedNok = 0;
    int unitMobileTotal = 0;
    int unitMobileNotReg = 0;
    int unitMobileNok = 0;
    int unitFixedTotal = 0;
    int unitFixedNotReg = 0;
    int unitFixedNok = 0;
    int tradeMobileTotal = 0;
    int tradeMobileNotReg = 0;
    int tradeMobileNok = 0;
    int tradeFixedTotal = 0;
    int tradeFixedNotReg = 0;
    int tradeFixedNok = 0;

private:
    Ui::Report *ui;
signals:
    void message(const QString& info);
    void messageWarning(const QString& str);
};

#endif // REPORT_H
