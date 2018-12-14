#include "userdb.h"

/**
 * @brief UserDb::UserDb
 * 数据分析文件
 *
 */

UserDb::UserDb()
{
     stopped = false;
//     xmlConfig = new XMLConfigReader();
     QList<QList<QString>> lls = xmlConfig->readAutoid();
     delimeter = xmlConfig->readDelimiterValue();
     qDebug()<<"delimeter="<<delimeter;
     userType=xmlConfig->readUserType();
     path = xmlConfig->readWorkingpathValue().value("workingpath");
     QDateTime current_date_time = QDateTime::currentDateTime();
     QString current_date = current_date_time.toString("yyyyMMddhhmmss");
     path += QDir::separator();
     path += current_date;
     mkMutiDir(path);
     qRegisterMetaType<QVector<int> >("QVector<int>");
//     QDir *temp = new QDir;
//        bool exist = temp->exists(path);
//        if(exist)
//            qDebug()<<"文件夹已经存在！";
//        else
//        {
//            bool ok = temp->mkdir(path); //temp->mkdir(path);
//            if( ok )
//                qDebug()<<"文件夹创建成功！";
//        }
     QString name;
     report = new Report();
//    report->init();
    int num;
    bool ok;
    //初始化列名
    for(int i=0; i<lls.size(); i++){
        name = lls.at(i).at(1);
        num = lls.at(i).at(2).toInt(&ok,10);
        qDebug()<<"col name is "<<name<<" num is "<<num;
        col_name_map.insert(name,num);
    }

    //初始化用户类型为固定电话
    bizTypeFixed = readValueToList(bizTypeFixed, "业务类型固定");//用户业务类型固定，除固定外全是移动号码

    //初始化个人合规证件类型
    personType = readValueToList(personType, "个人证件居民身份证");
    personType = readValueToList(personType, "个人证件临时居民身份证");
    personType = readValueToList(personType, "个人证件户口薄");
    personType = readValueToList(personType, "个人证件中国人民解放军军人身份证件");
    personType = readValueToList(personType, "个人证件中国人民武装警察身份证件");
    personType = readValueToList(personType, "个人证件港澳居民来往内地通行证");
    personType = readValueToList(personType, "个人证件台湾居民来往大陆通行证");
    personType = readValueToList(personType, "个人证件外国公民护照");
    personType = readValueToList(personType, "个人证件法律、行政法规和国家规定的其他有效身份证件");

    //初始化单位合规证件类型
    unitType  = readValueToList(unitType, "单位证件组织机构代码证");


    QList<QString> queryList;
    queryList.append("maxlimit");
    queryList.append("personNameLen_min");
    queryList.append("personNameLen_max");
    queryList.append("personNamePermit_char");
    queryList.append("personCardtypeTime_interval");
    queryList.append("personCard_numLen_min");
    queryList.append("personCard_numLen_max");
    queryList.append("personCard_addLen_min");
    queryList.append("personCard_addLen_max");
    queryList.append("unitNameLen_min");
    queryList.append("unitNameLen_max");
    queryList.append("unitCardtypeTime_interval");
    queryList.append("unitCard_numLen_min");
    queryList.append("unitCard_numLen_max");
    queryList.append("unitCard_addLen_min");
    queryList.append("unitCard_addLen_max");

    QMap<QString,QString> map = xmlConfig->readCommonRuleValue(queryList);
//    bool ok = true;
    maxlimit = map.value("maxlimit");
    personNameMin = map.value("personNameLen_min").compare("-")?map.value("personNameLen_min").toInt(&ok,10):-1;
    personNameMax = map.value("personNameLen_max").compare("-")?map.value("personNameLen_max").toInt(&ok,10):-1;
    personNamePermit = map.value("personNamePermit_char");
    personIntervalTime = map.value("personCardtypeTime_interval");
    personNumMin = map.value("personCard_numLen_min").compare("-")?map.value("personCard_numLen_min").toInt(&ok,10):-1;
    personNumMax = map.value("personCard_numLen_max").compare("-")?map.value("personCard_numLen_max").toInt(&ok,10):-1;
    personAddMin = map.value("personCard_addLen_min").compare("-")?map.value("personCard_addLen_min").toInt(&ok,10):-1;
    personAddMax = map.value("personCard_addLen_max").compare("-")?map.value("personCard_addLen_max").toInt(&ok,10):-1;
    unitNameMin = map.value("unitNameLen_min").compare("-")?map.value("unitNameLen_min").toInt(&ok,10):-1;
    unitNameMax = map.value("unitNameLen_max").compare("-")?map.value("unitNameLen_max").toInt(&ok,10):-1;
    unitIntervalTime = map.value("unitCardtypeTime_interval");
    unitNumMin = map.value("unitCard_numLen_min").compare("-")?map.value("unitCard_numLen_min").toInt(&ok,10):-1;
    unitNumMax = map.value("unitCard_numLen_max").compare("-")?map.value("unitCard_numLen_max").toInt(&ok,10):-1;
    unitAddMin = map.value("unitCard_addLen_min").compare("-")?map.value("unitCard_addLen_min").toInt(&ok,10):-1;
    unitAddMax = map.value("unitCard_addLen_max").compare("-")?map.value("unitCard_addLen_max").toInt(&ok,10):-1;
    //初始化个人用户姓名不合规
    personNameRule = readValueToList(personNameRule, "个人用户姓名comon-rule");
    personNameRule = readValueToList(personNameRule, "个人用户姓名match-rule");
    //初始化单位/行业用户名称不合规
    unitNameRule = readValueToList(unitNameRule, "行业用户姓名comon-rule");
    unitNameRule = readValueToList(unitNameRule, "行业用户姓名match-rule");
    //初始化个人证件号码不合规
    //初始化单位证件号码不合规
    numRule = readValueToList(numRule, "证件号码comon-rule");
    numRule = readValueToList(numRule, "证件号码match-rule");
    //初始化个人证件地址不合规
    //初始化单位证件地址不合规
    addRule = readValueToList(addRule, "证件地址addr-rule");
    addRule = readValueToList(addRule, "证件地址match-rule");

    nonRealName = readValueToList(nonRealName, "业务状态非实名制停机");
    leaveNet = readValueToList(leaveNet, "业务状态不在网");
}

QString UserDb::mkMutiDir(const QString path){
    QDir dir(path);
    if ( dir.exists(path)){
        return path;
    }
    QString parentDir = mkMutiDir(path.mid(0,path.lastIndexOf(QDir::separator())));
    QString dirname = path.mid(path.lastIndexOf(QDir::separator()) + 1);
    QDir parentPath(parentDir);
    if ( !dirname.isEmpty() )
        parentPath.mkpath(dirname);
    return parentDir + QDir::separator() + dirname;
}


QString UserDb::readValueToString(QString query){
    QString rtn = "";
    QList<QString> list = xmlConfig->readValue(query);
    for(int i=0; i<list.size(); i++){
        rtn.append(list.at(i));
    }
    return rtn;
}

QList<QString> UserDb::readValueToList(QList<QString> inList, QString query){

    QList<QString> list = xmlConfig->readValue(query);
    for(int i=0; i<list.size(); i++){
        inList.append(list.at(i));
    }
    return inList;
}

UserDb::~UserDb()
{
    delete report;
    delete xmlConfig;
}
void UserDb::printMessage(){
   // qDebug()<<QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId());
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
    report->init();
    countData();
    qDebug()<<"run begin"<<stopped;
     emit message("waiting...");
////    todo
//    qDebug()<<"bool UserDb::insertDb(QString filename)"<<insertDb(filename);//"C:\\test.txt");// /Users/zhangxianjin/qtcode/test.txt");//test_data.txt"); //
//    QThread::sleep(10);
 //   createReport();
    report->setTableValue();
    emit message("finished.");
}



QString UserDb::getColName(QString name){
    //    int rtn = ;
//        qDebug()<<"查询的列名是"<<name<<"列号是"<<col_name_map.value(name)+1;
        return "col"+QString::number(col_name_map.value(name)+1);
}

int UserDb::getColNum(QString name){
    //    int rtn = ;
//        qDebug()<<"查询的列名是"<<name<<"列号是"<<col_name_map.value(name)+1;
        return col_name_map.value(name);
}


QString UserDb::getCol(QString str){
    if(str=="null")
        return nullptr;//"'"+str+"'";
    else
        return str;
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


            processLine(line);
            report->allData +=1;
            qDebug()<<"line "<<line_num++<<" finish :"<<(line);//qPrintable

            if(!stopped && line_num%1000==0)
            {
                    qDebug()<<"commit";
                    qDebug()<<QStringLiteral("1000条数据耗时：")<<tmpTime.elapsed()<<"ms"<<endl;
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

/**
 * @brief UserDb::isNotReg
 * @param str
 * @return 字段未空指针、null或空字符串。
 */
bool UserDb::isNotReg(QString str){
    if(str.isNull())
        return true;
    else if(str.isEmpty())
        return true;
    else if(str.trimmed()=="null")
        return true;
    else if(str.trimmed()=="NULL")
        return true;
    else if(str.trimmed()=="Null")
        return true;
    else
        return false;
}

/**
 * @brief UserDb::isPersonTypeNok
 * @param str 证件类型
 * @return 个人证件类型是否不合规
 */
bool UserDb::isPersonTypeNok(QString str){
    if(!personType.contains(str)){
        qDebug()<<"个人证件类型不合规"<<str<<" "<<personType;
        return true;
    }
    return false;
}

bool UserDb::isUnitTypeNok(QString str){
    qDebug()<<"单位证件类型不合规"<<str<<" "<<unitType;
    return !unitType.contains(str);
}

bool UserDb::isPersonNameNok(QString str){
    if(personNameMin!=-1 && str.length()<personNameMin){
        qDebug()<<personNameMin<<"姓名字数不够"<<str.length()<<" "<<str;
        return true;
    }
    else if(personNameMax!=-1 && str.length()>personNameMax){
        qDebug()<<personNameMax<<"姓名太长"<<str.length()<<" "<<str;
        return true;
    }
    else if(personNameRule.contains(str)){
        qDebug()<<"姓名包含非法字符:  "<<str;
        return true;
    }
    return false;
}

bool UserDb::isUnitNameNok(QString str){
    if(unitNameMin!=-1 && str.length()<unitNameMin){
        qDebug()<<unitNameMin<<"单位名称字数不够"<<str.length()<<str;
        return true;
    }
    else if(unitNameMax!=-1 && str.length()>unitNameMax){
        qDebug()<<unitNameMax<<"单位名称超长"<<str.length()<<str;
        return true;
    }
    else if(unitNameRule.contains(str)){
        qDebug()<<"单位名称不合规"<<str;
        return true;
    }
    return false;
}
bool UserDb::isPersonNumNok(QString str){
    if(personNumMin!=-1 && str.length()<personNumMin){
        qDebug()<<personNumMin<<"个人证件号码长度不够"<<str.length()<<str;
        return true;
    }
    else if(personNumMax!=-1 && str.length()>personNumMax){
        qDebug()<<personNumMax<<"个人证件号码超长"<<str.length()<<str;
        return true;
    }
    else if(numRule.contains(str)){
        qDebug()<<"个人证件号码不合规"<<str;
        return true;
    }
    return false;
}
bool UserDb::isUnitNumNok(QString str){
    if(unitNumMin!=-1 && str.length()<unitNumMin){
        qDebug()<<unitNumMin<<"单位证件号码长度不够"<<str.length()<<str;
        return true;
    }
    else if(unitNumMax!=-1 &&str.length()>unitNumMax){
        qDebug()<<unitNumMax<<"单位证件号码超长"<<str.length()<<str;
        return true;
    }
    else if(numRule.contains(str)){
        qDebug()<<"单位证件号码不合规"<<str;
        return true;
    }
    return false;
}
bool UserDb::isPersonAddNok(QString str){
    if(-1!=personAddMin && str.length()<personAddMin){
        qDebug()<<personAddMin<<"个人证件地址不够"<<str.length()<<str;
        return true;
    }
    else if(-1!=personAddMax && str.length()>personAddMax){
        qDebug()<<personAddMax<<"个人证件地址超长"<<str.length()<<str;
        return true;
    }
    else if(addRule.contains(str)){
        qDebug()<<"个人证件地址不合规"<<str;
        return true;
    }
    return false;
}
bool UserDb::isUnitAddNok(QString str){
    if(-1!=unitAddMin && str.length()<unitAddMin){
        qDebug()<<unitAddMin<<"单位地址长度不够"<<str.length()<<str;
        return true;
    }
    else if(-1!=unitAddMax && str.length()>unitAddMax){
        qDebug()<<unitAddMax<<"单位地址超长"<<str.length()<<str;
        return true;
    }
    else if(addRule.contains(str)){
        qDebug()<<"单位地址不合规"<<str;
        return true;
    }
    return false;
}


void UserDb::processLine(QString line){

    QList<QString> col;
    col =  line.split(delimeter);

    /*格式异常数据*/
    if(col.size() != COL_NUM){
        qDebug()<<"列数不对"<<col.size();
        saveAbnormal(line);
        return;
    }

    /*非实名停机和销户的，不纳入检查范围，单独统计数字，加在报表里。*/
    if(nonRealName.contains(col.at(getColNum("使用状态"))) || leaveNet.contains(col.at(getColNum("使用状态")))){
        saveLeaveNet(line);
        return;
    }

    /* 除用户类型和用户业务类型之外为空的、字段全部为空的，计入全量未登记。 */
    int notRegCount = 0;
    for(int i=0;i<col.size();i++){
        if(isNotReg(col.at(i))){
            notRegCount ++;
        }
    }
    if(notRegCount>=COL_NUM-2){
        saveAllNotReg(line);
        qDebug()<<"count="<<notRegCount<<",col_num="<<COL_NUM;
        return;
    }

    /* 字段异常数据.abnormal */
    if(col.at(getColNum("登记激活时间"))==nullptr || isNotReg(col.at(getColNum("登记激活时间")))){
        saveFieldAbnormal(line);
    }

    /* 根据用户类型和用户业务类型进入到具体逻辑规则中判断和输出。 */
    if(col.at(getColNum("用户类型"))==userType.value("person")){  /*个人用户*/

        if(bizTypeFixed.contains(col.at(getColNum("用户业务类型")))){  /*个人固定用户*/
            processPersonFixed(col, line);
        }
        else {/*个人移动用户*/
            processPersonMobile(col, line);
        }

    }
    else if(col.at(getColNum("用户类型"))==userType.value("unit")){  /*单位用户*/

        if(bizTypeFixed.contains(col.at(getColNum("用户业务类型")))){ /*单位固话用户*/
            processUnitFixed(col,line);
        }
        else {
            processUnitMobile(col,line);
        }
    }
    else if(col.at(getColNum("用户类型"))==userType.value("industry")){
        if(bizTypeFixed.contains(col.at(getColNum("用户业务类型")))){
            processTradeFixed(col, line);
        }
        else {
            processTradeMobile(col, line);

        }

    }
    else{
        saveFieldAbnormal(line);
    }

//    saveOneCard(line);
}

void UserDb::saveAllNotReg(QString line){
    report->allNotReg+=1;
    writeFile("全量未登记.nreg",line);
}
void UserDb::saveAllNok(QString line){
    report->allNok+=1;
    writeFile("全量形式不合规.nck",line);
}
void UserDb::saveAbnormal(QString line){
    report->formatNok+=1;//不是42列的
    writeFile("格式异常数据.abnormal",line);
}
void UserDb::saveFieldAbnormal(QString line){
    report->fieldNok+=1;//（例如时间格式等不合规）
    writeFile("字段异常数据.abnormal",line);
}
void UserDb::saveAllOk(QString line){
    report->allOk+=1;
    writeFile("all.ok(全部合规数据)",line);
}
void UserDb::saveWaitData(QString line){
    //todo report->w
    writeFile("待挖掘记录(-\" + head_loop_num + \".txt)",line);
}
void UserDb::savePersonMobileOk(QString line){
    report->personMobileOk+=1;
    writeFile("个人移动用户-形式合规数据.ok",line);
}
void UserDb::savePersonMobileOwnerTypeNotReg(QString line){
    report->personMobileOwnerTypeNotReg+=1;
    writeFile("个人移动用户-证件类型未登记.nreg",line);
}
void UserDb::savePersonMobileOwnerNameNotReg(QString line){
    report->personMobileOwnerNameNotReg += 1;
    writeFile("个人移动用户-用户姓名未登记.nreg",line);
}
void UserDb::savePersonMobileOwnerNumNotReg(QString line){
    report->personMobileOwnerNumNotReg += 1;
    writeFile("个人移动用户-证件号码未登记.nreg",line);
}
void UserDb::savePersonMobileOwnerAddNotReg(QString line){
    report->personMobileOwnerAddNotReg += 1;
    writeFile("个人移动用户-证件地址未登记.nreg",line);
}
void UserDb::savePersonMobileOwnerNameNumNotReg(QString line){
    report->personMobileOwnerNameNumNotReg += 1;
    writeFile("个人移动用户-用户姓名&证件号码未登记.nreg",line);
}
void UserDb::savePersonMobileOwnerNameAddNotReg(QString line){
    report->personMobileOwnerNameAddNotReg += 1;
    writeFile("个人移动用户-用户姓名&证件地址未登记.nreg",line);
}
void UserDb::savePersonMobileOwnerNumAddNotReg(QString line){
    report->personMobileOwnerNameAddNotReg += 1;
    writeFile("个人移动用户-证件号码&证件地址未登记.nreg",line);
}
void UserDb::savePersonMobileOwnerNameNumAddNotReg(QString line){
    report->personMobileOwnerNameNumAddNotReg += 1;
    writeFile("个人移动用户-用户姓名&证件号码&证件地址未登记.nreg",line);
}
void UserDb::savePersonMobileOwnerTyteNok(QString line){
    report->personMobileOwnerTypeNok += 1;
    writeFile("个人移动用户-证件类型校验不合规.nck",line);
}
void UserDb::savePersonMobileOwnerNameNok(QString line){
    report->personMobileOwnerNameNok +=1;
    writeFile("个人移动用户-用户姓名校验不合规.nck",line);
}
void UserDb::savePersonMobileOwnerNumNok(QString line){
    report->personMobileOwnerNumNok +=1;
    writeFile("个人移动用户-证件号码校验不合规.nck",line);
}
void UserDb::savePersonMobileOwnerAddNok(QString line){
    report->personMobileOwnerAddNok += 1;
    writeFile("个人移动用户-证件地址校验不合规.nck",line);
}
void UserDb::savePersonMobileOwnerNameNumNok(QString line){
    report->personMobileOwnerNameNumNok+=1;
    writeFile("个人移动用户-用户姓名&证件号码校验不合规.nck",line);
}
void UserDb::savePersonMobileOwnerNameAddNok(QString line){
    report->personMobileOwnerNameAddNok+=1;
    writeFile("个人移动用户-用户姓名&证件地址校验不合规.nck",line);
}
void UserDb::savePersonMobileOwnerNumAddNok(QString line){
    report->personMobileOwnerNameNumAddNok+=1;
    writeFile("个人移动用户-证件号码&证件地址校验不合规.nck",line);
}
void UserDb::savePersonMobileOwnerNameNumAddNok(QString line){
    report->personMobileOwnerNameNumAddNok+=1;
    writeFile("个人移动用户-用户姓名&证件号码&证件地址校验不合规.nck",line);
}
// 个人-固定电话
void UserDb::savePersonFixedOk(QString line){
    report->personFixedOk+=1;
    writeFile("个人固话用户-形式合规数据.ok",line);
}
void UserDb::savePersonFixedOwnerTypeNotReg(QString line){
    report->personFixedOwnerTypeNotReg+=1;
    writeFile("个人固话用户-证件类型未登记.nreg",line);
}
void UserDb::savePersonFixedOwnerNameNotReg(QString line){
    report->personFixedOwnerNameNotReg+=1;
    writeFile("个人固话用户-用户姓名未登记.nreg",line);
}
void UserDb::savePersonFixedOwnerNumNotReg(QString line){
    report->personFixedOwnerNameNotReg+=1;
    writeFile("个人固话用户-证件号码未登记.nreg",line);
}
void UserDb::savePersonFixedOwnerAddNotReg(QString line){
    report->personFixedOwnerAddNotReg+=1;
    writeFile("个人固话用户-证件地址未登记.nreg",line);
}
void UserDb::savePersonFixedOwnerNameNumNotReg(QString line){
    report->personFixedOwnerNameNumNotReg+=1;
    writeFile("个人固话用户-用户姓名&证件号码未登记.nreg",line);
}
void UserDb::savePersonFixedOwnerNameAddNotReg(QString line){
    report->personFixedOwnerNameAddNotReg+=1;
    writeFile("个人固话用户-用户姓名&证件地址未登记.nreg",line);
}
void UserDb::savePersonFixedOwnerNumAddNotReg(QString line){
    report->personFixedOwnerNameAddNotReg+=1;
    writeFile("个人固话用户-证件号码&证件地址未登记.nreg",line);
}
void UserDb::savePersonFixedOwnerNameNumAddNotReg(QString line){
    report->personFixedOwnerNameNumAddNotReg+=1;
    writeFile("个人固话用户-用户姓名&证件号码&证件地址未登记.nreg",line);
}
void UserDb::savePersonFixedOwnerTypeNok(QString line){
    report->personFixedOwnerTypeNok+=1;
    writeFile("个人固话用户-证件类型校验不合规.nck",line);
}
void UserDb::savePersonFixedOwnerNameNok(QString line){
    report->personFixedOwnerNameNok+=1;
    writeFile("个人固话用户-用户姓名校验不合规.nck",line);
}
void UserDb::savePersonFixedOwnerNumNok(QString line){
    report->personFixedOwnerNameNok+=1;
    writeFile("个人固话用户-证件号码校验不合规.nck",line);
}
void UserDb::savePersonFixedOwnerAddNok(QString line){
    report->personFixedOwnerAddNok+=1;
    writeFile("个人固话用户-证件地址校验不合规.nck",line);
}
void UserDb::savePersonFixedOwnerNameNumNok(QString line){
    report->personFixedOwnerNameNumNok+=1;
    writeFile("个人固话用户-用户姓名&证件号码校验不合规.nck",line);
}
void UserDb::savePersonFixedOwnerNameAddNok(QString line){
    report->personFixedOwnerNameAddNok+=1;
    writeFile("个人固话用户-用户姓名&证件地址校验不合规.nck",line);
}
void UserDb::savePersonFixedOwnerNumAddNok(QString line){
    report->personFixedOwnerNumAddNok+=1;
    writeFile("个人固话用户-证件号码&证件地址校验不合规.nck",line);
}
void UserDb::savePersonFixedOwnerNameNumAddNok(QString line){
    report->personFixedOwnerNameNumAddNok+=1;
    writeFile("个人固话用户-用户姓名&证件号码&证件地址校验不合规.nck",line);
}
void UserDb::savePersonMobileAgentNotReg(QString line){
    report->personMobileAgentNotReg+=1;
    writeFile("个人移动用户-代办人信息未登记.nreg",line);
}
void UserDb::savePersonFixedAgentNotReg(QString line){
    report->personFixedAgentNotReg+=1;
    writeFile("个人固话用户-代办人信息未登记.nreg",line);
}
void UserDb::savePersonMobileAgentNok(QString line){
    report->personMobileAgentNok+=1;
    writeFile("个人移动用户-代办人信息校验不合规.nck",line);
}
void UserDb::savePersonFixedAgentNok(QString line){
    report->personFixedAgentNok+=1;
    writeFile("个人固话用户-代办人信息校验不合规.nck",line);
}
void UserDb::saveUnitMobileOk(QString line){
    report->unitMobileOk+=1;
    writeFile("单位移动用户-形式合规数据.ok",line);
}
void UserDb::saveUnitMobileOwnerNotReg(QString line){
    report->unitMobileOwnerNotReg+=1;
    writeFile("单位移动用户-使用人信息未登记.nreg",line);
}
void UserDb::saveUnitMobileAgentNotReg(QString line){
    report->unitMobileAgentNotReg+=1;
    writeFile("单位移动用户-经办人信息未登记.nreg",line);
}
void UserDb::saveUnitMobileUnitNotReg(QString line){
    report->unitMobileUnitNotReg+=1;
    writeFile("单位移动用户-单位信息未登记.nreg",line);
}
void UserDb::saveUnitMobileOwnerUnitNotReg(QString line){
    report->unitMobileOwnerUnitNotReg+=1;
    writeFile("单位移动用户-使用人&单位信息未登记.nreg",line);
}
void UserDb::saveUnitMobileAgentUnitNotReg(QString line){
    report->unitMobileAgentUnitNotReg+=1;
    writeFile("单位移动用户-经办人&单位信息未登记.nreg",line);
}
void UserDb::saveUnitMobileOwnerAgentUnitNotReg(QString line){
    report->unitMobileOwnerAgentUnitNotReg+=1;
    writeFile("单位移动用户-使用人&经办人&单位信息未登记.nreg",line);
}
void UserDb::saveUnitMobileOwnerNok(QString line){
    report->unitMobileOwnerNok+=1;
    writeFile("单位移动用户-使用人信息校验不合规.nck",line);
}
void UserDb::saveUnitMobileAgentNok(QString line){
    report->unitMobileAgentNok+=1;
    writeFile("单位移动用户-经办人信息校验不合规.nck",line);
}
void UserDb::saveUnitMobileUnitNok(QString line){
    report->unitMobileUnitNok+=1;
    writeFile("单位移动用户-单位信息校验不合规.nck",line);
}
void UserDb::saveUnitMobileOwnerAgentNok(QString line){
    report->unitMobileAgentNok+=1;
    writeFile("单位移动用户-使用人&经办人信息校验不合规.nck",line);
}
void UserDb::saveUnitMobileOwnerUnitNok(QString line){
    report->unitMobileOwnerUnitNok+=1;
    writeFile("单位移动用户-使用人&单位信息校验不合规.nck",line);
}
void UserDb::saveUnitMobileAgentUnitNok(QString line){
    report->unitMobileAgentUnitNok+=1;
    writeFile("单位移动用户-经办人&单位信息校验不合规.nck",line);
}
void UserDb::saveUnitMobileOwnerAgentUnitNok(QString line){
    report->unitMobileAgentUnitNok+=1;
    writeFile("单位移动用户-使用人&经办人&单位信息校验不合规.nck",line);
}
void UserDb::saveUnitFixedOk(QString line){
    report->unitFixedOk+=1;
    writeFile("单位固话用户-形式合规数据.ok",line);
}
void UserDb::saveUnitFixedOwnerNotReg(QString line){
    report->unitFixedOwnerNotReg+=1;
    writeFile("单位固话用户-形式合规数据.ok",line);
}
void UserDb::saveUnitFixedAgentNotReg(QString line){
    report->unitFixedAgentNotReg+=1;
    writeFile("单位固话用户-经办人信息未登记.nreg",line);
}
void UserDb::saveUnitFixedUnitNotReg(QString line){
    report->unitFixedUnitNotReg+=1;
    writeFile("单位固话用户-单位信息未登记.nreg",line);
}

//void UserDb::saveUnitFixedOwnerAgentNotReg(QString line){
//    report->unitFixedOwnerAgentNotReg+=1;
//    writeFile("单位固话用户-使用人&经办人信息未登记.nreg",line);
//}
//void UserDb::saveUnitFixedOwnerUnitNotReg(QString line){
//    report->unitFixedOwnerUnitNotReg+=1;
//    writeFile("单位固话用户-使用人&单位信息未登记.nreg",line);
//}
void UserDb::saveUnitFixedAgentUnitNotReg(QString line){
    report->unitFixedAgentUnitNotReg+=1;
    writeFile("单位固话用户-经办人&单位信息未登记.nreg",line);
}
//void UserDb::saveUnitFixedOwnerAgentUnitNotReg(QString line){
//    report->unitFixedOwnerAgentUnitNotReg+=1;
//    writeFile("单位固话用户-使用人&经办人&单位信息未登记.nreg",line);
//}
void UserDb::saveUnitFixedAgentNok(QString line){
    report->unitFixedAgentNok+=1;
    writeFile("单位固话用户-经办人信息校验不合规.nck",line);
}
void UserDb::saveUnitFixedUnitNok(QString line){
    report->unitFixedUnitNok+=1;
    writeFile("单位固话用户-单位信息校验不合规.nck",line);
}
void UserDb::saveUnitFixedAgentUnitNok(QString line){
    report->unitFixedAgentUnitNok+=1;
    writeFile("单位固话用户-经办人&单位信息校验不合规.nck",line);
}
void UserDb::saveTradeMobileOk(QString line){
    report->tradeMobileOk+=1;
    writeFile("行业移动应用-形式合规数据.ok",line);
}
void UserDb::saveTradeMobileAgentNotReg(QString line){
    report->tradeMobileAgentNotReg+=1;
    writeFile("行业移动应用-经办人信息未登记.nreg",line);
}
void UserDb::saveTradeMobileAgentUnitNotReg(QString line){
    report->tradeMobileAgentUnitNotReg+=1;
    writeFile("行业移动应用-经办人&单位信息未登记.nreg",line);
}
void UserDb::saveTradeMobileLiableAgentNotReg(QString line){
    report->tradeMobileLiableAgentNotReg+=1;
    writeFile("行业移动应用-责任人&经办人信息未登记.nreg",line);
}
void UserDb::saveTradeMobileLiableAgentUnitNotReg(QString line){
    report->tradeMobileLiableAgentUnitNotReg+=1;
    writeFile("行业移动应用-责任人&经办人&单位信息未登记.nreg",line);
}
void UserDb::saveTradeMobileUnitNotReg(QString line){
    report->tradeMobileUnitNotReg+=1;
    writeFile("行业移动应用-单位信息未登记.nreg",line);
}
void UserDb::saveTradeMobileLiableNotReg(QString line){
    report->tradeMobileLiableNotReg+=1;
    writeFile("行业移动应用-责任人信息未登记.nreg",line);
}
void UserDb::saveTradeMobileLiableUnitNotReg(QString line){
    report->tradeMobileLiableUnitNotReg+=1;
    writeFile("行业移动应用-责任人&单位信息未登记.nreg",line);
}
void UserDb::saveTradeMobileAgentNok(QString line){
    report->tradeMobileAgentNok+=1;
    writeFile("行业移动应用-经办人信息校验不合规.nck",line);
}
void UserDb::saveTradeMobileAgentUnitNok(QString line){
    report->tradeMobileAgentUnitNok+=1;
    writeFile("行业移动应用-经办人&单位信息校验不合规.nck",line);
}
void UserDb::saveTradeMobileLiableAgentNok(QString line){
    report->tradeMobileLiableAgentNok+=1;
    writeFile("行业移动应用-责任人&经办人信息校验不合规.nck",line);
}
void UserDb::saveTradeMobileLiableAgentUnitNok(QString line){
    report->tradeMobileLiableAgentUnitNok+=1;
    writeFile("行业移动应用-责任人&经办人&单位信息校验不合规.nck",line);
}
void UserDb::saveTradeMobileUnitNok(QString line){
    report->tradeMobileUnitNok+=1;
    writeFile("行业移动应用-单位信息校验不合规.nck",line);
}
void UserDb::saveTradeMobileLiableNok(QString line){
    report->tradeMobileLiableNok+=1;
    writeFile("行业移动应用-责任人信息校验不合规.nck",line);
}
void UserDb::saveTradeMobileLiableUnitNok(QString line){
    report->tradeMobileLiableUnitNok+=1;
    writeFile("行业移动应用-责任人&单位信息校验不合规.nck",line);
}
void UserDb::saveTradeFixedOk(QString line){
    report->tradeFixedOk+=1;
    writeFile("行业固话应用-形式合规数据.ok",line);
}
void UserDb::saveTradeFixedOwnerNotReg(QString line){
    report->tradeFixedOwnerNotReg+=1;
    writeFile("行业固话应用-使用人信息未登记.nreg", line);
}
void UserDb::saveTradeFixedOwnerNok(QString line){
    report->tradeFixedOwnerNok+=1;
    writeFile("行业固话应用-使用人信息校验不合规.nreg", line);
}
void UserDb::saveTradeFixedAgentNotReg(QString line){
    report->tradeFixedAgentNotReg+=1;
    writeFile("行业固话应用-经办人信息未登记.nreg",line);
}
void UserDb::saveTradeFixedLiableNotReg(QString line){
    report->tradeFixedLiableNotReg+=1;
    writeFile("行业固话应用-责任人信息未登记.nreg",line);
}
void UserDb::saveTradeFixedAgentUnitNotReg(QString line){
    report->tradeFixedAgentUnitNotReg+=1;
    writeFile("行业固话应用-经办人&单位信息未登记.nreg",line);
}
void UserDb::saveTradeFixedUnitNotReg(QString line){
    report->tradeFixedUnitNotReg+=1;
    writeFile("行业固话应用-单位信息未登记.nreg",line);
}
void UserDb::saveTradeFixedAgentNok(QString line){
    report->tradeFixedAgentNok+=1;
    writeFile("行业固话应用-经办人信息校验不合规.nck",line);
}
void UserDb::saveTradeFixedAgentUnitNok(QString line){
    report->tradeFixedAgentUnitNok+=1;
    writeFile("行业固话应用-经办人&单位信息校验不合规.nck",line);
}
void UserDb::saveTradeFixedUnitNok(QString line){
    report->tradeFixedUnitNok+=1;
    writeFile("行业固话应用-单位信息校验不合规.nck",line);
}
void UserDb::saveTradeMobileOwnerNok(QString line){
    report->tradeMobileOwnerNok+=1;
    writeFile("行业固话应用-单位信息校验不合规.nck",line);
}
void UserDb::saveTradeMobileOwnerNotReg(QString line){
    report->tradeMobileOwnerNotReg+=1;
    writeFile("行业固话应用-单位信息校验不合规.nck",line);
}

void UserDb::saveTradeFixedAgentLiableNotReg(QString line){
    report->tradeFixedAgentLiableNotReg+=1;
    writeFile("行业固话应用-经办人&责任人信息未登记.nreg",line);
}

void UserDb::saveTradeFixedLiableUnitNotReg(QString line){
    report->tradeFixedLiableUnitNotReg+=1;
    writeFile("行业固话应用-单位信息校验不合规.nreg",line);
}
void UserDb::saveTradeFixedAgentLiableUnitNotReg(QString line){
    report->tradeFixedAgentLiableUnitNotReg+=1;
    writeFile("行业固话应用-经办人&责任人&单位信息未登记.nreg",line);
}
void UserDb::saveTradeFixedAgentLiableNok(QString line){
    report->tradeFixedAgentLiableNok+=1;
    writeFile("行业固话应用-经办人&责任人信息校验不合规.nck",line);
}
void UserDb::saveTradeFixedLiableUnitNok(QString line){
    report->tradeFixedLiableUnitNok+=1;
    writeFile("行业固话应用-责任人&单位信息校验不合规.nck",line);
}
void UserDb::saveTradeFixedAgentLiableUnitNok(QString line){
    report->tradeFixedAgentLiableUnitNok+=1;
    writeFile("行业固话应用-经办人&责任人&单位信息校验不合规.nck",line);
}
void UserDb::saveTradeFixedLiableNok(QString line){
    report->tradeFixedLiableNok+=1;
    writeFile("行业固话应用-责任人信息校验不合规.nok",line);
}
void UserDb::savePersonMobileOneCard(QString line){
    report->personMobileOneCard+=1;
    writeFile("个人移动一证五卡不合规.nck",line);
}

void UserDb::saveLeaveNet(QString line){
    report->leaveNet +=1;
    writeFile("非实名制停机和离网状态.txt", line);
}

void UserDb::saveUnitMobileOwnerAgentNotReg(QString line){
    report->unitMobileOwnerAgentNotReg += 1;
    writeFile("单位移动用户-使用人&经办人信息校验不合规.nck",line);
}

/**
 * @brief makeDir 判断结果文件输出文件夹（工作路径）是否存在，不存在则创建。
 * @return 路径存在，或者创建路径成功。
 */
bool UserDb::makeDir(){
    QString path = xmlConfig->readWorkingpathValue().value("workingpath");
    QDir dir(path);
    if(dir.exists())
    {
      return true;
    }
    else
    {
       bool ok = dir.mkpath(path);//创建多级目录
       return ok;
    }
}

/**
 * @brief UserDb::writeFile 用于写入结果文件。
 * @param filename 目标文件。
 * @param line 欲写入结果文件的行。
 */
void UserDb::writeFile(QString filename, QString line){

    qDebug()<<"writeFile "<<path<<"\\"<<filename;
    QFile file(path+"\\"+filename);
    file.open(QFile::Append);
    line += "\n";
    file.write(line.toLocal8Bit());
    file.close();
}



/**
 * @brief UserDb::needAgent
 * @param idCardNum 身份证号
 * @param activeTime 入网激活时间
 * @return 判断代办人必填规则：2018年9月1日后，16周岁，大约120岁，之前是10周岁，大于120岁，就必须有代办人信息。入网时间-证件号码日期>10年
 */
bool UserDb::needAgent(QString idCardNum, QString activeTime){

    QDateTime idDate = QDateTime::fromString(idCardNum.mid(6,8), "yyyyMMdd");
    qDebug()<<"idDate:"<<idDate.toString("yyyy-MM-dd hh:mm:ss");
    QString dateFormat = xmlConfig->readDateformatValue().value("dateformat");//"yyyy-MM-dd hh:mm:ss";
    QDateTime checkTime = QDateTime::fromString("20180901", "yyyyMMdd");
    QDateTime time = QDateTime::fromString(activeTime, dateFormat);
    QDateTime date1,date2;

    qDebug()<<"active time:"<<time.toString("yyyy-MM-dd hh:mm:ss");

    if(time<checkTime){
        date1 = idDate.addYears(10);
    }
    else{
        date1 = idDate.addYears(16);
    }
    date2 = idDate.addYears(120);

    return date1>time||date2<time;
}

int UserDb::getDateForInt(QString activeTime){


    QString dateFormat = xmlConfig->readDateformatValue().value("dateformat");//"yyyy-MM-dd hh:mm:ss";
    QDateTime time = QDateTime::fromString(activeTime, dateFormat);
    QString timeString = time.toString("yyyyMMdd");
    bool ok;
    return timeString.toInt(&ok,10);
}

/**
 * @brief UserDb::processPersonFixed 处理个人固话信息
 * @param col
 * @param line
 */
void UserDb::processPersonFixed(QList<QString> col, QString line){
    /* 个人固定用户-证件类型未登记 */
   bool typeNotReg = false;
   if(isNotReg(col.at(getColNum("机主证件类型")))){
       typeNotReg = true;
   }

    /* 个人固定用户-用户姓名未登记 */
   bool nameNotReg = false;
   if(isNotReg(col.at(getColNum("机主用户姓名")))){
       nameNotReg = true;
   }

   /* 个人固定用户-证件号码未登记 */
   bool numNotReg = false;
   if(isNotReg(col.at(getColNum("机主证件号码")))){
       numNotReg = true;
   }

   /* 个人固定用户-证件地址未登记 */
   bool addNotReg = false;
   if(isNotReg(col.at(getColNum("机主证件地址")))){
       addNotReg = true;
   }


   if(typeNotReg){
       savePersonFixedOwnerTypeNotReg(line);
       return;
   }
   if(nameNotReg && !numNotReg && !addNotReg){
       savePersonFixedOwnerNameNotReg(line);
       return;
   }
   if(!nameNotReg && numNotReg && !addNotReg){
       savePersonFixedOwnerNumNotReg(line);
       return;
   }
   if(!nameNotReg && !numNotReg && addNotReg){
       savePersonFixedOwnerAddNotReg(line);
       return;
   }
   /* 个人固话用户-用户姓名&证件号码未登记 */
   if(nameNotReg && numNotReg && !addNotReg){
       savePersonFixedOwnerNameNumNotReg(line);
       return;
   }
   /* 个人固话用户-用户姓名&证件号码未登记 */
   if(nameNotReg && !numNotReg && addNotReg){
       savePersonFixedOwnerNameAddNotReg(line);
       return;
   }
   /* 个人固话用户-用户姓名&证件号码未登记 */
   if(!nameNotReg && numNotReg && addNotReg){
       savePersonFixedOwnerNumAddNotReg(line);
       return;
   }
   /* 个人固话用户-用户姓名&证件号码&证件地址未登记 */
   if(nameNotReg && numNotReg && addNotReg){
       savePersonFixedOwnerNameNumAddNotReg(line);
       return;
   }

   /* 判断是否需要代办人 */
   bool isNeedAgent = needAgent(col.at(getColNum("机主证件号码")), col.at(getColNum("登记激活时间")));

   /* 个人固定用户-代办人未登记 */
   if(isNotReg(col.at(getColNum("代（经）办人姓名"))) || isNotReg(col.at(getColNum("代（经）办人证件类型"))) ||
       isNotReg(col.at(getColNum("代（经）办人证件号码")))){
       if(isNeedAgent){
           savePersonFixedAgentNotReg(line);
           return;
       }
   }

   /* 个人固定用户-代办人信息不合规 */
   bool agentNok = false;
   if(col.at(getColNum("机主用户姓名")).compare(col.at(getColNum("代（经）办人姓名")))){
          agentNok = true;
    }
    else if(isNeedAgent && (isPersonNameNok(col.at(getColNum("代（经）办人姓名")))||isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))||
               isPersonNumNok(col.at(getColNum("代（经）办人证件号码"))))){
       agentNok = true;

   }
   else if(needAgent(col.at(getColNum("代（经）办人证件号码")),col.at(getColNum("代（经）办人证件号码")))){
       //代办人如果不满10岁（2018年9月1日后不满16岁），则判为不合规。
       agentNok = true;
   }
   if( agentNok){
       savePersonFixedAgentNok(line);
       return;
   }

   /* 个人固定用户-证件类型不合规 */
   bool typeNok = false;
   if(isPersonTypeNok(col.at(getColNum("机主证件类型")))){
       typeNok = true;
   }

   /* 个人固定用户-用户姓名不合规 */
   bool nameNok = false;
   if(isPersonNameNok(col.at(getColNum("机主用户姓名")))){
       nameNok = true;
   }

   /* 个人固定用户-证件号码不合规 */
   bool numNok = false;
   if(isPersonNumNok(col.at(getColNum("机主证件号码")))){
       numNok = true;
   }

   /* 个人固定用户-证件地址不合规 */
   bool addNok = false;
   if(isPersonAddNok(col.at(getColNum("机主证件地址")))){
       addNok = true;
   }

   if(typeNok){
       savePersonFixedOwnerTypeNok(line);
       return;
   }
   if( nameNok && !numNok && !addNok){
       savePersonFixedOwnerNameNok(line);
       return;
   }
   if( !nameNok && numNok && !addNok){
       savePersonFixedOwnerNumNok(line);
       return;
   }
   if( !nameNok && !numNok && addNok){
       savePersonFixedOwnerAddNok(line);
       return;
   }

   /* 个人固话用户-用户姓名&证件号码校验不合规 */
   if(!agentNok && !typeNok && nameNok && numNok && !addNok){
       savePersonFixedOwnerNameNumNok(line);
       return;
   }

   /* 个人固话用户-用户姓名&证件地址校验不合规 */
   if(!agentNok && !typeNok && nameNok && !numNok && addNok){
       savePersonFixedOwnerNameAddNok(line);
       return;
   }

   /* 个人固话用户-证件号码&证件地址校验不合规 */
   if(!agentNok && !typeNok && !nameNok && numNok && addNok){
       savePersonFixedOwnerNumAddNok(line);
       return;
   }

   /* 个人固话用户-用户姓名&证件号码&证件地址校验不合规 */
   if(!agentNok && !typeNok && nameNok && numNok && addNok){
       savePersonFixedOwnerNumAddNok(line);
       return;
   }



   /* 个人固话用户-形式合规数据 */
   if(!typeNotReg && !nameNotReg && !numNotReg && !addNotReg && !agentNok && !typeNok && !nameNok && !numNok && !addNok){
       savePersonFixedOk(line);
       saveAllOk(line);
       return;
   }

}

/**
 * @brief UserDb::processPersonMobile 处理个人移动用户信息
 * @param col
 * @param line
 */
void UserDb::processPersonMobile(QList<QString> col, QString line){
    /*个人移动用户-证件类型未登记*/
    bool typeNotReg = false;
    if(isNotReg(col.at(getColNum("机主证件类型")))){
        typeNotReg = true;
    }

    /*个人移动用户-用户姓名未登记*/
    bool nameNotReg = false;
    if(isNotReg(col.at(getColNum("机主用户姓名")))){
        nameNotReg = true;
    }

    /*个人移动用户-证件号码未登记*/
    bool numNotReg = false;
    if(isNotReg(col.at(getColNum("机主证件号码")))){
        numNotReg = true;
    }

    /*个人移动用户-证件地址未登记*/
    bool addNotReg = false;
    if(isNotReg(col.at(getColNum("机主证件地址")))){
        addNotReg = true;
    }

    if(typeNotReg){
        savePersonMobileOwnerTypeNotReg(line);
        return;
    }
    if(nameNotReg && !numNotReg && !addNotReg){
        savePersonMobileOwnerNameNotReg(line);
        return;
    }
    if(!nameNotReg && numNotReg && !addNotReg){
        savePersonMobileOwnerNumNotReg(line);
        return;
    }
    if(!nameNotReg && !numNotReg && addNotReg){
        savePersonMobileOwnerAddNotReg(line);
        return;
    }

    /* 个人移动用户-用户姓名&证件号码未登记 */
    if(nameNotReg && numNotReg && !addNotReg){
        savePersonMobileOwnerNameNumNotReg(line);
        return;
    }
    /* 个人移动用户-用户姓名&证件地址未登记 */
    if(nameNotReg && !numNotReg && addNotReg){
        savePersonMobileOwnerNameAddNotReg(line);
        return;
    }
    /* 个人移动用户-证件号码&证件地址未登记 */
    if(!nameNotReg && numNotReg && addNotReg){
        savePersonMobileOwnerNumAddNotReg(line);
        return;
    }
    /* 个人移动用户-用户姓名&证件号码&证件地址未登记 */
    if(nameNotReg && numNotReg && addNotReg){
        savePersonMobileOwnerNameNumAddNotReg(line);
        return;
    }



    /* 个人移动用户-证件类型不合规 */
    bool typeNok=false;
    if(isPersonTypeNok(col.at(getColNum("机主证件类型")))){
        typeNok=true;
    }

    /* 个人移动用户-用户姓名不合规 */
    bool nameNok=false;
    if(isPersonNameNok(col.at(getColNum("机主用户姓名")))){
        nameNok=true;
    }

    /* 个人移动用户-证件号码不合规 */
    bool numNok=false;
    if(isPersonNumNok(col.at(getColNum("机主证件号码")))){
        numNok=true;
    }

     /* 个人移动用户-证件地址不合规 */
    bool addNok=false;
    if(isPersonAddNok(col.at(getColNum("机主证件地址")))){
        addNok=true;
    }

    if(typeNok){
        savePersonMobileOwnerTyteNok(line);
        return;
    }
    if(nameNok && !numNok && !addNok){
        savePersonMobileOwnerNameNok(line);
        return;
    }
    if(!nameNok && numNok && !addNok){
        savePersonMobileOwnerNumNok(line);
        return;
    }
    if(!nameNok && !numNok && addNok){
        savePersonMobileOwnerAddNok(line);
        return;
    }

    /* 个人移动用户-用户姓名&证件号码校验不合规 */
    if(nameNok && numNok && !addNok){
        savePersonMobileOwnerNameNumNok(line);
        return;
    }

    /* 个人移动用户-用户姓名&证件地址校验不合规 */
    if(nameNok && !numNok && addNok){
        savePersonMobileOwnerNameAddNok(line);
        return;
    }

    /* 个人移动用户-证件号码&证件地址校验不合规 */
    if(!nameNok && numNok && addNok){
        savePersonMobileOwnerNumAddNok(line);
        return;
    }

    /* 个人移动用户-用户姓名&证件号码&证件地址校验不合规 */
    if(nameNok && numNok && addNok){
        savePersonMobileOwnerNumAddNok(line);
        return;
    }

    /* 判断是否需要代办人 */
    bool isNeedAgent = needAgent(col.at(getColNum("机主证件号码")), col.at(getColNum("登记激活时间")));

    /*个人移动用户-代办人信息未登记*/
   bool agentNotReg = false;
   if(isNeedAgent && (isNotReg(col.at(getColNum("代（经）办人姓名")))||isNotReg(col.at(getColNum("代（经）办人证件类型")))||
       isNotReg(col.at(getColNum("代（经）办人证件号码"))) || isNotReg(col.at(getColNum("代（经）办人证件地址"))))){

           agentNotReg = true;
           savePersonMobileAgentNotReg(line);
           return;
   }

   /* 个人移动用户-代办人信息不合规 */
   bool agentNok = false;
   if(isNeedAgent && (isPersonNameNok(col.at(getColNum("代（经）办人姓名")))||isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))||
               isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))||
           isPersonAddNok(col.at(getColNum("代（经）办人证件地址"))))){
       agentNok = true;
   }
   if(!agentNotReg && col.at(getColNum("机主用户姓名")).compare(col.at(getColNum("代（经）办人姓名")))){
       agentNok = true;
   }
   if(isNeedAgent && agentNok){
       savePersonMobileAgentNok(line);
       return;
   }


    /* 个人移动用户-形式合规数据 */
    if(!nameNotReg && !numNotReg && !addNotReg && !agentNok && !typeNok && !nameNok && !numNok && !addNok){
        savePersonMobileOk(line);
        saveAllOk(line);
    }

}


/**
 * @brief processUnitFixed 处理单位固话信息
 * @param line
 *
 */
void UserDb::processUnitFixed(QList<QString> col,QString line){

    /* 单位固话用户-代办人信息未登记 */
    bool agentNotReg = false;
    if(isNotReg(col.at(getColNum("代（经）办人姓名")))||isNotReg(col.at(getColNum("代（经）办人证件类型")))||
            isNotReg(col.at(getColNum("代（经）办人证件号码")))){
        agentNotReg = true;
    }

    /* 单位固话用户-单位信息未登记 */
    bool unitNotReg = false;
    if(isNotReg(col.at(getColNum("单位名称")))||isNotReg(col.at(getColNum("单位证件号码")))||isNotReg(col.at(getColNum("单位证件类型")))||
            isNotReg(col.at(getColNum("单位证件地址")))||isNotReg(col.at(getColNum("单位通讯地址")))){
        unitNotReg = true;
    }

    /* 单位固话用户-代办人信息不合规 */
     bool agentNok = false;
    if(isPersonNameNok(col.at(getColNum("代（经）办人姓名")))||isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))||
            isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))){
        agentNok=true;
    }

    /* 单位固话用户-单位信息不合规 */
    bool unitNok = false;
    if(isUnitNameNok(col.at(getColNum("单位名称")))||isUnitNumNok(col.at(getColNum("单位证件号码")))||isUnitTypeNok(col.at(getColNum("单位证件类型")))||
            isUnitAddNok(col.at(getColNum("单位证件地址")))||isUnitAddNok(col.at(getColNum("单位通讯地址")))){
        unitNok=true;
    }

    int activeDate = getDateForInt(col.at(getColNum("登记激活时间")));
    /* 2013年9月1日之前入网的单位固话用户需检查经办人或单位信息中任一个条目，该条目需包含姓名/单位名称、证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。*/
    if(activeDate < 20130901) {
        if( (!agentNotReg && !agentNok) || (!unitNotReg && !unitNok))  {
            saveUnitFixedOk(line);
            saveAllOk(line);
        }
        else{
            if(agentNotReg && !unitNotReg){
                saveUnitFixedUnitNotReg(line);
                return;
            }
            if(!agentNotReg && unitNotReg){
                saveUnitFixedAgentNotReg(line);
                return;
            }

            if(agentNok && !unitNok){
                saveUnitFixedAgentNok(line);
                return;
            }
            if(!agentNok && unitNok){
                saveUnitFixedUnitNok(line);
                return;
            }
            if(agentNok && unitNok){
                saveUnitMobileAgentUnitNok(line);
                return;
            }
        }
    }
    else {
        /* 2013年9月1日之后入网的单位固话用户需检查经办人和单位信息共2个条目，各条目均需包含姓名/单位名称、证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。*/
        if(agentNotReg && !unitNotReg){
            saveUnitFixedUnitNotReg(line);
            return;
        }
        else if(!agentNotReg && unitNotReg){
            saveUnitFixedAgentNotReg(line);
            return;
        }
        else if(agentNotReg && unitNotReg){
            saveUnitFixedAgentUnitNotReg(line);
            return;
        }
        else if(agentNok && !unitNok){
            saveUnitFixedAgentNok(line);
            return;
        }
        else if(!agentNok && unitNok){
            saveUnitFixedUnitNok(line);
            return;
        }
        else if(agentNok && unitNok){
            saveUnitMobileAgentUnitNok(line);
            return;
        }
        else {
            saveUnitFixedOk(line);
            saveAllOk(line);
        }
    }
}

/**
 * @brief processUnitMobile
 * @param col
 * @param line
 */
void UserDb::processUnitMobile(QList<QString> col, QString line){
    /* 单位移动用户-使用人信息未登记 */
    bool ownerNotReg = false;
    if(isNotReg(col.at(getColNum("机主用户姓名"))) || isNotReg(col.at(getColNum("机主证件号码"))) || isNotReg(col.at(getColNum("机主证件地址")))
            || isNotReg(col.at(getColNum("机主证件类型")))){
        ownerNotReg = true;
    }

    /* 单位移动用户-代办人信息未登记 */
    bool agentNotReg = false;
    if(isNotReg(col.at(getColNum("代（经）办人姓名")))||isNotReg(col.at(getColNum("代（经）办人证件类型")))||
            isNotReg(col.at(getColNum("代（经）办人证件号码"))) || isNotReg(col.at(getColNum("代（经）办人证件地址")))){
        agentNotReg = true;
    }

    /* 单位移动用户-单位信息未登记 */
    bool unitNotReg = false;
    if(isNotReg(col.at(getColNum("单位名称")))||isNotReg(col.at(getColNum("单位证件号码")))||isNotReg(col.at(getColNum("单位证件类型")))||
            isNotReg(col.at(getColNum("单位证件地址")))){
        unitNotReg = true;
    }

    /* 单位移动用户-使用人信息不合规 */
    bool ownerNok = false;
    if(isPersonNameNok(col.at(getColNum("机主用户姓名")))||isPersonNumNok(col.at(getColNum("机主证件号码")))||isPersonAddNok(col.at(getColNum("机主证件地址")))||
            isPersonTypeNok(col.at(getColNum("机主证件类型")))||col.at(getColNum("机主用户姓名"))==col.at(getColNum("代（经）办人姓名"))){
        ownerNok = true;
    }


    /* 单位移动用户-代办人信息不合规 */
    bool agentNok = true;
    if(isPersonNameNok(col.at(getColNum("代（经）办人姓名")))||isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))||
            isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))){
        agentNok = true;
    }
    if(col.at(getColNum("机主用户姓名")).compare(col.at(getColNum("代（经）办人姓名")))){
        agentNok = true;
    }

    /* 单位移动用户-单位信息不合规 */
    bool unitNok = true;
    if(isUnitNameNok(col.at(getColNum("单位名称")))||isUnitNumNok(col.at(getColNum("单位证件号码")))||isUnitTypeNok(col.at(getColNum("单位证件类型")))||
            isUnitAddNok(col.at(getColNum("单位证件地址")))||isUnitAddNok(col.at(getColNum("单位通讯地址")))){
        unitNok = true;
    }



    int activeDate = getDateForInt(col.at(getColNum("登记激活时间")));
    /* 2013年9月1日之前入网的单位移动用户，需检查实际使用人、经办人和单位信息中的任1个条目，该条目中需包含姓名/单位名称、证件类型、证件号码、地址四个字段，
     * 并符合完整性和真实性要求。 */
    if(activeDate < 20130901){
        if( (!ownerNotReg && !ownerNok) || (!agentNotReg && !agentNok) || (!unitNotReg&&!unitNok)){
            saveUnitMobileOk(line);
            saveAllOk(line);
        }
        else{
            if(ownerNotReg && !agentNotReg && !unitNotReg){
                saveUnitMobileOwnerNotReg(line);
                return;
            }
            if(!ownerNotReg && agentNotReg && !unitNotReg){
                saveUnitMobileAgentNotReg(line);
                return;
            }
            if(!ownerNotReg && !agentNotReg && unitNotReg){
                saveUnitMobileUnitNotReg(line);
                return;
            }
            if(ownerNotReg && agentNotReg && !unitNotReg){
                saveUnitMobileOwnerAgentNotReg(line);
                return;
            }
            if(ownerNotReg && !agentNotReg && unitNotReg){
                saveUnitMobileOwnerUnitNotReg(line);
                return;
            }
            if(!ownerNotReg && agentNotReg && unitNotReg){
                saveUnitMobileAgentUnitNotReg(line);
                return;
            }
            if(ownerNotReg && agentNotReg && unitNotReg){
                saveUnitMobileOwnerAgentUnitNotReg(line);
                return;
            }
            if(ownerNok && !agentNok && !unitNok){
                saveUnitMobileOwnerNok(line);
                return;
            }
            if(!ownerNok && agentNok && !unitNok){
                saveUnitMobileAgentNok(line);
                return;
            }
            if(!ownerNok && !agentNok && unitNok){
                saveUnitMobileUnitNok(line);
                return;
            }
            if(ownerNok && agentNok && !unitNok){
                saveUnitMobileOwnerAgentNok(line);
                return;
            }
            if(ownerNok && !agentNok && unitNok){
                saveUnitMobileOwnerUnitNok(line);
                return;
            }
            if(!ownerNok && agentNok && unitNok){
                saveUnitMobileAgentUnitNok(line);
                return;
            }
            if(ownerNok && agentNok && unitNok){
                saveUnitMobileOwnerAgentUnitNok(line);
                return;
            }
        }
    }
    else if(activeDate >= 20130901 && activeDate < 20150101){
        /* 2013年9月1日之后，2015年1月1日之前入网的单位移动用户，需检查实际使用人或经办人、单位信息共2个条目，各条目中均需包含姓名/单位名称、
         * 证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。*/
        if( (!ownerNotReg && !agentNotReg && !ownerNok && !agentNok) ||
                (!ownerNotReg && !unitNotReg && !ownerNok && !unitNok) ||
                (!agentNotReg && !unitNotReg && !agentNok && !unitNok) ){
            saveUnitMobileOk(line);
            saveAllOk(line);
        }
        else{
            if(ownerNotReg && !agentNotReg && !unitNotReg){
                saveUnitMobileOwnerNotReg(line);
                return;
            }
            if(!ownerNotReg && agentNotReg && !unitNotReg){
                saveUnitMobileAgentNotReg(line);
                return;
            }
            if(!ownerNotReg && !agentNotReg && unitNotReg){
                saveUnitMobileUnitNotReg(line);
                return;
            }
            if(ownerNotReg && agentNotReg && !unitNotReg){
                saveUnitMobileOwnerAgentNotReg(line);
                return;
            }
            if(ownerNotReg && !agentNotReg && unitNotReg){
                saveUnitMobileOwnerUnitNotReg(line);
                return;
            }
            if(!ownerNotReg && agentNotReg && unitNotReg){
                saveUnitMobileAgentUnitNotReg(line);
                return;
            }
            if(ownerNotReg && agentNotReg && unitNotReg){
                saveUnitMobileOwnerAgentUnitNotReg(line);
                return;
            }


            if(ownerNok && !agentNok && !unitNok){
                saveUnitMobileOwnerNok(line);
                return;
            }
            if(!ownerNok && agentNok && !unitNok){
                saveUnitMobileAgentNok(line);
                return;
            }
            if(!ownerNok && !agentNok && unitNok){
                saveUnitMobileUnitNok(line);
                return;
            }
            if(ownerNok && agentNok && !unitNok){
                saveUnitMobileOwnerAgentNok(line);
                return;
            }
            if(ownerNok && !agentNok && unitNok){
                saveUnitMobileOwnerUnitNok(line);
                return;
            }
            if(!ownerNok && agentNok && unitNok){
                saveUnitMobileAgentUnitNok(line);
                return;
            }
            if(ownerNok && agentNok && unitNok){
                saveUnitMobileOwnerAgentUnitNok(line);
                return;
            }
        }

    }
    else{
        /* 2015年1月1日之后入网的单位移动用户，需检查实际使用人、经办人、单位信息共3个条目，各条目中均需包含姓名/单位名称、证件类型、证件号码、
         * 地址四个字段，并符合完整性和真实性要求。 */
        if(!(ownerNotReg && agentNotReg && unitNotReg && ownerNok && agentNok && unitNok)){
            saveUnitMobileOk(line);
            saveAllOk(line);
        }
        if(ownerNotReg && !agentNotReg && !unitNotReg ){
            saveUnitMobileOwnerNotReg(line);
            return;
        }
        if(!ownerNotReg && agentNotReg && !unitNotReg ){
            saveUnitMobileAgentNotReg(line);
            return;
        }
        if(!ownerNotReg && !agentNotReg && unitNotReg ){
            saveUnitMobileUnitNotReg(line);
            return;
        }
        if(!ownerNok && agentNok && !unitNok ){
            saveUnitMobileAgentNok(line);
            return;
        }
        if(!ownerNok && !agentNok && unitNok ){
            saveUnitMobileUnitNok(line);
            return;
        }
        if(ownerNok && agentNok && !unitNok){
            saveUnitMobileOwnerAgentNok(line);
            return;
        }
        if(ownerNok && agentNok && !unitNok){
            saveUnitMobileOwnerUnitNok(line);
            return;
        }
        if(!ownerNok && agentNok && unitNok){
            saveUnitMobileAgentUnitNok(line);
            return;
        }
        if(ownerNok && agentNok && unitNok){
            saveUnitMobileOwnerAgentUnitNok(line);
            return;
        }
//        if(ownerNotReg && agentNotReg && unitNotReg ){
//            saveAllNotReg(line);
//        }
//        if(ownerNok && agentNok && unitNok){
//            saveAllNok(line);
//        }

    }

}

//void aprocessTradeFixed(QList<QString> col, QString line){
//    /* 行业固话用户-代办人未登记 */
//    bool agentNotReg = false;
//    if(isNotReg(col.at(getColNum("代（经）办人姓名")))||isNotReg(col.at(getColNum("代（经）办人证件类型")))||
//            isNotReg(col.at(getColNum("代（经）办人证件号码")))){
//        agentNotReg = true;
//    }

//    /* 行业固话用户-单位信息未登记 */
//    bool unitNotReg = false;
//    if(isNotReg(col.at(getColNum("单位名称")))||isNotReg(col.at(getColNum("单位证件号码")))||isNotReg(col.at(getColNum("单位证件类型")))||
//            isNotReg(col.at(getColNum("单位证件地址")))){
//        unitNotReg = true;
//    }

//    /* 行业固话用户-责任人信息未登记 */
//    bool liableNotReg = false;
//    if(isNotReg(col.at(getColNum("责任人姓名")))||isNotReg(col.at(getColNum("责任人证件类型")))||isNotReg(col.at(getColNum("责任人证件号码")))||
//            isNotReg(col.at(getColNum("责任人证件地址")))){
//        liableNotReg = true;
//    }


//    /* 行业固话用户-代办人不合规 */
//    bool agentNok = false;
//    if(isPersonNameNok(col.at(getColNum("代（经）办人姓名")))||isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))||
//            isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))){
//        agentNok = true;
//    }
//    if(col.at(getColNum("机主用户姓名")).compare(col.at(getColNum("代（经）办人姓名")))){
//        agentNok = true;
//    }

//    /* 行业固话用户-单位信息不合规 */
//    bool unitNok = false;
//    if(isUnitNameNok(col.at(getColNum("单位名称")))||isUnitNumNok(col.at(getColNum("单位证件号码")))||isUnitTypeNok(col.at(getColNum("单位证件类型")))||
//            isUnitAddNok(col.at(getColNum("单位证件地址")))){
//        unitNok=true;
//    }

//    /* 行业固话用户-责任人信息不合规 */
//    bool liableNok = false;
//    if(isPersonNameNok(col.at(getColNum("责任人姓名")))||isPersonTypeNok(col.at(getColNum("责任人证件类型")))||isPersonNumNok(col.at(getColNum("责任人证件号码")))||
//            isPersonAddNok(col.at(getColNum("责任人证件地址")))){
//        liableNotReg = true;
//    }

//    /* 2013年9月1日之前入网的行业固话用户需检查经办人或单位信息共1个条目，该条目需包含姓名/单位名称、证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。 */
//    int activeDate = getDateForInt(col.at(getColNum("登记激活时间")));
//    if(activeDate < 20130901) {
//        if( (agentNotReg || unitNotReg || liableNotReg) || (agentNok || unitNok || liableNok)){
//            if(agentNotReg && !unitNotReg && !liableNotReg){
//                saveTradeFixedUnitNotReg(line);
//                return;
//            }
//            if(!agentNotReg && unitNotReg && !liableNotReg){
//                saveTradeFixedAgentNotReg(line);
//                return;
//            }
//            if(!agentNotReg && !unitNotReg && liableNotReg){
//                saveTradeFixedLiableNotReg(line);
//                return;
//            }
//            if(agentNotReg && unitNotReg && !liableNotReg){
//                saveTradeFixedAgentUnitNotReg(line);
//                return;
//            }
//            if(agentNotReg && !unitNotReg && liableNotReg){
//                saveTradeFixedAgentLiableNotReg(line);
//                return;
//            }
//            if(!agentNotReg && unitNotReg && liableNotReg){
//                saveTradeFixedLiableUnitNotReg(line);
//                return;
//            }
//            if(agentNotReg && unitNotReg && liableNotReg){
//                saveTradeFixedAgentLiableUnitNotReg(line);
//                return;
//            }
//            if(agentNok && !unitNok && !liableNok){
//                saveTradeFixedAgentNok(line);
//                return;
//            }
//            if(!agentNok && unitNok && !liableNok){
//                saveTradeFixedUnitNok(line);
//                return;
//            }
//            if(agentNok && unitNok  && !liableNok){
//                saveTradeFixedAgentUnitNok(line);
//                return;
//            }
//            if(agentNok && !unitNok  && liableNok){
//                saveTradeFixedAgentLiableNok(line);
//                return;
//            }
//            if(!agentNok && unitNok  && liableNok){
//                saveTradeFixedLiableUnitNok(line);
//                return;
//            }
//            if(agentNok && unitNok  && liableNok){
//                saveTradeFixedAgentLiableUnitNok(line);
//                return;
//            }
//        }
//        else {
//            saveTradeFixedOk(line);
//            saveAllOk(line);
//        }
//    }
//    else {
//        /* 2013年9月1日之后入网的行业固话用户需检查经办人和单位信息共2个条目，各条目均需包含姓名/单位名称、证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。 */
//        if(agentNotReg && !unitNotReg){
//            saveTradeFixedUnitNotReg(line);
//        }
//        else if(!agentNotReg && unitNotReg){
//            saveTradeFixedAgentNotReg(line);
//        }
//        else if(agentNotReg && unitNotReg){
//            saveTradeFixedAgentUnitNotReg(line);
//        }
//        else if(agentNok && !unitNok){
//            saveTradeFixedAgentNok(line);
//        }
//        else if(!agentNok && unitNok){
//            saveTradeFixedUnitNok(line);
//        }
//        else if(agentNok && unitNok){
//            saveTradeMobileAgentUnitNok(line);
//        }
//        else {
//            saveTradeFixedOk(line);
//            saveAllOk(line);
//        }
//    }
//}

/**
 * @brief UserDb::processTradeMobile 处理行业移动数据
 * @param col
 * @param line
 */
void UserDb::processTradeMobile(QList<QString> col, QString line){

    /* 行业移动用户-使用人信息未登记 */
    bool ownerNotReg = false;
    if(isNotReg(col.at(getColNum("机主用户姓名"))) || isNotReg(col.at(getColNum("机主证件号码"))) || isNotReg(col.at(getColNum("机主证件地址")))
            || isNotReg(col.at(getColNum("机主证件类型")))){
        ownerNotReg = true;
    }

    /* 行业移动用户-代办人未登记 */
    bool agentNotReg = false;
    if(isNotReg(col.at(getColNum("代（经）办人姓名")))||isNotReg(col.at(getColNum("代（经）办人证件类型")))||
            isNotReg(col.at(getColNum("代（经）办人证件号码")))){
        agentNotReg = true;
    }

    /* 行业移动用户-单位信息未登记 */
    bool unitNotReg = false;
    if(isNotReg(col.at(getColNum("单位名称")))||isNotReg(col.at(getColNum("单位证件号码")))||isNotReg(col.at(getColNum("单位证件类型")))||
            isNotReg(col.at(getColNum("单位证件地址")))){
        unitNotReg = true;
    }

    /* 行业移动用户-责任人信息未登记 */
    bool liableNotReg = false;
    if(isNotReg(col.at(getColNum("责任人姓名")))||isNotReg(col.at(getColNum("责任人证件类型")))||isNotReg(col.at(getColNum("责任人证件号码")))||
            isNotReg(col.at(getColNum("责任人证件地址")))){
        liableNotReg = true;
    }

    /* 行业移动用户-使用人信息不合规 */
    bool ownerNok = false;
    if(isPersonNameNok(col.at(getColNum("机主用户姓名")))||isPersonNumNok(col.at(getColNum("机主证件号码")))||isPersonAddNok(col.at(getColNum("机主证件地址")))||
            isPersonTypeNok(col.at(getColNum("机主证件类型")))||col.at(getColNum("机主用户姓名"))==col.at(getColNum("代（经）办人姓名"))){
        ownerNok = true;
    }

    /* 行业移动用户-代办人不合规 */
    bool agentNok = false;
    if(isPersonNameNok(col.at(getColNum("代（经）办人姓名")))||isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))||
            isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))){
        agentNok = true;
    }
    if(col.at(getColNum("机主用户姓名")).compare(col.at(getColNum("代（经）办人姓名")))){
        agentNok = true;
    }

    /* 行业移动用户-单位信息不合规 */
    bool unitNok = false;
    if(isUnitNameNok(col.at(getColNum("单位名称")))||isUnitNumNok(col.at(getColNum("单位证件号码")))||isUnitTypeNok(col.at(getColNum("单位证件类型")))||
            isUnitNumNok(col.at(getColNum("单位证件地址")))){
        unitNok=true;
    }

    /* 行业移动用户-责任人信息不合规 */
    bool liableNok = false;
    if(isPersonNameNok(col.at(getColNum("责任人姓名")))||isPersonTypeNok(col.at(getColNum("责任人证件类型")))||isPersonNumNok(col.at(getColNum("责任人证件号码")))||
            isPersonAddNok(col.at(getColNum("责任人证件地址")))){

        liableNok=true;
    }
    /* 如果实际使用人合规，则不需要判断其他字段 */
    int activeDate = getDateForInt(col.at(getColNum("登记激活时间")));
    if( ownerNotReg || ownerNok){
        if(ownerNotReg){
            saveTradeMobileOwnerNotReg(line);
            return;
        }
        if(ownerNok){
            saveTradeMobileOwnerNok(line);
            return;
        }
        /* 2013年9月1日之前入网的行业移动用户，需检查责任人、(实际使用人)、经办人和单位信息中任一个条目，该条目中均需包含姓名/单位名称、证件类型、证件号码、地址，
         * 符合完整性和真实性要求。 */
        if(activeDate < 20130901){
            if((!agentNotReg && !agentNok) || (!unitNotReg && !unitNok) || (!liableNotReg && !liableNok)){
                saveTradeMobileOk(line);
                saveAllOk(line);
                return;
            }
            else {
                if(liableNotReg && !agentNotReg && !unitNotReg){
                    saveTradeMobileLiableNotReg(line);
                    return;
                }
                if(!liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeMobileAgentNotReg(line);
                    return;
                }
                if(!liableNotReg && !agentNotReg && unitNotReg){
                    saveUnitMobileUnitNotReg(line);
                    return;
                }
                if(liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeMobileLiableAgentNotReg(line);
                    return;
                }
                if(liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeMobileLiableUnitNotReg(line);
                    return;
                }
                if(!liableNotReg && agentNotReg && unitNotReg){
                    saveUnitMobileAgentUnitNotReg(line);
                    return;
                }
                if(liableNotReg && agentNotReg && unitNotReg){
                    saveTradeMobileLiableAgentUnitNotReg(line);
                    return;
                }
                if(liableNok && !agentNok && !unitNok){
                    saveTradeMobileLiableNok(line);
                    return;
                }
                if(!liableNok && agentNok && !unitNok){
                    saveTradeMobileAgentNok(line);
                    return;
                }
                if(!liableNok && !agentNok && unitNok){
                    saveUnitMobileUnitNok(line);
                    return;
                }
                if(liableNok && agentNok && !unitNok){
                    saveTradeMobileLiableAgentNok(line);
                    return;
                }
                if(liableNok && !agentNok && unitNok){
                    saveTradeMobileLiableUnitNok(line);
                    return;
                }
                if(!liableNok && agentNok && unitNok){
                    saveUnitMobileAgentUnitNok(line);
                    return;
                }
                if(liableNok && agentNok && unitNok){
                    saveTradeMobileLiableAgentUnitNok(line);
                    return;
                }
            }
        }
        else if(activeDate >= 20130901 && activeDate < 20150101){
            /* 2013年9月1日之后，2015年1月1日之前入网的行业移动用户，需检查责任人(实际使用人就ok)或经办人、单位信息共2个条目，各条目中均需包含姓名/单位名称、
             * 证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。*/

            if( (liableNotReg && agentNotReg) || (liableNotReg && unitNotReg) || (agentNotReg && unitNotReg)){
                if(liableNotReg && !agentNotReg && !unitNotReg){
                    saveTradeMobileLiableNotReg(line);
                    return;
                }
                if(!liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeMobileAgentNotReg(line);
                    return;
                }
                if(!liableNotReg && !agentNotReg && unitNotReg){
                    saveUnitMobileUnitNotReg(line);
                    return;
                }
                if(liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeMobileLiableAgentNotReg(line);
                    return;
                }
                if(liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeMobileLiableUnitNotReg(line);
                    return;
                }
                if(!liableNotReg && agentNotReg && unitNotReg){
                    saveUnitMobileAgentUnitNotReg(line);
                    return;
                }
                if(liableNotReg && agentNotReg && unitNotReg){
                    saveTradeMobileLiableAgentUnitNotReg(line);
                    return;
                }
            }
            if( (liableNok && agentNok) || (liableNok && unitNok) || (agentNok && unitNok)){
                if(liableNok && !agentNok && !unitNok){
                    saveTradeMobileLiableNok(line);
                    return;
                }
                if(!liableNok && agentNok && !unitNok){
                    saveTradeMobileAgentNok(line);
                    return;
                }
                if(!liableNok && !agentNok && unitNok){
                    saveUnitMobileUnitNok(line);
                    return;
                }
                if(liableNok && agentNok && !unitNok){
                    saveTradeMobileLiableAgentNok(line);
                    return;
                }
                if(liableNok && !agentNok && unitNok){
                    saveTradeMobileLiableUnitNok(line);
                    return;
                }
                if(!liableNok && agentNok && unitNok){
                    saveUnitMobileAgentUnitNok(line);
                    return;
                }
                if(liableNok && agentNok && unitNok){
                    saveTradeMobileLiableAgentUnitNok(line);
                    return;
                }
            }
            else{
                saveTradeMobileOk(line);
                saveAllOk(line);
                return;
            }

        }
        else{
            /* 2015年1月1日之后入网的行业移动用户，需检查责任人(实际使用人，优先)、经办人、单位信息共3个条目，各条目中均需包含姓名/单位名称、证件类型、
             * 证件号码、地址四个字段，并符合完整性和真实性要求。 */
            if(agentNotReg && !unitNotReg && !liableNotReg){
                saveTradeMobileAgentNotReg(line);
                return;
            }
            if(!agentNotReg && unitNotReg && !liableNotReg){
                saveTradeMobileUnitNotReg(line);
                return;
            }
            if(!agentNotReg && !unitNotReg && liableNotReg){
                saveTradeMobileLiableNotReg(line);
                return;
            }
            if(agentNotReg && unitNotReg && !liableNotReg){
                saveTradeMobileAgentUnitNotReg(line);
                return;
            }
            if(!agentNotReg && unitNotReg && liableNotReg){
                saveTradeMobileLiableUnitNotReg(line);
                return;
            }
            if(agentNotReg && !unitNotReg && liableNotReg){
                saveTradeMobileLiableAgentNotReg(line);
                return;
            }
            if(agentNotReg && unitNotReg && liableNotReg){
                saveTradeMobileLiableAgentUnitNotReg(line);
                return;
            }
            if(agentNok && !unitNok && !liableNok){
                saveTradeMobileAgentNok(line);
                return;
            }
            if(!agentNok && unitNok && !liableNok){
                saveTradeMobileUnitNok(line);
                return;
            }
            if(!agentNok && !unitNok && liableNok){
                saveTradeMobileLiableNok(line);
                return;
            }
            if(agentNok && unitNok && !liableNok){
                saveTradeMobileAgentUnitNok(line);
                return;
            }
            if(!agentNok && unitNok && liableNok){
                saveTradeMobileAgentUnitNok(line);
                return;
            }
            if(agentNok && !unitNok && liableNok){
                saveTradeMobileLiableAgentNok(line);
                return;
            }
            if(agentNok && unitNok && liableNok){
                saveTradeMobileLiableAgentUnitNok(line);
                return;
            }
            if(!(ownerNok&&agentNok&&unitNok)){
                saveTradeMobileOk(line);
                saveAllOk(line);
                return;
            }

        }


    }
    else {
        saveTradeMobileOk(line);
        saveAllOk(line);
    }

}


/**
 * @brief UserDb::processTradeMobile 处理行业固话数据
 * @param col
 * @param line
 */
void UserDb::processTradeFixed(QList<QString> col, QString line){

    /* 行业固话用户-使用人信息未登记 */
    bool ownerNotReg = false;
    if(isNotReg(col.at(getColNum("机主用户姓名"))) || isNotReg(col.at(getColNum("机主证件号码"))) || isNotReg(col.at(getColNum("机主证件地址")))
            || isNotReg(col.at(getColNum("机主证件类型")))){
        ownerNotReg = true;
    }

    /* 行业固话用户-代办人未登记 */
    bool agentNotReg = false;
    if(isNotReg(col.at(getColNum("代（经）办人姓名")))||isNotReg(col.at(getColNum("代（经）办人证件类型")))||
            isNotReg(col.at(getColNum("代（经）办人证件号码")))){
        agentNotReg = true;
    }

    /* 行业固话用户-单位信息未登记 */
    bool unitNotReg = false;
    if(isNotReg(col.at(getColNum("单位名称")))||isNotReg(col.at(getColNum("单位证件号码")))||isNotReg(col.at(getColNum("单位证件类型")))||
            isNotReg(col.at(getColNum("单位证件地址")))){
        unitNotReg = true;
    }

    /* 行业固话用户-责任人信息未登记 */
    bool liableNotReg = false;
    if(isNotReg(col.at(getColNum("责任人姓名")))||isNotReg(col.at(getColNum("责任人证件类型")))||isNotReg(col.at(getColNum("责任人证件号码")))||
            isNotReg(col.at(getColNum("责任人证件地址")))){
        liableNotReg = true;
    }

    /* 行业固话用户-使用人信息不合规 */
    bool ownerNok = false;
    if(isPersonNameNok(col.at(getColNum("机主用户姓名")))||isPersonNumNok(col.at(getColNum("机主证件号码")))||isPersonAddNok(col.at(getColNum("机主证件地址")))||
            isPersonTypeNok(col.at(getColNum("机主证件类型")))||col.at(getColNum("机主用户姓名"))==col.at(getColNum("代（经）办人姓名"))){
        ownerNok = true;
    }

    /* 行业固话用户-代办人不合规 */
    bool agentNok = false;
    if(isPersonNameNok(col.at(getColNum("代（经）办人姓名")))||isPersonTypeNok(col.at(getColNum("代（经）办人证件类型")))||
            isPersonNumNok(col.at(getColNum("代（经）办人证件号码")))){
        agentNok = true;
    }
    if(col.at(getColNum("机主用户姓名")).compare(col.at(getColNum("代（经）办人姓名")))){
        agentNok = true;
    }

    /* 行业固话用户-单位信息不合规 */
    bool unitNok = false;
    if(isUnitNameNok(col.at(getColNum("单位名称")))||isUnitNumNok(col.at(getColNum("单位证件号码")))||isUnitTypeNok(col.at(getColNum("单位证件类型")))||
            isUnitNumNok(col.at(getColNum("单位证件地址")))){
        unitNok=true;
    }

    /* 行业固话用户-责任人信息不合规 */
    bool liableNok = false;
    if(isPersonNameNok(col.at(getColNum("责任人姓名")))||isPersonTypeNok(col.at(getColNum("责任人证件类型")))||isPersonNumNok(col.at(getColNum("责任人证件号码")))||
            isPersonAddNok(col.at(getColNum("责任人证件地址")))){

        liableNok=true;
    }
    /* 如果实际使用人合规，则不需要判断其他字段 */
    int activeDate = getDateForInt(col.at(getColNum("登记激活时间")));
    if( ownerNotReg || ownerNok){
        if(ownerNotReg){
            saveTradeFixedOwnerNotReg(line);
        }
        if(ownerNok){
            saveTradeFixedOwnerNok(line);
        }
        /* 2013年9月1日之前入网的行业固话用户，需检查责任人、(实际使用人)、经办人和单位信息中任一个条目，该条目中均需包含姓名/单位名称、证件类型、证件号码、地址，
         * 符合完整性和真实性要求。 */
        if(activeDate < 20130901){
            if((!agentNotReg && !agentNok) || (!unitNotReg && !unitNok) || (!liableNotReg && !liableNok)){
                saveTradeFixedOk(line);
                saveAllOk(line);
            }
            else {
                if(liableNotReg && !agentNotReg && !unitNotReg){
                    saveTradeFixedLiableNotReg(line);
                    return;
                }
                if(!liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeFixedAgentNotReg(line);
                    return;
                }
                if(!liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeFixedUnitNotReg(line);
                    return;
                }
                if(liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeFixedAgentLiableNotReg(line);
                    return;
                }
                if(liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeFixedLiableUnitNotReg(line);
                    return;
                }
                if(!liableNotReg && agentNotReg && unitNotReg){
                    saveUnitFixedAgentUnitNotReg(line);
                    return;
                }
                if(liableNotReg && agentNotReg && unitNotReg){
                    saveTradeFixedAgentLiableUnitNotReg(line);
                    return;
                }
                if(liableNok && !agentNok && !unitNok){
                    saveTradeFixedLiableNok(line);
                    return;
                }
                if(!liableNok && agentNok && !unitNok){
                    saveTradeFixedAgentNok(line);
                    return;
                }
                if(!liableNok && !agentNok && unitNok){
                    saveUnitFixedUnitNok(line);
                    return;
                }
                if(liableNok && agentNok && !unitNok){
                    saveTradeFixedAgentLiableNok(line);
                    return;
                }
                if(liableNok && !agentNok && unitNok){
                    saveTradeFixedLiableUnitNok(line);
                    return;
                }
                if(!liableNok && agentNok && unitNok){
                    saveUnitFixedAgentUnitNok(line);
                    return;
                }
                if(liableNok && agentNok && unitNok){
                    saveTradeFixedAgentLiableUnitNok(line);
                    return;
                }
            }
        }
        else if(activeDate >= 20130901 && activeDate < 20150101){
            /* 2013年9月1日之后，2015年1月1日之前入网的行业固话用户，需检查责任人(实际使用人就ok)或经办人、单位信息共2个条目，各条目中均需包含姓名/单位名称、
             * 证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。*/

            if( (liableNotReg && agentNotReg) || (liableNotReg && unitNotReg) || (agentNotReg && unitNotReg)){
                if(liableNotReg && !agentNotReg && !unitNotReg){
                    saveTradeFixedLiableNotReg(line);
                    return;
                }
                if(!liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeFixedAgentNotReg(line);
                    return;
                }
                if(!liableNotReg && !agentNotReg && unitNotReg){
                    saveUnitFixedUnitNotReg(line);
                    return;
                }
                if(liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeFixedAgentLiableNotReg(line);
                    return;
                }
                if(liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeFixedLiableUnitNotReg(line);
                    return;
                }
                if(!liableNotReg && agentNotReg && unitNotReg){
                    saveUnitFixedAgentUnitNotReg(line);
                    return;
                }
                if(liableNotReg && agentNotReg && unitNotReg){
                    saveTradeFixedAgentLiableUnitNotReg(line);
                    return;
                }
            }
            if( (liableNok && agentNok) || (liableNok && unitNok) || (agentNok && unitNok)){
                if(liableNok && !agentNok && !unitNok){
                    saveTradeFixedLiableNok(line);
                    return;
                }
                if(!liableNok && agentNok && !unitNok){
                    saveTradeFixedAgentNok(line);
                    return;
                }
                if(!liableNok && !agentNok && unitNok){
                    saveUnitFixedUnitNok(line);
                    return;
                }
                if(liableNok && agentNok && !unitNok){
                    saveTradeFixedAgentLiableNok(line);
                    return;
                }
                if(liableNok && !agentNok && unitNok){
                    saveTradeFixedLiableUnitNok(line);
                    return;
                }
                if(!liableNok && agentNok && unitNok){
                    saveUnitFixedAgentUnitNok(line);
                    return;
                }
                if(liableNok && agentNok && unitNok){
                    saveTradeFixedAgentLiableUnitNok(line);
                    return;
                }
            }
            else{
                saveTradeFixedOk(line);
                saveAllOk(line);
                return;
            }

        }
        else{
            /* 2015年1月1日之后入网的行业固话用户，需检查责任人(实际使用人，优先)、经办人、单位信息共3个条目，各条目中均需包含姓名/单位名称、证件类型、
             * 证件号码、地址四个字段，并符合完整性和真实性要求。 */
            if(agentNotReg && !unitNotReg && !liableNotReg){
                saveTradeFixedAgentNotReg(line);
                return;
            }
            if(!agentNotReg && unitNotReg && !liableNotReg){
                saveTradeFixedUnitNotReg(line);
                return;
            }
            if(!agentNotReg && !unitNotReg && liableNotReg){
                saveTradeFixedLiableNotReg(line);
                return;
            }
            if(agentNotReg && unitNotReg && !liableNotReg){
                saveTradeFixedAgentUnitNotReg(line);
                return;
            }
            if(!agentNotReg && unitNotReg && liableNotReg){
                saveTradeFixedLiableUnitNotReg(line);
                return;
            }
            if(agentNotReg && !unitNotReg && liableNotReg){
                saveTradeFixedAgentLiableNotReg(line);
                return;
            }
            if(agentNotReg && unitNotReg && liableNotReg){
                saveTradeFixedAgentLiableUnitNotReg(line);
                return;
            }
            if(agentNok && !unitNok && !liableNok){
                saveTradeFixedAgentNok(line);
                return;
            }
            if(!agentNok && unitNok && !liableNok){
                saveTradeFixedUnitNok(line);
                return;
            }
            if(!agentNok && !unitNok && liableNok){
                saveTradeFixedLiableNok(line);
                return;
            }
            if(agentNok && unitNok && !liableNok){
                saveTradeFixedAgentUnitNok(line);
                return;
            }
            if(!agentNok && unitNok && liableNok){
                saveTradeFixedAgentUnitNok(line);
                return;
            }
            if(agentNok && !unitNok && liableNok){
                saveTradeFixedAgentLiableNok(line);
                return;
            }
            if(agentNok && unitNok && liableNok){
                saveTradeFixedAgentLiableUnitNok(line);
                return;
            }
            if(!(ownerNok&&agentNok&&unitNok)){
                saveTradeFixedOk(line);
                saveAllOk(line);
                return;
            }

        }


    }
    else {
        saveTradeFixedOk(line);
        saveAllOk(line);
    }

}
