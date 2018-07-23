#include "report.h"
#include "ui_report.h"
#include "connection.h"
#include "userfile.h"

Report::Report(QWidget *parent)
    :QDialog(parent),
    ui(new Ui::Report)
{
    ui->setupUi(this);
    QSqlQuery query;

    //创建报表
    qDebug()<<"drop report:"<<query.exec("drop table report");
    qDebug()<<"create report:"<<query.exec("create table report(id int primary key,allData int,allNotReg int,formatNotRight int,fieldNotRight int,allOk int,personMobileFormatRight int,"
                                           "personMobileOwnerTypeNotReg int,personMobileOwnerNameNotReg int,personMobileOwnerNumNotReg int,personMobileOwnerAddNotReg int,personMobileOwnerNameNumNotReg int,"
                                           "personMobileOwnerNameAddNotReg int,personMobileOwnerNumAddNotReg int,personMobileOwnerNameNumAddNotReg int,personMobileOwnerTypeIllegal int,personMobileOwnerNameIllegal int,"
                                           "personMobileOwnerNumIllegal int,personMobileOwnerAddIllegal int,personMobileOwnerNameNumIllegal int,personMobileOwnerNameAddIllegal int,personMobileOwnerNumAddIllegal int,"
                                           "personMobileOwnerNameNumAddIllegal int,personFixedLegal int,personFixedOwnerTypeNotReg int,personFixedOwnerNameNotReg int,personFixedOwnerNumNotReg int,"
                                           "personFixedOwnerAddNotReg int,personFixedOwnerNameNumNotReg int,personFixedOwnerNameAddNotReg int,personFixedOwnerNumAddNotReg int,personFixedOwnerNameNumAddNotReg int,"
                                           "personFixedOwnerTypeIllegal int,personFixedOwnerNameIllegal int,personFixedOwnerNumIllegal int,personFixedOwnerAddIllegal int,personFixedOwnerNameNumIllegal int,"
                                           "personFixedOwnerNameAddIllegal int,personFixedOwnerNumAddIllegal int,personFixedOwnerNameNumAddIllegal int,personMobileAgentNotReg int,personFixedAgentNotReg int,"
                                           "personMobileAgentIllegal int,personFixedAgentIllegal int,unitMobileLegal int,unitMobileOwnerNotReg int,unitMobileAgentNotReg int,unitMobileUnitNotReg int,"
                                           "unitMobileOwnerAgentNotReg int,unitMobileOwnerUnitNotReg int,unitMobileAgentUnitNotReg int,unitMobileOwnerAgentUnitNotReg int,unitMobileOwnerIllegal int,"
                                           "unitMobileAgentIllegal int,unitMobileUnitIllegal int,unitMobileOwnerAgentIllegal int,unitMobileAgentUnitIllegal int,unitMobileOwnerAgentUnitIllegal int,"
                                           "unitFixedLegal int,unitFixedAgentNotReg int,unitFixedUnitNotReg int,unitFixedAgentUnitNotReg int,unitFixedAgentIllegal int,unitFixedUnitIllegal int,"
                                           "unitFixedAgentUnitIllegal int,tradeMobileLegal int,tradeMobileAgentNotReg int,tradeMobileAgentUnitNotReg int,tradeMobileLiableAgentNotReg int,"
                                           "tradeMobileLiableAgentUnitNotReg int,tradeMobileUnitNotReg int,tradeMobileLiableNotReg int,tradeMobileLiableUnitNotReg int,tradeMobileAgentIllegal int,"
                                           "tradeMobileAgentUnitIllegal int,tradeMobileLiableAgentIllegal int,tradeMobileLiableAgentUnitIllegal int,tradeMobileUnitIllegal int,tradeMobileLiableIllegal int,"
                                           "tradeMobileLiableUnitIllegal int,tradeFixedLegal int, tradeFixedAgentNotReg int,tradeFixedAgentUnitNotReg int,tradeFixedUnitNotReg int,tradeFixedAgentIllegal int,"
                                           "tradeFixedAgentUnitIllegal int,tradeFixedUnitIllegal int,personMobileOneCard int)");



    qDebug()<<"delete report is:"<<query.exec("delete report");
    qDebug()<<"insert report data is:"<<query.exec("insert into report(id,allData,allNotReg,formatNotRight) values (1,2,3,4)");
    UserFile* uf;
    uf = new UserFile;
//  todo  uf->insertDb("/Users/zhangxianjin/qtcode/test_data.txt");

    //总量
        qDebug()<<"update allData is:"<<query.exec("update report set allData=(select count(*) from file)");
    //全量未登记
        qDebug()<<"update allNotReg is:"<<query.exec("update report set allNotReg=(select count(*) from file)");
    //格式异常数据
         qDebug()<<"update formatNotRight is:"<<query.exec("update report set formatNotRight=(select count(*) from file)");
    //字段异常数据
         qDebug()<<"update fieldNotRight is:"<<query.exec("update report set fieldNotRight=(select count(*) from file)");
    //all.ok
         qDebug()<<"update allOk is:"<<query.exec("update report set allOk=(select count(*) from file)");

    //待挖掘记录
//         qDebug()<<"update allData is:"<<query.exec("update report set allData=(select count(*) from file)");

    //个人移动用户-形式合规数据
         //qDebug()<<"update personMobileFormatRight is:"<<query.exec("update report set personMobileFormatRight=(select count(*) from file where col"+UserFile::getCol_num("用户类型")+"='')");

    //个人移动用户-证件类型未登记
         qDebug()<<"update personMobileOwnerTypeNotReg is:"<<query.exec("update report set personMobileOwnerTypeNotReg=(select count(*) from file)");

    //个人移动用户-用户姓名未登记
         qDebug()<<"update personMobileOwnerNameNotReg is:"<<query.exec("update report set personMobileOwnerNameNotReg=(select count(*) from file)");

    //个人移动用户-证件号码未登记
         qDebug()<<"update personMobileOwnerNumNotReg is:"<<query.exec("update report set personMobileOwnerNumNotReg=(select count(*) from file)");

    //个人移动用户-证件地址未登记
         qDebug()<<"update personMobileOwnerAddNotReg is:"<<query.exec("update report set personMobileOwnerAddNotReg=(select count(*) from file)");

    //个人移动用户-用户姓名&amp;证件号码未登记
         qDebug()<<"update personMobileOwnerNameNumNotReg is:"<<query.exec("update report set personMobileOwnerNameNumNotReg=(select count(*) from file)");

    //个人移动用户-用户姓名&amp;证件地址未登记
         qDebug()<<"update personMobileOwnerNameAddNotReg is:"<<query.exec("update report set personMobileOwnerNameAddNotReg=(select count(*) from file)");

    //个人移动用户-证件号码&amp;证件地址未登记
         qDebug()<<"update personMobileOwnerNumAddNotReg is:"<<query.exec("update report set personMobileOwnerNumAddNotReg=(select count(*) from file)");

    //个人移动用户-用户姓名&amp;证件号码&amp;证件地址未登记
         qDebug()<<"update personMobileOwnerNameNumAddNotReg is:"<<query.exec("update report set personMobileOwnerNameNumAddNotReg=(select count(*) from file)");

    //个人移动用户-证件类型校验不合规
         qDebug()<<"update personMobileOwnerTypeIllegal is:"<<query.exec("update report set personMobileOwnerTypeIllegal=(select count(*) from file)");

    //个人移动用户-用户姓名校验不合规
         qDebug()<<"update personMobileOwnerNameIllegal is:"<<query.exec("update report set personMobileOwnerNameIllegal=(select count(*) from file)");

    //个人移动用户-证件号码校验不合规
         qDebug()<<"update personMobileOwnerNumIllegal is:"<<query.exec("update report set personMobileOwnerNumIllegal=(select count(*) from file)");

    //个人移动用户-证件地址校验不合规
         qDebug()<<"update personMobileOwnerAddIllegal is:"<<query.exec("update report set personMobileOwnerAddIllegal=(select count(*) from file)");

    //个人移动用户-用户姓名&amp;证件号码校验不合规
         qDebug()<<"update personMobileOwnerNameNumIllegal is:"<<query.exec("update report set personMobileOwnerNameNumIllegal=(select count(*) from file)");

    //个人移动用户-用户姓名&amp;证件地址校验不合规
         qDebug()<<"update personMobileOwnerNameAddIllegal is:"<<query.exec("update report set personMobileOwnerNameAddIllegal=(select count(*) from file)");

    //个人移动用户-证件号码&amp;证件地址校验不合规
         qDebug()<<"update personMobileOwnerNumAddIllegal is:"<<query.exec("update report set personMobileOwnerNumAddIllegal=(select count(*) from file)");

    //个人移动用户-用户姓名&amp;证件号码&amp;证件地址校验不合规
         qDebug()<<"update personMobileOwnerNameNumAddIllegal is:"<<query.exec("update report set personMobileOwnerNameNumAddIllegal=(select count(*) from file)");

    //个人固话用户-形式合规数据
         qDebug()<<"update personFixedLegal is:"<<query.exec("update report set personFixedLegal=(select count(*) from file)");

    //个人固话用户-证件类型未登记
         qDebug()<<"update personFixedOwnerTypeNotReg is:"<<query.exec("update report set personFixedOwnerTypeNotReg=(select count(*) from file)");

    //个人固话用户-用户姓名未登记
         qDebug()<<"update personFixedOwnerNameNotReg is:"<<query.exec("update report set personFixedOwnerNameNotReg=(select count(*) from file)");

    //个人固话用户-证件号码未登记
         qDebug()<<"update personFixedOwnerNumNotReg is:"<<query.exec("update report set personFixedOwnerNumNotReg=(select count(*) from file)");

    //个人固话用户-证件地址未登记
         qDebug()<<"update personFixedOwnerAddNotReg is:"<<query.exec("update report set personFixedOwnerAddNotReg=(select count(*) from file)");

    //个人固话用户-用户姓名&amp;证件号码未登记
         qDebug()<<"update personFixedOwnerNameNumNotReg is:"<<query.exec("update report set personFixedOwnerNameNumNotReg=(select count(*) from file)");

    //个人固话用户-用户姓名&amp;证件地址未登记
         qDebug()<<"update personFixedOwnerNameAddNotReg is:"<<query.exec("update report set personFixedOwnerNameAddNotReg=(select count(*) from file)");

    //个人固话用户-证件号码&amp;证件地址未登记
         qDebug()<<"update personFixedOwnerNumAddNotReg is:"<<query.exec("update report set personFixedOwnerNumAddNotReg=(select count(*) from file)");

    //个人固话用户-用户姓名&amp;证件号码&amp;证件地址未登记
         qDebug()<<"update personFixedOwnerNameNumAddNotReg is:"<<query.exec("update report set personFixedOwnerNameNumAddNotReg=(select count(*) from file)");

    //个人固话用户-证件类型校验不合规
         qDebug()<<"update personFixedOwnerTypeIllegal is:"<<query.exec("update report set personFixedOwnerTypeIllegal=(select count(*) from file)");

    //个人固话用户-用户姓名校验不合规
         qDebug()<<"update personFixedOwnerNameIllegal is:"<<query.exec("update report set personFixedOwnerNameIllegal=(select count(*) from file)");

    //个人固话用户-证件号码校验不合规
         qDebug()<<"update personFixedOwnerNumIllegal is:"<<query.exec("update report set personFixedOwnerNumIllegal=(select count(*) from file)");

    //个人固话用户-证件地址校验不合规
         qDebug()<<"update personFixedOwnerAddIllegal is:"<<query.exec("update report set personFixedOwnerAddIllegal=(select count(*) from file)");

    //个人固话用户-用户姓名&amp;证件号码校验不合规
         qDebug()<<"update personFixedOwnerNameNumIllegal is:"<<query.exec("update report set personFixedOwnerNameNumIllegal=(select count(*) from file)");

    //个人固话用户-用户姓名&amp;证件地址校验不合规
         qDebug()<<"update personFixedOwnerNameAddIllegal is:"<<query.exec("update report set personFixedOwnerNameAddIllegal=(select count(*) from file)");

    //个人固话用户-证件号码&amp;证件地址校验不合规
         qDebug()<<"update personFixedOwnerNumAddIllegal is:"<<query.exec("update report set personFixedOwnerNumAddIllegal=(select count(*) from file)");

    //个人固话用户-用户姓名&amp;证件号码&amp;证件地址校验不合规
         qDebug()<<"update personFixedOwnerNameNumAddIllegal is:"<<query.exec("update report set personFixedOwnerNameNumAddIllegal=(select count(*) from file)");

    //个人移动用户-代办人信息未登记
         qDebug()<<"update personMobileAgentNotReg is:"<<query.exec("update report set personMobileAgentNotReg=(select count(*) from file)");

    //个人固话用户-代办人信息未登记
         qDebug()<<"update personFixedAgentNotReg is:"<<query.exec("update report set personFixedAgentNotReg=(select count(*) from file)");

    //个人移动用户-代办人信息校验不合规
         qDebug()<<"update personMobileAgentIllegal is:"<<query.exec("update report set personMobileAgentIllegal=(select count(*) from file)");

    //个人固话用户-代办人信息校验不合规
         qDebug()<<"update personFixedAgentIllegal is:"<<query.exec("update report set personFixedAgentIllegal=(select count(*) from file)");

    //单位移动用户-形式合规数据
         qDebug()<<"update unitMobileLegal is:"<<query.exec("update report set unitMobileLegal=(select count(*) from file)");

    //单位移动用户-使用人信息未登记
         qDebug()<<"update unitMobileOwnerNotReg is:"<<query.exec("update report set unitMobileOwnerNotReg=(select count(*) from file)");

    //单位移动用户-经办人信息未登记
         qDebug()<<"update unitMobileAgentNotReg is:"<<query.exec("update report set unitMobileAgentNotReg=(select count(*) from file)");

    //单位移动用户-单位信息未登记
         qDebug()<<"update unitMobileUnitNotReg is:"<<query.exec("update report set unitMobileUnitNotReg=(select count(*) from file)");

    //单位移动用户-使用人&amp;经办人信息未登记
         qDebug()<<"update unitMobileOwnerAgentNotReg is:"<<query.exec("update report set unitMobileOwnerAgentNotReg=(select count(*) from file)");

    //单位移动用户-使用人&amp;单位信息未登记
         qDebug()<<"update unitMobileOwnerUnitNotReg is:"<<query.exec("update report set unitMobileOwnerUnitNotReg=(select count(*) from file)");

    //单位移动用户-经办人&amp;单位信息未登记
         qDebug()<<"update unitMobileAgentUnitNotReg is:"<<query.exec("update report set unitMobileAgentUnitNotReg=(select count(*) from file)");

    //单位移动用户-使用人&amp;经办人&amp;单位信息未登记
         qDebug()<<"update unitMobileOwnerAgentUnitNotReg is:"<<query.exec("update report set unitMobileOwnerAgentUnitNotReg=(select count(*) from file)");

    //单位移动用户-使用人信息校验不合规
         qDebug()<<"update unitMobileOwnerIllegal is:"<<query.exec("update report set unitMobileOwnerIllegal=(select count(*) from file)");

    //单位移动用户-经办人信息校验不合规
         qDebug()<<"update unitMobileAgentIllegal is:"<<query.exec("update report set unitMobileAgentIllegal=(select count(*) from file)");

    //单位移动用户-单位信息校验不合规
         qDebug()<<"update unitMobileUnitIllegal is:"<<query.exec("update report set unitMobileUnitIllegal=(select count(*) from file)");

    //单位移动用户-使用人&amp;经办人信息校验不合规
         qDebug()<<"update unitMobileOwnerAgentIllegal is:"<<query.exec("update report set unitMobileOwnerAgentIllegal=(select count(*) from file)");

    //单位移动用户-经办人&amp;单位信息校验不合规
         qDebug()<<"update unitMobileAgentUnitIllegal is:"<<query.exec("update report set unitMobileAgentUnitIllegal=(select count(*) from file)");

    //单位移动用户-使用人&amp;经办人&amp;单位信息校验不合规
         qDebug()<<"update unitMobileOwnerAgentUnitIllegal is:"<<query.exec("update report set unitMobileOwnerAgentUnitIllegal=(select count(*) from file)");

    //单位固话用户-形式合规数据
         qDebug()<<"update unitFixedLegal is:"<<query.exec("update report set unitFixedLegal=(select count(*) from file)");

    //单位固话用户-经办人信息未登记
         qDebug()<<"update unitFixedAgentNotReg is:"<<query.exec("update report set unitFixedAgentNotReg=(select count(*) from file)");

    //单位固话用户-单位信息未登记
         qDebug()<<"update unitFixedUnitNotReg is:"<<query.exec("update report set unitFixedUnitNotReg=(select count(*) from file)");

    //单位固话用户-经办人&amp;单位信息未登记
         qDebug()<<"update unitFixedAgentUnitNotReg is:"<<query.exec("update report set unitFixedAgentUnitNotReg=(select count(*) from file)");

    //单位固话用户-经办人信息校验不合规
         qDebug()<<"update unitFixedAgentIllegal is:"<<query.exec("update report set unitFixedAgentIllegal=(select count(*) from file)");

    //单位固话用户-单位信息校验不合规
         qDebug()<<"update unitFixedUnitIllegal is:"<<query.exec("update report set unitFixedUnitIllegal=(select count(*) from file)");

    //单位固话用户-经办人&amp;单位信息校验不合规
         qDebug()<<"update unitFixedAgentUnitIllegal is:"<<query.exec("update report set unitFixedAgentUnitIllegal=(select count(*) from file)");

    //行业移动应用-形式合规数据
         qDebug()<<"update tradeMobileLegal is:"<<query.exec("update report set tradeMobileLegal=(select count(*) from file)");

    //行业移动应用-经办人信息未登记
         qDebug()<<"update tradeMobileAgentNotReg is:"<<query.exec("update report set tradeMobileAgentNotReg=(select count(*) from file)");

    //行业移动应用-经办人&amp;单位信息未登记
         qDebug()<<"update tradeMobileAgentUnitNotReg is:"<<query.exec("update report set tradeMobileAgentUnitNotReg=(select count(*) from file)");

    //行业移动应用-责任人&amp;经办人信息未登记
         qDebug()<<"update tradeMobileLiableAgentNotReg is:"<<query.exec("update report set tradeMobileLiableAgentNotReg=(select count(*) from file)");

    //行业移动应用-责任人&amp;经办人&amp;单位信息未登记
         qDebug()<<"update tradeMobileLiableAgentUnitNotReg is:"<<query.exec("update report set tradeMobileLiableAgentUnitNotReg=(select count(*) from file)");

    //行业移动应用-单位信息未登记
         qDebug()<<"update tradeMobileUnitNotReg is:"<<query.exec("update report set tradeMobileUnitNotReg=(select count(*) from file)");

    //行业移动应用-责任人信息未登记
         qDebug()<<"update tradeMobileLiableNotReg is:"<<query.exec("update report set tradeMobileLiableNotReg=(select count(*) from file)");

    //行业移动应用-责任人&amp;单位信息未登记
         qDebug()<<"update tradeMobileLiableUnitNotReg is:"<<query.exec("update report set tradeMobileLiableUnitNotReg=(select count(*) from file)");

    //行业移动应用-经办人信息校验不合规
         qDebug()<<"update tradeMobileAgentIllegal is:"<<query.exec("update report set tradeMobileAgentIllegal=(select count(*) from file)");

    //行业移动应用-经办人&amp;单位信息校验不合规
         qDebug()<<"update tradeMobileAgentUnitIllegal is:"<<query.exec("update report set tradeMobileAgentUnitIllegal=(select count(*) from file)");

    //行业移动应用-责任人&amp;经办人信息校验不合规
         qDebug()<<"update tradeMobileLiableAgentIllegal is:"<<query.exec("update report set tradeMobileLiableAgentIllegal=(select count(*) from file)");

    //行业移动应用-责任人&amp;经办人&amp;单位信息校验不合规
         qDebug()<<"update tradeMobileLiableAgentUnitIllegal is:"<<query.exec("update report set tradeMobileLiableAgentUnitIllegal=(select count(*) from file)");

    //行业移动应用-单位信息校验不合规
         qDebug()<<"update tradeMobileUnitIllegal is:"<<query.exec("update report set tradeMobileUnitIllegal=(select count(*) from file)");

    //行业移动应用-责任人信息校验不合规
         qDebug()<<"update tradeMobileLiableIllegal is:"<<query.exec("update report set tradeMobileLiableIllegal=(select count(*) from file)");

    //行业移动应用-责任人&amp;单位信息校验不合规
         qDebug()<<"update tradeMobileLiableUnitIllegal is:"<<query.exec("update report set tradeMobileLiableUnitIllegal=(select count(*) from file)");

    //行业固话应用-形式合规数据
         qDebug()<<"update tradeFixedLegal is:"<<query.exec("update report set tradeFixedLegal=(select count(*) from file)");

    //行业固话应用-经办人信息未登记
         qDebug()<<"update tradeFixedAgentNotReg is:"<<query.exec("update report set tradeFixedAgentNotReg=(select count(*) from file)");

    //行业固话应用-经办人&amp;单位信息未登记
         qDebug()<<"update tradeFixedAgentUnitNotReg is:"<<query.exec("update report set tradeFixedAgentUnitNotReg=(select count(*) from file)");

    //行业固话应用-单位信息未登记
         qDebug()<<"update tradeFixedUnitNotReg is:"<<query.exec("update report set tradeFixedUnitNotReg=(select count(*) from file)");

    //行业固话应用-经办人信息校验不合规
         qDebug()<<"update tradeFixedAgentIllegal is:"<<query.exec("update report set tradeFixedAgentIllegal=(select count(*) from file)");

    //行业固话应用-经办人&amp;单位信息校验不合规
         qDebug()<<"update tradeFixedAgentUnitIllegal is:"<<query.exec("update report set tradeFixedAgentUnitIllegal=(select count(*) from file)");

    //行业固话应用-单位信息校验不合规
         qDebug()<<"update tradeFixedUnitIllegal is:"<<query.exec("update report set tradeFixedUnitIllegal=98");

    //个人移动一证五卡不合规
         qDebug()<<"update is:"<<query.exec("update report set personMobileOneCard=99");
    qDebug()<<"report is:"<<query.exec("select * from report");
    qDebug()<<"report next is:"<<query.next();
    int j=0;//i行j列
    for(int i=0;i<100;i++){
        ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i+1).toString()));
    }
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerTypeNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNumNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerAddNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameNumNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameAddNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNumAddNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameNumAddNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerTypeNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNumNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerAddNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameNumNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameAddNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNumAddNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameNumAddNotReg,10)));
}

Report::~Report()
{
    delete ui;
}
