#include "userdb.h"

UserDb::UserDb()
{
     stopped = false;
     QList<QList<QString>> lls = xmlConfig->readAutoid();
     delimeter = xmlConfig->readDelimiterValue();
     qDebug()<<"delimeter="<<delimeter;
     userType=xmlConfig->readUserType();
     QString name;
     report = new Report();
//    report->init();
    int num;
    bool ok;
    for(int i=0; i<lls.size(); i++){
        name = lls.at(i).at(1);
        num = lls.at(i).at(2).toInt(&ok,10);
        qDebug()<<"col name is "<<name<<" num is "<<num;
        col_name_map.insert(name,num);
    }
}

UserDb::~UserDb()
{
    delete report;
}
void UserDb::printMessage(){
    qDebug()<<QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)(size_t)QThread::currentThreadId());
}

void UserDb::start()
{
    stopped = false;
}

void UserDb::stop()
{
    stopped = true;
}

void UserDb::run()
{
    countData();
    qDebug()<<"run begin"<<stopped;
     emit message("run begin");
//    todo
    qDebug()<<"bool UserDb::insertDb(QString filename)"<<insertDb(filename);//"C:\\test.txt");// /Users/zhangxianjin/qtcode/test.txt");//test_data.txt"); //
    createReport();
}
void UserDb::createReport(){
    QSqlQuery query;
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
    qDebug()<<"insert report is:"<<query.exec("insert into report (id) values (1)");
    QString sql;
    //总量
    if(!report->allData){
       sql = "update report set allData=(select count(*) from file)";
    }
    else{
       sql = "update report set allData="+QString::number(report->allData);
    }
    qDebug()<< "update allData is:"<<query.exec(sql);
//    printData("file");

    //全量未登记
    if(!report->allNotReg){
        sql = "update report set allNotReg=(select count(*) from file where ("
                + getColName("机主证件地址")+ " is null ) and "
                + getColName("用户类型")+"='个人客户' and "
                + getColName("用户业务类型")+"='移动手机号码')";
    }
    else{
        sql = "update report set allNotReg"+QString::number(report->allNotReg);
    }
        qDebug()<<"update personMobileOwnerTypeNotReg is:"<<query.exec(sql)<<sql;
    //格式异常数据
        sql = "update report set formatNotRight="+QString::number(report->formatNotRight);
        qDebug()<<"update formatNotRight is:"<<query.exec(sql)<<sql;
    //字段异常数据
        sql = "update report set fieldNotRight="+QString::number(report->fieldNotRight);
         qDebug()<<"update fieldNotRight is:"<<query.exec(sql)<<sql;
    //all.ok
         sql = "update report set allOk="+QString::number(report->allOk);
         qDebug()<<"update allOk is:"<<query.exec(sql)<<sql;

    //待挖掘记录
 //         qDebug()<<"update allData is:"<<query.exec("update report set allData=(select count(*) from file)");

    //个人移动用户-形式合规数据
         sql = "update report set personMobileFormatRight="+QString::number(report->personMobileFormatRight);
         qDebug()<<"update personMobileFormatRight is:"<<query.exec(sql)<<sql;

    //个人移动用户-证件类型未登记
         if(!report->personMobileOwnerTypeNotReg){
         sql = "update report set personMobileOwnerTypeNotReg=(select count(*) from file where "
                 + getColName("机主证件类型")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set personMobileOwnerTypeNotReg="+QString::number(report->personMobileOwnerTypeNotReg);
         }
         qDebug()<<"update personMobileOwnerTypeNotReg is:"<<query.exec(sql)<<sql;

    //个人移动用户-用户姓名未登记
         if(!report->personMobileOwnerNameNotReg){
         sql = "update report set personMobileOwnerNameNotReg=(select count(*) from file where "
                 + getColName("机主姓名")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
        }
         else{
             sql = "update report set personMobileOwnerNameNotReg="+QString::number(report->personMobileOwnerNameNotReg);
         }
         qDebug()<<"update personMobileOwnerTypeNotReg is:"<<query.exec(sql)<<sql;

    //个人移动用户-证件号码未登记
         if(!report->personMobileOwnerNumNotReg){
         sql = "update report set personMobileOwnerNumNotReg=(select count(*) from file where "
                 + getColName("机主证件号码")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set personMobileOwnerNumNotReg="+QString::number(report->personMobileOwnerNumNotReg);
         }
         qDebug()<<"update personMobileOwnerTypeNotReg is:"<<query.exec(sql)<<sql;

    //个人移动用户-证件地址未登记
         if(!report->personMobileOwnerAddNotReg){
         sql = "update report set personMobileOwnerAddNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set personMobileOwnerAddNotReg="+QString::number(report->personMobileOwnerAddNotReg);
         }
         qDebug()<<"update personMobileOwnerAddNotReg is:"<<query.exec(sql)<<sql;

    //个人移动用户-用户姓名&amp;证件号码未登记
         if(!report->personMobileOwnerNameNumNotReg){
         sql = "update report set personMobileOwnerNameNumNotReg=(select count(*) from file where "
                 + getColName("机主姓名")+ " is null and "+ getColName("机主证件号码")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set personMobileOwnerNameNumNotReg="+QString::number(report->personMobileOwnerNameNumNotReg);
         }
         qDebug()<<"update personMobileOwnerNameNumNotReg is:"<<query.exec(sql)<<sql;

    //个人移动用户-用户姓名&amp;证件地址未登记
         if(!report->personMobileOwnerNameAddNotReg){
         sql = "update report set personMobileOwnerNameAddNotReg=(select count(*) from file where "
                 + getColName("机主姓名")+ " is null and "+ getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set personMobileOwnerNameAddNotReg="+QString::number(report->personMobileOwnerNameAddNotReg);
         }
         qDebug()<<"update personMobileOwnerNameAddNotReg is:"<<query.exec(sql)<<sql;

    //个人移动用户-证件号码&amp;证件地址未登记
         if(!report->personMobileOwnerNumAddNotReg){
         sql = "update report set personMobileOwnerNumAddNotReg=(select count(*) from file where "
                 + getColName("机主证件号码")+ " is null and "+ getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set personMobileOwnerNumAddNotReg="+QString::number(report->personMobileOwnerNumAddNotReg);
         }
         qDebug()<<"update personMobileOwnerNumAddNotReg is:"<<query.exec(sql)<<sql;

    //个人移动用户-用户姓名&amp;证件号码&amp;证件地址未登记
         if(!report->personMobileOwnerNameNumAddNotReg){
         sql = "update report set personMobileOwnerNameNumAddNotReg=(select count(*) from file where "
                 + getColName("机主姓名")+ " is null and " + getColName("机主证件号码")+ " is null and " + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set personMobileOwnerNameNumAddNotReg="+QString::number(report->personMobileOwnerNameNumAddNotReg);
         }
         qDebug()<<"update personMobileOwnerNameNumAddNotReg is:"<<query.exec(sql)<<sql;

    //个人移动用户-证件类型校验不合规
         sql = "update report set personMobileOwnerTypeIllegal="+QString::number(report->personMobileOwnerTypeIllegal);
         qDebug()<<"update personMobileOwnerTypeIllegal is:"<<query.exec(sql)<<sql;

    //个人移动用户-用户姓名校验不合规
         sql = "update report set personMobileOwnerNameIllegal="+QString::number(report->personMobileOwnerNameIllegal);
         qDebug()<<"update personMobileOwnerNameIllegal is:"<<query.exec(sql)<<sql;

    //个人移动用户-证件号码校验不合规
         sql = "update report set personMobileOwnerNumIllegal="+QString::number(report->personMobileOwnerNumIllegal);
         qDebug()<<"update personMobileOwnerNumIllegal is:"<<query.exec(sql)<<sql;

    //个人移动用户-证件地址校验不合规
         sql = "update report set personMobileOwnerAddIllegal="+QString::number(report->personMobileOwnerAddIllegal);
         qDebug()<<"update personMobileOwnerAddIllegal is:"<<query.exec(sql)<<sql;

    //个人移动用户-用户姓名&amp;证件号码校验不合规
         sql = "update report set personMobileOwnerNameNumIllegal="+QString::number(report->personMobileOwnerNameNumIllegal);
         qDebug()<<"update personMobileOwnerNameNumIllegal is:"<<query.exec(sql)<<sql;

    //个人移动用户-用户姓名&amp;证件地址校验不合规
         sql = "update report set personMobileOwnerNameAddIllegal="+QString::number(report->personMobileOwnerNameAddIllegal);
         qDebug()<<"update personMobileOwnerNameAddIllegal is:"<<query.exec(sql)<<sql;

    //个人移动用户-证件号码&amp;证件地址校验不合规
         sql = "update report set personMobileOwnerNumAddIllegal="+QString::number(report->personMobileOwnerNumAddIllegal);
         qDebug()<<"update personMobileOwnerNumAddIllegal is:"<<query.exec(sql)<<sql;

    //个人移动用户-用户姓名&amp;证件号码&amp;证件地址校验不合规
         sql = "update report set personMobileOwnerNameNumAddIllegal="+QString::number(report->personMobileOwnerNameNumAddIllegal);
         qDebug()<<"update personMobileOwnerNameNumAddIllegal is:"<<query.exec(sql)<<sql;

    //个人固话用户-形式合规数据
         sql = "update report set personFixedLegal="+QString::number(report->personFixedLegal);
         qDebug()<<"update personFixedLegal is:"<<query.exec(sql)<<sql;

    //个人固话用户-证件类型未登记
         if(!report->personFixedOwnerTypeNotReg){
         sql = "update report set personFixedOwnerTypeNotReg = (select count(*) from file where "
                 + getColName("机主证件类型")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='固定')";
         }
         else{
             sql = "update report set personFixedOwnerTypeNotReg="+QString::number(report->personFixedOwnerTypeNotReg);
         }
         qDebug()<<"update personFixedOwnerTypeNotReg is:"<<query.exec(sql)<<sql;

//    //个人固话用户-用户姓名未登记
         if(!report->personFixedOwnerNameNotReg){
         sql = "update report set personFixedOwnerNameNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='固定')";
         }
         else{
             sql = "update report set personFixedOwnerNameNotReg="+QString::number(report->personFixedOwnerNameNotReg);
         }
         qDebug()<<"update personFixedOwnerNameNumNotReg is:"<<query.exec(sql)<<sql;

//    //个人固话用户-证件号码未登记
         if(!report->personFixedOwnerNumNotReg){
         sql = "update report set personFixedOwnerNumNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='固定')";
         }
         else{
             sql = "update report set personFixedOwnerNumNotReg="+QString::number(report->personFixedOwnerNumNotReg);
         }
         qDebug()<<"update personFixedOwnerNumNotReg is:"<<query.exec(sql)<<sql;

//    //个人固话用户-证件地址未登记
         if(!report->personFixedOwnerAddNotReg){
         sql = "update report set personFixedOwnerAddNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='固定')";
         }
         else{
             sql = "update report personFixedOwnerAddNotReg="+QString::number(report->personFixedOwnerAddNotReg);
         }
         qDebug()<<"update personFixedOwnerAddNotReg is:"<<query.exec(sql)<<sql;

//    //个人固话用户-用户姓名&amp;证件号码未登记
         if(!report->personFixedOwnerNameNumNotReg){
         sql = "update report set personFixedOwnerNameNumNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='固定')";
         }
         else{
             sql = "update report set personFixedOwnerNameNumNotReg="+QString::number(report->personFixedOwnerNameNumNotReg);
         }
         qDebug()<<"update personFixedOwnerNameNumNotReg is:"<<query.exec(sql)<<sql;

//    //个人固话用户-用户姓名&amp;证件地址未登记
         if(!report->personFixedOwnerNameAddNotReg){
         sql = "update report set personFixedOwnerNameAddNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='固定')";
         }
         else{
             sql = "update report set personFixedOwnerNameAddNotReg="+QString::number(report->personFixedOwnerNameAddNotReg);
         }
         qDebug()<<"update personFixedOwnerNameAddNotReg is:"<<query.exec(sql)<<sql;

//    //个人固话用户-证件号码&amp;证件地址未登记
         if(!report->personFixedOwnerNumAddNotReg){
         sql = "update report set personFixedOwnerNumAddNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='固定')";
         }
         else{
             sql = "update report set personFixedOwnerNumAddNotReg="+QString::number(report->personFixedOwnerNumAddNotReg);
         }
         qDebug()<<"update personFixedOwnerNumAddNotReg is:"<<query.exec(sql)<<sql;

//    //个人固话用户-用户姓名&amp;证件号码&amp;证件地址未登记
         if(!report->personFixedOwnerNameNumAddNotReg){
         sql = "update report set personFixedOwnerNameNumAddNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='固定')";
         }
         else{
             sql = "update report set personFixedOwnerNameNumAddNotReg="+QString::number(report->personFixedOwnerNameNumAddNotReg);
         }
         qDebug()<<"update personFixedOwnerNameNumAddNotReg is:"<<query.exec(sql)<<sql;

    //个人固话用户-证件类型校验不合规
         sql = "update report set personFixedOwnerTypeIllegal="+QString::number(report->personFixedOwnerTypeIllegal);
         qDebug()<<"update personFixedOwnerTypeIllegal is:"<<query.exec(sql)<<sql;

    //个人固话用户-用户姓名校验不合规
         sql = "update report set personFixedOwnerNameIllegal="+QString::number(report->personFixedOwnerNameIllegal);
         qDebug()<<"update personFixedOwnerNameIllegal is:"<<query.exec(sql)<<sql;

    //个人固话用户-证件号码校验不合规
         sql = "update report set personFixedOwnerNumIllegal="+QString::number(report->personFixedOwnerNumIllegal);
         qDebug()<<"update personFixedOwnerNumIllegal is:"<<query.exec(sql)<<sql;

    //个人固话用户-证件地址校验不合规
         sql = "update report set personFixedOwnerAddIllegal="+QString::number(report->personFixedOwnerAddIllegal);
         qDebug()<<"update personFixedOwnerAddIllegal is:"<<query.exec(sql)<<sql;

    //个人固话用户-用户姓名&amp;证件号码校验不合规
         sql = "update report set personFixedOwnerNameNumIllegal="+QString::number(report->personFixedOwnerNameNumIllegal);
         qDebug()<<"update personFixedOwnerNameNumIllegal is:"<<query.exec(sql)<<sql;

    //个人固话用户-用户姓名&amp;证件地址校验不合规
         sql = "update report set personFixedOwnerNameAddIllegal="+QString::number(report->personFixedOwnerNameAddIllegal);
         qDebug()<<"update personFixedOwnerNameAddIllegal is:"<<query.exec(sql)<<sql;

    //个人固话用户-证件号码&amp;证件地址校验不合规
         sql = "update report set personFixedOwnerNumAddIllegal="+QString::number(report->personFixedOwnerNumAddIllegal);
         qDebug()<<"update personFixedOwnerNumAddIllegal is:"<<query.exec(sql)<<sql;

    //个人固话用户-用户姓名&amp;证件号码&amp;证件地址校验不合规
         sql = "update report set personFixedOwnerNameNumAddIllegal="+QString::number(report->personFixedOwnerNameNumAddIllegal);
         qDebug()<<"update personFixedOwnerNameNumAddIllegal is:"<<query.exec(sql)<<sql;

    //个人移动用户-代办人信息未登记
         if(!report->personMobileAgentNotReg){
         sql = "update report set personMobileAgentNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='个人客户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set personMobileAgentNotReg="+QString::number(report->personMobileAgentNotReg);
         }
         qDebug()<<"update personMobileAgentNotReg is:"<<query.exec(sql)<<sql;

    //个人固话用户-代办人信息未登记
         if(!report->personFixedAgentNotReg){
             sql = "update report set personFixedAgentNotReg=(select count(*) from file where "
                     + getColName("机主证件地址")+ " is null and "
                     + getColName("用户类型")+"='个人客户' and "
                     + getColName("用户业务类型")+"='固定')";
         }
         else{
             sql = "update report set personFixedAgentNotReg="+QString::number(report->personFixedAgentNotReg);
         }
         qDebug()<<"update personFixedAgentNotReg is:"<<query.exec(sql)<<sql;

    //个人移动用户-代办人信息校验不合规
         sql = "update report set personMobileAgentIllegal="+QString::number(report->personMobileAgentIllegal);
         qDebug()<<"update personMobileAgentIllegal is:"<<query.exec(sql)<<sql;

    //个人固话用户-代办人信息校验不合规
         sql = "update report set personFixedAgentIllegal="+QString::number(report->personFixedAgentIllegal);
         qDebug()<<"update personFixedAgentIllegal is:"<<query.exec(sql)<<sql;

    //单位移动用户-形式合规数据
         sql = "update report set unitMobileLegal="+QString::number(report->unitMobileLegal);
         qDebug()<<"update unitMobileLegal is:"<<query.exec(sql)<<sql;

    //单位移动用户-使用人信息未登记
         if(!report->unitMobileOwnerNotReg){
             sql = "update report set unitMobileOwnerNotReg=(select count(*) from file where "
                     + getColName("机主证件地址")+ " is null and "
                     + getColName("用户类型")+"='单位用户' and "
                     + getColName("用户业务类型")+"='移动手机号码')";
        }
         else{
             sql = "update report set unitMobileOwnerNotReg="+QString::number(report->unitMobileOwnerNotReg);
         }
         qDebug()<<"update unitMobileOwnerNotReg is:"<<query.exec(sql)<<sql;

//    //单位移动用户-经办人信息未登记
         if(!report->unitMobileAgentNotReg){
             sql = "update report set unitMobileAgentNotReg=(select count(*) from file where "
                     + getColName("机主证件地址")+ " is null and "
                     + getColName("用户类型")+"='单位用户' and "
                     + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set unitMobileAgentNotReg="+QString::number(report->unitMobileAgentNotReg);
         }
         qDebug()<<"update unitMobileAgentNotReg is:"<<query.exec(sql)<<sql;

//    //单位移动用户-单位信息未登记
         if(!report->unitMobileUnitNotReg){
         sql = "update report set unitMobileUnitNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='单位用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set unitMobileUnitNotReg="+QString::number(report->unitMobileUnitNotReg);
         }
         qDebug()<<"update unitMobileUnitNotReg is:"<<query.exec(sql)<<sql;

//    //单位移动用户-使用人&amp;经办人信息未登记
         if(!report->unitMobileOwnerAgentNotReg){
             sql = "update report set unitMobileOwnerAgentNotReg=(select count(*) from file where "
                     + getColName("机主证件地址")+ " is null and "
                     + getColName("用户类型")+"='单位用户' and "
                     + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set unitMobileOwnerAgentNotReg="+QString::number(report->unitMobileOwnerAgentNotReg);
         }
         qDebug()<<"update unitMobileOwnerAgentNotReg is:"<<query.exec(sql)<<sql;

//    //单位移动用户-使用人&amp;单位信息未登记
         if(!report->unitMobileOwnerUnitNotReg){
         sql = "update report set unitMobileOwnerUnitNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='单位用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set unitMobileOwnerUnitNotReg="+QString::number(report->unitMobileOwnerUnitNotReg);
         }
         qDebug()<<"update unitMobileOwnerUnitNotReg is:"<<query.exec(sql)<<sql;

//    //单位移动用户-经办人&amp;单位信息未登记
         if(!report->unitMobileAgentUnitNotReg){
         sql = "update report set unitMobileAgentUnitNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='单位用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set unitMobileAgentUnitNotReg="+QString::number(report->unitMobileAgentUnitNotReg);
         }
         qDebug()<<"update unitMobileAgentUnitNotReg is:"<<query.exec(sql)<<sql;

//    //单位移动用户-使用人&amp;经办人&amp;单位信息未登记
         if(!report->unitMobileOwnerAgentUnitNotReg){
         sql = "update report set unitMobileOwnerAgentUnitNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='单位用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set unitMobileOwnerAgentUnitNotReg="+QString::number(report->unitMobileOwnerAgentUnitNotReg);
         }
         qDebug()<<"update unitMobileOwnerAgentUnitNotReg is:"<<query.exec(sql)<<sql;

    //单位移动用户-使用人信息校验不合规
         sql = "update report set unitMobileOwnerIllegal="+QString::number(report->unitMobileOwnerIllegal);
         qDebug()<<"update unitMobileOwnerIllegal is:"<<query.exec(sql)<<sql;

    //单位移动用户-经办人信息校验不合规
         sql = "update report set unitMobileAgentIllegal="+QString::number(report->unitMobileAgentIllegal);
         qDebug()<<"update unitMobileAgentIllegal is:"<<query.exec(sql)<<sql;

    //单位移动用户-单位信息校验不合规
         sql = "update report set unitMobileUnitIllegal="+QString::number(report->unitMobileUnitIllegal);
         qDebug()<<"update unitMobileUnitIllegal is:"<<query.exec(sql)<<sql;

    //单位移动用户-使用人&amp;经办人信息校验不合规
         sql = "update report set unitMobileOwnerAgentIllegal="+QString::number(report->unitMobileOwnerAgentIllegal);
         qDebug()<<"update unitMobileOwnerAgentIllegal is:"<<query.exec(sql)<<sql;

    //单位移动用户-经办人&amp;单位信息校验不合规
         sql = "update report set unitMobileAgentUnitIllegal="+QString::number(report->unitMobileAgentUnitIllegal);
         qDebug()<<"update unitMobileAgentUnitIllegal is:"<<query.exec(sql)<<sql;

    //单位移动用户-使用人&amp;经办人&amp;单位信息校验不合规
         sql = "update report set unitMobileOwnerAgentUnitIllegal="+QString::number(report->unitMobileOwnerAgentUnitIllegal);
         qDebug()<<"update unitMobileOwnerAgentUnitIllegal is:"<<query.exec(sql)<<sql;

    //单位固话用户-形式合规数据
         sql = "update report set unitFixedLegal="+QString::number(report->unitFixedLegal);
         qDebug()<<"update unitFixedLegal is:"<<query.exec(sql)<<sql;

    //单位固话用户-经办人信息未登记
         if(!report->unitFixedAgentNotReg){
         sql = "update report set unitFixedAgentNotReg=(select count(*) from file where "
                 + getColName("代（经）办人姓名")+ " is null and "
                 + getColName("用户类型")+"='单位用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set unitFixedAgentNotReg="+QString::number(report->unitFixedAgentNotReg);
         }
         qDebug()<<"update unitFixedAgentNotReg is:"<<query.exec(sql)<<sql;

//    //单位固话用户-单位信息未登记
         if(!report->unitFixedUnitNotReg){
         sql = "update report set unitFixedUnitNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='单位用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set unitFixedUnitNotReg="+QString::number(report->unitFixedUnitNotReg);
         }
         qDebug()<<"update unitMobileUnitNotReg is:"<<query.exec(sql)<<sql;

//    //单位固话用户-经办人&amp;单位信息未登记
         if(!report->unitFixedAgentUnitNotReg){
         sql = "update report set unitFixedAgentUnitNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='单位用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set unitFixedAgentUnitNotReg="+QString::number(report->unitFixedAgentUnitNotReg);
         }
         qDebug()<<"update unitFixedAgentUnitNotReg is:"<<query.exec(sql)<<sql;

    //单位固话用户-经办人信息校验不合规
         sql = "update report set unitFixedAgentIllegal="+QString::number(report->unitFixedAgentIllegal);
         qDebug()<<"update unitFixedAgentIllegal is:"<<query.exec(sql)<<sql;

    //单位固话用户-单位信息校验不合规
         sql = "update report set unitFixedUnitIllegal="+QString::number(report->unitFixedUnitIllegal);
         qDebug()<<"update unitFixedUnitIllegal is:"<<query.exec(sql)<<sql;

    //单位固话用户-经办人&amp;单位信息校验不合规
         sql = "update report set unitFixedAgentUnitIllegal="+QString::number(report->unitFixedAgentUnitIllegal);
         qDebug()<<"update unitFixedAgentUnitIllegal is:"<<query.exec(sql)<<sql;

    //行业移动应用-形式合规数据
         sql = "update report set tradeMobileLegal="+QString::number(report->tradeMobileLegal);
         qDebug()<<"update tradeMobileLegal is:"<<query.exec(sql)<<sql;

    //行业移动应用-经办人信息未登记
         if(!report->tradeMobileAgentNotReg){
         sql = "update report set tradeMobileAgentNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='行业用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set tradeMobileAgentNotReg="+QString::number(report->tradeMobileAgentNotReg);
         }
         qDebug()<<"update tradeMobileAgentNotReg is:"<<query.exec(sql)<<sql;

//    //行业移动应用-经办人&amp;单位信息未登记
         if(!report->tradeMobileAgentUnitNotReg){
             sql = "update report set tradeMobileAgentUnitNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='行业用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set tradeMobileAgentUnitNotReg="+QString::number(report->tradeMobileAgentUnitNotReg);
         }
         qDebug()<<"update tradeMobileAgentUnitNotReg is:"<<query.exec(sql)<<sql;

//    //行业移动应用-责任人&amp;经办人信息未登记
         if(!report->tradeMobileLiableAgentNotReg){
         sql = "update report set tradeMobileLiableAgentNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='行业用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set tradeMobileLiableAgentNotReg="+QString::number(report->tradeMobileLiableAgentNotReg);
         }
         qDebug()<<"update tradeMobileLiableAgentNotReg is:"<<query.exec(sql)<<sql;

//    //行业移动应用-责任人&amp;经办人&amp;单位信息未登记
         if(!report->tradeMobileLiableAgentUnitNotReg){
         sql = "update report set tradeMobileLiableAgentUnitNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='行业用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set tradeMobileLiableAgentUnitNotReg="+QString::number(report->tradeMobileLiableAgentUnitNotReg);
         }
         qDebug()<<"update tradeMobileLiableAgentUnitNotReg is:"<<query.exec(sql)<<sql;

//    //行业移动应用-单位信息未登记
         if(!report->tradeMobileUnitNotReg){
         sql = "update report set tradeMobileUnitNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='行业用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set tradeMobileUnitNotReg="+QString::number(report->tradeMobileUnitNotReg);
         }
         qDebug()<<"update tradeMobileUnitNotReg is:"<<query.exec(sql)<<sql;

//    //行业移动应用-责任人信息未登记
         if(!report->tradeMobileLiableNotReg){
         sql = "update report set tradeMobileLiableNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='行业用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set tradeMobileLiableNotReg="+QString::number(report->tradeMobileLiableNotReg);
         }
         qDebug()<<"update tradeMobileLiableNotReg is:"<<query.exec(sql)<<sql;

//    //行业移动应用-责任人&amp;单位信息未登记
         if(!report->tradeMobileLiableUnitNotReg){
         sql = "update report set tradeMobileLiableUnitNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='行业用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set tradeMobileLiableUnitNotReg="+QString::number(report->tradeMobileLiableUnitNotReg);
         }
         qDebug()<<"update tradeMobileLiableUnitNotReg is:"<<query.exec(sql)<<sql;

    //行业移动应用-经办人信息校验不合规
         sql = "update report set tradeMobileAgentIllegal="+QString::number(report->tradeMobileAgentIllegal);
         qDebug()<<"update tradeMobileAgentIllegal is:"<<query.exec(sql)<<sql;

    //行业移动应用-经办人&amp;单位信息校验不合规
         sql = "update report set tradeMobileAgentUnitIllegal="+QString::number(report->tradeMobileAgentUnitIllegal);
         qDebug()<<"update tradeMobileAgentUnitIllegal is:"<<query.exec(sql)<<sql;

    //行业移动应用-责任人&amp;经办人信息校验不合规
         sql = "update report set tradeMobileLiableAgentIllegal="+QString::number(report->tradeMobileLiableAgentIllegal);
         qDebug()<<"update tradeMobileLiableAgentIllegal is:"<<query.exec(sql)<<sql;

    //行业移动应用-责任人&amp;经办人&amp;单位信息校验不合规
         sql = "update report set tradeMobileLiableAgentUnitIllegal="+QString::number(report->tradeMobileLiableAgentUnitIllegal);
         qDebug()<<"update tradeMobileLiableAgentUnitIllegal is:"<<query.exec(sql)<<sql;

    //行业移动应用-单位信息校验不合规
         sql = "update report set tradeMobileUnitIllegal="+QString::number(report->tradeMobileUnitIllegal);
         qDebug()<<"update tradeMobileUnitIllegal is:"<<query.exec(sql)<<sql;

    //行业移动应用-责任人信息校验不合规
         sql = "update report set tradeMobileLiableIllegal="+QString::number(report->tradeMobileLiableIllegal);
         qDebug()<<"update tradeMobileLiableIllegal is:"<<query.exec(sql)<<sql;

    //行业移动应用-责任人&amp;单位信息校验不合规
         sql = "update report set tradeMobileLiableUnitIllegal="+QString::number(report->tradeMobileLiableUnitIllegal);
         qDebug()<<"update tradeMobileLiableUnitIllegal is:"<<query.exec(sql)<<sql;

    //行业固话应用-形式合规数据
         sql = "update report set tradeFixedLegal="+QString::number(report->tradeFixedLegal);
         qDebug()<<"update tradeFixedLegal is:"<<query.exec(sql)<<sql;

    //行业固话应用-经办人信息未登记
         if(!report->tradeFixedAgentNotReg){
         sql = "update report set tradeFixedAgentNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='行业用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set tradeFixedAgentNotReg="+QString::number(report->tradeFixedAgentNotReg);
         }
         qDebug()<<"update tradeFixedAgentNotReg is:"<<query.exec(sql)<<sql;

//    //行业固话应用-经办人&amp;单位信息未登记
         if(!report->tradeFixedAgentUnitNotReg){
         sql = "update report set tradeFixedAgentUnitNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='行业用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set tradeFixedAgentUnitNotReg="+QString::number(report->tradeFixedAgentUnitNotReg);
         }
         qDebug()<<"update tradeFixedAgentUnitNotReg is:"<<query.exec(sql)<<sql;

//    //行业固话应用-单位信息未登记
         if(!report->tradeFixedUnitNotReg){
         sql = "update report set tradeFixedUnitNotReg=(select count(*) from file where "
                 + getColName("机主证件地址")+ " is null and "
                 + getColName("用户类型")+"='行业用户' and "
                 + getColName("用户业务类型")+"='移动手机号码')";
         }
         else{
             sql = "update report set tradeFixedUnitNotReg="+QString::number(report->tradeFixedUnitNotReg);
         }
         qDebug()<<"update tradeFixedUnitNotReg is:"<<query.exec(sql)<<sql;

    //行业固话应用-经办人信息校验不合规
         sql = "update report set tradeFixedAgentIllegal="+QString::number(report->tradeFixedAgentIllegal);
         qDebug()<<"update tradeFixedAgentIllegal is:"<<query.exec(sql)<<sql;

    //行业固话应用-经办人&amp;单位信息校验不合规
         sql = "update report set tradeFixedAgentUnitIllegal="+QString::number(report->tradeFixedAgentUnitIllegal);
         qDebug()<<"update tradeFixedAgentUnitIllegal is:"<<query.exec(sql)<<sql;

    //行业固话应用-单位信息校验不合规
         sql = "update report set tradeFixedUnitIllegal="+QString::number(report->tradeFixedUnitIllegal);
         qDebug()<<"update tradeFixedUnitIllegal is:"<<query.exec(sql)<<sql;

    //个人移动一证五卡不合规
         if(!report->personMobileOneCard){
             sql = "update report set personMobileOneCard=(select count(1) from file group by col"+getColName("机主证件号码")+" having count(1)>5)";
         }
         else{
            sql = "update report set personMobileOneCard="+QString::number(report->personMobileOneCard);
         }
         qDebug()<<"update personMobileOneCard is:"<<query.exec(sql)<<sql;

}

QString UserDb::getColName(QString name){
    //    int rtn = ;
        qDebug()<<"查询的列名是"<<name<<"列号是"<<col_name_map.value(name)+1;
        return "col"+QString::number(col_name_map.value(name)+1);
}

int UserDb::getColNum(QString name){
    //    int rtn = ;
        qDebug()<<"查询的列名是"<<name<<"列号是"<<col_name_map.value(name)+1;
        return col_name_map.value(name)+1;
}

//创建数据库表
bool UserDb::createTable(){
//    connDb();

    QString sql = "create table file(id varchar primary key";
    for(int i=0;i<42;i++){
        sql.append(",col").append( QString::number(i+1, 10)).append(" varchar");
    }
    sql.append(")");


    QSqlQuery query;

    qDebug()<<"drop table"<<query.exec("drop table file");
    qDebug()<<"createTable()"<<sql;
    bool b = query.exec(sql);
    qDebug()<<b;
    return b;
}


QString UserDb::getCol(QString str){
    if(str=="null")
        return NULL;//"'"+str+"'";
    else
        return str;
}

//文件入库
bool UserDb::insertDb(QString filename){
    qDebug()<<"insertDb";
    if(!fileIsExists(filename)){
        qDebug()<<"文件不存在。\n当前路径是：";
        qDebug()<< QDir::currentPath();
        return false;
    }
    if(!createTable()){
        qDebug()<<"库表创建不成功。";
        return false;
    }


    QSqlQuery query;
    QFile file(filename);
    QTextCodec *code = QTextCodec::codecForName("GBK");//设置文件编码


    QList<QString> col;
    QString sql="";
    QString line = "";
    int line_num = 1;

    QTime    tmpTime;
    bool isSuccess = true;
    if(file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream stream(&file);
        stream.setCodec(code);

        createConnection();//建立数据库连接
        qDebug()<<"db isopen?"<<db.isOpen();
        qDebug()<<"start transaction"<<db.transaction();
         do {

            line = stream.readLine();
            col =  line.split(delimeter);
            if(col.size() != COL_NUM){
                qDebug()<<"列数不对"<<col.size();
                //todo
                continue;
            }
//            qDebug()<<"tmp is :"<<qPrintable(line);

            sql = "insert into file values(?";
            for(int i=0;i<col.size();i++){
                sql.append(",?");
//                sql.append(","+getCol(col[i])+"");
            }
            sql.append(")");
            query.prepare(sql);

            query.addBindValue(line_num++);
            for(int i=0;i<col.size();i++){
//                qDebug()<<"i:"<<i<<"--"<<getCol(col[i]);
                query.addBindValue(getCol(col[i]));
            }

            if(!query.exec()){
                isSuccess=false;
                qDebug()<<"执行出错"<<sql;
                break;
           }

            if(!stopped && line_num%10000==0)
            {
                if(db.commit())
                {
                    qDebug()<<"commit";
                    qDebug()<<"10000条数据耗时："<<tmpTime.elapsed()<<"ms"<<endl;
                    qDebug()<<"db isopen?"<<db.isOpen();
                    qDebug()<<"start transaction"<<db.transaction();
                    tmpTime.start();
                    emit message("已处理"+QString::number(line_num)+"行");
                    qDebug()<<"line_num"<<line_num;
                }
                else{
                    qDebug()<<"error: line_num"<<line_num<<" "<<sql;
                    qDebug()<<"roll back"<<db.rollback();
                }
            }
        }while(!stopped && !line.isEmpty());
        qDebug()<<"final commit"<<db.commit();
//        db.close();
    }
    else{
        qDebug()<<QStringLiteral("文件打开错误。");
    }
    return true;
}

//文件是否存在
bool UserDb::fileIsExists(QString filename){
    if(filename.isNull()||filename.isEmpty()){
        qDebug()<<QStringLiteral("文件名参数不正确。");
        return false;
    }
    QFile file(filename);
    return file.exists();
}


/**
 * 读取数据库函数
 * @brief UserFile::readTable
 * @param sql sqlite语句
 * @return 数据列表
 */
QList<QString> UserDb::readTable(QString sql){
    QList<QString> list;
    QString line = "";

    QSqlQuery query;
    query.exec(sql);
    QSqlRecord qr = query.record();
    qDebug()<<sql<<"中字段数为"<<qr.count();

    while(query.next()){
        line = "";
        for(int i=0;i<qr.count();i++){
            line.append(query.value(i).toString());

        }
         qDebug()<<"line:"<<qPrintable(line);
        list.append(line);
    }
//    db.close();
    return list;
}

void UserDb::printData(QString table){
    QList<QString> list = readTable("select * from "+table);
    for(int i=0;i<list.size();i++){
        qDebug()<<list.at(i);
    }
}

bool UserDb::countData(){
    qDebug()<<__FUNCTION__;
    if(!fileIsExists(filename)){
        qDebug()<<"文件不存在。\n当前路径是：";
        qDebug()<< QDir::currentPath();
        return false;
    }

    QFile file(filename);
    QTextCodec *code = QTextCodec::codecForName("GBK");//设置文件编码


//    QList<QString> col;
    QString line = "";
    int line_num = 1;

    QTime    tmpTime;
    if(file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream stream(&file);
        stream.setCodec(code);

         do {
            line = stream.readLine();

//            col =  line.split(strItemDelimeter);

//            if(col.size() != COL_NUM){
//                qDebug()<<"列数不对"<<col.size();
//                //todo
//                continue;
//            }
            processLine(line);
//            qDebug()<<"tmp is :"<<qPrintable(line);

            if(!stopped && line_num%10000==0)
            {
                    qDebug()<<"commit";
                    qDebug()<<"10000条数据耗时："<<tmpTime.elapsed()<<"ms"<<endl;
                    tmpTime.start();
                    emit message("已处理"+QString::number(line_num)+"行");
                    qDebug()<<"line_num"<<line_num;
            }
        }while(!stopped && !line.isEmpty());
    }
    else{
        qDebug()<<QStringLiteral("文件打开错误。");
    }
    return true;
}


void UserDb::processLine(QString line){
//    delimeter = XMLConfigReader.readDelimiterValue();
    QList<QString> col;
    col =  line.split(delimeter);

    if(col.size() != COL_NUM){
        qDebug()<<"列数不对"<<col.size();
        saveAbnormal(line);
    }

    if(col.at(getColNum("用户类型"))==userType.value("person")){
        if(col.at(getColNum("用户业务类型"))=="移动"){
            bool p_m_o_t_r=false;//"个人移动用户-证件类型未登记
            bool p_m_o_name_r=false;//个人移动用户-用户姓名未登记
            bool p_m_o_num_r=false;//个人移动用户-证件号码未登记
            bool p_m_o_add_r=false;//个人移动用户-证件地址未登记
            bool p_m_o_t_n=false;//"个人移动用户-证件类型不合规
            bool p_m_o_name_n=false;//个人移动用户-用户姓名不合规
            bool p_m_o_num_n=false;//个人移动用户-证件号码不合规
            bool p_m_o_add_n=false;//个人移动用户-证件地址不合规
            if(col.at(getColNum("机主证件类型")).isEmpty()){
                savePersonMobileOwnerTypeNotReg(line);
                saveAllNotReg(line);
                p_m_o_t_r = true;
            }
            if(col.at(getColNum("机主用户姓名")).isEmpty()){
                savePersonMobileOwnerNameNotReg(line);
                saveAllNotReg(line);
                p_m_o_name_r=true;
            }
            if(col.at(getColNum("机主证件号码")).isEmpty()){
                savePersonMobileOwnerNumNotReg(line);
                saveAllNotReg(line);
                p_m_o_num_r=true;
            }
            if(col.at(getColNum("机主证件地址")).isEmpty()){
                savePersonMobileOwnerAddNotReg(line);
                saveAllNotReg(line);
                p_m_o_add_r=true;
            }
            if(p_m_o_name_r&&p_m_o_num_r){
                savePersonMobileOwnerNameNumNotReg(line);
            }
            if(p_m_o_name_r&&p_m_o_add_r){
                savePersonMobileOwnerNameAddNotReg(line);
            }
            if(p_m_o_num_r&&p_m_o_add_r){
                savePersonMobileOwnerNumAddNotReg(line);
            }
            if(p_m_o_name_r&&p_m_o_num_r&&p_m_o_add_r){
                savePersonMobileOwnerNameNumAddNotReg(line);
            }
            if(col.at(getColNum("机主证件类型")).isEmpty()){
                savePeronMobileOwnerTyteNok(line);
                p_m_o_t_n=true;
            }
            if(col.at(getColNum("机主用户姓名")).isEmpty()){
                savePeronMobileOwnerNameNok(line);
                p_m_o_name_n=true;
            }
            if(col.at(getColNum("机主证件号码")).isEmpty()){
                savePeronMobileOwnerNumNok(line);
                p_m_o_num_n=true;
            }
            if(col.at(getColNum("机主证件地址")).isEmpty()){
                savePeronMobileOwnerAddNok(line);
                p_m_o_add_n=true;
            }
            if(p_m_o_name_n&&p_m_o_num_n){
                savePeronMobileOwnerNameNumNok(line);
            }
            if(p_m_o_name_n&&p_m_o_add_n){
                savePeronMobileOwnerNameAddNok(line);
            }
            if(p_m_o_num_n&&p_m_o_add_n){
                savePeronMobileOwnerNumAddNok(line);
            }
            if(p_m_o_name_n&&p_m_o_num_n&&p_m_o_add_n){
                savePeronMobileOwnerNameNumAddNok(line);
            }
            if(!(p_m_o_t_r&&p_m_o_t_n&&p_m_o_name_r&&p_m_o_num_r&&p_m_o_add_r&&p_m_o_name_n&&p_m_o_num_n&&p_m_o_add_n)){
                savePersonMobileOk(line);
            }
        }
        else if(col.at(getColNum("用户业务类型"))=="固定"){
            bool p_f_o_t_r=false;//"个人固定用户-证件类型未登记
            bool p_f_o_name_r=false;//个人固定用户-用户姓名未登记
            bool p_f_o_num_r=false;//个人固定用户-证件号码未登记
            bool p_f_o_add_r=false;//个人固定用户-证件地址未登记
            bool p_f_o_agent_r=false;//个人固定用户-代办人未登记
            if(col.at(getColNum("机主证件类型")).isEmpty()){
                savePersonFixedOwnerTypeNotReg(line);
                saveAllNotReg(line);
                p_f_o_t_r=true;
            }
            if(col.at(getColNum("机主用户姓名")).isEmpty()){
                savePersonFixedOwnerNameNotReg(line);
                saveAllNotReg(line);
                p_f_o_name_r=true;
            }
            if(col.at(getColNum("机主证件号码")).isEmpty()){
                savePersonFixedOwnerNumNotReg(line);
                saveAllNotReg(line);
                p_f_o_num_r=true;
            }
            if(col.at(getColNum("机主证件地址")).isEmpty()){
                savePersonFixedOwnerAddNotReg(line);
                saveAllNotReg(line);
                p_f_o_add_r=true;
            }
            if(p_f_o_name_r&&p_f_o_num_r){
                savePersonFixedOwnerNameNumNotReg(line);
            }
            if(p_f_o_name_r&&p_f_o_add_r){
                savePersonFixedOwnerNameAddNotReg(line);
            }
            if(p_f_o_num_r&&p_f_o_add_r){
                savePersonFixedOwnerNumAddNotReg(line);
            }
            if(p_f_o_name_r&&p_f_o_num_r&&p_f_o_add_r){
                savePersonFixedOwnerNameNumAddNotReg(line);
            }
            if(col.at(getColNum("代（经）办人姓名")).isEmpty()||col.at(getColNum("代（经）办人证件类型")).isEmpty()||
                    col.at(getColNum("代（经）办人证件号码")).isEmpty()||col.at(getColNum("代（经）办人证件地址")).isEmpty()||col.at(getColNum("代（经）办人通讯地址")).isEmpty()){
                savePeronMobileAgentNotReg(line);
                saveAllNotReg(line);
                p_f_o_agent_r=true;
            }
            bool p_f_o_t_n=false;//"个人固定用户-证件类型不合规
            bool p_f_o_name_n=false;//个人固定用户-用户姓名不合规
            bool p_f_o_num_n=false;//个人固定用户-证件号码不合规
            bool p_f_o_add_n=false;//个人固定用户-证件地址不合规
            bool p_f_o_agent_n=false;//个人固定用户-代办人不合规
            if(col.at(getColNum("代（经）办人姓名")).isEmpty()||col.at(getColNum("代（经）办人证件类型")).isEmpty()||
                        col.at(getColNum("代（经）办人证件号码")).isEmpty()||col.at(getColNum("代（经）办人证件地址")).isEmpty()||col.at(getColNum("代（经）办人通讯地址")).isEmpty()){
                    savePeronMobileAgentNok(line);
                    saveAllNok(line);
                    p_f_o_agent_n=true;
            }
            if(col.at(getColNum("机主证件类型")).isEmpty()){
                savePersonFixedOwnerTypeNok(line);
                p_f_o_t_n=true;
            }
            if(col.at(getColNum("机主用户姓名")).isEmpty()){
                savePersonFixedOwnerNameNok(line);
                p_f_o_name_n=true;
            }
            if(col.at(getColNum("机主证件号码")).isEmpty()){
                savePersonFixedOwnerNumNok(line);
                p_f_o_num_n=true;
            }
            if(col.at(getColNum("机主证件地址")).isEmpty()){
                savePersonFixedOwnerAddNok(line);
                p_f_o_add_n=true;
            }
            if(p_f_o_name_n&&p_f_o_num_n){
                savePersonFixedOwnerNameNumNok(line);
            }
            if(p_f_o_name_n&&p_f_o_add_n){
                savePersonFixedOwnerNameAddNok(line);
            }
            if(p_f_o_num_n&&p_f_o_add_n){
                savePersonFixedOwnerNumAddNok(line);
            }
            if(p_f_o_name_n&&p_f_o_num_n&&p_f_o_add_n){
                savePersonFixedOwnerNameNumAddNok(line);
            }
            if(col.at(getColNum("代（经）办人姓名")).isEmpty()||col.at(getColNum("代（经）办人证件类型")).isEmpty()||
                    col.at(getColNum("代（经）办人证件号码")).isEmpty()||col.at(getColNum("代（经）办人证件地址")).isEmpty()||col.at(getColNum("代（经）办人通讯地址")).isEmpty()){
                savePersonFixedAgentNotReg(line);
                saveAllNok(line);
                p_f_o_agent_r=true;
            }
            if(col.at(getColNum("代（经）办人姓名")).isEmpty()||col.at(getColNum("代（经）办人证件类型")).isEmpty()||
                    col.at(getColNum("代（经）办人证件号码")).isEmpty()||col.at(getColNum("代（经）办人证件地址")).isEmpty()||col.at(getColNum("代（经）办人通讯地址")).isEmpty()){
                savePersonFixedAgentNok(line);
                saveAllNok(line);
                p_f_o_agent_n=true;
            }
            if(!(p_f_o_t_r&&p_f_o_name_r&&p_f_o_num_r&&p_f_o_add_r&&p_f_o_t_n&&p_f_o_name_n&&p_f_o_num_n&&p_f_o_add_n&&p_f_o_agent_r&&p_f_o_agent_n)){
                savePersonFixedOk(line);
            }
        }
    }
    else if(col.at(getColNum("用户类型"))==userType.value("unit")){
        if(col.at(getColNum("用户业务类型"))=="移动"){
            bool u_m_o_r=false;//单位移动用户-使用人信息未登记
            bool u_m_a_r=false;//单位移动用户-代办人信息未登记
            bool u_m_u_r=false;//单位移动用户-单位信息未登记

            if(col.at(getColNum("机主用户姓名")).isEmpty()||col.at(getColNum("机主证件号码")).isEmpty()||col.at(getColNum("机主证件地址")).isEmpty()||col.at(getColNum("机主证件类型")).isEmpty()){
                saveUnitMobileOwnerNotReg(line);
                u_m_o_r=true;
            }
            if(col.at(getColNum("代（经）办人姓名")).isEmpty()||col.at(getColNum("代（经）办人证件类型")).isEmpty()||
                    col.at(getColNum("代（经）办人证件号码")).isEmpty()||col.at(getColNum("代（经）办人证件地址")).isEmpty()||col.at(getColNum("代（经）办人通讯地址")).isEmpty()){
                saveUnitMobileAgentNotReg(line);
                saveAllNotReg(line);
                u_m_a_r=true;
            }
            if(col.at(getColNum("单位名称")).isEmpty()||col.at(getColNum("单位证件号码")).isEmpty()||col.at(getColNum("单位证件类型")).isEmpty()||
                    col.at(getColNum("单位证件地址")).isEmpty()||col.at(getColNum("单位通讯地址")).isEmpty()||col.at(getColNum("单位装机地址")).isEmpty()){
                saveUnitMobileUnitNotReg(line);
                saveAllNotReg(line);
                u_m_u_r=true;
            }
            if(u_m_o_r||u_m_u_r){
                saveUnitMobileOwnerUnitNotReg(line);
                saveAllNotReg(line);
            }
            if(u_m_a_r||u_m_u_r){
                saveUnitMobileAgentUnitNotReg(line);
                saveAllNotReg(line);
            }
            if(u_m_o_r||u_m_a_r||u_m_u_r){
                saveUnitMobileOwnerAgentUnitNotReg(line);
                saveAllNotReg(line);
            }
            bool u_m_o_n=false;//单位移动用户-使用人信息不合规
            bool u_m_a_n=false;//单位移动用户-代办人信息不合规
            bool u_m_u_n=false;//单位移动用户-单位信息不合规

            if(col.at(getColNum("机主用户姓名")).isEmpty()||col.at(getColNum("机主证件号码")).isEmpty()||col.at(getColNum("机主证件地址")).isEmpty()||col.at(getColNum("机主证件类型")).isEmpty()){
                saveUnitMobileOwnerNok(line);
                u_m_o_n=true;
            }
            if(col.at(getColNum("代（经）办人姓名")).isEmpty()||col.at(getColNum("代（经）办人证件类型")).isEmpty()||
                    col.at(getColNum("代（经）办人证件号码")).isEmpty()||col.at(getColNum("代（经）办人证件地址")).isEmpty()||col.at(getColNum("代（经）办人通讯地址")).isEmpty()){
                saveUnitMobileAgentNok(line);
                saveAllNok(line);
                u_m_a_n=true;
            }
            if(col.at(getColNum("单位名称")).isEmpty()||col.at(getColNum("单位证件号码")).isEmpty()||col.at(getColNum("单位证件类型")).isEmpty()||
                    col.at(getColNum("单位证件地址")).isEmpty()||col.at(getColNum("单位通讯地址")).isEmpty()||col.at(getColNum("单位装机地址")).isEmpty()){
                saveUnitMobileUnitNok(line);
                saveAllNok(line);
                u_m_u_n=true;
            }
            if(u_m_o_n||u_m_a_n){
                saveUnitMobileOwnerAgentNok(line);
                saveAllNok(line);
            }
            if(u_m_o_n||u_m_u_n){
                saveUnitMobileOwnerUnitNok(line);
                saveAllNok(line);
            }
            if(u_m_a_n||u_m_u_n){
                saveUnitMobileAgentUnitNok(line);
                saveAllNok(line);
            }
            if(u_m_o_n||u_m_a_n||u_m_u_n){
                saveUnitMobileOwnerAgentUnitNok(line);
                saveAllNok(line);
            }
            if(!(u_m_o_r||u_m_a_r||u_m_u_r||u_m_o_n||u_m_a_n||u_m_u_n)){
                saveUnitMobileOk(line);
            }
        }
        else if(col.at(getColNum("用户业务类型"))=="固定"){
            bool u_f_a_r=false;//单位固话用户-代办人信息未登记
            bool u_f_u_r=false;//单位固话用户-单位信息未登记


            if(col.at(getColNum("代（经）办人姓名")).isEmpty()||col.at(getColNum("代（经）办人证件类型")).isEmpty()||
                    col.at(getColNum("代（经）办人证件号码")).isEmpty()||col.at(getColNum("代（经）办人证件地址")).isEmpty()||col.at(getColNum("代（经）办人通讯地址")).isEmpty()){
                saveUnitFixedAgentNotReg(line);
                saveAllNotReg(line);
                u_f_a_r=true;
            }
            if(col.at(getColNum("单位名称")).isEmpty()||col.at(getColNum("单位证件号码")).isEmpty()||col.at(getColNum("单位证件类型")).isEmpty()||
                    col.at(getColNum("单位证件地址")).isEmpty()||col.at(getColNum("单位通讯地址")).isEmpty()||col.at(getColNum("单位装机地址")).isEmpty()){
                saveUnitFixedUnitNotReg(line);
                saveAllNotReg(line);
                u_f_u_r=true;
            }
            if(u_f_a_r||u_f_u_r){
                saveUnitFixedAgentUnitNotReg(line);
                saveAllNotReg(line);
            }
            bool u_f_a_n=false;//单位移动用户-代办人信息不合规
            bool u_f_u_n=false;//单位移动用户-单位信息不合规
            if(col.at(getColNum("代（经）办人姓名")).isEmpty()||col.at(getColNum("代（经）办人证件类型")).isEmpty()||
                    col.at(getColNum("代（经）办人证件号码")).isEmpty()||col.at(getColNum("代（经）办人证件地址")).isEmpty()||col.at(getColNum("代（经）办人通讯地址")).isEmpty()){
                saveUnitFixedAgentNok(line);
                saveAllNok(line);
                u_f_a_n=true;
            }
            if(col.at(getColNum("单位名称")).isEmpty()||col.at(getColNum("单位证件号码")).isEmpty()||col.at(getColNum("单位证件类型")).isEmpty()||
                    col.at(getColNum("单位证件地址")).isEmpty()||col.at(getColNum("单位通讯地址")).isEmpty()||col.at(getColNum("单位装机地址")).isEmpty()){
                saveUnitFixedUnitNok(line);
                saveAllNok(line);
                u_f_u_n=true;
            }
            if(u_f_a_n||u_f_u_n){
                saveUnitMobileAgentUnitNok(line);
                saveAllNok(line);
            }
            if(!(u_f_a_r||u_f_u_r||u_f_a_n||u_f_u_n)){
                saveUnitFixedOk(line);
            }
        }
    }
    else if(col.at(getColNum("用户类型"))==userType.value("industry")){
        if(col.at(getColNum("用户业务类型"))=="移动"){
            bool t_m_a_r=false;//"行业移动用户-代办人未登记
            bool t_m_u_r=false;//行业移动用户-单位信息未登记
            bool t_m_l_r=false;//行业移动用户-责任人信息未登记
            if(col.at(getColNum("代（经）办人姓名")).isEmpty()||col.at(getColNum("代（经）办人证件类型")).isEmpty()||
                    col.at(getColNum("代（经）办人证件号码")).isEmpty()||col.at(getColNum("代（经）办人证件地址")).isEmpty()||col.at(getColNum("代（经）办人通讯地址")).isEmpty()){
                saveTradeMobileAgentNotReg(line);
                saveAllNotReg(line);
                t_m_a_r=true;
            }
            if(col.at(getColNum("单位名称")).isEmpty()||col.at(getColNum("单位证件号码")).isEmpty()||col.at(getColNum("单位证件类型")).isEmpty()||
                    col.at(getColNum("单位证件地址")).isEmpty()||col.at(getColNum("单位通讯地址")).isEmpty()||col.at(getColNum("单位装机地址")).isEmpty()){
                saveTradeMobileUnitNotReg(line);
                saveAllNotReg(line);
                t_m_u_r=true;
            }
            if(col.at(getColNum("责任人姓名")).isEmpty()||col.at(getColNum("责任人证件类型")).isEmpty()||col.at(getColNum("责任人证件号码")).isEmpty()||
                    col.at(getColNum("责任人证件地址")).isEmpty()||col.at(getColNum("责任人通讯地址")).isEmpty()){
                saveTradeMobileLiableNotReg(line);
                saveAllNotReg(line);
                t_m_l_r=true;
            }
            if(t_m_a_r&&t_m_u_r){
                saveTradeMobileAgentUnitNotReg(line);
                saveAllNotReg(line);
            }
            if(t_m_a_r&&t_m_l_r){
                saveTradeMobileLiableAgentNotReg(line);
                saveAllNotReg(line);
            }
            if(t_m_l_r&&t_m_u_r){
                saveTradeMobileLiableUnitNotReg(line);
                saveAllNotReg(line);
            }
            if(t_m_l_r&&t_m_a_r&&t_m_u_r){
                saveTradeMobileLiableAgentUnitNotReg(line);
                saveAllNotReg(line);
            }
            bool t_m_a_n=false;//"行业移动用户-代办人未登记
            bool t_m_u_n=false;//行业移动用户-单位信息未登记
            bool t_m_l_n=false;//行业移动用户-责任人信息未登记
            if(col.at(getColNum("代（经）办人姓名")).isEmpty()||col.at(getColNum("代（经）办人证件类型")).isEmpty()||
                    col.at(getColNum("代（经）办人证件号码")).isEmpty()||col.at(getColNum("代（经）办人证件地址")).isEmpty()||col.at(getColNum("代（经）办人通讯地址")).isEmpty()){
                saveTradeMobileAgentNok(line);
                saveAllNotReg(line);
                t_m_a_n=true;
            }
            if(col.at(getColNum("单位名称")).isEmpty()||col.at(getColNum("单位证件号码")).isEmpty()||col.at(getColNum("单位证件类型")).isEmpty()||
                    col.at(getColNum("单位证件地址")).isEmpty()||col.at(getColNum("单位通讯地址")).isEmpty()||col.at(getColNum("单位装机地址")).isEmpty()){
                saveTradeMobileUnitNok(line);
                saveAllNotReg(line);
                t_m_u_n=true;
            }
            if(col.at(getColNum("责任人姓名")).isEmpty()||col.at(getColNum("责任人证件类型")).isEmpty()||col.at(getColNum("责任人证件号码")).isEmpty()||
                    col.at(getColNum("责任人证件地址")).isEmpty()||col.at(getColNum("责任人通讯地址")).isEmpty()){
                saveTradeMobileLiableNok(line);
                saveAllNotReg(line);
                t_m_l_n=true;
            }
            if(t_m_a_n&&t_m_u_n){
                saveTradeMobileAgentUnitNok(line);
                saveAllNotReg(line);
            }
            if(t_m_l_n&&t_m_a_n){
                saveTradeMobileLiableAgentNok(line);
                saveAllNotReg(line);
            }
            if(t_m_l_n&&t_m_u_n){
                saveTradeMobileLiableUnitNok(line);
                saveAllNotReg(line);
            }
            if(t_m_l_n&&t_m_a_n&&t_m_u_n){
                saveTradeMobileLiableAgentUnitNok(line);
                saveAllNotReg(line);
            }
            if(!(t_m_l_r&&t_m_a_r&&t_m_u_r&&t_m_l_n&&t_m_a_n&&t_m_u_n)){
                saveTradeMobileOk(line);
            }
        }
        else if(col.at(getColNum("用户业务类型"))=="固定"){
            bool t_f_a_r=false;//"行业移动用户-代办人未登记
            bool t_f_u_r=false;//行业移动用户-单位信息未登记
            bool t_f_l_r=false;//行业移动用户-责任人信息未登记
            if(col.at(getColNum("代（经）办人姓名")).isEmpty()||col.at(getColNum("代（经）办人证件类型")).isEmpty()||
                    col.at(getColNum("代（经）办人证件号码")).isEmpty()||col.at(getColNum("代（经）办人证件地址")).isEmpty()||col.at(getColNum("代（经）办人通讯地址")).isEmpty()){
                saveTradeMobileAgentNotReg(line);
                saveAllNotReg(line);
                t_f_a_r=true;
            }
            if(col.at(getColNum("单位名称")).isEmpty()||col.at(getColNum("单位证件号码")).isEmpty()||col.at(getColNum("单位证件类型")).isEmpty()||
                    col.at(getColNum("单位证件地址")).isEmpty()||col.at(getColNum("单位通讯地址")).isEmpty()||col.at(getColNum("单位装机地址")).isEmpty()){
                saveTradeMobileUnitNotReg(line);
                saveAllNotReg(line);
                t_f_u_r=true;
            }
            if(col.at(getColNum("责任人姓名")).isEmpty()||col.at(getColNum("责任人证件类型")).isEmpty()||col.at(getColNum("责任人证件号码")).isEmpty()||
                    col.at(getColNum("责任人证件地址")).isEmpty()||col.at(getColNum("责任人通讯地址")).isEmpty()){
                saveTradeMobileLiableNotReg(line);
                saveAllNotReg(line);
                t_f_l_r=true;
            }
            if(t_f_a_r&&t_f_u_r){
                saveTradeFixedAgentUnitNotReg(line);
                saveAllNotReg(line);
            }
            if(t_f_a_r&&t_f_l_r){
                saveTradeMobileLiableAgentNotReg(line);
                saveAllNotReg(line);
            }
            if(t_f_l_r&&t_f_u_r){
                saveTradeMobileLiableUnitNotReg(line);
                saveAllNotReg(line);
            }
            if(t_f_l_r&&t_f_a_r&&t_f_u_r){
                saveTradeMobileLiableAgentUnitNotReg(line);
                saveAllNotReg(line);
            }
            bool t_f_a_n=false;//"行业移动用户-代办人未登记
            bool t_f_u_n=false;//行业移动用户-单位信息未登记
            if(col.at(getColNum("代（经）办人姓名")).isEmpty()||col.at(getColNum("代（经）办人证件类型")).isEmpty()||
                    col.at(getColNum("代（经）办人证件号码")).isEmpty()||col.at(getColNum("代（经）办人证件地址")).isEmpty()||col.at(getColNum("代（经）办人通讯地址")).isEmpty()){
                saveTradeFixedAgentNok(line);
                saveAllNotReg(line);
                t_f_a_n=true;
            }
            if(col.at(getColNum("单位名称")).isEmpty()||col.at(getColNum("单位证件号码")).isEmpty()||col.at(getColNum("单位证件类型")).isEmpty()||
                    col.at(getColNum("单位证件地址")).isEmpty()||col.at(getColNum("单位通讯地址")).isEmpty()||col.at(getColNum("单位装机地址")).isEmpty()){
                saveTradeFixedUnitNotReg(line);
                saveTradeFixedUnitNok(line);
                t_f_u_n=true;
            }
            if(t_f_a_n&&t_f_u_n){
                saveTradeFixedAgentUnitNok(line);
                saveAllNotReg(line);
            }

            if(!(t_f_l_r&&t_f_a_r&&t_f_u_r&&t_f_a_n&&t_f_u_n)){
                saveTradeFixedOk(line);
            }
        }
    }
//
//    saveAllNotReg(line);
//    saveAllNok(line);
//    saveFieldAbnormal(line);
//    saveAllOk(line);
//    saveWaitData(line);

//    (line);

//    saveOneCard(line);
}

void UserDb::saveAllNotReg(QString line){
    qDebug()<<"全量未登记.nreg"<<line;
}
void UserDb::saveAllNok(QString line){
    qDebug()<<"全量形式不合规.nck"<<line;
}
void UserDb::saveAbnormal(QString line){
    writeFile("格式异常数据.abnormal",line);
    qDebug()<<"格式异常数据.abnormal（不是42列的）"<<line;
}
void UserDb::saveFieldAbnormal(QString line){
    qDebug()<<"字段异常数据.abnormal（例如时间格式等不合规）"<<line;
}
void UserDb::saveAllOk(QString line){
    qDebug()<<"all.ok(全部合规数据)"<<line;
}
void UserDb::saveWaitData(QString line){
    qDebug()<<"待挖掘记录(-\" + head_loop_num + \".txt)"<<line;
}
void UserDb::savePersonMobileOk(QString line){
    qDebug()<<"个人移动用户-形式合规数据.ok"<<line;
}
void UserDb::savePersonMobileOwnerTypeNotReg(QString line){
    qDebug()<<"个人移动用户-证件类型未登记.nreg"<<line;
}
void UserDb::savePersonMobileOwnerNameNotReg(QString line){
    report->personMobileOwnerNameNotReg += 1;
    writeFile("个人移动用户-用户姓名未登记.nreg",line);
//    if(line.at(getColName("机主姓名")))
    qDebug()<<"个人移动用户-用户姓名未登记.nreg"<< report->personMobileOwnerNameNotReg;
}
void UserDb::savePersonMobileOwnerNumNotReg(QString line){
    qDebug()<<"个人移动用户-证件号码未登记.nreg"<<line;
}
void UserDb::savePersonMobileOwnerAddNotReg(QString line){
    qDebug()<<"个人移动用户-证件地址未登记.nreg"<<line;
}
void UserDb::savePersonMobileOwnerNameNumNotReg(QString line){
    qDebug()<<"个人移动用户-用户姓名&证件号码未登记.nreg"<<line;
}
void UserDb::savePersonMobileOwnerNameAddNotReg(QString line){
    qDebug()<<"个人移动用户-用户姓名&证件地址未登记.nreg"<<line;
}
void UserDb::savePersonMobileOwnerNumAddNotReg(QString line){
    qDebug()<<"个人移动用户-证件号码&证件地址未登记.nreg"<<line;
}
void UserDb::savePersonMobileOwnerNameNumAddNotReg(QString line){
    qDebug()<<"个人移动用户-用户姓名&证件号码&证件地址未登记.nreg"<<line;
}
void UserDb::savePeronMobileOwnerTyteNok(QString line){
    qDebug()<<"个人移动用户-证件类型校验不合规.nck"<<line;
}
void UserDb::savePeronMobileOwnerNameNok(QString line){
    qDebug()<<"个人移动用户-用户姓名校验不合规.nck"<<line;
}
void UserDb::savePeronMobileOwnerNumNok(QString line){
    qDebug()<<"个人移动用户-证件号码校验不合规.nck"<<line;
}
void UserDb::savePeronMobileOwnerAddNok(QString line){
    qDebug()<<"个人移动用户-证件地址校验不合规.nck"<<line;
}
void UserDb::savePeronMobileOwnerNameNumNok(QString line){
    qDebug()<<"个人移动用户-用户姓名&证件号码校验不合规.nck"<<line;
}
void UserDb::savePeronMobileOwnerNameAddNok(QString line){
    qDebug()<<"个人移动用户-用户姓名&证件地址校验不合规.nck"<<line;
}
void UserDb::savePeronMobileOwnerNumAddNok(QString line){
    qDebug()<<"个人移动用户-证件号码&证件地址校验不合规.nck"<<line;
}
void UserDb::savePeronMobileOwnerNameNumAddNok(QString line){
    qDebug()<<"个人移动用户-用户姓名&证件号码&证件地址校验不合规.nck"<<line;
}
// 个人-固定电话
void UserDb::savePersonFixedOk(QString line){
    qDebug()<<"个人固话用户-形式合规数据.ok"<<line;
}
void UserDb::savePersonFixedOwnerTypeNotReg(QString line){
    qDebug()<<"个人固话用户-证件类型未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerNameNotReg(QString line){
    qDebug()<<"个人固话用户-用户姓名未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerNumNotReg(QString line){
    qDebug()<<"个人固话用户-证件号码未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerAddNotReg(QString line){
    qDebug()<<"个人固话用户-证件地址未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerNameNumNotReg(QString line){
    qDebug()<<"个人固话用户-用户姓名&证件号码未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerNameAddNotReg(QString line){
    qDebug()<<"个人固话用户-用户姓名&证件地址未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerNumAddNotReg(QString line){
    qDebug()<<"个人固话用户-证件号码&证件地址未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerNameNumAddNotReg(QString line){
    qDebug()<<"个人固话用户-用户姓名&证件号码&证件地址未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerTypeNok(QString line){
    qDebug()<<"个人固话用户-证件类型校验不合规.nck"<<line;
}
void UserDb::savePersonFixedOwnerNameNok(QString line){
    qDebug()<<"个人固话用户-用户姓名校验不合规.nck"<<line;
}
void UserDb::savePersonFixedOwnerNumNok(QString line){
    qDebug()<<"个人固话用户-证件号码校验不合规.nck"<<line;
}
void UserDb::savePersonFixedOwnerAddNok(QString line){
    qDebug()<<"个人固话用户-证件地址校验不合规.nck"<<line;
}
void UserDb::savePersonFixedOwnerNameNumNok(QString line){
    qDebug()<<"个人固话用户-用户姓名&证件号码校验不合规.nck"<<line;
}
void UserDb::savePersonFixedOwnerNameAddNok(QString line){
    qDebug()<<"个人固话用户-用户姓名&证件地址校验不合规.nck"<<line;
}
void UserDb::savePersonFixedOwnerNumAddNok(QString line){
    qDebug()<<"个人固话用户-证件号码&证件地址校验不合规.nck"<<line;
}
void UserDb::savePersonFixedOwnerNameNumAddNok(QString line){
    qDebug()<<"个人固话用户-用户姓名&证件号码&证件地址校验不合规.nck"<<line;
}
void UserDb::savePeronMobileAgentNotReg(QString line){
    qDebug()<<"个人移动用户-代办人信息未登记.nreg"<<line;
}
void UserDb::savePersonFixedAgentNotReg(QString line){
    qDebug()<<"个人固话用户-代办人信息未登记.nreg"<<line;
}
void UserDb::savePeronMobileAgentNok(QString line){
    qDebug()<<"个人移动用户-代办人信息校验不合规.nck"<<line;
}
void UserDb::savePersonFixedAgentNok(QString line){
    qDebug()<<"个人固话用户-代办人信息校验不合规.nck"<<line;
}
void UserDb::saveUnitMobileOk(QString line){
    qDebug()<<"单位移动用户-形式合规数据.ok"<<line;
}
void UserDb::saveUnitMobileOwnerNotReg(QString line){
    qDebug()<<"单位移动用户-使用人信息未登记.nreg"<<line;
}
void UserDb::saveUnitMobileAgentNotReg(QString line){
    qDebug()<<"单位移动用户-经办人信息未登记.nreg"<<line;
}
void UserDb::saveUnitMobileUnitNotReg(QString line){
    qDebug()<<"单位移动用户-单位信息未登记.nreg"<<line;
}
void UserDb::saveUnitMobileOwnerUnitNotReg(QString line){
    qDebug()<<"单位移动用户-使用人&单位信息未登记.nreg"<<line;
}
void UserDb::saveUnitMobileAgentUnitNotReg(QString line){
    qDebug()<<"单位移动用户-经办人&单位信息未登记.nreg"<<line;
}
void UserDb::saveUnitMobileOwnerAgentUnitNotReg(QString line){
    qDebug()<<"单位移动用户-使用人&经办人&单位信息未登记.nreg"<<line;
}
void UserDb::saveUnitMobileOwnerNok(QString line){
    qDebug()<<"单位移动用户-使用人信息校验不合规.nck"<<line;
}
void UserDb::saveUnitMobileAgentNok(QString line){
    qDebug()<<"单位移动用户-经办人信息校验不合规.nck"<<line;
}
void UserDb::saveUnitMobileUnitNok(QString line){
    qDebug()<<"单位移动用户-单位信息校验不合规.nck"<<line;
}
void UserDb::saveUnitMobileOwnerAgentNok(QString line){
    qDebug()<<"单位移动用户-使用人&经办人信息校验不合规.nck"<<line;
}
void UserDb::saveUnitMobileOwnerUnitNok(QString line){
    qDebug()<<"单位移动用户-使用人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveUnitMobileAgentUnitNok(QString line){
    qDebug()<<"单位移动用户-经办人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveUnitMobileOwnerAgentUnitNok(QString line){
    qDebug()<<"单位移动用户-使用人&经办人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveUnitFixedOk(QString line){
    qDebug()<<"单位固话用户-形式合规数据.ok"<<line;
}
void UserDb::saveUnitFixedOwnerNotReg(QString line){
        qDebug()<<"单位固话用户-形式合规数据.ok"<<line;
}
void UserDb::saveUnitFixedAgentNotReg(QString line){
    qDebug()<<"单位固话用户-经办人信息未登记"<<line;
}
void UserDb::saveUnitFixedUnitNotReg(QString line){
    qDebug()<<"单位固话用户-单位信息未登记"<<line;
}
void UserDb::saveUnitFixedOwnerAgentNotReg(QString line){
    qDebug()<<"单位固话用户-使用人&经办人信息未登记"<<line;
}
void UserDb::saveUnitFixedOwnerUnitNotReg(QString line){
    qDebug()<<"单位固话用户-使用人&单位信息未登记"<<line;
}
void UserDb::saveUnitFixedAgentUnitNotReg(QString line){
    qDebug()<<"单位固话用户-经办人&单位信息未登记"<<line;
}
void UserDb::saveUnitFixedOwnerAgentUnitNotReg(QString line){
    qDebug()<<"单位固话用户-使用人&经办人&单位信息未登记"<<line;
}
void UserDb::saveUnitFixedAgentNok(QString line){
    qDebug()<<"单位固话用户-经办人信息校验不合规.nck"<<line;
}
void UserDb::saveUnitFixedUnitNok(QString line){
    qDebug()<<"单位固话用户-单位信息校验不合规.nck"<<line;
}
void UserDb::saveUnitFixedAgentUnitNok(QString line){
    qDebug()<<"单位固话用户-经办人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveTradeMobileOk(QString line){
    qDebug()<<"行业移动应用-形式合规数据.ok"<<line;
}
void UserDb::saveTradeMobileAgentNotReg(QString line){
    qDebug()<<"行业移动应用-经办人信息未登记"<<line;
}
void UserDb::saveTradeMobileAgentUnitNotReg(QString line){
    qDebug()<<"行业移动应用-经办人&单位信息未登记"<<line;
}
void UserDb::saveTradeMobileLiableAgentNotReg(QString line){
    qDebug()<<"行业移动应用-责任人&经办人信息未登记"<<line;
}
void UserDb::saveTradeMobileLiableAgentUnitNotReg(QString line){
    qDebug()<<"行业移动应用-责任人&经办人&单位信息未登记"<<line;
}
void UserDb::saveTradeMobileUnitNotReg(QString line){
    qDebug()<<"行业移动应用-单位信息未登记"<<line;
}
void UserDb::saveTradeMobileLiableNotReg(QString line){
    qDebug()<<"行业移动应用-责任人信息未登记"<<line;
}
void UserDb::saveTradeMobileLiableUnitNotReg(QString line){
    qDebug()<<"行业移动应用-责任人&单位信息未登记"<<line;
}
void UserDb::saveTradeMobileAgentNok(QString line){
    qDebug()<<"行业移动应用-经办人信息校验不合规.nck"<<line;
}
void UserDb::saveTradeMobileAgentUnitNok(QString line){
    qDebug()<<"行业移动应用-经办人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveTradeMobileLiableAgentNok(QString line){
    qDebug()<<"行业移动应用-责任人&经办人信息校验不合规.nck"<<line;
}
void UserDb::saveTradeMobileLiableAgentUnitNok(QString line){
    qDebug()<<"行业移动应用-责任人&经办人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveTradeMobileUnitNok(QString line){
    qDebug()<<"行业移动应用-单位信息校验不合规.nck"<<line;
}
void UserDb::saveTradeMobileLiableNok(QString line){
    qDebug()<<"行业移动应用-责任人信息校验不合规.nck"<<line;
}
void UserDb::saveTradeMobileLiableUnitNok(QString line){
    qDebug()<<"行业移动应用-责任人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveTradeFixedOk(QString line){
    qDebug()<<"行业固话应用-形式合规数据.ok"<<line;
}
void UserDb::saveTradeFixedAgentNotReg(QString line){
    qDebug()<<"行业固话应用-经办人信息未登记.nreg"<<line;
}
void UserDb::saveTradeFixedAgentUnitNotReg(QString line){
    qDebug()<<"行业固话应用-经办人&单位信息未登记.nreg"<<line;
}
void UserDb::saveTradeFixedUnitNotReg(QString line){
    qDebug()<<"行业固话应用-单位信息未登记.nreg"<<line;
}
void UserDb::saveTradeFixedAgentNok(QString line){
    qDebug()<<"行业固话应用-经办人信息校验不合规.nck"<<line;
}
void UserDb::saveTradeFixedAgentUnitNok(QString line){
    qDebug()<<"行业固话应用-经办人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveTradeFixedUnitNok(QString line){
    qDebug()<<"行业固话应用-单位信息校验不合规.nck"<<line;
}
void UserDb::saveOneCard(QString line){
    qDebug()<<"个人移动一证五卡不合规.nck"<<line;
}

void UserDb::writeFile(QString filename, QString line){
    QString path = xmlConfig->readWorkingpathValue().value("workingpath");
    qDebug()<<"writeFile "<<path<<filename;
    QFile file(path+filename);
    file.open(QFile::Append);
    line += "\n";
    file.write(line.toLocal8Bit());
    file.close();
}
