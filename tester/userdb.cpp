﻿#include "userdb.h"

UserDb::UserDb()
{
     stopped = false;
     QList<QList<QString>> lls = xmlConfig->readAutoid();
     QString name;
     report = new Report();
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
    qDebug()<<"run begin"<<stopped;
     emit message("run begin");
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
        qDebug()<<"update allData is:"<<query.exec("update report set allData=(select count(*) from file)");
//    printData("file");

//    //全量未登记
//        qDebug()<<"update allNotReg is:"<<query.exec("update report set allNotReg=(select count(*) from file)");
//    //格式异常数据
//         qDebug()<<"update formatNotRight is:"<<query.exec("update report set formatNotRight=(select count(*) from file)");
//    //字段异常数据
//         qDebug()<<"update fieldNotRight is:"<<query.exec("update report set fieldNotRight=(select count(*) from file)");
//    //all.ok
//         qDebug()<<"update allOk is:"<<query.exec("update report set allOk=(select count(*) from file)");

//    //待挖掘记录
// //         qDebug()<<"update allData is:"<<query.exec("update report set allData=(select count(*) from file)");

//    //个人移动用户-形式合规数据
//         //qDebug()<<"update personMobileFormatRight is:"<<query.exec("update report set personMobileFormatRight=(select count(*) from file where col"+UserFile::getCol_num("用户类型")+"='')");

//    //个人移动用户-证件类型未登记
         sql = "update report set personMobileOwnerTypeNotReg=(select count(*) from file where "
                 + getCol("机主证件类型")+ " is null and "
                 + getCol("用户类型")+"='个人客户' and "
                 + getCol("用户业务类型")+"='移动手机号码')";
         qDebug()<<"update personMobileOwnerTypeNotReg is:"<<query.exec(sql)<<sql;

//    //个人移动用户-用户姓名未登记
         sql = "update report set personMobileOwnerNameNotReg=(select count(*) from file where "
                 + getCol("用户姓名")+ " is null and "
                 + getCol("用户类型")+"='个人客户' and "
                 + getCol("用户业务类型")+"='移动手机号码')";
         qDebug()<<"update personMobileOwnerTypeNotReg is:"<<query.exec(sql)<<sql;

//    //个人移动用户-证件号码未登记
         sql = "update report set personMobileOwnerNumNotReg=(select count(*) from file where "
                 + getCol("证件号码")+ " is null and "
                 + getCol("用户类型")+"='个人客户' and "
                 + getCol("用户业务类型")+"='移动手机号码')";
         qDebug()<<"update personMobileOwnerTypeNotReg is:"<<query.exec(sql)<<sql;

//    //个人移动用户-证件地址未登记
         sql = "update report set personMobileOwnerAddNotReg=(select count(*) from file where "
                 + getCol("证件地址")+ " is null and "
                 + getCol("用户类型")+"='个人客户' and "
                 + getCol("用户业务类型")+"='移动手机号码')";
         qDebug()<<"update personMobileOwnerTypeNotReg is:"<<query.exec(sql)<<sql;

//    //个人移动用户-用户姓名&amp;证件号码未登记
         sql = "update report set personMobileOwnerNameNumNotReg=(select count(*) from file where "
                 + getCol("证件地址")+ " is null and "
                 + getCol("用户类型")+"='个人客户' and "
                 + getCol("用户业务类型")+"='移动手机号码')";
         qDebug()<<"update personMobileOwnerTypeNotReg is:"<<query.exec(sql)<<sql;

//    //个人移动用户-用户姓名&amp;证件地址未登记
//         qDebug()<<"update personMobileOwnerNameAddNotReg is:"<<query.exec("update report set personMobileOwnerNameAddNotReg=(select count(*) from file)");

//    //个人移动用户-证件号码&amp;证件地址未登记
//         qDebug()<<"update personMobileOwnerNumAddNotReg is:"<<query.exec("update report set personMobileOwnerNumAddNotReg=(select count(*) from file)");

//    //个人移动用户-用户姓名&amp;证件号码&amp;证件地址未登记
//         qDebug()<<"update personMobileOwnerNameNumAddNotReg is:"<<query.exec("update report set personMobileOwnerNameNumAddNotReg=(select count(*) from file)");

//    //个人移动用户-证件类型校验不合规
//         qDebug()<<"update personMobileOwnerTypeIllegal is:"<<query.exec("update report set personMobileOwnerTypeIllegal=(select count(*) from file)");

//    //个人移动用户-用户姓名校验不合规
//         qDebug()<<"update personMobileOwnerNameIllegal is:"<<query.exec("update report set personMobileOwnerNameIllegal=(select count(*) from file)");

//    //个人移动用户-证件号码校验不合规
//         qDebug()<<"update personMobileOwnerNumIllegal is:"<<query.exec("update report set personMobileOwnerNumIllegal=(select count(*) from file)");

//    //个人移动用户-证件地址校验不合规
//         qDebug()<<"update personMobileOwnerAddIllegal is:"<<query.exec("update report set personMobileOwnerAddIllegal=(select count(*) from file)");

//    //个人移动用户-用户姓名&amp;证件号码校验不合规
//         qDebug()<<"update personMobileOwnerNameNumIllegal is:"<<query.exec("update report set personMobileOwnerNameNumIllegal=(select count(*) from file)");

//    //个人移动用户-用户姓名&amp;证件地址校验不合规
//         qDebug()<<"update personMobileOwnerNameAddIllegal is:"<<query.exec("update report set personMobileOwnerNameAddIllegal=(select count(*) from file)");

//    //个人移动用户-证件号码&amp;证件地址校验不合规
//         qDebug()<<"update personMobileOwnerNumAddIllegal is:"<<query.exec("update report set personMobileOwnerNumAddIllegal=(select count(*) from file)");

//    //个人移动用户-用户姓名&amp;证件号码&amp;证件地址校验不合规
//         qDebug()<<"update personMobileOwnerNameNumAddIllegal is:"<<query.exec("update report set personMobileOwnerNameNumAddIllegal=(select count(*) from file)");

//    //个人固话用户-形式合规数据
//         qDebug()<<"update personFixedLegal is:"<<query.exec("update report set personFixedLegal=(select count(*) from file)");

//    //个人固话用户-证件类型未登记
//         qDebug()<<"update personFixedOwnerTypeNotReg is:"<<query.exec("update report set personFixedOwnerTypeNotReg=(select count(*) from file)");

//    //个人固话用户-用户姓名未登记
//         qDebug()<<"update personFixedOwnerNameNotReg is:"<<query.exec("update report set personFixedOwnerNameNotReg=(select count(*) from file)");

//    //个人固话用户-证件号码未登记
//         qDebug()<<"update personFixedOwnerNumNotReg is:"<<query.exec("update report set personFixedOwnerNumNotReg=(select count(*) from file)");

//    //个人固话用户-证件地址未登记
//         qDebug()<<"update personFixedOwnerAddNotReg is:"<<query.exec("update report set personFixedOwnerAddNotReg=(select count(*) from file)");

//    //个人固话用户-用户姓名&amp;证件号码未登记
//         qDebug()<<"update personFixedOwnerNameNumNotReg is:"<<query.exec("update report set personFixedOwnerNameNumNotReg=(select count(*) from file)");

//    //个人固话用户-用户姓名&amp;证件地址未登记
//         qDebug()<<"update personFixedOwnerNameAddNotReg is:"<<query.exec("update report set personFixedOwnerNameAddNotReg=(select count(*) from file)");

//    //个人固话用户-证件号码&amp;证件地址未登记
//         qDebug()<<"update personFixedOwnerNumAddNotReg is:"<<query.exec("update report set personFixedOwnerNumAddNotReg=(select count(*) from file)");

//    //个人固话用户-用户姓名&amp;证件号码&amp;证件地址未登记
//         qDebug()<<"update personFixedOwnerNameNumAddNotReg is:"<<query.exec("update report set personFixedOwnerNameNumAddNotReg=(select count(*) from file)");

//    //个人固话用户-证件类型校验不合规
//         qDebug()<<"update personFixedOwnerTypeIllegal is:"<<query.exec("update report set personFixedOwnerTypeIllegal=(select count(*) from file)");

//    //个人固话用户-用户姓名校验不合规
//         qDebug()<<"update personFixedOwnerNameIllegal is:"<<query.exec("update report set personFixedOwnerNameIllegal=(select count(*) from file)");

//    //个人固话用户-证件号码校验不合规
//         qDebug()<<"update personFixedOwnerNumIllegal is:"<<query.exec("update report set personFixedOwnerNumIllegal=(select count(*) from file)");

//    //个人固话用户-证件地址校验不合规
//         qDebug()<<"update personFixedOwnerAddIllegal is:"<<query.exec("update report set personFixedOwnerAddIllegal=(select count(*) from file)");

//    //个人固话用户-用户姓名&amp;证件号码校验不合规
//         qDebug()<<"update personFixedOwnerNameNumIllegal is:"<<query.exec("update report set personFixedOwnerNameNumIllegal=(select count(*) from file)");

//    //个人固话用户-用户姓名&amp;证件地址校验不合规
//         qDebug()<<"update personFixedOwnerNameAddIllegal is:"<<query.exec("update report set personFixedOwnerNameAddIllegal=(select count(*) from file)");

//    //个人固话用户-证件号码&amp;证件地址校验不合规
//         qDebug()<<"update personFixedOwnerNumAddIllegal is:"<<query.exec("update report set personFixedOwnerNumAddIllegal=(select count(*) from file)");

//    //个人固话用户-用户姓名&amp;证件号码&amp;证件地址校验不合规
//         qDebug()<<"update personFixedOwnerNameNumAddIllegal is:"<<query.exec("update report set personFixedOwnerNameNumAddIllegal=(select count(*) from file)");

//    //个人移动用户-代办人信息未登记
//         qDebug()<<"update personMobileAgentNotReg is:"<<query.exec("update report set personMobileAgentNotReg=(select count(*) from file)");

//    //个人固话用户-代办人信息未登记
//         qDebug()<<"update personFixedAgentNotReg is:"<<query.exec("update report set personFixedAgentNotReg=(select count(*) from file)");

//    //个人移动用户-代办人信息校验不合规
//         qDebug()<<"update personMobileAgentIllegal is:"<<query.exec("update report set personMobileAgentIllegal=(select count(*) from file)");

//    //个人固话用户-代办人信息校验不合规
//         qDebug()<<"update personFixedAgentIllegal is:"<<query.exec("update report set personFixedAgentIllegal=(select count(*) from file)");

//    //单位移动用户-形式合规数据
//         qDebug()<<"update unitMobileLegal is:"<<query.exec("update report set unitMobileLegal=(select count(*) from file)");

//    //单位移动用户-使用人信息未登记
//         qDebug()<<"update unitMobileOwnerNotReg is:"<<query.exec("update report set unitMobileOwnerNotReg=(select count(*) from file)");

//    //单位移动用户-经办人信息未登记
//         qDebug()<<"update unitMobileAgentNotReg is:"<<query.exec("update report set unitMobileAgentNotReg=(select count(*) from file)");

//    //单位移动用户-单位信息未登记
//         qDebug()<<"update unitMobileUnitNotReg is:"<<query.exec("update report set unitMobileUnitNotReg=(select count(*) from file)");

//    //单位移动用户-使用人&amp;经办人信息未登记
//         qDebug()<<"update unitMobileOwnerAgentNotReg is:"<<query.exec("update report set unitMobileOwnerAgentNotReg=(select count(*) from file)");

//    //单位移动用户-使用人&amp;单位信息未登记
//         qDebug()<<"update unitMobileOwnerUnitNotReg is:"<<query.exec("update report set unitMobileOwnerUnitNotReg=(select count(*) from file)");

//    //单位移动用户-经办人&amp;单位信息未登记
//         qDebug()<<"update unitMobileAgentUnitNotReg is:"<<query.exec("update report set unitMobileAgentUnitNotReg=(select count(*) from file)");

//    //单位移动用户-使用人&amp;经办人&amp;单位信息未登记
//         qDebug()<<"update unitMobileOwnerAgentUnitNotReg is:"<<query.exec("update report set unitMobileOwnerAgentUnitNotReg=(select count(*) from file)");

//    //单位移动用户-使用人信息校验不合规
//         qDebug()<<"update unitMobileOwnerIllegal is:"<<query.exec("update report set unitMobileOwnerIllegal=(select count(*) from file)");

//    //单位移动用户-经办人信息校验不合规
//         qDebug()<<"update unitMobileAgentIllegal is:"<<query.exec("update report set unitMobileAgentIllegal=(select count(*) from file)");

//    //单位移动用户-单位信息校验不合规
//         qDebug()<<"update unitMobileUnitIllegal is:"<<query.exec("update report set unitMobileUnitIllegal=(select count(*) from file)");

//    //单位移动用户-使用人&amp;经办人信息校验不合规
//         qDebug()<<"update unitMobileOwnerAgentIllegal is:"<<query.exec("update report set unitMobileOwnerAgentIllegal=(select count(*) from file)");

//    //单位移动用户-经办人&amp;单位信息校验不合规
//         qDebug()<<"update unitMobileAgentUnitIllegal is:"<<query.exec("update report set unitMobileAgentUnitIllegal=(select count(*) from file)");

//    //单位移动用户-使用人&amp;经办人&amp;单位信息校验不合规
//         qDebug()<<"update unitMobileOwnerAgentUnitIllegal is:"<<query.exec("update report set unitMobileOwnerAgentUnitIllegal=(select count(*) from file)");

//    //单位固话用户-形式合规数据
//         qDebug()<<"update unitFixedLegal is:"<<query.exec("update report set unitFixedLegal=(select count(*) from file)");

//    //单位固话用户-经办人信息未登记
//         qDebug()<<"update unitFixedAgentNotReg is:"<<query.exec("update report set unitFixedAgentNotReg=(select count(*) from file)");

//    //单位固话用户-单位信息未登记
//         qDebug()<<"update unitFixedUnitNotReg is:"<<query.exec("update report set unitFixedUnitNotReg=(select count(*) from file)");

//    //单位固话用户-经办人&amp;单位信息未登记
//         qDebug()<<"update unitFixedAgentUnitNotReg is:"<<query.exec("update report set unitFixedAgentUnitNotReg=(select count(*) from file)");

//    //单位固话用户-经办人信息校验不合规
//         qDebug()<<"update unitFixedAgentIllegal is:"<<query.exec("update report set unitFixedAgentIllegal=(select count(*) from file)");

//    //单位固话用户-单位信息校验不合规
//         qDebug()<<"update unitFixedUnitIllegal is:"<<query.exec("update report set unitFixedUnitIllegal=(select count(*) from file)");

//    //单位固话用户-经办人&amp;单位信息校验不合规
//         qDebug()<<"update unitFixedAgentUnitIllegal is:"<<query.exec("update report set unitFixedAgentUnitIllegal=(select count(*) from file)");

//    //行业移动应用-形式合规数据
//         qDebug()<<"update tradeMobileLegal is:"<<query.exec("update report set tradeMobileLegal=(select count(*) from file)");

//    //行业移动应用-经办人信息未登记
//         qDebug()<<"update tradeMobileAgentNotReg is:"<<query.exec("update report set tradeMobileAgentNotReg=(select count(*) from file)");

//    //行业移动应用-经办人&amp;单位信息未登记
//         qDebug()<<"update tradeMobileAgentUnitNotReg is:"<<query.exec("update report set tradeMobileAgentUnitNotReg=(select count(*) from file)");

//    //行业移动应用-责任人&amp;经办人信息未登记
//         qDebug()<<"update tradeMobileLiableAgentNotReg is:"<<query.exec("update report set tradeMobileLiableAgentNotReg=(select count(*) from file)");

//    //行业移动应用-责任人&amp;经办人&amp;单位信息未登记
//         qDebug()<<"update tradeMobileLiableAgentUnitNotReg is:"<<query.exec("update report set tradeMobileLiableAgentUnitNotReg=(select count(*) from file)");

//    //行业移动应用-单位信息未登记
//         qDebug()<<"update tradeMobileUnitNotReg is:"<<query.exec("update report set tradeMobileUnitNotReg=(select count(*) from file)");

//    //行业移动应用-责任人信息未登记
//         qDebug()<<"update tradeMobileLiableNotReg is:"<<query.exec("update report set tradeMobileLiableNotReg=(select count(*) from file)");

//    //行业移动应用-责任人&amp;单位信息未登记
//         qDebug()<<"update tradeMobileLiableUnitNotReg is:"<<query.exec("update report set tradeMobileLiableUnitNotReg=(select count(*) from file)");

//    //行业移动应用-经办人信息校验不合规
//         qDebug()<<"update tradeMobileAgentIllegal is:"<<query.exec("update report set tradeMobileAgentIllegal=(select count(*) from file)");

//    //行业移动应用-经办人&amp;单位信息校验不合规
//         qDebug()<<"update tradeMobileAgentUnitIllegal is:"<<query.exec("update report set tradeMobileAgentUnitIllegal=(select count(*) from file)");

//    //行业移动应用-责任人&amp;经办人信息校验不合规
//         qDebug()<<"update tradeMobileLiableAgentIllegal is:"<<query.exec("update report set tradeMobileLiableAgentIllegal=(select count(*) from file)");

//    //行业移动应用-责任人&amp;经办人&amp;单位信息校验不合规
//         qDebug()<<"update tradeMobileLiableAgentUnitIllegal is:"<<query.exec("update report set tradeMobileLiableAgentUnitIllegal=(select count(*) from file)");

//    //行业移动应用-单位信息校验不合规
//         qDebug()<<"update tradeMobileUnitIllegal is:"<<query.exec("update report set tradeMobileUnitIllegal=(select count(*) from file)");

//    //行业移动应用-责任人信息校验不合规
//         qDebug()<<"update tradeMobileLiableIllegal is:"<<query.exec("update report set tradeMobileLiableIllegal=(select count(*) from file)");

//    //行业移动应用-责任人&amp;单位信息校验不合规
//         qDebug()<<"update tradeMobileLiableUnitIllegal is:"<<query.exec("update report set tradeMobileLiableUnitIllegal=(select count(*) from file)");

//    //行业固话应用-形式合规数据
//         qDebug()<<"update tradeFixedLegal is:"<<query.exec("update report set tradeFixedLegal=(select count(*) from file)");

//    //行业固话应用-经办人信息未登记
//         qDebug()<<"update tradeFixedAgentNotReg is:"<<query.exec("update report set tradeFixedAgentNotReg=(select count(*) from file)");

//    //行业固话应用-经办人&amp;单位信息未登记
//         qDebug()<<"update tradeFixedAgentUnitNotReg is:"<<query.exec("update report set tradeFixedAgentUnitNotReg=(select count(*) from file)");

//    //行业固话应用-单位信息未登记
//         qDebug()<<"update tradeFixedUnitNotReg is:"<<query.exec("update report set tradeFixedUnitNotReg=(select count(*) from file)");

//    //行业固话应用-经办人信息校验不合规
//         qDebug()<<"update tradeFixedAgentIllegal is:"<<query.exec("update report set tradeFixedAgentIllegal=(select count(*) from file)");

//    //行业固话应用-经办人&amp;单位信息校验不合规
//         qDebug()<<"update tradeFixedAgentUnitIllegal is:"<<query.exec("update report set tradeFixedAgentUnitIllegal=(select count(*) from file)");

//    //行业固话应用-单位信息校验不合规
//         qDebug()<<"update tradeFixedUnitIllegal is:"<<query.exec("update report set tradeFixedUnitIllegal=98");

//    //个人移动一证五卡不合规
//         qDebug()<<"update is:"<<query.exec("update report set personMobileOneCard=99");

}

QString UserDb::getCol(QString name){
    //    int rtn = ;
        qDebug()<<"查询的列名是"<<name<<"列号是"<<col_name_map.value(name)+1;
        return "col"+QString::number(col_name_map.value(name)+1);
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


QString getCol(QString str){
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
            col =  line.split(strItemDelimeter);
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

void UserDb::processLine(QList<QString> line){
    savePersonMobileOwnerNameNotReg(line);
    savePersonMobileOwnerTypeNotReg(line);
    savePersonMobileOwnerNumNotReg(line);
    savePersonMobileOwnerAddNotReg(line);
    savePersonMobileOwnerNameNumNotReg(line);
    savePersonMobileOwnerNameAddNotReg(line);
    savePersonMobileOwnerNumAddNotReg(line);
    savePersonMobileOwnerNameNumAddNotReg(line);
    savePeronMobileOwnerTyteNok(line);
    savePeronMobileOwnerNameNok(line);
    savePeronMobileOwnerNumNok(line);
    savePeronMobileOwnerAddNok(line);
    savePeronMobileOwnerNameNumNok(line);
    savePeronMobileOwnerNameAddNok(line);
    savePeronMobileOwnerNumAddNok(line);
    savePeronMobileOwnerNameNumAddNok(line);
    savePersonFixedOk(line);
    saveAllNotReg(line);
    saveAllNok(line);
    saveAbnormal(line);
    saveFieldAbnormal(line);
    saveAllOk(line);
    saveWaitData(line);
    savePersonMobileOk(line);
    savePersonFixedOwnerNameNotReg(line);
    savePersonFixedOwnerTypeNotReg(line);
    savePersonFixedOwnerNumNotReg(line);
    savePersonFixedOwnerAddNotReg(line);
    savePersonFixedOwnerNameNumNotReg(line);
    savePersonFixedOwnerNameAddNotReg(line);
    savePersonFixedOwnerNumAddNotReg(line);
    savePersonFixedOwnerNameNumAddNotReg(line);
    savePersonFixedOwnerTypeNok(line);
    savePersonFixedOwnerNameNok(line);
    savePersonFixedOwnerNumNok(line);
    savePersonFixedOwnerAddNok(line);
    savePersonFixedOwnerNameNumNok(line);
    savePersonFixedOwnerNameAddNok(line);
    savePersonFixedOwnerNumAddNok(line);
    savePersonFixedOwnerNameNumAddNok(line);
    savePeronMobileAgentNotReg(line);
    savePersonFixedAgentNotReg(line);
    savePeronMobileAgentNok(line);
    savePersonFixedAgentNok(line);
    saveUnitMobileOk(line);
    saveUnitMobileOwnerNotReg(line);
    saveUnitMobileOwnerAgentNotReg(line);
    saveUnitMobileUnitNotReg(line);
    saveUnitMobileOwnerUnitNotReg(line);
    saveUnitMobileAgentUnitNotReg(line);
    saveUnitMobileOwnerAgentUnitAddNotReg(line);
    saveUnitMobileOwnerNok(line);
    saveUnitMobileAgentNok(line);
    saveUnitMobileUnitNok(line);
    saveUnitMobileOwnerAgentNok(line);
    saveUnitMobileOwnerUnitNok(line);
    saveUnitMobileAgentUnitNok(line);
    saveUnitMobileOwnerAgentUnitNok(line);
    saveUnitFixedOk(line);
    saveUnitFixedOwnerNotReg(line);
    saveUnitFixedAgentNotReg(line);
    saveUnitFixedUnitNotReg(line);
    saveUnitFixedOwnerAgentNotReg(line);
    saveUnitFixedOwnerUnitNotReg(line);
    saveUnitFixedAgentUnitNotReg(line);
    saveUnitFixedOwnerAgentUnitAddNotReg(line);
    saveUnitFixedAgentNok(line);
    saveUnitFixedUnitNok(line);
    saveUnitFixedAgentUnitNok(line);
    saveTradeMobileOk(line);
    saveTradeMobileAgentNotReg(line);
    saveTradeMobileUnitNotReg(line);
    saveTradeMobileLiableNotReg(line);
    saveTradeMobileAgentUnitNotReg(line);
    saveTradeMobileLiableAgentNotReg(line);
    saveTradeMobileLiableUnitNotReg(line);
    saveTradeMobileLiableAgentUnitAddNotReg(line);
    saveTradeMobileAgentNok(line);
    saveTradeMobileAgentUnitNok(line);
    saveTradeMobileLiableAgentNok(line);
    saveTradeMobileLiableAgentUnitAddNok(line);
    saveTradeMobileUnitNok(line);
    saveTradeMobileLiableNok(line);
    saveTradeMobileLiableUnitNok(line);
    saveTradeFixedOk(line);
    saveTradeFixedAgentNotReg(line);
    saveTradeFixedUnitNotReg(line);
    saveTradeFixedAgentUnitNotReg(line);
    saveTradeFixedAgentNok(line);
    saveTradeFixedAgentUnitNok(line);
    saveTradeFixedUnitNok(line);
    saveOneCard(line);
}

void UserDb::saveAllNotReg(QList<QString> line){
    qDebug()<<"全量未登记.nreg"<<line;
}
void UserDb::saveAllNok(QList<QString> line){
    qDebug()<<"全量形式不合规.nck"<<line;
}
void UserDb::saveAbnormal(QList<QString> line){
    qDebug()<<"格式异常数据.abnormal（不是42列的）"<<line;
}
void UserDb::saveFieldAbnormal(QList<QString> line){
    qDebug()<<"字段异常数据.abnormal（例如时间格式等不合规）"<<line;
}
void UserDb::saveAllOk(QList<QString> line){
    qDebug()<<"all.ok(全部合规数据)"<<line;
}
void UserDb::saveWaitData(QList<QString> line){
    qDebug()<<"待挖掘记录(-\" + head_loop_num + \".txt)"<<line;
}
void UserDb::savePersonMobileOk(QList<QString> line){
    qDebug()<<"个人移动用户-形式合规数据.ok"<<line;
}
void UserDb::savePersonMobileOwnerTypeNotReg(QList<QString> line){
    qDebug()<<"个人移动用户-证件类型未登记.nreg"<<line;
}
void UserDb::savePersonMobileOwnerNameNotReg(QList<QString> line){
    qDebug()<<"个人移动用户-用户姓名未登记.nreg"<<line;
}
void UserDb::savePersonMobileOwnerNumNotReg(QList<QString> line){
    qDebug()<<"个人移动用户-证件号码未登记.nreg"<<line;
}
void UserDb::savePersonMobileOwnerAddNotReg(QList<QString> line){
    qDebug()<<"个人移动用户-证件地址未登记.nreg"<<line;
}
void UserDb::savePersonMobileOwnerNameNumNotReg(QList<QString> line){
    qDebug()<<"个人移动用户-用户姓名&证件号码未登记.nreg"<<line;
}
void UserDb::savePersonMobileOwnerNameAddNotReg(QList<QString> line){
    qDebug()<<"个人移动用户-用户姓名&证件地址未登记.nreg"<<line;
}
void UserDb::savePersonMobileOwnerNumAddNotReg(QList<QString> line){
    qDebug()<<"个人移动用户-证件号码&证件地址未登记.nreg"<<line;
}
void UserDb::savePersonMobileOwnerNameNumAddNotReg(QList<QString> line){
    qDebug()<<"个人移动用户-用户姓名&证件号码&证件地址未登记.nreg"<<line;
}
void UserDb::savePeronMobileOwnerTyteNok(QList<QString> line){
    qDebug()<<"个人移动用户-证件类型校验不合规.nck"<<line;
}
void UserDb::savePeronMobileOwnerNameNok(QList<QString> line){
    qDebug()<<"个人移动用户-用户姓名校验不合规.nck"<<line;
}
void UserDb::savePeronMobileOwnerNumNok(QList<QString> line){
    qDebug()<<"个人移动用户-证件号码校验不合规.nck"<<line;
}
void UserDb::savePeronMobileOwnerAddNok(QList<QString> line){
    qDebug()<<"个人移动用户-证件地址校验不合规.nck"<<line;
}
void UserDb::savePeronMobileOwnerNameNumNok(QList<QString> line){
    qDebug()<<"个人移动用户-用户姓名&证件号码校验不合规.nck"<<line;
}
void UserDb::savePeronMobileOwnerNameAddNok(QList<QString> line){
    qDebug()<<"个人移动用户-用户姓名&证件地址校验不合规.nck"<<line;
}
void UserDb::savePeronMobileOwnerNumAddNok(QList<QString> line){
    qDebug()<<"个人移动用户-证件号码&证件地址校验不合规.nck"<<line;
}
void UserDb::savePeronMobileOwnerNameNumAddNok(QList<QString> line){
    qDebug()<<"个人移动用户-用户姓名&证件号码&证件地址校验不合规.nck"<<line;
}
// 个人-固定电话
void UserDb::savePersonFixedOk(QList<QString> line){
    qDebug()<<"个人固话用户-形式合规数据.ok"<<line;
}
void UserDb::savePersonFixedOwnerTypeNotReg(QList<QString> line){
    qDebug()<<"个人固话用户-证件类型未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerNameNotReg(QList<QString> line){
    qDebug()<<"个人固话用户-用户姓名未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerNumNotReg(QList<QString> line){
    qDebug()<<"个人固话用户-证件号码未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerAddNotReg(QList<QString> line){
    qDebug()<<"个人固话用户-证件地址未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerNameNumNotReg(QList<QString> line){
    qDebug()<<"个人固话用户-用户姓名&证件号码未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerNameAddNotReg(QList<QString> line){
    qDebug()<<"个人固话用户-用户姓名&证件地址未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerNumAddNotReg(QList<QString> line){
    qDebug()<<"个人固话用户-证件号码&证件地址未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerNameNumAddNotReg(QList<QString> line){
    qDebug()<<"个人固话用户-用户姓名&证件号码&证件地址未登记.nreg"<<line;
}
void UserDb::savePersonFixedOwnerTypeNok(QList<QString> line){
    qDebug()<<"个人固话用户-证件类型校验不合规.nck"<<line;
}
void UserDb::savePersonFixedOwnerNameNok(QList<QString> line){
    qDebug()<<"个人固话用户-用户姓名校验不合规.nck"<<line;
}
void UserDb::savePersonFixedOwnerNumNok(QList<QString> line){
    qDebug()<<"个人固话用户-证件号码校验不合规.nck"<<line;
}
void UserDb::savePersonFixedOwnerAddNok(QList<QString> line){
    qDebug()<<"个人固话用户-证件地址校验不合规.nck"<<line;
}
void UserDb::savePersonFixedOwnerNameNumNok(QList<QString> line){
    qDebug()<<"个人固话用户-用户姓名&证件号码校验不合规.nck"<<line;
}
void UserDb::savePersonFixedOwnerNameAddNok(QList<QString> line){
    qDebug()<<"个人固话用户-用户姓名&证件地址校验不合规.nck"<<line;
}
void UserDb::savePersonFixedOwnerNumAddNok(QList<QString> line){
    qDebug()<<"个人固话用户-证件号码&证件地址校验不合规.nck"<<line;
}
void UserDb::savePersonFixedOwnerNameNumAddNok(QList<QString> line){
    qDebug()<<"个人固话用户-用户姓名&证件号码&证件地址校验不合规.nck"<<line;
}
void UserDb::savePeronMobileAgentNotReg(QList<QString> line){
    qDebug()<<"个人移动用户-代办人信息未登记.nreg"<<line;
}
void UserDb::savePersonFixedAgentNotReg(QList<QString> line){
    qDebug()<<"个人固话用户-代办人信息未登记.nreg"<<line;
}
void UserDb::savePeronMobileAgentNok(QList<QString> line){
    qDebug()<<"个人移动用户-代办人信息校验不合规.nck"<<line;
}
void UserDb::savePersonFixedAgentNok(QList<QString> line){
    qDebug()<<"个人固话用户-代办人信息校验不合规.nck"<<line;
}
void UserDb::saveUnitMobileOk(QList<QString> line){
    qDebug()<<"单位移动用户-形式合规数据.ok"<<line;
}
void UserDb::saveUnitMobileOwnerNotReg(QList<QString> line){
    qDebug()<<"单位移动用户-使用人信息未登记.nreg"<<line;
}
void UserDb::saveUnitMobileOwnerAgentNotReg(QList<QString> line){
    qDebug()<<"单位移动用户-经办人信息未登记.nreg"<<line;
}
void UserDb::saveUnitMobileUnitNotReg(QList<QString> line){
    qDebug()<<"单位移动用户-单位信息未登记.nreg"<<line;
}
void UserDb::saveUnitMobileOwnerUnitNotReg(QList<QString> line){
    qDebug()<<"单位移动用户-使用人&单位信息未登记.nreg"<<line;
}

void UserDb::saveUnitMobileAgentUnitNotReg(QList<QString> line){
    qDebug()<<"单位移动用户-经办人&单位信息未登记.nreg"<<line;
}

void UserDb::saveUnitMobileOwnerAgentUnitAddNotReg(QList<QString> line){
    qDebug()<<"单位移动用户-使用人&经办人&单位信息未登记.nreg"<<line;
}
void UserDb::saveUnitMobileOwnerNok(QList<QString> line){
    qDebug()<<"单位移动用户-使用人信息校验不合规.nck"<<line;
}
void UserDb::saveUnitMobileAgentNok(QList<QString> line){
    qDebug()<<"单位移动用户-经办人信息校验不合规.nck"<<line;
}
void UserDb::saveUnitMobileUnitNok(QList<QString> line){
    qDebug()<<"单位移动用户-单位信息校验不合规.nck"<<line;
}
void UserDb::saveUnitMobileOwnerAgentNok(QList<QString> line){
    qDebug()<<"单位移动用户-使用人&经办人信息校验不合规.nck"<<line;
}
void UserDb::saveUnitMobileOwnerUnitNok(QList<QString> line){
    qDebug()<<"单位移动用户-使用人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveUnitMobileAgentUnitNok(QList<QString> line){
    qDebug()<<"单位移动用户-经办人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveUnitMobileOwnerAgentUnitNok(QList<QString> line){
    qDebug()<<"单位移动用户-使用人&经办人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveUnitFixedOk(QList<QString> line){
    qDebug()<<"单位固话用户-形式合规数据.ok"<<line;
}
void UserDb::saveUnitFixedOwnerNotReg(QList<QString> line){
        qDebug()<<"单位固话用户-形式合规数据.ok"<<line;
}
void UserDb::saveUnitFixedAgentNotReg(QList<QString> line){
    qDebug()<<"单位固话用户-经办人信息未登记"<<line;
}
void UserDb::saveUnitFixedUnitNotReg(QList<QString> line){
    qDebug()<<"单位固话用户-单位信息未登记"<<line;
}
void UserDb::saveUnitFixedOwnerAgentNotReg(QList<QString> line){
    qDebug()<<"单位固话用户-使用人&经办人信息未登记"<<line;
}
void UserDb::saveUnitFixedOwnerUnitNotReg(QList<QString> line){
    qDebug()<<"单位固话用户-使用人&单位信息未登记"<<line;
}
void UserDb::saveUnitFixedAgentUnitNotReg(QList<QString> line){
    qDebug()<<"单位固话用户-经办人&单位信息未登记"<<line;
}
void UserDb::saveUnitFixedOwnerAgentUnitAddNotReg(QList<QString> line){
    qDebug()<<"单位固话用户-使用人&经办人&单位信息未登记"<<line;
}
void UserDb::saveUnitFixedAgentNok(QList<QString> line){
    qDebug()<<"单位固话用户-经办人信息校验不合规.nck"<<line;
}
void UserDb::saveUnitFixedUnitNok(QList<QString> line){
    qDebug()<<"单位固话用户-单位信息校验不合规.nck"<<line;
}
void UserDb::saveUnitFixedAgentUnitNok(QList<QString> line){
    qDebug()<<"单位固话用户-经办人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveTradeMobileOk(QList<QString> line){
    qDebug()<<"行业移动应用-形式合规数据.ok"<<line;
}
void UserDb::saveTradeMobileAgentNotReg(QList<QString> line){
    qDebug()<<"行业移动应用-经办人信息未登记"<<line;
}
void UserDb::saveTradeMobileAgentUnitNotReg(QList<QString> line){
    qDebug()<<"行业移动应用-经办人&单位信息未登记"<<line;
}
void UserDb::saveTradeMobileLiableAgentNotReg(QList<QString> line){
    qDebug()<<"行业移动应用-责任人&经办人信息未登记"<<line;
}
void UserDb::saveTradeMobileLiableAgentUnitAddNotReg(QList<QString> line){
    qDebug()<<"行业移动应用-责任人&经办人&单位信息未登记"<<line;
}
void UserDb::saveTradeMobileUnitNotReg(QList<QString> line){
    qDebug()<<"行业移动应用-单位信息未登记"<<line;
}
void UserDb::saveTradeMobileLiableNotReg(QList<QString> line){
    qDebug()<<"行业移动应用-责任人信息未登记"<<line;
}
void UserDb::saveTradeMobileLiableUnitNotReg(QList<QString> line){
    qDebug()<<"行业移动应用-责任人&单位信息未登记"<<line;
}
void UserDb::saveTradeMobileAgentNok(QList<QString> line){
    qDebug()<<"行业移动应用-经办人信息校验不合规.nck"<<line;
}
void UserDb::saveTradeMobileAgentUnitNok(QList<QString> line){
    qDebug()<<"行业移动应用-经办人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveTradeMobileLiableAgentNok(QList<QString> line){
    qDebug()<<"行业移动应用-责任人&经办人信息校验不合规.nck"<<line;
}
void UserDb::saveTradeMobileLiableAgentUnitAddNok(QList<QString> line){
    qDebug()<<"行业移动应用-责任人&经办人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveTradeMobileUnitNok(QList<QString> line){
    qDebug()<<"行业移动应用-单位信息校验不合规.nck"<<line;
}
void UserDb::saveTradeMobileLiableNok(QList<QString> line){
    qDebug()<<"行业移动应用-责任人信息校验不合规.nck"<<line;
}
void UserDb::saveTradeMobileLiableUnitNok(QList<QString> line){
    qDebug()<<"行业移动应用-责任人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveTradeFixedOk(QList<QString> line){
    qDebug()<<"行业固话应用-形式合规数据.ok"<<line;
}
void UserDb::saveTradeFixedAgentNotReg(QList<QString> line){
    qDebug()<<"行业固话应用-经办人信息未登记.nreg"<<line;
}
void UserDb::saveTradeFixedAgentUnitNotReg(QList<QString> line){
    qDebug()<<"行业固话应用-经办人&单位信息未登记.nreg"<<line;
}
void UserDb::saveTradeFixedUnitNotReg(QList<QString> line){
    qDebug()<<"行业固话应用-单位信息未登记.nreg"<<line;
}
void UserDb::saveTradeFixedAgentNok(QList<QString> line){
    qDebug()<<"行业固话应用-经办人信息校验不合规.nck"<<line;
}
void UserDb::saveTradeFixedAgentUnitNok(QList<QString> line){
    qDebug()<<"行业固话应用-经办人&单位信息校验不合规.nck"<<line;
}
void UserDb::saveTradeFixedUnitNok(QList<QString> line){
    qDebug()<<"行业固话应用-单位信息校验不合规.nck"<<line;
}
void UserDb::saveOneCard(QList<QString> line){
    qDebug()<<"个人移动一证五卡不合规.nck"<<line;
}

