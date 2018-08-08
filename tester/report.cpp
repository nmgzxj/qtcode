#include "report.h"
#include "ui_report.h"

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
                int id = query.value(0).toInt();
                int j=0;//i行j列
                for(int i=1;i<100;i++){
                    ui->tableWidget->setItem(i-1, j, new QTableWidgetItem(query.value(i).toString()));
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
    unitFixedOwnerAgentUnitAddNotReg = 0;//单位固话用户-单位信息未登记

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
    formatNotRight = 0;
    fieldNotRight = 0;
    allOk = 0;
    personMobileFormatRight = 0;
    personMobileOwnerTypeIllegal = 0;
    personMobileOwnerNameIllegal = 0;
    personMobileOwnerNumIllegal = 0;
    personMobileOwnerAddIllegal = 0;
    personMobileOwnerNameNumIllegal = 0;
    personMobileOwnerNameAddIllegal = 0;
    personMobileOwnerNumAddIllegal = 0;
    personMobileOwnerNameNumAddIllegal = 0;
    personFixedLegal = 0;
    personFixedOwnerTypeIllegal = 0;
    personFixedOwnerNameIllegal = 0;
    personFixedOwnerNumIllegal = 0;
    personFixedOwnerAddIllegal = 0;
    personFixedOwnerNameNumIllegal = 0;
    personFixedOwnerNameAddIllegal = 0;
    personFixedOwnerNumAddIllegal = 0;
    personFixedOwnerNameNumAddIllegal = 0;
    personMobileAgentNotReg = 0;
    personFixedAgentNotReg = 0;
    personMobileAgentIllegal = 0;
    personFixedAgentIllegal = 0;
    unitMobileLegal = 0;
    unitMobileOwnerAgentUnitNotReg = 0;
    unitMobileOwnerIllegal = 0;
    unitMobileAgentIllegal = 0;
    unitMobileUnitIllegal = 0;
    unitMobileOwnerAgentIllegal = 0;
    unitMobileAgentUnitIllegal = 0;
    unitMobileOwnerAgentUnitIllegal = 0;
    unitFixedLegal = 0;
    unitFixedAgentIllegal = 0;
    unitFixedUnitIllegal = 0;
    unitFixedAgentUnitIllegal = 0;
    tradeMobileLegal = 0;
    tradeMobileLiableAgentUnitNotReg = 0;
    tradeMobileAgentIllegal = 0;
    tradeMobileAgentUnitIllegal = 0;
    tradeMobileLiableAgentIllegal = 0;
    tradeMobileLiableAgentUnitIllegal = 0;
    tradeMobileUnitIllegal = 0;
    tradeMobileLiableIllegal = 0;
    tradeMobileLiableUnitIllegal = 0;
    tradeFixedLegal = 0;
    tradeFixedAgentIllegal = 0;
    tradeFixedAgentUnitIllegal = 0;
    tradeFixedUnitIllegal = 0;
    personMobileOneCard= 0;
}

Report::~Report()
{
    delete ui;
}
