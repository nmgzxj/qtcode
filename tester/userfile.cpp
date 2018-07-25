#include "userfile.h"
#include <QDir>
#include <QSqlRecord>
#include <QList>
#include <QTextCodec>


UserFile::UserFile()
{
     stopped = false;
     QList<QList<QString>> lls = xmlConfig->readAutoid();
     QString name;
//     report = new Report();
     int num;
     bool ok;
     for(int i=0; i<lls.size(); i++){
         name = lls.at(i).at(1);
         num = lls.at(i).at(2).toInt(&ok,10);
         qDebug()<<"col name is "<<name<<" num is "<<num;
         col_name_map.insert(name,num);
     }

//     createTable();

}

//文件是否存在
bool UserFile::fileIsExists(QString filename){
    if(filename.isNull()||filename.isEmpty()){
        writeLog("文件名参数不正确。");
        return false;
    }
    QFile file(filename);
    return file.exists();
}

//创建数据库表
bool UserFile::createTable(){

    QString sql = "create table file(id varchar primary key";
    for(int i=0;i<COL_NUM;i++){
        sql.append(",col").append( QString::number(i+1, 10)).append(" varchar");
    }
    sql.append(")");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setHostName("localhost");
    db.setDatabaseName("data.db");
    db.setUserName("king");
    db.setPassword("123456");
    if(!db.open()){
        qDebug()<<"数据库连接出错。";
        return false;
    }

    QSqlQuery query;
    qDebug()<<"drop table"<<query.exec("drop table file");
    qDebug()<<"createTable()"<<sql;
    bool b = query.exec(sql);
    db.close();
    return b;
}

//文件入库
bool UserFile::insertDb(QString filename){
    if(!fileIsExists(filename)){
        qDebug()<<"文件不存在。\n当前路径是：";
        qDebug()<< QDir::currentPath();
        return false;
    }
    if(!createTable()){
        qDebug()<<"库表创建不成功。";
        return false;
    }
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

//    db.setHostName("localhost");
//    db.setDatabaseName("data.db");
//    db.setUserName("king");
//    db.setPassword("123456");
//    if(!db.open()){
//        writeLog("创建数据库连接出错。");
//        return false;
//    }

    QSqlQuery query;
    QFile file(filename);
    QTextCodec *code = QTextCodec::codecForName("GBK");//设置文件编码
    QList<QString> col;
    QString sql="";
    QString line = "";
    int line_num = 1;
    if(file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream stream(&file);
        stream.setCodec(code);

         do {
            sql = "insert into file values(";
            sql.append(QString::number(line_num++));
            line = stream.readLine();
            col =  line.split(strItemDelimeter);
            qDebug()<<"tmp is :"<<qPrintable(line);
            for(int i=0;i<col.size();i++){
                sql.append(",'"+col[i]+"'");
            }
            sql.append(")");
            qDebug()<<"insertDb()"<<qPrintable(sql);
            qDebug()<<query.exec(sql);
        }while(!line.isEmpty());
    }
    else{
        qDebug()<<"文件打开错误。";
    }
//    db.close();
    return true;
}

//文件导入内存
QList<QList<QString>> UserFile::insertList(QString filename){
    QList<QList<QString>> list;
    if(!fileIsExists(filename)){
        qDebug()<<"文件不存在。\n当前路径是：";
        qDebug()<< QDir::currentPath();
        return list;
    }

    QFile file(filename);
    QTextCodec *code = QTextCodec::codecForName("GBK");//设置文件编码
    QList<QString> col;
    QString line = "";
    if(file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream stream(&file);
        stream.setCodec(code);

         do {
            line = stream.readLine();
            col =  line.split(strItemDelimeter);
            list.append(col);
            //qDebug()<<"line is :"<<qPrintable(line);
        }while(!line.isEmpty());
    }
    else{
        qDebug()<<"文件打开错误。";
    }
    return list;
}

/**
 * 读取数据库函数
 * @brief UserFile::readTable
 * @param sql sqlite语句
 * @return 数据列表
 */
QList<QString> UserFile::readTable(QString sql){
    QList<QString> list;
    QString line = "";
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("data.db");
    db.setUserName("king");
    db.setPassword("123456");
    if(!db.open()){
        writeLog("创建数据库连接出错。");
    }

    QSqlQuery query;
    query.exec(sql);
    QSqlRecord qr = query.record();
    qDebug()<<sql<<"中字段数为"<<qr.count();

    while(query.next()){
        line = "";
        for(int i=0;i<COL_NUM;i++){
            line.append(query.value(i).toString());

        }
         qDebug()<<"line:"<<qPrintable(line);
        list.append(line);
    }
    db.close();
    return list;
}

//读取规则
bool UserFile::readRule(){
    QList<QString> rule1;
    //护照--姓名不少于2个字符
    //身份证号码非空且为数字组合
    /**身份证（含军人身份证）
     * 1、不能为空
     * 2、必须为汉字,且汉字个数至少是2个
     * 3、姓名中不能带阿拉伯数字以及除.与•之外的特殊字符
     * @return boolean
     */
    QString temp = "";
    return false;
}

void UserFile::setFileName(QString fileName)
{
    this->fileName = fileName;
}

bool isNull(QString str){
    return (str.isNull()||str.isEmpty()||str.toUpper().compare("NULL")==0);
}


int UserFile::getCol_num(QString name){
//    int rtn = ;
    qDebug()<<"查询的列名是"<<name<<"列号是"<<col_name_map.value(name);
    return col_name_map.value(name);
}

void UserFile::savePersonMobileOwnerNameNotReg(QList<QString> line){
    qDebug()<<"个人移动用户机主姓名未登记"<<line;

}
void UserFile::savePersonMobileOwnerTypeNotReg(QList<QString> line){
    qDebug()<<"个人移动用户机主证件类型未登记"<<line;
}
void UserFile::savePersonMobileOwnerNumNotReg(QList<QString> line){
    qDebug()<<"个人移动用户机主证件号码未登记"<<line;
}
void UserFile::savePersonMobileOwnerAddNotReg(QList<QString> line){
    qDebug()<<"个人移动用户机主证件地址未登记"<<line;
}
void UserFile::savePersonMobileOwnerNameNumNotReg(QList<QString> line){
    qDebug()<<"个人移动用户机主姓名证件号码未登记"<<line;
}
void UserFile::savePersonMobileOwnerNameAddNotReg(QList<QString> line){
    qDebug()<<"个人移动用户机主姓名证件地址未登记"<<line;
}
void UserFile::savePersonMobileOwnerNumAddNotReg(QList<QString> line){
    qDebug()<<"个人移动用户机主证件号码地址未登记"<<line;
}
void UserFile::savePersonMobileOwnerNameNumAddNotReg(QList<QString> line){
    qDebug()<<"个人移动用户机主姓名证件号码地址未登记"<<line;
}
void UserFile::saveAllNotReg(QList<QString> line){
    qDebug()<<"全量未登记"<<line;
}

/**
 * 处理个人移动号码
 * 		// 个人--移动电话
        filename5pmok = str_files_out_path+ "个人移动用户-形式合规数据.ok";

        filename10pm = str_files_out_path + "个人移动用户-证件类型未登记.nreg";
        filename11pm = str_files_out_path + "个人移动用户-用户姓名未登记.nreg";
        filename12pm = str_files_out_path + "个人移动用户-证件号码未登记.nreg";
        filename13pm = str_files_out_path + "个人移动用户-证件地址未登记.nreg";
        filename14pm = str_files_out_path + "个人移动用户-用户姓名&证件号码未登记.nreg";
        filename15pm = str_files_out_path + "个人移动用户-用户姓名&证件地址未登记.nreg";
        filename16pm = str_files_out_path + "个人移动用户-证件号码&证件地址未登记.nreg";
        filename17pm = str_files_out_path + "个人移动用户-用户姓名&证件号码&证件地址未登记.nreg";

        filename20pm = str_files_out_path + "个人移动用户-证件类型校验不合规.nck";
        filename21pm = str_files_out_path + "个人移动用户-用户姓名校验不合规.nck";
        filename22pm = str_files_out_path + "个人移动用户-证件号码校验不合规.nck";
        filename23pm = str_files_out_path + "个人移动用户-证件地址校验不合规.nck";
        filename24pm = str_files_out_path + "个人移动用户-用户姓名&证件号码校验不合规.nck";
        filename25pm = str_files_out_path + "个人移动用户-用户姓名&证件地址校验不合规.nck";
        filename26pm = str_files_out_path + "个人移动用户-证件号码&证件地址校验不合规.nck";
        filename27pm = str_files_out_path + "个人移动用户-用户姓名&证件号码&证件地址校验不合规.nck";

 * */
bool UserFile::processPersonMobile(QList<QString> line){
    bool isnt_onwer = false;
    bool isnt_owner_name = false;
    QString owner_name = line[getCol_num("机主姓名")];
    qDebug()<<"processing owner_name "<<owner_name;
    if(isNull(owner_name)){
        savePersonMobileOwnerNameNotReg(line);//个人移动用户-用户姓名未登记
//        report->personMobileOwnerNameNotReg+=1;
        isnt_owner_name = true;
    }
    bool isnt_owner_type = false;
    QString owner_type = line[getCol_num("机主证件类型")];
    qDebug()<<"processing owner_type "<<owner_type;
    if(isNull(owner_type)){
        savePersonMobileOwnerTypeNotReg(line);//个人移动用户-证件类型未登记
//        report->personMobileOwnerTypeNotReg+=1;
        isnt_owner_type = true;
    }
    bool isnt_owner_num = false;
    QString owner_num = line[getCol_num("机主证件号码")];
    qDebug()<<"processing owner_num "<<owner_num;
    if(isNull(owner_num)){
        savePersonMobileOwnerNumNotReg(line);//个人移动用户-证件号码未登记
        isnt_owner_num = true;
    }
    bool isnt_owner_add = false;
    QString owner_add = line[getCol_num("机主证件地址")];
    qDebug()<<"processing owner_add "<<owner_add;
    if(isNull(owner_add)){
        savePersonMobileOwnerAddNotReg(line);//个人移动用户-证件地址未登记
        isnt_owner_add = true;
    }

    if(isnt_owner_name&isnt_owner_num){
        savePersonMobileOwnerNameNumNotReg(line);//个人移动用户-用户姓名&证件号码未登记
    }
    if(isnt_owner_name&isnt_owner_add){
        savePersonMobileOwnerNameAddNotReg(line);//个人移动用户-用户姓名&证件地址未登记
    }
    if(isnt_owner_num&isnt_owner_add){
        savePersonMobileOwnerNumAddNotReg(line);//个人移动用户-证件号码&证件地址未登记
    }
    if(isnt_owner_name&isnt_owner_num&isnt_owner_add){
        savePersonMobileOwnerNameNumAddNotReg(line);//个人移动用户-用户姓名&证件号码&证件地址未登记
    }
    if(isnt_owner_name||isnt_owner_num||isnt_owner_add){
        isnt_onwer = true;
        saveAllNotReg(line);//全量未登记
    }
    return isnt_onwer;
}

void savePersonFixedOwnerNameNotReg(QList<QString> line){
    qDebug()<<"个人固话用户机主姓名未登记"<<line;
}
void savePersonFixedOwnerTypeNotReg(QList<QString> line){
    qDebug()<<"个人固话用户机主证件类型未登记"<<line;
}
void savePersonFixedOwnerNumNotReg(QList<QString> line){
    qDebug()<<"个人固话用户机主证件号码未登记"<<line;
}
void savePersonFixedOwnerAddNotReg(QList<QString> line){
    qDebug()<<"个人固话用户机主证件地址未登记"<<line;
}
void savePersonFixedOwnerNameNumNotReg(QList<QString> line){
    qDebug()<<"个人固话用户机主姓名证件号码未登记"<<line;
}
void savePersonFixedOwnerNameAddNotReg(QList<QString> line){
    qDebug()<<"个人固话用户机主姓名证件地址未登记"<<line;
}
void savePersonFixedOwnerNumAddNotReg(QList<QString> line){
    qDebug()<<"个人固话用户机主证件号码地址未登记"<<line;
}
void savePersonFixedOwnerNameNumAddNotReg(QList<QString> line){
    qDebug()<<"个人固话用户机主姓名证件号码地址未登记"<<line;
}


/**
 * @brief UserFile::processPersonFixed 处理个人固定电话
 * @param line
 * 		// 个人-固定电话
        filename5pfok = str_files_out_path+ "个人固话用户-形式合规数据.ok";

        filename10pf = str_files_out_path + "个人固话用户-证件类型未登记.nreg";
        filename11pf = str_files_out_path + "个人固话用户-用户姓名未登记.nreg";
        filename12pf = str_files_out_path + "个人固话用户-证件号码未登记.nreg";
        filename13pf = str_files_out_path + "个人固话用户-证件地址未登记.nreg";
        filename14pf = str_files_out_path + "个人固话用户-用户姓名&证件号码未登记.nreg";
        filename15pf = str_files_out_path + "个人固话用户-用户姓名&证件地址未登记.nreg";
        filename16pf = str_files_out_path + "个人固话用户-证件号码&证件地址未登记.nreg";
        filename17pf = str_files_out_path + "个人固话用户-用户姓名&证件号码&证件地址未登记.nreg";

        filename20pf = str_files_out_path + "个人固话用户-证件类型校验不合规.nck";
        filename21pf = str_files_out_path + "个人固话用户-用户姓名校验不合规.nck";
        filename22pf = str_files_out_path + "个人固话用户-证件号码校验不合规.nck";
        filename23pf = str_files_out_path + "个人固话用户-证件地址校验不合规.nck";
        filename24pf = str_files_out_path + "个人固话用户-用户姓名&证件号码校验不合规.nck";
        filename25pf = str_files_out_path + "个人固话用户-用户姓名&证件地址校验不合规.nck";
        filename26pf = str_files_out_path + "个人固话用户-证件号码&证件地址校验不合规.nck";
        filename27pf = str_files_out_path + "个人固话用户-用户姓名&证件号码&证件地址校验不合规.nck";

        filename1pma = str_files_out_path + "个人移动用户-代办人信息未登记.nreg";
        filename1pfa = str_files_out_path + "个人固话用户-代办人信息未登记.nreg";
        filename2pma = str_files_out_path + "个人移动用户-代办人信息校验不合规.nck";
        filename2pfa = str_files_out_path + "个人固话用户-代办人信息校验不合规.nck";

 */
bool UserFile::processPersonFixed(QList<QString> line){

    bool isnt_owner_name = false;
    QString owner_name = line[getCol_num("机主姓名")];
    qDebug()<<"processing owner_name "<<owner_name;
    if(isNull(owner_name)){
        savePersonFixedOwnerNameNotReg(line);//个人固话用户-用户姓名未登记
        isnt_owner_name = true;
    }
    bool isnt_owner_type = false;
    QString owner_type = line[getCol_num("机主证件类型")];
    qDebug()<<"processing owner_type "<<owner_type;
    if(isNull(owner_type)){
        savePersonFixedOwnerTypeNotReg(line);//个人固话用户-证件类型未登记
        isnt_owner_type = true;
    }
    bool isnt_owner_num = false;
    QString owner_num = line[getCol_num("机主证件号码")];
    qDebug()<<"processing owner_num "<<owner_num;
    if(isNull(owner_num)){
        savePersonFixedOwnerNumNotReg(line);//个人固话用户-证件号码未登记
        isnt_owner_num = true;
    }
    bool isnt_owner_add = false;
    QString owner_add = line[getCol_num("机主证件地址")];
    qDebug()<<"processing owner_add "<<owner_add;
    if(isNull(owner_add)){
        savePersonFixedOwnerAddNotReg(line);//个人固话用户-证件地址未登记
        isnt_owner_add = true;
    }

    if(isnt_owner_name&isnt_owner_num){
        savePersonFixedOwnerNameNumNotReg(line);//个人固话用户-用户姓名&证件号码未登记
    }
    if(isnt_owner_name&isnt_owner_add){
        savePersonFixedOwnerNameAddNotReg(line);//个人固话用户-用户姓名&证件地址未登记
    }
    if(isnt_owner_num&isnt_owner_add){
        savePersonFixedOwnerNumAddNotReg(line);//个人固话用户-证件号码&证件地址未登记
    }
    if(isnt_owner_name&isnt_owner_num&isnt_owner_add){
        savePersonFixedOwnerNameNumAddNotReg(line);//个人固话用户-用户姓名&证件号码&证件地址未登记
    }
    if(isnt_owner_name||isnt_owner_num||isnt_owner_add){
        saveAllNotReg(line);//全量未登记
    }
    return true;
}

void saveUnitMobileOwnerNotReg(QList<QString> line){
    qDebug()<<"单位移动用户-使用人信息未登记"<<line;
}

void saveUnitMobileOwnerAgentNotReg(QList<QString> line){
    qDebug()<<"单位移动用户-经办人信息未登记"<<line;
}

void saveUnitMobileUnitNotReg(QList<QString> line){
    qDebug()<<"单位移动用户-单位信息未登记"<<line;
}

void saveUnitMobileOwnerUnitNotReg(QList<QString> line){
    qDebug()<<"单位移动用户-使用人&单位信息未登记"<<line;
}

void saveUnitMobileAgentUnitNotReg(QList<QString> line){
    qDebug()<<"单位移动用户-经办人&单位信息未登记"<<line;
}

void saveUnitMobileOwnerAgentUnitAddNotReg(QList<QString> line){
    qDebug()<<"单位移动用户-使用人&经办人&单位信息未登记"<<line;
}

/**
 * @brief processUnitMobile 单位移动电话
 * @param line
 * 		filename5umok = str_files_out_path+ "单位移动用户-形式合规数据.ok";

        filename11um = str_files_out_path + "单位移动用户-使用人信息未登记.nreg";
        filename12um = str_files_out_path + "单位移动用户-经办人信息未登记.nreg";
        filename13um = str_files_out_path + "单位移动用户-单位信息未登记.nreg";
        filename14um = str_files_out_path + "单位移动用户-使用人&经办人信息未登记.nreg";
        filename15um = str_files_out_path + "单位移动用户-使用人&单位信息未登记.nreg";
        filename16um = str_files_out_path + "单位移动用户-经办人&单位信息未登记.nreg";
        filename17um = str_files_out_path + "单位移动用户-使用人&经办人&单位信息未登记.nreg";

        filename21um = str_files_out_path + "单位移动用户-使用人信息校验不合规.nck";
        filename22um = str_files_out_path + "单位移动用户-经办人信息校验不合规.nck";
        filename23um = str_files_out_path + "单位移动用户-单位信息校验不合规.nck";
        filename24um = str_files_out_path + "单位移动用户-使用人&经办人信息校验不合规.nck";
        filename25um = str_files_out_path + "单位移动用户-使用人&单位信息校验不合规.nck";
        filename26um = str_files_out_path + "单位移动用户-经办人&单位信息校验不合规.nck";
        filename27um = str_files_out_path + "单位移动用户-使用人&经办人&单位信息校验不合规.nck";
 */
bool UserFile::processUnitMobile(QList<QString> line){
    bool isnt_owner_info = false;
    if(processPersonMobile(line)){
        saveUnitMobileOwnerNotReg(line);//单位移动用户-使用人信息未登记
        isnt_owner_info = true;
    }
    bool isnt_agent_info = false;
    if(isNull(line[getCol_num("代（经）办人姓名")])|
       isNull(line[getCol_num("代（经）办人证件类型")])|
       isNull(line[getCol_num("代（经）办人证件号码")])|
       isNull(line[getCol_num("代（经）办人证件地址")])|
       isNull(line[getCol_num("代（经）办人通讯地址")])){
        saveUnitMobileOwnerAgentNotReg(line);//单位移动用户-经办人信息未登记
        isnt_agent_info = true;

    }
    bool isnt_unit_info = false;
    if(isNull(line[getCol_num("单位名称")])|
       isNull(line[getCol_num("单位证件号码")])|
       isNull(line[getCol_num("单位证件类型")])|
       isNull(line[getCol_num("单位证件地址")])|
       isNull(line[getCol_num("单位通讯地址")])){
        saveUnitMobileUnitNotReg(line);//单位移动用户-单位信息未登记
        isnt_unit_info = true;

    }

    if(isnt_owner_info&isnt_agent_info){
        saveUnitMobileOwnerAgentNotReg(line);//单位移动用户-使用人&经办人信息未登记
    }
    if(isnt_owner_info&isnt_unit_info){
        saveUnitMobileOwnerUnitNotReg(line);//单位移动用户-使用人&单位信息未登记
    }
    if(isnt_agent_info&isnt_unit_info){
        saveUnitMobileAgentUnitNotReg(line);//单位移动用户-经办人&单位信息未登记
    }
    if(isnt_owner_info&isnt_agent_info&isnt_unit_info){
        saveUnitMobileOwnerAgentUnitAddNotReg(line);//单位移动用户-使用人&经办人&单位信息未登记
    }
    if(isnt_owner_info||isnt_agent_info||isnt_unit_info){
        saveAllNotReg(line);//全量未登记
    }
    return true;

}

void UserFile::saveUnitFixedOwnerNotReg(QList<QString> line){
    qDebug()<<"单位固话用户-使用人信息未登记"<<line;
}
void UserFile::saveUnitFixedAgentNotReg(QList<QString> line){
    qDebug()<<"单位固话用户-经办人信息未登记"<<line;
}
void UserFile::saveUnitFixedUnitNotReg(QList<QString> line){
    qDebug()<<"单位固话用户-单位信息未登记"<<line;
}
void UserFile::saveUnitFixedOwnerAgentNotReg(QList<QString> line){
    qDebug()<<"单位固话用户-使用人&经办人信息未登记"<<line;
}
void UserFile::saveUnitFixedOwnerUnitNotReg(QList<QString> line){
    qDebug()<<"单位固话用户-使用人&单位信息未登记"<<line;
}
void UserFile::saveUnitFixedAgentUnitNotReg(QList<QString> line){
    qDebug()<<"单位固话用户-经办人&单位信息未登记"<<line;
}
void UserFile::saveUnitFixedOwnerAgentUnitAddNotReg(QList<QString> line){
    qDebug()<<"单位固话用户-使用人&经办人&单位信息未登记"<<line;
}

/**
 * @brief processUnitFixed
 * @param line
 * 		// 单位--固定电话
        filename5ufok = str_files_out_path+ "单位固话用户-形式合规数据.ok";

        filename21uf = str_files_out_path + "单位固话用户-200.nck";
        filename22uf = str_files_out_path + "单位固话用户-经办人信息校验不合规.nck";
        filename23uf = str_files_out_path + "单位固话用户-单位信息校验不合规.nck";
        filename24uf = str_files_out_path + "单位固话用户-220.nck";
        filename25uf = str_files_out_path + "单位固话用户-202.nck";
        filename26uf = str_files_out_path + "单位固话用户-经办人&单位信息校验不合规.nck";
        filename27uf = str_files_out_path + "单位固话用户-222.nck";
 */
bool UserFile::processUnitFixed(QList<QString> line){
    bool isnt_owner_info = false;
    if(processPersonFixed(line)){
        saveUnitFixedOwnerNotReg(line);//单位固话用户-使用人信息未登记
        isnt_owner_info = true;
    }
    bool isnt_agent_info = false;
    if(isNull(line[getCol_num("代（经）办人姓名")])|
       isNull(line[getCol_num("代（经）办人证件类型")])|
       isNull(line[getCol_num("代（经）办人证件号码")])|
       isNull(line[getCol_num("代（经）办人证件地址")])|
       isNull(line[getCol_num("代（经）办人通讯地址")])){
        saveUnitFixedAgentNotReg(line);//单位固话用户-经办人信息未登记
        isnt_agent_info = true;

    }
    bool isnt_unit_info = false;
    if(isNull(line[getCol_num("单位名称")])|
       isNull(line[getCol_num("单位证件号码")])|
       isNull(line[getCol_num("单位证件类型")])|
       isNull(line[getCol_num("单位证件地址")])|
       isNull(line[getCol_num("单位通讯地址")])){
        saveUnitFixedUnitNotReg(line);//单位固话用户-单位信息未登记
        isnt_unit_info = true;

    }

    if(isnt_owner_info&isnt_agent_info){
        saveUnitFixedOwnerAgentNotReg(line);//单位固话用户-使用人&经办人信息未登记
    }
    if(isnt_owner_info&isnt_unit_info){
        saveUnitFixedOwnerUnitNotReg(line);//单位固话用户-使用人&单位信息未登记
    }
    if(isnt_agent_info&isnt_unit_info){
        saveUnitFixedAgentUnitNotReg(line);//单位固话用户-经办人&单位信息未登记
    }
    if(isnt_owner_info&isnt_agent_info&isnt_unit_info){
        saveUnitFixedOwnerAgentUnitAddNotReg(line);//单位固话用户-使用人&经办人&单位信息未登记
    }
    if(isnt_owner_info||isnt_agent_info||isnt_unit_info){
        saveAllNotReg(line);//全量未登记
    }

    return true;
}
void UserFile::saveTradeMobileAgentNotReg(QList<QString> line){
    qDebug()<<"行业移动应用-经办人信息未登记"<<line;
}
void UserFile::saveTradeMobileUnitNotReg(QList<QString> line){
    qDebug()<<"行业移动应用-单位信息未登记"<<line;
}
void UserFile::saveTradeMobileLiableNotReg(QList<QString> line){
    qDebug()<<"行业移动应用-责任人信息未登记"<<line;
}
void UserFile::saveTradeMobileAgentUnitNotReg(QList<QString> line){
    qDebug()<<"行业移动应用-经办人&单位信息未登记"<<line;
}
void UserFile::saveTradeMobileLiableAgentNotReg(QList<QString> line){
    qDebug()<<"行业移动应用-责任人&经办人信息未登记"<<line;
}
void UserFile::saveTradeMobileLiableUnitNotReg(QList<QString> line){
    qDebug()<<"行业移动应用-责任人&单位信息未登记"<<line;
}
void UserFile::saveTradeMobileLiableAgentUnitAddNotReg(QList<QString> line){
    qDebug()<<"行业移动应用-责任人&经办人&单位信息未登记"<<line;
}
/**
 * @brief processTradeMobile
 * @param line
 * 		// 行业--移动 应用
        filename5imok = str_files_out_path+ "行业移动应用-形式合规数据.ok";

        filename21im = str_files_out_path + "行业移动应用-经办人信息校验不合规.nck";
        filename24im = str_files_out_path + "行业移动应用-经办人&单位信息校验不合规.nck";
        filename25im = str_files_out_path + "行业移动应用-责任人&经办人信息校验不合规.nck";
        filename26im = str_files_out_path + "行业移动应用-责任人&经办人&单位信息校验不合规.nck";
        filename27im = str_files_out_path + "行业移动应用-单位信息校验不合规.nck";
        filename28im = str_files_out_path + "行业移动应用-责任人信息校验不合规.nck";
        filename29im = str_files_out_path + "行业移动应用-责任人&单位信息校验不合规.nck";
 */
bool UserFile::processTradeMobile(QList<QString> line){

    bool isnt_agent_info = false;
    if(isNull(line[getCol_num("代（经）办人姓名")])|
       isNull(line[getCol_num("代（经）办人证件类型")])|
       isNull(line[getCol_num("代（经）办人证件号码")])|
       isNull(line[getCol_num("代（经）办人证件地址")])|
       isNull(line[getCol_num("代（经）办人通讯地址")])){
        saveTradeMobileAgentNotReg(line);//行业移动应用-经办人信息未登记
        isnt_agent_info = true;

    }
    bool isnt_unit_info = false;
    if(isNull(line[getCol_num("单位名称")])|
       isNull(line[getCol_num("单位证件号码")])|
       isNull(line[getCol_num("单位证件类型")])|
       isNull(line[getCol_num("单位证件地址")])|
       isNull(line[getCol_num("单位通讯地址")])){
        saveTradeMobileUnitNotReg(line);//行业移动应用-单位信息未登记
        isnt_unit_info = true;

    }
    bool isnt_liable_info = false;
    if(isNull(line[getCol_num("责任人姓名")])|
       isNull(line[getCol_num("责任人证件类型")])|
       isNull(line[getCol_num("责任人证件号码")])|
       isNull(line[getCol_num("责任人证件地址")])|
       isNull(line[getCol_num("责任人通讯地址")])){
        saveTradeMobileLiableNotReg(line);//行业移动应用-责任人信息未登记
        isnt_liable_info = true;

    }

    if(isnt_agent_info&isnt_unit_info){
        saveTradeMobileAgentUnitNotReg(line);//行业移动应用-经办人&单位信息未登记
    }
    if(isnt_liable_info&isnt_agent_info){
        saveTradeMobileLiableAgentNotReg(line);//行业移动应用-责任人&经办人信息未登记
    }
    if(isnt_liable_info&isnt_unit_info){
        saveTradeMobileLiableUnitNotReg(line);//行业移动应用-责任人&单位信息未登记
    }
    if(isnt_liable_info&isnt_agent_info&isnt_unit_info){
        saveTradeMobileLiableAgentUnitAddNotReg(line);//行业移动应用-责任人&经办人&单位信息未登记
    }
    if(isnt_liable_info||isnt_agent_info||isnt_unit_info){
        saveAllNotReg(line);//全量未登记
    }
        return true;
}

void UserFile::saveTradeFixedAgentNotReg(QList<QString> line){
    qDebug()<<"行业固话应用-经办人信息未登记"<<line;
}
void UserFile::saveTradeFixedUnitNotReg(QList<QString> line){
    qDebug()<<"行业固话应用-单位信息未登记"<<line;
}
void UserFile::saveTradeFixedAgentUnitNotReg(QList<QString> line){
    qDebug()<<"行业固话应用-经办人&单位信息未登记"<<line;
}

/**
 * @brief processTradeFixed
 * @param line
 * 		// 行业--固定 应用
        filename5ifok = str_files_out_path+ "行业固话应用-形式合规数据.ok";

        filename21if = str_files_out_path + "行业固话应用-经办人信息校验不合规.nck";
        filename24if = str_files_out_path + "行业固话应用-经办人&单位信息校验不合规.nck";
        filename27if = str_files_out_path + "行业固话应用-单位信息校验不合规.nck";

        //filename_photo_2 = str_files_out_path + "现场照片核对记录-2.photo";
        //filename_photo_1 = "e:/" + "现场照片核对记录-1.photo";

        //filename_oneday_data = str_files_out_path + "抽取的一天的全量数据-1.data";
        //filename_oneday_data2 = "e:/" + "抽取的一天的全量数据-2.data";

        filename_one2five_pm = str_files_out_path + "个人移动一证五卡不合规.nck";
 */
bool UserFile::processTradeFixed(QList<QString> line){

    bool isnt_agent_info = false;
    if(isNull(line[getCol_num("代（经）办人姓名")])|
       isNull(line[getCol_num("代（经）办人证件类型")])|
       isNull(line[getCol_num("代（经）办人证件号码")])|
       isNull(line[getCol_num("代（经）办人证件地址")])|
       isNull(line[getCol_num("代（经）办人通讯地址")])){
        saveTradeFixedAgentNotReg(line);//行业固话应用-经办人信息未登记
        isnt_agent_info = true;

    }
    bool isnt_unit_info = false;
    if(isNull(line[getCol_num("单位名称")])|
       isNull(line[getCol_num("单位证件号码")])|
       isNull(line[getCol_num("单位证件类型")])|
       isNull(line[getCol_num("单位证件地址")])|
       isNull(line[getCol_num("单位通讯地址")])){
        saveTradeFixedUnitNotReg(line);//行业固话应用-单位信息未登记
        isnt_unit_info = true;

    }
    if(isnt_agent_info&isnt_unit_info){
        saveTradeFixedAgentUnitNotReg(line);//行业固话应用-经办人&单位信息未登记
    }
    if(isnt_agent_info||isnt_unit_info){
        saveAllNotReg(line);//全量未登记
    }

    return true;

}
/**
 * @brief processLine
 * @param line 单行文本数据

   //  0 个人移动， 1个人固话
   //  2单位移动， 3单位固话
   //  4行业移动，5行业固话
   //  6个人移动代办，7个人固话代办
        // 全量（个人+单位）
        filename2 = str_files_out_path + "全量形式不合规.nck";
        filename3 = str_files_out_path + "idcard.overdue";
        filename4 = str_files_out_path + "格式异常数据.abnormal";
        filename44 = str_files_out_path + "字段异常数据.abnormal";
        filename5 = str_files_out_path+ "all.ok";
        filename6 = str_files_out_path + "待挖掘记录-" + head_loop_num + ".txt";

        filename55 = str_files_out_path + "tian.mao";
 */
void UserFile::processLine(QList<QString> line){
    QString user_category = line[getCol_num("用户类型")];
    QString business_type = line[getCol_num("用户业务类型")];
    qDebug()<<"user_category is "<<user_category;
    qDebug()<<"business_type is "<<business_type;
    if(user_category=="个人客户"&&business_type=="移动手机号码"){//个人移动用户
        processPersonMobile(line);
    }
    else if(user_category=="个人客户"&&business_type=="2"){//个人固话用户
        processPersonFixed(line);
    }
    else if(user_category=="2"&&business_type=="移动手机号码"){//单位移动用户
        processUnitMobile(line);
    }
    else if(user_category=="2"&&business_type=="2"){//单位固话用户
        processUnitFixed(line);
    }
    else if(user_category=="3"&&business_type=="移动手机号码"){//行业移动用户
        processTradeMobile(line);
    }
    else if(user_category=="3"&&business_type=="2"){//行业固话用户
        processTradeFixed(line);
    }
}

/*
 * 代办人，机主年龄段可以配置
 * 用户业务类型和用户类型可配置。
 * 数据加翻页
 */

void processOneCard(QList<QList<QString>> lines){
    qDebug()<<"processing 一证五号。"<<lines.at(0);
}

void UserFile::run(){
    QList<QList<QString>> lines =  insertList(this->fileName);//文件数据装入内存
    int line_id = 0;
    while (!m_isStop&&line_id<lines.size()) {//按行处理数据
//        QThread::sleep(1);
        qDebug()<<QStringLiteral("开始处理数据第")<<line_id<<QStringLiteral("行");
        if(lines[line_id].size()==COL_NUM)
            processLine(lines[line_id]);
        else
            qDebug()<<line_id<<QStringLiteral("行数据列数不对");
        line_id++;
    }
    if(!m_isStop){
        processOneCard(lines);
    }
    isFinsh = true;
//        Report *report = new Report;
//        report->show();

}
//void UserFile::run1()
//{
//    qDebug()<<"file name is:"<<fileName;

//    int i=0;
//    while(i<2)
//    {
//        printMessage();
//        QThread::sleep(1);
//        i++;
//    }
//////    stopped = false;
//    {
//        QMutexLocker locker(&m_stopMutex);
//        m_isStop = false;
//    }
//    int count = 0;
//    QString str = QString("%1->%2,thread id:%3").arg(__FILE__).arg(__FUNCTION__).arg((int)(size_t)QThread::currentThreadId());
////    emit message(str);
//    int process = 0;
//    while(1)
//    {
//        {
//            QMutexLocker locker(&m_stopMutex);
//            if(m_isStop)
//                return;
//        }
//        printMessage();
//        if(m_runCount == count)
//        {
//            break;
//        }
//        QThread::sleep(1);

//        int pro = ((float)count / m_runCount) * 100;
//        qDebug()<<"pro is "<<pro;
//        if(pro != process)
//        {
////            qDebug()<<"process is "<<process;
//            printMessage();
//            process = pro;
//            printMessage();
////            emit progress(((float)count / m_runCount) * 100);
////            emit message(QString("Object::run times:%1,m_runCount:%2").arg(count).arg(m_runCount2));
//        }
//        ++count;
//    }
//}

void UserFile::printMessage(){
    qDebug()<<QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)(size_t)QThread::currentThreadId());
}

void UserFile::stop()
{
    stopped = true;
    m_isStop = true;
}


enum col_name11
{
    owner_name,  //"机主", "姓名"
    owner_type,  //"机主", "证件类型"
    owner_num,  //"机主", "证件号码"
    owner_add,  //"机主", "证件地址"
    owner_mailadd,  //"机主", "通讯地址"
    owner_loadadd,  //"机主", "装机地址"

    agent_name,  //"代（经）办人", "姓名"
    agent_type,  //"代（经）办人", "证件类型"
    agent_num,  //"代（经）办人", "证件号码"
    agent_add,  //"代（经）办人", "证件地址"
    agent_mailadd,  //"代（经）办人", "通讯地址"

    unitliable_name,  //"责任人", "姓名"
    unitliable_type,  //"责任人", "证件类型"
    unitliable_num,  //"责任人", "证件号码"
    unitliable_add,  //"责任人", "证件地址"
    unitliable_mailadd,  //"责任人", "通讯地址"

    unit_name,  //"单位或行业", "单位名称"
    unit_num,  //"单位或行业", "单位证件号码"
    unit_type,  //"单位或行业", "单位证件类型"
    unit_add,  //"单位或行业", "单位证件地址"
    unit_mailadd,  //"单位或行业", "单位通讯地址"
    unit_loadadd,  //"单位或行业", "单位装机地址"

    msisdn_num,  //"电话卡信息", "MSISDN号码"
    reg_act_time,  //"电话卡信息", "登记激活时间"
    phone_state,  //"电话卡信息", "号码状态"
    business_type,  //"电话卡信息", "用户业务类型"

    outlets_num,  //"营业网点信息", "网点编号"
    outlets_name,  //"营业网点信息", "网点名称"
    outlets_address,  //"营业网点信息", "网点地址"
    outlets_district,  //"营业网点信息", "网点所在区县"
    outlets_type,  //"营业网点信息", "网点类型"
    open_business_num,  //"营业网点信息", "开通商编号"

    bill_num,  //"支付信息", "交易流水账单号"
    user_account,  //"支付信息", "交易平台用户账号"
    payment_account,  //"支付信息", "用户交易的银行卡卡号或第三方支付账号名称"
    payment_time,  //"支付信息", "支付时间"
    owner_card_pic_name,  //"支付信息", "机主证件电子复印件图片名称"
    agent_card_pic_name,  //"支付信息", "代办人证件电子复印件图片名称"

    user_category,  //"用户类型", "用户类型"
    channel_type,  //"渠道类型", "渠道类型"
    business_use_state,  //"使用状态", "使用状态"
    reserved_field,  //"预留字段", "预留字段"

};


//分析文件
bool UserFile::analysisData(QList<QList<QString>> list){

    writeLog("需处理文件：\n");
    QList<QString> line;;
    for(int i=0;i<list.size();i++){
        writeLog(QString("文件第").append(QString::number(i+1,10)).append("行:\n"));
        line=list.at(i);
        int col_count = COL_NUM;

        if(line.size()<col_count){
            qDebug()<<"文件出错，本行列数不够，程序将退出，请检查文件格式。";
            return false;
        }
        qDebug()<<"用户名是"<<line[owner_name];
//        for(int j=0;j<line.size();j++){
//            qDebug()<<line[j];
//        }


    //如果业务状态为“不在网”,不计入统计范围
    // 如果业务状态为“非实名停机”,不计入统计范围
    //2013年9月1日后~2015年1月1日
    if(isNull(line[owner_name])){
        //个人移动用户-用户姓名未登记
        writeFile("个人移动用户-用户姓名未登记",line);
        writeFile("全量未登记.nreg",line);
        qDebug()<<"个人移动用户-用户姓名未登记";
        qDebug()<<"全量未登记.nreg";
    }
    else if(isNull(line[owner_type])){
        //个人移动用户-证件类型未登记
        qDebug()<<"个人移动用户-证件类型未登记";
        qDebug()<<"全量未登记.nreg";
    }
    else if(isNull(line[owner_num])){
        //个人移动用户-证件号码未登记
        qDebug()<<"个人移动用户-证件号码未登记";
        qDebug()<<"全量未登记.nreg";
    }
    else if(isNull(line[owner_add])){
        //个人移动用户-证件地址未登记
        qDebug()<<"个人移动用户-证件地址未登记";
        qDebug()<<"全量未登记.nreg";
    }
    else if(isNull(line[owner_name])&&isNull(line[owner_type])){
        //"个人移动用户-用户姓名&证件号码未登记.nreg"

    }
    else if(isNull(line[owner_name])&&isNull(line[owner_add])){
        //"个人移动用户-用户姓名&证件地址未登记.nreg"

    }
    else if(isNull(line[owner_add])&&isNull(line[owner_type])){
        //"个人移动用户-证件号码&证件地址未登记.nreg"

    }
    else if(isNull(line[owner_name])&&isNull(line[owner_add])&&isNull(line[owner_type])){
        //"个人移动用户-用户姓名&证件号码&证件地址未登记.nreg"

    }

    //个人移动用户-形式合规数据.


//    // 全量（个人+单位）
//    filename1 = str_files_out_path + "全量未登记.nreg";
//    filename2 = str_files_out_path + "全量形式不合规.nck";
//    filename3 = str_files_out_path + "idcard.overdue";
//    filename4 = str_files_out_path + "格式异常数据.abnormal";
//    filename44 = str_files_out_path + "字段异常数据.abnormal";
//    filename5 = str_files_out_path+ "all.ok";
//    filename6 = str_files_out_path + "待挖掘记录-" + head_loop_num + ".txt";

//    filename55 = str_files_out_path + "tian.mao";
//    // 个人--移动电话
//    filename5pmok = str_files_out_path+ "个人移动用户-形式合规数据.ok";


//    filename20pm = str_files_out_path + "个人移动用户-证件类型校验不合规.nck";
//    filename21pm = str_files_out_path + "个人移动用户-用户姓名校验不合规.nck";
//    filename22pm = str_files_out_path + "个人移动用户-证件号码校验不合规.nck";
//    filename23pm = str_files_out_path + "个人移动用户-证件地址校验不合规.nck";
//    filename24pm = str_files_out_path + "个人移动用户-用户姓名&证件号码校验不合规.nck";
//    filename25pm = str_files_out_path + "个人移动用户-用户姓名&证件地址校验不合规.nck";
//    filename26pm = str_files_out_path + "个人移动用户-证件号码&证件地址校验不合规.nck";
//    filename27pm = str_files_out_path + "个人移动用户-用户姓名&证件号码&证件地址校验不合规.nck";

//    // 个人-固定电话
//    filename5pfok = str_files_out_path+ "个人固话用户-形式合规数据.ok";

//    filename10pf = str_files_out_path + "个人固话用户-证件类型未登记.nreg";
//    filename11pf = str_files_out_path + "个人固话用户-用户姓名未登记.nreg";
//    filename12pf = str_files_out_path + "个人固话用户-证件号码未登记.nreg";
//    filename13pf = str_files_out_path + "个人固话用户-证件地址未登记.nreg";
//    filename14pf = str_files_out_path + "个人固话用户-用户姓名&证件号码未登记.nreg";
//    filename15pf = str_files_out_path + "个人固话用户-用户姓名&证件地址未登记.nreg";
//    filename16pf = str_files_out_path + "个人固话用户-证件号码&证件地址未登记.nreg";
//    filename17pf = str_files_out_path + "个人固话用户-用户姓名&证件号码&证件地址未登记.nreg";

//    filename20pf = str_files_out_path + "个人固话用户-证件类型校验不合规.nck";
//    filename21pf = str_files_out_path + "个人固话用户-用户姓名校验不合规.nck";
//    filename22pf = str_files_out_path + "个人固话用户-证件号码校验不合规.nck";
//    filename23pf = str_files_out_path + "个人固话用户-证件地址校验不合规.nck";
//    filename24pf = str_files_out_path + "个人固话用户-用户姓名&证件号码校验不合规.nck";
//    filename25pf = str_files_out_path + "个人固话用户-用户姓名&证件地址校验不合规.nck";
//    filename26pf = str_files_out_path + "个人固话用户-证件号码&证件地址校验不合规.nck";
//    filename27pf = str_files_out_path + "个人固话用户-用户姓名&证件号码&证件地址校验不合规.nck";

//    filename1pma = str_files_out_path + "个人移动用户-代办人信息未登记.nreg";
//    filename1pfa = str_files_out_path + "个人固话用户-代办人信息未登记.nreg";
//    filename2pma = str_files_out_path + "个人移动用户-代办人信息校验不合规.nck";
//    filename2pfa = str_files_out_path + "个人固话用户-代办人信息校验不合规.nck";

//    // 单位 -- 移动
//    filename5umok = str_files_out_path+ "单位移动用户-形式合规数据.ok";

//    filename11um = str_files_out_path + "单位移动用户-使用人信息未登记.nreg";
//    filename12um = str_files_out_path + "单位移动用户-经办人信息未登记.nreg";
//    filename13um = str_files_out_path + "单位移动用户-单位信息未登记.nreg";
//    filename14um = str_files_out_path + "单位移动用户-使用人&经办人信息未登记.nreg";
//    filename15um = str_files_out_path + "单位移动用户-使用人&单位信息未登记.nreg";
//    filename16um = str_files_out_path + "单位移动用户-经办人&单位信息未登记.nreg";
//    filename17um = str_files_out_path + "单位移动用户-使用人&经办人&单位信息未登记.nreg";

//    filename21um = str_files_out_path + "单位移动用户-使用人信息校验不合规.nck";
//    filename22um = str_files_out_path + "单位移动用户-经办人信息校验不合规.nck";
//    filename23um = str_files_out_path + "单位移动用户-单位信息校验不合规.nck";
//    filename24um = str_files_out_path + "单位移动用户-使用人&经办人信息校验不合规.nck";
//    filename25um = str_files_out_path + "单位移动用户-使用人&单位信息校验不合规.nck";
//    filename26um = str_files_out_path + "单位移动用户-经办人&单位信息校验不合规.nck";
//    filename27um = str_files_out_path + "单位移动用户-使用人&经办人&单位信息校验不合规.nck";


//    // 单位--固定电话
//    filename5ufok = str_files_out_path+ "单位固话用户-形式合规数据.ok";

//    filename11uf = str_files_out_path + "单位固话用户-100.nreg";
//    filename12uf = str_files_out_path + "单位固话用户-经办人信息未登记.nreg";
//    filename13uf = str_files_out_path + "单位固话用户-单位信息未登记.nreg";
//    filename14uf = str_files_out_path + "单位固话用户-110.nreg";
//    filename15uf = str_files_out_path + "单位固话用户-101.nreg";
//    filename16uf = str_files_out_path + "单位固话用户-经办人&单位信息未登记.nreg";
//    filename17uf = str_files_out_path + "单位固话用户-111.nreg";

//    filename21uf = str_files_out_path + "单位固话用户-200.nck";
//    filename22uf = str_files_out_path + "单位固话用户-经办人信息校验不合规.nck";
//    filename23uf = str_files_out_path + "单位固话用户-单位信息校验不合规.nck";
//    filename24uf = str_files_out_path + "单位固话用户-220.nck";
//    filename25uf = str_files_out_path + "单位固话用户-202.nck";
//    filename26uf = str_files_out_path + "单位固话用户-经办人&单位信息校验不合规.nck";
//    filename27uf = str_files_out_path + "单位固话用户-222.nck";

//    // 行业--移动 应用
//    filename5imok = str_files_out_path+ "行业移动应用-形式合规数据.ok";
//    filename11im = str_files_out_path + "行业移动应用-经办人信息未登记.nreg";
//    filename14im = str_files_out_path + "行业移动应用-经办人&单位信息未登记.nreg";
//    filename15im = str_files_out_path + "行业移动应用-责任人&经办人信息未登记.nreg";
//    filename16im = str_files_out_path + "行业移动应用-责任人&经办人&单位信息未登记.nreg";
//    filename17im = str_files_out_path + "行业移动应用-单位信息未登记.nreg";
//    filename18im = str_files_out_path + "行业移动应用-责任人信息未登记.nreg";
//    filename19im = str_files_out_path + "行业移动应用-责任人&单位信息未登记.nreg";

//    filename21im = str_files_out_path + "行业移动应用-经办人信息校验不合规.nck";
//    filename24im = str_files_out_path + "行业移动应用-经办人&单位信息校验不合规.nck";
//    filename25im = str_files_out_path + "行业移动应用-责任人&经办人信息校验不合规.nck";
//    filename26im = str_files_out_path + "行业移动应用-责任人&经办人&单位信息校验不合规.nck";
//    filename27im = str_files_out_path + "行业移动应用-单位信息校验不合规.nck";
//    filename28im = str_files_out_path + "行业移动应用-责任人信息校验不合规.nck";
//    filename29im = str_files_out_path + "行业移动应用-责任人&单位信息校验不合规.nck";

//    // 行业--固定 应用
//    filename5ifok = str_files_out_path+ "行业固话应用-形式合规数据.ok";
//    filename11if = str_files_out_path + "行业固话应用-经办人信息未登记.nreg";
//    filename14if = str_files_out_path + "行业固话应用-经办人&单位信息未登记.nreg";
//    filename17if = str_files_out_path + "行业固话应用-单位信息未登记.nreg";

//    filename21if = str_files_out_path + "行业固话应用-经办人信息校验不合规.nck";
//    filename24if = str_files_out_path + "行业固话应用-经办人&单位信息校验不合规.nck";
//    filename27if = str_files_out_path + "行业固话应用-单位信息校验不合规.nck";

//    //filename_photo_2 = str_files_out_path + "现场照片核对记录-2.photo";
//    //filename_photo_1 = "e:/" + "现场照片核对记录-1.photo";

//    //filename_oneday_data = str_files_out_path + "抽取的一天的全量数据-1.data";
//    //filename_oneday_data2 = "e:/" + "抽取的一天的全量数据-2.data";

//    filename_one2five_pm = str_files_out_path + "个人移动一证五卡不合规.nck";
    }

    return false;
}

//写日志
bool UserFile::writeLog(QString msg){
    qDebug()<<msg;
    return false;
}

//输出文件
bool UserFile::writeFile(QString filename,QList<QString> list){
    QFile file(filename);
    QString line = "";
    for(QString str:list){
        line += str;
    }
    if(file.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream out(&file);
        out<<line;
    }

    file.close();
    qDebug()<<"写入文件"<<filename;
    return false;
}
