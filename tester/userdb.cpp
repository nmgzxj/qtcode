#include "userdb.h"

/**
 * @brief UserDb::UserDb
 * 数据分析文件
 *
 */

UserDb::UserDb()
{
     stopped = false;
     report = new Report();
     qRegisterMetaType<QVector<int> >("QVector<int>");

    readConfig();
    initIndex();
}

void UserDb::readConfig(){
    //     xmlConfig = new XMLConfigReader();
         QList<QList<QString>> lls = xmlConfig->readAutoid();
         delimeter = xmlConfig->readDelimiterValue();
         userType=xmlConfig->readUserType();
         path = xmlConfig->readWorkingpathValue().value("workingpath");
         QDateTime current_date_time = QDateTime::currentDateTime();
         QString current_date = current_date_time.toString("yyyyMMddhhmmss");
         path += QDir::separator();
         path += current_date;
         mkMutiDir(path);

         QString name;
        int num;
        bool ok;
        //初始化列名
        for(int i=0; i<lls.size(); i++){
            name = lls.at(i).at(1);
            num = lls.at(i).at(2).toInt(&ok,10);
//            qDebug()<<"col name is "<<name<<" num is "<<num;
            col_name_map.insert(name,num);
        }

        //初始化用户类型为固定电话
        bizTypeFixed = readValueToList(bizTypeFixed, "业务类型固定");//用户业务类型固定，除固定外全是移动号码

//        qDebug()<<"biz type==========================";
//        for(int i=0;i<bizTypeFixed.size();i++){
//            qDebug()<<bizTypeFixed.at(i);
//        }

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
    if ( !dirname.isEmpty() ){
        if(!parentPath.mkpath(dirname)){
            emit messageWarning("创建目录失败，请检查是否有权限。");
        }
    }
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
    QTime    tmpTime;
    readConfig();
    report->init();
    tmpTime.start();
    countData();
    flushFile();
//    qDebug()<<"run begin"<<stopped;
     emit message("waiting...");

    report->setTableValue(path+QDir::separator()+"report.csv");
    emit message("finished.");
    emit messageWarning("检测完成，用时"+QString::number(tmpTime.elapsed()/1000.0)+"秒");
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

void UserDb::initIndex(){
    codeStatusIndex = getColNum("使用状态");
    activeTimeIndex = getColNum("登记激活时间");
    userTypeInex = getColNum("用户类型");
    bizTypeIndex = getColNum("用户业务类型");
    ownerNameIndex = getColNum("机主姓名");
    ownerTypeIndex = getColNum("机主证件类型");
    ownerNumIndex = getColNum("机主证件号码");
    ownerAddIndex = getColNum("机主证件地址");
    agentNameIndex = getColNum("代（经）办人姓名");
    agentTypeIndex = getColNum("代（经）办人证件类型");
    agentNumIndex = getColNum("代（经）办人证件号码");
    agentAddIndex = getColNum("代（经）办人证件地址");
    liableNameIndex = getColNum("责任人姓名");
    liableTypeIndex = getColNum("责任人证件类型");
    liableNumIndex = getColNum("责任人证件号码");
    liableAddIndex = getColNum("责任人证件地址");
    unitNameIndex = getColNum("单位名称");
    unitNumIndex = getColNum("单位证件号码");
    unitTypeIndex = getColNum("单位证件类型");
    unitAddIndex = getColNum("单位证件地址");
    msisdnIndex = getColNum("MSISDN号码");

}



bool UserDb::countData(){
//    qDebug()<<__FUNCTION__;
    if(!fileIsExists(filename)){
        qDebug()<<"文件不存在。\n当前路径是：";
        qDebug()<< QDir::currentPath();
        return false;
    }

    QFile file(filename);
    QTextCodec *code = QTextCodec::codecForName("GBK");//设置文件编码


//    QList<QString> col;
//    QString line = "";
    int line_num = 1;

    if(file.open(QFile::ReadOnly | QFile::Text)){
        //QBuffer buffer(&file);
       // uchar file.map(file.size());
        QTextStream stream(&file);
        stream.setCodec(code);

         do {
            line = stream.readLine();


            processLine();
            report->allData++;
            line_num++;

            if(line_num%1000==0)
            {
                emit message("已处理"+QString::number(line_num)+"行");
            }
        }while(!stopped && !line.isEmpty());
    }
    else{
        emit messageWarning("文件打开错误。");
    }
    return true;
}

/**
 * @brief UserDb::isNotReg
 * @param str
 * @return 字段未空指针、null或空字符串。
 */
bool UserDb::isNotReg(QString *str){
    if(str==nullptr)
        return true;
    else if(str->isEmpty())
        return true;
    else if((*str).trimmed().contains("null", Qt::CaseInsensitive))
        return true;
    else
        return false;
}

bool UserDb::isNotReg(QString const str){
    if(str==nullptr)
        return true;
    else if(str.isEmpty())
        return true;
    else if(str.trimmed().contains("null", Qt::CaseInsensitive))
        return true;
    else
        return false;
}

/**
 * @brief UserDb::isPersonTypeNok
 * @param str 证件类型
 * @return 个人证件类型是否不合规
 */
bool UserDb::isPersonTypeNok(QString const &str){
    if(!personType.contains(str)){
//        qDebug()<<"个人证件类型不合规"<<str<<" "<<personType;
        return true;
    }
    return false;
}

bool UserDb::isUnitTypeNok(QString const &str){
//    qDebug()<<"单位证件类型不合规"<<str<<" "<<unitType;
    return !unitType.contains(str);
}

bool UserDb::isPersonNameNok(QString const & str){
    if(personNameMin!=-1 && str.length()<personNameMin){
//        qDebug()<<personNameMin<<"姓名字数不够"<<str.length()<<" "<<str;
        return true;
    }
    else if(personNameMax!=-1 && str.length()>personNameMax){
//        qDebug()<<personNameMax<<"姓名太长"<<str.length()<<" "<<str;
        return true;
    }
    else if(personNameRule.contains(str)){
//        qDebug()<<"姓名包含非法字符:  "<<str;
        return true;
    }
    return false;
}

bool UserDb::isUnitNameNok(QString const & str){
    if(unitNameMin!=-1 && str.length()<unitNameMin){
//        qDebug()<<unitNameMin<<"单位名称字数不够"<<str.length()<<str;
        return true;
    }
    else if(unitNameMax!=-1 && str.length()>unitNameMax){
//        qDebug()<<unitNameMax<<"单位名称超长"<<str.length()<<str;
        return true;
    }
    else if(unitNameRule.contains(str)){
//        qDebug()<<"单位名称不合规"<<str;
        return true;
    }
    return false;
}
bool UserDb::isPersonNumNok(QString const & str){
    if(personNumMin!=-1 && str.length()<personNumMin){
//        qDebug()<<personNumMin<<"个人证件号码长度不够"<<str.length()<<str;
        return true;
    }
    else if(personNumMax!=-1 && str.length()>personNumMax){
//        qDebug()<<personNumMax<<"个人证件号码超长"<<str.length()<<str;
        return true;
    }
    else if(numRule.contains(str)){
//        qDebug()<<"个人证件号码不合规"<<str;
        return true;
    }
    return false;
}
bool UserDb::isUnitNumNok(QString const & str){
    if(unitNumMin!=-1 && str.length()<unitNumMin){
//        qDebug()<<unitNumMin<<"单位证件号码长度不够"<<str.length()<<str;
        return true;
    }
    else if(unitNumMax!=-1 &&str.length()>unitNumMax){
//        qDebug()<<unitNumMax<<"单位证件号码超长"<<str.length()<<str;
        return true;
    }
    else if(numRule.contains(str)){
//        qDebug()<<"单位证件号码不合规"<<str;
        return true;
    }
    return false;
}
bool UserDb::isPersonAddNok(QString const & str){
    if(-1!=personAddMin && str.length()<personAddMin){
//        qDebug()<<personAddMin<<"个人证件地址不够"<<str.length()<<str;
        return true;
    }
    else if(-1!=personAddMax && str.length()>personAddMax){
//        qDebug()<<personAddMax<<"个人证件地址超长"<<str.length()<<str;
        return true;
    }
    else if(addRule.contains(str)){
//        qDebug()<<"个人证件地址不合规"<<str;
        return true;
    }
    return false;
}
bool UserDb::isUnitAddNok(QString const & str){
    if(-1!=unitAddMin && str.length()<unitAddMin){
//        qDebug()<<unitAddMin<<"单位地址长度不够"<<str.length()<<str;
        return true;
    }
    else if(-1!=unitAddMax && str.length()>unitAddMax){
//        qDebug()<<unitAddMax<<"单位地址超长"<<str.length()<<str;
        return true;
    }
    else if(addRule.contains(str)){
//        qDebug()<<"单位地址不合规"<<str;
        return true;
    }
    return false;
}




void UserDb::processLine(){


    col =  line.split(delimeter);

    /*格式异常数据*/
    if(col.size() != COL_NUM){
//        qDebug()<<"列数不对"<<col.size();
        saveAbnormal();
        return;
    }


    /*非实名停机和销户的，不纳入检查范围，单独统计数字，加在报表里。*/
    if(nonRealName.contains(col.at(codeStatusIndex)) || leaveNet.contains(col.at(codeStatusIndex))){
        saveLeaveNet();
        return;
    }



    /* 字段异常数据.abnormal */
    if(col.at(activeTimeIndex)==nullptr || isNotReg(col[activeTimeIndex])){
        saveFieldAbnormal();
        return;
    }

    /* 根据用户类型和用户业务类型进入到具体逻辑规则中判断和输出。 */
    if(col.at(userTypeInex)==userType.value("person")){  /*个人用户*/

        if(bizTypeFixed.contains(col.at(bizTypeIndex))){  /*个人固定用户*/
            processPersonFixed();
        }
        else {/*个人移动用户*/
            processPersonMobile();
        }

    }
    else if(col.at(userTypeInex)==userType.value("unit")){  /*单位用户*/

        if(bizTypeFixed.contains(col.at(bizTypeIndex))){ /*单位固话用户*/
            processUnitFixed();
        }
        else {
            processUnitMobile();
        }
    }
    else if(col.at(userTypeInex)==userType.value("industry")){
        if(bizTypeFixed.contains(col.at(bizTypeIndex))){
            processTradeFixed();
        }
        else {
            processTradeMobile();

        }

    }
    else{
        //未识别的用户类型
        //QMessageBox::warning(parent,"警告","未识别的用户类型。")
        emit message("未识别的用户类型！");

        saveFieldAbnormal();
        /* 除用户类型和用户业务类型之外为空的、字段全部为空的，计入全量未登记。 */
        int notRegCount = 0;
        for(int i=0;i<col.size();i++){
            if(isNotReg(col[i])){
                notRegCount ++;
            }
        }
        if(notRegCount>=COL_NUM-2){
            saveAllNotReg();
//            qDebug()<<"count="<<notRegCount<<",col_num="<<COL_NUM;
            return;
        }
    }
//    processOneCardMultiName();
    processOneCardFiveNumber();
//    saveOneCard();
}

void UserDb::saveAllNotReg(){
    report->allNotReg++;
    writeFile("全量未登记.nreg", report->allNotReg);
}
void UserDb::saveAllNok(){
    report->allNok++;
    writeFile("全量形式不合规.nck", report->allNok);
}
void UserDb::saveAbnormal(){
    report->formatNok++;//不是42列的
    writeFile("格式异常数据.abnormal", report->formatNok);
}
void UserDb::saveFieldAbnormal(){
    report->fieldNok++;//（例如时间格式等不合规）
    writeFile("字段异常数据.abnormal", report->fieldNok);
}
void UserDb::saveAllOk(){
    report->allOk++;
    writeFile("all.ok(全部合规数据)", report->allOk);
}
void UserDb::saveWaitData(){
    //todo report->w
    writeFile("待挖掘记录(-\" + head_loop_num + \".txt)", 1);
}
void UserDb::savePersonMobileOk(){
    report->personMobileOk++;
    writeFile("个人移动用户-形式合规数据.ok", report->personMobileOk);
}
void UserDb::savePersonMobileOwnerTypeNotReg(){
    report->personMobileOwnerTypeNotReg++;
    writeFile("个人移动用户-证件类型未登记.nreg", report->personMobileOwnerTypeNotReg);
}
void UserDb::savePersonMobileOwnerNameNotReg(){
    report->personMobileOwnerNameNotReg ++;
    writeFile("个人移动用户-用户姓名未登记.nreg", report->personMobileOwnerNameNotReg);
}
void UserDb::savePersonMobileOwnerNumNotReg(){
    report->personMobileOwnerNumNotReg ++;
    writeFile("个人移动用户-证件号码未登记.nreg", report->personMobileOwnerNumNotReg);
}
void UserDb::savePersonMobileOwnerAddNotReg(){
    report->personMobileOwnerAddNotReg ++;
    writeFile("个人移动用户-证件地址未登记.nreg", report->personMobileOwnerAddNotReg);
}
void UserDb::savePersonMobileOwnerNameNumNotReg(){
    report->personMobileOwnerNameNumNotReg ++;
    writeFile("个人移动用户-用户姓名&证件号码未登记.nreg", report->personMobileOwnerNameNumNotReg);
}
void UserDb::savePersonMobileOwnerNameAddNotReg(){
    report->personMobileOwnerNameAddNotReg ++;
    writeFile("个人移动用户-用户姓名&证件地址未登记.nreg", report->personMobileOwnerNameAddNotReg);
}
void UserDb::savePersonMobileOwnerNumAddNotReg(){
    report->personMobileOwnerNameAddNotReg ++;
    writeFile("个人移动用户-证件号码&证件地址未登记.nreg", report->personMobileOwnerNameAddNotReg);
}
void UserDb::savePersonMobileOwnerNameNumAddNotReg(){
    report->personMobileOwnerNameNumAddNotReg ++;
    writeFile("个人移动用户-用户姓名&证件号码&证件地址未登记.nreg", report->personMobileOwnerNameNumAddNotReg);
}
void UserDb::savePersonMobileOwnerTyteNok(){
    report->personMobileOwnerTypeNok ++;
    writeFile("个人移动用户-证件类型校验不合规.nck", report->personMobileOwnerTypeNok);
}
void UserDb::savePersonMobileOwnerNameNok(){
    report->personMobileOwnerNameNok++;
    writeFile("个人移动用户-用户姓名校验不合规.nck",report->personMobileOwnerNameNok);
}
void UserDb::savePersonMobileOwnerNumNok(){
    report->personMobileOwnerNumNok++;
    writeFile("个人移动用户-证件号码校验不合规.nck",report->personMobileOwnerNumNok);
}
void UserDb::savePersonMobileOwnerAddNok(){
    report->personMobileOwnerAddNok ++;
    writeFile("个人移动用户-证件地址校验不合规.nck",report->personMobileOwnerAddNok);
}
void UserDb::savePersonMobileOwnerNameNumNok(){
    report->personMobileOwnerNameNumNok++;
    writeFile("个人移动用户-用户姓名&证件号码校验不合规.nck",report->personMobileOwnerNameNumNok);
}
void UserDb::savePersonMobileOwnerNameAddNok(){
    report->personMobileOwnerNameAddNok++;
    writeFile("个人移动用户-用户姓名&证件地址校验不合规.nck",report->personMobileOwnerNameAddNok);
}
void UserDb::savePersonMobileOwnerNumAddNok(){
    report->personMobileOwnerNameNumAddNok++;
    writeFile("个人移动用户-证件号码&证件地址校验不合规.nck",report->personMobileOwnerNameNumAddNok);
}
void UserDb::savePersonMobileOwnerNameNumAddNok(){
    report->personMobileOwnerNameNumAddNok++;
    writeFile("个人移动用户-用户姓名&证件号码&证件地址校验不合规.nck",report->personMobileOwnerNameNumAddNok);
}
// 个人-固定电话
void UserDb::savePersonFixedOk(){
    report->personFixedOk++;
    writeFile("个人固话用户-形式合规数据.ok",report->personFixedOk);
}
void UserDb::savePersonFixedOwnerTypeNotReg(){
    report->personFixedOwnerTypeNotReg++;
    writeFile("个人固话用户-证件类型未登记.nreg",report->personFixedOwnerTypeNotReg);
}
void UserDb::savePersonFixedOwnerNameNotReg(){
    report->personFixedOwnerNameNotReg++;
    writeFile("个人固话用户-用户姓名未登记.nreg",report->personFixedOwnerNameNotReg);
}
void UserDb::savePersonFixedOwnerNumNotReg(){
    report->personFixedOwnerNameNotReg++;
    writeFile("个人固话用户-证件号码未登记.nreg",report->personFixedOwnerNameNotReg);
}
void UserDb::savePersonFixedOwnerAddNotReg(){
    report->personFixedOwnerAddNotReg++;
    writeFile("个人固话用户-证件地址未登记.nreg",report->personFixedOwnerAddNotReg);
}
void UserDb::savePersonFixedOwnerNameNumNotReg(){
    report->personFixedOwnerNameNumNotReg++;
    writeFile("个人固话用户-用户姓名&证件号码未登记.nreg",report->personFixedOwnerNameNumNotReg);
}
void UserDb::savePersonFixedOwnerNameAddNotReg(){
    report->personFixedOwnerNameAddNotReg++;
    writeFile("个人固话用户-用户姓名&证件地址未登记.nreg",report->personFixedOwnerNameAddNotReg);
}
void UserDb::savePersonFixedOwnerNumAddNotReg(){
    report->personFixedOwnerNameAddNotReg++;
    writeFile("个人固话用户-证件号码&证件地址未登记.nreg",report->personFixedOwnerNameAddNotReg);
}
void UserDb::savePersonFixedOwnerNameNumAddNotReg(){
    report->personFixedOwnerNameNumAddNotReg++;
    writeFile("个人固话用户-用户姓名&证件号码&证件地址未登记.nreg",report->personFixedOwnerNameNumAddNotReg);
}
void UserDb::savePersonFixedOwnerTypeNok(){
    report->personFixedOwnerTypeNok++;
    writeFile("个人固话用户-证件类型校验不合规.nck",report->personFixedOwnerTypeNok);
}
void UserDb::savePersonFixedOwnerNameNok(){
    report->personFixedOwnerNameNok++;
    writeFile("个人固话用户-用户姓名校验不合规.nck",report->personFixedOwnerNameNok);
}
void UserDb::savePersonFixedOwnerNumNok(){
    report->personFixedOwnerNameNok++;
    writeFile("个人固话用户-证件号码校验不合规.nck",report->personFixedOwnerNameNok);
}
void UserDb::savePersonFixedOwnerAddNok(){
    report->personFixedOwnerAddNok++;
    writeFile("个人固话用户-证件地址校验不合规.nck",report->personFixedOwnerAddNok);
}
void UserDb::savePersonFixedOwnerNameNumNok(){
    report->personFixedOwnerNameNumNok++;
    writeFile("个人固话用户-用户姓名&证件号码校验不合规.nck",report->personFixedOwnerNameNumNok);
}
void UserDb::savePersonFixedOwnerNameAddNok(){
    report->personFixedOwnerNameAddNok++;
    writeFile("个人固话用户-用户姓名&证件地址校验不合规.nck",report->personFixedOwnerNameAddNok);
}
void UserDb::savePersonFixedOwnerNumAddNok(){
    report->personFixedOwnerNumAddNok++;
    writeFile("个人固话用户-证件号码&证件地址校验不合规.nck",report->personFixedOwnerNumAddNok);
}
void UserDb::savePersonFixedOwnerNameNumAddNok(){
    report->personFixedOwnerNameNumAddNok++;
    writeFile("个人固话用户-用户姓名&证件号码&证件地址校验不合规.nck",report->personFixedOwnerNameNumAddNok);
}
void UserDb::savePersonMobileAgentNotReg(){
    report->personMobileAgentNotReg++;
    writeFile("个人移动用户-代办人信息未登记.nreg",report->personMobileAgentNotReg);
}
void UserDb::savePersonFixedAgentNotReg(){
    report->personFixedAgentNotReg++;
    writeFile("个人固话用户-代办人信息未登记.nreg",report->personFixedAgentNotReg);
}
void UserDb::savePersonMobileAgentNok(){
    report->personMobileAgentNok++;
    writeFile("个人移动用户-代办人信息校验不合规.nck",report->personMobileAgentNok);
}
void UserDb::savePersonFixedAgentNok(){
    report->personFixedAgentNok++;
    writeFile("个人固话用户-代办人信息校验不合规.nck",report->personFixedAgentNok);
}
void UserDb::saveUnitMobileOk(){
    report->unitMobileOk++;
    writeFile("单位移动用户-形式合规数据.ok",report->unitMobileOk);
}
void UserDb::saveUnitMobileOwnerNotReg(){
    report->unitMobileOwnerNotReg++;
    writeFile("单位移动用户-使用人信息未登记.nreg",report->unitMobileOwnerNotReg);
}
void UserDb::saveUnitMobileAgentNotReg(){
    report->unitMobileAgentNotReg++;
    writeFile("单位移动用户-经办人信息未登记.nreg",report->unitMobileAgentNotReg);
}
void UserDb::saveUnitMobileUnitNotReg(){
    report->unitMobileUnitNotReg++;
    writeFile("单位移动用户-单位信息未登记.nreg",report->unitMobileUnitNotReg);
}
void UserDb::saveUnitMobileOwnerUnitNotReg(){
    report->unitMobileOwnerUnitNotReg++;
    writeFile("单位移动用户-使用人&单位信息未登记.nreg",report->unitMobileOwnerUnitNotReg);
}
void UserDb::saveUnitMobileAgentUnitNotReg(){
    report->unitMobileAgentUnitNotReg++;
    writeFile("单位移动用户-经办人&单位信息未登记.nreg",report->unitMobileAgentUnitNotReg);
}
void UserDb::saveUnitMobileOwnerAgentUnitNotReg(){
    report->unitMobileOwnerAgentUnitNotReg++;
    writeFile("单位移动用户-使用人&经办人&单位信息未登记.nreg",report->unitMobileOwnerAgentUnitNotReg);
}
void UserDb::saveUnitMobileOwnerNok(){
    report->unitMobileOwnerNok++;
    writeFile("单位移动用户-使用人信息校验不合规.nck",report->unitMobileOwnerNok);
}
void UserDb::saveUnitMobileAgentNok(){
    report->unitMobileAgentNok++;
    writeFile("单位移动用户-经办人信息校验不合规.nck",report->unitMobileAgentNok);
}
void UserDb::saveUnitMobileUnitNok(){
    report->unitMobileUnitNok++;
    writeFile("单位移动用户-单位信息校验不合规.nck",report->unitMobileUnitNok);
}
void UserDb::saveUnitMobileOwnerAgentNok(){
    report->unitMobileAgentNok++;
    writeFile("单位移动用户-使用人&经办人信息校验不合规.nck",report->unitMobileAgentNok);
}
void UserDb::saveUnitMobileOwnerUnitNok(){
    report->unitMobileOwnerUnitNok++;
    writeFile("单位移动用户-使用人&单位信息校验不合规.nck",report->unitMobileOwnerUnitNok);
}
void UserDb::saveUnitMobileAgentUnitNok(){
    report->unitMobileAgentUnitNok++;
    writeFile("单位移动用户-经办人&单位信息校验不合规.nck",report->unitMobileAgentUnitNok);
}
void UserDb::saveUnitMobileOwnerAgentUnitNok(){
    report->unitMobileAgentUnitNok++;
    writeFile("单位移动用户-使用人&经办人&单位信息校验不合规.nck",report->unitMobileAgentUnitNok);
}
void UserDb::saveUnitFixedOk(){
    report->unitFixedOk++;
    writeFile("单位固话用户-形式合规数据.ok",report->unitFixedOk);
}
void UserDb::saveUnitFixedOwnerNotReg(){
    report->unitFixedOwnerNotReg++;
    writeFile("单位固话用户-形式合规数据.ok",report->unitFixedOwnerNotReg);
}
void UserDb::saveUnitFixedAgentNotReg(){
    report->unitFixedAgentNotReg++;
    writeFile("单位固话用户-经办人信息未登记.nreg",report->unitFixedAgentNotReg);
}
void UserDb::saveUnitFixedUnitNotReg(){
    report->unitFixedUnitNotReg++;
    writeFile("单位固话用户-单位信息未登记.nreg",report->unitFixedUnitNotReg);
}

//void UserDb::saveUnitFixedOwnerAgentNotReg(){
//    report->unitFixedOwnerAgentNotReg++;
//    writeFile("单位固话用户-使用人&经办人信息未登记.nreg",report->unitFixedOwnerAgentNotReg);
//}
//void UserDb::saveUnitFixedOwnerUnitNotReg(){
//    report->unitFixedOwnerUnitNotReg++;
//    writeFile("单位固话用户-使用人&单位信息未登记.nreg",report->unitFixedOwnerUnitNotReg);
//}
void UserDb::saveUnitFixedAgentUnitNotReg(){
    report->unitFixedAgentUnitNotReg++;
    writeFile("单位固话用户-经办人&单位信息未登记.nreg",report->unitFixedAgentUnitNotReg);
}
//void UserDb::saveUnitFixedOwnerAgentUnitNotReg(){
//    report->unitFixedOwnerAgentUnitNotReg++;
//    writeFile("单位固话用户-使用人&经办人&单位信息未登记.nreg",report->unitFixedOwnerAgentUnitNotReg);
//}
void UserDb::saveUnitFixedAgentNok(){
    report->unitFixedAgentNok++;
    writeFile("单位固话用户-经办人信息校验不合规.nck",report->unitFixedAgentNok);
}
void UserDb::saveUnitFixedUnitNok(){
    report->unitFixedUnitNok++;
    writeFile("单位固话用户-单位信息校验不合规.nck",report->unitFixedUnitNok);
}
void UserDb::saveUnitFixedAgentUnitNok(){
    report->unitFixedAgentUnitNok++;
    writeFile("单位固话用户-经办人&单位信息校验不合规.nck",report->unitFixedAgentUnitNok);
}
void UserDb::saveTradeMobileOk(){
    report->tradeMobileOk++;
    writeFile("行业移动应用-形式合规数据.ok",report->tradeMobileOk);
}
void UserDb::saveTradeMobileAgentNotReg(){
    report->tradeMobileAgentNotReg++;
    writeFile("行业移动应用-经办人信息未登记.nreg",report->tradeMobileAgentNotReg);
}
void UserDb::saveTradeMobileAgentUnitNotReg(){
    report->tradeMobileAgentUnitNotReg++;
    writeFile("行业移动应用-经办人&单位信息未登记.nreg",report->tradeMobileAgentUnitNotReg);
}
void UserDb::saveTradeMobileLiableAgentNotReg(){
    report->tradeMobileLiableAgentNotReg++;
    writeFile("行业移动应用-责任人&经办人信息未登记.nreg",report->tradeMobileLiableAgentNotReg);
}
void UserDb::saveTradeMobileLiableAgentUnitNotReg(){
    report->tradeMobileLiableAgentUnitNotReg++;
    writeFile("行业移动应用-责任人&经办人&单位信息未登记.nreg",report->tradeMobileLiableAgentUnitNotReg);
}
void UserDb::saveTradeMobileUnitNotReg(){
    report->tradeMobileUnitNotReg++;
    writeFile("行业移动应用-单位信息未登记.nreg",report->tradeMobileUnitNotReg);
}
void UserDb::saveTradeMobileLiableNotReg(){
    report->tradeMobileLiableNotReg++;
    writeFile("行业移动应用-责任人信息未登记.nreg",report->tradeMobileLiableNotReg);
}
void UserDb::saveTradeMobileLiableUnitNotReg(){
    report->tradeMobileLiableUnitNotReg++;
    writeFile("行业移动应用-责任人&单位信息未登记.nreg",report->tradeMobileLiableUnitNotReg);
}
void UserDb::saveTradeMobileAgentNok(){
    report->tradeMobileAgentNok++;
    writeFile("行业移动应用-经办人信息校验不合规.nck",report->tradeMobileAgentNok);
}
void UserDb::saveTradeMobileAgentUnitNok(){
    report->tradeMobileAgentUnitNok++;
    writeFile("行业移动应用-经办人&单位信息校验不合规.nck",report->tradeMobileAgentUnitNok);
}
void UserDb::saveTradeMobileLiableAgentNok(){
    report->tradeMobileLiableAgentNok++;
    writeFile("行业移动应用-责任人&经办人信息校验不合规.nck",report->tradeMobileLiableAgentNok);
}
void UserDb::saveTradeMobileLiableAgentUnitNok(){
    report->tradeMobileLiableAgentUnitNok++;
    writeFile("行业移动应用-责任人&经办人&单位信息校验不合规.nck",report->tradeMobileLiableAgentUnitNok);
}
void UserDb::saveTradeMobileUnitNok(){
    report->tradeMobileUnitNok++;
    writeFile("行业移动应用-单位信息校验不合规.nck",report->tradeMobileUnitNok);
}
void UserDb::saveTradeMobileLiableNok(){
    report->tradeMobileLiableNok++;
    writeFile("行业移动应用-责任人信息校验不合规.nck",report->tradeMobileLiableNok);
}
void UserDb::saveTradeMobileLiableUnitNok(){
    report->tradeMobileLiableUnitNok++;
    writeFile("行业移动应用-责任人&单位信息校验不合规.nck",report->tradeMobileLiableUnitNok);
}
void UserDb::saveTradeFixedOk(){
    report->tradeFixedOk++;
    writeFile("行业固话应用-形式合规数据.ok",report->tradeFixedOk);
}
void UserDb::saveTradeFixedOwnerNotReg(){
    report->tradeFixedOwnerNotReg++;
    writeFile("行业固话应用-使用人信息未登记.nreg", report->tradeFixedOwnerNotReg);
}
void UserDb::saveTradeFixedOwnerNok(){
    report->tradeFixedOwnerNok++;
    writeFile("行业固话应用-使用人信息校验不合规.nreg", report->tradeFixedOwnerNok);
}
void UserDb::saveTradeFixedAgentNotReg(){
    report->tradeFixedAgentNotReg++;
    writeFile("行业固话应用-经办人信息未登记.nreg",report->tradeFixedAgentNotReg);
}
void UserDb::saveTradeFixedLiableNotReg(){
    report->tradeFixedLiableNotReg++;
    writeFile("行业固话应用-责任人信息未登记.nreg",report->tradeFixedLiableNotReg);
}
void UserDb::saveTradeFixedAgentUnitNotReg(){
    report->tradeFixedAgentUnitNotReg++;
    writeFile("行业固话应用-经办人&单位信息未登记.nreg",report->tradeFixedAgentUnitNotReg);
}
void UserDb::saveTradeFixedUnitNotReg(){
    report->tradeFixedUnitNotReg++;
    writeFile("行业固话应用-单位信息未登记.nreg",report->tradeFixedUnitNotReg);
}
void UserDb::saveTradeFixedAgentNok(){
    report->tradeFixedAgentNok++;
    writeFile("行业固话应用-经办人信息校验不合规.nck",report->tradeFixedAgentNok);
}
void UserDb::saveTradeFixedAgentUnitNok(){
    report->tradeFixedAgentUnitNok++;
    writeFile("行业固话应用-经办人&单位信息校验不合规.nck",report->tradeFixedAgentUnitNok);
}
void UserDb::saveTradeFixedUnitNok(){
    report->tradeFixedUnitNok++;
    writeFile("行业固话应用-单位信息校验不合规.nck",report->tradeFixedUnitNok);
}
void UserDb::saveTradeMobileOwnerNok(){
    report->tradeMobileOwnerNok++;
    writeFile("行业移动应用-使用人信息校验不合规.nck",report->tradeMobileOwnerNok);
}
void UserDb::saveTradeMobileOwnerNotReg(){
    report->tradeMobileOwnerNotReg++;
    writeFile("行业移动应用-使用人信息未登记.nreg",report->tradeMobileOwnerNotReg);
}

void UserDb::saveTradeFixedAgentLiableNotReg(){
    report->tradeFixedAgentLiableNotReg++;
    writeFile("行业固话应用-经办人&责任人信息未登记.nreg",report->tradeFixedAgentLiableNotReg);
}

void UserDb::saveTradeFixedLiableUnitNotReg(){
    report->tradeFixedLiableUnitNotReg++;
    writeFile("行业固话应用-责任人&单位信息未登记.nreg",report->tradeFixedLiableUnitNotReg);
}
void UserDb::saveTradeFixedAgentLiableUnitNotReg(){
    report->tradeFixedAgentLiableUnitNotReg++;
    writeFile("行业固话应用-经办人&责任人&单位信息未登记.nreg",report->tradeFixedAgentLiableUnitNotReg);
}
void UserDb::saveTradeFixedAgentLiableNok(){
    report->tradeFixedAgentLiableNok++;
    writeFile("行业固话应用-经办人&责任人信息校验不合规.nck",report->tradeFixedAgentLiableNok);
}
void UserDb::saveTradeFixedLiableUnitNok(){
    report->tradeFixedLiableUnitNok++;
    writeFile("行业固话应用-责任人&单位信息校验不合规.nck",report->tradeFixedLiableUnitNok);
}
void UserDb::saveTradeFixedAgentLiableUnitNok(){
    report->tradeFixedAgentLiableUnitNok++;
    writeFile("行业固话应用-经办人&责任人&单位信息校验不合规.nck",report->tradeFixedAgentLiableUnitNok);
}
void UserDb::saveTradeFixedLiableNok(){
    report->tradeFixedLiableNok++;
    writeFile("行业固话应用-责任人信息校验不合规.nok",report->tradeFixedLiableNok);
}
void UserDb::savePersonMobileOneCard(){
    report->personMobileOneCard++;
    writeFile("个人移动一证五卡不合规.nck",report->personMobileOneCard);
}

void UserDb::saveLeaveNet(){
    report->leaveNet++;
    writeFile("非实名制停机和离网状态.txt", report->leaveNet);
}

void UserDb::saveUnitMobileOwnerAgentNotReg(){
    report->unitMobileOwnerAgentNotReg ++;
    writeFile("单位移动用户-使用人&经办人信息校验不合规.nck",report->unitMobileOwnerAgentNotReg);
}

void UserDb::saveOnecardMultiName(){
    report->onecardMultiName++;
    writeFile("一证多名.nok", report->onecardMultiName);
}

void UserDb::saveOnecardFiveCode(){
    report->onecardFiveCode++;
    writeFile("一证超五号不合规.nok", report->onecardFiveCode);
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
//void UserDb::writeFile(QString filename, QString int count){

//    qDebug()<<"writeFile "<<path<<"\\"<<filename;
//    QFile file(path+QDir::separator()+filename);
//    file.open(QFile::Append);
//    QTextStream out(&file);
//    //line += "\n";
//    //file.write(line.toLocal8Bit());
//    out << line << endl;
//    file.close();
//}
static const int QTEXTSTREAM_BUFFERSIZE = 65536;
void UserDb::writeFile(QString filename,  int count){

    if(count%10000==0){
        QList<QString> lineList = fileBuffer.value(filename);
//        qDebug()<<"writeFile "<<path<<"\\"<<filename;
        QFile file(path+QDir::separator()+filename);
        file.open(QFile::Append);
        QTextStream out(&file);
        //line += "\n";
        //file.write(line.toLocal8Bit());
        for(int i=0;i<lineList.size();i++){
            out <<lineList.at(i) << endl;
//            qDebug()<<"================="<<lineList.size()<<" "<<i;
        }
        //out << line << endl;
        file.close();
        fileBuffer.remove(filename);
    }
    else{
        if(fileBuffer.contains(filename)){
            QList<QString> list = fileBuffer.take(filename);
            list.append(this->line);
            fileBuffer.insert(filename, list);
        }
        else{
            QList<QString> list;
            list.append(line);
            fileBuffer.insert(filename, list);
        }
    }
}

void UserDb::flushFile(){
    QMap<QString,QList<QString>>::iterator it; //遍历map
    for (it=fileBuffer.begin(); it != fileBuffer.end(); ++it ) {
        filename = it.key();
//       qDebug()<< "filename===="<<filename; //用key()和data()分别获取“键”和“值”
       QList<QString> lineList = fileBuffer.value(filename);
//       qDebug()<<"writeFile "<<path<<"\\"<<filename;
       QFile file(path+QDir::separator()+filename);
       file.open(QFile::Append);
       QTextStream out(&file);
       //line += "\n";
       //file.write(line.toLocal8Bit());
       for(int i=0;i<lineList.size();i++){
           out <<lineList.at(i) << endl;
         //  qDebug()<<"================="<<lineList.size()<<" "<<i;
       }
       //out << line << endl;
       file.close();
       //fileBuffer.remove(filename);
    }

    fileBuffer.clear(); //清空map
}


/**
 * @brief UserDb::needAgent
 * @param idCardNum 身份证号
 * @param activeTime 入网激活时间
 * @return 判断代办人必填规则：2018年9月1日后，16周岁，大约120岁，之前是10周岁，大于120岁，就必须有代办人信息。入网时间-证件号码日期>10年
 */
bool UserDb::needAgent(QString idCardNum, QString activeTime){

    QDateTime idDate = QDateTime::fromString(idCardNum.trimmed().mid(6,8), "yyyyMMdd");
//    qDebug()<<"id="<<idCardNum<<" "<<idCardNum.trimmed().mid(6,8);
//    qDebug()<<"idDate:"<<idDate.toString("yyyy-MM-dd hh:mm:ss");
    QString dateFormat = xmlConfig->readDateformatValue().value("dateformat");//"yyyy-MM-dd hh:mm:ss";
    QDateTime checkTime = QDateTime::fromString("20180901", "yyyyMMdd");
    QDateTime time = QDateTime::fromString(activeTime.trimmed(), dateFormat);
    QDateTime date1,date2;

//    qDebug()<<"active time:"<<time.toString("yyyy-MM-dd hh:mm:ss");

    if(time<checkTime){
        date1 = idDate.addYears(10);
    }
    else{
        date1 = idDate.addYears(16);
    }
    date2 = idDate.addYears(120);
//    qDebug()<<"是否需要代办人："<<(date1>time||date2<time);
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
void UserDb::processPersonFixed(){
    /* 个人固定用户-证件类型未登记 */
   bool typeNotReg = false;
   if(isNotReg(col[ownerTypeIndex])){
       typeNotReg = true;
       return;
   }

    /* 个人固定用户-用户姓名未登记 */
   bool nameNotReg = false;
   if(isNotReg(col[ownerNameIndex])){
       nameNotReg = true;
   }

   /* 个人固定用户-证件号码未登记 */
   bool numNotReg = false;
   if(isNotReg(col[ownerNumIndex])){
       numNotReg = true;
   }

   /* 个人固定用户-证件地址未登记 */
   bool addNotReg = false;
   if(isNotReg(col[ownerAddIndex])){
       addNotReg = true;
   }


   if(typeNotReg){
       savePersonFixedOwnerTypeNotReg();
       return;
   }
   if(nameNotReg && !numNotReg && !addNotReg){
       savePersonFixedOwnerNameNotReg();
       return;
   }
   if(!nameNotReg && numNotReg && !addNotReg){
       savePersonFixedOwnerNumNotReg();
       return;
   }
   if(!nameNotReg && !numNotReg && addNotReg){
       savePersonFixedOwnerAddNotReg();
       return;
   }
   /* 个人固话用户-用户姓名&证件号码未登记 */
   if(nameNotReg && numNotReg && !addNotReg){
       savePersonFixedOwnerNameNumNotReg();
       return;
   }
   /* 个人固话用户-用户姓名&证件号码未登记 */
   if(nameNotReg && !numNotReg && addNotReg){
       savePersonFixedOwnerNameAddNotReg();
       return;
   }
   /* 个人固话用户-用户姓名&证件号码未登记 */
   if(!nameNotReg && numNotReg && addNotReg){
       savePersonFixedOwnerNumAddNotReg();
       return;
   }
   /* 个人固话用户-用户姓名&证件号码&证件地址未登记 */
   if(nameNotReg && numNotReg && addNotReg){
       savePersonFixedOwnerNameNumAddNotReg();
       return;
   }

   /* 判断是否需要代办人 */
   bool isNeedAgent = needAgent(col.at(ownerNumIndex), col.at(getColNum("登记激活时间")));

   /* 个人固定用户-代办人未登记 */
   if(isNotReg(col[agentNameIndex]) || isNotReg(col[agentTypeIndex]) ||
       isNotReg(col[agentNumIndex])){
       if(isNeedAgent){
           savePersonFixedAgentNotReg();
           return;
       }
   }

   /* 个人固定用户-代办人信息不合规 */
   bool agentNok = false;
   if(col.at(getColNum("机主用户姓名")).compare(col.at(agentNameIndex))){
          agentNok = true;
    }
    else if(isNeedAgent && (isPersonNameNok(col.at(agentNameIndex))||isPersonTypeNok(col.at(agentTypeIndex))||
               isPersonNumNok(col.at(agentNumIndex)))){
       agentNok = true;

   }
   else if(needAgent(col.at(agentNumIndex),col.at(getColNum("登记激活时间")))){
       //代办人如果不满10岁（2018年9月1日后不满16岁），则判为不合规。
       agentNok = true;
   }
   if( agentNok){
       savePersonFixedAgentNok();
       return;
   }

   /* 个人固定用户-证件类型不合规 */
   bool typeNok = false;
   if(isPersonTypeNok(col.at(ownerTypeIndex))){
       typeNok = true;
   }

   /* 个人固定用户-用户姓名不合规 */
   bool nameNok = false;
   if(isPersonNameNok(col.at(getColNum("机主用户姓名")))){
       nameNok = true;
   }

   /* 个人固定用户-证件号码不合规 */
   bool numNok = false;
   if(isPersonNumNok(col.at(ownerNumIndex))){
       numNok = true;
   }

   /* 个人固定用户-证件地址不合规 */
   bool addNok = false;
   if(isPersonAddNok(col.at(ownerAddIndex))){
       addNok = true;
   }

   if(typeNok){
       savePersonFixedOwnerTypeNok();
       return;
   }
   if( nameNok && !numNok && !addNok){
       savePersonFixedOwnerNameNok();
       return;
   }
   if( !nameNok && numNok && !addNok){
       savePersonFixedOwnerNumNok();
       return;
   }
   if( !nameNok && !numNok && addNok){
       savePersonFixedOwnerAddNok();
       return;
   }

   /* 个人固话用户-用户姓名&证件号码校验不合规 */
   if(!agentNok && !typeNok && nameNok && numNok && !addNok){
       savePersonFixedOwnerNameNumNok();
       return;
   }

   /* 个人固话用户-用户姓名&证件地址校验不合规 */
   if(!agentNok && !typeNok && nameNok && !numNok && addNok){
       savePersonFixedOwnerNameAddNok();
       return;
   }

   /* 个人固话用户-证件号码&证件地址校验不合规 */
   if(!agentNok && !typeNok && !nameNok && numNok && addNok){
       savePersonFixedOwnerNumAddNok();
       return;
   }

   /* 个人固话用户-用户姓名&证件号码&证件地址校验不合规 */
   if(!agentNok && !typeNok && nameNok && numNok && addNok){
       savePersonFixedOwnerNumAddNok();
       return;
   }



   /* 个人固话用户-形式合规数据 */
   if(!typeNotReg && !nameNotReg && !numNotReg && !addNotReg && !agentNok && !typeNok && !nameNok && !numNok && !addNok){
       savePersonFixedOk();
       saveAllOk();
       return;
   }

}

/**
 * @brief UserDb::processPersonMobile 处理个人移动用户信息
 * @param col
 * @param
 */
void UserDb::processPersonMobile(){
    /*个人移动用户-证件类型未登记*/
    bool typeNotReg = false;
    if(isNotReg(col[ownerTypeIndex])){
        typeNotReg = true;
    }

    /*个人移动用户-用户姓名未登记*/
    bool nameNotReg = false;
    if(isNotReg(col[ownerNameIndex])){
        nameNotReg = true;
    }

    /*个人移动用户-证件号码未登记*/
    bool numNotReg = false;
    if(isNotReg(col[ownerNumIndex])){
        numNotReg = true;
    }

    /*个人移动用户-证件地址未登记*/
    bool addNotReg = false;
    if(isNotReg(col[ownerAddIndex])){
        addNotReg = true;
    }

    if(typeNotReg){
        savePersonMobileOwnerTypeNotReg();
        return;
    }
    if(nameNotReg && !numNotReg && !addNotReg){
        savePersonMobileOwnerNameNotReg();
        return;
    }
    if(!nameNotReg && numNotReg && !addNotReg){
        savePersonMobileOwnerNumNotReg();
        return;
    }
    if(!nameNotReg && !numNotReg && addNotReg){
        savePersonMobileOwnerAddNotReg();
        return;
    }

    /* 个人移动用户-用户姓名&证件号码未登记 */
    if(nameNotReg && numNotReg && !addNotReg){
        savePersonMobileOwnerNameNumNotReg();
        return;
    }
    /* 个人移动用户-用户姓名&证件地址未登记 */
    if(nameNotReg && !numNotReg && addNotReg){
        savePersonMobileOwnerNameAddNotReg();
        return;
    }
    /* 个人移动用户-证件号码&证件地址未登记 */
    if(!nameNotReg && numNotReg && addNotReg){
        savePersonMobileOwnerNumAddNotReg();
        return;
    }
    /* 个人移动用户-用户姓名&证件号码&证件地址未登记 */
    if(nameNotReg && numNotReg && addNotReg){
        savePersonMobileOwnerNameNumAddNotReg();
        return;
    }



    /* 个人移动用户-证件类型不合规 */
    bool typeNok=false;
    if(isPersonTypeNok(col.at(ownerTypeIndex))){
        typeNok=true;
    }

    if(typeNok){
        savePersonMobileOwnerTyteNok();
        return;
    }

    /* 个人移动用户-用户姓名不合规 */
    bool nameNok=false;
    if(isPersonNameNok(col.at(getColNum("机主用户姓名")))){
        nameNok=true;
    }

    /* 个人移动用户-证件号码不合规 */
    bool numNok=false;
    if(isPersonNumNok(col.at(ownerNumIndex))){
        numNok=true;
    }

     /* 个人移动用户-证件地址不合规 */
    bool addNok=false;
    if(isPersonAddNok(col.at(ownerAddIndex))){
        addNok=true;
    }

    if(nameNok && !numNok && !addNok){
        savePersonMobileOwnerNameNok();
        return;
    }
    if(!nameNok && numNok && !addNok){
        savePersonMobileOwnerNumNok();
        return;
    }
    if(!nameNok && !numNok && addNok){
        savePersonMobileOwnerAddNok();
        return;
    }

    /* 个人移动用户-用户姓名&证件号码校验不合规 */
    if(nameNok && numNok && !addNok){
        savePersonMobileOwnerNameNumNok();
        return;
    }

    /* 个人移动用户-用户姓名&证件地址校验不合规 */
    if(nameNok && !numNok && addNok){
        savePersonMobileOwnerNameAddNok();
        return;
    }

    /* 个人移动用户-证件号码&证件地址校验不合规 */
    if(!nameNok && numNok && addNok){
        savePersonMobileOwnerNumAddNok();
        return;
    }

    /* 个人移动用户-用户姓名&证件号码&证件地址校验不合规 */
    if(nameNok && numNok && addNok){
        savePersonMobileOwnerNumAddNok();
        return;
    }

    /* 判断是否需要代办人 */
    bool isNeedAgent = needAgent(col.at(ownerNumIndex), col.at(getColNum("登记激活时间")));

    /*个人移动用户-代办人信息未登记*/
   bool agentNotReg = false;
   if(isNeedAgent && (isNotReg(col[agentNameIndex])||isNotReg(col[agentTypeIndex])||
       isNotReg(col[agentNumIndex]) || isNotReg(col[agentAddIndex]))){

           agentNotReg = true;
           savePersonMobileAgentNotReg();
           return;
   }

   /* 个人移动用户-代办人信息不合规 */
   bool agentNok = false;
   if(isNeedAgent && !agentNotReg && (isPersonNameNok(col.at(agentNameIndex))||isPersonTypeNok(col.at(agentTypeIndex))||
               isPersonNumNok(col.at(agentNumIndex))||
           isPersonAddNok(col.at(agentAddIndex))|| col.at(getColNum("机主用户姓名")).compare(col.at(agentNameIndex)))){
       agentNok = true;
   }

   if(isNeedAgent && agentNok){
       savePersonMobileAgentNok();
       return;
   }


    /* 个人移动用户-形式合规数据 */
    if(!nameNotReg && !numNotReg && !addNotReg && !agentNok && !typeNok && !nameNok && !numNok && !addNok){
        savePersonMobileOk();
        saveAllOk();
//        qDebug()<<"ok ";
    }
    else{
//        qDebug()<<"nameNotReg "<<nameNotReg;
//        qDebug()<<"numNotReg "<<numNotReg;
//        qDebug()<<"addNotReg "<<addNotReg;
//        qDebug()<<"agentNok "<<agentNok;
//        qDebug()<<"typeNok "<<typeNok;
//        qDebug()<<"nameNok "<<nameNok;
//        qDebug()<<"numNok "<<numNok;
//        qDebug()<<"addNok "<<addNok;
    }

}


/**
 * @brief processUnitFixed 处理单位固话信息
 * @param
 *
 */
void UserDb::processUnitFixed(){

    /* 单位固话用户-代办人信息未登记 */
    bool agentNotReg = false;
    if(isNotReg(col[agentNameIndex]) || isNotReg(col[agentTypeIndex]) || isNotReg(col[agentNumIndex])){
        agentNotReg = true;
    }

    /* 单位固话用户-单位信息未登记 */
    bool unitNotReg = false;
    if(isNotReg(col[unitNameIndex])||isNotReg(col[unitNumIndex])||isNotReg(col[unitTypeIndex])||
            isNotReg(col[unitAddIndex])){
        unitNotReg = true;
    }

    /* 单位固话用户-代办人信息不合规 */
     bool agentNok = false;
    if(isPersonNameNok(col.at(agentNameIndex))||isPersonTypeNok(col.at(agentTypeIndex))||
            isPersonNumNok(col.at(agentNumIndex))){
        agentNok=true;
    }

    /* 单位固话用户-单位信息不合规 */
    bool unitNok = false;
    if(isUnitNameNok(col.at(unitNameIndex))||isUnitNumNok(col.at(unitNumIndex))||isUnitTypeNok(col.at(unitTypeIndex))||
            isUnitAddNok(col.at(unitAddIndex))){
        unitNok=true;
    }

    int activeDate = getDateForInt(col.at(getColNum("登记激活时间")));
    /* 2013年9月1日之前入网的单位固话用户需检查经办人或单位信息中任一个条目，该条目需包含姓名/单位名称、证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。*/
    if(activeDate < 20130901) {
        if( (!agentNotReg && !agentNok) || (!unitNotReg && !unitNok))  {
            saveUnitFixedOk();
            saveAllOk();
        }
        else{
            if(agentNotReg && !unitNotReg){
                saveUnitFixedUnitNotReg();
                return;
            }
            if(!agentNotReg && unitNotReg){
                saveUnitFixedAgentNotReg();
                return;
            }
            if(agentNotReg && unitNotReg){
                saveUnitFixedAgentUnitNotReg();
                return;
            }
            if(agentNok && !unitNok){
                saveUnitFixedAgentNok();
                return;
            }
            if(!agentNok && unitNok){
                saveUnitFixedUnitNok();
                return;
            }
            if(agentNok && unitNok){
                saveUnitFixedAgentUnitNok();
                return;
            }
        }
    }
    else {
        /* 2013年9月1日之后入网的单位固话用户需检查经办人和单位信息共2个条目，各条目均需包含姓名/单位名称、证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。*/
        if(agentNotReg && !unitNotReg){
            saveUnitFixedUnitNotReg();
            return;
        }
        else if(!agentNotReg && unitNotReg){
            saveUnitFixedAgentNotReg();
            return;
        }
        else if(agentNotReg && unitNotReg){
            saveUnitFixedAgentUnitNotReg();
            return;
        }
        else if(agentNok && !unitNok){
            saveUnitFixedAgentNok();
            return;
        }
        else if(!agentNok && unitNok){
            saveUnitFixedUnitNok();
            return;
        }
        else if(agentNok && unitNok){
            saveUnitFixedAgentUnitNok();
            return;
        }
        else {
            saveUnitFixedOk();
            saveAllOk();
        }
    }
}

/**
 * @brief processUnitMobile
 * @param col
 * @param
 */
void UserDb::processUnitMobile(){
    /* 单位移动用户-使用人信息未登记 */
    bool ownerNotReg = false;
    if(isNotReg(col[ownerNameIndex]) || isNotReg(col[ownerNumIndex]) || isNotReg(col[ownerAddIndex])
            || isNotReg(col[ownerTypeIndex])){
        ownerNotReg = true;
    }

    /* 单位移动用户-代办人信息未登记 */
    bool agentNotReg = false;
    if(isNotReg(col[agentNameIndex])||isNotReg(col[agentTypeIndex])||
            isNotReg(col[agentNumIndex]) || isNotReg(col[agentAddIndex])){
        agentNotReg = true;
    }

    /* 单位移动用户-单位信息未登记 */
    bool unitNotReg = false;
    if(isNotReg(col[unitNameIndex])||isNotReg(col[unitNumIndex])||isNotReg(col[unitTypeIndex])||
            isNotReg(col[unitAddIndex])){
        unitNotReg = true;
    }

    /* 单位移动用户-使用人信息不合规 */
    bool ownerNok = false;
    if(isPersonNameNok(col.at(ownerNameIndex))||isPersonNumNok(col.at(ownerNumIndex))||isPersonAddNok(col.at(ownerAddIndex))||
            isPersonTypeNok(col.at(ownerTypeIndex))){
        ownerNok = true;
    }


    /* 单位移动用户-代办人信息不合规 */
    bool agentNok = true;
    if(isPersonNameNok(col.at(agentNameIndex))||isPersonTypeNok(col.at(agentTypeIndex))||
            isPersonNumNok(col.at(agentNumIndex))){
        agentNok = true;
    }
    if(col.at(ownerNameIndex).compare(col.at(agentNameIndex))){
        agentNok = true;
    }

    /* 单位移动用户-单位信息不合规 */
    bool unitNok = true;
    if(isUnitNameNok(col.at(unitNameIndex))||isUnitNumNok(col.at(unitNumIndex))||isUnitTypeNok(col.at(unitTypeIndex))||
            isUnitAddNok(col.at(unitAddIndex))){
        unitNok = true;
    }



    int activeDate = getDateForInt(col.at(getColNum("登记激活时间")));
    /* 2013年9月1日之前入网的单位移动用户，需检查实际使用人、经办人和单位信息中的任1个条目，该条目中需包含姓名/单位名称、证件类型、证件号码、地址四个字段，
     * 并符合完整性和真实性要求。 */
    if(activeDate < 20130901){
        if( (!ownerNotReg && !ownerNok) || (!agentNotReg && !agentNok) || (!unitNotReg&&!unitNok)){
            saveUnitMobileOk();
            saveAllOk();
        }
        else{
            if(ownerNotReg && !agentNotReg && !unitNotReg){
                saveUnitMobileOwnerNotReg();
                return;
            }
            if(!ownerNotReg && agentNotReg && !unitNotReg){
                saveUnitMobileAgentNotReg();
                return;
            }
            if(!ownerNotReg && !agentNotReg && unitNotReg){
                saveUnitMobileUnitNotReg();
                return;
            }
            if(ownerNotReg && agentNotReg && !unitNotReg){
                saveUnitMobileOwnerAgentNotReg();
                return;
            }
            if(ownerNotReg && !agentNotReg && unitNotReg){
                saveUnitMobileOwnerUnitNotReg();
                return;
            }
            if(!ownerNotReg && agentNotReg && unitNotReg){
                saveUnitMobileAgentUnitNotReg();
                return;
            }
            if(ownerNotReg && agentNotReg && unitNotReg){
                saveUnitMobileOwnerAgentUnitNotReg();
                return;
            }
            if(ownerNok && !agentNok && !unitNok){
                saveUnitMobileOwnerNok();
                return;
            }
            if(!ownerNok && agentNok && !unitNok){
                saveUnitMobileAgentNok();
                return;
            }
            if(!ownerNok && !agentNok && unitNok){
                saveUnitMobileUnitNok();
                return;
            }
            if(ownerNok && agentNok && !unitNok){
                saveUnitMobileOwnerAgentNok();
                return;
            }
            if(ownerNok && !agentNok && unitNok){
                saveUnitMobileOwnerUnitNok();
                return;
            }
            if(!ownerNok && agentNok && unitNok){
                saveUnitMobileAgentUnitNok();
                return;
            }
            if(ownerNok && agentNok && unitNok){
                saveUnitMobileOwnerAgentUnitNok();
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
            saveUnitMobileOk();
            saveAllOk();
        }
        else{
            if(ownerNotReg && !agentNotReg && !unitNotReg){
                saveUnitMobileOwnerNotReg();
                return;
            }
            if(!ownerNotReg && agentNotReg && !unitNotReg){
                saveUnitMobileAgentNotReg();
                return;
            }
            if(!ownerNotReg && !agentNotReg && unitNotReg){
                saveUnitMobileUnitNotReg();
                return;
            }
            if(ownerNotReg && agentNotReg && !unitNotReg){
                saveUnitMobileOwnerAgentNotReg();
                return;
            }
            if(ownerNotReg && !agentNotReg && unitNotReg){
                saveUnitMobileOwnerUnitNotReg();
                return;
            }
            if(!ownerNotReg && agentNotReg && unitNotReg){
                saveUnitMobileAgentUnitNotReg();
                return;
            }
            if(ownerNotReg && agentNotReg && unitNotReg){
                saveUnitMobileOwnerAgentUnitNotReg();
                return;
            }


            if(ownerNok && !agentNok && !unitNok){
                saveUnitMobileOwnerNok();
                return;
            }
            if(!ownerNok && agentNok && !unitNok){
                saveUnitMobileAgentNok();
                return;
            }
            if(!ownerNok && !agentNok && unitNok){
                saveUnitMobileUnitNok();
                return;
            }
            if(ownerNok && agentNok && !unitNok){
                saveUnitMobileOwnerAgentNok();
                return;
            }
            if(ownerNok && !agentNok && unitNok){
                saveUnitMobileOwnerUnitNok();
                return;
            }
            if(!ownerNok && agentNok && unitNok){
                saveUnitMobileAgentUnitNok();
                return;
            }
            if(ownerNok && agentNok && unitNok){
                saveUnitMobileOwnerAgentUnitNok();
                return;
            }
        }

    }
    else{
        /* 2015年1月1日之后入网的单位移动用户，需检查实际使用人、经办人、单位信息共3个条目，各条目中均需包含姓名/单位名称、证件类型、证件号码、
         * 地址四个字段，并符合完整性和真实性要求。 */
        if(!(ownerNotReg && agentNotReg && unitNotReg && ownerNok && agentNok && unitNok)){
            saveUnitMobileOk();
            saveAllOk();
        }
        if(ownerNotReg && !agentNotReg && !unitNotReg ){
            saveUnitMobileOwnerNotReg();
            return;
        }
        if(!ownerNotReg && agentNotReg && !unitNotReg ){
            saveUnitMobileAgentNotReg();
            return;
        }
        if(!ownerNotReg && !agentNotReg && unitNotReg ){
            saveUnitMobileUnitNotReg();
            return;
        }
        if(!ownerNok && agentNok && !unitNok ){
            saveUnitMobileAgentNok();
            return;
        }
        if(!ownerNok && !agentNok && unitNok ){
            saveUnitMobileUnitNok();
            return;
        }
        if(ownerNok && agentNok && !unitNok){
            saveUnitMobileOwnerAgentNok();
            return;
        }
        if(ownerNok && agentNok && !unitNok){
            saveUnitMobileOwnerUnitNok();
            return;
        }
        if(!ownerNok && agentNok && unitNok){
            saveUnitMobileAgentUnitNok();
            return;
        }
        if(ownerNok && agentNok && unitNok){
            saveUnitMobileOwnerAgentUnitNok();
            return;
        }

    }

}


/**
 * @brief UserDb::processTradeMobile 处理行业移动数据
 * @param col
 * @param
 */
void UserDb::processTradeMobile(){

    /* 行业移动用户-使用人信息未登记 */
    bool ownerNotReg = false;
    if(isNotReg(col[ownerNameIndex]) || isNotReg(col[ownerNumIndex]) || isNotReg(col[ownerAddIndex])
            || isNotReg(col[ownerTypeIndex])){
        ownerNotReg = true;
    }

    /* 行业移动用户-代办人未登记 */
    bool agentNotReg = false;
    if(isNotReg(col[agentNameIndex])||isNotReg(col[agentTypeIndex])||
            isNotReg(col[agentNumIndex])){
        agentNotReg = true;
    }

    /* 行业移动用户-单位信息未登记 */
    bool unitNotReg = false;
    if(isNotReg(col[unitNameIndex])||isNotReg(col[unitNumIndex])||isNotReg(col[unitTypeIndex])||
            isNotReg(col[unitAddIndex])){
        unitNotReg = true;
    }

    /* 行业移动用户-责任人信息未登记 */
    bool liableNotReg = false;
    if(isNotReg(col[liableNameIndex])||isNotReg(col[liableTypeIndex])||isNotReg(col[liableNumIndex])||
            isNotReg(col[liableAddIndex])){
        liableNotReg = true;
    }

    /* 行业移动用户-使用人信息不合规 */
    bool ownerNok = false;
    if(isPersonNameNok(col.at(ownerNameIndex))||isPersonNumNok(col.at(ownerNumIndex))||isPersonAddNok(col.at(ownerAddIndex))||
            isPersonTypeNok(col.at(ownerTypeIndex))){
        ownerNok = true;
    }

    /* 行业移动用户-代办人不合规 */
    bool agentNok = false;
    if(isPersonNameNok(col.at(agentNameIndex))||isPersonTypeNok(col.at(agentTypeIndex))||
            isPersonNumNok(col.at(agentNumIndex))){
        agentNok = true;
    }
    if(col.at(ownerNameIndex).compare(col.at(agentNameIndex))){
        agentNok = true;
    }

    /* 行业移动用户-单位信息不合规 */
    bool unitNok = false;
    if(isUnitNameNok(col.at(unitNameIndex))||isUnitNumNok(col.at(unitNumIndex))||isUnitTypeNok(col.at(unitTypeIndex))||
            isUnitNumNok(col.at(unitAddIndex))){
        unitNok=true;
    }

    /* 行业移动用户-责任人信息不合规 */
    bool liableNok = false;
    if(isPersonNameNok(col.at(liableNameIndex))||isPersonTypeNok(col.at(liableTypeIndex))||isPersonNumNok(col.at(liableNumIndex))||
            isPersonAddNok(col.at(liableAddIndex))){

        liableNok=true;
    }
    /* 如果实际使用人合规，则不需要判断其他字段 */
    int activeDate = getDateForInt(col.at(activeTimeIndex));
    if( ownerNotReg || ownerNok){
        if(ownerNotReg){
            saveTradeMobileOwnerNotReg();
            return;
        }
        if(ownerNok){
            saveTradeMobileOwnerNok();
            return;
        }
        /* 2013年9月1日之前入网的行业移动用户，需检查责任人、(实际使用人)、经办人和单位信息中任一个条目，该条目中均需包含姓名/单位名称、证件类型、证件号码、地址，
         * 符合完整性和真实性要求。 */
        if(activeDate < 20130901){
            if((!agentNotReg && !agentNok) || (!unitNotReg && !unitNok) || (!liableNotReg && !liableNok)){
                saveTradeMobileOk();
                saveAllOk();
                return;
            }
            else {
                if(liableNotReg && !agentNotReg && !unitNotReg){
                    saveTradeMobileLiableNotReg();
                    return;
                }
                if(!liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeMobileAgentNotReg();
                    return;
                }
                if(!liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeMobileUnitNotReg();
                    return;
                }
                if(liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeMobileLiableAgentNotReg();
                    return;
                }
                if(liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeMobileLiableUnitNotReg();
                    return;
                }
                if(!liableNotReg && agentNotReg && unitNotReg){
                    saveTradeMobileAgentUnitNotReg();
                    return;
                }
                if(liableNotReg && agentNotReg && unitNotReg){
                    saveTradeMobileLiableAgentUnitNotReg();
                    return;
                }
                if(liableNok && !agentNok && !unitNok){
                    saveTradeMobileLiableNok();
                    return;
                }
                if(!liableNok && agentNok && !unitNok){
                    saveTradeMobileAgentNok();
                    return;
                }
                if(!liableNok && !agentNok && unitNok){
                    saveTradeMobileUnitNok();
                    return;
                }
                if(liableNok && agentNok && !unitNok){
                    saveTradeMobileLiableAgentNok();
                    return;
                }
                if(liableNok && !agentNok && unitNok){
                    saveTradeMobileLiableUnitNok();
                    return;
                }
                if(!liableNok && agentNok && unitNok){
                    saveTradeMobileAgentUnitNok();
                    return;
                }
                if(liableNok && agentNok && unitNok){
                    saveTradeMobileLiableAgentUnitNok();
                    return;
                }
            }
        }
        else if(activeDate >= 20130901 && activeDate < 20150101){
            /* 2013年9月1日之后，2015年1月1日之前入网的行业移动用户，需检查责任人(实际使用人就ok)或经办人、单位信息共2个条目，各条目中均需包含姓名/单位名称、
             * 证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。*/

            if( (liableNotReg && agentNotReg) || (liableNotReg && unitNotReg) || (agentNotReg && unitNotReg)){
                if(liableNotReg && !agentNotReg && !unitNotReg){
                    saveTradeMobileLiableNotReg();
                    return;
                }
                if(!liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeMobileAgentNotReg();
                    return;
                }
                if(!liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeMobileUnitNotReg();
                    return;
                }
                if(liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeMobileLiableAgentNotReg();
                    return;
                }
                if(liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeMobileLiableUnitNotReg();
                    return;
                }
                if(!liableNotReg && agentNotReg && unitNotReg){
                    saveTradeMobileAgentUnitNotReg();
                    return;
                }
                if(liableNotReg && agentNotReg && unitNotReg){
                    saveTradeMobileLiableAgentUnitNotReg();
                    return;
                }
            }
            if( (liableNok && agentNok) || (liableNok && unitNok) || (agentNok && unitNok)){
                if(liableNok && !agentNok && !unitNok){
                    saveTradeMobileLiableNok();
                    return;
                }
                if(!liableNok && agentNok && !unitNok){
                    saveTradeMobileAgentNok();
                    return;
                }
                if(!liableNok && !agentNok && unitNok){
                    saveTradeMobileUnitNok();
                    return;
                }
                if(liableNok && agentNok && !unitNok){
                    saveTradeMobileLiableAgentNok();
                    return;
                }
                if(liableNok && !agentNok && unitNok){
                    saveTradeMobileLiableUnitNok();
                    return;
                }
                if(!liableNok && agentNok && unitNok){
                    saveTradeMobileAgentUnitNok();
                    return;
                }
                if(liableNok && agentNok && unitNok){
                    saveTradeMobileLiableAgentUnitNok();
                    return;
                }
            }
            else{
                saveTradeMobileOk();
                saveAllOk();
                return;
            }

        }
        else{
            /* 2015年1月1日之后入网的行业移动用户，需检查责任人(实际使用人，优先)、经办人、单位信息共3个条目，各条目中均需包含姓名/单位名称、证件类型、
             * 证件号码、地址四个字段，并符合完整性和真实性要求。 */
            if(agentNotReg && !unitNotReg && !liableNotReg){
                saveTradeMobileAgentNotReg();
                return;
            }
            if(!agentNotReg && unitNotReg && !liableNotReg){
                saveTradeMobileUnitNotReg();
                return;
            }
            if(!agentNotReg && !unitNotReg && liableNotReg){
                saveTradeMobileLiableNotReg();
                return;
            }
            if(agentNotReg && unitNotReg && !liableNotReg){
                saveTradeMobileAgentUnitNotReg();
                return;
            }
            if(!agentNotReg && unitNotReg && liableNotReg){
                saveTradeMobileLiableUnitNotReg();
                return;
            }
            if(agentNotReg && !unitNotReg && liableNotReg){
                saveTradeMobileLiableAgentNotReg();
                return;
            }
            if(agentNotReg && unitNotReg && liableNotReg){
                saveTradeMobileLiableAgentUnitNotReg();
                return;
            }
            if(agentNok && !unitNok && !liableNok){
                saveTradeMobileAgentNok();
                return;
            }
            if(!agentNok && unitNok && !liableNok){
                saveTradeMobileUnitNok();
                return;
            }
            if(!agentNok && !unitNok && liableNok){
                saveTradeMobileLiableNok();
                return;
            }
            if(agentNok && unitNok && !liableNok){
                saveTradeMobileAgentUnitNok();
                return;
            }
            if(!agentNok && unitNok && liableNok){
                saveTradeMobileAgentUnitNok();
                return;
            }
            if(agentNok && !unitNok && liableNok){
                saveTradeMobileLiableAgentNok();
                return;
            }
            if(agentNok && unitNok && liableNok){
                saveTradeMobileLiableAgentUnitNok();
                return;
            }
            if(!(ownerNok&&agentNok&&unitNok)){
                saveTradeMobileOk();
                saveAllOk();
                return;
            }

        }


    }
    else {
        saveTradeMobileOk();
        saveAllOk();
    }

}


/**
 * @brief UserDb::processTradeFixed 处理行业固话数据
 * @param col
 * @param
 */
void UserDb::processTradeFixed(){

    /* 行业固话用户-使用人信息未登记 */
    bool ownerNotReg = false;
    if(isNotReg(col[ownerNameIndex]) || isNotReg(col[ownerNumIndex]) || isNotReg(col[ownerAddIndex])
            || isNotReg(col[ownerTypeIndex])){
        ownerNotReg = true;
    }

    /* 行业固话用户-代办人未登记 */
    bool agentNotReg = false;
    if(isNotReg(col[agentNameIndex])||isNotReg(col[agentTypeIndex])||
            isNotReg(col[agentNumIndex])){
        agentNotReg = true;
    }

    /* 行业固话用户-单位信息未登记 */
    bool unitNotReg = false;
    if(isNotReg(col[unitNameIndex])||isNotReg(col[unitNumIndex])||isNotReg(col[unitTypeIndex])||
            isNotReg(col[unitAddIndex])){
        unitNotReg = true;
    }

    /* 行业固话用户-责任人信息未登记 */
    bool liableNotReg = false;
    if(isNotReg(col[liableNameIndex])||isNotReg(col[liableTypeIndex])||isNotReg(col[liableNumIndex])||
            isNotReg(col[liableAddIndex])){
        liableNotReg = true;
    }

    /* 行业固话用户-使用人信息不合规 */
    bool ownerNok = false;
    if(isPersonNameNok(col.at(ownerNameIndex))||isPersonNumNok(col.at(ownerNumIndex))||isPersonAddNok(col.at(ownerAddIndex))||
            isPersonTypeNok(col.at(ownerTypeIndex))){
        ownerNok = true;
    }

    /* 行业固话用户-代办人不合规 */
    bool agentNok = false;
    if(isPersonNameNok(col.at(agentNameIndex))||isPersonTypeNok(col.at(agentTypeIndex))||
            isPersonNumNok(col.at(agentNumIndex))){
        agentNok = true;
    }
    if(col.at(getColNum("机主用户姓名")).compare(col.at(agentNameIndex))){
        agentNok = true;
    }

    /* 行业固话用户-单位信息不合规 */
    bool unitNok = false;
    if(isUnitNameNok(col.at(unitNameIndex))||isUnitNumNok(col.at(unitNumIndex))||isUnitTypeNok(col.at(unitTypeIndex))||
            isUnitNumNok(col.at(unitAddIndex))){
        unitNok=true;
    }

    /* 行业固话用户-责任人信息不合规 */
    bool liableNok = false;
    if(isPersonNameNok(col.at(liableNameIndex))||isPersonTypeNok(col.at(liableTypeIndex))||isPersonNumNok(col.at(liableNumIndex))||
            isPersonAddNok(col.at(liableAddIndex))){

        liableNok=true;
    }
    /* 如果实际使用人合规，则不需要判断其他字段 */
    int activeDate = getDateForInt(col.at(getColNum("登记激活时间")));
    if( ownerNotReg || ownerNok){
        if(ownerNotReg){
            saveTradeFixedOwnerNotReg();
        }
        if(ownerNok){
            saveTradeFixedOwnerNok();
        }
        /* 2013年9月1日之前入网的行业固话用户，需检查责任人、(实际使用人)、经办人和单位信息中任一个条目，该条目中均需包含姓名/单位名称、证件类型、证件号码、地址，
         * 符合完整性和真实性要求。 */
        if(activeDate < 20130901){
            if((!agentNotReg && !agentNok) || (!unitNotReg && !unitNok) || (!liableNotReg && !liableNok)){
                saveTradeFixedOk();
                saveAllOk();
            }
            else {
                if(liableNotReg && !agentNotReg && !unitNotReg){
                    saveTradeFixedLiableNotReg();
                    return;
                }
                if(!liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeFixedAgentNotReg();
                    return;
                }
                if(!liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeFixedUnitNotReg();
                    return;
                }
                if(liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeFixedAgentLiableNotReg();
                    return;
                }
                if(liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeFixedLiableUnitNotReg();
                    return;
                }
                if(!liableNotReg && agentNotReg && unitNotReg){
                    saveTradeFixedAgentUnitNotReg();
                    return;
                }
                if(liableNotReg && agentNotReg && unitNotReg){
                    saveTradeFixedAgentLiableUnitNotReg();
                    return;
                }
                if(liableNok && !agentNok && !unitNok){
                    saveTradeFixedLiableNok();
                    return;
                }
                if(!liableNok && agentNok && !unitNok){
                    saveTradeFixedAgentNok();
                    return;
                }
                if(!liableNok && !agentNok && unitNok){
                    saveTradeFixedUnitNok();
                    return;
                }
                if(liableNok && agentNok && !unitNok){
                    saveTradeFixedAgentLiableNok();
                    return;
                }
                if(liableNok && !agentNok && unitNok){
                    saveTradeFixedLiableUnitNok();
                    return;
                }
                if(!liableNok && agentNok && unitNok){
                    saveTradeFixedAgentUnitNok();
                    return;
                }
                if(liableNok && agentNok && unitNok){
                    saveTradeFixedAgentLiableUnitNok();
                    return;
                }
            }
        }
        else if(activeDate >= 20130901 && activeDate < 20150101){
            /* 2013年9月1日之后，2015年1月1日之前入网的行业固话用户，需检查责任人(实际使用人就ok)或经办人、单位信息共2个条目，各条目中均需包含姓名/单位名称、
             * 证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。*/

            if( (liableNotReg && agentNotReg) || (liableNotReg && unitNotReg) || (agentNotReg && unitNotReg)){
                if(liableNotReg && !agentNotReg && !unitNotReg){
                    saveTradeFixedLiableNotReg();
                    return;
                }
                if(!liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeFixedAgentNotReg();
                    return;
                }
                if(!liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeFixedUnitNotReg();
                    return;
                }
                if(liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeFixedAgentLiableNotReg();
                    return;
                }
                if(liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeFixedLiableUnitNotReg();
                    return;
                }
                if(!liableNotReg && agentNotReg && unitNotReg){
                    saveTradeFixedAgentUnitNotReg();
                    return;
                }
                if(liableNotReg && agentNotReg && unitNotReg){
                    saveTradeFixedAgentLiableUnitNotReg();
                    return;
                }
            }
            if( (liableNok && agentNok) || (liableNok && unitNok) || (agentNok && unitNok)){
                if(liableNok && !agentNok && !unitNok){
                    saveTradeFixedLiableNok();
                    return;
                }
                if(!liableNok && agentNok && !unitNok){
                    saveTradeFixedAgentNok();
                    return;
                }
                if(!liableNok && !agentNok && unitNok){
                    saveTradeFixedUnitNok();
                    return;
                }
                if(liableNok && agentNok && !unitNok){
                    saveTradeFixedAgentLiableNok();
                    return;
                }
                if(liableNok && !agentNok && unitNok){
                    saveTradeFixedLiableUnitNok();
                    return;
                }
                if(!liableNok && agentNok && unitNok){
                    saveTradeFixedAgentUnitNok();
                    return;
                }
                if(liableNok && agentNok && unitNok){
                    saveTradeFixedAgentLiableUnitNok();
                    return;
                }
            }
            else{
                saveTradeFixedOk();
                saveAllOk();
                return;
            }

        }
        else{
            /* 2015年1月1日之后入网的行业固话用户，需检查责任人(实际使用人，优先)、经办人、单位信息共3个条目，各条目中均需包含姓名/单位名称、证件类型、
             * 证件号码、地址四个字段，并符合完整性和真实性要求。 */
            if(agentNotReg && !unitNotReg && !liableNotReg){
                saveTradeFixedAgentNotReg();
                return;
            }
            if(!agentNotReg && unitNotReg && !liableNotReg){
                saveTradeFixedUnitNotReg();
                return;
            }
            if(!agentNotReg && !unitNotReg && liableNotReg){
                saveTradeFixedLiableNotReg();
                return;
            }
            if(agentNotReg && unitNotReg && !liableNotReg){
                saveTradeFixedAgentUnitNotReg();
                return;
            }
            if(!agentNotReg && unitNotReg && liableNotReg){
                saveTradeFixedLiableUnitNotReg();
                return;
            }
            if(agentNotReg && !unitNotReg && liableNotReg){
                saveTradeFixedAgentLiableNotReg();
                return;
            }
            if(agentNotReg && unitNotReg && liableNotReg){
                saveTradeFixedAgentLiableUnitNotReg();
                return;
            }
            if(agentNok && !unitNok && !liableNok){
                saveTradeFixedAgentNok();
                return;
            }
            if(!agentNok && unitNok && !liableNok){
                saveTradeFixedUnitNok();
                return;
            }
            if(!agentNok && !unitNok && liableNok){
                saveTradeFixedLiableNok();
                return;
            }
            if(agentNok && unitNok && !liableNok){
                saveTradeFixedAgentUnitNok();
                return;
            }
            if(!agentNok && unitNok && liableNok){
                saveTradeFixedAgentUnitNok();
                return;
            }
            if(agentNok && !unitNok && liableNok){
                saveTradeFixedAgentLiableNok();
                return;
            }
            if(agentNok && unitNok && liableNok){
                saveTradeFixedAgentLiableUnitNok();
                return;
            }
            if(!(ownerNok&&agentNok&&unitNok)){
                saveTradeFixedOk();
                saveAllOk();
                return;
            }

        }


    }
    else {
        saveTradeFixedOk();
        saveAllOk();
    }

}

/**
 * @brief UserDb::processOneCardFiveNumber 处理一证五号
 */
void UserDb::processOneCardFiveNumber(){
//    if(onecardFiveCode.contains(col.at(ownerNumIndex))){
//        if(onecardFiveCode.values(col.at(ownerNumIndex)).size()>5){
//            saveOnecardFiveCode();
//        }
//        onecardFiveCode.insertMulti(col.at(ownerNumIndex), col.at(msisdnIndex));
//    }
//    else{
//        onecardFiveCode.insertMulti(col.at(ownerNumIndex), col.at(msisdnIndex));
//    }
}

/**
 * @brief UserDb::processOneCardMultiName 处理一证多名
 * @param
 */
void UserDb::processOneCardMultiName(){
    if(onecardMultiName.size()==0){
        onecardMultiName.insert(col.at(ownerNameIndex), col.at(ownerNumIndex));
    }
    else{
        QMap<QString,QString>::Iterator  it;
        for(it = onecardMultiName.begin();it != onecardMultiName.end();++it){
            if(!it.key().compare(col.at(ownerNameIndex))&& it.value().compare(col.at(ownerNumIndex))){
                  saveOnecardMultiName();
            }
        }
    }
}
