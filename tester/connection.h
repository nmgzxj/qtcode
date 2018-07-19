#ifndef CONNECTION_H
#define CONNECTION_H
#define DELIMITER ||
#define ITEMNUM 42
#define DATEFORMAT yyyyMMdd


#include <QtSql>
#include <QDebug>
#include "qdom.h"

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setHostName("localhost");
    db.setDatabaseName("data.db");
    db.setUserName("king");
    db.setPassword("123456");
    if(!db.open()){
        //提示出错
        return false;
    }

    QSqlQuery query;

    //创建密码表
    query.exec("create table password(pwd varchar primary key)");
    query.exec("delete password");
    query.exec("insert into password values('1')");


    //创建原始数据表
    query.exec("create table userData(id int primary key, col1, col2, col3, col4, col5, col6, col7, col8, col9, col10, col11");
    //创建字段表
    query.exec("create table autoid(id varchar primary key,col_type varchar,col_name varchar)");
    query.exec("delete autoid");
    query.exec(QString("insert into autoid values('0','机主','姓名')"));
    query.exec(QString("insert into autoid values('01','机主','证件类型')"));
    query.exec(QString("insert into autoid values('02','机主','证件号码')"));
    query.exec(QString("insert into autoid values('03','机主','证件地址')"));
    query.exec(QString("insert into autoid values('04','机主','通讯地址')"));
    query.exec(QString("insert into autoid values('05','机主','装机地址')"));
    query.exec(QString("insert into autoid values('06','代（经）办人','姓名')"));
    query.exec(QString("insert into autoid values('07','代（经）办人','证件类型')"));
    query.exec(QString("insert into autoid values('08','代（经）办人','证件号码')"));
    query.exec(QString("insert into autoid values('09','代（经）办人','证件地址')"));
    query.exec(QString("insert into autoid values('10','代（经）办人','通讯地址')"));
    query.exec(QString("insert into autoid values('11','责任人','姓名')"));
    query.exec(QString("insert into autoid values('12','责任人','证件类型')"));
    query.exec(QString("insert into autoid values('13','责任人','证件号码')"));
    query.exec(QString("insert into autoid values('14','责任人','证件地址')"));
    query.exec(QString("insert into autoid values('15','责任人','通讯地址')"));
    query.exec(QString("insert into autoid values('16','单位或行业','单位名称')"));
    query.exec(QString("insert into autoid values('17','单位或行业','单位证件号码')"));
    query.exec(QString("insert into autoid values('18','单位或行业','单位证件类型')"));
    query.exec(QString("insert into autoid values('19','单位或行业','单位证件地址')"));
    query.exec(QString("insert into autoid values('20','单位或行业','单位通讯地址')"));
    query.exec(QString("insert into autoid values('21','单位或行业','单位装机地址')"));
    query.exec(QString("insert into autoid values('22','电话卡信息','MSISDN')"));
    query.exec(QString("insert into autoid values('23','电话卡信息','登记激活时间')"));
    query.exec(QString("insert into autoid values('24','电话卡信息','号码状态')"));
    query.exec(QString("insert into autoid values('25','电话卡信息','用户业务类型')"));
    query.exec(QString("insert into autoid values('26','营业网点信息','网点编号')"));
    query.exec(QString("insert into autoid values('27','营业网点信息','网点名称')"));
    query.exec(QString("insert into autoid values('28','营业网点信息','网点地址')"));
    query.exec(QString("insert into autoid values('29','营业网点信息','网点所在区县')"));
    query.exec(QString("insert into autoid values('30','营业网点信息','网点类型')"));
    query.exec(QString("insert into autoid values('31','营业网点信息','开通商编号')"));
    query.exec(QString("insert into autoid values('32','营业网点信息','证件地址')"));
    query.exec(QString("insert into autoid values('33','支付信息','交易流水账单号')"));
    query.exec(QString("insert into autoid values('34','支付信息','交易平台用户账号')"));
    query.exec(QString("insert into autoid values('35','支付信息','用户交易的银行卡卡号或第三方支付账号名称')"));
    query.exec(QString("insert into autoid values('36','支付信息','机主证件电子复印件图片名称')"));
    query.exec(QString("insert into autoid values('37','支付信息','代办人证件电子复印件图片名称')"));
    query.exec(QString("insert into autoid values('38','用户类型','用户类型')"));
    query.exec(QString("insert into autoid values('39','渠道类型','渠道类型')"));
    query.exec(QString("insert into autoid values('40','使用状态','使用状态')"));
    query.exec(QString("insert into autoid values('41','预留字段','预留字段')"));

    //创建业务类型表
    query.exec("create table businesstype(id varchar primary key,category varchar,biztype varchar)");
    query.exec(QString("insert into businesstype values('01','移动','-')"));
    query.exec(QString("insert into businesstype values('02','固定','固话业务',34,20,5,15)"));
    query.exec(QString("insert into businesstype values('03','固定','固话',41,80,20,60)"));
    query.exec(QString("insert into businesstype values('04','固定','PSTN业务',83,40,15,25)"));
    query.exec(QString("insert into businesstype values('05','固定','NGN业务',39,50,15,35)"));
    query.exec(QString("insert into businesstype values('06','固定','SCDMA业务',28,60,10,50)"));
    query.exec(QString("insert into businesstype values('07','固定','普通电话',27,70,20,50)"));
    query.exec(QString("insert into businesstype values('08','固定','固定电话',25,75,25,50)"));
    query.exec(QString("insert into businesstype values('09','固定','FIX',27,65,20,45)"));

    //创建业务状态表
    query.exec("create table businessstatus(id varchar primary key,category varchar,bizstatus varchar)");
    query.exec(QString("insert into businessstatus values('01','非实名停机','未实名停机')"));
    query.exec(QString("insert into businessstatus values('02','非实名停机','非实名制停机')"));
    query.exec(QString("insert into businessstatus values('03','非实名停机','非实名停机')"));
    query.exec(QString("insert into businessstatus values('04','非实名停机','未实名全停')"));
    query.exec(QString("insert into businessstatus values('05','非实名停机','实名审核停机')"));
    query.exec(QString("insert into businessstatus values('06','非实名停机','实名审核停机2')"));
    query.exec(QString("insert into businessstatus values('07','非实名停机','实名审核停机3')"));
    query.exec(QString("insert into businessstatus values('08','非实名停机','未实名违章停机')"));
    query.exec(QString("insert into businessstatus values('09','非实名停机','局方非实名停机')"));
    query.exec(QString("insert into businessstatus values('10','非实名停机','非实名违章双停')"));
    query.exec(QString("insert into businessstatus values('11','不在网','拆机')"));
    query.exec(QString("insert into businessstatus values('12','现场拍照时间节点','20170101')"));

    //创建证件类型表
    query.exec("create table cardtype(id varchar primary key,category varchar,cardname varchar)");
    query.exec(QString("insert into cardtype values('01','居民身份证','01')"));
    query.exec(QString("insert into cardtype values('02','居民身份证','0')"));
    query.exec(QString("insert into cardtype values('03','居民身份证','身份证')"));
    query.exec(QString("insert into cardtype values('04','居民身份证','身份证迁移')"));
    query.exec(QString("insert into cardtype values('05','居民身份证','国内身份证')"));
    query.exec(QString("insert into cardtype values('06','居民身份证','IDCARD')"));
    query.exec(QString("insert into cardtype values('07','居民身份证','身份证-18位')"));
    query.exec(QString("insert into cardtype values('08','居民身份证','身份证(18位)')"));
    query.exec(QString("insert into cardtype values('09','居民身份证','身份证18位')"));
    query.exec(QString("insert into cardtype values('10','居民身份证','身份证15位')"));
    query.exec(QString("insert into cardtype values('11','居民身份证','公众证件-居民身份证')"));
    query.exec(QString("insert into cardtype values('12','居民身份证','居民身份证')"));
    query.exec(QString("insert into cardtype values('13','居民身份证','居民身份证(18位)')"));
    query.exec(QString("insert into cardtype values('14','居民身份证','居民身份证(15位)')"));
    query.exec(QString("insert into cardtype values('15','居民身份证','0-本地身份证')"));
    query.exec(QString("insert into cardtype values('16','居民身份证','1-外地身份证')"));
    query.exec(QString("insert into cardtype values('17','居民身份证','IdCard')"));
    query.exec(QString("insert into cardtype values('18','居民身份证','IdTypeJSX')"));
    query.exec(QString("insert into cardtype values('19','居民身份证','101')"));
    query.exec(QString("insert into cardtype values('20','居民身份证','1')"));
    query.exec(QString("insert into cardtype values('21','居民身份证','2')"));

    query.exec(QString("insert into cardtype values('22','临时居民身份证','临时身份证')"));
    query.exec(QString("insert into cardtype values('23','临时居民身份证','临时居民身份证')"));
    query.exec(QString("insert into cardtype values('24','临时居民身份证','41')"));
    query.exec(QString("insert into cardtype values('25','临时居民身份证','TempId')"));

    query.exec(QString("insert into cardtype values('26','户口薄','户口簿')"));
    return true;
}

static bool createXml()
{
    QFile file("data.xml");
    if(file.exists())return true;
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
        return false;
    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    QDomElement root = doc.createElement(QString("清单"));
    doc.appendChild(root);
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
    return true;
}

#endif // CONNECTION_H
