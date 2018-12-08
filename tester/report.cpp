#include "report.h"
#include "ui_report.h"
#include <QString>

Report::Report(QWidget *parent)
    :QDialog(parent),
    ui(new Ui::Report)
{

    ui->setupUi(this);
    init();
    QSqlQuery query;

        query.prepare("select * from report ");
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }
        else
        {
            while(query.next())
            {
//                int id = query.value(0).toInt();
                int j=0;//i行j列
                for(int i=0;i<100;i++){
                    ui->tableWidget->setItem(i, j,new QTableWidgetItem(query.value(i+1).toString()));
                }

            }
            qDebug()<<"get report data is finished.";
        }

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

    personFixedOwnerNameNotReg = 0;//个人固话用户-机主姓名未登记
    personFixedOwnerTypeNotReg = 0;//个人固话用户-机主证件类型未登记
    personFixedOwnerNumNotReg = 0;//个人固话用户-机主证件号码未登记
    personFixedOwnerAddNotReg = 0;//个人固话用户-机主证件地址未登记
    personFixedOwnerNameNumNotReg = 0;//个人固话用户-机主姓名证件号码未登记
    personFixedOwnerNameAddNotReg = 0;//个人固话用户-机主姓名证件地址未登记
    personFixedOwnerNumAddNotReg = 0;//个人固话用户-机主证件号码地址未登记
    personFixedOwnerNameNumAddNotReg = 0;//个人固话用户-机主姓名证件号码地址未登记

    unitMobileOwnerNotReg = 0;//单位移动用户-使用人信息未登记
    unitMobileAgentNotReg = 0;//单位移动用户-代办人信息未登记
    unitMobileUnitNotReg = 0;//单位移动用户-单位信息未登记
    unitMobileOwnerAgentNotReg = 0;//单位移动用户-使用人代办人信息未登记
    unitMobileOwnerUnitNotReg = 0;//单位移动用户-使用人单位信息未登记
    unitMobileAgentUnitNotReg = 0;//单位移动用户-代办人单位信息未登记
    unitMobileOwnerAgentUnitAddNotReg = 0;//单位移动用户-单位信息未登记

    unitFixedOwnerNotReg = 0;//单位固话用户-使用人信息未登记
    unitFixedAgentNotReg = 0;//单位固话用户-代办人信息未登记
    unitFixedUnitNotReg = 0;//单位固话用户-单位信息未登记
    unitFixedOwnerAgentNotReg = 0;//单位固话用户-使用人代办人信息未登记
    unitFixedOwnerUnitNotReg = 0;//单位固话用户-使用人单位信息未登记
    unitFixedAgentUnitNotReg = 0;//单位固话用户-代办人单位信息未登记
    unitFixedOwnerAgentUnitNotReg = 0;//单位固话用户-单位信息未登记

    tradeMobileAgentNotReg = 0;//行业移动用户-单位信息未登记
    tradeMobileUnitNotReg = 0;//行业移动用户-单位信息未登记
    tradeMobileLiableNotReg = 0;//行业移动用户-单位信息未登记
    tradeMobileAgentUnitNotReg = 0;//行业移动用户-单位信息未登记
    tradeMobileLiableAgentNotReg = 0;//行业移动用户-单位信息未登记
    tradeMobileLiableUnitNotReg = 0;//行业移动用户-单位信息未登记
    tradeMobileLiableAgentUnitAddNotReg = 0;//行业移动用户-单位信息未登记
    tradeFixedAgentNotReg = 0;//行业移动用户-单位信息未登记
    tradeFixedUnitNotReg = 0;//行业移动用户-单位信息未登记
    tradeFixedAgentUnitNotReg = 0;//行业移动用户-单位信息未登记

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
    personFixedOk = 0;
    personFixedOwnerTypeNok = 0;
    personFixedOwnerNameNok = 0;
    personFixedOwnerNumNok = 0;
    personFixedOwnerAddNok = 0;
    personFixedOwnerNameNumNok = 0;
    personFixedOwnerNameAddNok = 0;
    personFixedOwnerNumAddNok = 0;
    personFixedOwnerNameNumAddNok = 0;
    personMobileAgentNotReg = 0;
    personFixedAgentNotReg = 0;
    personMobileAgentNok = 0;
    personFixedAgentNok = 0;
    unitMobileOk = 0;
    unitMobileOwnerAgentUnitNotReg = 0;
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
    tradeMobileLiableAgentUnitNotReg = 0;
    tradeMobileAgentNok = 0;
    tradeMobileAgentUnitNok = 0;
    tradeMobileLiableAgentNok = 0;
    tradeMobileLiableAgentUnitNok = 0;
    tradeMobileUnitNok = 0;
    tradeMobileLiableNok = 0;
    tradeMobileLiableUnitNok = 0;
    tradeFixedOk = 0;
    tradeFixedAgentNok = 0;
    tradeFixedAgentUnitNok = 0;
    tradeFixedUnitNok = 0;
    personMobileOneCard= 0;
    leaveNet = 0;
    tradeFixedLiableNotReg =0;
    unitFixedUnitLiableNotReg = 0;
    unitFixedUnitLiableNok = 0;
    unitMobileUnitLiableNotReg = 0;
    unitMobileUnitLiableNok = 0;
}

Report::~Report()
{
    delete ui;
}
