#ifndef REPORT_H
#define REPORT_H

#include <QDialog>
#include <QSqlQuery>
#include<QDebug>
#include<QSqlError>

namespace Ui {
class Report;
}

class Report : public QDialog
{
    Q_OBJECT

public:
    explicit Report(QWidget *parent = 0);
    ~Report();
    void init();

    int personMobileOwnerNameNotReg;//个人移动用户-机主姓名未登记
    int personMobileOwnerTypeNotReg;//个人移动用户-机主证件类型未登记
    int personMobileOwnerNumNotReg;//个人移动用户机-主证件号码未登记
    int personMobileOwnerAddNotReg;//个人移动用户-机主证件地址未登记
    int personMobileOwnerNameNumNotReg;//个人移动用户-机主姓名证件号码未登记
    int personMobileOwnerNameAddNotReg;//个人移动用户-机主姓名证件地址未登记
    int personMobileOwnerNumAddNotReg;//个人移动用户-机主证件号码地址未登记
    int personMobileOwnerNameNumAddNotReg;//个人移动用户-机主姓名证件号码地址未登记

    int personFixedOwnerNameNotReg;//个人固话用户-机主姓名未登记
    int personFixedOwnerTypeNotReg;//个人固话用户-机主证件类型未登记
    int personFixedOwnerNumNotReg;//个人固话用户-机主证件号码未登记
    int personFixedOwnerAddNotReg;//个人固话用户-机主证件地址未登记
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
    int unitMobileOwnerAgentUnitAddNotReg;//单位移动用户-单位信息未登记

    int unitFixedOwnerNotReg;//单位固话用户-使用人信息未登记
    int unitFixedAgentNotReg;//单位固话用户-代办人信息未登记
    int unitFixedUnitNotReg;//单位固话用户-单位信息未登记
    int unitFixedOwnerAgentNotReg;//单位固话用户-使用人代办人信息未登记
    int unitFixedOwnerUnitNotReg;//单位固话用户-使用人单位信息未登记
    int unitFixedAgentUnitNotReg;//单位固话用户-代办人单位信息未登记
    int unitFixedOwnerAgentUnitNotReg;//单位固话用户-单位信息未登记

    int tradeMobileAgentNotReg;//行业移动用户-单位信息未登记
    int tradeMobileUnitNotReg;//行业移动用户-单位信息未登记
    int tradeMobileLiableNotReg;//行业移动用户-单位信息未登记
    int tradeMobileAgentUnitNotReg;//行业移动用户-单位信息未登记
    int tradeMobileLiableAgentNotReg;//行业移动用户-单位信息未登记
    int tradeMobileLiableUnitNotReg;//行业移动用户-单位信息未登记
    int tradeMobileLiableAgentUnitAddNotReg;//行业移动用户-单位信息未登记
    int tradeFixedAgentNotReg;//行业移动用户-单位信息未登记
    int tradeFixedUnitNotReg;//行业移动用户-单位信息未登记
    int tradeFixedAgentUnitNotReg;//行业移动用户-单位信息未登记

    int allData;
    int allNotReg;
    int formatNok;
    int fieldNok;
    int allOk;
    int personMobileFormatRight;
    int personMobileOwnerTypeNok;
    int personMobileOwnerNameNok;
    int personMobileOwnerNumNok;
    int personMobileOwnerAddNok;
    int personMobileOwnerNameNumNok;
    int personMobileOwnerNameAddNok;
    int personMobileOwnerNumAddNok;
    int personMobileOwnerNameNumAddNok;
    int personFixedOk;
    int personFixedOwnerTypeNok;
    int personFixedOwnerNameNok;
    int personFixedOwnerNumNok;
    int personFixedOwnerAddNok;
    int personFixedOwnerNameNumNok;
    int personFixedOwnerNameAddNok;
    int personFixedOwnerNumAddNok;
    int personFixedOwnerNameNumAddNok;
    int personMobileAgentNotReg;
    int personFixedAgentNotReg;
    int personMobileAgentNok;
    int personFixedAgentNok;
    int unitMobileOk;
    int unitMobileOwnerAgentUnitNotReg;
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
    int tradeMobileLiableAgentUnitNotReg;
    int tradeMobileAgentNok;
    int tradeMobileAgentUnitNok;
    int tradeMobileLiableAgentNok;
    int tradeMobileLiableAgentUnitNok;
    int tradeMobileUnitNok;
    int tradeMobileLiableNok;
    int tradeMobileLiableUnitNok;
    int tradeFixedOk;
    int tradeFixedAgentNok;
    int tradeFixedAgentUnitNok;
    int tradeFixedUnitNok;
    int personMobileOneCard= 0;


private:
    Ui::Report *ui;
};

#endif // REPORT_H
