#include "userdb.h"

#define FILE_DIV_TEST  0
#if  FILE_DIV_TEST
#define TEST_LIMIT   1000000
#endif

/**
 * @brief UserDb::UserDb
 * 数据分析文件
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
     cstrHashm18personType = 0;
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
    {
        free(pchunk->chunks[index]);
        pchunk->chunks[index] = nullptr;
    }
}

void UserDb::bchunkReset(bchunk_t *pchunk)
{
    pchunk->ncount = 0;
}

void *UserDb::bchunkAllocNode(bchunk_t *pchunk)
{
    void *pstr = nullptr;
    if(pchunk->ncount >= MAX_BCHUNKS * MAX_BCHUNKNODES)return pstr;
    //out of memory
    if(0 == (pchunk->ncount%MAX_BCHUNKNODES))
    {
        if(pchunk->chunks[pchunk->ncount/MAX_BCHUNKNODES] == nullptr)
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

//计算18位身份证的校验位
char UserDb::calculateVerifyCode(const char* m_str)
{
    static char VERIFY_CODE[] = { '1', '0', 'X', '9', '8', '7',  '6', '5', '4', '3', '2' };
    static int  VERIFY_CODE_WEIGHT[] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };
    int sum = 0;
    for (int i = 0; i < 17; i++) {
        sum += VERIFY_CODE_WEIGHT[i] * ((int) (m_str[i] - '0')) ;
    }
    return VERIFY_CODE[sum % 11];
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
//        personType = readValueToList(personType, "个人证件非法律、行政法规和国家规定的有效身份证件",strHashpersonType,cstrHashpersonType);

        m18personType = readValueToList(m18personType, "个人证件居民身份证",strHashm18personType,cstrHashm18personType);
        m18personType = readValueToList(m18personType, "个人证件临时居民身份证",strHashm18personType,cstrHashm18personType);
        m18personType = readValueToList(m18personType, "个人证件户口薄",strHashm18personType,cstrHashm18personType);

        //初始化单位合规证件类型
        unitType  = readValueToList(unitType, "单位证件组织机构代码证",strHashunitType,cstrHashunitType);
        unitType  = readValueToList(unitType, "单位证件营业执照",strHashunitType,cstrHashunitType);
        unitType  = readValueToList(unitType, "单位证件事业单位法人证书或者社会团体法人登记证书",strHashunitType,cstrHashunitType);
        unitType  = readValueToList(unitType, "单位证件法律、行政法规和国家规定的其他有效证件或者证明文件",strHashunitType,cstrHashunitType);
//        unitType  = readValueToList(unitType, "单位证件非法律、行政法规和国家规定的有效证件",strHashunitType,cstrHashunitType);

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
        personNameRule = readValueToList1(personNameRule, "个人用户姓名comon-rule",strHashpersonNameRule,cstrHashpersonNameRule);
        personNameRule = readValueToList1(personNameRule, "个人用户姓名match-rule",nullptr,cstrHashpersonNameRule);
        //初始化单位/行业用户名称不合规
        unitNameRule = readValueToList1(unitNameRule, "行业用户姓名comon-rule",strHashunitNameRule,cstrHashunitNameRule);
        unitNameRule = readValueToList1(unitNameRule, "行业用户姓名match-rule",nullptr,cstrHashunitNameRule);
        //初始化个人证件号码不合规
        //初始化单位证件号码不合规
        numRule = readValueToList1(numRule, "证件号码comon-rule",strHashnumRule,cstrHashnumRule);
        numRule = readValueToList1(numRule, "证件号码match-rule",nullptr,cstrHashnumRule);
        //初始化个人证件地址不合规
        //初始化单位证件地址不合规
        addRule = readValueToList1(addRule, "证件地址addr-rule",strHashaddRule,cstrHashaddRule);
        addRule = readValueToList1(addRule, "证件地址match-rule",nullptr,cstrHashaddRule);

        nonRealName = readValueToList(nonRealName, "业务状态非实名停机",strHashnonRealName,cstrHashnonRealName);
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
        rtn.append(list.at(i).trimmed());
    }
    return rtn;
}

QList<QString> UserDb::readValueToList(QList<QString> inList, QString query,strHashNode *psHNode,int &psHNodeCount){
    QList<QString> list = xmlConfig->readValue(query);
    for(int i=0; i<list.size(); i++){
        psHNode[psHNodeCount].sHashKey = strHash(list.at(i).trimmed().toStdString().c_str(),strlen(list.at(i).toStdString().c_str()));
        memcpy(psHNode[psHNodeCount].sHashContent,list.at(i).trimmed().toStdString().c_str(),strlen(list.at(i).toStdString().c_str())+1);
        inList.append(list.at(i).trimmed());
        psHNodeCount ++;
    }
    return inList;
}

QList<QString> UserDb::readValueToList1(QList<QString> inList, QString query,strHashNode *psHNode,int &psHNodeCount){
    QList<QString> list = xmlConfig->readValue(query);
    if(psHNode == nullptr)
    {
        for(int i=0; i<list.size(); i++)inList.append(list.at(i).trimmed());
    }
    else
    {
        for(int i=0; i<list.size(); i++){
            psHNode[psHNodeCount].sHashKey = strHash(list.at(i).trimmed().toStdString().c_str(),strlen(list.at(i).toStdString().c_str()));
            memcpy(psHNode[psHNodeCount].sHashContent,list.at(i).trimmed().toStdString().c_str(),strlen(list.at(i).toStdString().c_str())+1);
            psHNodeCount ++;
        }
    }
    return inList;
}

void UserDb::printMessage(){
   // qDebug()<<QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId());
}

UserDb::~UserDb()
{
    delete report;
    delete xmlConfig;
    bchunkFree(&bErrMulti);
    bchunkFree(&bErrFive);
}

void UserDb::run()
{
    QTime    tmpTime;
//    readConfig();
    report->init();

    QString m_tmpstr = xmlConfig->readItemnumValue().value("itemnum");
    int  needdivFile = m_tmpstr.toInt();
    if(needdivFile > 0)
        m_needdivFile = true;
    else
        m_needdivFile = false;

    if(m_needdivFile == true)
    {
        divFile();
        tmpTime.start();
        for(int tmpindex = 0;tmpindex <= m_fileindex ; tmpindex ++)
            countData(path+QDir::separator()+m_basename+QString::number(tmpindex));
        if(m_leaveindex != -1)
            countData(path+QDir::separator()+m_leavename+QString::number(m_leaveindex));
    }
    else {
        tmpTime.start();
        countData();
    }
    report->errFiveNumber = errFiveNumber;
    report->errCardCount = errCardCount;
    report->errMultiName = errMultiName;
    emit message("waiting...");

    report->setTableValue(path+QDir::separator());
    emit message("finished.");
    emit messageWarning("检测完成，用时"+QString::number(tmpTime.elapsed()/1000.0)+"秒");

    if(m_needdivFile == true)
    {
        for(int tmpindex = 0;tmpindex <= m_fileindex ; tmpindex ++)
            QFile::remove(path+QDir::separator()+m_basename+QString::number(tmpindex));
        if(m_leaveindex != -1)
            QFile::remove(path+QDir::separator()+m_leavename+QString::number(m_leaveindex));
    }
}

int UserDb::getColNum(QString name){
        return col_name_map.value(name);
}


void UserDb::initIndex(){
    //codeStatusIndex = getColNum("使用状态");
    codeStatusIndex = getColNum("号码状态");
    activeTimeIndex = getColNum("登记激活时间");
    userTypeInex = getColNum("用户类型");
    bizTypeIndex = getColNum("用户业务类型");
    ownerNameIndex = getColNum("机主姓名");
    ownerTypeIndex = getColNum("机主证件类型");
    ownerNumIndex = getColNum("机主证件号码");
    ownerAddIndex = getColNum("机主证件地址");
    ownerAdd1Index = getColNum("机主通讯地址");
    ownerAdd2Index = getColNum("机主装机地址");

    agentNameIndex = getColNum("代（经）办人姓名");
    agentTypeIndex = getColNum("代（经）办人证件类型");
    agentNumIndex = getColNum("代（经）办人证件号码");
    agentAddIndex = getColNum("代（经）办人证件地址");
    agentAdd1Index = getColNum("代（经）办人通讯地址");

    liableNameIndex = getColNum("责任人姓名");
    liableTypeIndex = getColNum("责任人证件类型");
    liableNumIndex = getColNum("责任人证件号码");
    liableAddIndex = getColNum("责任人证件地址");
    liableAdd1Index = getColNum("责任人通讯地址");

    unitNameIndex = getColNum("单位名称");
    unitNumIndex = getColNum("单位证件号码");
    unitTypeIndex = getColNum("单位证件类型");
    unitAddIndex = getColNum("单位证件地址");
    unitAdd1Index = getColNum("单位通讯地址");
    unitAdd2Index = getColNum("单位装机地址");

    msisdnIndex = getColNum("MSISDN号码");
}

bool UserDb::countData(const QString filename){
    QString pname = filename;
    if(filename == nullptr)
        pname = m_filename;
    if(pname.isNull()||pname.isEmpty())return false;

    QFile file(pname);
    if(!file.exists())return false;
    bchunkReset(&bErrFive);
    bchunkReset(&bErrMulti);
    memset(m_pstErrMultiName,0,sizeof(stErrorMultiName *)*MAX_NUMBER_HASH_NODE);
    memset(m_pstErrFiveName,0,sizeof(stErrorFiveNum *)*MAX_NUMBER_HASH_NODE);

    QTextCodec *code = QTextCodec::codecForName("GBK");//设置文件编码
    int line_num = 0;
    if(file.open(QFile::ReadOnly | QFile::Text )){
        QTextStream stream(&file);
        stream.setCodec(code);

         do {
            line = stream.readLine();
            processLine();
            report->allData++;
            line_num++;
#if       FILE_DIV_TEST
            if(line_num >= TEST_LIMIT)
                break;
#endif
            if(line_num%1000==0)
            {
                emit message("已处理文件"+pname+","+QString::number(line_num)+"行");
            }
        }while(!stopped && !stream.atEnd());
        file.close();
        emit message("已处理完成，文件关闭");
    }
    else{
        emit messageWarning("文件打开错误。");
    }

    int nodecount = outputSimpleOneCardFiveNumber();
    if(file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream stream(&file);
        stream.setCodec(code);
        line_num = 0;

         do {
            line = stream.readLine();
            processLineoutput();
            line_num++;
#if       FILE_DIV_TEST
            if(line_num >= TEST_LIMIT)
                break;
#endif
            if(line_num%1000==0)
            {
                emit message("已二次输出"+pname+","+QString::number(line_num)+"行");
            }
        }while(!stopped && !stream.atEnd());
        file.close();
        emit message("已二次输出处理完成，文件再次关闭");
    }
    else{
        emit messageWarning("文件打开错误。");
    }
    flushFile();
#define   NODE_LIMIT_ONECARDFIVENUMBER  2500
    if(nodecount <= NODE_LIMIT_ONECARDFIVENUMBER)
    {
        writeOneCardFiveNumberFile();
        flushFile();
                QFile::remove(path+QDir::separator()+"一证五号不合规原始.nck"); //超大文件，分段输出合并
    }
    else {
        QFile::rename(path+QDir::separator()+"一证五号不合规原始.nck",path+QDir::separator()+"一证五号不合规.nck");
    }
    return true;
}

/**
 * @brief UserDb::isNotReg
 * @param str
 * @return 字段未空指针、null或空字符串。
 */
bool UserDb::isNotReg(QString *str){
    if(str==nullptr)return true;
    if(str->isEmpty())return true;
    if(0 == (*str).trimmed().length())return true;
    if(!(*str).trimmed().compare("null", Qt::CaseInsensitive))return true;
    return false;
}

bool UserDb::isNotReg(QString const str){
    if(str==nullptr)return true;
    if(str.isEmpty())return true;
    if(0 == str.trimmed().length())return true;
    if(!str.trimmed().compare("null", Qt::CaseInsensitive))return true;
    return false;
}

/**
 * @brief UserDb::isPersonTypeNok
 * @param str 证件类型
 * @return 个人证件类型是否不合规
 */
bool UserDb::isPersonTypeNok(QString const &str){
    if(isNotReg(str))return true;
    unsigned long sHashv = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
    for(int index = 0;index < cstrHashpersonType ;index ++){
        if(strHashpersonType[index].sHashKey == sHashv){
            if(0 == strcmp(strHashpersonType[index].sHashContent,str.toStdString().c_str()) )return false;
        }
    }
    return true;
}

bool UserDb::isUnitTypeNok(QString const &str){
    if(isNotReg(str))return true;
    unsigned long sHashv = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
    for(int index = 0;index < cstrHashunitType ;index ++){
        if(strHashunitType[index].sHashKey == sHashv){
            if(0 == strcmp(strHashunitType[index].sHashContent,str.toStdString().c_str()) )return false;
        }
    }
    return true;
}

bool UserDb::isPersonNameNok(QString const & str){
    if(isNotReg(str))return true;
    if(personNameMin!=-1 && str.length()<personNameMin)return true;
    if(personNameMax!=-1 && str.length()>personNameMax)return true;

    unsigned long sHashv = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
    int index ;
    for(index = 0;index < cstrHashpersonNameRule ;index ++) {//common-rule
        if(strHashpersonNameRule[index].sHashKey == sHashv){
            if(0 == strcmp(strHashpersonNameRule[index].sHashContent,str.toStdString().c_str()) )return true;
        }
     }
     for(index = 0; index <personNameRule.size(); index++) //match-rule
        if(str.contains(personNameRule.at(index)))return true;
    return false;
}

bool UserDb::isUnitNameNok(QString const & str){
    if(isNotReg(str))return true;
    if(unitNameMin!=-1 && str.length()<unitNameMin)return true;
    if(unitNameMax!=-1 && str.length()>unitNameMax)return true;
        unsigned long sHashv = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
        int index ;
        for(index = 0;index < cstrHashunitNameRule ;index ++){
            if(strHashunitNameRule[index].sHashKey == sHashv){
                if(0 == strcmp(strHashunitNameRule[index].sHashContent,str.toStdString().c_str()) )return true;
            }
        }

        for(index = 0; index <unitNameRule.size(); index++) //match-rule
            //20190313 单位名称仍然是模糊匹配也认为不合规
            if(str.contains(unitNameRule.at(index)))return true;
            //包含单位名称关键字，即认为合规
            //if(str.contains(unitNameRule.at(index)))return false;
    return false;
}

bool UserDb::isPersonNumNok(QString const & numstr,QString const & typestr){
    if(isNotReg(numstr))return true;
    if(personNumMin!=-1 && numstr.length()<personNumMin)return true;
    if(personNumMax!=-1 && numstr.length()>personNumMax)return true;
        unsigned long sHashv = strHash(numstr.toStdString().c_str(),strlen(numstr.toStdString().c_str()));
        int index;
        for(index = 0;index < cstrHashnumRule ;index ++){//common-rule
            if(strHashnumRule[index].sHashKey == sHashv){
                if(0 == strcmp(strHashnumRule[index].sHashContent,numstr.toStdString().c_str()) )return true;
            }
        }
        for(index = 0; index <numRule.size(); index++) //match-rule
            if(numstr.contains(numRule.at(index)))return true;
    //检查证件类型   m18personType
    unsigned long m18sHashv = strHash(typestr.toStdString().c_str(),strlen(typestr.toStdString().c_str()));
    int m18index;
    for(m18index = 0;m18index < cstrHashm18personType ;m18index ++) {
        if(strHashm18personType[m18index].sHashKey == m18sHashv){
            if(0 == strcmp(strHashm18personType[m18index].sHashContent,typestr.toStdString().c_str()) )break;
        }
    }
    //不是18位身份证件，返回false（合规）
    if(m18index == cstrHashm18personType)return false;
    //长度不是18(15)，不合规
    int plen = strlen(numstr.toStdString().c_str());
    if(plen != 18 && plen != 15) return true;
    if(plen == 15 && activeDate >= 20130901)//2013年9月1日以后入网采用15位身份证入网要判为“证件号码不合规”
            return true;
    for(int i = 0; i < plen - 1; i ++ )
        if(numstr.toStdString().at(i)< '0' ||numstr.toStdString().at(i) > '9') return true;
    if(plen == 15 && (numstr.toStdString().at(plen-1)< '0' || numstr.toStdString().at(plen-1) > '9'))return true;

    QString mnumstr;
    if(plen == 18)
    {
                char calv = calculateVerifyCode(numstr.toStdString().c_str());
                if(calv != 'X')
                {
            if(calv != numstr.toStdString().at(17))return true;
                }
                else
                {
                        if(numstr.toStdString().at(17) != 'x' && numstr.toStdString().at(17) != 'X') return true;
                }
        mnumstr = numstr;
    }
    else  //15位
        {
        mnumstr = numstr.mid(0,6)+"19"+numstr.mid(6,9)+"?";
        }

                //确保从6~8位取出来的内容可以正确转换为时间：按照yyyyMMDD的方式
        const char* pstr = mnumstr.mid(6,8).toStdString().c_str();
        if(pstr[0]!='1'&&pstr[0]!='2')return true;
        if((pstr[0]=='1'&&pstr[1]!='9')||(pstr[0]=='2'&&pstr[1]!='0'))return true;
        if(pstr[4]!='0'&&pstr[4]!='1')return true;

        return false;
}

bool UserDb::isUnitNumNok(QString const & str){
    if(isNotReg(str))return true;
    if(unitNumMin!=-1 && str.length()<unitNumMin)return true;
    if(unitNumMax!=-1 &&str.length()>unitNumMax)return true;
        unsigned long sHashv = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
        int index ;
        for(index = 0;index < cstrHashnumRule ;index ++) {//common-rule
            if(strHashnumRule[index].sHashKey == sHashv){
                if(0 == strcmp(strHashnumRule[index].sHashContent,str.toStdString().c_str()) )return true;
            }
        }
        for(index = 0; index <numRule.size(); index++) //match-rule
            if(str.contains(numRule.at(index)))return true;
    return false;
}

bool UserDb::isPersonAddNok(QString const & str){
    if(isNotReg(str))return true;
    if(str.trimmed().toStdString().at(0) >= '0' && str.trimmed().toStdString().at(0) <= '9')return true;
    if(-1!=personAddMin && str.length()<personAddMin)return true;
    if(-1!=personAddMax && str.length()>personAddMax)return true;
        unsigned long sHashv = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
        int index ;
        for(index = 0;index < cstrHashaddRule ;index ++){ //addr-rule
            if(strHashaddRule[index].sHashKey == sHashv){
                if(0 == strcmp(strHashaddRule[index].sHashContent,str.toStdString().c_str()) )return true;
            }
        }
        for(index = 0; index <addRule.size(); index++) //match-rule
            if(str.contains(addRule.at(index)))return true;
    return false;
}

bool UserDb::isUnitAddNok(QString const & str){
    if(isNotReg(str))return true;
    if(str.trimmed().toStdString().at(0) >= '0' && str.trimmed().toStdString().at(0) <= '9')return true;
    if(-1!=unitAddMin && str.length()<unitAddMin)return true;
    if(-1!=unitAddMax && str.length()>unitAddMax)return true;
        unsigned long sHashv = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
        int index ;
        for(index = 0;index < cstrHashaddRule ;index ++){ //addr-rule
            if(strHashaddRule[index].sHashKey == sHashv){
                if(0 == strcmp(strHashaddRule[index].sHashContent,str.toStdString().c_str()) )return true;
            }
        }
        for(index = 0; index <addRule.size(); index++) //match-rule
            if(str.contains(addRule.at(index)))return true;
    return false;
}

void UserDb::processLine(){
    col =  line.split(delimeter);

    /*格式异常数据*/
    if(col.size() != COL_NUM){
        writeFile("格式异常数据.abnormal", report->formatNok);
        return;
    }

    /*非实名停机和销户的，不纳入检查范围，单独统计数字，加在报表里。*/
    if(nonRealName.contains(col.at(codeStatusIndex))){
        writeFile("非实名制停机.txt", report->nonRealName);
        return;
    }
    if(leaveNet.contains(col.at(codeStatusIndex))){
        writeFile("离网状态.txt", report->leaveNet);
        return;
    }

    /* 字段异常数据.abnormal */
    if(col.at(activeTimeIndex)==nullptr || isNotReg(col[activeTimeIndex])){
        writeFile("字段异常数据.abnormal", report->fieldNok);
        return;
    }
        activeDate = getDateForInt(col.at(activeTimeIndex));
    if(activeDate == 0)
    {
        writeFile("格式异常数据.abnormal", report->formatNok);
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

        writeFile("字段异常数据.abnormal", report->fieldNok);
        /* 除用户类型和用户业务类型之外为空的、字段全部为空的，计入全量未登记。 */
        int notRegCount = 0;
        for(int i=0;i<col.size();i++){
            if(isNotReg(col[i])){
                notRegCount ++;
            }
        }
        if(notRegCount>=COL_NUM-2){
            writeFile("全量未登记.nreg", report->allNotReg);
        }
    }
}

void UserDb::processLineoutput(){

    stErrorMultiName *ptrMulti;
    stErrorFiveNum   *ptrFive;
    col =  line.split(delimeter);
    /*格式异常数据*/
    if(col.size() != COL_NUM)return;
    if(nonRealName.contains(col.at(codeStatusIndex)) || leaveNet.contains(col.at(codeStatusIndex)))return;

    /* 字段异常数据.abnormal */
    if(col.at(activeTimeIndex)==nullptr || isNotReg(col[activeTimeIndex]))        return;

    id_TypeChar = id_typeknown;
    /* 根据用户类型和用户业务类型进入到具体逻辑规则中判断和输出。 */
    if(userType.value("person").contains(col.at(userTypeInex))){  /*个人用户*/
        if(bizTypeFixed.contains(col.at(bizTypeIndex))) /*个人固定用户*/
            id_TypeChar = id_personTelephone;
        else /*个人移动用户*/
            id_TypeChar = id_personMobile;
    }
    else if(userType.value("unit").contains(col.at(userTypeInex))){  /*单位用户*/
        if(bizTypeFixed.contains(col.at(bizTypeIndex))) /*单位固话用户*/
            id_TypeChar = id_unitTelephone;
        else
            id_TypeChar = id_unitMobile;
    }
    else if(userType.value("industry").contains(col.at(userTypeInex))){
        if(bizTypeFixed.contains(col.at(bizTypeIndex)))
            id_TypeChar = id_serviceTelephone;
        else
            id_TypeChar = id_serviceMobile;
    }
    if(id_TypeChar == id_typeknown)return;

    unsigned long sHashTreev = strHash(col.at(ownerNumIndex).toStdString().c_str(),strlen(col.at(ownerNumIndex).toStdString().c_str()))%MAX_NUMBER_HASH_NODE;
    if(m_pstErrMultiName[sHashTreev] != nullptr)
    {
        ptrMulti = m_pstErrMultiName[sHashTreev];
        do{
            if((ptrMulti->errflag&id_TypeMask) == id_TypeChar)
            {
                if(0 == strncmp(ptrMulti->number,col.at(ownerNumIndex).toStdString().c_str(),strlen(ptrMulti->number)))
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
                            writeFile("个人移动一证多名不合规.nck",report->personMobileOneCard);
                            break;
                        case id_personTelephone:
                            writeFile("个人固话一证多名不合规.nck", report->personFixedOneCard);
                            break;
                        case id_unitMobile:
                            writeFile("单位移动一证多名不合规.nck", report->unitMobileOneCard);
                            break;
                        case id_unitTelephone:
                        case id_serviceMobile:
                        case id_serviceTelephone:
                        default:
                            break;
                        }
                     }
                     break;
                 }
             }
             ptrMulti = ptrMulti->next;
        }while(ptrMulti != nullptr);
    }

    if(id_TypeChar != id_personMobile && id_TypeChar != id_unitMobile)
        return;
    if(m_pstErrFiveName[sHashTreev] == nullptr) // Error !!!!
        return;
    ptrFive = m_pstErrFiveName[sHashTreev];
    do
    {
        if(0 == strncmp(ptrFive->number,col.at(ownerNumIndex).toStdString().c_str(),strlen(ptrFive->number)))
        {
            if(ptrFive->errflag&errType_oneCardFiveNumber)
                writeFile("一证五号不合规原始.nck", report->onecardFiveNumber);
            break;
        }
        ptrFive = ptrFive->next;
    }while(ptrFive != nullptr);
}

/**
 * @brief makeDir 判断结果文件输出文件夹（工作路径）是否存在，不存在则创建。
 * @return 路径存在，或者创建路径成功。
 */
bool UserDb::makeDir(){
    QString path = xmlConfig->readWorkingpathValue().value("workingpath");
    QDir dir(path);
    if(dir.exists()) return true;
    return dir.mkpath(path);//创建多级目录
}

/**
 * @brief UserDb::writeFile 用于写入结果文件。
 * @param filename 目标文件。
 * @param qstr 欲写入结果文件的行。如果不指定，就是当前正在处理的原始记录行（line）
 */
void UserDb::writeFile(QString filename,  int& count,QString qstr){
    count ++;
    if(count%500==0){
        QList<QString> lineList = fileBuffer.value(filename);
        QFile file(path+QDir::separator()+filename);
        file.open(QFile::Append);
        QTextStream out(&file);
        for(int i=0;i<lineList.size();i++){
            out <<lineList.at(i) << endl;
        }
        file.close();
        fileBuffer.remove(filename);
    }
    QList<QString> list;
    if(fileBuffer.contains(filename))list = fileBuffer.take(filename);

    if(qstr == nullptr)
        list.append(line);
    else
        list.append(qstr);
    fileBuffer.insert(filename, list);
}

void UserDb::flushFile(){
    QMap<QString,QList<QString>>::iterator it; //遍历map
    for (it=fileBuffer.begin(); it != fileBuffer.end(); ++it ) {
       QString filename = it.key();
       QList<QString> lineList = fileBuffer.value(filename);
       QFile file(path+QDir::separator()+filename);
       file.open(QFile::Append);
       QTextStream out(&file);
       for(int i=0;i<lineList.size();i++){
           out <<lineList.at(i) << endl;
       }
       file.close();
    }
    fileBuffer.clear(); //清空map
}

/**
 * @brief UserDb::needAgent
 * @param idCardNum 身份证号
 * @param activeTime 入网激活时间
 * @return 判断经办人必填规则：2018年9月1日后，16周岁，大约120岁，之前是10周岁，大于120岁，就必须有经办人信息。入网时间-证件号码日期>10年
 */
bool UserDb::needAgent(QString typestr,QString idCardNum, QString activeTime){
    unsigned long m18sHashv = strHash(typestr.toStdString().c_str(),strlen(typestr.toStdString().c_str()));
    int m18index;
    for(m18index = 0;m18index < cstrHashm18personType ;m18index ++){
        if(strHashm18personType[m18index].sHashKey == m18sHashv){
            if(0 == strcmp(strHashm18personType[m18index].sHashContent,typestr.toStdString().c_str()) )break;
        }
    }
    //不是18位身份证件，返回 不需要代理人(false)
    if(m18index == cstrHashm18personType)return false;
    //使用18位身份证件，如果不合规，均设定需要代理人
    int plen = strlen(idCardNum.toStdString().c_str());
    if(plen != 18 && plen != 15) return true;
        if(plen == 15 && activeDate >= 20130901)return true;

    //确保从6~8位取出来的内容可以正确转换为时间：按照yyyyMMDD的方式
    for(int i = 0; i < plen - 1; i ++ )
        if(idCardNum.toStdString().at(i)< '0' || idCardNum.toStdString().at(i) > '9') return true;
    if(plen == 15 && (idCardNum.toStdString().at(plen-1)< '0' || idCardNum.toStdString().at(plen-1) > '9'))return true;
    QString midCardNum;
    if(plen == 18)
    {
                char calv = calculateVerifyCode(idCardNum.toStdString().c_str());
                if(calv != 'X')
                {
            if(calv != idCardNum.toStdString().at(17))return true;
                }
                else
                {
                        if(idCardNum.toStdString().at(17) != 'x' && idCardNum.toStdString().at(17) != 'X')return true;
                }
        midCardNum = idCardNum;
    }
    else  //15位
        {
        midCardNum = idCardNum.mid(0,6)+"19"+idCardNum.mid(6,9)+"?";
        }

    //这时检查时间（日期），如果日期混乱，先设定为需要代理人
        const char* pstr = midCardNum.mid(6,8).toStdString().c_str();
        if(pstr[0]!='1'&&pstr[0]!='2')return true;
        if((pstr[0]=='1'&&pstr[1]!='9')||(pstr[0]=='2'&&pstr[1]!='0'))return true;
        if(pstr[4]!='0'&&pstr[4]!='1')return true;

    QDateTime idDate = QDateTime::fromString(midCardNum.trimmed().mid(6,8), "yyyyMMdd");
    QDateTime checkTime = QDateTime::fromString("20180901", "yyyyMMdd");
    QDateTime time = QDateTime::fromString(activeTime.trimmed(), dateFormat);
    QDateTime date1,date2;

    if(time<checkTime)
        date1 = idDate.addYears(10);
    else
        date1 = idDate.addYears(16);

    date2 = idDate.addYears(120);
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

   bool addNotReg = false;
   /* 个人固定用户-证件地址未登记 */
   if(activeDate < 20130901)
    {
         if(isNotReg(col[ownerAddIndex]) && isNotReg(col[ownerAdd1Index]) && isNotReg(col[ownerAdd2Index]))
             addNotReg = true;
   }
   else
   {
       if(isNotReg(col[ownerAddIndex]) && isNotReg(col[ownerAdd2Index]))
           addNotReg = true;
   }

   if(typeNotReg){
       writeFile("个人固话用户-证件类型未登记.nreg",report->personFixedOwnerTypeNotReg);
       report->personFixedNotReg++;
       return;
   }
   if(nameNotReg && !numNotReg && !addNotReg){
       writeFile("个人固话用户-用户姓名未登记.nreg",report->personFixedOwnerNameNotReg);
       report->personFixedNotReg++;
       return;
   }
   if(!nameNotReg && numNotReg && !addNotReg){
       writeFile("个人固话用户-证件号码未登记.nreg",report->personFixedOwnerNameNotReg);
       report->personFixedNotReg++;
       return;
   }
   if(!nameNotReg && !numNotReg && addNotReg){
       writeFile("个人固话用户-证件地址未登记.nreg",report->personFixedOwnerAddNotReg);
       report->personFixedNotReg++;
       return;
   }
   /* 个人固话用户-用户姓名&证件号码未登记 */
   if(nameNotReg && numNotReg && !addNotReg){
       writeFile("个人固话用户-用户姓名&证件号码未登记.nreg",report->personFixedOwnerNameNumNotReg);
       report->personFixedNotReg++;
       return;
   }
   /* 个人固话用户-用户姓名&证件地址未登记 */
   if(nameNotReg && !numNotReg && addNotReg){
       writeFile("个人固话用户-用户姓名&证件地址未登记.nreg",report->personFixedOwnerNameAddNotReg);
       report->personFixedNotReg++;
       return;
   }
   /* 个人固话用户-用户姓名&证件号码未登记 */
   if(!nameNotReg && numNotReg && addNotReg){
       writeFile("个人固话用户-证件号码&证件地址未登记.nreg",report->personFixedOwnerNameAddNotReg);
       report->personFixedNotReg++;
       return;
   }
   /* 个人固话用户-用户姓名&证件号码&证件地址未登记 */
   if(nameNotReg && numNotReg && addNotReg){
       writeFile("个人固话用户-用户姓名&证件号码&证件地址未登记.nreg",report->personFixedOwnerNameNumAddNotReg);
       report->personFixedNotReg++;
       return;
   }

   /* 判断是否需要经办人 */
   bool isNeedAgent = needAgent(col.at(ownerTypeIndex),col.at(ownerNumIndex), col.at(activeTimeIndex));

   if(isNeedAgent)
   {
       /* 个人固定用户-经办人未登记 */
       if(isNotReg(col[agentNameIndex]) || isNotReg(col[agentTypeIndex]) ||
           isNotReg(col[agentNumIndex])){
           writeFile("个人固话用户-经办人信息未登记.nreg",report->personFixedAgentNotReg);
           report->personFixedNotReg++;
           return;
       }

        /* 个人固定用户-经办人信息不合规 */
        bool agentNok = false;
        if(!col.at(ownerNameIndex).compare(col.at(agentNameIndex)))
            {
                    agentNok = true;
            }
        else if(isPersonNameNok(col.at(agentNameIndex))||isPersonTypeNok(col.at(agentTypeIndex))||
                isPersonNumNok(col.at(agentNumIndex),col.at(agentTypeIndex)))
        {
            agentNok = true;
        }
        else if(needAgent(col.at(agentTypeIndex),col.at(agentNumIndex),col.at(activeTimeIndex)))
            {
        //经办人如果不满10岁（2018年9月1日后不满16岁），则判为不合规。
            agentNok = true;
        }
        if( agentNok){
            writeFile("个人固话用户-经办人信息校验不合规.nck",report->personFixedAgentNok);
            report->personFixedNok++;
            return;
        }
    }

   /* 个人固定用户-证件类型不合规 */
   bool typeNok = false;
   if(isPersonTypeNok(col.at(ownerTypeIndex))){
       typeNok = true;
   }

   /* 个人固定用户-用户姓名不合规 */
   bool nameNok = false;
   if(isPersonNameNok(col.at(ownerNameIndex))){
       nameNok = true;
   }

   /* 个人固定用户-证件号码不合规 */
   bool numNok = false;
   if(isPersonNumNok(col.at(ownerNumIndex),col.at(ownerTypeIndex))){
       numNok = true;
   }

   /* 个人固定用户-证件地址不合规 */
   bool addNok = false;
   if(activeDate < 20130901)
   {
   if(isPersonAddNok(col.at(ownerAddIndex)) && isPersonAddNok(col.at(ownerAdd1Index)) && isPersonAddNok(col.at(ownerAdd2Index)))
       addNok = true;
   }
   else
   {
   if(isPersonAddNok(col.at(ownerAddIndex)) && isPersonAddNok(col.at(ownerAdd2Index)))
       addNok = true;
   }

   if(typeNok){
       writeFile("个人固话用户-证件类型校验不合规.nck",report->personFixedOwnerTypeNok);
       report->personFixedNok++;
       return;
   }
   if( nameNok && !numNok && !addNok){
       writeFile("个人固话用户-用户姓名校验不合规.nck",report->personFixedOwnerNameNok);
       report->personFixedNok++;
       return;
   }
   if( !nameNok && numNok && !addNok){
       writeFile("个人固话用户-证件号码校验不合规.nck",report->personFixedOwnerNameNok);
       report->personFixedNok++;
       return;
   }
   if( !nameNok && !numNok && addNok){
       writeFile("个人固话用户-证件地址校验不合规.nck",report->personFixedOwnerAddNok);
       report->personFixedNok++;
       return;
   }

   /* 个人固话用户-用户姓名&证件号码校验不合规 */
   if(!typeNok && nameNok && numNok && !addNok){
       writeFile("个人固话用户-用户姓名&证件号码校验不合规.nck",report->personFixedOwnerNameNumNok);
       report->personFixedNok++;
       return;
   }

   /* 个人固话用户-用户姓名&证件地址校验不合规 */
   if(!typeNok && nameNok && !numNok && addNok){
       writeFile("个人固话用户-用户姓名&证件地址校验不合规.nck",report->personFixedOwnerNameAddNok);
       report->personFixedNok++;
       return;
   }

   /* 个人固话用户-证件号码&证件地址校验不合规 */
   if(!typeNok && !nameNok && numNok && addNok){
       writeFile("个人固话用户-证件号码&证件地址校验不合规.nck",report->personFixedOwnerNumAddNok);
       report->personFixedNok++;
       return;
   }

   /* 个人固话用户-用户姓名&证件号码&证件地址校验不合规 */
   if(!typeNok && nameNok && numNok && addNok){
       writeFile("个人固话用户-用户姓名&证件号码&证件地址校验不合规.nck",report->personFixedOwnerNameNumAddNok);
       report->personFixedNok++;
       return;
   }

   /* 个人固话用户-形式合规数据 */
   if(!typeNotReg && !nameNotReg && !numNotReg && !addNotReg && !typeNok && !nameNok && !numNok && !addNok){
       writeFile("个人固话用户-形式合规数据.ok",report->personFixedOk);
       writeFile("all.ok(全部合规数据)", report->allOk);
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
    if(isNotReg(col[ownerNumIndex]))
        numNotReg = true;
    else
        processOneCardFiveNumber();

    /*个人移动用户-证件地址未登记*/
    bool addNotReg = false;
    if(activeDate < 20130901)
    {
    if(isNotReg(col[ownerAddIndex]) && isNotReg(col[ownerAdd1Index]))
        addNotReg = true;
    }
    else {
        if(isNotReg(col[ownerAddIndex]))
            addNotReg = true;
    }

    if(typeNotReg){
        writeFile("个人移动用户-证件类型未登记.nreg", report->personMobileOwnerTypeNotReg);
        report->personMobileNotReg++;
        return;
    }
    if(nameNotReg && !numNotReg && !addNotReg){
        writeFile("个人移动用户-用户姓名未登记.nreg", report->personMobileOwnerNameNotReg);
        report->personMobileNotReg++;
        return;
    }
    if(!nameNotReg && numNotReg && !addNotReg){
        writeFile("个人移动用户-证件号码未登记.nreg", report->personMobileOwnerNumNotReg);
        report->personMobileNotReg++;
        return;
    }
    if(!nameNotReg && !numNotReg && addNotReg){
        writeFile("个人移动用户-证件地址未登记.nreg", report->personMobileOwnerAddNotReg);
        report->personMobileNotReg++;
        return;
    }

    /* 个人移动用户-用户姓名&证件号码未登记 */
    if(nameNotReg && numNotReg && !addNotReg){
        writeFile("个人移动用户-用户姓名&证件号码未登记.nreg", report->personMobileOwnerNameNumNotReg);
        report->personMobileNotReg++;
        return;
    }
    /* 个人移动用户-用户姓名&证件地址未登记 */
    if(nameNotReg && !numNotReg && addNotReg){
        writeFile("个人移动用户-用户姓名&证件地址未登记.nreg", report->personMobileOwnerNameAddNotReg);
        report->personMobileNotReg++;
        return;
    }
    /* 个人移动用户-证件号码&证件地址未登记 */
    if(!nameNotReg && numNotReg && addNotReg){
        writeFile("个人移动用户-证件号码&证件地址未登记.nreg", report->personMobileOwnerNumAddNotReg);
        report->personMobileNotReg++;
        return;
    }
    /* 个人移动用户-用户姓名&证件号码&证件地址未登记 */
    if(nameNotReg && numNotReg && addNotReg){
        writeFile("个人移动用户-用户姓名&证件号码&证件地址未登记.nreg", report->personMobileOwnerNameNumAddNotReg);
        report->personMobileNotReg++;
        return;
    }

    /* 个人移动用户-证件类型不合规 */
    bool typeNok=false;
    if(isPersonTypeNok(col.at(ownerTypeIndex))){
        typeNok=true;
    }
    if(typeNok){
        writeFile("个人移动用户-证件类型校验不合规.nck", report->personMobileOwnerTypeNok);
        report->personMobileNok++;
        return;
    }

    /* 个人移动用户-用户姓名不合规 */
    bool nameNok=false;
    if(isPersonNameNok(col.at(ownerNameIndex))){
        nameNok=true;
    }

    /* 个人移动用户-证件号码不合规 */
    bool numNok=false;
    if(isPersonNumNok(col.at(ownerNumIndex),col.at(ownerTypeIndex))){
        numNok=true;
    }

     /* 个人移动用户-证件地址不合规 */
    bool addNok=false;
    if(activeDate < 20130901)
    {
    if(isPersonAddNok(col.at(ownerAddIndex)) && isPersonAddNok(col.at(ownerAdd1Index)))
        addNok=true;
    }
    else {
        if(isPersonAddNok(col.at(ownerAddIndex)))
            addNok=true;
    }

    if(nameNok && !numNok && !addNok){
        writeFile("个人移动用户-用户姓名校验不合规.nck",report->personMobileOwnerNameNok);
        report->personMobileNok++;
        return;
    }
    if(!nameNok && numNok && !addNok){
        writeFile("个人移动用户-证件号码校验不合规.nck",report->personMobileOwnerNumNok);
        report->personMobileNok++;
        return;
    }
    if(!nameNok && !numNok && addNok){
        writeFile("个人移动用户-证件地址校验不合规.nck",report->personMobileOwnerAddNok);
        report->personMobileNok++;
        return;
    }

    /* 个人移动用户-用户姓名&证件号码校验不合规 */
    if(nameNok && numNok && !addNok){
        writeFile("个人移动用户-用户姓名&证件号码校验不合规.nck",report->personMobileOwnerNameNumNok);
        report->personMobileNok++;
        return;
    }

    /* 个人移动用户-用户姓名&证件地址校验不合规 */
    if(nameNok && !numNok && addNok){
        writeFile("个人移动用户-用户姓名&证件地址校验不合规.nck",report->personMobileOwnerNameAddNok);
        report->personMobileNok++;
        return;
    }

    /* 个人移动用户-证件号码&证件地址校验不合规 */
    if(!nameNok && numNok && addNok){
        writeFile("个人移动用户-证件号码&证件地址校验不合规.nck",report->personMobileOwnerNumAddNok);
        report->personMobileNok++;
        return;
    }

    /* 个人移动用户-用户姓名&证件号码&证件地址校验不合规 */
    if(nameNok && numNok && addNok){
        writeFile("个人移动用户-证件号码&证件地址校验不合规.nck",report->personMobileOwnerNameNumAddNok);
        report->personMobileNok++;
        return;
    }

    /* 判断是否需要经办人 */
    bool isNeedAgent = needAgent(col.at(ownerTypeIndex),col.at(ownerNumIndex), col.at(activeTimeIndex));

    if(isNeedAgent)
        {
       /*个人移动用户-经办人信息未登记*/
       if(isNotReg(col[agentNameIndex])||isNotReg(col[agentTypeIndex])||
           isNotReg(col[agentNumIndex]) || isNotReg(col[agentAddIndex])){
           writeFile("个人移动用户-经办人信息未登记.nreg",report->personMobileAgentNotReg);
           report->personMobileNotReg++;
           return;
           }
       /* 个人移动用户-经办人信息不合规 */
       bool agentNok = false;
       if(isPersonNameNok(col.at(agentNameIndex))||isPersonTypeNok(col.at(agentTypeIndex))||
               isPersonNumNok(col.at(agentNumIndex),col.at(agentTypeIndex))||
               isPersonAddNok(col.at(agentAddIndex))|| !col.at(ownerNameIndex).compare(col.at(agentNameIndex))){
           agentNok = true;
       }
       else if(needAgent(col.at(agentTypeIndex),col.at(agentNumIndex),col.at(activeTimeIndex)))
       {
       //经办人如果不满10岁（2018年9月1日后不满16岁），则判为不合规。
             agentNok = true;
       }
       if(agentNok){
           writeFile("个人移动用户-经办人信息校验不合规.nck",report->personMobileAgentNok);
           report->personMobileNok++;
           return;
       }
        }
    /* 个人移动用户-形式合规数据 */
    if(!typeNotReg && !nameNotReg && !numNotReg && !typeNok && !nameNok && !numNok && !addNok){
        writeFile("个人移动用户-形式合规数据.ok", report->personMobileOk);
        writeFile("all.ok(全部合规数据)", report->allOk);
        processOneCardMultiName();
        return;
    }
}

/**
 * @brief processUnitFixed 处理单位固话信息
 * @param
 *
 */
void UserDb::processUnitFixed(){
    /* 单位固话用户-经办人信息未登记 */
    bool agentNotReg = false;
    if(isNotReg(col[agentNameIndex]) || isNotReg(col[agentTypeIndex]) || isNotReg(col[agentNumIndex])
            || isNotReg(col[agentAddIndex]) ){
        agentNotReg = true;
    }

    /* 单位固话用户-单位信息未登记 */
    bool unitNotReg = false;
    if(activeDate < 20130901)
    {
    if(isNotReg(col[unitNameIndex])||isNotReg(col[unitNumIndex])||isNotReg(col[unitTypeIndex])||
            (isNotReg(col[unitAddIndex]) && isNotReg(col[unitAdd1Index]) && isNotReg(col[unitAdd2Index])))
        unitNotReg = true;
    }
    else
    {
    if(isNotReg(col[unitNameIndex])||isNotReg(col[unitNumIndex])||isNotReg(col[unitTypeIndex])||
            (isNotReg(col[unitAddIndex]) && isNotReg(col[unitAdd2Index])))
        unitNotReg = true;
    }

    /* 单位固话用户-经办人信息不合规 */
     bool agentNok = false;
    if(isPersonNameNok(col.at(agentNameIndex))||isPersonTypeNok(col.at(agentTypeIndex))||
            isPersonNumNok(col.at(agentNumIndex),col.at(agentTypeIndex)) || isPersonAddNok(col.at(agentAddIndex))){
        agentNok=true;
    }

    /* 单位固话用户-单位信息不合规 */
    bool unitNok = false;
    if(activeDate < 20130901)
    {
    if(isUnitNameNok(col.at(unitNameIndex))||isUnitNumNok(col.at(unitNumIndex))||isUnitTypeNok(col.at(unitTypeIndex))||
            (isUnitAddNok(col.at(unitAddIndex))&&isUnitAddNok(col.at(unitAdd1Index))&&isUnitAddNok(col.at(unitAdd2Index))))
        unitNok=true;
    }
    else {
        if(isUnitNameNok(col.at(unitNameIndex))||isUnitNumNok(col.at(unitNumIndex))||isUnitTypeNok(col.at(unitTypeIndex))||
                (isUnitAddNok(col.at(unitAddIndex))&&isUnitAddNok(col.at(unitAdd2Index))))
            unitNok=true;

    }

    /* 2013年9月1日之前入网的单位固话用户需检查经办人或单位信息中任一个条目，该条目需包含姓名/单位名称、证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。*/
    if(activeDate < 20130901) {
        if( (!agentNotReg && !agentNok) || (!unitNotReg && !unitNok))  {
            writeFile("单位固话用户-形式合规数据.ok",report->unitFixedOk);
            writeFile("all.ok(全部合规数据)", report->allOk);
            return;
        }
        else{
            if(agentNotReg && unitNotReg){
                writeFile("单位固话用户-经办人&单位信息未登记.nreg",report->unitFixedAgentUnitNotReg);
                report->unitFixedNotReg++;
                return;
            }
            if(agentNotReg && unitNok){
                writeFile("单位固话用户-单位信息校验不合规.nck",report->unitFixedUnitNok);
                report->unitFixedNok++;
                return;
            }
            if(agentNok && unitNotReg){
                writeFile("单位固话用户-经办人信息校验不合规.nreg",report->unitFixedAgentNok);
                report->unitFixedNok++;
                return;
            }
            if(agentNok && unitNok){
                writeFile("单位固话用户-经办人&单位信息校验不合规.nck",report->unitFixedAgentUnitNok);
                report->unitFixedNok++;
                return;
            }
        }
    }
    else {
        /* 2013年9月1日之后入网的单位固话用户需检查经办人和单位信息共2个条目，各条目均需包含姓名/单位名称、证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。*/
        if(!agentNotReg && !agentNok && !unitNotReg && !unitNok)
                {
            writeFile("单位固话用户-形式合规数据.ok",report->unitFixedOk);
            writeFile("all.ok(全部合规数据)", report->allOk);
            return;
                }
                if(agentNotReg && !unitNotReg){
            writeFile("单位固话用户-经办人信息未登记.nreg",report->unitFixedAgentNotReg);
            report->unitFixedNotReg++;
            return;
        }
        if(!agentNotReg && unitNotReg){
            writeFile("单位固话用户-单位信息未登记.nreg",report->unitFixedUnitNotReg);
            report->unitFixedNotReg++;
            return;
        }
        if(agentNotReg && unitNotReg){
            writeFile("单位固话用户-经办人&单位信息未登记.nreg",report->unitFixedAgentUnitNotReg);
            report->unitFixedNotReg++;
            return;
        }
        if(agentNok && !unitNok){
            writeFile("单位固话用户-经办人信息校验不合规.nck",report->unitFixedAgentNok);
            report->unitFixedNok++;
            return;
        }
        if(!agentNok && unitNok){
            writeFile("单位固话用户-单位信息校验不合规.nck",report->unitFixedUnitNok);
            report->unitFixedNok++;
            return;
        }
        if(agentNok && unitNok){
            writeFile("单位固话用户-经办人&单位信息校验不合规.nck",report->unitFixedAgentUnitNok);
            report->unitFixedNok++;
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
    if(activeDate < 20130901)
    {
    if(isNotReg(col[ownerNameIndex]) || isNotReg(col[ownerNumIndex]) || isNotReg(col[ownerTypeIndex])
            || (isNotReg(col[ownerAddIndex]) && isNotReg(col[ownerAdd1Index])))
        ownerNotReg = true;
    }
    else
    {
        if(isNotReg(col[ownerNameIndex]) || isNotReg(col[ownerNumIndex]) || isNotReg(col[ownerTypeIndex])
                || isNotReg(col[ownerAddIndex]))
            ownerNotReg = true;
    }
    if(!isNotReg(col[ownerNumIndex]))processOneCardFiveNumber();

    /* 单位移动用户-经办人信息未登记 */
    bool agentNotReg = false;
    if(isNotReg(col[agentNameIndex])||isNotReg(col[agentTypeIndex])||
            isNotReg(col[agentNumIndex]) || isNotReg(col[agentAddIndex])){
        agentNotReg = true;
    }

    /* 单位移动用户-单位信息未登记 */
    bool unitNotReg = false;
    if(activeDate < 20130901)
    {
    if(isNotReg(col[unitNameIndex])||isNotReg(col[unitNumIndex])||isNotReg(col[unitTypeIndex])||
            (isNotReg(col[unitAddIndex]) && isNotReg(col[unitAdd1Index])))
        unitNotReg = true;
    }
    else {
        if(isNotReg(col[unitNameIndex])||isNotReg(col[unitNumIndex])||isNotReg(col[unitTypeIndex])||
                isNotReg(col[unitAddIndex]))
            unitNotReg = true;
    }

    /* 单位移动用户-使用人信息不合规 */
    bool ownerNok = false;
    if(activeDate < 20130901)
    {
    if(isPersonNameNok(col.at(ownerNameIndex))||isPersonNumNok(col.at(ownerNumIndex),col.at(ownerTypeIndex))||
            isPersonTypeNok(col.at(ownerTypeIndex))||(isPersonAddNok(col.at(ownerAddIndex)) && isPersonAddNok(col.at(ownerAdd1Index))))
        ownerNok = true;
    }
    else
    {
    if(isPersonNameNok(col.at(ownerNameIndex))||isPersonNumNok(col.at(ownerNumIndex),col.at(ownerTypeIndex))||
            isPersonTypeNok(col.at(ownerTypeIndex))||isPersonAddNok(col.at(ownerAddIndex)))
        ownerNok = true;
    }

    /* 单位移动用户-经办人信息不合规 */
    bool agentNok = false;
    if(isPersonNameNok(col.at(agentNameIndex))||isPersonTypeNok(col.at(agentTypeIndex))||
            isPersonNumNok(col.at(agentNumIndex),col.at(agentTypeIndex))){
        agentNok = true;
    }
// 单位移动用户，使用人和经办人为同一个人，不能判为不合规 20190311
//    if(!col.at(ownerNameIndex).compare(col.at(agentNameIndex))){
//        agentNok = true;
//    }

    /* 单位移动用户-单位信息不合规 */
    bool unitNok = false;
    if(activeDate < 20130901)
    {
        if(isUnitNameNok(col.at(unitNameIndex)) || isUnitNumNok(col.at(unitNumIndex))
                || isUnitTypeNok(col.at(unitTypeIndex))
                ||(isUnitAddNok(col.at(unitAddIndex)) && isUnitAddNok(col.at(unitAdd1Index))))
        unitNok = true;
    }
    else
    {
        if(isUnitNameNok(col.at(unitNameIndex))||isUnitNumNok(col.at(unitNumIndex))||isUnitTypeNok(col.at(unitTypeIndex))||
                isUnitAddNok(col.at(unitAddIndex)))
            unitNok = true;
    }

    /* 2013年9月1日之前入网的单位移动用户，需检查实际使用人、经办人和单位信息中的任1个条目，该条目中需包含姓名/单位名称、证件类型、证件号码、地址四个字段，
     * 并符合完整性和真实性要求。 */
    if(activeDate < 20130901){
        if( (!ownerNotReg && !ownerNok) || (!agentNotReg && !agentNok) || (!unitNotReg&&!unitNok)){
            writeFile("单位移动用户-形式合规数据.ok",report->unitMobileOk);
            writeFile("all.ok(全部合规数据)", report->allOk);
                        if(!ownerNotReg && !ownerNok)processOneCardMultiName();
            return;
        }
        else{
            if(ownerNotReg && agentNotReg && unitNotReg){
                writeFile("单位移动用户-使用人&经办人&单位信息未登记.nreg",report->unitMobileOwnerAgentUnitNotReg);
                report->unitMobileNotReg++;
                return;
            }
            if(ownerNok && agentNotReg && unitNotReg){
                writeFile("单位移动用户-使用人信息校验不合规.nck",report->unitMobileOwnerNok);
                report->unitMobileNok++;
                return;
            }
            if(ownerNotReg && agentNok && unitNotReg){
                writeFile("单位移动用户-经办人信息校验不合规.nck",report->unitMobileAgentNok);
                report->unitMobileNok++;
                return;
            }
            if(ownerNotReg && agentNotReg && unitNok){
                writeFile("单位移动用户-单位信息校验不合规.nck",report->unitMobileUnitNok);
                report->unitMobileNok++;
                return;
            }
            if(ownerNok && agentNok && unitNotReg){
                writeFile("单位移动用户-使用人&经办人信息校验不合规.nck",report->unitMobileOwnerAgentNok);
                report->unitMobileNok++;
                return;
            }
            if(ownerNok && agentNotReg && unitNok){
                writeFile("单位移动用户-使用人&单位信息校验不合规.nck",report->unitMobileOwnerUnitNok);
                report->unitMobileNok++;
                return;
            }
            if(ownerNotReg && agentNok && unitNok){
                writeFile("单位移动用户-经办人&单位信息校验不合规.nck",report->unitMobileAgentUnitNok);
                report->unitMobileNok++;
                return;
            }
            if(ownerNok && agentNok && unitNok){
                writeFile("单位移动用户-使用人&经办人&单位信息校验不合规.nck",report->unitMobileOwnerAgentUnitNok);
                report->unitMobileNok++;
                return;
            }
        }
    }
    else if(activeDate >= 20130901 && activeDate < 20150101){
        /* 2013年9月1日之后，2015年1月1日之前入网的单位移动用户，需检查实际使用人或经办人、单位信息共2个条目，各条目中均需包含姓名/单位名称、
         * 证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。*/
        //2013年9月1日至2015年1月1日 入网的  凡是单位信息未登记 均显示单位信息未登记；凡是单位信息不合规的 均显示单位信息不合规即可 因为另外两条一条合规即可，单位信息是必须合规的
        if( (!ownerNotReg && !unitNotReg && !ownerNok && !unitNok) ||
                (!agentNotReg && !unitNotReg && !agentNok && !unitNok) ){
            writeFile("单位移动用户-形式合规数据.ok",report->unitMobileOk);
            writeFile("all.ok(全部合规数据)", report->allOk);
            if(!ownerNotReg && !ownerNok)processOneCardMultiName();
            return;
        }
        else{
            if(unitNotReg){
                writeFile("单位移动用户-单位信息未登记.nreg",report->unitMobileUnitNotReg);
                report->unitMobileNotReg++;
                return;
            }
            if(unitNok){
                writeFile("单位移动用户-单位信息校验不合规.nck",report->unitMobileUnitNok);
                report->unitMobileNok++;
                return;
            }
            if(ownerNotReg && agentNotReg && !unitNok){
                writeFile("单位移动用户-使用人&经办人信息未登记.nreg",report->unitMobileOwnerAgentNotReg);
                report->unitMobileNotReg++;
                return;
            }
            if(ownerNok && agentNotReg && !unitNok){
                writeFile("单位移动用户-使用人信息校验不合规.nck",report->unitMobileOwnerNok);
                report->unitMobileNok++;
                return;
            }
            if(ownerNotReg && agentNok && !unitNok){
                writeFile("单位移动用户-经办人信息校验不合规.nck",report->unitMobileAgentNok);
                report->unitMobileNok++;
                return;
            }
            if(ownerNok && agentNok && !unitNok){
                writeFile("单位移动用户-使用人&经办人信息校验不合规.nck",report->unitMobileOwnerAgentNok);
                report->unitMobileNok++;
                return;
            }
        }
    }
    else{
        /* 2015年1月1日之后入网的单位移动用户，需检查实际使用人、经办人、单位信息共3个条目，各条目中均需包含姓名/单位名称、证件类型、证件号码、
         * 地址四个字段，并符合完整性和真实性要求。 */
        if(!ownerNotReg && !agentNotReg && !unitNotReg && !ownerNok && !agentNok && !unitNok){
            writeFile("单位移动用户-形式合规数据.ok",report->unitMobileOk);
            writeFile("all.ok(全部合规数据)", report->allOk);
            processOneCardMultiName();
            return;
        }
        if(ownerNotReg && !agentNotReg && !unitNotReg ){
            writeFile("单位移动用户-使用人信息未登记.nreg",report->unitMobileOwnerNotReg);
            report->unitMobileNotReg++;
            return;
        }
        if(!ownerNotReg && agentNotReg && !unitNotReg ){
            writeFile("单位移动用户-经办人信息未登记.nreg",report->unitMobileAgentNotReg);
            report->unitMobileNotReg++;
            return;
        }
        if(!ownerNotReg && !agentNotReg && unitNotReg ){
            writeFile("单位移动用户-单位信息未登记.nreg",report->unitMobileUnitNotReg);
            report->unitMobileNotReg++;
            return;
        }
        if(ownerNotReg && agentNotReg && !unitNotReg){
            writeFile("单位移动用户-使用人&经办人信息未登记.nreg",report->unitMobileOwnerAgentNotReg);
            report->unitMobileNotReg++;
            return;
        }
        if(ownerNotReg && !agentNotReg && unitNotReg){
            writeFile("单位移动用户-使用人&单位信息未登记.nreg",report->unitMobileOwnerUnitNotReg);
            report->unitMobileNotReg++;
            return;
        }
        if(!ownerNotReg && agentNotReg && unitNotReg){
            writeFile("单位移动用户-经办人&单位信息未登记.nreg",report->unitMobileAgentUnitNotReg);
            report->unitMobileNotReg++;
            return;
        }
        if(ownerNotReg && agentNotReg && unitNotReg){
            writeFile("单位移动用户-使用人&经办人&单位信息未登记.nreg",report->unitMobileOwnerAgentUnitNotReg);
            report->unitMobileNotReg++;
            return;
        }
        if(ownerNok && !agentNok && !unitNok){
            writeFile("单位移动用户-使用人信息校验不合规.nck",report->unitMobileOwnerNok);
            report->unitMobileNok++;
            return;
        }
        if(!ownerNok && agentNok && !unitNok ){
            writeFile("单位移动用户-经办人信息校验不合规.nck",report->unitMobileAgentNok);
            report->unitMobileNok++;
            return;
        }
        if(!ownerNok && !agentNok && unitNok ){
            writeFile("单位移动用户-单位信息校验不合规.nck",report->unitMobileUnitNok);
            report->unitMobileNok++;
            return;
        }
        if(ownerNok && agentNok && !unitNok){
            writeFile("单位移动用户-使用人&经办人信息校验不合规.nck",report->unitMobileOwnerAgentNok);
            report->unitMobileNok++;
            return;
        }
        if(ownerNok && agentNok && !unitNok){
            writeFile("单位移动用户-使用人&单位信息校验不合规.nck",report->unitMobileOwnerUnitNok);
            report->unitMobileNok++;
            return;
        }
        if(!ownerNok && agentNok && unitNok){
            writeFile("单位移动用户-经办人&单位信息校验不合规.nck",report->unitMobileAgentUnitNok);
            report->unitMobileNok++;
            return;
        }
        if(ownerNok && agentNok && unitNok){
            writeFile("单位移动用户-使用人&经办人&单位信息校验不合规.nck",report->unitMobileOwnerAgentUnitNok);
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
    /* 行业移动应用-使用人信息未登记 */
    bool ownerNotReg = false;
    if(activeDate < 20130901)
    {
    if(isNotReg(col[ownerNameIndex]) || isNotReg(col[ownerNumIndex]) || isNotReg(col[ownerTypeIndex])
            || (isNotReg(col[ownerAddIndex])&&isNotReg(col[ownerAdd1Index])))
        ownerNotReg = true;
    }
    else {
        if(isNotReg(col[ownerNameIndex]) || isNotReg(col[ownerNumIndex]) || isNotReg(col[ownerAddIndex])
                || isNotReg(col[ownerTypeIndex]))
            ownerNotReg = true;
    }

    /* 行业移动应用-经办人未登记 */
    bool agentNotReg = false;
    if(isNotReg(col[agentNameIndex])||isNotReg(col[agentTypeIndex])||
            isNotReg(col[agentNumIndex])){
        agentNotReg = true;
    }

    /* 行业移动应用-单位信息未登记 */
    bool unitNotReg = false;
    if(activeDate < 20130901)
    {
    if(isNotReg(col[unitNameIndex])||isNotReg(col[unitNumIndex])||isNotReg(col[unitTypeIndex])||
            (isNotReg(col[unitAddIndex]) && isNotReg(col[unitAdd1Index])))
        unitNotReg = true;
    }
    else
    {
        if(isNotReg(col[unitNameIndex])||isNotReg(col[unitNumIndex])||isNotReg(col[unitTypeIndex])||
                isNotReg(col[unitAddIndex]))
            unitNotReg = true;
    }

    /* 行业移动应用-责任人信息未登记 */
    bool liableNotReg = false;
    if(isNotReg(col[liableNameIndex])||isNotReg(col[liableTypeIndex])||isNotReg(col[liableNumIndex])||
            isNotReg(col[liableAddIndex])){
        liableNotReg = true;
    }

    /* 行业移动应用-使用人信息不合规 */
    bool ownerNok = false;
    if(activeDate < 20130901)
    {
    if(isPersonNameNok(col.at(ownerNameIndex))||isPersonNumNok(col.at(ownerNumIndex),col.at(ownerTypeIndex))||isPersonTypeNok(col.at(ownerTypeIndex))||
            (isPersonAddNok(col.at(ownerAddIndex))&&isPersonAddNok(col.at(ownerAdd1Index))))
        ownerNok = true;
    }
    else {
        if(isPersonNameNok(col.at(ownerNameIndex))||isPersonNumNok(col.at(ownerNumIndex),col.at(ownerTypeIndex))||isPersonTypeNok(col.at(ownerTypeIndex))||
                isPersonAddNok(col.at(ownerAddIndex)))
            ownerNok = true;
    }

    /* 行业移动应用-经办人不合规 */
    bool agentNok = false;
    if(isPersonNameNok(col.at(agentNameIndex))||isPersonTypeNok(col.at(agentTypeIndex))||
            isPersonNumNok(col.at(agentNumIndex),col.at(agentTypeIndex))){
        agentNok = true;
    }
    if(!col.at(ownerNameIndex).compare(col.at(agentNameIndex))){
        agentNok = true;
    }

    /* 行业移动应用-单位信息不合规 */
    bool unitNok = false;
    if(activeDate < 20130901)
    {
    if(isUnitNameNok(col.at(unitNameIndex))||isUnitNumNok(col.at(unitNumIndex))||isUnitTypeNok(col.at(unitTypeIndex))||
            (isUnitAddNok(col.at(unitAddIndex))&&isUnitAddNok(col.at(unitAdd1Index))))
        unitNok=true;
    }
    else {
        if(isUnitNameNok(col.at(unitNameIndex))||isUnitNumNok(col.at(unitNumIndex))||isUnitTypeNok(col.at(unitTypeIndex))||
                isUnitAddNok(col.at(unitAddIndex)))
            unitNok=true;
    }

    /* 行业移动应用-责任人信息不合规 */
    bool liableNok = false;
    if(isPersonNameNok(col.at(liableNameIndex))||isPersonTypeNok(col.at(liableTypeIndex))||isPersonNumNok(col.at(liableNumIndex),col.at(liableTypeIndex))||
            isPersonAddNok(col.at(liableAddIndex))){

        liableNok=true;
    }
    /* 如果实际使用人合规，则不需要判断其他字段 */
    if(!(ownerNotReg || ownerNok))
    {
        writeFile("行业移动应用-形式合规数据.ok",report->tradeMobileOk);
        writeFile("all.ok(全部合规数据)", report->allOk);
        return;
    }
    else
    {
        /* 2013年9月1日之前入网的行业移动应用，需检查责任人、(实际使用人)、经办人和单位信息中任一个条目，该条目中均需包含姓名/单位名称、证件类型、证件号码、地址，
         * 符合完整性和真实性要求。 */
        if(activeDate < 20130901){
            if((!agentNotReg && !agentNok) || (!unitNotReg && !unitNok) || (!liableNotReg && !liableNok)){
                writeFile("行业移动应用-形式合规数据.ok",report->tradeMobileOk);
                writeFile("all.ok(全部合规数据)", report->allOk);
                return;
            }
            else {
                if(liableNotReg && agentNotReg && unitNotReg){
                    writeFile("行业移动应用-责任人&经办人&单位信息未登记.nreg",report->tradeMobileLiableAgentUnitNotReg);
                    report->tradeMobileNotReg++;
                    return;
                }
                if(liableNok && agentNotReg && unitNotReg){
                    writeFile("行业移动应用-责任人信息校验不合规.nck",report->tradeMobileLiableNok);
                    report->tradeMobileNok++;
                    return;
                }
                if(liableNotReg && agentNok && unitNotReg){
                    writeFile("行业移动应用-经办人信息校验不合规.nck",report->tradeMobileAgentNok);
                    report->tradeMobileNok++;
                    return;
                }
                if(liableNotReg && agentNotReg && unitNok){
                    writeFile("行业移动应用-单位信息校验不合规.nck",report->tradeMobileUnitNok);
                    report->tradeMobileNok++;
                    return;
                }
                if(liableNok && agentNok && unitNotReg){
                    writeFile("行业移动应用-责任人&经办人信息校验不合规.nck",report->tradeMobileLiableAgentNok);
                    report->tradeMobileNok++;
                    return;
                }
                if(liableNok && agentNotReg && unitNok){
                    writeFile("行业移动应用-责任人&单位信息校验不合规.nck",report->tradeMobileLiableUnitNok);
                    report->tradeMobileNok++;
                    return;
                }
                if(liableNotReg && agentNok && unitNok){
                    writeFile("行业移动应用-经办人&单位信息校验不合规.nck",report->tradeMobileAgentUnitNok);
                    report->tradeMobileNok++;
                    return;
                }
                if(liableNok && agentNok && unitNok){
                    writeFile("行业移动应用-责任人&经办人&单位信息校验不合规.nck",report->tradeMobileLiableAgentUnitNok);
                    report->tradeMobileNok++;
                    return;
                }
            }
        }
        else if(activeDate >= 20130901 && activeDate < 20150101){
            /* 2013年9月1日之后，2015年1月1日之前入网的行业移动应用，需检查责任人(实际使用人就ok)或经办人、单位信息共2个条目，各条目中均需包含姓名/单位名称、
             * 证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。*/
            //2013年9月1日至2015年1月1日 入网的  凡是单位信息未登记 均显示单位信息未登记；凡是单位信息不合规的 均显示单位信息不合规即可 因为另外两条一条合规即可，单位信息是必须合规的
            if( (!liableNotReg && !unitNotReg && !liableNok && !unitNok) ||
                (!agentNotReg && !unitNotReg && !agentNok && !unitNok) ){
                writeFile("行业移动应用-形式合规数据.ok",report->tradeMobileOk);
                writeFile("all.ok(全部合规数据)", report->allOk);
                return;
            }
                    else
                    {
                if(unitNotReg){
                    writeFile("行业移动应用-单位信息未登记.nreg",report->tradeMobileUnitNotReg);
                    report->tradeMobileNotReg++;
                    return;
                }
                if(unitNok){
                    writeFile("行业移动应用-单位信息校验不合规.nck",report->tradeMobileUnitNok);
                    report->tradeMobileNok++;
                    return;
                }
                if(liableNotReg && agentNotReg && !unitNok){
                    writeFile("行业移动应用-责任人&经办人信息未登记.nreg",report->tradeMobileLiableAgentNotReg);
                    report->tradeMobileNotReg++;
                    return;
                }
                if(liableNok && agentNotReg && !unitNok){
                    writeFile("行业移动应用-责任人信息校验不合规.nck",report->tradeMobileLiableNok);
                    report->tradeMobileNok++;
                    return;
                }
                if(liableNotReg && agentNok && !unitNok){
                    writeFile("行业移动应用-经办人信息校验不合规.nck",report->tradeMobileAgentNok);
                    report->tradeMobileNok++;
                    return;
                }
                if(liableNok && agentNok && !unitNok){
                    writeFile("行业移动应用-责任人&经办人信息校验不合规.nck",report->tradeMobileLiableAgentNok);
                    report->tradeMobileNok++;
                    return;
                }
            }
        }
        else{
            /* 2015年1月1日之后入网的行业移动应用，需检查责任人(实际使用人，优先)、经办人、单位信息共3个条目，各条目中均需包含姓名/单位名称、证件类型、
             * 证件号码、地址四个字段，并符合完整性和真实性要求。 */
            if(!liableNotReg && !agentNotReg && !unitNotReg && !liableNok && !agentNok && !unitNok)
                        {
                writeFile("行业移动应用-形式合规数据.ok",report->tradeMobileOk);
                writeFile("all.ok(全部合规数据)", report->allOk);
                return;
            }
            if(agentNotReg && !unitNotReg && !liableNotReg){
                writeFile("行业移动应用-经办人信息未登记.nreg",report->tradeMobileAgentNotReg);
                report->tradeMobileNotReg++;
                return;
            }
            if(!agentNotReg && unitNotReg && !liableNotReg){
                writeFile("行业移动应用-单位信息未登记.nreg",report->tradeMobileUnitNotReg);
                report->tradeMobileNotReg++;
                return;
            }
            if(!agentNotReg && !unitNotReg && liableNotReg){
                writeFile("行业移动应用-责任人信息未登记.nreg",report->tradeMobileLiableNotReg);
                report->tradeMobileNotReg++;
                return;
            }
            if(agentNotReg && unitNotReg && !liableNotReg){
                writeFile("行业移动应用-经办人&单位信息未登记.nreg",report->tradeMobileAgentUnitNotReg);
                report->tradeMobileNotReg++;
                return;
            }
            if(!agentNotReg && unitNotReg && liableNotReg){
                writeFile("行业移动应用-责任人&单位信息未登记.nreg",report->tradeMobileLiableUnitNotReg);
                report->tradeMobileNotReg++;
                return;
            }
            if(agentNotReg && !unitNotReg && liableNotReg){
                writeFile("行业移动应用-责任人&经办人信息未登记.nreg",report->tradeMobileLiableAgentNotReg);
                return;
            }
            if(agentNotReg && unitNotReg && liableNotReg){
                writeFile("行业移动应用-责任人&经办人&单位信息未登记.nreg",report->tradeMobileLiableAgentUnitNotReg);
                report->tradeMobileNotReg++;
                return;
            }
            if(agentNok && !unitNok && !liableNok){
                writeFile("行业移动应用-经办人信息校验不合规.nck",report->tradeMobileAgentNok);
                report->tradeMobileNok++;
                return;
            }
            if(!agentNok && unitNok && !liableNok){
                writeFile("行业移动应用-单位信息校验不合规.nck",report->tradeMobileUnitNok);
                report->tradeMobileNok++;
                return;
            }
            if(!agentNok && !unitNok && liableNok){
                writeFile("行业移动应用-责任人信息校验不合规.nck",report->tradeMobileLiableNok);
                report->tradeMobileNok++;
                return;
            }
            if(agentNok && unitNok && !liableNok){
                writeFile("行业移动应用-经办人&单位信息校验不合规.nck",report->tradeMobileAgentUnitNok);
                report->tradeMobileNok++;
                return;
            }
            if(!agentNok && unitNok && liableNok){
                writeFile("行业移动应用-责任人&单位信息校验不合规.nck",report->tradeMobileLiableUnitNok);
                report->tradeMobileNok++;
                return;
            }
            if(agentNok && !unitNok && liableNok){
                writeFile("行业移动应用-责任人&经办人信息校验不合规.nck",report->tradeMobileLiableAgentNok);
                report->tradeMobileNok++;
                return;
            }
            if(agentNok && unitNok && liableNok){
                writeFile("行业移动应用-责任人&经办人&单位信息校验不合规.nck",report->tradeMobileLiableAgentUnitNok);
                report->tradeMobileNok++;
                return;
            }
        }
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
    if(activeDate < 20130901)
    {
    if(isNotReg(col[ownerNameIndex]) || isNotReg(col[ownerNumIndex]) || isNotReg(col[ownerTypeIndex])
            || (isNotReg(col[ownerAddIndex])&&isNotReg(col[ownerAdd1Index])&&isNotReg(col[ownerAdd2Index])))
        ownerNotReg = true;
    }
    else {
        if(isNotReg(col[ownerNameIndex]) || isNotReg(col[ownerNumIndex]) || isNotReg(col[ownerTypeIndex])
                || (isNotReg(col[ownerAddIndex])&&isNotReg(col[ownerAdd2Index])))
            ownerNotReg = true;
    }

    /* 行业固话用户-经办人未登记 */
    bool agentNotReg = false;
    if(isNotReg(col[agentNameIndex])||isNotReg(col[agentTypeIndex])||
            isNotReg(col[agentNumIndex])){
        agentNotReg = true;
    }

    /* 行业固话用户-单位信息未登记 */
    bool unitNotReg = false;
    if(activeDate < 20130901)
    {
    if(isNotReg(col[unitNameIndex])||isNotReg(col[unitNumIndex])||isNotReg(col[unitTypeIndex])||
            (isNotReg(col[unitAddIndex])&&isNotReg(col[unitAdd1Index])&&isNotReg(col[unitAdd2Index])))
        unitNotReg = true;
    }
    else
    {
    if(isNotReg(col[unitNameIndex])||isNotReg(col[unitNumIndex])||isNotReg(col[unitTypeIndex])||
            (isNotReg(col[unitAddIndex])&&isNotReg(col[unitAdd2Index])))
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
    if(activeDate < 20130901)
    {
    if(isPersonNameNok(col.at(ownerNameIndex))||isPersonNumNok(col.at(ownerNumIndex),col.at(ownerTypeIndex))
            ||(isPersonAddNok(col.at(ownerAddIndex)) && isPersonAddNok(col.at(ownerAdd1Index)) && isPersonAddNok(col.at(ownerAdd2Index)))
            ||isPersonTypeNok(col.at(ownerTypeIndex)))
        ownerNok = true;
    }
    else
    {
    if(isPersonNameNok(col.at(ownerNameIndex))||isPersonNumNok(col.at(ownerNumIndex),col.at(ownerTypeIndex))
            ||(isPersonAddNok(col.at(ownerAddIndex)) && isPersonAddNok(col.at(ownerAdd2Index)))
            ||isPersonTypeNok(col.at(ownerTypeIndex)))
        ownerNok = true;
    }

    /* 行业固话用户-经办人不合规 */
    bool agentNok = false;
    if(isPersonNameNok(col.at(agentNameIndex))||isPersonTypeNok(col.at(agentTypeIndex))||
            isPersonNumNok(col.at(agentNumIndex),col.at(agentTypeIndex))){
        agentNok = true;
    }
    if(!col.at(ownerNameIndex).compare(col.at(agentNameIndex))){
        agentNok = true;
    }

    /* 行业固话用户-单位信息不合规 */
    bool unitNok = false;
    if(activeDate < 20130901){
    if(isUnitNameNok(col.at(unitNameIndex))||isUnitNumNok(col.at(unitNumIndex))||isUnitTypeNok(col.at(unitTypeIndex))||
            (isUnitAddNok(col.at(unitAddIndex)) && isUnitAddNok(col.at(unitAdd1Index)) && isUnitAddNok(col.at(unitAdd2Index))))
        unitNok=true;
    }
    else{
        if(isUnitNameNok(col.at(unitNameIndex))||isUnitNumNok(col.at(unitNumIndex))||isUnitTypeNok(col.at(unitTypeIndex))||
                (isUnitAddNok(col.at(unitAddIndex)) && isUnitAddNok(col.at(unitAdd2Index))))
            unitNok=true;
    }

    /* 行业固话用户-责任人信息不合规 */
    bool liableNok = false;
    if(isPersonNameNok(col.at(liableNameIndex))||isPersonTypeNok(col.at(liableTypeIndex))||isPersonNumNok(col.at(liableNumIndex),col.at(liableTypeIndex))||
            isPersonAddNok(col.at(liableAddIndex))){
        liableNok=true;
    }

    /* 如果实际使用人合规，则不需要判断其他字段 */
    if(!( ownerNotReg || ownerNok)){
        writeFile("行业固话应用-形式合规数据.ok",report->tradeFixedOk);
        writeFile("all.ok(全部合规数据)", report->allOk);
        return;
    }
    else {
        /* 2013年9月1日之前入网的行业固话用户，需检查责任人、(实际使用人)、经办人和单位信息中任一个条目，该条目中均需包含姓名/单位名称、证件类型、证件号码、地址，
         * 符合完整性和真实性要求。 */
        if(activeDate < 20130901){
            if((!agentNotReg && !agentNok) || (!unitNotReg && !unitNok) || (!liableNotReg && !liableNok)){
                writeFile("行业固话应用-形式合规数据.ok",report->tradeFixedOk);
                writeFile("all.ok(全部合规数据)", report->allOk);
                return;
            }
            else {
                if(liableNotReg && agentNotReg && unitNotReg){
                    writeFile("行业固话应用-经办人&责任人&单位信息未登记.nreg",report->tradeFixedAgentLiableUnitNotReg);
                    report->tradeFixedNotReg++;
                    return;
                }
                if(liableNok && agentNotReg && unitNotReg){
                    writeFile("行业固话应用-责任人信息校验不合规.nck",report->tradeFixedLiableNok);
                    report->tradeFixedNok++;
                    return;
                }
                if(liableNotReg && agentNok && unitNotReg){
                    writeFile("行业固话应用-经办人信息校验不合规.nck",report->tradeFixedAgentNok);
                    report->tradeFixedNok++;
                    return;
                }
                if(liableNotReg && agentNotReg && unitNok){
                    writeFile("行业固话应用-单位信息校验不合规.nck",report->tradeFixedUnitNok);
                    report->tradeFixedNok++;
                    return;
                }
                if(liableNok && agentNok && unitNotReg){
                    writeFile("行业固话应用-经办人&责任人信息校验不合规.nck",report->tradeFixedAgentLiableNok);
                    report->tradeFixedNok++;
                    return;
                }
                if(liableNok && agentNotReg && unitNok){
                    writeFile("行业固话应用-责任人&单位信息校验不合规.nck",report->tradeFixedLiableUnitNok);
                    report->tradeFixedNok++;
                    return;
                }
                if(liableNotReg && agentNok && unitNok){
                    writeFile("行业固话应用-经办人&单位信息校验不合规.nck",report->tradeFixedAgentUnitNok);
                    report->tradeFixedNok++;
                    return;
                }
                if(liableNok && agentNok && unitNok){
                    writeFile("行业固话应用-经办人&责任人&单位信息校验不合规.nck",report->tradeFixedAgentLiableUnitNok);
                    report->tradeFixedNok++;
                    return;
                }
            }
        }
        else if(activeDate >= 20130901 && activeDate < 20150101){
            /* 2013年9月1日之后，2015年1月1日之前入网的行业固话用户，需检查责任人(实际使用人就ok)或经办人、单位信息共2个条目，各条目中均需包含姓名/单位名称、
             * 证件类型、证件号码、地址四个字段，并符合完整性和真实性要求。*/
            //2013年9月1日至2015年1月1日 入网的  凡是单位信息未登记 均显示单位信息未登记；凡是单位信息不合规的 均显示单位信息不合规即可 因为另外两条一条合规即可，单位信息是必须合规的
            if( (!liableNotReg && !unitNotReg && !liableNok && !unitNok) ||
                (!agentNotReg && !unitNotReg && !agentNok && !unitNok) ){
                writeFile("行业固话应用-形式合规数据.ok",report->tradeFixedOk);
                writeFile("all.ok(全部合规数据)", report->allOk);
                return;
            }
                        else
            {
                if(unitNotReg){
                    writeFile("行业固话应用-单位信息未登记.nreg",report->tradeFixedUnitNotReg);
                    report->tradeFixedNotReg++;
                    return;
                }
                if(unitNok){
                    writeFile("行业固话应用-单位信息校验不合规.nck",report->tradeFixedUnitNok);
                    report->tradeFixedNok++;
                    return;
                }
                if(liableNotReg && agentNotReg && !unitNok){
                    writeFile("行业固话应用-经办人&责任人信息未登记.nreg",report->tradeFixedAgentLiableNotReg);
                    report->tradeFixedNotReg++;
                    return;
                }
                if(liableNok && agentNotReg && !unitNok){
                    writeFile("行业固话应用-责任人信息校验不合规.nck",report->tradeFixedLiableNok);
                    report->tradeFixedNok++;
                    return;
                }
                if(liableNotReg && agentNok && !unitNok){
                    writeFile("行业固话应用-经办人信息校验不合规.nck",report->tradeFixedAgentNok);
                    report->tradeFixedNok++;
                    return;
                }
                if(liableNok && agentNok && !unitNok){
                    writeFile("行业固话应用-经办人&责任人信息校验不合规.nck",report->tradeFixedAgentLiableNok);
                    report->tradeFixedNok++;
                    return;
                }
            }
        }
        else{
            /* 2015年1月1日之后入网的行业固话用户，需检查责任人(实际使用人，优先)、经办人、单位信息共3个条目，各条目中均需包含姓名/单位名称、证件类型、
             * 证件号码、地址四个字段，并符合完整性和真实性要求。 */
            if(!liableNotReg && !agentNotReg && !unitNotReg && !liableNok && !agentNok && !unitNok)
                        {
                writeFile("行业固话应用-形式合规数据.ok",report->tradeFixedOk);
                writeFile("all.ok(全部合规数据)", report->allOk);
                return;
            }
            if(agentNotReg && !unitNotReg && !liableNotReg){
                writeFile("行业固话应用-经办人信息未登记.nreg",report->tradeFixedAgentNotReg);
                report->tradeFixedNotReg++;
                return;
            }
            if(!agentNotReg && unitNotReg && !liableNotReg){
                writeFile("行业固话应用-单位信息未登记.nreg",report->tradeFixedUnitNotReg);
                report->tradeFixedNotReg++;
                return;
            }
            if(!agentNotReg && !unitNotReg && liableNotReg){
                writeFile("行业固话应用-责任人信息未登记.nreg",report->tradeFixedLiableNotReg);
                report->tradeFixedNotReg++;
                return;
            }
            if(agentNotReg && unitNotReg && !liableNotReg){
                writeFile("行业固话应用-经办人&单位信息未登记.nreg",report->tradeFixedAgentUnitNotReg);
                report->tradeFixedNotReg++;
                return;
            }
            if(!agentNotReg && unitNotReg && liableNotReg){
                writeFile("行业固话应用-责任人&单位信息未登记.nreg",report->tradeFixedLiableUnitNotReg);
                report->tradeFixedNotReg++;
                return;
            }
            if(agentNotReg && !unitNotReg && liableNotReg){
                writeFile("行业固话应用-经办人&责任人信息未登记.nreg",report->tradeFixedAgentLiableNotReg);
                report->tradeFixedNotReg++;
                return;
            }
            if(agentNotReg && unitNotReg && liableNotReg){
                writeFile("行业固话应用-经办人&责任人&单位信息未登记.nreg",report->tradeFixedAgentLiableUnitNotReg);
                report->tradeFixedNotReg++;
                return;
            }
            if(agentNok && !unitNok && !liableNok){
                writeFile("行业固话应用-经办人信息校验不合规.nck",report->tradeFixedAgentNok);
                report->tradeFixedNok++;
                return;
            }
            if(!agentNok && unitNok && !liableNok){
                writeFile("行业固话应用-单位信息校验不合规.nck",report->tradeFixedUnitNok);
                report->tradeFixedNok++;
                return;
            }
            if(!agentNok && !unitNok && liableNok){
                writeFile("行业固话应用-责任人信息校验不合规.nck",report->tradeFixedLiableNok);
                report->tradeFixedNok++;
                return;
            }
            if(agentNok && unitNok && !liableNok){
                writeFile("行业固话应用-经办人&单位信息校验不合规.nck",report->tradeFixedAgentUnitNok);
                report->tradeFixedNok++;
                return;
            }
            if(!agentNok && unitNok && liableNok){
                writeFile("行业固话应用-责任人&单位校验不合规.nck",report->tradeFixedLiableUnitNok);
                report->tradeFixedNok++;
                return;
            }
            if(agentNok && !unitNok && liableNok){
                writeFile("行业固话应用-经办人&责任人信息校验不合规.nck",report->tradeFixedAgentLiableNok);
                report->tradeFixedNok++;
                return;
            }
            if(agentNok && unitNok && liableNok){
                writeFile("行业固话应用-经办人&责任人&单位信息校验不合规.nck",report->tradeFixedAgentLiableUnitNok);
                report->tradeFixedNok++;
                return;
            }
        }
    }
}

/**
 * @brief UserDb::processOneCardFiveNumber 处理一证五号
 */
void UserDb::processOneCardFiveNumber(){
    stErrorFiveNum *ptrMulti = nullptr,*pptr;
    int checkDay;
    //checkDay = 20170401;
    QString onecard2five_date = systemValue.key("onecard2five-date");
    if(onecard2five_date==nullptr){
       checkDay = 20170401;
    }
    else {
       bool ok;
       checkDay = onecard2five_date.toLong(&ok,10); //dec=255 ; ok=rue
       if(!ok){
           checkDay = 20170401;
       }
    }

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
        if(activeDate < checkDay)
            ptrMulti->err1count = 1;
        else //Now activeDate >= checkDay
            ptrMulti->err2count = 1;

        m_pstErrFiveName[sHashTreev] = ptrMulti;
        return;
    }

    ptrMulti = m_pstErrFiveName[sHashTreev];
    do{
        if(0 == strncmp(ptrMulti->number,col.at(ownerNumIndex).toStdString().c_str(),strlen(ptrMulti->number)))
        {
            if(activeDate < checkDay)
            {
                if(ptrMulti->err1count != 0xffff)ptrMulti->err1count ++;
            }
            else {
                if(ptrMulti->err2count != 0xffff)ptrMulti->err2count ++;
            }
            if(ptrMulti->err1count+ptrMulti->err2count > 5 && ptrMulti->err2count && !ptrMulti->errflag)
            {
                ptrMulti->errflag = errType_oneCardFiveNumber;
                errFiveNumber ++; //违规证件号计数
                if(ptrMulti->err1count >= 5)
                    errCardCount += ptrMulti->err2count;
                else
                    errCardCount += ptrMulti->err1count + ptrMulti->err2count - 5 ;
            }
            else if(ptrMulti->errflag&errType_oneCardFiveNumber)
            {
                if(activeDate >= checkDay || ptrMulti->err1count <= 5)
                    errCardCount ++;
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
    if(activeDate < checkDay)
        ptrMulti->err1count = 1;
    else //Now activeDate >= checkDay
        ptrMulti->err2count = 1;
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
            if(0 == strncmp(ptrMulti->number,col.at(ownerNumIndex).toStdString().c_str(),strlen(ptrMulti->number))
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
}

/**
 * @brief UserDb::outputSimpleOneCardFiveNumber 输出一证五号的简要文件
 */
int UserDb::outputSimpleOneCardFiveNumber(){
    stErrorFiveNum *ptrMulti = nullptr,*pptr;
    char myline[512];
    int  tmpnodecount = 0;
    int  hashindex,myerrcount,ioutconut = 0;
    for(hashindex = 0;hashindex < MAX_NUMBER_HASH_NODE; hashindex ++)
    {
        ptrMulti = m_pstErrFiveName[hashindex];
        if(ptrMulti == nullptr)continue;
        do{
            pptr = ptrMulti;
            if(ptrMulti->errflag&errType_oneCardFiveNumber)
            {
                tmpnodecount ++;
                if(ptrMulti->err1count >= 5)
                    myerrcount = ptrMulti->err2count;
                else
                    myerrcount = ptrMulti->err1count + ptrMulti->err2count - 5 ;
                sprintf(myline,"%d:%s|%d|%d",ioutconut+1,ptrMulti->number,ptrMulti->err1count+ptrMulti->err2count,myerrcount);
                writeFile("一证五号简要输出.txt",ioutconut,myline);
            }
            ptrMulti = pptr->next;
        }while(ptrMulti != nullptr);
    }
    return tmpnodecount;
}

/**
 * @brief UserDb::writeOneCardFiveNumberFile 输出一证五号的排序后文件
 */
void UserDb::writeOneCardFiveNumberFile()
{
    //writeFile("一证五号不合规原始.nck", report->onecardFiveNumber);
    const QString filename="一证五号不合规原始.nck";
    stErrorFiveNum *ptrMulti = nullptr,*pptr;
    int inode = 0,iinode;
    for(int hashindex = 0;hashindex < MAX_NUMBER_HASH_NODE; hashindex ++)
    {
        ptrMulti = m_pstErrFiveName[hashindex];
        if(ptrMulti == nullptr)continue;
        do{
            pptr = ptrMulti;
            //如果需要输出文件，根据  ptrMulti->number 进行检索
            if(ptrMulti->errflag&errType_oneCardFiveNumber)
            {
                iinode = outputSearch(filename,ptrMulti->number,ownerNumIndex,ptrMulti->err1count+ptrMulti->err2count);
                inode ++;
                emit message("二次输出一证五号文件,节点数"+QString::number(inode)+",文件记录数"+QString::number(iinode)+"行");
            }
            ptrMulti = pptr->next;
        }while(ptrMulti != nullptr);
    }
}

/**
 * @brief UserDb::outputSearch 输出特定文件中匹配的特定行
 */
int UserDb::outputSearch(const QString filename,const char *checkline,const int index,const int icount)
{
    QFile file(path+QDir::separator()+filename);
    QTextCodec *code = QTextCodec::codecForName("GBK");//设置文件编码
    int mcount = 0;

    if(file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream stream(&file);
        stream.setCodec(code);
         do {
            line = stream.readLine();
            col =  line.split(delimeter);
            if(col.size() == COL_NUM)
            {
                if(0 == strncmp(checkline,col.at(index).toStdString().c_str(),strlen(checkline)))
                    writeFile("一证五号不合规.nck", mcount);
                if(mcount == icount)break;
            }
//            if(col.size() != COL_NUM)//Error
//                break;
        }while(!stopped && !stream.atEnd());
        file.close();
    }
    else
        emit messageWarning("文件打开错误。");

    return mcount;
}

#if  FILE_DIV_TEST
#define   MAX_FILE_NODE_LIMIT_BYNUMBER  100000
#else
#define  MAX_FILE_NODE_LIMIT_BYNUMBER (MAX_BCHUNKS*MAX_BCHUNKNODES)/3
#endif

void UserDb::divFile(int ifileindex)
{
    QString origfilename;
    QString dfname,lfname;
    int lnodecount = 0,tmpcount = 0;
    bchunkReset(&bErrFive);
    if(ifileindex == -1)
        origfilename = m_filename;
    else
        origfilename = path+QDir::separator()+m_leavename+QString::number(ifileindex);

    if(origfilename.isNull()||origfilename.isEmpty())return;
    QFile file(origfilename);
    if(!file.exists())  return;
    QTextCodec *code = QTextCodec::codecForName("GBK");//设置文件编码
    dfname  =  m_basename + QString::number(ifileindex+1);
    lfname  =  m_leavename + QString::number(ifileindex+1);
    m_fileindex = ifileindex+1;
    bchunkReset(&bErrFive);
    memset(m_pstErrFiveName,0,sizeof(stErrorFiveNum *)*MAX_NUMBER_HASH_NODE);
    emit message("扫描文件中，准备切割......");

    if(!file.open(QFile::ReadOnly | QFile::Text))
        emit messageWarning("文件打开错误。");
    else
    {
        QTextStream stream(&file);
        stream.setCodec(code);
        int line_count = 0;
        do
        {   //逐行读取
            line = stream.readLine();
            col =  line.split(delimeter);
            if(col.size() != COL_NUM)//Error
                writeFile(dfname,tmpcount);
            else {
                //根据使用者证件号码进行切分
                //如果证件号码超过限制数，迭代到下一个文件,写入到一个新文件
                if(checkKeyInfo(col.at(ownerNumIndex)))
                {
                    writeFile(dfname,tmpcount);
                }
                else
                    writeFile(lfname,lnodecount);
            }
            line_count ++;
#if       FILE_DIV_TEST
            if(line_count >= TEST_LIMIT)
                break;
#endif
            if(line_count%10000 == 0)
                emit message("扫描文件"+ origfilename +"记录数"+QString::number(tmpcount+lnodecount)+"行");
        }while(!stopped && !stream.atEnd());
        file.close();
    }
    emit message("切割文件"+dfname+",记录数"+QString::number(tmpcount)+"行，剩余"+QString::number(lnodecount)+"行");
    flushFile();

    if(m_fileindex > 0) //Need Remove leave file  ...... release space
        QFile::remove(origfilename);

    if(lnodecount > MAX_FILE_NODE_LIMIT_BYNUMBER * 3 )
        divFile(ifileindex+1);
    else if(lnodecount )
        m_leaveindex = m_fileindex;
    else
        m_leaveindex = -1;
}

bool UserDb::checkKeyInfo(const QString str)
{
    stErrorFiveNum *ptrMulti = nullptr,*pptr;
    unsigned long sHashTreev = strHash(str.toStdString().c_str(),strlen(str.toStdString().c_str()))%MAX_NUMBER_HASH_NODE;
    if(m_pstErrFiveName[sHashTreev] == nullptr)
    {
        if(bErrFive.ncount >= MAX_FILE_NODE_LIMIT_BYNUMBER)
            return false;
        ptrMulti = (stErrorFiveNum *)bchunkAllocNode(&bErrFive);
        if(ptrMulti == nullptr) //out of memory
            return false;
        if(strlen(str.toStdString().c_str())+1 <= MAX_NUMBER_LENGTH)
            memcpy(ptrMulti->number,str.toStdString().c_str(),strlen(str.toStdString().c_str())+1);
        else
            memcpy(ptrMulti->number,str.toStdString().c_str(),MAX_NUMBER_LENGTH-1);
        m_pstErrFiveName[sHashTreev] = ptrMulti;
        return true;
    }
    ptrMulti = m_pstErrFiveName[sHashTreev];
    do{
        if(0 == strncmp(ptrMulti->number,str.toStdString().c_str(),strlen(ptrMulti->number)))
            return true;
        pptr = ptrMulti;
        ptrMulti = ptrMulti->next;
    }while(ptrMulti != nullptr);

    ptrMulti = pptr;
    if(bErrFive.ncount >= MAX_FILE_NODE_LIMIT_BYNUMBER)
        return false;
    ptrMulti->next = (stErrorFiveNum *)bchunkAllocNode(&bErrFive);
    if(ptrMulti->next == nullptr)
        return false;
    ptrMulti = ptrMulti->next;
    if(strlen(str.toStdString().c_str())+1 <= MAX_NUMBER_LENGTH)
        memcpy(ptrMulti->number,str.toStdString().c_str(),strlen(str.toStdString().c_str())+1);
    else
        memcpy(ptrMulti->number,str.toStdString().c_str(),MAX_NUMBER_LENGTH-1);
     return true;
}
