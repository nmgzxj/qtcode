#include "userdb.h"

/**
 * @brief UserDb::UserDb
 * 数据分析文件
 *
 */

unsigned long UserDb::strHash(const char *pstr,const size_t strlen){
    unsigned long h = 0, g;
    unsigned char *pBegin = (unsigned char *)pstr;
    unsigned char *pEnd= pBegin+strlen;

    while (pBegin < pEnd) {
        h = (h << 4) + *pBegin++;
        if ((g = (h & 0xF0000000))) {
            h = h ^ (g >> 24);
            h = h ^ g;
        }
    }
    return h;
}

UserDb::UserDb()
{
     stopped = false;
     report = new Report();
     qRegisterMetaType<QVector<int> >("QVector<int>");
     cstrHashpersonType = 0;
     cstrHashbizTypeFixed = 0;
     cstrHashunitType = 0;
     cstrHashpersonNameRule = 0;
     cstrHashunitNameRule = 0 ;
     cstrHashnumRule = 0;
     cstrHashaddRule = 0;
     cstrHashnonRealName = 0;
     cstrHashleaveNet = 0;

     errFiveNumber = 0;
     errMultiName  = 0;
     errCardCount  = 0;
     memset(m_pstErrMultiName,0,sizeof(stErrorMultiName *)*MAX_NUMBER_HASH_NODE);
     memset(m_pstErrFiveName,0,sizeof(stErrorFiveNum *)*MAX_NUMBER_HASH_NODE);

     bchunkInit(&bErrMulti,sizeof(stErrorMultiName));
     bchunkInit(&bErrFive,sizeof(stErrorFiveNum));

     readConfig();
     initIndex();
}

void UserDb::bchunkInit(bchunk_t *pchunk,int nsize)
{
    memset(pchunk,0,sizeof(struct bchunk_t));
    pchunk->nsize = nsize;
    pchunk->maxchunks = MAX_BCHUNKS;
}

void UserDb::bchunkFree(bchunk_t *pchunk)
{
    for(int index = 0;index < pchunk->maxchunks ;index ++)
        free(pchunk->chunks[index]);
}

void *UserDb::bchunkAllocNode(bchunk_t *pchunk)
{
//#define MAX_BCHUNKS 1024
//#define MAX_BCHUNKNODES 10000
    void *pstr = nullptr;
    if(pchunk->ncount >= MAX_BCHUNKS * MAX_BCHUNKNODES)return pstr;
    //out of memory
    if(0 == (pchunk->ncount%MAX_BCHUNKNODES)){
        pchunk->chunks[pchunk->ncount/MAX_BCHUNKNODES]=(char *)malloc(MAX_BCHUNKNODES*pchunk->nsize);
        if(pchunk->chunks[pchunk->ncount/MAX_BCHUNKNODES] != nullptr)
        {
            memset(pchunk->chunks[pchunk->ncount/MAX_BCHUNKNODES],0,MAX_BCHUNKNODES*pchunk->nsize);
            pstr = pchunk->chunks[pchunk->ncount/MAX_BCHUNKNODES];
        }
    }
    else {
        pstr = &(pchunk->chunks[pchunk->ncount/MAX_BCHUNKNODES][(pchunk->ncount%MAX_BCHUNKNODES)*pchunk->nsize]);
    }
    if( pstr!= nullptr) pchunk->ncount ++;
    return pstr;
}

void UserDb::readConfig(){
    //     xmlConfig = new XMLConfigReader();
         QList<QList<QString>> lls = xmlConfig->readAutoid();
         delimeter = xmlConfig->readDelimiterValue();
         userType=xmlConfig->readUserType();
         path = xmlConfig->readWorkingpathValue().value("workingpath");
         dateFormat = xmlConfig->readDateformatValue().value("dateformat");//"yyyy-MM-dd hh:mm:ss";
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
        bizTypeFixed = readValueToList(bizTypeFixed, "业务类型固定",strHashbizTypeFixed,cstrHashbizTypeFixed);//用户业务类型固定，除固定外全是移动号码

//        qDebug()<<"biz type==========================";
//        for(int i=0;i<bizTypeFixed.size();i++){
//            qDebug()<<bizTypeFixed.at(i);
//        }

        //初始化个人合规证件类型
        personType = readValueToList(personType, "个人证件居民身份证",strHashpersonType,cstrHashpersonType);
        personType = readValueToList(personType, "个人证件临时居民身份证",strHashpersonType,cstrHashpersonType);
        personType = readValueToList(personType, "个人证件户口薄",strHashpersonType,cstrHashpersonType);
        personType = readValueToList(personType, "个人证件中国人民解放军军人身份证件",strHashpersonType,cstrHashpersonType);
        personType = readValueToList(personType, "个人证件中国人民武装警察身份证件",strHashpersonType,cstrHashpersonType);
        personType = readValueToList(personType, "个人证件港澳居民来往内地通行证",strHashpersonType,cstrHashpersonType);
        personType = readValueToList(personType, "个人证件台湾居民来往大陆通行证",strHashpersonType,cstrHashpersonType);
        personType = readValueToList(personType, "个人证件外国公民护照",strHashpersonType,cstrHashpersonType);
        personType = readValueToList(personType, "个人证件法律、行政法规和国家规定的其他有效身份证件",strHashpersonType,cstrHashpersonType);

        //初始化单位合规证件类型
        unitType  = readValueToList(unitType, "单位证件组织机构代码证",strHashunitType,cstrHashunitType);


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
        personNameRule = readValueToList(personNameRule, "个人用户姓名comon-rule",strHashpersonNameRule,cstrHashpersonNameRule);
        personNameRule = readValueToList(personNameRule, "个人用户姓名match-rule",strHashpersonNameRule,cstrHashpersonNameRule);
        //初始化单位/行业用户名称不合规
        unitNameRule = readValueToList(unitNameRule, "行业用户姓名comon-rule",strHashunitNameRule,cstrHashunitNameRule);
        unitNameRule = readValueToList(unitNameRule, "行业用户姓名match-rule",strHashunitNameRule,cstrHashunitNameRule);
        //初始化个人证件号码不合规
        //初始化单位证件号码不合规
        numRule = readValueToList(numRule, "证件号码comon-rule",strHashnumRule,cstrHashnumRule);
        numRule = readValueToList(numRule, "证件号码match-rule",strHashnumRule,cstrHashnumRule);
        //初始化个人证件地址不合规
        //初始化单位证件地址不合规
        addRule = readValueToList(addRule, "证件地址addr-rule",strHashaddRule,cstrHashaddRule);
        addRule = readValueToList(addRule, "证件地址match-rule",strHashaddRule,cstrHashaddRule);

        nonRealName = readValueToList(nonRealName, "业务状态非实名制停机",strHashnonRealName,cstrHashnonRealName);
        leaveNet = readValueToList(leaveNet, "业务状态不在网",strHashleaveNet,cstrHashleaveNet);
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

QList<QString> UserDb::readValueToList(QList<QString> inList, QString query,strHashNode *psHNode,int &psHNodeCount){
    QList<QString> list = xmlConfig->readValue(query);
    for(int i=0; i<list.size(); i++){
        psHNode[psHNodeCount].sHashKey = strHash(list.at(i).toStdString().c_str(),strlen(list.at(i).toStdString().c_str()));
        memcpy(psHNode[psHNodeCount].sHashContent,list.at(i).toStdString().c_str(),strlen(list.at(i).toStdString().c_str())+1);
        inList.append(list.at(i));
        psHNodeCount ++;

    }
    return inList;
}

UserDb::~UserDb()
{
    delete report;
    delete xmlConfig;
    bchunkFree(&bErrMulti);
    bchunkFree(&bErrFive);
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

    report->setTableValue(path+QDir::separator());
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
        file.close();
        emit message("已处理完成，文件关闭");
    }
    else{
        emit messageWarning("文件打开错误。");
    }

    if(file.open(QFile::ReadOnly | QFile::Text)){
        //QBuffer buffer(&file);
       // uchar file.map(file.size());
        QTextStream stream(&file);
        stream.setCodec(code);
        line_num = 1;

         do {
            line = stream.readLine();
            processLine(1);
            line_num++;

            if(line_num%1000==0)
            {
                emit message("已二次输出AAAA"+QString::number(line_num)+"行");
            }

        }while(!stopped && !line.isEmpty());
        file.close();
        emit message("已处理AAAA完成，文件再次关闭");
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
    unsigned long sHashv = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
    for(int index = 0;index < cstrHashpersonType ;index ++)
    {
        if(strHashpersonType[index].sHashKey == sHashv)
        {
            if(0 == strcmp(strHashpersonType[index].sHashContent,str.toStdString().c_str()) )return false;
        }
    }
//QDateTime idDate = QDateTime::fromString(idCardNum.trimmed().mid(6,8), "yyyyMMdd")
/*
    if(!personType.contains(str)){
//        qDebug()<<"个人证件类型不合规"<<str<<" "<<personType;
        return true;
    }
*/
    return true;
}

bool UserDb::isUnitTypeNok(QString const &str){

    //    qDebug()<<"单位证件类型不合规"<<str<<" "<<unitType;
    unsigned long sHashv = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
    for(int index = 0;index < cstrHashunitType ;index ++)
    {
        if(strHashunitType[index].sHashKey == sHashv)
        {
            if(0 == strcmp(strHashunitType[index].sHashContent,str.toStdString().c_str()) )return false;
        }
    }
    return true;

//    return !unitType.contains(str);

}

bool UserDb::
isPersonNameNok(QString const & str){
    if(personNameMin!=-1 && str.length()<personNameMin){
//        qDebug()<<personNameMin<<"姓名字数不够"<<str.length()<<" "<<str;
        return true;
    }
    else if(personNameMax!=-1 && str.length()>personNameMax){
//        qDebug()<<personNameMax<<"姓名太长"<<str.length()<<" "<<str;
        return true;
    }
    else //if(personNameRule.contains(str))
    {
//        qDebug()<<"姓名包含非法字符:  "<<str;
        unsigned long sHashv = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
        for(int index = 0;index < cstrHashpersonNameRule ;index ++)
        {
            if(strHashpersonNameRule[index].sHashKey == sHashv)
            {
                if(0 == strcmp(strHashpersonNameRule[index].sHashContent,str.toStdString().c_str()) )return true;
            }
        }
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
    else //if(unitNameRule.contains(str)){
//        qDebug()<<"单位名称不合规"<<str;
    {
        unsigned long sHashv = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
        for(int index = 0;index < cstrHashunitNameRule ;index ++)
        {
            if(strHashunitNameRule[index].sHashKey == sHashv)
            {
                if(0 == strcmp(strHashunitNameRule[index].sHashContent,str.toStdString().c_str()) )return true;
            }
        }
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
    else //if(numRule.contains(str)){
    {
//        qDebug()<<"个人证件号码不合规"<<str;
        unsigned long sHashv = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
        for(int index = 0;index < cstrHashnumRule ;index ++)
        {
            if(strHashnumRule[index].sHashKey == sHashv)
            {
                if(0 == strcmp(strHashnumRule[index].sHashContent,str.toStdString().c_str()) )return true;
            }
        }
    }
    //这里的检验需要和needAgent中的内容一致
    //确保从6~8位取出来的内容可以正确转换为时间：按照yyyyMMDD的方式
    //还可以持续完善
    {
        if((strlen(str.toStdString().c_str())) < 14) return true;
        QString str1 = str.mid(6,8);
        const char* pstr = str1.toStdString().c_str();
        if(pstr[0]!='1'&&pstr[0]!='2')return true;
        if((pstr[0]=='1'&&pstr[1]!='9')||(pstr[0]=='2'&&pstr[1]!='0'))return true;
        if(pstr[2]<'0'||pstr[2]>'9'||pstr[3]<'0'||pstr[3]>'9')return true;
        if(pstr[4]!='0'&&pstr[4]!='1')return true;
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
    else //if(numRule.contains(str)){
    {
//        qDebug()<<"单位证件号码不合规"<<str;
        unsigned long sHashv = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
        for(int index = 0;index < cstrHashnumRule ;index ++)
        {
            if(strHashnumRule[index].sHashKey == sHashv)
            {
                if(0 == strcmp(strHashnumRule[index].sHashContent,str.toStdString().c_str()) )return true;
            }
        }
    }
    {
        if((strlen(str.toStdString().c_str())) < 14) return true;
        QString str1 = str.mid(6,8);
        const char* pstr = str1.toStdString().c_str();
        if(pstr[0]!='1'&&pstr[0]!='2')return true;
        if((pstr[0]=='1'&&pstr[1]!='9')||(pstr[0]=='2'&&pstr[1]!='0'))return true;
        if(pstr[2]<'0'||pstr[2]>'9'||pstr[3]<'0'||pstr[3]>'9')return true;
        if(pstr[4]!='0'&&pstr[4]!='1')return true;
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
    else //if(addRule.contains(str)){
    {
//        qDebug()<<"个人证件地址不合规"<<str;
        unsigned long sHashv = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
        for(int index = 0;index < cstrHashaddRule ;index ++)
        {
            if(strHashaddRule[index].sHashKey == sHashv)
            {
                if(0 == strcmp(strHashaddRule[index].sHashContent,str.toStdString().c_str()) )return true;
            }
        }
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
    else //if(addRule.contains(str)){
    {
//        qDebug()<<"单位地址不合规"<<str;
        unsigned long sHashv = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
        for(int index = 0;index < cstrHashaddRule ;index ++)
        {
            if(strHashaddRule[index].sHashKey == sHashv)
            {
                if(0 == strcmp(strHashaddRule[index].sHashContent,str.toStdString().c_str()) )return true;
            }
        }
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

    id_TypeChar = id_typeknown;
    /* 根据用户类型和用户业务类型进入到具体逻辑规则中判断和输出。 */
    if(userType.value("person").contains(col.at(userTypeInex))){  /*个人用户*/

        if(bizTypeFixed.contains(col.at(bizTypeIndex))){  /*个人固定用户*/
            id_TypeChar = id_personTelephone;
            report->personFixedTotal++;
            processPersonFixed();
        }
        else {/*个人移动用户*/
            id_TypeChar = id_personMobile;
            report->personMobileTotal++;
            processPersonMobile();
        }

    }
    else if(userType.value("unit").contains(col.at(userTypeInex))){  /*单位用户*/

        if(bizTypeFixed.contains(col.at(bizTypeIndex))){ /*单位固话用户*/
            id_TypeChar = id_unitTelephone;
            report->unitFixedTotal++;
            processUnitFixed();
        }
        else {
            id_TypeChar = id_unitMobile;
            report->unitMobileTotal++;
            processUnitMobile();
        }
    }
    else if(userType.value("industry").contains(col.at(userTypeInex))){
        if(bizTypeFixed.contains(col.at(bizTypeIndex))){
            id_TypeChar = id_serviceTelephone;
            report->tradeFixedTotal++;
            processTradeFixed();
        }
        else {
            id_TypeChar = id_serviceMobile;
            report->tradeMobileTotal++;
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
//    processOneCardFiveNumber();

}

void UserDb::processLine(int flag){

    stErrorMultiName *ptrMulti;
    stErrorFiveNum   *ptrFive;
    col =  line.split(delimeter);
    /*格式异常数据*/
    if(col.size() != COL_NUM)return;
    if(nonRealName.contains(col.at(codeStatusIndex)) || leaveNet.contains(col.at(codeStatusIndex))){
        return;
    }

    /* 字段异常数据.abnormal */
    if(col.at(activeTimeIndex)==nullptr || isNotReg(col[activeTimeIndex])){
        return;
    }

    id_TypeChar = id_typeknown;
    /* 根据用户类型和用户业务类型进入到具体逻辑规则中判断和输出。 */
    if(userType.value("person").contains(col.at(userTypeInex))){  /*个人用户*/
        if(bizTypeFixed.contains(col.at(bizTypeIndex))){  /*个人固定用户*/
            id_TypeChar = id_personTelephone;
        }
        else {/*个人移动用户*/
            id_TypeChar = id_personMobile;
        }

    }
    else if(userType.value("unit").contains(col.at(userTypeInex))){  /*单位用户*/
        if(bizTypeFixed.contains(col.at(bizTypeIndex))){ /*单位固话用户*/
            id_TypeChar = id_unitTelephone;
        }
        else {
            id_TypeChar = id_unitMobile;
        }
    }
    else if(userType.value("industry").contains(col.at(userTypeInex))){
        if(bizTypeFixed.contains(col.at(bizTypeIndex))){
            id_TypeChar = id_serviceTelephone;
        }
        else {
            id_TypeChar = id_serviceMobile;
        }
    }
    if(id_TypeChar == id_typeknown)return;

    unsigned long sHashTreev = strHash(col.at(ownerNumIndex).toStdString().c_str(),strlen(col.at(ownerNumIndex).toStdString().c_str()))%MAX_NUMBER_HASH_NODE;
    if(m_pstErrMultiName[sHashTreev] == nullptr) //Error !!!!
        return;
    ptrMulti = m_pstErrMultiName[sHashTreev];
    do{
        if((ptrMulti->errflag&id_TypeMask) == id_TypeChar)
        {
            if(0 == strcmp(ptrMulti->number,col.at(ownerNumIndex).toStdString().c_str()))
            {
                if((ptrMulti->errflag&errType_oneCardMultiName) == errType_oneCardMultiName)
                {
                    //个人移动 个人固话 单位移动 单位固话  行业移动  行业固话
                    //static const char id_personMobile     = 0x01;  //...1
                    //static const char id_personTelephone  = 0x02;   //..1.
                    //static const char id_unitMobile       = 0x05;   //.1.1
                    //static const char id_unitTelephone    = 0x06;   //.11.
                    //static const char id_serviceMobile    = 0x09;   //1..1
                    //static const char id_serviceTelephone = 0x0a;   //1.1.
                    switch(id_TypeChar)
                    {
                    case id_personMobile:
                        //Need output this line
                        //Need More Content
                        savePersonMobileOneCard();
                        break;
                    case id_personTelephone:
                        //Need output this line
                        //Need More Content
                        savePersonFixedOnecard();
                        break;
                    case id_unitMobile:
                        //Need output this line
                        //Need More Content
                        saveUnitMobileOnecard();
                        break;
                    case id_unitTelephone:
                        //Need output this line
                        //Need More Content
                        saveUnitFixedOnecard();
                        break;
                    case id_serviceMobile:
                        //Need output this line
                        //Need More Content
                        saveTradeMobileOnecard();
                        break;
                    case id_serviceTelephone:
                        //Need output this line
                        //Need More Content
                        saveTradeFixedOnecard();
                        break;
                    default:
                        saveFieldAbnormal();
                        //There is something wrong !!!!
                        break;
                    }
                 }
                 break;
             }
        }
        ptrMulti = ptrMulti->next;
    }while(ptrMulti != nullptr);

    if(m_pstErrFiveName[sHashTreev] == nullptr) // Error !!!!
        return;
    ptrFive = m_pstErrFiveName[sHashTreev];
    do{
            if(0 == strcmp(ptrFive->number,col.at(ownerNumIndex).toStdString().c_str()))
            {
                if(ptrFive->errflag&errType_oneCardFiveNumber)
                {
                    //Need output this line
                    //Need More Content
                    saveOnecardFiveNumber();
                }
                break;
            }
         ptrFive = ptrFive->next;
        }while(ptrFive != nullptr);
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

void UserDb::saveOnecardFiveNumber(){
    report->onecardFiveNumber++;
    writeFile("一证五号不合规.nok", report->onecardFiveNumber);
}

void UserDb::savePersonMobileOneCard(){
    report->personMobileOneCard++;
    writeFile("个人移动一证多名不合规.nck",report->personMobileOneCard);
}


void UserDb::savePersonFixedOnecard(){
    report->personFixedOneCard++;
    writeFile("个人固话一证多名不合规.nok", report->personFixedOneCard);
}

void UserDb::saveUnitMobileOnecard(){
    report->unitMobileOneCard++;
    writeFile("单位移动一证多名不合规.nok", report->unitMobileOneCard);
}

void UserDb::saveUnitFixedOnecard(){
    //根据需求，不处理
//    report->unitFixedOneCard++;
//    writeFile("单位固话一证多名不合规.nok", report->unitFixedOneCard);
}

void UserDb::saveTradeMobileOnecard(){
    //根据需求，不处理
//    report->tradeMobileOneCard++;
//    writeFile("行业移动一证多名不合规.nok", report->tradeMobileOneCard);
}

void UserDb::saveTradeFixedOnecard(){
    //根据需求，不处理
//    report->tradeFixedOneCard++;
//    writeFile("行业固话一证多名不合规.nok", report->tradeFixedOneCard);
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
       report->personFixedNotReg++;
       return;
   }
   if(nameNotReg && !numNotReg && !addNotReg){
       savePersonFixedOwnerNameNotReg();
       report->personFixedNotReg++;
       return;
   }
   if(!nameNotReg && numNotReg && !addNotReg){
       savePersonFixedOwnerNumNotReg();
       report->personFixedNotReg++;
       return;
   }
   if(!nameNotReg && !numNotReg && addNotReg){
       savePersonFixedOwnerAddNotReg();
       report->personFixedNotReg++;
       return;
   }
   /* 个人固话用户-用户姓名&证件号码未登记 */
   if(nameNotReg && numNotReg && !addNotReg){
       savePersonFixedOwnerNameNumNotReg();
       report->personFixedNotReg++;
       return;
   }
   /* 个人固话用户-用户姓名&证件号码未登记 */
   if(nameNotReg && !numNotReg && addNotReg){
       savePersonFixedOwnerNameAddNotReg();
       report->personFixedNotReg++;
       return;
   }
   /* 个人固话用户-用户姓名&证件号码未登记 */
   if(!nameNotReg && numNotReg && addNotReg){
       savePersonFixedOwnerNumAddNotReg();
       report->personFixedNotReg++;
       return;
   }
   /* 个人固话用户-用户姓名&证件号码&证件地址未登记 */
   if(nameNotReg && numNotReg && addNotReg){
       savePersonFixedOwnerNameNumAddNotReg();
       report->personFixedNotReg++;
       return;
   }

   /* 判断是否需要代办人 */
   bool isNeedAgent = needAgent(col.at(ownerNumIndex), col.at(getColNum("登记激活时间")));

   /* 个人固定用户-代办人未登记 */
   if(isNotReg(col[agentNameIndex]) || isNotReg(col[agentTypeIndex]) ||
       isNotReg(col[agentNumIndex])){
       if(isNeedAgent){
           savePersonFixedAgentNotReg();
           report->personFixedNotReg++;
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
       report->personFixedNok++;
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
       report->personFixedNok++;
       return;
   }
   if( nameNok && !numNok && !addNok){
       savePersonFixedOwnerNameNok();
       report->personFixedNok++;
       return;
   }
   if( !nameNok && numNok && !addNok){
       savePersonFixedOwnerNumNok();
       report->personFixedNok++;
       return;
   }
   if( !nameNok && !numNok && addNok){
       savePersonFixedOwnerAddNok();
       report->personFixedNok++;
       return;
   }

   /* 个人固话用户-用户姓名&证件号码校验不合规 */
   if(!agentNok && !typeNok && nameNok && numNok && !addNok){
       savePersonFixedOwnerNameNumNok();
       report->personFixedNok++;
       return;
   }

   /* 个人固话用户-用户姓名&证件地址校验不合规 */
   if(!agentNok && !typeNok && nameNok && !numNok && addNok){
       savePersonFixedOwnerNameAddNok();
       report->personFixedNok++;
       return;
   }

   /* 个人固话用户-证件号码&证件地址校验不合规 */
   if(!agentNok && !typeNok && !nameNok && numNok && addNok){
       savePersonFixedOwnerNumAddNok();
       report->personFixedNok++;
       return;
   }

   /* 个人固话用户-用户姓名&证件号码&证件地址校验不合规 */
   if(!agentNok && !typeNok && nameNok && numNok && addNok){
       savePersonFixedOwnerNumAddNok();
       report->personFixedNok++;
       return;
   }



   /* 个人固话用户-形式合规数据 */
   if(!typeNotReg && !nameNotReg && !numNotReg && !addNotReg && !agentNok && !typeNok && !nameNok && !numNok && !addNok){
       savePersonFixedOk();
       saveAllOk();
       processOneCardMultiName();
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
        report->personMobileNotReg++;
        return;
    }
    if(nameNotReg && !numNotReg && !addNotReg){
        savePersonMobileOwnerNameNotReg();
        report->personMobileNotReg++;
        return;
    }
    if(!nameNotReg && numNotReg && !addNotReg){
        savePersonMobileOwnerNumNotReg();
        report->personMobileNotReg++;
        return;
    }
    if(!nameNotReg && !numNotReg && addNotReg){
        savePersonMobileOwnerAddNotReg();
        report->personMobileNotReg++;
        return;
    }

    /* 个人移动用户-用户姓名&证件号码未登记 */
    if(nameNotReg && numNotReg && !addNotReg){
        savePersonMobileOwnerNameNumNotReg();
        report->personMobileNotReg++;
        return;
    }
    /* 个人移动用户-用户姓名&证件地址未登记 */
    if(nameNotReg && !numNotReg && addNotReg){
        savePersonMobileOwnerNameAddNotReg();
        report->personMobileNotReg++;
        return;
    }
    /* 个人移动用户-证件号码&证件地址未登记 */
    if(!nameNotReg && numNotReg && addNotReg){
        savePersonMobileOwnerNumAddNotReg();
        report->personMobileNotReg++;
        return;
    }
    /* 个人移动用户-用户姓名&证件号码&证件地址未登记 */
    if(nameNotReg && numNotReg && addNotReg){
        savePersonMobileOwnerNameNumAddNotReg();
        report->personMobileNotReg++;
        return;
    }



    /* 个人移动用户-证件类型不合规 */
    bool typeNok=false;
    if(isPersonTypeNok(col.at(ownerTypeIndex))){
        typeNok=true;
    }

    if(typeNok){
        savePersonMobileOwnerTyteNok();
        report->personMobileNok++;
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
        report->personMobileNok++;
        return;
    }
    if(!nameNok && numNok && !addNok){
        savePersonMobileOwnerNumNok();
        report->personMobileNok++;
        return;
    }
    if(!nameNok && !numNok && addNok){
        savePersonMobileOwnerAddNok();
        report->personMobileNok++;
        return;
    }

    /* 个人移动用户-用户姓名&证件号码校验不合规 */
    if(nameNok && numNok && !addNok){
        savePersonMobileOwnerNameNumNok();
        report->personMobileNok++;
        return;
    }

    /* 个人移动用户-用户姓名&证件地址校验不合规 */
    if(nameNok && !numNok && addNok){
        savePersonMobileOwnerNameAddNok();
        report->personMobileNok++;
        return;
    }

    /* 个人移动用户-证件号码&证件地址校验不合规 */
    if(!nameNok && numNok && addNok){
        savePersonMobileOwnerNumAddNok();
        report->personMobileNok++;
        return;
    }

    /* 个人移动用户-用户姓名&证件号码&证件地址校验不合规 */
    if(nameNok && numNok && addNok){
        savePersonMobileOwnerNumAddNok();
        report->personMobileNok++;
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
           report->personMobileNotReg++;
           return;
   }

   /* 个人移动用户-代办人信息不合规 */
   bool agentNok = false;
   if(isNeedAgent && !agentNotReg && (isPersonNameNok(col.at(agentNameIndex))||isPersonTypeNok(col.at(agentTypeIndex))||
               isPersonNumNok(col.at(agentNumIndex))||
           isPersonAddNok(col.at(agentAddIndex))|| !col.at(ownerNameIndex).compare(col.at(agentNameIndex)))){
       agentNok = true;
   }

   if(isNeedAgent && agentNok){
       savePersonMobileAgentNok();
       report->personMobileNok++;
       return;
   }


    /* 个人移动用户-形式合规数据 */
    if(!nameNotReg && !numNotReg && !addNotReg && !agentNok && !typeNok && !nameNok && !numNok && !addNok){
        savePersonMobileOk();
        saveAllOk();
        processOneCardMultiName();
        processOneCardFiveNumber();
        return;
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
            processOneCardMultiName();
            return;
        }
        else{
            if(agentNotReg && !unitNotReg){
                saveUnitFixedAgentNotReg();
                report->unitFixedNotReg++;
                return;
            }
            if(!agentNotReg && unitNotReg){
                saveUnitFixedUnitNotReg();
                report->unitFixedNotReg++;
                return;
            }
            if(agentNotReg && unitNotReg){
                saveUnitFixedAgentUnitNotReg();
                report->unitFixedNotReg++;
                return;
            }
            if(agentNok && !unitNok){
                saveUnitFixedAgentNok();
                report->unitFixedNok++;
                return;
            }
            if(!agentNok && unitNok){
                saveUnitFixedUnitNok();
                report->unitFixedNok++;
                return;
            }
            if(agentNok && unitNok){
                saveUnitFixedAgentUnitNok();
                report->unitFixedNok++;
                return;
            }
        }
    }
    else {
        /* 2013年9月1日之后入网的单位固话用户需检查经办人和单位信息共2个条目，各条目均需包含姓名/单位名称、证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。*/
        if(agentNotReg && !unitNotReg){
            saveUnitFixedAgentNotReg();
            report->unitFixedNotReg++;
            return;
        }
        else if(!agentNotReg && unitNotReg){
            saveUnitFixedUnitNotReg();
            report->unitFixedNotReg++;
            return;
        }
        else if(agentNotReg && unitNotReg){
            saveUnitFixedAgentUnitNotReg();
            report->unitFixedNotReg++;
            return;
        }
        else if(agentNok && !unitNok){
            saveUnitFixedAgentNok();
            report->unitFixedNok++;
            return;
        }
        else if(!agentNok && unitNok){
            saveUnitFixedUnitNok();
            report->unitFixedNok++;
            return;
        }
        else if(agentNok && unitNok){
            saveUnitFixedAgentUnitNok();
            report->unitFixedNok++;
            return;
        }
        else {
            saveUnitFixedOk();
            saveAllOk();
            processOneCardMultiName();
            return;
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
            processOneCardMultiName();
            processOneCardFiveNumber();
            return;
        }
        else{
            if(ownerNotReg && !agentNotReg && !unitNotReg){
                saveUnitMobileOwnerNotReg();
                report->unitMobileNotReg++;
                return;
            }
            if(!ownerNotReg && agentNotReg && !unitNotReg){
                saveUnitMobileAgentNotReg();
                report->unitMobileNotReg++;
                return;
            }
            if(!ownerNotReg && !agentNotReg && unitNotReg){
                saveUnitMobileUnitNotReg();
                report->unitMobileNotReg++;
                return;
            }
            if(ownerNotReg && agentNotReg && !unitNotReg){
                saveUnitMobileOwnerAgentNotReg();
                report->unitMobileNotReg++;
                return;
            }
            if(ownerNotReg && !agentNotReg && unitNotReg){
                saveUnitMobileOwnerUnitNotReg();
                report->unitMobileNotReg++;
                return;
            }
            if(!ownerNotReg && agentNotReg && unitNotReg){
                saveUnitMobileAgentUnitNotReg();
                report->unitMobileNotReg++;
                return;
            }
            if(ownerNotReg && agentNotReg && unitNotReg){
                saveUnitMobileOwnerAgentUnitNotReg();
                report->unitMobileNotReg++;
                return;
            }
            if(ownerNok && !agentNok && !unitNok){
                saveUnitMobileOwnerNok();
                report->unitMobileNok++;
                return;
            }
            if(!ownerNok && agentNok && !unitNok){
                saveUnitMobileAgentNok();
                report->unitMobileNok++;
                return;
            }
            if(!ownerNok && !agentNok && unitNok){
                saveUnitMobileUnitNok();
                report->unitMobileNok++;
                return;
            }
            if(ownerNok && agentNok && !unitNok){
                saveUnitMobileOwnerAgentNok();
                report->unitMobileNok++;
                return;
            }
            if(ownerNok && !agentNok && unitNok){
                saveUnitMobileOwnerUnitNok();
                report->unitMobileNok++;
                return;
            }
            if(!ownerNok && agentNok && unitNok){
                saveUnitMobileAgentUnitNok();
                report->unitMobileNok++;
                return;
            }
            if(ownerNok && agentNok && unitNok){
                saveUnitMobileOwnerAgentUnitNok();
                report->unitMobileNok++;
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
            processOneCardMultiName();
            processOneCardFiveNumber();
            return;
        }
        else{
            if(ownerNotReg && !agentNotReg && !unitNotReg){
                saveUnitMobileOwnerNotReg();
                report->unitMobileNotReg++;
                return;
            }
            if(!ownerNotReg && agentNotReg && !unitNotReg){
                saveUnitMobileAgentNotReg();
                report->unitMobileNotReg++;
                return;
            }
            if(!ownerNotReg && !agentNotReg && unitNotReg){
                saveUnitMobileUnitNotReg();
                report->unitMobileNotReg++;
                return;
            }
            if(ownerNotReg && agentNotReg && !unitNotReg){
                saveUnitMobileOwnerAgentNotReg();
                report->unitMobileNotReg++;
                return;
            }
            if(ownerNotReg && !agentNotReg && unitNotReg){
                saveUnitMobileOwnerUnitNotReg();
                report->unitMobileNotReg++;
                return;
            }
            if(!ownerNotReg && agentNotReg && unitNotReg){
                saveUnitMobileAgentUnitNotReg();
                report->unitMobileNotReg++;
                return;
            }
            if(ownerNotReg && agentNotReg && unitNotReg){
                saveUnitMobileOwnerAgentUnitNotReg();
                report->unitMobileNotReg++;
                return;
            }


            if(ownerNok && !agentNok && !unitNok){
                saveUnitMobileOwnerNok();
                report->unitMobileNok++;
                return;
            }
            if(!ownerNok && agentNok && !unitNok){
                saveUnitMobileAgentNok();
                report->unitMobileNok++;
                return;
            }
            if(!ownerNok && !agentNok && unitNok){
                saveUnitMobileUnitNok();
                report->unitMobileNok++;
                return;
            }
            if(ownerNok && agentNok && !unitNok){
                saveUnitMobileOwnerAgentNok();
                report->unitMobileNok++;
                return;
            }
            if(ownerNok && !agentNok && unitNok){
                saveUnitMobileOwnerUnitNok();
                report->unitMobileNok++;
                return;
            }
            if(!ownerNok && agentNok && unitNok){
                saveUnitMobileAgentUnitNok();
                report->unitMobileNok++;
                return;
            }
            if(ownerNok && agentNok && unitNok){
                saveUnitMobileOwnerAgentUnitNok();
                report->unitMobileNok++;
                return;
            }
        }

    }
    else{
        /* 2015年1月1日之后入网的单位移动用户，需检查实际使用人、经办人、单位信息共3个条目，各条目中均需包含姓名/单位名称、证件类型、证件号码、
         * 地址四个字段，并符合完整性和真实性要求。 */
        if(!ownerNotReg && !agentNotReg && !unitNotReg && !ownerNok && !agentNok && !unitNok){
            saveUnitMobileOk();
            saveAllOk();
            processOneCardMultiName();
            processOneCardFiveNumber();
            return;
        }
        if(ownerNotReg && !agentNotReg && !unitNotReg ){
            saveUnitMobileOwnerNotReg();
            report->unitMobileNotReg++;
            return;
        }
        if(!ownerNotReg && agentNotReg && !unitNotReg ){
            saveUnitMobileAgentNotReg();
            report->unitMobileNotReg++;
            return;
        }
        if(!ownerNotReg && !agentNotReg && unitNotReg ){
            saveUnitMobileUnitNotReg();
            report->unitMobileNotReg++;
            return;
        }
        if(!ownerNok && agentNok && !unitNok ){
            saveUnitMobileAgentNok();
            report->unitMobileNok++;
            return;
        }
        if(!ownerNok && !agentNok && unitNok ){
            saveUnitMobileUnitNok();
            report->unitMobileNok++;
            return;
        }
        if(ownerNok && agentNok && !unitNok){
            saveUnitMobileOwnerAgentNok();
            report->unitMobileNok++;
            return;
        }
        if(ownerNok && agentNok && !unitNok){
            saveUnitMobileOwnerUnitNok();
            report->unitMobileNok++;
            return;
        }
        if(!ownerNok && agentNok && unitNok){
            saveUnitMobileAgentUnitNok();
            report->unitMobileNok++;
            return;
        }
        if(ownerNok && agentNok && unitNok){
            saveUnitMobileOwnerAgentUnitNok();
            report->unitMobileNok++;
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
            report->tradeMobileNotReg++;
            return;
        }
        if(ownerNok){
            saveTradeMobileOwnerNok();
            report->tradeMobileNok++;
            return;
        }
        /* 2013年9月1日之前入网的行业移动用户，需检查责任人、(实际使用人)、经办人和单位信息中任一个条目，该条目中均需包含姓名/单位名称、证件类型、证件号码、地址，
         * 符合完整性和真实性要求。 */
        if(activeDate < 20130901){
            if((!agentNotReg && !agentNok) || (!unitNotReg && !unitNok) || (!liableNotReg && !liableNok)){
                saveTradeMobileOk();
                saveAllOk();
                processOneCardMultiName();
                return;
            }
            else {
                if(liableNotReg && !agentNotReg && !unitNotReg){
                    saveTradeMobileLiableNotReg();
                    report->tradeMobileNotReg++;
                    return;
                }
                if(!liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeMobileAgentNotReg();
                    report->tradeMobileNotReg++;
                    return;
                }
                if(!liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeMobileUnitNotReg();
                    report->tradeMobileNotReg++;
                    return;
                }
                if(liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeMobileLiableAgentNotReg();
                    report->tradeMobileNotReg++;
                    return;
                }
                if(liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeMobileLiableUnitNotReg();
                    report->tradeMobileNotReg++;
                    return;
                }
                if(!liableNotReg && agentNotReg && unitNotReg){
                    saveTradeMobileAgentUnitNotReg();
                    report->tradeMobileNotReg++;
                    return;
                }
                if(liableNotReg && agentNotReg && unitNotReg){
                    saveTradeMobileLiableAgentUnitNotReg();
                    report->tradeMobileNotReg++;
                    return;
                }
                if(liableNok && !agentNok && !unitNok){
                    saveTradeMobileLiableNok();
                    report->tradeMobileNok++;
                    return;
                }
                if(!liableNok && agentNok && !unitNok){
                    saveTradeMobileAgentNok();
                    report->tradeMobileNok++;
                    return;
                }
                if(!liableNok && !agentNok && unitNok){
                    saveTradeMobileUnitNok();
                    report->tradeMobileNok++;
                    return;
                }
                if(liableNok && agentNok && !unitNok){
                    saveTradeMobileLiableAgentNok();
                    report->tradeMobileNok++;
                    return;
                }
                if(liableNok && !agentNok && unitNok){
                    saveTradeMobileLiableUnitNok();
                    report->tradeMobileNok++;
                    return;
                }
                if(!liableNok && agentNok && unitNok){
                    saveTradeMobileAgentUnitNok();
                    report->tradeMobileNok++;
                    return;
                }
                if(liableNok && agentNok && unitNok){
                    saveTradeMobileLiableAgentUnitNok();
                    report->tradeMobileNok++;
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
                    report->tradeMobileNotReg++;
                    return;
                }
                if(!liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeMobileAgentNotReg();
                    report->tradeMobileNotReg++;
                    return;
                }
                if(!liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeMobileUnitNotReg();
                    report->tradeMobileNotReg++;
                    return;
                }
                if(liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeMobileLiableAgentNotReg();
                    report->tradeMobileNotReg++;
                    return;
                }
                if(liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeMobileLiableUnitNotReg();
                    report->tradeMobileNotReg++;
                    return;
                }
                if(!liableNotReg && agentNotReg && unitNotReg){
                    saveTradeMobileAgentUnitNotReg();
                    report->tradeMobileNotReg++;
                    return;
                }
                if(liableNotReg && agentNotReg && unitNotReg){
                    saveTradeMobileLiableAgentUnitNotReg();
                    report->tradeMobileNotReg++;
                    return;
                }
            }
            if( (liableNok && agentNok) || (liableNok && unitNok) || (agentNok && unitNok)){
                if(liableNok && !agentNok && !unitNok){
                    saveTradeMobileLiableNok();
                    report->tradeMobileNok++;
                    return;
                }
                if(!liableNok && agentNok && !unitNok){
                    saveTradeMobileAgentNok();
                    report->tradeMobileNok++;
                    return;
                }
                if(!liableNok && !agentNok && unitNok){
                    saveTradeMobileUnitNok();
                    report->tradeMobileNok++;
                    return;
                }
                if(liableNok && agentNok && !unitNok){
                    saveTradeMobileLiableAgentNok();
                    report->tradeMobileNok++;
                    return;
                }
                if(liableNok && !agentNok && unitNok){
                    saveTradeMobileLiableUnitNok();
                    report->tradeMobileNok++;
                    return;
                }
                if(!liableNok && agentNok && unitNok){
                    saveTradeMobileAgentUnitNok();
                    report->tradeMobileNok++;
                    return;
                }
                if(liableNok && agentNok && unitNok){
                    saveTradeMobileLiableAgentUnitNok();
                    report->tradeMobileNok++;
                    return;
                }
            }
            else{
                saveTradeMobileOk();
                saveAllOk();
                processOneCardMultiName();
                return;
            }

        }
        else{
            /* 2015年1月1日之后入网的行业移动用户，需检查责任人(实际使用人，优先)、经办人、单位信息共3个条目，各条目中均需包含姓名/单位名称、证件类型、
             * 证件号码、地址四个字段，并符合完整性和真实性要求。 */
            if(agentNotReg && !unitNotReg && !liableNotReg){
                saveTradeMobileAgentNotReg();
                report->tradeMobileNotReg++;
                return;
            }
            if(!agentNotReg && unitNotReg && !liableNotReg){
                saveTradeMobileUnitNotReg();
                report->tradeMobileNotReg++;
                return;
            }
            if(!agentNotReg && !unitNotReg && liableNotReg){
                saveTradeMobileLiableNotReg();
                report->tradeMobileNotReg++;
                return;
            }
            if(agentNotReg && unitNotReg && !liableNotReg){
                saveTradeMobileAgentUnitNotReg();
                report->tradeMobileNotReg++;
                return;
            }
            if(!agentNotReg && unitNotReg && liableNotReg){
                saveTradeMobileLiableUnitNotReg();
                report->tradeMobileNotReg++;
                return;
            }
            if(agentNotReg && !unitNotReg && liableNotReg){
                saveTradeMobileLiableAgentNotReg();
                return;
            }
            if(agentNotReg && unitNotReg && liableNotReg){
                saveTradeMobileLiableAgentUnitNotReg();
                report->tradeMobileNotReg++;
                return;
            }
            if(agentNok && !unitNok && !liableNok){
                saveTradeMobileAgentNok();
                report->tradeMobileNok++;
                return;
            }
            if(!agentNok && unitNok && !liableNok){
                saveTradeMobileUnitNok();
                report->tradeMobileNok++;
                return;
            }
            if(!agentNok && !unitNok && liableNok){
                saveTradeMobileLiableNok();
                report->tradeMobileNok++;
                return;
            }
            if(agentNok && unitNok && !liableNok){
                saveTradeMobileAgentUnitNok();
                report->tradeMobileNok++;
                return;
            }
            if(!agentNok && unitNok && liableNok){
                saveTradeMobileAgentUnitNok();
                report->tradeMobileNok++;
                return;
            }
            if(agentNok && !unitNok && liableNok){
                saveTradeMobileLiableAgentNok();
                report->tradeMobileNok++;
                return;
            }
            if(agentNok && unitNok && liableNok){
                saveTradeMobileLiableAgentUnitNok();
                report->tradeMobileNok++;
                return;
            }
            if(!(ownerNok&&agentNok&&unitNok)){
                saveTradeMobileOk();
                saveAllOk();
                processOneCardMultiName();
                return;
            }

        }


    }
    else {
        saveTradeMobileOk();
        saveAllOk();
        processOneCardMultiName();
        return;
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
            report->tradeFixedNotReg++;
        }
        if(ownerNok){
            saveTradeFixedOwnerNok();
            report->tradeFixedNok++;
        }
        /* 2013年9月1日之前入网的行业固话用户，需检查责任人、(实际使用人)、经办人和单位信息中任一个条目，该条目中均需包含姓名/单位名称、证件类型、证件号码、地址，
         * 符合完整性和真实性要求。 */
        if(activeDate < 20130901){
            if((!agentNotReg && !agentNok) || (!unitNotReg && !unitNok) || (!liableNotReg && !liableNok)){
                saveTradeFixedOk();
                saveAllOk();
                processOneCardMultiName();
                return;
            }
            else {
                if(liableNotReg && !agentNotReg && !unitNotReg){
                    saveTradeFixedLiableNotReg();
                    report->tradeFixedNotReg++;
                    return;
                }
                if(!liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeFixedAgentNotReg();
                    report->tradeFixedNotReg++;
                    return;
                }
                if(!liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeFixedUnitNotReg();
                    report->tradeFixedNotReg++;
                    return;
                }
                if(liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeFixedAgentLiableNotReg();
                    report->tradeFixedNotReg++;
                    return;
                }
                if(liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeFixedLiableUnitNotReg();
                    report->tradeFixedNotReg++;
                    return;
                }
                if(!liableNotReg && agentNotReg && unitNotReg){
                    saveTradeFixedAgentUnitNotReg();
                    report->tradeFixedNotReg++;
                    return;
                }
                if(liableNotReg && agentNotReg && unitNotReg){
                    saveTradeFixedAgentLiableUnitNotReg();
                    report->tradeFixedNotReg++;
                    return;
                }
                if(liableNok && !agentNok && !unitNok){
                    saveTradeFixedLiableNok();
                    report->tradeFixedNok++;
                    return;
                }
                if(!liableNok && agentNok && !unitNok){
                    saveTradeFixedAgentNok();
                    report->tradeFixedNok++;
                    return;
                }
                if(!liableNok && !agentNok && unitNok){
                    saveTradeFixedUnitNok();
                    report->tradeFixedNok++;
                    return;
                }
                if(liableNok && agentNok && !unitNok){
                    saveTradeFixedAgentLiableNok();
                    report->tradeFixedNok++;
                    return;
                }
                if(liableNok && !agentNok && unitNok){
                    saveTradeFixedLiableUnitNok();
                    report->tradeFixedNok++;
                    return;
                }
                if(!liableNok && agentNok && unitNok){
                    saveTradeFixedAgentUnitNok();
                    report->tradeFixedNok++;
                    return;
                }
                if(liableNok && agentNok && unitNok){
                    saveTradeFixedAgentLiableUnitNok();
                    report->tradeFixedNok++;
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
                    report->tradeFixedNotReg++;
                    return;
                }
                if(!liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeFixedAgentNotReg();
                    report->tradeFixedNotReg++;
                    return;
                }
                if(!liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeFixedUnitNotReg();
                    report->tradeFixedNotReg++;
                    return;
                }
                if(liableNotReg && agentNotReg && !unitNotReg){
                    saveTradeFixedAgentLiableNotReg();
                    report->tradeFixedNotReg++;
                    return;
                }
                if(liableNotReg && !agentNotReg && unitNotReg){
                    saveTradeFixedLiableUnitNotReg();
                    report->tradeFixedNotReg++;
                    return;
                }
                if(!liableNotReg && agentNotReg && unitNotReg){
                    saveTradeFixedAgentUnitNotReg();
                    report->tradeFixedNotReg++;
                    return;
                }
                if(liableNotReg && agentNotReg && unitNotReg){
                    saveTradeFixedAgentLiableUnitNotReg();
                    report->tradeFixedNotReg++;
                    return;
                }
            }
            if( (liableNok && agentNok) || (liableNok && unitNok) || (agentNok && unitNok)){
                if(liableNok && !agentNok && !unitNok){
                    saveTradeFixedLiableNok();
                    report->tradeFixedNok++;
                    return;
                }
                if(!liableNok && agentNok && !unitNok){
                    saveTradeFixedAgentNok();
                    report->tradeFixedNok++;
                    return;
                }
                if(!liableNok && !agentNok && unitNok){
                    saveTradeFixedUnitNok();
                    report->tradeFixedNok++;
                    return;
                }
                if(liableNok && agentNok && !unitNok){
                    saveTradeFixedAgentLiableNok();
                    report->tradeFixedNok++;
                    return;
                }
                if(liableNok && !agentNok && unitNok){
                    saveTradeFixedLiableUnitNok();
                    report->tradeFixedNok++;
                    return;
                }
                if(!liableNok && agentNok && unitNok){
                    saveTradeFixedAgentUnitNok();
                    report->tradeFixedNok++;
                    return;
                }
                if(liableNok && agentNok && unitNok){
                    saveTradeFixedAgentLiableUnitNok();
                    report->tradeFixedNok++;
                    return;
                }
            }
            else{
                saveTradeFixedOk();
                saveAllOk();
                processOneCardMultiName();
                return;
            }

        }
        else{
            /* 2015年1月1日之后入网的行业固话用户，需检查责任人(实际使用人，优先)、经办人、单位信息共3个条目，各条目中均需包含姓名/单位名称、证件类型、
             * 证件号码、地址四个字段，并符合完整性和真实性要求。 */
            if(agentNotReg && !unitNotReg && !liableNotReg){
                saveTradeFixedAgentNotReg();
                report->tradeFixedNotReg++;
                return;
            }
            if(!agentNotReg && unitNotReg && !liableNotReg){
                saveTradeFixedUnitNotReg();
                report->tradeFixedNotReg++;
                return;
            }
            if(!agentNotReg && !unitNotReg && liableNotReg){
                saveTradeFixedLiableNotReg();
                report->tradeFixedNotReg++;
                return;
            }
            if(agentNotReg && unitNotReg && !liableNotReg){
                saveTradeFixedAgentUnitNotReg();
                report->tradeFixedNotReg++;
                return;
            }
            if(!agentNotReg && unitNotReg && liableNotReg){
                saveTradeFixedLiableUnitNotReg();
                report->tradeFixedNotReg++;
                return;
            }
            if(agentNotReg && !unitNotReg && liableNotReg){
                saveTradeFixedAgentLiableNotReg();
                report->tradeFixedNotReg++;
                return;
            }
            if(agentNotReg && unitNotReg && liableNotReg){
                saveTradeFixedAgentLiableUnitNotReg();
                report->tradeFixedNotReg++;
                return;
            }
            if(agentNok && !unitNok && !liableNok){
                saveTradeFixedAgentNok();
                report->tradeFixedNok++;
                return;
            }
            if(!agentNok && unitNok && !liableNok){
                saveTradeFixedUnitNok();
                report->tradeFixedNok++;
                return;
            }
            if(!agentNok && !unitNok && liableNok){
                saveTradeFixedLiableNok();
                report->tradeFixedNok++;
                return;
            }
            if(agentNok && unitNok && !liableNok){
                saveTradeFixedAgentUnitNok();
                report->tradeFixedNok++;
                return;
            }
            if(!agentNok && unitNok && liableNok){
                saveTradeFixedAgentUnitNok();
                report->tradeFixedNok++;
                return;
            }
            if(agentNok && !unitNok && liableNok){
                saveTradeFixedAgentLiableNok();
                report->tradeFixedNok++;
                return;
            }
            if(agentNok && unitNok && liableNok){
                saveTradeFixedAgentLiableUnitNok();
                report->tradeFixedNok++;
                return;
            }
            if(!(ownerNok&&agentNok&&unitNok)){
                saveTradeFixedOk();
                saveAllOk();
                processOneCardMultiName();
                return;
            }

        }


    }
    else {
        saveTradeFixedOk();
        saveAllOk();
        processOneCardMultiName();
        return;

    }

}

/**
 * @brief UserDb::processOneCardFiveNumber 处理一证五号
 */
void UserDb::processOneCardFiveNumber(){
    stErrorFiveNum *ptrMulti = nullptr,*pptr;
    unsigned long activeDay ,checkDay;

    activeDay = getDateForInt(col.at(getColNum("登记激活时间")));
    checkDay = 20170401;
    unsigned long sHashTreev = strHash(col.at(ownerNumIndex).toStdString().c_str(),strlen(col.at(ownerNumIndex).toStdString().c_str()))%MAX_NUMBER_HASH_NODE;
    if(m_pstErrFiveName[sHashTreev] == nullptr)
    {
        ptrMulti = (stErrorFiveNum *)bchunkAllocNode(&bErrFive);
        if(ptrMulti == nullptr) //out of memory
            return;
        if(strlen(col.at(ownerNumIndex).toStdString().c_str())+1 <= MAX_NUMBER_LENGTH)
            memcpy(ptrMulti->number,col.at(ownerNumIndex).toStdString().c_str(),strlen(col.at(ownerNumIndex).toStdString().c_str())+1);
        else
            memcpy(ptrMulti->number,col.at(ownerNumIndex).toStdString().c_str(),MAX_NUMBER_LENGTH-1);
        ptrMulti->errflag = 0x01;
        ptrMulti->activeDay = activeDay; //Need More Information
        if(activeDay >= checkDay && ptrMulti->errcount < 0x7f) ptrMulti->errcount ++;

        m_pstErrFiveName[sHashTreev] = ptrMulti;
        return;
    }
    else{
        ptrMulti = m_pstErrFiveName[sHashTreev];
        do{
            if(0 == strcmp(ptrMulti->number,col.at(ownerNumIndex).toStdString().c_str()))
            {
                if(activeDay >= checkDay && ptrMulti->errcount < 0x7f)
                    ptrMulti->errcount ++;
                if(ptrMulti->errflag&errType_oneCardFiveNumber)
                {
                    if(activeDay >= checkDay)
                        errCardCount ++;
                    return;
                }
                if(activeDay > ptrMulti->activeDay )
                    ptrMulti->activeDay = activeDay;
                if((ptrMulti->errflag&0x3f) != 0x3f) ptrMulti->errflag ++;
                if((ptrMulti->activeDay >= checkDay) && (ptrMulti->errflag&0x3f) > 5)
                {
                    errFiveNumber ++;
                    ptrMulti->errflag = errType_oneCardFiveNumber + (ptrMulti->errflag&0x3f);
                    errCardCount += ptrMulti->errcount;
                }
                return;
            }
            pptr = ptrMulti;
            ptrMulti = ptrMulti->next;
        }while(ptrMulti != nullptr);

        ptrMulti = pptr;
        ptrMulti->next = (stErrorFiveNum *)bchunkAllocNode(&bErrFive);
        if(ptrMulti->next == nullptr)
            return;
        ptrMulti = ptrMulti->next;
        if(strlen(col.at(ownerNumIndex).toStdString().c_str())+1 <= MAX_NUMBER_LENGTH)
            memcpy(ptrMulti->number,col.at(ownerNumIndex).toStdString().c_str(),strlen(col.at(ownerNumIndex).toStdString().c_str())+1);
        else
            memcpy(ptrMulti->number,col.at(ownerNumIndex).toStdString().c_str(),MAX_NUMBER_LENGTH-1);
        ptrMulti->errflag = 0x01;
        ptrMulti->activeDay = activeDay;
        if(activeDay >= checkDay && ptrMulti->errcount < 0x7f) ptrMulti->errcount ++;
    }
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
    //col.at(ownerNameIndex)   机主名称
    //col.at(ownerNumIndex)    机主号码
    stErrorMultiName *ptrMulti = nullptr,*pptr;
    size_t  slen = strlen(col.at(ownerNumIndex).toStdString().c_str());

    unsigned long sHashTreev = strHash(col.at(ownerNumIndex).toStdString().c_str(),slen)%MAX_NUMBER_HASH_NODE;
    if(slen + 1 <= MAX_NUMBER_LENGTH ) slen = slen + 1;
    else {
        slen = MAX_NUMBER_LENGTH - 1;
    }
    if(m_pstErrMultiName[sHashTreev] == nullptr)
    {
        ptrMulti = (stErrorMultiName *)bchunkAllocNode(&bErrMulti);
        if(ptrMulti == nullptr) //out of memory
            return;
        if(strlen(col.at(ownerNumIndex).toStdString().c_str())+1 <= MAX_NUMBER_LENGTH)
            memcpy(ptrMulti->number,col.at(ownerNumIndex).toStdString().c_str(),strlen(col.at(ownerNumIndex).toStdString().c_str())+1);
        else
            memcpy(ptrMulti->number,col.at(ownerNumIndex).toStdString().c_str(),MAX_NUMBER_LENGTH-1);
       if(strlen(col.at(ownerNameIndex).toStdString().c_str())+1 <= MAX_NAME_LENGTH)
            memcpy(ptrMulti->origName,col.at(ownerNameIndex).toStdString().c_str(),strlen(col.at(ownerNameIndex).toStdString().c_str())+1);
        else
            memcpy(ptrMulti->origName,col.at(ownerNameIndex).toStdString().c_str(),MAX_NAME_LENGTH-1);
        ptrMulti->errflag = id_TypeChar;
        m_pstErrMultiName[sHashTreev] = ptrMulti;
        return;
    }
    else{
        ptrMulti = m_pstErrMultiName[sHashTreev];
        do{
            if(0 == strcmp(ptrMulti->number,col.at(ownerNumIndex).toStdString().c_str())
                    && id_TypeChar == (ptrMulti->errflag&id_TypeMask))
            {
                if((ptrMulti->errflag&errType_oneCardMultiName) == errType_oneCardMultiName)
                    return;
                if(0 != strncmp(ptrMulti->origName,col.at(ownerNameIndex).toStdString().c_str(),strlen(ptrMulti->origName)))
                {
                    ptrMulti->errflag |= errType_oneCardMultiName;
                    errMultiName ++;
                }
                return;
            }
            pptr = ptrMulti;
            ptrMulti = ptrMulti->next;
        }while(ptrMulti != nullptr);

        ptrMulti = pptr;
        ptrMulti->next = (stErrorMultiName *)bchunkAllocNode(&bErrMulti);
        if(ptrMulti->next == nullptr)
            return;
        ptrMulti = ptrMulti->next;
        if(strlen(col.at(ownerNumIndex).toStdString().c_str())+1 <= MAX_NUMBER_LENGTH)
            memcpy(ptrMulti->number,col.at(ownerNumIndex).toStdString().c_str(),strlen(col.at(ownerNumIndex).toStdString().c_str())+1);
        else
            memcpy(ptrMulti->number,col.at(ownerNumIndex).toStdString().c_str(),MAX_NUMBER_LENGTH-1);
       if(strlen(col.at(ownerNameIndex).toStdString().c_str())+1 <= MAX_NAME_LENGTH)
            memcpy(ptrMulti->origName,col.at(ownerNameIndex).toStdString().c_str(),strlen(col.at(ownerNameIndex).toStdString().c_str())+1);
        else
            memcpy(ptrMulti->origName,col.at(ownerNameIndex).toStdString().c_str(),MAX_NAME_LENGTH-1);
       ptrMulti->errflag = id_TypeChar;
    }
/*
    if(onecardMultiName.size()==0){
        onecardMultiName.insert(col.at(ownerNameIndex), col.at(ownerNumIndex));
    }
    else{
        Map<QString,QString>::Iterator  it;
        for(it = onecardMultiName.begin();it != onecardMultiName.end();++it){
            if(!it.key().compare(col.at(ownerNameIndex))&& it.value().compare(col.at(ownerNumIndex))){
                  saveOnecardMultiName();
            }
        }
    }

}
(ownerNumIndex))){
                  saveOnecardMultiName();
            }
        }
    }
*/
}
