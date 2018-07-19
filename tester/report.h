#ifndef REPORT_H
#define REPORT_H

#include <QDialog>

namespace Ui {
class Report;
}

class Report : public QDialog
{
    Q_OBJECT

public:
    explicit Report(QWidget *parent = 0);
    ~Report();
    int personMobileOwnerNameNotReg = 0;//个人移动用户-机主姓名未登记
    int personMobileOwnerTypeNotReg = 0;//个人移动用户-机主证件类型未登记
    int personMobileOwnerNumNotReg = 0;//个人移动用户机-主证件号码未登记
    int personMobileOwnerAddNotReg = 0;//个人移动用户-机主证件地址未登记
    int personMobileOwnerNameNumNotReg = 0;//个人移动用户-机主姓名证件号码未登记
    int personMobileOwnerNameAddNotReg = 0;//个人移动用户-机主姓名证件地址未登记
    int personMobileOwnerNumAddNotReg = 0;//个人移动用户-机主证件号码地址未登记
    int personMobileOwnerNameNumAddNotReg = 0;//个人移动用户-机主姓名证件号码地址未登记

    int personFixedOwnerNameNotReg = 0;//个人固话用户-机主姓名未登记
    int personFixedOwnerTypeNotReg = 0;//个人固话用户-机主证件类型未登记
    int personFixedOwnerNumNotReg = 0;//个人固话用户-机主证件号码未登记
    int personFixedOwnerAddNotReg = 0;//个人固话用户-机主证件地址未登记
    int personFixedOwnerNameNumNotReg = 0;//个人固话用户-机主姓名证件号码未登记
    int personFixedOwnerNameAddNotReg = 0;//个人固话用户-机主姓名证件地址未登记
    int personFixedOwnerNumAddNotReg = 0;//个人固话用户-机主证件号码地址未登记
    int personFixedOwnerNameNumAddNotReg = 0;//个人固话用户-机主姓名证件号码地址未登记

    int unitMobileOwnerNotReg = 0;//单位移动用户-使用人信息未登记
    int unitMobileAgentNotReg = 0;//单位移动用户-代办人信息未登记
    int unitMobileUnitNotReg = 0;//单位移动用户-单位信息未登记
    int unitMobileOwnerAgentNotReg = 0;//单位移动用户-使用人代办人信息未登记
    int unitMobileOwnerUnitNotReg = 0;//单位移动用户-使用人单位信息未登记
    int unitMobileAgentUnitNotReg = 0;//单位移动用户-代办人单位信息未登记
    int unitMobileOwnerAgentUnitAddNotReg = 0;//单位移动用户-单位信息未登记

    int unitFixedOwnerNotReg = 0;//单位固话用户-使用人信息未登记
    int unitFixedAgentNotReg = 0;//单位固话用户-代办人信息未登记
    int unitFixedUnitNotReg = 0;//单位固话用户-单位信息未登记
    int unitFixedOwnerAgentNotReg = 0;//单位固话用户-使用人代办人信息未登记
    int unitFixedOwnerUnitNotReg = 0;//单位固话用户-使用人单位信息未登记
    int unitFixedAgentUnitNotReg = 0;//单位固话用户-代办人单位信息未登记
    int unitFixedOwnerAgentUnitAddNotReg = 0;//单位固话用户-单位信息未登记

    int tradeMobileAgentNotReg = 0;//行业移动用户-单位信息未登记
    int tradeMobileUnitNotReg = 0;//行业移动用户-单位信息未登记
    int tradeMobileLiableNotReg = 0;//行业移动用户-单位信息未登记
    int tradeMobileAgentUnitNotReg = 0;//行业移动用户-单位信息未登记
    int tradeMobileLiableAgentNotReg = 0;//行业移动用户-单位信息未登记
    int tradeMobileLiableUnitNotReg = 0;//行业移动用户-单位信息未登记
    int tradeMobileLiableAgentUnitAddNotReg = 0;//行业移动用户-单位信息未登记
    int tradeFixedAgentNotReg = 0;//行业移动用户-单位信息未登记
    int tradeFixedUnitNotReg = 0;//行业移动用户-单位信息未登记
    int tradeFixedAgentUnitNotReg = 0;//行业移动用户-单位信息未登记


private:
    Ui::Report *ui;
};

#endif // REPORT_H
