﻿////#include "userfile.h"



////UserFile::UserFile()
////{
////     stopped = false;
////     QList<QList<QString>> lls = xmlConfig->readAutoid();
////     QString name;
//////     report = new Report();
////     int num;
////     bool ok;
////     for(int i=0; i<lls.size(); i++){
////         name = lls.at(i).at(1);
////         num = lls.at(i).at(2).toInt(&ok,10);
////         qDebug()<<"col name is "<<name<<" num is "<<num;
////         col_name_map.insert(name,num);
////     }

//////     createTable();

////}

//////文件是否存在
////bool UserFile::fileIsExists(QString filename){
////    if(filename.isNull()||filename.isEmpty()){
////        writeLog("文件名参数不正确。");
////        return false;
////    }
////    QFile file(filename);
////    return file.exists();
////}



//////文件导入内存
////QList<QList<QString>> UserFile::insertList(QString filename){
////    QList<QList<QString>> list;
////    if(!fileIsExists(filename)){
////        qDebug()<<"文件不存在。\n当前路径是：";
////        qDebug()<< QDir::currentPath();
////        return list;
////    }

////    QFile file(filename);
////    QTextCodec *code = QTextCodec::codecForName("GBK");//设置文件编码
////    QList<QString> col;
////    QString line = "";
////    if(file.open(QFile::ReadOnly | QFile::Text)){
////        QTextStream stream(&file);
////        stream.setCodec(code);

////         do {
////            line = stream.readLine();
////            col =  line.split(strItemDelimeter);
////            list.append(col);
////            //qDebug()<<"line is :"<<qPrintable(line);
////        }while(!line.isEmpty());
////    }
////    else{
////        qDebug()<<"文件打开错误。";
////    }
////    return list;
////}



//////读取规则
////bool UserFile::readRule(){
////    QList<QString> rule1;
////    //护照--姓名不少于2个字符
////    //身份证号码非空且为数字组合
////    /**身份证（含军人身份证）
////     * 1、不能为空
////     * 2、必须为汉字,且汉字个数至少是2个
////     * 3、姓名中不能带阿拉伯数字以及除.与•之外的特殊字符
////     * @return boolean
////     */
////    QString temp = "";
////    return false;
////}

////void UserFile::setFileName(QString fileName)
////{
////    this->fileName = fileName;
////}

////bool isNull(QString str){
////    return (str.isNull()||str.isEmpty()||str.toUpper().compare("NULL")==0);
////}


////int UserFile::getCol_num(QString name){
//////    int rtn = ;
////    qDebug()<<"查询的列名是"<<name<<"列号是"<<col_name_map.value(name);
////    return col_name_map.value(name);
////}

////void UserFile::savePersonMobileOwnerNameNotReg(QList<QString> line){
////    qDebug()<<"个人移动用户机主姓名未登记"<<line;

////}
////void UserFile::savePersonMobileOwnerTypeNotReg(QList<QString> line){
////    qDebug()<<"个人移动用户机主证件类型未登记"<<line;
////}
////void UserFile::savePersonMobileOwnerNumNotReg(QList<QString> line){
////    qDebug()<<"个人移动用户机主证件号码未登记"<<line;
////}
////void UserFile::savePersonMobileOwnerAddNotReg(QList<QString> line){
////    qDebug()<<"个人移动用户机主证件地址未登记"<<line;
////}
////void UserFile::savePersonMobileOwnerNameNumNotReg(QList<QString> line){
////    qDebug()<<"个人移动用户机主姓名证件号码未登记"<<line;
////}
////void UserFile::savePersonMobileOwnerNameAddNotReg(QList<QString> line){
////    qDebug()<<"个人移动用户机主姓名证件地址未登记"<<line;
////}
////void UserFile::savePersonMobileOwnerNumAddNotReg(QList<QString> line){
////    qDebug()<<"个人移动用户机主证件号码地址未登记"<<line;
////}
////void UserFile::savePersonMobileOwnerNameNumAddNotReg(QList<QString> line){
////    qDebug()<<"个人移动用户机主姓名证件号码地址未登记"<<line;
////}
////void UserFile::saveAllNotReg(QList<QString> line){
////    qDebug()<<"全量未登记"<<line;
////}

/////**
//// * 处理个人移动号码
//// * 		// 个人--移动电话
////        filename5pmok = str_files_out_path+ "个人移动用户-形式合规数据.ok";

////        filename10pm = str_files_out_path + "个人移动用户-证件类型未登记.nreg";
////        filename11pm = str_files_out_path + "个人移动用户-用户姓名未登记.nreg";
////        filename12pm = str_files_out_path + "个人移动用户-证件号码未登记.nreg";
////        filename13pm = str_files_out_path + "个人移动用户-证件地址未登记.nreg";
////        filename14pm = str_files_out_path + "个人移动用户-用户姓名&证件号码未登记.nreg";
////        filename15pm = str_files_out_path + "个人移动用户-用户姓名&证件地址未登记.nreg";
////        filename16pm = str_files_out_path + "个人移动用户-证件号码&证件地址未登记.nreg";
////        filename17pm = str_files_out_path + "个人移动用户-用户姓名&证件号码&证件地址未登记.nreg";

////        filename20pm = str_files_out_path + "个人移动用户-证件类型校验不合规.nck";
////        filename21pm = str_files_out_path + "个人移动用户-用户姓名校验不合规.nck";
////        filename22pm = str_files_out_path + "个人移动用户-证件号码校验不合规.nck";
////        filename23pm = str_files_out_path + "个人移动用户-证件地址校验不合规.nck";
////        filename24pm = str_files_out_path + "个人移动用户-用户姓名&证件号码校验不合规.nck";
////        filename25pm = str_files_out_path + "个人移动用户-用户姓名&证件地址校验不合规.nck";
////        filename26pm = str_files_out_path + "个人移动用户-证件号码&证件地址校验不合规.nck";
////        filename27pm = str_files_out_path + "个人移动用户-用户姓名&证件号码&证件地址校验不合规.nck";

//// * */
////bool UserFile::processPersonMobile(QList<QString> line){
////    bool isnt_onwer = false;
////    bool isnt_owner_name = false;
////    QString owner_name = line[getCol_num("机主姓名")];
////    qDebug()<<"processing owner_name "<<owner_name;
////    if(isNull(owner_name)){
////        savePersonMobileOwnerNameNotReg(line);//个人移动用户-用户姓名未登记
//////        report->personMobileOwnerNameNotReg+=1;
////        isnt_owner_name = true;
////    }
////    bool isnt_owner_type = false;
////    QString owner_type = line[getCol_num("机主证件类型")];
////    qDebug()<<"processing owner_type "<<owner_type;
////    if(isNull(owner_type)){
////        savePersonMobileOwnerTypeNotReg(line);//个人移动用户-证件类型未登记
//////        report->personMobileOwnerTypeNotReg+=1;
////        isnt_owner_type = true;
////    }
////    bool isnt_owner_num = false;
////    QString owner_num = line[getCol_num("机主证件号码")];
////    qDebug()<<"processing owner_num "<<owner_num;
////    if(isNull(owner_num)){
////        savePersonMobileOwnerNumNotReg(line);//个人移动用户-证件号码未登记
////        isnt_owner_num = true;
////    }
////    bool isnt_owner_add = false;
////    QString owner_add = line[getCol_num("机主证件地址")];
////    qDebug()<<"processing owner_add "<<owner_add;
////    if(isNull(owner_add)){
////        savePersonMobileOwnerAddNotReg(line);//个人移动用户-证件地址未登记
////        isnt_owner_add = true;
////    }

////    if(isnt_owner_name&isnt_owner_num){
////        savePersonMobileOwnerNameNumNotReg(line);//个人移动用户-用户姓名&证件号码未登记
////    }
////    if(isnt_owner_name&isnt_owner_add){
////        savePersonMobileOwnerNameAddNotReg(line);//个人移动用户-用户姓名&证件地址未登记
////    }
////    if(isnt_owner_num&isnt_owner_add){
////        savePersonMobileOwnerNumAddNotReg(line);//个人移动用户-证件号码&证件地址未登记
////    }
////    if(isnt_owner_name&isnt_owner_num&isnt_owner_add){
////        savePersonMobileOwnerNameNumAddNotReg(line);//个人移动用户-用户姓名&证件号码&证件地址未登记
////    }
////    if(isnt_owner_name||isnt_owner_num||isnt_owner_add){
////        isnt_onwer = true;
////        saveAllNotReg(line);//全量未登记
////    }
////    return isnt_onwer;
////}

////void savePersonFixedOwnerNameNotReg(QList<QString> line){
////    qDebug()<<"个人固话用户机主姓名未登记"<<line;
////}
////void savePersonFixedOwnerTypeNotReg(QList<QString> line){
////    qDebug()<<"个人固话用户机主证件类型未登记"<<line;
////}
////void savePersonFixedOwnerNumNotReg(QList<QString> line){
////    qDebug()<<"个人固话用户机主证件号码未登记"<<line;
////}
////void savePersonFixedOwnerAddNotReg(QList<QString> line){
////    qDebug()<<"个人固话用户机主证件地址未登记"<<line;
////}
////void savePersonFixedOwnerNameNumNotReg(QList<QString> line){
////    qDebug()<<"个人固话用户机主姓名证件号码未登记"<<line;
////}
////void savePersonFixedOwnerNameAddNotReg(QList<QString> line){
////    qDebug()<<"个人固话用户机主姓名证件地址未登记"<<line;
////}
////void savePersonFixedOwnerNumAddNotReg(QList<QString> line){
////    qDebug()<<"个人固话用户机主证件号码地址未登记"<<line;
////}
////void savePersonFixedOwnerNameNumAddNotReg(QList<QString> line){
////    qDebug()<<"个人固话用户机主姓名证件号码地址未登记"<<line;
////}


/////**
//// * @brief UserFile::processPersonFixed 处理个人固定电话
//// * @param line
//// * 		// 个人-固定电话
////        filename5pfok = str_files_out_path+ "个人固话用户-形式合规数据.ok";

////        filename10pf = str_files_out_path + "个人固话用户-证件类型未登记.nreg";
////        filename11pf = str_files_out_path + "个人固话用户-用户姓名未登记.nreg";
////        filename12pf = str_files_out_path + "个人固话用户-证件号码未登记.nreg";
////        filename13pf = str_files_out_path + "个人固话用户-证件地址未登记.nreg";
////        filename14pf = str_files_out_path + "个人固话用户-用户姓名&证件号码未登记.nreg";
////        filename15pf = str_files_out_path + "个人固话用户-用户姓名&证件地址未登记.nreg";
////        filename16pf = str_files_out_path + "个人固话用户-证件号码&证件地址未登记.nreg";
////        filename17pf = str_files_out_path + "个人固话用户-用户姓名&证件号码&证件地址未登记.nreg";

////        filename20pf = str_files_out_path + "个人固话用户-证件类型校验不合规.nck";
////        filename21pf = str_files_out_path + "个人固话用户-用户姓名校验不合规.nck";
////        filename22pf = str_files_out_path + "个人固话用户-证件号码校验不合规.nck";
////        filename23pf = str_files_out_path + "个人固话用户-证件地址校验不合规.nck";
////        filename24pf = str_files_out_path + "个人固话用户-用户姓名&证件号码校验不合规.nck";
////        filename25pf = str_files_out_path + "个人固话用户-用户姓名&证件地址校验不合规.nck";
////        filename26pf = str_files_out_path + "个人固话用户-证件号码&证件地址校验不合规.nck";
////        filename27pf = str_files_out_path + "个人固话用户-用户姓名&证件号码&证件地址校验不合规.nck";

////        filename1pma = str_files_out_path + "个人移动用户-代办人信息未登记.nreg";
////        filename1pfa = str_files_out_path + "个人固话用户-代办人信息未登记.nreg";
////        filename2pma = str_files_out_path + "个人移动用户-代办人信息校验不合规.nck";
////        filename2pfa = str_files_out_path + "个人固话用户-代办人信息校验不合规.nck";

//// */
////bool UserFile::processPersonFixed(QList<QString> line){

////    bool isnt_owner_name = false;
////    QString owner_name = line[getCol_num("机主姓名")];
////    qDebug()<<"processing owner_name "<<owner_name;
////    if(isNull(owner_name)){
////        savePersonFixedOwnerNameNotReg(line);//个人固话用户-用户姓名未登记
////        isnt_owner_name = true;
////    }
////    bool isnt_owner_type = false;
////    QString owner_type = line[getCol_num("机主证件类型")];
////    qDebug()<<"processing owner_type "<<owner_type;
////    if(isNull(owner_type)){
////        savePersonFixedOwnerTypeNotReg(line);//个人固话用户-证件类型未登记
////        isnt_owner_type = true;
////    }
////    bool isnt_owner_num = false;
////    QString owner_num = line[getCol_num("机主证件号码")];
////    qDebug()<<"processing owner_num "<<owner_num;
////    if(isNull(owner_num)){
////        savePersonFixedOwnerNumNotReg(line);//个人固话用户-证件号码未登记
////        isnt_owner_num = true;
////    }
////    bool isnt_owner_add = false;
////    QString owner_add = line[getCol_num("机主证件地址")];
////    qDebug()<<"processing owner_add "<<owner_add;
////    if(isNull(owner_add)){
////        savePersonFixedOwnerAddNotReg(line);//个人固话用户-证件地址未登记
////        isnt_owner_add = true;
////    }

////    if(isnt_owner_name&isnt_owner_num){
////        savePersonFixedOwnerNameNumNotReg(line);//个人固话用户-用户姓名&证件号码未登记
////    }
////    if(isnt_owner_name&isnt_owner_add){
////        savePersonFixedOwnerNameAddNotReg(line);//个人固话用户-用户姓名&证件地址未登记
////    }
////    if(isnt_owner_num&isnt_owner_add){
////        savePersonFixedOwnerNumAddNotReg(line);//个人固话用户-证件号码&证件地址未登记
////    }
////    if(isnt_owner_name&isnt_owner_num&isnt_owner_add){
////        savePersonFixedOwnerNameNumAddNotReg(line);//个人固话用户-用户姓名&证件号码&证件地址未登记
////    }
////    if(isnt_owner_name||isnt_owner_num||isnt_owner_add){
////        saveAllNotReg(line);//全量未登记
////    }
////    return true;
////}

////void saveUnitMobileOwnerNotReg(QList<QString> line){
////    qDebug()<<"单位移动用户-使用人信息未登记"<<line;
////}

////void saveUnitMobileOwnerAgentNotReg(QList<QString> line){
////    qDebug()<<"单位移动用户-经办人信息未登记"<<line;
////}

////void saveUnitMobileUnitNotReg(QList<QString> line){
////    qDebug()<<"单位移动用户-单位信息未登记"<<line;
////}

////void saveUnitMobileOwnerUnitNotReg(QList<QString> line){
////    qDebug()<<"单位移动用户-使用人&单位信息未登记"<<line;
////}

////void saveUnitMobileAgentUnitNotReg(QList<QString> line){
////    qDebug()<<"单位移动用户-经办人&单位信息未登记"<<line;
////}

////void saveUnitMobileOwnerAgentUnitAddNotReg(QList<QString> line){
////    qDebug()<<"单位移动用户-使用人&经办人&单位信息未登记"<<line;
////}

/////**
//// * @brief processUnitMobile 单位移动电话
//// * @param line
//// * 		filename5umok = str_files_out_path+ "单位移动用户-形式合规数据.ok";

////        filename11um = str_files_out_path + "单位移动用户-使用人信息未登记.nreg";
////        filename12um = str_files_out_path + "单位移动用户-经办人信息未登记.nreg";
////        filename13um = str_files_out_path + "单位移动用户-单位信息未登记.nreg";
////        filename14um = str_files_out_path + "单位移动用户-使用人&经办人信息未登记.nreg";
////        filename15um = str_files_out_path + "单位移动用户-使用人&单位信息未登记.nreg";
////        filename16um = str_files_out_path + "单位移动用户-经办人&单位信息未登记.nreg";
////        filename17um = str_files_out_path + "单位移动用户-使用人&经办人&单位信息未登记.nreg";

////        filename21um = str_files_out_path + "单位移动用户-使用人信息校验不合规.nck";
////        filename22um = str_files_out_path + "单位移动用户-经办人信息校验不合规.nck";
////        filename23um = str_files_out_path + "单位移动用户-单位信息校验不合规.nck";
////        filename24um = str_files_out_path + "单位移动用户-使用人&经办人信息校验不合规.nck";
////        filename25um = str_files_out_path + "单位移动用户-使用人&单位信息校验不合规.nck";
////        filename26um = str_files_out_path + "单位移动用户-经办人&单位信息校验不合规.nck";
////        filename27um = str_files_out_path + "单位移动用户-使用人&经办人&单位信息校验不合规.nck";
//// */
////bool UserFile::processUnitMobile(QList<QString> line){
////    bool isnt_owner_info = false;
////    if(processPersonMobile(line)){
////        saveUnitMobileOwnerNotReg(line);//单位移动用户-使用人信息未登记
////        isnt_owner_info = true;
////    }
////    bool isnt_agent_info = false;
////    if(isNull(line[getCol_num("代（经）办人姓名")])|
////       isNull(line[getCol_num("代（经）办人证件类型")])|
////       isNull(line[getCol_num("代（经）办人证件号码")])|
////       isNull(line[getCol_num("代（经）办人证件地址")])|
////       isNull(line[getCol_num("代（经）办人通讯地址")])){
////        saveUnitMobileOwnerAgentNotReg(line);//单位移动用户-经办人信息未登记
////        isnt_agent_info = true;

////    }
////    bool isnt_unit_info = false;
////    if(isNull(line[getCol_num("单位名称")])|
////       isNull(line[getCol_num("单位证件号码")])|
////       isNull(line[getCol_num("单位证件类型")])|
////       isNull(line[getCol_num("单位证件地址")])|
////       isNull(line[getCol_num("单位通讯地址")])){
////        saveUnitMobileUnitNotReg(line);//单位移动用户-单位信息未登记
////        isnt_unit_info = true;

////    }

////    if(isnt_owner_info&isnt_agent_info){
////        saveUnitMobileOwnerAgentNotReg(line);//单位移动用户-使用人&经办人信息未登记
////    }
////    if(isnt_owner_info&isnt_unit_info){
////        saveUnitMobileOwnerUnitNotReg(line);//单位移动用户-使用人&单位信息未登记
////    }
////    if(isnt_agent_info&isnt_unit_info){
////        saveUnitMobileAgentUnitNotReg(line);//单位移动用户-经办人&单位信息未登记
////    }
////    if(isnt_owner_info&isnt_agent_info&isnt_unit_info){
////        saveUnitMobileOwnerAgentUnitAddNotReg(line);//单位移动用户-使用人&经办人&单位信息未登记
////    }
////    if(isnt_owner_info||isnt_agent_info||isnt_unit_info){
////        saveAllNotReg(line);//全量未登记
////    }
////    return true;

////}

////void UserFile::saveUnitFixedOwnerNotReg(QList<QString> line){
////    qDebug()<<"单位固话用户-使用人信息未登记"<<line;
////}
////void UserFile::saveUnitFixedAgentNotReg(QList<QString> line){
////    qDebug()<<"单位固话用户-经办人信息未登记"<<line;
////}
////void UserFile::saveUnitFixedUnitNotReg(QList<QString> line){
////    qDebug()<<"单位固话用户-单位信息未登记"<<line;
////}
////void UserFile::saveUnitFixedOwnerAgentNotReg(QList<QString> line){
////    qDebug()<<"单位固话用户-使用人&经办人信息未登记"<<line;
////}
////void UserFile::saveUnitFixedOwnerUnitNotReg(QList<QString> line){
////    qDebug()<<"单位固话用户-使用人&单位信息未登记"<<line;
////}
////void UserFile::saveUnitFixedAgentUnitNotReg(QList<QString> line){
////    qDebug()<<"单位固话用户-经办人&单位信息未登记"<<line;
////}
////void UserFile::saveUnitFixedOwnerAgentUnitAddNotReg(QList<QString> line){
////    qDebug()<<"单位固话用户-使用人&经办人&单位信息未登记"<<line;
////}

/////**
//// * @brief processUnitFixed
//// * @param line
//// * 		// 单位--固定电话
////        filename5ufok = str_files_out_path+ "单位固话用户-形式合规数据.ok";

////        filename21uf = str_files_out_path + "单位固话用户-200.nck";
////        filename22uf = str_files_out_path + "单位固话用户-经办人信息校验不合规.nck";
////        filename23uf = str_files_out_path + "单位固话用户-单位信息校验不合规.nck";
////        filename24uf = str_files_out_path + "单位固话用户-220.nck";
////        filename25uf = str_files_out_path + "单位固话用户-202.nck";
////        filename26uf = str_files_out_path + "单位固话用户-经办人&单位信息校验不合规.nck";
////        filename27uf = str_files_out_path + "单位固话用户-222.nck";
//// */
////bool UserFile::processUnitFixed(QList<QString> line){
////    bool isnt_owner_info = false;
////    if(processPersonFixed(line)){
////        saveUnitFixedOwnerNotReg(line);//单位固话用户-使用人信息未登记
////        isnt_owner_info = true;
////    }
////    bool isnt_agent_info = false;
////    if(isNull(line[getCol_num("代（经）办人姓名")])|
////       isNull(line[getCol_num("代（经）办人证件类型")])|
////       isNull(line[getCol_num("代（经）办人证件号码")])|
////       isNull(line[getCol_num("代（经）办人证件地址")])|
////       isNull(line[getCol_num("代（经）办人通讯地址")])){
////        saveUnitFixedAgentNotReg(line);//单位固话用户-经办人信息未登记
////        isnt_agent_info = true;

////    }
////    bool isnt_unit_info = false;
////    if(isNull(line[getCol_num("单位名称")])|
////       isNull(line[getCol_num("单位证件号码")])|
////       isNull(line[getCol_num("单位证件类型")])|
////       isNull(line[getCol_num("单位证件地址")])|
////       isNull(line[getCol_num("单位通讯地址")])){
////        saveUnitFixedUnitNotReg(line);//单位固话用户-单位信息未登记
////        isnt_unit_info = true;

////    }

////    if(isnt_owner_info&isnt_agent_info){
////        saveUnitFixedOwnerAgentNotReg(line);//单位固话用户-使用人&经办人信息未登记
////    }
////    if(isnt_owner_info&isnt_unit_info){
////        saveUnitFixedOwnerUnitNotReg(line);//单位固话用户-使用人&单位信息未登记
////    }
////    if(isnt_agent_info&isnt_unit_info){
////        saveUnitFixedAgentUnitNotReg(line);//单位固话用户-经办人&单位信息未登记
////    }
////    if(isnt_owner_info&isnt_agent_info&isnt_unit_info){
////        saveUnitFixedOwnerAgentUnitAddNotReg(line);//单位固话用户-使用人&经办人&单位信息未登记
////    }
////    if(isnt_owner_info||isnt_agent_info||isnt_unit_info){
////        saveAllNotReg(line);//全量未登记
////    }

////    return true;
////}
////void UserFile::saveTradeMobileAgentNotReg(QList<QString> line){
////    qDebug()<<"行业移动应用-经办人信息未登记"<<line;
////}
////void UserFile::saveTradeMobileUnitNotReg(QList<QString> line){
////    qDebug()<<"行业移动应用-单位信息未登记"<<line;
////}
////void UserFile::saveTradeMobileLiableNotReg(QList<QString> line){
////    qDebug()<<"行业移动应用-责任人信息未登记"<<line;
////}
////void UserFile::saveTradeMobileAgentUnitNotReg(QList<QString> line){
////    qDebug()<<"行业移动应用-经办人&单位信息未登记"<<line;
////}
////void UserFile::saveTradeMobileLiableAgentNotReg(QList<QString> line){
////    qDebug()<<"行业移动应用-责任人&经办人信息未登记"<<line;
////}
////void UserFile::saveTradeMobileLiableUnitNotReg(QList<QString> line){
////    qDebug()<<"行业移动应用-责任人&单位信息未登记"<<line;
////}
////void UserFile::saveTradeMobileLiableAgentUnitAddNotReg(QList<QString> line){
////    qDebug()<<"行业移动应用-责任人&经办人&单位信息未登记"<<line;
////}
/////**
//// * @brief processTradeMobile
//// * @param line
//// * 		// 行业--移动 应用
////        filename5imok = str_files_out_path+ "行业移动应用-形式合规数据.ok";

////        filename21im = str_files_out_path + "行业移动应用-经办人信息校验不合规.nck";
////        filename24im = str_files_out_path + "行业移动应用-经办人&单位信息校验不合规.nck";
////        filename25im = str_files_out_path + "行业移动应用-责任人&经办人信息校验不合规.nck";
////        filename26im = str_files_out_path + "行业移动应用-责任人&经办人&单位信息校验不合规.nck";
////        filename27im = str_files_out_path + "行业移动应用-单位信息校验不合规.nck";
////        filename28im = str_files_out_path + "行业移动应用-责任人信息校验不合规.nck";
////        filename29im = str_files_out_path + "行业移动应用-责任人&单位信息校验不合规.nck";
//// */
////bool UserFile::processTradeMobile(QList<QString> line){

////    bool isnt_agent_info = false;
////    if(isNull(line[getCol_num("代（经）办人姓名")])|
////       isNull(line[getCol_num("代（经）办人证件类型")])|
////       isNull(line[getCol_num("代（经）办人证件号码")])|
////       isNull(line[getCol_num("代（经）办人证件地址")])|
////       isNull(line[getCol_num("代（经）办人通讯地址")])){
////        saveTradeMobileAgentNotReg(line);//行业移动应用-经办人信息未登记
////        isnt_agent_info = true;

////    }
////    bool isnt_unit_info = false;
////    if(isNull(line[getCol_num("单位名称")])|
////       isNull(line[getCol_num("单位证件号码")])|
////       isNull(line[getCol_num("单位证件类型")])|
////       isNull(line[getCol_num("单位证件地址")])|
////       isNull(line[getCol_num("单位通讯地址")])){
////        saveTradeMobileUnitNotReg(line);//行业移动应用-单位信息未登记
////        isnt_unit_info = true;

////    }
////    bool isnt_liable_info = false;
////    if(isNull(line[getCol_num("责任人姓名")])|
////       isNull(line[getCol_num("责任人证件类型")])|
////       isNull(line[getCol_num("责任人证件号码")])|
////       isNull(line[getCol_num("责任人证件地址")])|
////       isNull(line[getCol_num("责任人通讯地址")])){
////        saveTradeMobileLiableNotReg(line);//行业移动应用-责任人信息未登记
////        isnt_liable_info = true;

////    }

////    if(isnt_agent_info&isnt_unit_info){
////        saveTradeMobileAgentUnitNotReg(line);//行业移动应用-经办人&单位信息未登记
////    }
////    if(isnt_liable_info&isnt_agent_info){
////        saveTradeMobileLiableAgentNotReg(line);//行业移动应用-责任人&经办人信息未登记
////    }
////    if(isnt_liable_info&isnt_unit_info){
////        saveTradeMobileLiableUnitNotReg(line);//行业移动应用-责任人&单位信息未登记
////    }
////    if(isnt_liable_info&isnt_agent_info&isnt_unit_info){
////        saveTradeMobileLiableAgentUnitAddNotReg(line);//行业移动应用-责任人&经办人&单位信息未登记
////    }
////    if(isnt_liable_info||isnt_agent_info||isnt_unit_info){
////        saveAllNotReg(line);//全量未登记
////    }
////        return true;
////}

////void UserFile::saveTradeFixedAgentNotReg(QList<QString> line){
////    qDebug()<<"行业固话应用-经办人信息未登记"<<line;
////}
////void UserFile::saveTradeFixedUnitNotReg(QList<QString> line){
////    qDebug()<<"行业固话应用-单位信息未登记"<<line;
////}
////void UserFile::saveTradeFixedAgentUnitNotReg(QList<QString> line){
////    qDebug()<<"行业固话应用-经办人&单位信息未登记"<<line;
////}

/////**
//// * @brief processTradeFixed
//// * @param line
//// * 		// 行业--固定 应用
////        filename5ifok = str_files_out_path+ "行业固话应用-形式合规数据.ok";

////        filename21if = str_files_out_path + "行业固话应用-经办人信息校验不合规.nck";
////        filename24if = str_files_out_path + "行业固话应用-经办人&单位信息校验不合规.nck";
////        filename27if = str_files_out_path + "行业固话应用-单位信息校验不合规.nck";

////        //filename_photo_2 = str_files_out_path + "现场照片核对记录-2.photo";
////        //filename_photo_1 = "e:/" + "现场照片核对记录-1.photo";

////        //filename_oneday_data = str_files_out_path + "抽取的一天的全量数据-1.data";
////        //filename_oneday_data2 = "e:/" + "抽取的一天的全量数据-2.data";

////        filename_one2five_pm = str_files_out_path + "个人移动一证五卡不合规.nck";
//// */
////bool UserFile::processTradeFixed(QList<QString> line){

////    bool isnt_agent_info = false;
////    if(isNull(line[getCol_num("代（经）办人姓名")])|
////       isNull(line[getCol_num("代（经）办人证件类型")])|
////       isNull(line[getCol_num("代（经）办人证件号码")])|
////       isNull(line[getCol_num("代（经）办人证件地址")])|
////       isNull(line[getCol_num("代（经）办人通讯地址")])){
////        saveTradeFixedAgentNotReg(line);//行业固话应用-经办人信息未登记
////        isnt_agent_info = true;

////    }
////    bool isnt_unit_info = false;
////    if(isNull(line[getCol_num("单位名称")])|
////       isNull(line[getCol_num("单位证件号码")])|
////       isNull(line[getCol_num("单位证件类型")])|
////       isNull(line[getCol_num("单位证件地址")])|
////       isNull(line[getCol_num("单位通讯地址")])){
////        saveTradeFixedUnitNotReg(line);//行业固话应用-单位信息未登记
////        isnt_unit_info = true;

////    }
////    if(isnt_agent_info&isnt_unit_info){
////        saveTradeFixedAgentUnitNotReg(line);//行业固话应用-经办人&单位信息未登记
////    }
////    if(isnt_agent_info||isnt_unit_info){
////        saveAllNotReg(line);//全量未登记
////    }

////    return true;

////}
/////**
//// * @brief processLine
//// * @param line 单行文本数据

////   //  0 个人移动， 1个人固话
////   //  2单位移动， 3单位固话
////   //  4行业移动，5行业固话
////   //  6个人移动代办，7个人固话代办
////        // 全量（个人+单位）
////        filename2 = str_files_out_path + "全量形式不合规.nck";
////        filename3 = str_files_out_path + "idcard.overdue";
////        filename4 = str_files_out_path + "格式异常数据.abnormal";
////        filename44 = str_files_out_path + "字段异常数据.abnormal";
////        filename5 = str_files_out_path+ "all.ok";
////        filename6 = str_files_out_path + "待挖掘记录-" + head_loop_num + ".txt";

////        filename55 = str_files_out_path + "tian.mao";
//// */
////void UserFile::processLine(QList<QString> line){
////    QString user_category = line[getCol_num("用户类型")];
////    QString business_type = line[getCol_num("用户业务类型")];
////    qDebug()<<"user_category is "<<user_category;
////    qDebug()<<"business_type is "<<business_type;
////    if(user_category=="个人客户"&&business_type=="移动手机号码"){//个人移动用户
////        processPersonMobile(line);
////    }
////    else if(user_category=="个人客户"&&business_type=="2"){//个人固话用户
////        processPersonFixed(line);
////    }
////    else if(user_category=="2"&&business_type=="移动手机号码"){//单位移动用户
////        processUnitMobile(line);
////    }
////    else if(user_category=="2"&&business_type=="2"){//单位固话用户
////        processUnitFixed(line);
////    }
////    else if(user_category=="3"&&business_type=="移动手机号码"){//行业移动用户
////        processTradeMobile(line);
////    }
////    else if(user_category=="3"&&business_type=="2"){//行业固话用户
////        processTradeFixed(line);
////    }
////}

/////*
//// * 代办人，机主年龄段可以配置
//// * 用户业务类型和用户类型可配置。
//// * 数据加翻页
//// */

////void processOneCard(QList<QList<QString>> lines){
////    qDebug()<<"processing 一证五号。"<<lines.at(0);
////}

////void UserFile::run(){
////    QList<QList<QString>> lines =  insertList(this->fileName);//文件数据装入内存
////    int line_id = 0;
////    while (!m_isStop&&line_id<lines.size()) {//按行处理数据
//////        QThread::sleep(1);
////        qDebug()<<QStringLiteral("开始处理数据第")<<line_id<<QStringLiteral("行");
////        if(lines[line_id].size()==COL_NUM)
////            processLine(lines[line_id]);
////        else
////            qDebug()<<line_id<<QStringLiteral("行数据列数不对");
////        line_id++;
////    }
////    if(!m_isStop){
////        processOneCard(lines);
////    }
////    isFinsh = true;
//////        Report *report = new Report;
//////        report->show();

////}
//////void UserFile::run1()
//////{
//////    qDebug()<<"file name is:"<<fileName;

//////    int i=0;
//////    while(i<2)
//////    {
//////        printMessage();
//////        QThread::sleep(1);
//////        i++;
//////    }
//////////    stopped = false;
//////    {
//////        QMutexLocker locker(&m_stopMutex);
//////        m_isStop = false;
//////    }
//////    int count = 0;
//////    QString str = QString("%1->%2,thread id:%3").arg(__FILE__).arg(__FUNCTION__).arg((int)(size_t)QThread::currentThreadId());
////////    emit message(str);
//////    int process = 0;
//////    while(1)
//////    {
//////        {
//////            QMutexLocker locker(&m_stopMutex);
//////            if(m_isStop)
//////                return;
//////        }
//////        printMessage();
//////        if(m_runCount == count)
//////        {
//////            break;
//////        }
//////        QThread::sleep(1);

//////        int pro = ((float)count / m_runCount) * 100;
//////        qDebug()<<"pro is "<<pro;
//////        if(pro != process)
//////        {
////////            qDebug()<<"process is "<<process;
//////            printMessage();
//////            process = pro;
//////            printMessage();
////////            emit progress(((float)count / m_runCount) * 100);
////////            emit message(QString("Object::run times:%1,m_runCount:%2").arg(count).arg(m_runCount2));
//////        }
//////        ++count;
//////    }
//////}

////void UserFile::printMessage(){
////    qDebug()<<QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)(size_t)QThread::currentThreadId());
////}

////void UserFile::stop()
////{
////    stopped = true;
////    m_isStop = true;
////}


////enum col_name11
////{
////    owner_name,  //"机主", "姓名"
////    owner_type,  //"机主", "证件类型"
////    owner_num,  //"机主", "证件号码"
////    owner_add,  //"机主", "证件地址"
////    owner_mailadd,  //"机主", "通讯地址"
////    owner_loadadd,  //"机主", "装机地址"

////    agent_name,  //"代（经）办人", "姓名"
////    agent_type,  //"代（经）办人", "证件类型"
////    agent_num,  //"代（经）办人", "证件号码"
////    agent_add,  //"代（经）办人", "证件地址"
////    agent_mailadd,  //"代（经）办人", "通讯地址"

////    unitliable_name,  //"责任人", "姓名"
////    unitliable_type,  //"责任人", "证件类型"
////    unitliable_num,  //"责任人", "证件号码"
////    unitliable_add,  //"责任人", "证件地址"
////    unitliable_mailadd,  //"责任人", "通讯地址"

////    unit_name,  //"单位或行业", "单位名称"
////    unit_num,  //"单位或行业", "单位证件号码"
////    unit_type,  //"单位或行业", "单位证件类型"
////    unit_add,  //"单位或行业", "单位证件地址"
////    unit_mailadd,  //"单位或行业", "单位通讯地址"
////    unit_loadadd,  //"单位或行业", "单位装机地址"

////    msisdn_num,  //"电话卡信息", "MSISDN号码"
////    reg_act_time,  //"电话卡信息", "登记激活时间"
////    phone_state,  //"电话卡信息", "号码状态"
////    business_type,  //"电话卡信息", "用户业务类型"

////    outlets_num,  //"营业网点信息", "网点编号"
////    outlets_name,  //"营业网点信息", "网点名称"
////    outlets_address,  //"营业网点信息", "网点地址"
////    outlets_district,  //"营业网点信息", "网点所在区县"
////    outlets_type,  //"营业网点信息", "网点类型"
////    open_business_num,  //"营业网点信息", "开通商编号"

////    bill_num,  //"支付信息", "交易流水账单号"
////    user_account,  //"支付信息", "交易平台用户账号"
////    payment_account,  //"支付信息", "用户交易的银行卡卡号或第三方支付账号名称"
////    payment_time,  //"支付信息", "支付时间"
////    owner_card_pic_name,  //"支付信息", "机主证件电子复印件图片名称"
////    agent_card_pic_name,  //"支付信息", "代办人证件电子复印件图片名称"

////    user_category,  //"用户类型", "用户类型"
////    channel_type,  //"渠道类型", "渠道类型"
////    business_use_state,  //"使用状态", "使用状态"
////    reserved_field,  //"预留字段", "预留字段"

////};


//////分析文件
////bool UserFile::analysisData(QList<QList<QString>> list){

////    writeLog("需处理文件：\n");
////    QList<QString> line;;
////    for(int i=0;i<list.size();i++){
////        writeLog(QString("文件第").append(QString::number(i+1,10)).append("行:\n"));
////        line=list.at(i);
////        int col_count = COL_NUM;

////        if(line.size()<col_count){
////            qDebug()<<"文件出错，本行列数不够，程序将退出，请检查文件格式。";
////            return false;
////        }
////        qDebug()<<"用户名是"<<line[owner_name];
//////        for(int j=0;j<line.size();j++){
//////            qDebug()<<line[j];
//////        }


////    //如果业务状态为“不在网”,不计入统计范围
////    // 如果业务状态为“非实名停机”,不计入统计范围
////    //2013年9月1日后~2015年1月1日
////    if(isNull(line[owner_name])){
////        //个人移动用户-用户姓名未登记
////        writeFile("个人移动用户-用户姓名未登记",line);
////        writeFile("全量未登记.nreg",line);
////        qDebug()<<"个人移动用户-用户姓名未登记";
////        qDebug()<<"全量未登记.nreg";
////    }
////    else if(isNull(line[owner_type])){
////        //个人移动用户-证件类型未登记
////        qDebug()<<"个人移动用户-证件类型未登记";
////        qDebug()<<"全量未登记.nreg";
////    }
////    else if(isNull(line[owner_num])){
////        //个人移动用户-证件号码未登记
////        qDebug()<<"个人移动用户-证件号码未登记";
////        qDebug()<<"全量未登记.nreg";
////    }
////    else if(isNull(line[owner_add])){
////        //个人移动用户-证件地址未登记
////        qDebug()<<"个人移动用户-证件地址未登记";
////        qDebug()<<"全量未登记.nreg";
////    }
////    else if(isNull(line[owner_name])&&isNull(line[owner_type])){
////        //"个人移动用户-用户姓名&证件号码未登记.nreg"

////    }
////    else if(isNull(line[owner_name])&&isNull(line[owner_add])){
////        //"个人移动用户-用户姓名&证件地址未登记.nreg"

////    }
////    else if(isNull(line[owner_add])&&isNull(line[owner_type])){
////        //"个人移动用户-证件号码&证件地址未登记.nreg"

////    }
////    else if(isNull(line[owner_name])&&isNull(line[owner_add])&&isNull(line[owner_type])){
////        //"个人移动用户-用户姓名&证件号码&证件地址未登记.nreg"

////    }

////    //个人移动用户-形式合规数据.


//////    // 全量（个人+单位）
//////    filename1 = str_files_out_path + "全量未登记.nreg";
//////    filename2 = str_files_out_path + "全量形式不合规.nck";
//////    filename3 = str_files_out_path + "idcard.overdue";
//////    filename4 = str_files_out_path + "格式异常数据.abnormal";
//////    filename44 = str_files_out_path + "字段异常数据.abnormal";
//////    filename5 = str_files_out_path+ "all.ok";
//////    filename6 = str_files_out_path + "待挖掘记录-" + head_loop_num + ".txt";

//////    filename55 = str_files_out_path + "tian.mao";
//////    // 个人--移动电话
//////    filename5pmok = str_files_out_path+ "个人移动用户-形式合规数据.ok";


//////    filename20pm = str_files_out_path + "个人移动用户-证件类型校验不合规.nck";
//////    filename21pm = str_files_out_path + "个人移动用户-用户姓名校验不合规.nck";
//////    filename22pm = str_files_out_path + "个人移动用户-证件号码校验不合规.nck";
//////    filename23pm = str_files_out_path + "个人移动用户-证件地址校验不合规.nck";
//////    filename24pm = str_files_out_path + "个人移动用户-用户姓名&证件号码校验不合规.nck";
//////    filename25pm = str_files_out_path + "个人移动用户-用户姓名&证件地址校验不合规.nck";
//////    filename26pm = str_files_out_path + "个人移动用户-证件号码&证件地址校验不合规.nck";
//////    filename27pm = str_files_out_path + "个人移动用户-用户姓名&证件号码&证件地址校验不合规.nck";

//////    // 个人-固定电话
//////    filename5pfok = str_files_out_path+ "个人固话用户-形式合规数据.ok";

//////    filename10pf = str_files_out_path + "个人固话用户-证件类型未登记.nreg";
//////    filename11pf = str_files_out_path + "个人固话用户-用户姓名未登记.nreg";
//////    filename12pf = str_files_out_path + "个人固话用户-证件号码未登记.nreg";
//////    filename13pf = str_files_out_path + "个人固话用户-证件地址未登记.nreg";
//////    filename14pf = str_files_out_path + "个人固话用户-用户姓名&证件号码未登记.nreg";
//////    filename15pf = str_files_out_path + "个人固话用户-用户姓名&证件地址未登记.nreg";
//////    filename16pf = str_files_out_path + "个人固话用户-证件号码&证件地址未登记.nreg";
//////    filename17pf = str_files_out_path + "个人固话用户-用户姓名&证件号码&证件地址未登记.nreg";

//////    filename20pf = str_files_out_path + "个人固话用户-证件类型校验不合规.nck";
//////    filename21pf = str_files_out_path + "个人固话用户-用户姓名校验不合规.nck";
//////    filename22pf = str_files_out_path + "个人固话用户-证件号码校验不合规.nck";
//////    filename23pf = str_files_out_path + "个人固话用户-证件地址校验不合规.nck";
//////    filename24pf = str_files_out_path + "个人固话用户-用户姓名&证件号码校验不合规.nck";
//////    filename25pf = str_files_out_path + "个人固话用户-用户姓名&证件地址校验不合规.nck";
//////    filename26pf = str_files_out_path + "个人固话用户-证件号码&证件地址校验不合规.nck";
//////    filename27pf = str_files_out_path + "个人固话用户-用户姓名&证件号码&证件地址校验不合规.nck";

//////    filename1pma = str_files_out_path + "个人移动用户-代办人信息未登记.nreg";
//////    filename1pfa = str_files_out_path + "个人固话用户-代办人信息未登记.nreg";
//////    filename2pma = str_files_out_path + "个人移动用户-代办人信息校验不合规.nck";
//////    filename2pfa = str_files_out_path + "个人固话用户-代办人信息校验不合规.nck";

//////    // 单位 -- 移动
//////    filename5umok = str_files_out_path+ "单位移动用户-形式合规数据.ok";

//////    filename11um = str_files_out_path + "单位移动用户-使用人信息未登记.nreg";
//////    filename12um = str_files_out_path + "单位移动用户-经办人信息未登记.nreg";
//////    filename13um = str_files_out_path + "单位移动用户-单位信息未登记.nreg";
//////    filename14um = str_files_out_path + "单位移动用户-使用人&经办人信息未登记.nreg";
//////    filename15um = str_files_out_path + "单位移动用户-使用人&单位信息未登记.nreg";
//////    filename16um = str_files_out_path + "单位移动用户-经办人&单位信息未登记.nreg";
//////    filename17um = str_files_out_path + "单位移动用户-使用人&经办人&单位信息未登记.nreg";

//////    filename21um = str_files_out_path + "单位移动用户-使用人信息校验不合规.nck";
//////    filename22um = str_files_out_path + "单位移动用户-经办人信息校验不合规.nck";
//////    filename23um = str_files_out_path + "单位移动用户-单位信息校验不合规.nck";
//////    filename24um = str_files_out_path + "单位移动用户-使用人&经办人信息校验不合规.nck";
//////    filename25um = str_files_out_path + "单位移动用户-使用人&单位信息校验不合规.nck";
//////    filename26um = str_files_out_path + "单位移动用户-经办人&单位信息校验不合规.nck";
//////    filename27um = str_files_out_path + "单位移动用户-使用人&经办人&单位信息校验不合规.nck";


//////    // 单位--固定电话
//////    filename5ufok = str_files_out_path+ "单位固话用户-形式合规数据.ok";

//////    filename11uf = str_files_out_path + "单位固话用户-100.nreg";
//////    filename12uf = str_files_out_path + "单位固话用户-经办人信息未登记.nreg";
//////    filename13uf = str_files_out_path + "单位固话用户-单位信息未登记.nreg";
//////    filename14uf = str_files_out_path + "单位固话用户-110.nreg";
//////    filename15uf = str_files_out_path + "单位固话用户-101.nreg";
//////    filename16uf = str_files_out_path + "单位固话用户-经办人&单位信息未登记.nreg";
//////    filename17uf = str_files_out_path + "单位固话用户-111.nreg";

//////    filename21uf = str_files_out_path + "单位固话用户-200.nck";
//////    filename22uf = str_files_out_path + "单位固话用户-经办人信息校验不合规.nck";
//////    filename23uf = str_files_out_path + "单位固话用户-单位信息校验不合规.nck";
//////    filename24uf = str_files_out_path + "单位固话用户-220.nck";
//////    filename25uf = str_files_out_path + "单位固话用户-202.nck";
//////    filename26uf = str_files_out_path + "单位固话用户-经办人&单位信息校验不合规.nck";
//////    filename27uf = str_files_out_path + "单位固话用户-222.nck";

//////    // 行业--移动 应用
//////    filename5imok = str_files_out_path+ "行业移动应用-形式合规数据.ok";
//////    filename11im = str_files_out_path + "行业移动应用-经办人信息未登记.nreg";
//////    filename14im = str_files_out_path + "行业移动应用-经办人&单位信息未登记.nreg";
//////    filename15im = str_files_out_path + "行业移动应用-责任人&经办人信息未登记.nreg";
//////    filename16im = str_files_out_path + "行业移动应用-责任人&经办人&单位信息未登记.nreg";
//////    filename17im = str_files_out_path + "行业移动应用-单位信息未登记.nreg";
//////    filename18im = str_files_out_path + "行业移动应用-责任人信息未登记.nreg";
//////    filename19im = str_files_out_path + "行业移动应用-责任人&单位信息未登记.nreg";

//////    filename21im = str_files_out_path + "行业移动应用-经办人信息校验不合规.nck";
//////    filename24im = str_files_out_path + "行业移动应用-经办人&单位信息校验不合规.nck";
//////    filename25im = str_files_out_path + "行业移动应用-责任人&经办人信息校验不合规.nck";
//////    filename26im = str_files_out_path + "行业移动应用-责任人&经办人&单位信息校验不合规.nck";
//////    filename27im = str_files_out_path + "行业移动应用-单位信息校验不合规.nck";
//////    filename28im = str_files_out_path + "行业移动应用-责任人信息校验不合规.nck";
//////    filename29im = str_files_out_path + "行业移动应用-责任人&单位信息校验不合规.nck";

//////    // 行业--固定 应用
//////    filename5ifok = str_files_out_path+ "行业固话应用-形式合规数据.ok";
//////    filename11if = str_files_out_path + "行业固话应用-经办人信息未登记.nreg";
//////    filename14if = str_files_out_path + "行业固话应用-经办人&单位信息未登记.nreg";
//////    filename17if = str_files_out_path + "行业固话应用-单位信息未登记.nreg";

//////    filename21if = str_files_out_path + "行业固话应用-经办人信息校验不合规.nck";
//////    filename24if = str_files_out_path + "行业固话应用-经办人&单位信息校验不合规.nck";
//////    filename27if = str_files_out_path + "行业固话应用-单位信息校验不合规.nck";

//////    //filename_photo_2 = str_files_out_path + "现场照片核对记录-2.photo";
//////    //filename_photo_1 = "e:/" + "现场照片核对记录-1.photo";

//////    //filename_oneday_data = str_files_out_path + "抽取的一天的全量数据-1.data";
//////    //filename_oneday_data2 = "e:/" + "抽取的一天的全量数据-2.data";

//////    filename_one2five_pm = str_files_out_path + "个人移动一证五卡不合规.nck";
////    }

////    return false;
////}

//////写日志
////bool UserFile::writeLog(QString msg){
////    qDebug()<<msg;
////    return false;
////}

//////输出文件
////bool UserFile::writeFile(QString filename,QList<QString> list){
////    QFile file(filename);
////    QString line = "";
////    for(QString str:list){
////        line += str;
////    }
////    if(file.open(QFile::WriteOnly|QFile::Truncate)){
////        QTextStream out(&file);
////        out<<line;
////    }

////    file.close();
////    qDebug()<<"写入文件"<<filename;
////    return false;
////}
////==============================================userDb.cpp+++++++++++++
//#include "userdb.h"

//UserDb::UserDb()
//{
//     stopped = false;
////     xmlConfig = new XMLConfigReader();
//     QList<QList<QString>> lls = xmlConfig->readAutoid();
//     delimeter = xmlConfig->readDelimiterValue();
//     qDebug()<<"delimeter="<<delimeter;
//     userType=xmlConfig->readUserType();
//     QString name;
//     report = new Report();
////    report->init();
//    int num;
//    bool ok;
//    //初始化列名
//    for(int i=0; i<lls.size(); i++){
//        name = lls.at(i).at(1);
//        num = lls.at(i).at(2).toInt(&ok,10);
//        qDebug()<<"col name is "<<name<<" num is "<<num;
//        col_name_map.insert(name,num);
//    }
////    //初始化用户类型为固定电话
////    bizTypeFixed = readValueToString("业务类型固定");//用户业务类型固定，除固定外全是移动号码

////    //初始化个人合规证件类型
////    personType = readValueToString("个人证件居民身份证");
////    personType += readValueToString("个人证件临时居民身份证");
////    personType += readValueToString("个人证件户口薄");
////    personType += readValueToString("个人证件中国人民解放军军人身份证件");
////    personType += readValueToString("个人证件中国人民武装警察身份证件");
////    personType += readValueToString("个人证件港澳居民来往内地通行证");
////    personType += readValueToString("个人证件台湾居民来往大陆通行证");
////    personType += readValueToString("个人证件外国公民护照");
////    personType += readValueToString("个人证件法律、行政法规和国家规定的其他有效身份证件");

//    //初始化用户类型为固定电话
//    bizTypeFixed = readValueToList(bizTypeFixed, "业务类型固定");//用户业务类型固定，除固定外全是移动号码

//    //初始化个人合规证件类型
//    personType = readValueToList(personType, "个人证件居民身份证");
//    personType = readValueToList(personType, "个人证件临时居民身份证");
//    personType = readValueToList(personType, "个人证件户口薄");
//    personType = readValueToList(personType, "个人证件中国人民解放军军人身份证件");
//    personType = readValueToList(personType, "个人证件中国人民武装警察身份证件");
//    personType = readValueToList(personType, "个人证件港澳居民来往内地通行证");
//    personType = readValueToList(personType, "个人证件台湾居民来往大陆通行证");
//    personType = readValueToList(personType, "个人证件外国公民护照");
//    personType = readValueToList(personType, "个人证件法律、行政法规和国家规定的其他有效身份证件");

//    //初始化单位合规证件类型
//    unitType  = readValueToList(unitType, "单位证件组织机构代码证");


//    QList<QString> queryList;
//    queryList.append("maxlimit");
//    queryList.append("personNameLen_min");
//    queryList.append("personNameLen_max");
//    queryList.append("personNamePermit_char");
//    queryList.append("personCardtypeTime_interval");
//    queryList.append("personCard_numLen_min");
//    queryList.append("personCard_numLen_max");
//    queryList.append("personCard_addLen_min");
//    queryList.append("personCard_addLen_max");
//    queryList.append("unitNameLen_min");
//    queryList.append("unitNameLen_max");
//    queryList.append("unitCardtypeTime_interval");
//    queryList.append("unitCard_numLen_min");
//    queryList.append("unitCard_numLen_max");
//    queryList.append("unitCard_addLen_min");
//    queryList.append("unitCard_addLen_max");

//    QMap<QString,QString> map = xmlConfig->readCommonRuleValue(queryList);
////    bool ok = true;
//    maxlimit = map.value("maxlimit");
//    personNameMin = map.value("personNameLen_min").compare("-")?map.value("personNameLen_min").toInt(&ok,10):-1;
//    personNameMax = map.value("personNameLen_max").compare("-")?map.value("personNameLen_max").toInt(&ok,10):-1;
//    personNamePermit = map.value("personNamePermit_char");
//    personIntervalTime = map.value("personCardtypeTime_interval");
//    personNumMin = map.value("personCard_numLen_min").compare("-")?map.value("personCard_numLen_min").toInt(&ok,10):-1;
//    personNumMax = map.value("personCard_numLen_max").compare("-")?map.value("personCard_numLen_max").toInt(&ok,10):-1;
//    personAddMin = map.value("personCard_addLen_min").compare("-")?map.value("personCard_addLen_min").toInt(&ok,10):-1;
//    personAddMax = map.value("personCard_addLen_max").compare("-")?map.value("personCard_addLen_max").toInt(&ok,10):-1;
//    unitNameMin = map.value("unitNameLen_min").compare("-")?map.value("unitNameLen_min").toInt(&ok,10):-1;
//    unitNameMax = map.value("unitNameLen_max").compare("-")?map.value("unitNameLen_max").toInt(&ok,10):-1;
//    unitIntervalTime = map.value("unitCardtypeTime_interval");
//    unitNumMin = map.value("unitCard_numLen_min").compare("-")?map.value("unitCard_numLen_min").toInt(&ok,10):-1;
//    unitNumMax = map.value("unitCard_numLen_max").compare("-")?map.value("unitCard_numLen_max").toInt(&ok,10):-1;
//    unitAddMin = map.value("unitCard_addLen_min").compare("-")?map.value("unitCard_addLen_min").toInt(&ok,10):-1;
//    unitAddMax = map.value("unitCard_addLen_max").compare("-")?map.value("unitCard_addLen_max").toInt(&ok,10):-1;
//    //初始化个人用户姓名不合规
//    personNameRule = readValueToList(personNameRule, "个人用户姓名comon-rule");
//    personNameRule = readValueToList(personNameRule, "个人用户姓名match-rule");
//    //初始化单位/行业用户名称不合规
//    unitNameRule = readValueToList(unitNameRule, "行业用户姓名comon-rule");
//    unitNameRule = readValueToList(unitNameRule, "行业用户姓名match-rule");
//    //初始化个人证件号码不合规
//    //初始化单位证件号码不合规
//    numRule = readValueToList(numRule, "证件号码comon-rule");
//    numRule = readValueToList(numRule, "证件号码match-rule");
//    //初始化个人证件地址不合规
//    //初始化单位证件地址不合规
//    addRule = readValueToList(addRule, "证件地址addr-rule");
//    addRule = readValueToList(addRule, "证件地址match-rule");

//    nonRealName = readValueToList(nonRealName, "业务状态非实名制停机");
//    leaveNet = readValueToList(leaveNet, "业务状态不在网");
//}

//QString UserDb::readValueToString(QString query){
//    QString rtn = "";
//    QList<QString> list = xmlConfig->readValue(query);
//    for(int i=0; i<list.size(); i++){
//        rtn.append(list.at(i));
//    }
//    return rtn;
//}

//QList<QString> UserDb::readValueToList(QList<QString> inList, QString query){

//    QList<QString> list = xmlConfig->readValue(query);
//    for(int i=0; i<list.size(); i++){
//        inList.append(list.at(i));
//    }
//    return inList;
//}

//UserDb::~UserDb()
//{
//    delete report;
//    delete xmlConfig;
//}
//void UserDb::printMessage(){
//   // qDebug()<<QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId());
//}

//void UserDb::start()
//{
//    stopped = false;
//}

//void UserDb::stop()
//{
//    stopped = true;
//}

//void UserDb::run()
//{
//    countData();
//    qDebug()<<"run begin"<<stopped;
//     emit message("waiting...");
//////    todo
////    qDebug()<<"bool UserDb::insertDb(QString filename)"<<insertDb(filename);//"C:\\test.txt");// /Users/zhangxianjin/qtcode/test.txt");//test_data.txt"); //
////    QThread::sleep(10);
//    createReport();
//    emit message("finished.");
//}

//void UserDb::createReport(){
//    QSqlQuery query;
//    qDebug()<<"drop report:"<<query.exec("drop table report");
//    qDebug()<<"create report:"<<query.exec("create table report(id int primary key,allData int,allNotReg int,formatNok int,fieldNok int,allOk int,personMobileOk int,"
//                                           "personMobileOwnerTypeNotReg int,personMobileOwnerNameNotReg int,personMobileOwnerNumNotReg int,personMobileOwnerAddNotReg int,personMobileOwnerNameNumNotReg int,"
//                                           "personMobileOwnerNameAddNotReg int,personMobileOwnerNumAddNotReg int,personMobileOwnerNameNumAddNotReg int,personMobileOwnerTypeNok int,personMobileOwnerNameNok int,"
//                                           "personMobileOwnerNumNok int,personMobileOwnerAddNok int,personMobileOwnerNameNumNok int,personMobileOwnerNameAddNok int,personMobileOwnerNumAddNok int,"
//                                           "personMobileOwnerNameNumAddNok int,personFixedOk int,personFixedOwnerTypeNotReg int,personFixedOwnerNameNotReg int,personFixedOwnerNumNotReg int,"
//                                           "personFixedOwnerAddNotReg int,personFixedOwnerNameNumNotReg int,personFixedOwnerNameAddNotReg int,personFixedOwnerNumAddNotReg int,personFixedOwnerNameNumAddNotReg int,"
//                                           "personFixedOwnerTypeNok int,personFixedOwnerNameNok int,personFixedOwnerNumNok int,personFixedOwnerAddNok int,personFixedOwnerNameNumNok int,"
//                                           "personFixedOwnerNameAddNok int,personFixedOwnerNumAddNok int,personFixedOwnerNameNumAddNok int,personMobileAgentNotReg int,personFixedAgentNotReg int,"
//                                           "personMobileAgentNok int,personFixedAgentNok int,unitMobileOk int,unitMobileOwnerNotReg int,unitMobileAgentNotReg int,unitMobileUnitNotReg int,"
//                                           "unitMobileOwnerAgentNotReg int,unitMobileOwnerUnitNotReg int,unitMobileAgentUnitNotReg int,unitMobileOwnerAgentUnitNotReg int,unitMobileOwnerNok int,"
//                                           "unitMobileAgentNok int,unitMobileUnitNok int,unitMobileOwnerAgentNok int,unitMobileOwnerUnitNok int,unitMobileAgentUnitNok int,unitMobileOwnerAgentUnitNok int,"
//                                           "unitFixedOk int,unitFixedAgentNotReg int,unitFixedUnitNotReg int,unitFixedAgentUnitNotReg int,unitFixedAgentNok int,unitFixedUnitNok int,"
//                                           "unitFixedAgentUnitNok int,tradeMobileOk int,tradeMobileAgentNotReg int,tradeMobileAgentUnitNotReg int,tradeMobileLiableAgentNotReg int,"
//                                           "tradeMobileLiableAgentUnitNotReg int,tradeMobileUnitNotReg int,tradeMobileLiableNotReg int,tradeMobileLiableUnitNotReg int,tradeMobileAgentNok int,"
//                                           "tradeMobileAgentUnitNok int,tradeMobileLiableAgentNok int,tradeMobileLiableAgentUnitNok int,tradeMobileUnitNok int,tradeMobileLiableNok int,"
//                                           "tradeMobileLiableUnitNok int,tradeFixedOk int, tradeFixedAgentNotReg int,tradeFixedAgentUnitNotReg int,tradeFixedUnitNotReg int,tradeFixedAgentNok int,"
//                                           "tradeFixedAgentUnitNok int,tradeFixedUnitNok int,personMobileOneCard int)");
//    qDebug()<<"insert report is:"<<query.exec("insert into report (id) values (1)");
//    QString sql;
//    //总量
//    if(!report->allData){
//       sql = "update report set allData="+QString::number(report->allData);
//    }
//    qDebug()<< "update allData is:"<<query.exec(sql)<<sql;


//    //全量未登记
//    sql = "update report set allNotReg="+QString::number(report->allNotReg);
//    qDebug()<<"update allNotReg is:"<<query.exec(sql)<<sql;
//    //格式异常数据
//        sql = "update report set formatNok="+QString::number(report->formatNok);
//        qDebug()<<"update formatNok is:"<<query.exec(sql)<<sql;
//    //字段异常数据
//        sql = "update report set fieldNok="+QString::number(report->fieldNok);
//        qDebug()<<"update fieldNok is:"<<query.exec(sql)<<sql;
//    //all.ok
//         sql = "update report set allOk="+QString::number(report->allOk);
//         qDebug()<<"update allOk is:"<<query.exec(sql)<<sql;

//    //个人移动用户-形式合规数据
//         sql = "update report set personMobileOk="+QString::number(report->personMobileOk);
//         qDebug()<<"update personMobileOk is:"<<query.exec(sql)<<sql;

//    //个人移动用户-证件类型未登记

//         sql = "update report set personMobileOwnerTypeNotReg="+QString::number(report->personMobileOwnerTypeNotReg);
//         qDebug()<<"update personMobileOwnerTypeNotReg is:"<<query.exec(sql)<<sql;

//    //个人移动用户-用户姓名未登记
//             sql = "update report set personMobileOwnerNameNotReg="+QString::number(report->personMobileOwnerNameNotReg);
//         qDebug()<<"update personMobileOwnerTypeNotReg is:"<<query.exec(sql)<<sql;

//    //个人移动用户-证件号码未登记
//             sql = "update report set personMobileOwnerNumNotReg="+QString::number(report->personMobileOwnerNumNotReg);
//         qDebug()<<"update personMobileOwnerTypeNotReg is:"<<query.exec(sql)<<sql;

//    //个人移动用户-证件地址未登记
//             sql = "update report set personMobileOwnerAddNotReg="+QString::number(report->personMobileOwnerAddNotReg);
//         qDebug()<<"update personMobileOwnerAddNotReg is:"<<query.exec(sql)<<sql;

//    //个人移动用户-用户姓名&amp;证件号码未登记
//             sql = "update report set personMobileOwnerNameNumNotReg="+QString::number(report->personMobileOwnerNameNumNotReg);
//         qDebug()<<"update personMobileOwnerNameNumNotReg is:"<<query.exec(sql)<<sql;

//    //个人移动用户-用户姓名&证件地址未登记
//             sql = "update report set personMobileOwnerNameAddNotReg="+QString::number(report->personMobileOwnerNameAddNotReg);
//         qDebug()<<"update personMobileOwnerNameAddNotReg is:"<<query.exec(sql)<<sql;

//    //个人移动用户-证件号码&证件地址未登记
//             sql = "update report set personMobileOwnerNumAddNotReg="+QString::number(report->personMobileOwnerNumAddNotReg);
//         qDebug()<<"update personMobileOwnerNumAddNotReg is:"<<query.exec(sql)<<sql;

//    //个人移动用户-用户姓名&证件号码&证件地址未登记
//             sql = "update report set personMobileOwnerNameNumAddNotReg="+QString::number(report->personMobileOwnerNameNumAddNotReg);
//         qDebug()<<"update personMobileOwnerNameNumAddNotReg is:"<<query.exec(sql)<<sql;

//    //个人移动用户-证件类型校验不合规
//         sql = "update report set personMobileOwnerTypeNok="+QString::number(report->personMobileOwnerTypeNok);
//         qDebug()<<"update personMobileOwnerTypeNok is:"<<query.exec(sql)<<sql;

//    //个人移动用户-用户姓名校验不合规
//         sql = "update report set personMobileOwnerNameNok="+QString::number(report->personMobileOwnerNameNok);
//         qDebug()<<"update personMobileOwnerNameNok is:"<<query.exec(sql)<<sql;

//    //个人移动用户-证件号码校验不合规
//         sql = "update report set personMobileOwnerNumNok="+QString::number(report->personMobileOwnerNumNok);
//         qDebug()<<"update personMobileOwnerNumNok is:"<<query.exec(sql)<<sql;

//    //个人移动用户-证件地址校验不合规
//         sql = "update report set personMobileOwnerAddNok="+QString::number(report->personMobileOwnerAddNok);
//         qDebug()<<"update personMobileOwnerAddNok is:"<<query.exec(sql)<<sql;

//    //个人移动用户-用户姓名&amp;证件号码校验不合规
//         sql = "update report set personMobileOwnerNameNumNok="+QString::number(report->personMobileOwnerNameNumNok);
//         qDebug()<<"update personMobileOwnerNameNumNok is:"<<query.exec(sql)<<sql;

//    //个人移动用户-用户姓名&amp;证件地址校验不合规
//         sql = "update report set personMobileOwnerNameAddNok="+QString::number(report->personMobileOwnerNameAddNok);
//         qDebug()<<"update personMobileOwnerNameAddNok is:"<<query.exec(sql)<<sql;

//    //个人移动用户-证件号码&amp;证件地址校验不合规
//         sql = "update report set personMobileOwnerNumAddNok="+QString::number(report->personMobileOwnerNumAddNok);
//         qDebug()<<"update personMobileOwnerNumAddNok is:"<<query.exec(sql)<<sql;

//    //个人移动用户-用户姓名&amp;证件号码&amp;证件地址校验不合规
//         sql = "update report set personMobileOwnerNameNumAddNok="+QString::number(report->personMobileOwnerNameNumAddNok);
//         qDebug()<<"update personMobileOwnerNameNumAddNok is:"<<query.exec(sql)<<sql;

//    //个人固话用户-形式合规数据
//         sql = "update report set personFixedOk="+QString::number(report->personFixedOk);
//         qDebug()<<"update personFixedOk is:"<<query.exec(sql)<<sql;

//    //个人固话用户-证件类型未登记
//             sql = "update report set personFixedOwnerTypeNotReg="+QString::number(report->personFixedOwnerTypeNotReg);
//         qDebug()<<"update personFixedOwnerTypeNotReg is:"<<query.exec(sql)<<sql;

////    //个人固话用户-用户姓名未登记
//             sql = "update report set personFixedOwnerNameNotReg="+QString::number(report->personFixedOwnerNameNotReg);
//         qDebug()<<"update personFixedOwnerNameNumNotReg is:"<<query.exec(sql)<<sql;

////    //个人固话用户-证件号码未登记
//             sql = "update report set personFixedOwnerNumNotReg="+QString::number(report->personFixedOwnerNumNotReg);
//         qDebug()<<"update personFixedOwnerNumNotReg is:"<<query.exec(sql)<<sql;

////    //个人固话用户-证件地址未登记
//             sql = "update report personFixedOwnerAddNotReg="+QString::number(report->personFixedOwnerAddNotReg);
//         qDebug()<<"update personFixedOwnerAddNotReg is:"<<query.exec(sql)<<sql;

////    //个人固话用户-用户姓名&amp;证件号码未登记
//             sql = "update report set personFixedOwnerNameNumNotReg="+QString::number(report->personFixedOwnerNameNumNotReg);
//         qDebug()<<"update personFixedOwnerNameNumNotReg is:"<<query.exec(sql)<<sql;

////    //个人固话用户-用户姓名&amp;证件地址未登记
//             sql = "update report set personFixedOwnerNameAddNotReg="+QString::number(report->personFixedOwnerNameAddNotReg);
//         qDebug()<<"update personFixedOwnerNameAddNotReg is:"<<query.exec(sql)<<sql;

////    //个人固话用户-证件号码&amp;证件地址未登记
//             sql = "update report set personFixedOwnerNumAddNotReg="+QString::number(report->personFixedOwnerNumAddNotReg);
//         qDebug()<<"update personFixedOwnerNumAddNotReg is:"<<query.exec(sql)<<sql;

////    //个人固话用户-用户姓名&amp;证件号码&amp;证件地址未登记
//         sql = "update report set personFixedOwnerNameNumAddNotReg="+QString::number(report->personFixedOwnerNameNumAddNotReg);
//         qDebug()<<"update personFixedOwnerNameNumAddNotReg is:"<<query.exec(sql)<<sql;

//    //个人固话用户-证件类型校验不合规
//         sql = "update report set personFixedOwnerTypeNok="+QString::number(report->personFixedOwnerTypeNok);
//         qDebug()<<"update personFixedOwnerTypeNok is:"<<query.exec(sql)<<sql;

//    //个人固话用户-用户姓名校验不合规
//         sql = "update report set personFixedOwnerNameNok="+QString::number(report->personFixedOwnerNameNok);
//         qDebug()<<"update personFixedOwnerNameNok is:"<<query.exec(sql)<<sql;

//    //个人固话用户-证件号码校验不合规
//         sql = "update report set personFixedOwnerNumNok="+QString::number(report->personFixedOwnerNumNok);
//         qDebug()<<"update personFixedOwnerNumNok is:"<<query.exec(sql)<<sql;

//    //个人固话用户-证件地址校验不合规
//         sql = "update report set personFixedOwnerAddNok="+QString::number(report->personFixedOwnerAddNok);
//         qDebug()<<"update personFixedOwnerAddNok is:"<<query.exec(sql)<<sql;

//    //个人固话用户-用户姓名&amp;证件号码校验不合规
//         sql = "update report set personFixedOwnerNameNumNok="+QString::number(report->personFixedOwnerNameNumNok);
//         qDebug()<<"update personFixedOwnerNameNumNok is:"<<query.exec(sql)<<sql;

//    //个人固话用户-用户姓名&amp;证件地址校验不合规
//         sql = "update report set personFixedOwnerNameAddNok="+QString::number(report->personFixedOwnerNameAddNok);
//         qDebug()<<"update personFixedOwnerNameAddNok is:"<<query.exec(sql)<<sql;

//    //个人固话用户-证件号码&amp;证件地址校验不合规
//         sql = "update report set personFixedOwnerNumAddNok="+QString::number(report->personFixedOwnerNumAddNok);
//         qDebug()<<"update personFixedOwnerNumAddNok is:"<<query.exec(sql)<<sql;

//    //个人固话用户-用户姓名&amp;证件号码&amp;证件地址校验不合规
//         sql = "update report set personFixedOwnerNameNumAddNok="+QString::number(report->personFixedOwnerNameNumAddNok);
//         qDebug()<<"update personFixedOwnerNameNumAddNok is:"<<query.exec(sql)<<sql;

//    //个人移动用户-代办人信息未登记
//             sql = "update report set personMobileAgentNotReg="+QString::number(report->personMobileAgentNotReg);
//         qDebug()<<"update personMobileAgentNotReg is:"<<query.exec(sql)<<sql;

//    //个人固话用户-代办人信息未登记
//             sql = "update report set personFixedAgentNotReg="+QString::number(report->personFixedAgentNotReg);
//         qDebug()<<"update personFixedAgentNotReg is:"<<query.exec(sql)<<sql;

//    //个人移动用户-代办人信息校验不合规
//         sql = "update report set personMobileAgentNok="+QString::number(report->personMobileAgentNok);
//         qDebug()<<"update personMobileAgentNok is:"<<query.exec(sql)<<sql;

//    //个人固话用户-代办人信息校验不合规
//         sql = "update report set personFixedAgentNok="+QString::number(report->personFixedAgentNok);
//         qDebug()<<"update personFixedAgentNok is:"<<query.exec(sql)<<sql;

//    //单位移动用户-形式合规数据
//         sql = "update report set unitMobileOk="+QString::number(report->unitMobileOk);
//         qDebug()<<"update unitMobileOk is:"<<query.exec(sql)<<sql;

//    //单位移动用户-使用人信息未登记
//             sql = "update report set unitMobileOwnerNotReg="+QString::number(report->unitMobileOwnerNotReg);
//         qDebug()<<"update unitMobileOwnerNotReg is:"<<query.exec(sql)<<sql;

////    //单位移动用户-经办人信息未登记
//             sql = "update report set unitMobileAgentNotReg="+QString::number(report->unitMobileAgentNotReg);
//         qDebug()<<"update unitMobileAgentNotReg is:"<<query.exec(sql)<<sql;

////    //单位移动用户-单位信息未登记
//             sql = "update report set unitMobileUnitNotReg="+QString::number(report->unitMobileUnitNotReg);
//         qDebug()<<"update unitMobileUnitNotReg is:"<<query.exec(sql)<<sql;

////    //单位移动用户-使用人&amp;经办人信息未登记
//             sql = "update report set unitMobileOwnerAgentNotReg="+QString::number(report->unitMobileOwnerAgentNotReg);
//         qDebug()<<"update unitMobileOwnerAgentNotReg is:"<<query.exec(sql)<<sql;

////    //单位移动用户-使用人&amp;单位信息未登记
//             sql = "update report set unitMobileOwnerUnitNotReg="+QString::number(report->unitMobileOwnerUnitNotReg);
//         qDebug()<<"update unitMobileOwnerUnitNotReg is:"<<query.exec(sql)<<sql;

////    //单位移动用户-经办人&amp;单位信息未登记
//             sql = "update report set unitMobileAgentUnitNotReg="+QString::number(report->unitMobileAgentUnitNotReg);
//         qDebug()<<"update unitMobileAgentUnitNotReg is:"<<query.exec(sql)<<sql;

////    //单位移动用户-使用人&amp;经办人&amp;单位信息未登记
//             sql = "update report set unitMobileOwnerAgentUnitNotReg="+QString::number(report->unitMobileOwnerAgentUnitNotReg);
//         qDebug()<<"update unitMobileOwnerAgentUnitNotReg is:"<<query.exec(sql)<<sql;

//    //单位移动用户-使用人信息校验不合规
//         sql = "update report set unitMobileOwnerNok="+QString::number(report->unitMobileOwnerNok);
//         qDebug()<<"update unitMobileOwnerNok is:"<<query.exec(sql)<<sql;

//    //单位移动用户-经办人信息校验不合规
//         sql = "update report set unitMobileAgentNok="+QString::number(report->unitMobileAgentNok);
//         qDebug()<<"update unitMobileAgentNok is:"<<query.exec(sql)<<sql;

//    //单位移动用户-单位信息校验不合规
//         sql = "update report set unitMobileUnitNok="+QString::number(report->unitMobileUnitNok);
//         qDebug()<<"update unitMobileUnitNok is:"<<query.exec(sql)<<sql;

//    //单位移动用户-使用人&amp;经办人信息校验不合规
//         sql = "update report set unitMobileOwnerAgentNok="+QString::number(report->unitMobileOwnerAgentNok);
//         qDebug()<<"update unitMobileOwnerAgentNok is:"<<query.exec(sql)<<sql;
//    //单位移动用户-使用人&amp;单位信息校验不合规
//         sql = "update report set unitMobileOwnerUnitNok="+ QString::number(report->unitMobileOwnerUnitNok);
//         qDebug()<<"update unitMobileOwnerUnitNok is:"<<query.exec(sql)<<sql;
//    //单位移动用户-经办人&amp;单位信息校验不合规
//         sql = "update report set unitMobileAgentUnitNok="+QString::number(report->unitMobileAgentUnitNok);
//         qDebug()<<"update unitMobileAgentUnitNok is:"<<query.exec(sql)<<sql;

//    //单位移动用户-使用人&amp;经办人&amp;单位信息校验不合规
//         sql = "update report set unitMobileOwnerAgentUnitNok="+QString::number(report->unitMobileOwnerAgentUnitNok);
//         qDebug()<<"update unitMobileOwnerAgentUnitNok is:"<<query.exec(sql)<<sql;

//    //单位固话用户-形式合规数据
//         sql = "update report set unitFixedOk="+QString::number(report->unitFixedOk);
//         qDebug()<<"update unitFixedOk is:"<<query.exec(sql)<<sql;

//    //单位固话用户-经办人信息未登记
//             sql = "update report set unitFixedAgentNotReg="+QString::number(report->unitFixedAgentNotReg);
//         qDebug()<<"update unitFixedAgentNotReg is:"<<query.exec(sql)<<sql;

////    //单位固话用户-单位信息未登记
//             sql = "update report set unitFixedUnitNotReg="+QString::number(report->unitFixedUnitNotReg);
//         qDebug()<<"update unitMobileUnitNotReg is:"<<query.exec(sql)<<sql;

////    //单位固话用户-经办人&amp;单位信息未登记
//             sql = "update report set unitFixedAgentUnitNotReg="+QString::number(report->unitFixedAgentUnitNotReg);
//         qDebug()<<"update unitFixedAgentUnitNotReg is:"<<query.exec(sql)<<sql;

//    //单位固话用户-经办人信息校验不合规
//         sql = "update report set unitFixedAgentNok="+QString::number(report->unitFixedAgentNok);
//         qDebug()<<"update unitFixedAgentNok is:"<<query.exec(sql)<<sql;

//    //单位固话用户-单位信息校验不合规
//         sql = "update report set unitFixedUnitNok="+QString::number(report->unitFixedUnitNok);
//         qDebug()<<"update unitFixedUnitNok is:"<<query.exec(sql)<<sql;

//    //单位固话用户-经办人&amp;单位信息校验不合规
//         sql = "update report set unitFixedAgentUnitNok="+QString::number(report->unitFixedAgentUnitNok);
//         qDebug()<<"update unitFixedAgentUnitNok is:"<<query.exec(sql)<<sql;

//    //行业移动应用-形式合规数据
//         sql = "update report set tradeMobileOk="+QString::number(report->tradeMobileOk);
//         qDebug()<<"update tradeMobileOk is:"<<query.exec(sql)<<sql;

//    //行业移动应用-经办人信息未登记
//             sql = "update report set tradeMobileAgentNotReg="+QString::number(report->tradeMobileAgentNotReg);
//         qDebug()<<"update tradeMobileAgentNotReg is:"<<query.exec(sql)<<sql;

////    //行业移动应用-经办人&amp;单位信息未登记
//             sql = "update report set tradeMobileAgentUnitNotReg="+QString::number(report->tradeMobileAgentUnitNotReg);
//         qDebug()<<"update tradeMobileAgentUnitNotReg is:"<<query.exec(sql)<<sql;

////    //行业移动应用-责任人&amp;经办人信息未登记

//             sql = "update report set tradeMobileLiableAgentNotReg="+QString::number(report->tradeMobileLiableAgentNotReg);
//         qDebug()<<"update tradeMobileLiableAgentNotReg is:"<<query.exec(sql)<<sql;

////    //行业移动应用-责任人&amp;经办人&amp;单位信息未登记
//             sql = "update report set tradeMobileLiableAgentUnitNotReg="+QString::number(report->tradeMobileLiableAgentUnitNotReg);
//         qDebug()<<"update tradeMobileLiableAgentUnitNotReg is:"<<query.exec(sql)<<sql;

////    //行业移动应用-单位信息未登记
//             sql = "update report set tradeMobileUnitNotReg="+QString::number(report->tradeMobileUnitNotReg);
//         qDebug()<<"update tradeMobileUnitNotReg is:"<<query.exec(sql)<<sql;

////    //行业移动应用-责任人信息未登记
//             sql = "update report set tradeMobileLiableNotReg="+QString::number(report->tradeMobileLiableNotReg);
//         qDebug()<<"update tradeMobileLiableNotReg is:"<<query.exec(sql)<<sql;

////    //行业移动应用-责任人&amp;单位信息未登记
//             sql = "update report set tradeMobileLiableUnitNotReg="+QString::number(report->tradeMobileLiableUnitNotReg);
//         qDebug()<<"update tradeMobileLiableUnitNotReg is:"<<query.exec(sql)<<sql;

//    //行业移动应用-经办人信息校验不合规
//         sql = "update report set tradeMobileAgentNok="+QString::number(report->tradeMobileAgentNok);
//         qDebug()<<"update tradeMobileAgentNok is:"<<query.exec(sql)<<sql;

//    //行业移动应用-经办人&amp;单位信息校验不合规
//         sql = "update report set tradeMobileAgentUnitNok="+QString::number(report->tradeMobileAgentUnitNok);
//         qDebug()<<"update tradeMobileAgentUnitNok is:"<<query.exec(sql)<<sql;

//    //行业移动应用-责任人&amp;经办人信息校验不合规
//         sql = "update report set tradeMobileLiableAgentNok="+QString::number(report->tradeMobileLiableAgentNok);
//         qDebug()<<"update tradeMobileLiableAgentNok is:"<<query.exec(sql)<<sql;

//    //行业移动应用-责任人&amp;经办人&amp;单位信息校验不合规
//         sql = "update report set tradeMobileLiableAgentUnitNok="+QString::number(report->tradeMobileLiableAgentUnitNok);
//         qDebug()<<"update tradeMobileLiableAgentUnitNok is:"<<query.exec(sql)<<sql;

//    //行业移动应用-单位信息校验不合规
//         sql = "update report set tradeMobileUnitNok="+QString::number(report->tradeMobileUnitNok);
//         qDebug()<<"update tradeMobileUnitNok is:"<<query.exec(sql)<<sql;

//    //行业移动应用-责任人信息校验不合规
//         sql = "update report set tradeMobileLiableNok="+QString::number(report->tradeMobileLiableNok);
//         qDebug()<<"update tradeMobileLiableNok is:"<<query.exec(sql)<<sql;

//    //行业移动应用-责任人&amp;单位信息校验不合规
//         sql = "update report set tradeMobileLiableUnitNok="+QString::number(report->tradeMobileLiableUnitNok);
//         qDebug()<<"update tradeMobileLiableUnitNok is:"<<query.exec(sql)<<sql;

//    //行业固话应用-形式合规数据
//         sql = "update report set tradeFixedOk="+QString::number(report->tradeFixedOk);
//         qDebug()<<"update tradeFixedOk is:"<<query.exec(sql)<<sql;

//    //行业固话应用-经办人信息未登记
//             sql = "update report set tradeFixedAgentNotReg="+QString::number(report->tradeFixedAgentNotReg);
//         qDebug()<<"update tradeFixedAgentNotReg is:"<<query.exec(sql)<<sql;

////    //行业固话应用-经办人&amp;单位信息未登记
//             sql = "update report set tradeFixedAgentUnitNotReg="+QString::number(report->tradeFixedAgentUnitNotReg);
//         qDebug()<<"update tradeFixedAgentUnitNotReg is:"<<query.exec(sql)<<sql;

////    //行业固话应用-单位信息未登记
//             sql = "update report set tradeFixedUnitNotReg="+QString::number(report->tradeFixedUnitNotReg);
//         qDebug()<<"update tradeFixedUnitNotReg is:"<<query.exec(sql)<<sql;

//    //行业固话应用-经办人信息校验不合规
//         sql = "update report set tradeFixedAgentNok="+QString::number(report->tradeFixedAgentNok);
//         qDebug()<<"update tradeFixedAgentNok is:"<<query.exec(sql)<<sql;

//    //行业固话应用-经办人&amp;单位信息校验不合规
//         sql = "update report set tradeFixedAgentUnitNok="+QString::number(report->tradeFixedAgentUnitNok);
//         qDebug()<<"update tradeFixedAgentUnitNok is:"<<query.exec(sql)<<sql;

//    //行业固话应用-单位信息校验不合规
//         sql = "update report set tradeFixedUnitNok="+QString::number(report->tradeFixedUnitNok);
//         qDebug()<<"update tradeFixedUnitNok is:"<<query.exec(sql)<<sql;

//    //个人移动一证五卡不合规
//            sql = "update report set personMobileOneCard="+QString::number(report->personMobileOneCard);
//         qDebug()<<"update personMobileOneCard is:"<<query.exec(sql)<<sql;

//}

//QString UserDb::getColName(QString name){
//    //    int rtn = ;
////        qDebug()<<"查询的列名是"<<name<<"列号是"<<col_name_map.value(name)+1;
//        return "col"+QString::number(col_name_map.value(name)+1);
//}

//int UserDb::getColNum(QString name){
//    //    int rtn = ;
////        qDebug()<<"查询的列名是"<<name<<"列号是"<<col_name_map.value(name)+1;
//        return col_name_map.value(name);
//}

////创建数据库表
//bool UserDb::createTable(){
////    connDb();

//    QString sql = "create table file(id varchar primary key";
//    for(int i=0;i<42;i++){
//        sql.append(",col").append( QString::number(i+1, 10)).append(" varchar");
//    }
//    sql.append(")");


//    QSqlQuery query;

//    qDebug()<<"drop table"<<query.exec("drop table file");
//    qDebug()<<"createTable()"<<sql;
//    bool b = query.exec(sql);
//    qDebug()<<b;
//    return b;
//}


//QString UserDb::getCol(QString str){
//    if(str=="null")
//        return nullptr;//"'"+str+"'";
//    else
//        return str;
//}

////文件入库
//bool UserDb::insertDb(QString filename){
//    qDebug()<<"insertDb";
//    if(!fileIsExists(filename)){
//        qDebug()<<"文件不存在。\n当前路径是：";
//        qDebug()<< QDir::currentPath();
//        return false;
//    }
//    if(!createTable()){
//        qDebug()<<"库表创建不成功。";
//        return false;
//    }


//    QSqlQuery query;
//    QFile file(filename);
//    QTextCodec *code = QTextCodec::codecForName("GBK");//设置文件编码


//    QList<QString> col;
//    QString sql="";
//    QString line = "";
//    int line_num = 1;

//    QTime    tmpTime;
//    bool isSuccess = true;
//    if(file.open(QFile::ReadOnly | QFile::Text)){
//        QTextStream stream(&file);
//        stream.setCodec(code);

//        createConnection();//建立数据库连接
//        qDebug()<<"db isopen?"<<db.isOpen();
//        qDebug()<<"start transaction"<<db.transaction();
//         do {

//            line = stream.readLine();
//            col =  line.split(delimeter);
//            if(col.size() != COL_NUM){
//                qDebug()<<"列数不对"<<col.size();
//                //todo
//                continue;
//            }
////            qDebug()<<"tmp is :"<<qPrintable(line);

//            sql = "insert into file values(?";
//            for(int i=0;i<col.size();i++){
//                sql.append(",?");
////                sql.append(","+getCol(col[i])+"");
//            }
//            sql.append(")");
//            query.prepare(sql);

//            query.addBindValue(line_num);
//            line_num++;
//            for(int i=0;i<col.size();i++){
////                qDebug()<<"i:"<<i<<"--"<<getCol(col[i]);
//                query.addBindValue(getCol(col[i]));
//            }

//            if(query.exec()){
//                qDebug("insert %d success.\n",line_num);
//            }
//            else
//            {
//                isSuccess=false;
//                qDebug()<<"执行出错"<<sql;
//                break;
//           }


//            if(line_num%100==0)//!stopped &&
//            {
//                if(db.commit())
//                {
//                    qDebug()<<"commit";
//                    qDebug()<<"1000条数据耗时："<<tmpTime.elapsed()<<"ms"<<endl;
//                    qDebug()<<"db isopen?"<<db.isOpen();
//                    qDebug()<<"start transaction"<<db.transaction();
//                    tmpTime.start();
//                    emit message("已处理"+QString::number(line_num)+"行");
//                    qDebug()<<"line_num"<<line_num;
//                }
//                else{
//                    qDebug()<<"error: line_num"<<line_num<<" "<<sql;
//                    qDebug()<<"roll back"<<db.rollback();
//                }
//            }

//        }while(!stopped && !line.isEmpty());
//        qDebug()<<"final commit"<<db.commit();
////        db.close();
//    }
//    else{
//        qDebug()<<QStringLiteral("文件打开错误。");
//    }
//    return isSuccess;
//}

////文件是否存在
//bool UserDb::fileIsExists(QString filename){
//    if(filename.isNull()||filename.isEmpty()){
//        qDebug()<<QStringLiteral("文件名参数不正确。");
//        return false;
//    }
//    QFile file(filename);
//    return file.exists();
//}


///**
// * 读取数据库函数
// * @brief UserFile::readTable
// * @param sql sqlite语句
// * @return 数据列表
// */
//QList<QString> UserDb::readTable(QString sql){
//    QList<QString> list;
//    QString line = "";

//    QSqlQuery query;
//    query.exec(sql);
//    QSqlRecord qr = query.record();
//    qDebug()<<sql<<"中字段数为"<<qr.count();

//    while(query.next()){
//        line = "";
//        for(int i=0;i<qr.count();i++){
//            line.append(query.value(i).toString());

//        }
//         qDebug()<<"line:"<<qPrintable(line);
//        list.append(line);
//    }
////    db.close();
//    return list;
//}

//void UserDb::printData(QString table){
//    QList<QString> list = readTable("select * from "+table);
//    for(int i=0;i<list.size();i++){
//        qDebug()<<list.at(i);
//    }
//}

//bool UserDb::countData(){
//    qDebug()<<__FUNCTION__;
//    if(!fileIsExists(filename)){
//        qDebug()<<"文件不存在。\n当前路径是：";
//        qDebug()<< QDir::currentPath();
//        return false;
//    }

//    QFile file(filename);
//    QTextCodec *code = QTextCodec::codecForName("GBK");//设置文件编码


////    QList<QString> col;
//    QString line = "";
//    int line_num = 1;

//    QTime    tmpTime;
//    if(file.open(QFile::ReadOnly | QFile::Text)){
//        QTextStream stream(&file);
//        stream.setCodec(code);

//         do {
//            line = stream.readLine();


//            processLine(line);
//            report->allData +=1;
//            qDebug()<<"line "<<line_num++<<" finish :"<<(line);//qPrintable

//            if(!stopped && line_num%1000==0)
//            {
//                    qDebug()<<"commit";
//                    qDebug()<<QStringLiteral("1000条数据耗时：")<<tmpTime.elapsed()<<"ms"<<endl;
//                    tmpTime.start();
//                    emit message("已处理"+QString::number(line_num)+"行");
//                    qDebug()<<"line_num"<<line_num;
//            }
//        }while(!stopped && !line.isEmpty());
//    }
//    else{
//        qDebug()<<QStringLiteral("文件打开错误。");
//    }
//    return true;
//}

//bool UserDb::isNotReg(QString str){
//    if(str.isNull())
//        return true;
//    else if(str.isEmpty())
//        return true;
//    else if(str.trimmed()=="null")
//        return true;
//    else if(str.trimmed()=="NULL")
//        return true;
//    else if(str.trimmed()=="Null")
//        return true;
//    else
//        return false;
//}

///**
// * @brief UserDb::isPersonTypeNok
// * @param str 证件类型
// * @return 个人证件类型是否不合规
// */
//bool UserDb::isPersonTypeNok(QString str){
//    if(!personType.contains(str)){
//        qDebug()<<"个人证件类型不合规"<<str<<" "<<personType;
//        return true;
//    }

//    return false;
//}

//bool UserDb::isUnitTypeNok(QString str){
//    qDebug()<<"单位证件类型不合规"<<str<<" "<<unitType;
//    return !unitType.contains(str);
//}

//bool UserDb::isPersonNameNok(QString str){
//    if(personNameMin!=-1 && str.length()<personNameMin){
//        qDebug()<<personNameMin<<"姓名字数不够"<<str.length()<<" "<<str;
//        return true;
//    }
//    else if(personNameMax!=-1 && str.length()>personNameMax){
//        qDebug()<<personNameMax<<"姓名太长"<<str.length()<<" "<<str;
//        return true;
//    }
//    else if(personNameRule.contains(str)){
//        qDebug()<<"姓名包含非法字符:  "<<str;
//        return true;
//    }
//    return false;
//}

//bool UserDb::isUnitNameNok(QString str){
//    if(unitNameMin!=-1 && str.length()<unitNameMin){
//        qDebug()<<unitNameMin<<"单位名称字数不够"<<str.length()<<str;
//        return true;
//    }
//    else if(unitNameMax!=-1 && str.length()>unitNameMax){
//        qDebug()<<unitNameMax<<"单位名称超长"<<str.length()<<str;
//        return true;
//    }
//    else if(unitNameRule.contains(str)){
//        qDebug()<<"单位名称不合规"<<str;
//        return true;
//    }
//    return false;
//}
//bool UserDb::isPersonNumNok(QString str){
//    if(personNumMin!=-1 && str.length()<personNumMin){
//        qDebug()<<personNumMin<<"个人证件号码长度不够"<<str.length()<<str;
//        return true;
//    }
//    else if(personNumMax!=-1 && str.length()>personNumMax){
//        qDebug()<<personNumMax<<"个人证件号码超长"<<str.length()<<str;
//        return true;
//    }
//    else if(numRule.contains(str)){
//        qDebug()<<"个人证件号码不合规"<<str;
//        return true;
//    }
//    return false;
//}
//bool UserDb::isUnitNumNok(QString str){
//    if(unitNumMin!=-1 && str.length()<unitNumMin){
//        qDebug()<<unitNumMin<<"单位证件号码长度不够"<<str.length()<<str;
//        return true;
//    }
//    else if(unitNumMax!=-1 &&str.length()>unitNumMax){
//        qDebug()<<unitNumMax<<"单位证件号码超长"<<str.length()<<str;
//        return true;
//    }
//    else if(numRule.contains(str)){
//        qDebug()<<"单位证件号码不合规"<<str;
//        return true;
//    }
//    return false;
//}
//bool UserDb::isPersonAddNok(QString str){
//    if(-1!=personAddMin && str.length()<personAddMin){
//        qDebug()<<personAddMin<<"个人证件地址不够"<<str.length()<<str;
//        return true;
//    }
//    else if(-1!=personAddMax && str.length()>personAddMax){
//        qDebug()<<personAddMax<<"个人证件地址超长"<<str.length()<<str;
//        return true;
//    }
//    else if(addRule.contains(str)){
//        qDebug()<<"个人证件地址不合规"<<str;
//        return true;
//    }
//    return false;
//}
//bool UserDb::isUnitAddNok(QString str){
//    if(-1!=unitAddMin && str.length()<unitAddMin){
//        qDebug()<<unitAddMin<<"单位地址长度不够"<<str.length()<<str;
//        return true;
//    }
//    else if(-1!=unitAddMax && str.length()>unitAddMax){
//        qDebug()<<unitAddMax<<"单位地址超长"<<str.length()<<str;
//        return true;
//    }
//    else if(addRule.contains(str)){
//        qDebug()<<"单位地址不合规"<<str;
//        return true;
//    }
//    return false;
//}


//void UserDb::processLine(QString line){

//    QList<QString> col;
//    col =  line.split(delimeter);

//    if(col.size() != COL_NUM){
//        qDebug()<<"列数不对"<<col.size();
//        saveAbnormal(line);
//        return;
//    }

//    //非实名停机和销户的，不纳入检查范围，单独统计数字，加在报表里。
//    if(nonRealName.contains(col.at(getColNum("使用状态")))||leaveNet.contains(col.at(getColNum("使用状态")))){
//        saveLeaveNet(line);
//        return;
//    }

//    /*


//入网时间在20130901的不能用15位身份证，身份证校验规则问景欣。
//入网时间格式不同。期望可以配置
//年月日、时分秒、- /    :    等10多类包括欧美格式的，改为下拉选择？
//20170401以后开卡的超过5张的算违规，证件号有多少？开了多少号？
//一证多名，所有身份证、使用人、责任人、经办人、所有证件号码对于超过1个名字。
//名字里面不能出现特殊字符，规则里面是不合规的。
//多字段、少字段、时间类型、编码格式（可设置）、用户类型*/

//    if(col.at(getColNum("用户类型"))==userType.value("person")){
//        if(bizTypeFixed.contains(col.at(getColNum("用户业务类型")))){
//            bool p_f_o_t_r=false;//"个人固定用户-证件类型未登记
//            bool p_f_o_name_r=false;//个人固定用户-用户姓名未登记
//            bool p_f_o_num_r=false;//个人固定用户-证件号码未登记
//            bool p_f_o_add_r=false;//个人固定用户-证件地址未登记
//            bool p_f_o_agent_r=false;//个人固定用户-代办人未登记
//            if(isNotReg(col.at(getColNum("机主证件类型")))){
//                savePersonFixedOwnerTypeNotReg(line);
//                p_f_o_t_r=true;
//            }
//            if(isNotReg(col.at(getColNum("机主用户姓名")))){
//                savePersonFixedOwnerNameNotReg(line);
//                p_f_o_name_r=true;
//            }
//            if(isNotReg(col.at(getColNum("机主证件号码")))){
//                savePersonFixedOwnerNumNotReg(line);
//                p_f_o_num_r=true;
//            }
//            if(isNotReg(col.at(getColNum("机主证件地址")))){
//                savePersonFixedOwnerAddNotReg(line);
//                p_f_o_add_r=true;
//            }
//            if(p_f_o_name_r&&p_f_o_num_r){
//                savePersonFixedOwnerNameNumNotReg(line);
//            }
//            if(p_f_o_name_r&&p_f_o_add_r){
//                savePersonFixedOwnerNameAddNotReg(line);
//            }
//            if(p_f_o_num_r&&p_f_o_add_r){
//                savePersonFixedOwnerNumAddNotReg(line);
//            }
//            if(p_f_o_name_r&&p_f_o_num_r&&p_f_o_add_r){
//                savePersonFixedOwnerNameNumAddNotReg(line);
//            }
//            if(isNotReg(col.at(getColNum("代（经）办人姓名")))||isNotReg(col.at(getColNum("代（经）办人证件类型")))||
//                    isNotReg(col.at(getColNum("代（经）办人证件号码")))||isNotReg(col.at(getColNum("代（经）办人证件地址")))||isNotReg(col.at(getColNum("代（经）办人通讯地址")))){
//                savePeronMobileAgentNotReg(line);
//                p_f_o_agent_r=true;
//            }
//            if(p_f_o_t_r&&p_f_o_name_r&&p_f_o_num_r&&p_f_o_add_r&&isNotReg(col.at(getColNum("代（经）办人姓名")))&&isNotReg(col.at(getColNum("代（经）办人证件类型")))&&
//                    isNotReg(col.at(getColNum("代（经）办人证件号码")))&&isNotReg(col.at(getColNum("代（经）办人证件地址")))&&isNotReg(col.at(getColNum("代（经）办人通讯地址")))){
//                saveAllNotReg(line);//全量未登记
//            }
//            bool p_f_o_t_n=false;//"个人固定用户-证件类型不合规
//            bool p_f_o_name_n=false;//个人固定用户-用户姓名不合规
//            bool p_f_o_num_n=false;//个人固定用户-证件号码不合规
//            bool p_f_o_add_n=false;//个人固定用户-证件地址不合规
//            bool p_f_o_agent_n=false;//个人固定用户-代办人不合规
//            if(isNotReg(col.at(getColNum("代（经）办人姓名")))||isNotReg(col.at(getColNum("代（经）办人证件类型")))||
//                        isNotReg(col.at(getColNum("代（经）办人证件号码")))||isNotReg(col.at(getColNum("代（经）办人证件地址")))||isNotReg(col.at(getColNum("代（经）办人通讯地址")))){
//                    savePeronMobileAgentNok(line);
//                    p_f_o_agent_n=true;
//            }
//            if(isNotReg(col.at(getColNum("机主证件类型")))){
//                savePersonFixedOwnerTypeNok(line);
//                p_f_o_t_n=true;
//            }
//            if(isNotReg(col.at(getColNum("机主用户姓名")))){
//                savePersonFixedOwnerNameNok(line);
//                p_f_o_name_n=true;
//            }
//            if(isNotReg(col.at(getColNum("机主证件号码")))){
//                savePersonFixedOwnerNumNok(line);
//                p_f_o_num_n=true;
//            }
//            if(isNotReg(col.at(getColNum("机主证件地址")))){
//                savePersonFixedOwnerAddNok(line);
//                p_f_o_add_n=true;
//            }
//            if(p_f_o_name_n&&p_f_o_num_n){
//                savePersonFixedOwnerNameNumNok(line);
//            }
//            if(p_f_o_name_n&&p_f_o_add_n){
//                savePersonFixedOwnerNameAddNok(line);
//            }
//            if(p_f_o_num_n&&p_f_o_add_n){
//                savePersonFixedOwnerNumAddNok(line);
//            }
//            if(p_f_o_name_n&&p_f_o_num_n&&p_f_o_add_n){
//                savePersonFixedOwnerNameNumAddNok(line);
//            }
//            if(isNotReg(col.at(getColNum("代（经）办人姓名")))||isNotReg(col.at(getColNum("代（经）办人证件类型")))||
//                    isNotReg(col.at(getColNum("代（经）办人证件号码")))||isNotReg(col.at(getColNum("代（经）办人证件地址")))||isNotReg(col.at(getColNum("代（经）办人通讯地址")))){
//                savePersonFixedAgentNotReg(line);
//                p_f_o_agent_r=true;
//            }
//            if(isPersonNameNok(col.at(getColNum("代（经）办人姓名")))||isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))||
//                    isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))||isPersonAddNok(col.at(getColNum("代（经）办人证件地址")))||isPersonAddNok(col.at(getColNum("代（经）办人通讯地址")))){
//                savePersonFixedAgentNok(line);
//                p_f_o_agent_n=true;
//            }
//            if(!(p_f_o_t_r&&p_f_o_name_r&&p_f_o_num_r&&p_f_o_add_r&&p_f_o_t_n&&p_f_o_name_n&&p_f_o_num_n&&p_f_o_add_n&&p_f_o_agent_r&&p_f_o_agent_n)){
//                savePersonFixedOk(line);
//            }
//            if(p_f_o_t_n&&p_f_o_name_n&&p_f_o_num_n&&p_f_o_add_n&&isPersonNameNok(col.at(getColNum("代（经）办人姓名")))&&isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))&&
//                    isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))&&isPersonAddNok(col.at(getColNum("代（经）办人证件地址")))&&isPersonAddNok(col.at(getColNum("代（经）办人通讯地址")))){
//                saveAllNok(line);//全量不合规
//            }
//        }
//        else {
//            bool p_m_o_t_r=false;//"个人移动用户-证件类型未登记
//            bool p_m_o_name_r=false;//个人移动用户-用户姓名未登记
//            bool p_m_o_num_r=false;//个人移动用户-证件号码未登记
//            bool p_m_o_add_r=false;//个人移动用户-证件地址未登记
//            bool p_m_o_t_n=false;//"个人移动用户-证件类型不合规
//            bool p_m_o_name_n=false;//个人移动用户-用户姓名不合规
//            bool p_m_o_num_n=false;//个人移动用户-证件号码不合规
//            bool p_m_o_add_n=false;//个人移动用户-证件地址不合规
//            if(isNotReg(col.at(getColNum("机主证件类型")))){
//                savePersonMobileOwnerTypeNotReg(line);
//                p_m_o_t_r = true;
//            }
//            if(isNotReg(col.at(getColNum("机主用户姓名")))){
//                savePersonMobileOwnerNameNotReg(line);
//                p_m_o_name_r=true;
//            }
//            if(isNotReg(col.at(getColNum("机主证件号码")))){
//                savePersonMobileOwnerNumNotReg(line);
//                p_m_o_num_r=true;
//            }
//            if(isNotReg(col.at(getColNum("机主证件地址")))){
//                savePersonMobileOwnerAddNotReg(line);
//                p_m_o_add_r=true;
//            }
//            if(p_m_o_name_r&&p_m_o_num_r){
//                savePersonMobileOwnerNameNumNotReg(line);
//            }
//            if(p_m_o_name_r&&p_m_o_add_r){
//                savePersonMobileOwnerNameAddNotReg(line);
//            }
//            if(p_m_o_num_r&&p_m_o_add_r){
//                savePersonMobileOwnerNumAddNotReg(line);
//            }
//            if(p_m_o_name_r&&p_m_o_num_r&&p_m_o_add_r){
//                savePersonMobileOwnerNameNumAddNotReg(line);
//            }
//            if(p_m_o_t_r&&p_m_o_name_r&&p_m_o_num_r&&p_m_o_add_r){
//                saveAllNotReg(line);//全量未登记
//            }
//            if(isPersonTypeNok(col.at(getColNum("机主证件类型")))){
//                savePeronMobileOwnerTyteNok(line);
//                p_m_o_t_n=true;
//            }
//            if(isPersonNameNok(col.at(getColNum("机主用户姓名")))){
//                savePeronMobileOwnerNameNok(line);
//                p_m_o_name_n=true;
//            }
//            if(isPersonNumNok(col.at(getColNum("机主证件号码")))){
//                savePeronMobileOwnerNumNok(line);
//                p_m_o_num_n=true;
//            }
//            if(isPersonAddNok(col.at(getColNum("机主证件地址")))){
//                savePeronMobileOwnerAddNok(line);
//                p_m_o_add_n=true;
//            }
//            if(p_m_o_name_n&&p_m_o_num_n){
//                savePeronMobileOwnerNameNumNok(line);
//            }
//            if(p_m_o_name_n&&p_m_o_add_n){
//                savePeronMobileOwnerNameAddNok(line);
//            }
//            if(p_m_o_num_n&&p_m_o_add_n){
//                savePeronMobileOwnerNumAddNok(line);
//            }
//            if(p_m_o_name_n&&p_m_o_num_n&&p_m_o_add_n){
//                savePeronMobileOwnerNameNumAddNok(line);
//            }
//            if(!(p_m_o_t_r&&p_m_o_t_n&&p_m_o_name_r&&p_m_o_num_r&&p_m_o_add_r&&p_m_o_name_n&&p_m_o_num_n&&p_m_o_add_n)){
//                savePersonMobileOk(line);
//            }
//            if(p_m_o_t_n&&p_m_o_name_n&&p_m_o_num_n&&p_m_o_add_n){
//                saveAllNok(line);//全量不合规
//            }
//        }

//    }
//    else if(col.at(getColNum("用户类型"))==userType.value("unit")){
//        if(bizTypeFixed.contains(col.at(getColNum("用户业务类型")))){
//            bool u_f_a_r=false;//单位固话用户-代办人信息未登记
//            bool u_f_u_r=false;//单位固话用户-单位信息未登记


//            if(isNotReg(col.at(getColNum("代（经）办人姓名")))||isNotReg(col.at(getColNum("代（经）办人证件类型")))||
//                    isNotReg(col.at(getColNum("代（经）办人证件号码")))||isNotReg(col.at(getColNum("代（经）办人证件地址")))||isNotReg(col.at(getColNum("代（经）办人通讯地址")))){
//                saveUnitFixedAgentNotReg(line);
//                u_f_a_r=true;
//            }
//            if(isNotReg(col.at(getColNum("单位名称")))||isNotReg(col.at(getColNum("单位证件号码")))||isNotReg(col.at(getColNum("单位证件类型")))||
//                    isNotReg(col.at(getColNum("单位证件地址")))||isNotReg(col.at(getColNum("单位通讯地址")))||isNotReg(col.at(getColNum("单位装机地址")))){
//                saveUnitFixedUnitNotReg(line);
//                u_f_u_r=true;
//            }
//            if(u_f_a_r&&u_f_u_r){
//                saveUnitFixedAgentUnitNotReg(line);
//            }
//            if(isNotReg(col.at(getColNum("代（经）办人姓名")))&&isNotReg(col.at(getColNum("代（经）办人证件类型")))&&
//                    isNotReg(col.at(getColNum("代（经）办人证件号码")))&&isNotReg(col.at(getColNum("代（经）办人证件地址")))&&isNotReg(col.at(getColNum("代（经）办人通讯地址")))&&
//                isNotReg(col.at(getColNum("单位名称")))&&isNotReg(col.at(getColNum("单位证件号码")))&&isNotReg(col.at(getColNum("单位证件类型")))&&
//                    isNotReg(col.at(getColNum("单位证件地址")))&&isNotReg(col.at(getColNum("单位通讯地址")))&&isNotReg(col.at(getColNum("单位装机地址")))){
//                saveAllNotReg(line);
//            }
//            bool u_f_a_n=false;//单位移动用户-代办人信息不合规
//            bool u_f_u_n=false;//单位移动用户-单位信息不合规
//            if(isPersonNameNok(col.at(getColNum("代（经）办人姓名")))||isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))||
//                    isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))||isPersonAddNok(col.at(getColNum("代（经）办人证件地址")))||
//                    isPersonAddNok(col.at(getColNum("代（经）办人通讯地址")))){
//                saveUnitFixedAgentNok(line);
//                u_f_a_n=true;
//            }
//            if(isUnitNameNok(col.at(getColNum("单位名称")))||isUnitNumNok(col.at(getColNum("单位证件号码")))||isUnitTypeNok(col.at(getColNum("单位证件类型")))||
//                    isUnitAddNok(col.at(getColNum("单位证件地址")))||isUnitAddNok(col.at(getColNum("单位通讯地址")))||isUnitAddNok(col.at(getColNum("单位装机地址")))){
//                saveUnitFixedUnitNok(line);
//                u_f_u_n=true;
//            }
//            if(u_f_a_n&&u_f_u_n){
//                saveUnitMobileAgentUnitNok(line);
//            }
//            if(!(u_f_a_r&&u_f_u_r&&u_f_a_n&&u_f_u_n)){
//                saveUnitFixedOk(line);
//            }
//            if(isPersonNameNok(col.at(getColNum("代（经）办人姓名")))&&isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))&&
//                    isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))&&isPersonAddNok(col.at(getColNum("代（经）办人证件地址")))&&
//                    isPersonAddNok(col.at(getColNum("代（经）办人通讯地址")))&&isUnitNameNok(col.at(getColNum("单位名称")))&&isUnitNumNok(col.at(getColNum("单位证件号码")))&&
//                    isUnitTypeNok(col.at(getColNum("单位证件类型")))&&
//                    isUnitAddNok(col.at(getColNum("单位证件地址")))&&isUnitAddNok(col.at(getColNum("单位通讯地址")))&&isUnitAddNok(col.at(getColNum("单位装机地址")))){
//                saveAllNok(line);
//            }
//        }
//        else {
//            bool u_m_o_r=false;//单位移动用户-使用人信息未登记
//            bool u_m_a_r=false;//单位移动用户-代办人信息未登记
//            bool u_m_u_r=false;//单位移动用户-单位信息未登记

//            if(isNotReg(col.at(getColNum("机主用户姓名")))||isNotReg(col.at(getColNum("机主证件号码")))||isNotReg(col.at(getColNum("机主证件地址")))||isNotReg(col.at(getColNum("机主证件类型")))){
//                saveUnitMobileOwnerNotReg(line);
//                u_m_o_r=true;
//            }
//            if(isNotReg(col.at(getColNum("代（经）办人姓名")))||isNotReg(col.at(getColNum("代（经）办人证件类型")))||
//                    isNotReg(col.at(getColNum("代（经）办人证件号码")))||isNotReg(col.at(getColNum("代（经）办人证件地址")))||isNotReg(col.at(getColNum("代（经）办人通讯地址")))){
//                saveUnitMobileAgentNotReg(line);
//                u_m_a_r=true;
//            }
//            if(isNotReg(col.at(getColNum("单位名称")))||isNotReg(col.at(getColNum("单位证件号码")))||isNotReg(col.at(getColNum("单位证件类型")))||
//                    isNotReg(col.at(getColNum("单位证件地址")))||isNotReg(col.at(getColNum("单位通讯地址")))||isNotReg(col.at(getColNum("单位装机地址")))){
//                saveUnitMobileUnitNotReg(line);
//                u_m_u_r=true;
//            }
//            if(u_m_o_r&&u_m_u_r){
//                saveUnitMobileOwnerUnitNotReg(line);
//            }
//            if(u_m_a_r&&u_m_u_r){
//                saveUnitMobileAgentUnitNotReg(line);
//            }
//            if(u_m_o_r&&u_m_a_r&&u_m_u_r){
//                saveUnitMobileOwnerAgentUnitNotReg(line);
//            }
//            if(isNotReg(col.at(getColNum("机主用户姓名")))&&isNotReg(col.at(getColNum("机主证件号码")))&&isNotReg(col.at(getColNum("机主证件地址")))&&
//                    isNotReg(col.at(getColNum("机主证件类型")))&&isNotReg(col.at(getColNum("代（经）办人姓名")))&&isNotReg(col.at(getColNum("代（经）办人证件类型")))&&
//                    isNotReg(col.at(getColNum("代（经）办人证件号码")))&&isNotReg(col.at(getColNum("代（经）办人证件地址")))&&isNotReg(col.at(getColNum("代（经）办人通讯地址")))&&
//                isNotReg(col.at(getColNum("单位名称")))&&isNotReg(col.at(getColNum("单位证件号码")))&&isNotReg(col.at(getColNum("单位证件类型")))&&
//                    isNotReg(col.at(getColNum("单位证件地址")))&&isNotReg(col.at(getColNum("单位通讯地址")))&&isNotReg(col.at(getColNum("单位装机地址")))){
//                saveAllNotReg(line);
//            }
//            bool u_m_o_n=false;//单位移动用户-使用人信息不合规
//            bool u_m_a_n=false;//单位移动用户-代办人信息不合规
//            bool u_m_u_n=false;//单位移动用户-单位信息不合规

//            if(isPersonNameNok(col.at(getColNum("机主用户姓名")))||isPersonNumNok(col.at(getColNum("机主证件号码")))||isPersonAddNok(col.at(getColNum("机主证件地址")))||
//                    isPersonTypeNok(col.at(getColNum("机主证件类型")))||col.at(getColNum("机主用户姓名"))==col.at(getColNum("代（经）办人姓名"))){
//                saveUnitMobileOwnerNok(line);
//                u_m_o_n=true;
//            }
//            if(isPersonNameNok(col.at(getColNum("代（经）办人姓名")))||isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))||
//                    isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))||isPersonAddNok(col.at(getColNum("代（经）办人证件地址")))||isPersonAddNok(col.at(getColNum("代（经）办人通讯地址")))){
//                saveUnitMobileAgentNok(line);
//                u_m_a_n=true;
//            }
//            if(isUnitNameNok(col.at(getColNum("单位名称")))||isUnitNumNok(col.at(getColNum("单位证件号码")))||isUnitTypeNok(col.at(getColNum("单位证件类型")))||
//                    isUnitAddNok(col.at(getColNum("单位证件地址")))||isUnitAddNok(col.at(getColNum("单位通讯地址")))||isUnitAddNok(col.at(getColNum("单位装机地址")))){
//                saveUnitMobileUnitNok(line);
//                u_m_u_n=true;
//            }
//            if(u_m_o_n&&u_m_a_n){
//                saveUnitMobileOwnerAgentNok(line);
//            }
//            if(u_m_o_n&&u_m_u_n){
//                saveUnitMobileOwnerUnitNok(line);
//            }
//            if(u_m_a_n&&u_m_u_n){
//                saveUnitMobileAgentUnitNok(line);
//            }
//            if(u_m_o_n&&u_m_a_n&&u_m_u_n){
//                saveUnitMobileOwnerAgentUnitNok(line);
//            }
//            if(!(u_m_o_r&&u_m_a_r&&u_m_u_r&&u_m_o_n&&u_m_a_n&&u_m_u_n)){
//                saveUnitMobileOk(line);
//            }
//            if(isPersonNameNok(col.at(getColNum("机主用户姓名")))&&isPersonNumNok(col.at(getColNum("机主证件号码")))&&isPersonAddNok(col.at(getColNum("机主证件地址")))&&
//                    isPersonTypeNok(col.at(getColNum("机主证件类型")))&&col.at(getColNum("机主用户姓名"))==col.at(getColNum("代（经）办人姓名"))&&
//                    isPersonNameNok(col.at(getColNum("代（经）办人姓名")))&&isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))&&
//                    isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))&&isPersonAddNok(col.at(getColNum("代（经）办人证件地址")))&&
//                    isPersonAddNok(col.at(getColNum("代（经）办人通讯地址")))&&isUnitNameNok(col.at(getColNum("单位名称")))&&isUnitNumNok(col.at(getColNum("单位证件号码")))&&
//                    isUnitTypeNok(col.at(getColNum("单位证件类型")))&&isUnitAddNok(col.at(getColNum("单位证件地址")))&&isUnitAddNok(col.at(getColNum("单位通讯地址")))&&
//                    isUnitAddNok(col.at(getColNum("单位装机地址")))){
//                saveAllNok(line);
//            }
//        }
//    }
//    else if(col.at(getColNum("用户类型"))==userType.value("industry")){
//        if(bizTypeFixed.contains(col.at(getColNum("用户业务类型")))){
//            bool t_f_a_r=false;//"行业固话用户-代办人未登记
//            bool t_f_u_r=false;//行业固话用户-单位信息未登记
//            bool t_f_l_r=false;//行业固话用户-责任人信息未登记
//            if(isNotReg(col.at(getColNum("代（经）办人姓名")))||isNotReg(col.at(getColNum("代（经）办人证件类型")))||
//                    isNotReg(col.at(getColNum("代（经）办人证件号码")))||isNotReg(col.at(getColNum("代（经）办人证件地址")))||isNotReg(col.at(getColNum("代（经）办人通讯地址")))){
//                saveTradeMobileAgentNotReg(line);
//                t_f_a_r=true;
//            }
//            if(isNotReg(col.at(getColNum("单位名称")))||isNotReg(col.at(getColNum("单位证件号码")))||isNotReg(col.at(getColNum("单位证件类型")))||
//                    isNotReg(col.at(getColNum("单位证件地址")))||isNotReg(col.at(getColNum("单位通讯地址")))||isNotReg(col.at(getColNum("单位装机地址")))){
//                saveTradeMobileUnitNotReg(line);
//                t_f_u_r=true;
//            }
//            if(isNotReg(col.at(getColNum("责任人姓名")))||isNotReg(col.at(getColNum("责任人证件类型")))||isNotReg(col.at(getColNum("责任人证件号码")))||
//                    isNotReg(col.at(getColNum("责任人证件地址")))||isNotReg(col.at(getColNum("责任人通讯地址")))){
//                saveTradeMobileLiableNotReg(line);
//                t_f_l_r=true;
//            }
//            if(t_f_a_r&&t_f_u_r){
//                saveTradeFixedAgentUnitNotReg(line);
//            }
//            if(t_f_a_r&&t_f_l_r){
//                saveTradeMobileLiableAgentNotReg(line);
//            }
//            if(t_f_l_r&&t_f_u_r){
//                saveTradeMobileLiableUnitNotReg(line);
//            }
//            if(t_f_l_r&&t_f_a_r&&t_f_u_r){
//                saveTradeMobileLiableAgentUnitNotReg(line);
//            }
//            if(isNotReg(col.at(getColNum("代（经）办人姓名")))&&isNotReg(col.at(getColNum("代（经）办人证件类型")))&&
//                    isNotReg(col.at(getColNum("代（经）办人证件号码")))&&isNotReg(col.at(getColNum("代（经）办人证件地址")))&&isNotReg(col.at(getColNum("代（经）办人通讯地址")))&&
//                    isNotReg(col.at(getColNum("单位名称")))&&isNotReg(col.at(getColNum("单位证件号码")))&&isNotReg(col.at(getColNum("单位证件类型")))&&
//                                        isNotReg(col.at(getColNum("单位证件地址")))&&isNotReg(col.at(getColNum("单位通讯地址")))&&isNotReg(col.at(getColNum("单位装机地址")))&&
//                    isNotReg(col.at(getColNum("责任人姓名")))&&isNotReg(col.at(getColNum("责任人证件类型")))&&isNotReg(col.at(getColNum("责任人证件号码")))&&
//                                        isNotReg(col.at(getColNum("责任人证件地址")))&&isNotReg(col.at(getColNum("责任人通讯地址")))){
//                saveAllNotReg(line);
//            }
//            bool t_f_a_n=false;//"行业固话用户-代办人不合规
//            bool t_f_u_n=false;//行业固话用户-单位信息不合规
//            if(isPersonNameNok(col.at(getColNum("代（经）办人姓名")))||isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))||
//                    isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))||isPersonAddNok(col.at(getColNum("代（经）办人证件地址")))||
//                    isPersonAddNok(col.at(getColNum("代（经）办人通讯地址")))){
//                saveTradeFixedAgentNok(line);
//                t_f_a_n=true;
//            }
//            if(isUnitNameNok(col.at(getColNum("单位名称")))||isUnitNumNok(col.at(getColNum("单位证件号码")))||isUnitTypeNok(col.at(getColNum("单位证件类型")))||
//                    isUnitAddNok(col.at(getColNum("单位证件地址")))||isUnitAddNok(col.at(getColNum("单位通讯地址")))||isUnitAddNok(col.at(getColNum("单位装机地址")))){
//                saveTradeFixedUnitNotReg(line);
//                saveTradeFixedUnitNok(line);
//                t_f_u_n=true;
//            }
//            if(t_f_a_n&&t_f_u_n){
//                saveTradeFixedAgentUnitNok(line);
//            }
//            if(isPersonNameNok(col.at(getColNum("代（经）办人姓名")))&&isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))&&
//                    isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))&&isPersonAddNok(col.at(getColNum("代（经）办人证件地址")))&&
//                    isPersonAddNok(col.at(getColNum("代（经）办人通讯地址")))&&isUnitNameNok(col.at(getColNum("单位名称")))&&isUnitNumNok(col.at(getColNum("单位证件号码")))&&
//                    isUnitTypeNok(col.at(getColNum("单位证件类型")))&&isUnitAddNok(col.at(getColNum("单位证件地址")))&&isUnitAddNok(col.at(getColNum("单位通讯地址")))&&
//                    isUnitAddNok(col.at(getColNum("单位装机地址")))){
//                saveAllNok(line);
//            }
//            if(!(t_f_l_r&&t_f_a_r&&t_f_u_r&&t_f_a_n&&t_f_u_n)){
//                saveTradeFixedOk(line);
//            }
//        }
//        else {
//            bool t_m_a_r=false;//"行业移动用户-代办人未登记
//            bool t_m_u_r=false;//行业移动用户-单位信息未登记
//            bool t_m_l_r=false;//行业移动用户-责任人信息未登记
//            if(isNotReg(col.at(getColNum("代（经）办人姓名")))||isNotReg(col.at(getColNum("代（经）办人证件类型")))||
//                    isNotReg(col.at(getColNum("代（经）办人证件号码")))||isNotReg(col.at(getColNum("代（经）办人证件地址")))||isNotReg(col.at(getColNum("代（经）办人通讯地址")))){
//                saveTradeMobileAgentNotReg(line);
//                t_m_a_r=true;
//            }
//            if(isNotReg(col.at(getColNum("单位名称")))||isNotReg(col.at(getColNum("单位证件号码")))||isNotReg(col.at(getColNum("单位证件类型")))||
//                    isNotReg(col.at(getColNum("单位证件地址")))||isNotReg(col.at(getColNum("单位通讯地址")))||isNotReg(col.at(getColNum("单位装机地址")))){
//                saveTradeMobileUnitNotReg(line);
//                t_m_u_r=true;
//            }
//            if(isNotReg(col.at(getColNum("责任人姓名")))||isNotReg(col.at(getColNum("责任人证件类型")))||isNotReg(col.at(getColNum("责任人证件号码")))||
//                    isNotReg(col.at(getColNum("责任人证件地址")))||isNotReg(col.at(getColNum("责任人通讯地址")))){
//                saveTradeMobileLiableNotReg(line);
//                t_m_l_r=true;
//            }
//            if(t_m_a_r&&t_m_u_r){
//                saveTradeMobileAgentUnitNotReg(line);
//            }
//            if(t_m_a_r&&t_m_l_r){
//                saveTradeMobileLiableAgentNotReg(line);
//            }
//            if(t_m_l_r&&t_m_u_r){
//                saveTradeMobileLiableUnitNotReg(line);
//            }
//            if(t_m_l_r&&t_m_a_r&&t_m_u_r){
//                saveTradeMobileLiableAgentUnitNotReg(line);
//                saveAllNotReg(line);
//            }
//            bool t_m_a_n=false;//"行业移动用户-代办人不合规
//            bool t_m_u_n=false;//行业移动用户-单位信息不合规
//            bool t_m_l_n=false;//行业移动用户-责任人信息不合规
//            if(isPersonNameNok(col.at(getColNum("代（经）办人姓名")))||isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))||
//                    isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))||isPersonAddNok(col.at(getColNum("代（经）办人证件地址")))||isPersonAddNok(col.at(getColNum("代（经）办人通讯地址")))){
//                saveTradeMobileAgentNok(line);
//                t_m_a_n=true;
//            }
//            if(isUnitNameNok(col.at(getColNum("单位名称")))||isUnitNumNok(col.at(getColNum("单位证件号码")))||isUnitTypeNok(col.at(getColNum("单位证件类型")))||
//                    isUnitNumNok(col.at(getColNum("单位证件地址")))||isUnitAddNok(col.at(getColNum("单位通讯地址")))||isUnitAddNok(col.at(getColNum("单位装机地址")))){
//                saveTradeMobileUnitNok(line);
//                t_m_u_n=true;
//            }
//            if(isPersonNameNok(col.at(getColNum("责任人姓名")))||isPersonTypeNok(col.at(getColNum("责任人证件类型")))||isPersonNumNok(col.at(getColNum("责任人证件号码")))||
//                    isPersonAddNok(col.at(getColNum("责任人证件地址")))||isPersonAddNok(col.at(getColNum("责任人通讯地址")))){
//                saveTradeMobileLiableNok(line);
//                t_m_l_n=true;
//            }
//            if(t_m_a_n&&t_m_u_n){
//                saveTradeMobileAgentUnitNok(line);
//            }
//            if(t_m_l_n&&t_m_a_n){
//                saveTradeMobileLiableAgentNok(line);
//            }
//            if(t_m_l_n&&t_m_u_n){
//                saveTradeMobileLiableUnitNok(line);
//            }
//            if(t_m_l_n&&t_m_a_n&&t_m_u_n){
//                saveTradeMobileLiableAgentUnitNok(line);
//            }
//            if(isPersonNameNok(col.at(getColNum("代（经）办人姓名")))&&isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))&&
//                 isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))&&isPersonAddNok(col.at(getColNum("代（经）办人证件地址")))&&
//                    isPersonAddNok(col.at(getColNum("代（经）办人通讯地址")))&&isUnitNameNok(col.at(getColNum("单位名称")))&&isUnitNumNok(col.at(getColNum("单位证件号码")))&&
//                    isUnitTypeNok(col.at(getColNum("单位证件类型")))&&isUnitNumNok(col.at(getColNum("单位证件地址")))&&
//                    isUnitAddNok(col.at(getColNum("单位通讯地址")))&&isUnitAddNok(col.at(getColNum("单位装机地址")))&&
//                    isPersonNameNok(col.at(getColNum("责任人姓名")))&&isPersonTypeNok(col.at(getColNum("责任人证件类型")))&&isPersonNumNok(col.at(getColNum("责任人证件号码")))&&
//                 isPersonAddNok(col.at(getColNum("责任人证件地址")))&&isPersonAddNok(col.at(getColNum("责任人通讯地址")))){
//                 saveAllNok(line);
//            }
//            if(!(t_m_l_r&&t_m_a_r&&t_m_u_r&&t_m_l_n&&t_m_a_n&&t_m_u_n)){
//                saveTradeMobileOk(line);
//            }
//        }

//    }
////
////    saveAllNotReg(line);
////    saveAllNok(line);
////    saveFieldAbnormal(line);
////    saveAllOk(line);
////    saveWaitData(line);

////    (line);

////    saveOneCard(line);
//}

//void UserDb::saveAllNotReg(QString line){
//    report->allNotReg+=1;
//    writeFile("全量未登记.nreg",line);
//}
//void UserDb::saveAllNok(QString line){
//    report->allNok+=1;
//    writeFile("全量形式不合规.nck",line);
//}
//void UserDb::saveAbnormal(QString line){
//    //不是42列的
//    report->formatNok+=1;
//    writeFile("格式异常数据.abnormal",line);
//}
//void UserDb::saveFieldAbnormal(QString line){
//    //（例如时间格式等不合规）
//    report->fieldNok+=1;
//    writeFile("字段异常数据.abnormal",line);
//}
//void UserDb::saveAllOk(QString line){
//    report->allOk+=1;
//    writeFile("all.ok(全部合规数据)",line);
//}
//void UserDb::saveWaitData(QString line){
//    //todo report->w
//    writeFile("待挖掘记录(-\" + head_loop_num + \".txt)",line);
//}
//void UserDb::savePersonMobileOk(QString line){
//    report->personMobileOk+=1;
//    writeFile("个人移动用户-形式合规数据.ok",line);
//}
//void UserDb::savePersonMobileOwnerTypeNotReg(QString line){
//    report->personMobileOwnerTypeNotReg+=1;
//    writeFile("个人移动用户-证件类型未登记.nreg",line);
//}
//void UserDb::savePersonMobileOwnerNameNotReg(QString line){
//    report->personMobileOwnerNameNotReg += 1;
//    writeFile("个人移动用户-用户姓名未登记.nreg",line);
//}
//void UserDb::savePersonMobileOwnerNumNotReg(QString line){
//    report->personMobileOwnerNumNotReg += 1;
//    writeFile("个人移动用户-证件号码未登记.nreg",line);
//}
//void UserDb::savePersonMobileOwnerAddNotReg(QString line){
//    report->personMobileOwnerAddNotReg += 1;
//    writeFile("个人移动用户-证件地址未登记.nreg",line);
//}
//void UserDb::savePersonMobileOwnerNameNumNotReg(QString line){
//    report->personMobileOwnerNameNumNotReg += 1;
//    writeFile("个人移动用户-用户姓名&证件号码未登记.nreg",line);
//}
//void UserDb::savePersonMobileOwnerNameAddNotReg(QString line){
//    report->personMobileOwnerNameAddNotReg += 1;
//    writeFile("个人移动用户-用户姓名&证件地址未登记.nreg",line);
//}
//void UserDb::savePersonMobileOwnerNumAddNotReg(QString line){
//    report->personMobileOwnerNameAddNotReg += 1;
//    writeFile("个人移动用户-证件号码&证件地址未登记.nreg",line);
//}
//void UserDb::savePersonMobileOwnerNameNumAddNotReg(QString line){
//    report->personMobileOwnerNameNumAddNotReg += 1;
//    writeFile("个人移动用户-用户姓名&证件号码&证件地址未登记.nreg",line);
//}
//void UserDb::savePeronMobileOwnerTyteNok(QString line){
//    report->personMobileOwnerTypeNok += 1;
//    writeFile("个人移动用户-证件类型校验不合规.nck",line);
//}
//void UserDb::savePeronMobileOwnerNameNok(QString line){
//    report->personMobileOwnerNameNok +=1;
//    writeFile("个人移动用户-用户姓名校验不合规.nck",line);
//}
//void UserDb::savePeronMobileOwnerNumNok(QString line){
//    report->personMobileOwnerNumNok +=1;
//    writeFile("个人移动用户-证件号码校验不合规.nck",line);
//}
//void UserDb::savePeronMobileOwnerAddNok(QString line){
//    report->personMobileOwnerAddNok += 1;
//    writeFile("个人移动用户-证件地址校验不合规.nck",line);
//}
//void UserDb::savePeronMobileOwnerNameNumNok(QString line){
//    report->personMobileOwnerNameNumNok+=1;
//    writeFile("个人移动用户-用户姓名&证件号码校验不合规.nck",line);
//}
//void UserDb::savePeronMobileOwnerNameAddNok(QString line){
//    report->personMobileOwnerNameAddNok+=1;
//    writeFile("个人移动用户-用户姓名&证件地址校验不合规.nck",line);
//}
//void UserDb::savePeronMobileOwnerNumAddNok(QString line){
//    report->personMobileOwnerNameNumAddNok+=1;
//    writeFile("个人移动用户-证件号码&证件地址校验不合规.nck",line);
//}
//void UserDb::savePeronMobileOwnerNameNumAddNok(QString line){
//    report->personMobileOwnerNameNumAddNok+=1;
//    writeFile("个人移动用户-用户姓名&证件号码&证件地址校验不合规.nck",line);
//}
//// 个人-固定电话
//void UserDb::savePersonFixedOk(QString line){
//    report->personFixedOk+=1;
//    writeFile("个人固话用户-形式合规数据.ok",line);
//}
//void UserDb::savePersonFixedOwnerTypeNotReg(QString line){
//    report->personFixedOwnerTypeNotReg+=1;
//    writeFile("个人固话用户-证件类型未登记.nreg",line);
//}
//void UserDb::savePersonFixedOwnerNameNotReg(QString line){
//    report->personFixedOwnerNameNotReg+=1;
//    writeFile("个人固话用户-用户姓名未登记.nreg",line);
//}
//void UserDb::savePersonFixedOwnerNumNotReg(QString line){
//    report->personFixedOwnerNameNotReg+=1;
//    writeFile("个人固话用户-证件号码未登记.nreg",line);
//}
//void UserDb::savePersonFixedOwnerAddNotReg(QString line){
//    report->personFixedOwnerAddNotReg+=1;
//    writeFile("个人固话用户-证件地址未登记.nreg",line);
//}
//void UserDb::savePersonFixedOwnerNameNumNotReg(QString line){
//    report->personFixedOwnerNameNumNotReg+=1;
//    writeFile("个人固话用户-用户姓名&证件号码未登记.nreg",line);
//}
//void UserDb::savePersonFixedOwnerNameAddNotReg(QString line){
//    report->personFixedOwnerNameAddNotReg+=1;
//    writeFile("个人固话用户-用户姓名&证件地址未登记.nreg",line);
//}
//void UserDb::savePersonFixedOwnerNumAddNotReg(QString line){
//    report->personFixedOwnerNameAddNotReg+=1;
//    writeFile("个人固话用户-证件号码&证件地址未登记.nreg",line);
//}
//void UserDb::savePersonFixedOwnerNameNumAddNotReg(QString line){
//    report->personFixedOwnerNameNumAddNotReg+=1;
//    writeFile("个人固话用户-用户姓名&证件号码&证件地址未登记.nreg",line);
//}
//void UserDb::savePersonFixedOwnerTypeNok(QString line){
//    report->personFixedOwnerTypeNok+=1;
//    writeFile("个人固话用户-证件类型校验不合规.nck",line);
//}
//void UserDb::savePersonFixedOwnerNameNok(QString line){
//    report->personFixedOwnerNameNok+=1;
//    writeFile("个人固话用户-用户姓名校验不合规.nck",line);
//}
//void UserDb::savePersonFixedOwnerNumNok(QString line){
//    report->personFixedOwnerNameNok+=1;
//    writeFile("个人固话用户-证件号码校验不合规.nck",line);
//}
//void UserDb::savePersonFixedOwnerAddNok(QString line){
//    report->personFixedOwnerAddNok+=1;
//    writeFile("个人固话用户-证件地址校验不合规.nck",line);
//}
//void UserDb::savePersonFixedOwnerNameNumNok(QString line){
//    report->personFixedOwnerNameNumNok+=1;
//    writeFile("个人固话用户-用户姓名&证件号码校验不合规.nck",line);
//}
//void UserDb::savePersonFixedOwnerNameAddNok(QString line){
//    report->personFixedOwnerNameAddNok+=1;
//    writeFile("个人固话用户-用户姓名&证件地址校验不合规.nck",line);
//}
//void UserDb::savePersonFixedOwnerNumAddNok(QString line){
//    report->personFixedOwnerNumAddNok+=1;
//    writeFile("个人固话用户-证件号码&证件地址校验不合规.nck",line);
//}
//void UserDb::savePersonFixedOwnerNameNumAddNok(QString line){
//    report->personFixedOwnerNameNumAddNok+=1;
//    writeFile("个人固话用户-用户姓名&证件号码&证件地址校验不合规.nck",line);
//}
//void UserDb::savePeronMobileAgentNotReg(QString line){
//    report->personMobileAgentNotReg+=1;
//    writeFile("个人移动用户-代办人信息未登记.nreg",line);
//}
//void UserDb::savePersonFixedAgentNotReg(QString line){
//    report->personFixedAgentNotReg+=1;
//    writeFile("个人固话用户-代办人信息未登记.nreg",line);
//}
//void UserDb::savePeronMobileAgentNok(QString line){
//    report->personMobileAgentNok+=1;
//    writeFile("个人移动用户-代办人信息校验不合规.nck",line);
//}
//void UserDb::savePersonFixedAgentNok(QString line){
//    report->personFixedAgentNok+=1;
//    writeFile("个人固话用户-代办人信息校验不合规.nck",line);
//}
//void UserDb::saveUnitMobileOk(QString line){
//    report->unitMobileOk+=1;
//    writeFile("单位移动用户-形式合规数据.ok",line);
//}
//void UserDb::saveUnitMobileOwnerNotReg(QString line){
//    report->unitMobileOwnerNotReg+=1;
//    writeFile("单位移动用户-使用人信息未登记.nreg",line);
//}
//void UserDb::saveUnitMobileAgentNotReg(QString line){
//    report->unitMobileAgentNotReg+=1;
//    writeFile("单位移动用户-经办人信息未登记.nreg",line);
//}
//void UserDb::saveUnitMobileUnitNotReg(QString line){
//    report->unitMobileUnitNotReg+=1;
//    writeFile("单位移动用户-单位信息未登记.nreg",line);
//}
//void UserDb::saveUnitMobileOwnerUnitNotReg(QString line){
//    report->unitMobileOwnerUnitNotReg+=1;
//    writeFile("单位移动用户-使用人&单位信息未登记.nreg",line);
//}
//void UserDb::saveUnitMobileAgentUnitNotReg(QString line){
//    report->unitMobileAgentUnitNotReg+=1;
//    writeFile("单位移动用户-经办人&单位信息未登记.nreg",line);
//}
//void UserDb::saveUnitMobileOwnerAgentUnitNotReg(QString line){
//    report->unitMobileOwnerAgentUnitNotReg+=1;
//    writeFile("单位移动用户-使用人&经办人&单位信息未登记.nreg",line);
//}
//void UserDb::saveUnitMobileOwnerNok(QString line){
//    report->unitMobileOwnerNok+=1;
//    writeFile("单位移动用户-使用人信息校验不合规.nck",line);
//}
//void UserDb::saveUnitMobileAgentNok(QString line){
//    report->unitMobileAgentNok+=1;
//    writeFile("单位移动用户-经办人信息校验不合规.nck",line);
//}
//void UserDb::saveUnitMobileUnitNok(QString line){
//    report->unitMobileUnitNok+=1;
//    writeFile("单位移动用户-单位信息校验不合规.nck",line);
//}
//void UserDb::saveUnitMobileOwnerAgentNok(QString line){
//    report->unitMobileAgentNok+=1;
//    writeFile("单位移动用户-使用人&经办人信息校验不合规.nck",line);
//}
//void UserDb::saveUnitMobileOwnerUnitNok(QString line){
//    report->unitMobileOwnerUnitNok+=1;
//    writeFile("单位移动用户-使用人&单位信息校验不合规.nck",line);
//}
//void UserDb::saveUnitMobileAgentUnitNok(QString line){
//    report->unitMobileAgentUnitNok+=1;
//    writeFile("单位移动用户-经办人&单位信息校验不合规.nck",line);
//}
//void UserDb::saveUnitMobileOwnerAgentUnitNok(QString line){
//    report->unitMobileAgentUnitNok+=1;
//    writeFile("单位移动用户-使用人&经办人&单位信息校验不合规.nck",line);
//}
//void UserDb::saveUnitFixedOk(QString line){
//    report->unitFixedOk+=1;
//    writeFile("单位固话用户-形式合规数据.ok",line);
//}
//void UserDb::saveUnitFixedOwnerNotReg(QString line){
//    report->unitFixedOwnerNotReg+=1;
//    writeFile("单位固话用户-形式合规数据.ok",line);
//}
//void UserDb::saveUnitFixedAgentNotReg(QString line){
//    report->unitFixedAgentNotReg+=1;
//    writeFile("单位固话用户-经办人信息未登记.nreg",line);
//}
//void UserDb::saveUnitFixedUnitNotReg(QString line){
//    report->unitFixedUnitNotReg+=1;
//    writeFile("单位固话用户-单位信息未登记.nreg",line);
//}
//void UserDb::saveUnitFixedOwnerAgentNotReg(QString line){
//    report->unitFixedOwnerAgentNotReg+=1;
//    writeFile("单位固话用户-使用人&经办人信息未登记.nreg",line);
//}
//void UserDb::saveUnitFixedOwnerUnitNotReg(QString line){
//    report->unitFixedOwnerUnitNotReg+=1;
//    writeFile("单位固话用户-使用人&单位信息未登记.nreg",line);
//}
//void UserDb::saveUnitFixedAgentUnitNotReg(QString line){
//    report->unitFixedAgentUnitNotReg+=1;
//    writeFile("单位固话用户-经办人&单位信息未登记.nreg",line);
//}
//void UserDb::saveUnitFixedOwnerAgentUnitNotReg(QString line){
//    report->unitFixedOwnerAgentUnitNotReg+=1;
//    writeFile("单位固话用户-使用人&经办人&单位信息未登记.nreg",line);
//}
//void UserDb::saveUnitFixedAgentNok(QString line){
//    report->unitFixedAgentNok+=1;
//    writeFile("单位固话用户-经办人信息校验不合规.nck",line);
//}
//void UserDb::saveUnitFixedUnitNok(QString line){
//    report->unitFixedUnitNok+=1;
//    writeFile("单位固话用户-单位信息校验不合规.nck",line);
//}
//void UserDb::saveUnitFixedAgentUnitNok(QString line){
//    report->unitFixedAgentUnitNok+=1;
//    writeFile("单位固话用户-经办人&单位信息校验不合规.nck",line);
//}
//void UserDb::saveTradeMobileOk(QString line){
//    report->tradeMobileOk+=1;
//    writeFile("行业移动应用-形式合规数据.ok",line);
//}
//void UserDb::saveTradeMobileAgentNotReg(QString line){
//    report->tradeMobileAgentNotReg+=1;
//    writeFile("行业移动应用-经办人信息未登记.nreg",line);
//}
//void UserDb::saveTradeMobileAgentUnitNotReg(QString line){
//    report->tradeMobileAgentUnitNotReg+=1;
//    writeFile("行业移动应用-经办人&单位信息未登记.nreg",line);
//}
//void UserDb::saveTradeMobileLiableAgentNotReg(QString line){
//    report->tradeMobileLiableAgentNotReg+=1;
//    writeFile("行业移动应用-责任人&经办人信息未登记.nreg",line);
//}
//void UserDb::saveTradeMobileLiableAgentUnitNotReg(QString line){
//    report->tradeMobileLiableAgentUnitNotReg+=1;
//    writeFile("行业移动应用-责任人&经办人&单位信息未登记.nreg",line);
//}
//void UserDb::saveTradeMobileUnitNotReg(QString line){
//    report->tradeMobileUnitNotReg+=1;
//    writeFile("行业移动应用-单位信息未登记.nreg",line);
//}
//void UserDb::saveTradeMobileLiableNotReg(QString line){
//    report->tradeMobileLiableNotReg+=1;
//    writeFile("行业移动应用-责任人信息未登记.nreg",line);
//}
//void UserDb::saveTradeMobileLiableUnitNotReg(QString line){
//    report->tradeMobileLiableUnitNotReg+=1;
//    writeFile("行业移动应用-责任人&单位信息未登记.nreg",line);
//}
//void UserDb::saveTradeMobileAgentNok(QString line){
//    report->tradeMobileAgentNok+=1;
//    writeFile("行业移动应用-经办人信息校验不合规.nck",line);
//}
//void UserDb::saveTradeMobileAgentUnitNok(QString line){
//    report->tradeMobileAgentUnitNok+=1;
//    writeFile("行业移动应用-经办人&单位信息校验不合规.nck",line);
//}
//void UserDb::saveTradeMobileLiableAgentNok(QString line){
//    report->tradeMobileLiableAgentNok+=1;
//    writeFile("行业移动应用-责任人&经办人信息校验不合规.nck",line);
//}
//void UserDb::saveTradeMobileLiableAgentUnitNok(QString line){
//    report->tradeMobileLiableAgentUnitNok+=1;
//    writeFile("行业移动应用-责任人&经办人&单位信息校验不合规.nck",line);
//}
//void UserDb::saveTradeMobileUnitNok(QString line){
//    report->tradeMobileUnitNok+=1;
//    writeFile("行业移动应用-单位信息校验不合规.nck",line);
//}
//void UserDb::saveTradeMobileLiableNok(QString line){
//    report->tradeMobileLiableNok+=1;
//    writeFile("行业移动应用-责任人信息校验不合规.nck",line);
//}
//void UserDb::saveTradeMobileLiableUnitNok(QString line){
//    report->tradeMobileLiableUnitNok+=1;
//    writeFile("行业移动应用-责任人&单位信息校验不合规.nck",line);
//}
//void UserDb::saveTradeFixedOk(QString line){
//    report->tradeFixedOk+=1;
//    writeFile("行业固话应用-形式合规数据.ok",line);
//}
//void UserDb::saveTradeFixedAgentNotReg(QString line){
//    report->tradeFixedAgentNotReg+=1;
//    writeFile("行业固话应用-经办人信息未登记.nreg",line);
//}
//void UserDb::saveTradeFixedAgentUnitNotReg(QString line){
//    report->tradeFixedAgentUnitNotReg+=1;
//    writeFile("行业固话应用-经办人&单位信息未登记.nreg",line);
//}
//void UserDb::saveTradeFixedUnitNotReg(QString line){
//    report->tradeFixedUnitNotReg+=1;
//    writeFile("行业固话应用-单位信息未登记.nreg",line);
//}
//void UserDb::saveTradeFixedAgentNok(QString line){
//    report->tradeFixedAgentNok+=1;
//    writeFile("行业固话应用-经办人信息校验不合规.nck",line);
//}
//void UserDb::saveTradeFixedAgentUnitNok(QString line){
//    report->tradeFixedAgentUnitNok+=1;
//    writeFile("行业固话应用-经办人&单位信息校验不合规.nck",line);
//}
//void UserDb::saveTradeFixedUnitNok(QString line){
//    report->tradeFixedUnitNok+=1;
//    writeFile("行业固话应用-单位信息校验不合规.nck",line);
//}
//void UserDb::savePersonMobileOneCard(QString line){
//    report->personMobileOneCard+=1;
//    writeFile("个人移动一证五卡不合规.nck",line);
//}

//void UserDb::saveLeaveNet(QString line){
//    report->leaveNet +=1;
//    writeFile("非实名制停机和离网状态", line);
//}

///**
// * @brief makeDir 判断结果文件输出文件夹（工作路径）是否存在，不存在则创建。
// * @return 路径存在，或者创建路径成功。
// */
//bool UserDb::makeDir(){
//    QString path = xmlConfig->readWorkingpathValue().value("workingpath");
//    QDir dir(path);
//    if(dir.exists())
//    {
//      return true;
//    }
//    else
//    {
//       bool ok = dir.mkpath(path);//创建多级目录
//       return ok;
//    }
//}

///**
// * @brief UserDb::writeFile 用于写入结果文件。
// * @param filename 目标文件。
// * @param line 欲写入结果文件的行。
// */
//void UserDb::writeFile(QString filename, QString line){
//    QString path = xmlConfig->readWorkingpathValue().value("workingpath");
//    qDebug()<<"writeFile "<<path<<filename;
//    QFile file(path+"\\"+filename);
//    file.open(QFile::Append);
//    line += "\n";
//    file.write(line.toLocal8Bit());
//    file.close();
//}
