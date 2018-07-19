#include "xmlconfigreader.h"
#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QDebug>
#include <iostream>
#include <QDomElement>

//读取数据列配置
QList<QList<QString>> XMLConfigReader::readAutoid(){
    enum ExitCode
    {
        Success,
        ParseFailure,
        ArgumentError,
        WriteError,
        FileFailure
    };
    QTextStream errorStream(stderr);
    QString inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-autoid.xml";
    QFile file(inputFilePath);
    if (!QFile::exists(inputFilePath))
    {
        errorStream << QString("File %1 does not exist.\n").arg(inputFilePath);

    } else if (!file.open(QIODevice::ReadOnly)) {
        errorStream << QString("Failed to open file %1.\n").arg(inputFilePath);
    }
    QList<QList<QString>> rtnList;
    QStringList tempLine;
    QDomDocument doc;
    if(!doc.setContent(&file))
     {
                 file.close();
//                 return;
     }
     file.close();
//     QDomElement root=doc.documentElement();
     QDomNodeList list=doc.elementsByTagName("sub");
     int count= list.size();
        qDebug()<<"count = "<<count;

    for(int i=0; i<count; i++)
    {
        tempLine.clear();

        if(list.at(i).toElement().nodeName()=="sub"){
            tempLine.clear();
//            qDebug()<<"category="<<reader.attributes().value("category");
            tempLine.append(list.at(i).parentNode().toElement().attribute("category"));
            tempLine.append(list.at(i).toElement().attribute("category"));
            //            qDebug()<<"lineNumber="<<reader.lineNumber();
            //            qDebug()<<"name="<<reader.name();
            //            qDebug()<<"text="<<reader.text();
            //            qDebug()<<"tokenString="<<reader.tokenString();
            //            qDebug()<<"qualifiedName="<<reader.qualifiedName();
//            qDebug()<<"readElementText"<<reader.readElementText();
            tempLine.append(list.at(i).toElement().text());
            rtnList.append(tempLine);
        }

    }
//! [2]
        return rtnList;
}

//读取单列配置
void XMLConfigReader::processFile(QString* inputFilePath, QString* child, QString* var)
{
    if("业务类型移动"==*var){
        *child = "移动";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-businesstype.xml";
    }
    else if("业务类型固定"==*var){
        *child = "固定";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-businesstype.xml";
    }
    else if("业务状态非实名停机"==*var){
        *child = "非实名停机";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-businesstype.xml";
    }
    else if("业务状态不在网"==*var){
        *child = "不在网";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-businesstype.xml";
    }
    else if("个人证件居民身份证"==*var){
        *child = "居民身份证";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-cardtype.xml";
    }
    else if("个人证件临时居民身份证"==*var){
        *child = "临时居民身份证";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-cardtype.xml";
    }
    else if("个人证件户口薄"==*var){
        *child = "户口薄";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-cardtype.xml";
    }
    else if("个人证件中国人民解放军军人身份证件"==*var){
        *child = "中国人民解放军军人身份证件";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-cardtype.xml";
    }
    else if("个人证件中国人民武装警察身份证件"==*var){
        *child = "中国人民武装警察身份证件";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-cardtype.xml";
    }
    else if("个人证件港澳居民来往内地通行证"==*var){
        *child = "港澳居民来往内地通行证";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-cardtype.xml";
    }
    else if("个人证件台湾居民来往大陆通行证"==*var){
        *child = "台湾居民来往大陆通行证";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-cardtype.xml";
    }
    else if("个人证件外国公民护照"==*var){
        *child = "外国公民护照";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-cardtype.xml";
    }
    else if("个人证件法律、行政法规和国家规定的其他有效身份证件"==*var){
        *child = "法律、行政法规和国家规定的其他有效身份证件";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-cardtype.xml";
    }
    else if("个人证件非法律、行政法规和国家规定的有效身份证件"==*var){
        *child = "非法律、行政法规和国家规定的有效身份证件";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-cardtype.xml";
    }
    else if("单位证件组织机构代码证"==*var){
        *child = "组织机构代码证";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-cardtype.xml";
    }
    else if("单位证件营业执照"==*var){
        *child = "营业执照";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-cardtype.xml";
    }
    else if("单位证件事业单位法人证书或者社会团体法人登记证书"==*var){
        *child = "事业单位法人证书或者社会团体法人登记证书";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-cardtype.xml";
    }
    else if("单位证件法律、行政法规和国家规定的其他有效证件或者证明文件"==*var){
        *child = "法律、行政法规和国家规定的其他有效证件或者证明文件";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-cardtype.xml";
    }
    else if("单位证件非法律、行政法规和国家规定的有效身份证件"==*var){
        *child = "非法律、行政法规和国家规定的有效身份证件";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-cardtype.xml";
    }
    else if("个人用户姓名comon-rule"==*var){
        *child = "common-rule";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/rule/rule-name-person.xml";
     }
    else if("个人用户姓名match-rule"==*var){
        *child = "match-rule";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/rule/rule-name-person.xml";
     }
    else if("行业用户姓名comon-rule"==*var){
        *child = "common-rule";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/rule/rule-name-unit.xml";
     }
    else if("行业用户姓名match-rule"==*var){
        *child = "match-rule";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/rule/rule-name-unit.xml";
     }
    else if("证件号码comon-rule"==*var){
        *child = "common-rule";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/rule/rule-cardnum-person-unit.xml";
     }
    else if("证件号码match-rule"==*var){
        *child = "match-rule";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/rule/rule-cardnum-person-unit.xml";
     }
    else if("证件地址addr-rule"==*var){
        *child = "addr-rule";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/rule/rule-addr-person-unit.xml";
     }
    else if("证件地址match-rule"==*var){
        *child = "match-rule";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/rule/rule-addr-person-unit.xml";
     }
    else if("重号率阈值"==*var){
        *child = "重号率阈值";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/rule/rule-common.xml";
     }
    else if("个人用户规则"==*var){
        *child = "个人用户规则";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/rule/rule-common.xml";
     }
    else if("单位/行业用户规则"==*var){
        *child = "单位/行业用户规则";
        *inputFilePath = "/Users/zhangxianjin/qtcode/testXml/rule/rule-common.xml";
     }
}

QList<QString> XMLConfigReader::readValue(QString var){
    enum ExitCode
    {
        Success,
        ParseFailure,
        ArgumentError,
        WriteError,
        FileFailure
    };
    QTextStream errorStream(stderr);
    QString inputFilePath;
    QString child;
    processFile(&inputFilePath, &child, &var);


    qDebug()<<"读取配置文件"<<inputFilePath;

    QFile file(inputFilePath);
    if (!QFile::exists(inputFilePath))
    {
        errorStream << QString("File %1 does not exist.\n").arg(inputFilePath);

    }
    else if (!file.open(QIODevice::ReadOnly)) {
        errorStream << QString("Failed to open file %1.\n").arg(inputFilePath);
    }
    QList<QString> rtnList;
    QDomDocument doc;
    if(!doc.setContent(&file))
     {
                 file.close();
//                 return;
     }
     file.close();
//     QDomElement root=doc.documentElement();
     QDomNodeList list=doc.elementsByTagName("sub");
     int count= list.size();
        qDebug()<<"count = "<<count;

    for(int i=0; i<count; i++)
    {
//        qDebug()<<"item is "<<list.at(i).toElement().text();
        if(list.at(i).toElement().nodeName()=="sub" && list.at(i).parentNode().toElement().attribute("category")==child)
        {
            rtnList.append(list.at(i).toElement().text());
        }

    }

    return rtnList;
}


void XMLConfigReader::deleteAutoid(QString item){
    qDebug()<<"=========================in deleteAutoid =======================";
    QString outputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-autoid.xml";
    QTextStream errorStream(stderr);

    QFile file(outputFilePath);
    if(!file.open(QFile::ReadOnly)){
                errorStream << QString("Failed to open stdout.");
                    return;
    }
    //删除一个一级子节点及其元素，外层节点删除内层节点于此相同
   QDomDocument doc;
   if(!doc.setContent(&file))
    {
                file.close();
                return;
    }
    file.close();
    QDomElement root=doc.documentElement();
    QDomNodeList list=doc.elementsByTagName("sub");
    int count= list.size();

    //由标签名定位
    for(int i=0;i<count;i++)
    {
        qDebug()<<"count="<<list.size();
        QDomElement e=list.at(0).toElement();
//                if(e.attribute("category")=="机主")
        {
            e.parentNode().removeChild(e);//list.at(0));
            qDebug()<<"删除执行完毕！"<<e.nodeName()<<e.attribute("category");//list.at(0).nodeName();
        }
    }
    if(!file.open(QFile::WriteOnly|QFile::Truncate))
        return;
    //输出到文件
    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    //缩进4格
    file.close();

}

void XMLConfigReader::addAutoid(QString parent, QString item, int offset){
    qDebug()<<"=========================in addAutoid =======================";
    QString outputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-autoid.xml";


    QFile file(outputFilePath);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug()<<"open for add error..." ;
    }
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug()<<"add setcontent error..." ;
            file.close();
    }

    file.close();
    QDomElement root = doc.documentElement();//.firstChildElement("items").at(0);//doc.documentElement();
    if(root.isNull())
    {
        root = doc.createElement("ipconfig");
    }
    QDomElement element_root = doc.createElement("items");
    QDomAttr attr_id = doc.createAttribute("id");
    QDomElement element_rmt = doc.createElement("rmt_name");
    QDomElement element_ipa = doc.createElement("ipa");
    QDomElement element_ipb = doc.createElement("ipb");
    QString str_id;
    if(root.lastChild().isNull())
    {
        str_id = "1";
        attr_id.setValue(str_id);
    }
    else
    {
        str_id = root.lastChild().toElement().attribute("id");
        int count = str_id.toInt()+1;
        attr_id.setValue(QString::number(count));
    }
    QDomText text;
    QString rmt_name="remote1";
    QString ipa="127.0.0.1";
    QString ipb="192.168.1.199";
    text =doc.createTextNode(rmt_name);
    element_rmt.appendChild(text);
    text = doc.createTextNode(ipa);
    element_ipa.appendChild(text);
    text = doc.createTextNode(ipb);
    element_ipb.appendChild(text);
    text.clear();
    element_root.appendChild(element_rmt);
    element_root.appendChild(element_ipa);
    element_root.appendChild(element_ipb);
    element_root.setAttributeNode(attr_id);
    root.appendChild(element_root);

    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
        qDebug() << "open for add error!";
    QTextStream out(&file);
    doc.save(out,4);
    file.close();

}

void XMLConfigReader::updateAutoid(QString parent, QList<QList<QString>> items, int offset){
    qDebug()<<"=========================in updateAutoid =======================";
    QString outputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-autoid.xml";

    qDebug()<<"parent is "<<parent;
    for(int i=0; i<items.size(); i++){
        qDebug()<<"items is "<<items.at(i);
    }
    QFile file(outputFilePath);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug()<<"open for add error..." ;
    }
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug()<<"add setcontent error..." ;
            file.close();
    }

    file.close();
//    QDomElement root = doc.documentElement();//.firstChildElement("items").at(0);//doc.documentElement();
    QDomNodeList lists = doc.elementsByTagName("item");
    QDomElement ele;
    for(int i=0; i<lists.size(); i++){
         ele = lists.at(i).toElement();
        if(ele.attribute("category") == parent)  {
            QDomNodeList child=ele.childNodes();
            int childsize = child.size();
            for(int j=0; j< childsize; j++){
                qDebug()<<"child size = "<<child.size();
                qDebug()<<"deleted "<<child.at(0).toElement().attribute("category");
                ele.removeChild(child.at(0).toElement());
            }
//         child.at(0).toElement().firstChild().setNodeValue("1234"); //修改节点
         QDomElement menuOnlyElement;

         QDomText text;
         for(int k=0; k<items.size(); k++)
         {
             menuOnlyElement = doc.createElement("sub");
             text = doc.createTextNode(items.at(k).at(2));
             menuOnlyElement.setAttribute("category",items.at(k).at(1));
             menuOnlyElement.appendChild(text);
             ele.appendChild(menuOnlyElement);
             qDebug()<<"在"<<parent<<"节点中增加了"<<items.at(k).at(1);
         }

        }
    }
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        qDebug() << "open for add error!";
    QTextStream out(&file);
    doc.save(out,4);
    file.close();

}


void XMLConfigReader::writeAutoid(QList<QList<QString>> autoid){
    qDebug()<<"=========================in writeAutoid =======================";
//   deleteAutoid("items");
    QString temp="";
    QList<QList<QString>> qqq;
    for(int i=0; i<autoid.size(); i++){
        qDebug()<<"autoid is "<<autoid.at(i).at(1);
//        if(temp=="")
        {
            if(temp!=""&&autoid.at(i).at(0)!=temp){
                qDebug()<<"temp is "<<temp;

                updateAutoid(temp,qqq,0);//autoid.at(i),offset++);
                qqq.clear();
            }
            qqq.append(autoid.at(i));
            temp = autoid.at(i).at(0);
        }

        updateAutoid(temp,qqq,0);
    }
    //updateAutoid(temp,qqq,0);
}


/**
 * @brief XMLConfigReader::writeValue 通用修改单列配置项
 * @param menu 要修改的节点
 * @param value 子节点值数组
 */
void XMLConfigReader::writeValue(QString menu,QList<QString> value){
    qDebug()<<"=========================in writeValue =======================";
    QList<QString> qqq;
    qDebug()<<"menu is "<<menu;
    QString inputFilePath;
    QString child;
    processFile(&inputFilePath, &child, &menu);
    qDebug()<<"要写入的文件是："<<inputFilePath;
    qDebug()<<"分支是："<<child;
    for(int i=0; i<value.size(); i++){
        qDebug()<<"valueid is "<<value.at(i);
    }

    //修改文件
    QFile file(inputFilePath);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug()<<"open for add error..." ;
    }
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug()<<"add setcontent error..." ;
            file.close();
    }

    file.close();

    //找到对应的子节点
    QString item;
    if("移动"==child||"固定"==child){
        item = "type";
    }
    else if("非实名停机"==child){
        item = "o-realname-stop";
    }
    else if("不在网"==child){
        item = "no-in-net";
    }
    else if("common-rule"==child){
        item = "rule";
    }
    else if("match-rule"==child){
        item = "rule";
    }
    else if("addr-rule"==child){
        item = "rule";
    }
    else{
        item = "cardtype";
    }
//    qDebug()<<"item is "<<item;
    QDomNodeList lists = doc.elementsByTagName(item);
    QDomElement ele;
    for(int i=0; i<lists.size(); i++){
         ele = lists.at(i).toElement();
          qDebug()<<"ele is = "<<ele.nodeName();
        if(ele.attribute("category") == child)  {
            QDomNodeList childnode=ele.childNodes();
            int childsize = childnode.size();
            //删除子节点（旧数据）
            for(int j=0; j< childsize; j++){
                qDebug()<<"child size = "<<child.size();
                qDebug()<<"deleted "<<childnode.at(0).toElement().text();
                ele.removeChild(childnode.at(0));
            }

          //添加新节点
         QDomElement menuOnlyElement;

         QDomText text;
         for(int k=0; k<value.size(); k++)
         {
             menuOnlyElement = doc.createElement("sub");
             text = menuOnlyElement.toDocument().createTextNode(value.at(k));
             text.setNodeValue(value.at(k));
             menuOnlyElement.appendChild(text);
             ele.appendChild(menuOnlyElement);
             qDebug()<<"在"<<menu<<"节点中增加了"<<value.at(k);
         }

        }
    }
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        qDebug() << "open for add error!";
    QTextStream out(&file);
    doc.save(out,4);
    file.close();

}


/**
 * @brief XMLConfigReader::writeSystemValue 修改系统参数
 * @param dataRange 数据范围
 * @param compliantDate 合规性检查日期
 * @param onecard2fiveDate 一证五号时间节点
 * @param randomDateLabel 随机日期
 */
void XMLConfigReader::writeSystemValue(QString dataRange, QString compliantDate, QString onecard2fiveDate, QString randomDate){
    qDebug()<<"调用writeSystemValue函数：";
    qDebug()<<"保存的值为"<<dataRange<<compliantDate<<onecard2fiveDate<<randomDate;
    QString outputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-system.xml";


    QFile file(outputFilePath);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug()<<"open for add error..." ;
    }
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug()<<"add setcontent error..." ;
            file.close();
    }

    file.close();
    QDomNodeList lists = doc.elementsByTagName("data-range");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点data-range";
    }
    else {
        lists.at(0).toElement().firstChild().setNodeValue(dataRange);// 修改对应XML值。
    }
    lists = doc.elementsByTagName("compliant-date");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点compliant-date";
    }
    else {
        lists.at(0).toElement().firstChild().setNodeValue(compliantDate);// 修改对应XML值。
    }
    lists = doc.elementsByTagName("onecard2five-date");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点onecard2five-date";
    }
    else {
        lists.at(0).toElement().firstChild().setNodeValue(onecard2fiveDate);// 修改对应XML值。
    }
    lists = doc.elementsByTagName("random-date");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点random-date";
    }
    else {
        lists.at(0).toElement().firstChild().setNodeValue(randomDate);// 修改对应XML值。
    }
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        qDebug() << "open for add error!";
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}

QMap<QString,QString> XMLConfigReader::readSystemValue(){
    qDebug()<<"调用readSystemValue函数：";
//    qDebug()<<"保存的值为"<<dataRange<<compliantDate<<onecard2fiveDate<<randomDateLabel;
    QString outputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-system.xml";
    QMap<QString,QString> rtn_map;


    QFile file(outputFilePath);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug()<<"open for add error..." ;
    }
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug()<<"add setcontent error..." ;
            file.close();
    }

    file.close();
    QDomNodeList lists = doc.elementsByTagName("data-range");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点dataRange";
    }
    else {
        qDebug()<<lists.at(0).toElement().text();
        rtn_map.insert("data-range",lists.at(0).toElement().text());
    }
    lists = doc.elementsByTagName("compliant-date");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点compliant-date";
    }
    else {
        qDebug()<<lists.at(0).toElement().text();
        rtn_map.insert("compliant-date",lists.at(0).toElement().text());
    }
    lists = doc.elementsByTagName("onecard2five-date");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点onecard2five-date";
    }
    else {
        qDebug()<<lists.at(0).toElement().text();
        rtn_map.insert("onecard2five-date",lists.at(0).toElement().text());
    }
    lists = doc.elementsByTagName("random-date");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点random-date";
    }
    else {
        qDebug()<<lists.at(0).toElement().text();
        rtn_map.insert("random-date",lists.at(0).toElement().text());
    }
//    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
//        qDebug() << "open for add error!";
//    QTextStream out(&file);
//    doc.save(out,4);
//    file.close();
    return rtn_map;
}

/**
 * @brief XMLConfigReader::writeWorkingpathValue 设置工作路径
 * @param workingpath
 */
void XMLConfigReader::writeWorkingpathValue(QString workingpath){
    qDebug()<<"调用 writeWorkingpathValue 函数：";
    qDebug()<<"保存的值为"<<workingpath;
    QString outputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-workingpath.xml";


    QFile file(outputFilePath);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug()<<"open for add error..." ;
    }
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug()<<"add setcontent error..." ;
            file.close();
    }

    file.close();
    QDomNodeList lists = doc.elementsByTagName("workingpath");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点workingpath";
    }
    else {
        lists.at(0).toElement().firstChild().setNodeValue(workingpath);// 修改对应XML值。
    }
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        qDebug() << "open for add error!";
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}

/**
 * @brief XMLConfigReader::readWorkingpathValue 读取工作路径
 * @return
 */
QMap<QString,QString> XMLConfigReader::readWorkingpathValue(){
    qDebug()<<"调用 writeWorkingpathValue 函数：";
    QString outputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-workingpath.xml";
    QMap<QString,QString> rtn_map;

    QFile file(outputFilePath);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug()<<"open for add error..." ;
    }
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug()<<"add setcontent error..." ;
            file.close();
    }
    file.close();
    QDomNodeList lists = doc.elementsByTagName("workingpath");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点 workingpath";
    }
    else {
        qDebug()<<lists.at(0).toElement().text();
        rtn_map.insert("workingpath",lists.at(0).toElement().text());
    }
    return rtn_map;
}

/**
 * @brief XMLConfigReader::writeDelimiterValue 设置字段间分隔符
 * @param delimiter
 */
void XMLConfigReader::writeDelimiterValue(QString delimiter){
    qDebug()<<"调用 writeDelimiterValue 函数：";
    qDebug()<<"保存的值为"<<delimiter;
    QString outputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-autoid.xml";


    QFile file(outputFilePath);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug()<<"open for add error..." ;
    }
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug()<<"add setcontent error..." ;
            file.close();
    }

    file.close();
    QDomNodeList lists = doc.elementsByTagName("delimiter");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点 delimiter";
    }
    else {
        lists.at(0).toElement().firstChild().setNodeValue(delimiter);// 修改对应XML值。
    }
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        qDebug() << "open for add error!";
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}

/**
 * @brief XMLConfigReader::readWorkingpathValue 读取字段间分隔符
 * @return
 */
QMap<QString,QString> XMLConfigReader::readDelimiterValue(){
    qDebug()<<"调用 readDelimiterValue 函数：";
    QString outputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-autoid.xml";
    QMap<QString,QString> rtn_map;

    QFile file(outputFilePath);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug()<<"open for add error..." ;
    }
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug()<<"add setcontent error..." ;
            file.close();
    }
    file.close();
    QDomNodeList lists = doc.elementsByTagName("delimiter");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点 delimiter";
    }
    else {
        qDebug()<<lists.at(0).toElement().text();
        rtn_map.insert("delimiter",lists.at(0).toElement().text());
    }
    return rtn_map;
}

/**
 * @brief XMLConfigReader::writeItemnumValue 设置字段个数
 * @param delimiter
 */
void XMLConfigReader::writeItemnumValue(QString itemnum){
    qDebug()<<"调用 writeItemnumValue 函数：";
    qDebug()<<"保存的值为"<<itemnum;
    QString outputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-autoid.xml";


    QFile file(outputFilePath);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug()<<"open for add error..." ;
    }
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug()<<"add setcontent error..." ;
            file.close();
    }

    file.close();
    QDomNodeList lists = doc.elementsByTagName("itemnum");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点 itemnum";
    }
    else {
        lists.at(0).toElement().firstChild().setNodeValue(itemnum);// 修改对应XML值。
    }
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        qDebug() << "open for add error!";
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}

/**
 * @brief XMLConfigReader::readItemnumValue 读取字段个数
 * @return
 */
QMap<QString,QString> XMLConfigReader::readItemnumValue(){
    qDebug()<<"调用 readItemnumValue 函数：";
    QString outputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-autoid.xml";
    QMap<QString,QString> rtn_map;

    QFile file(outputFilePath);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug()<<"open for add error..." ;
    }
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug()<<"add setcontent error..." ;
            file.close();
    }
    file.close();
    QDomNodeList lists = doc.elementsByTagName("itemnum");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点 itemnum";
    }
    else {
        qDebug()<<lists.at(0).toElement().text();
        rtn_map.insert("itemnum",lists.at(0).toElement().text());
    }
    return rtn_map;
}

/**
 * @brief XMLConfigReader::writeDateformatValue 设置时间格式
 * @param delimiter
 */
void XMLConfigReader::writeDateformatValue(QString dateformat){
    qDebug()<<"调用 writeDateformatValue 函数：";
    qDebug()<<"保存的值为"<<dateformat;
    QString outputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-autoid.xml";


    QFile file(outputFilePath);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug()<<"open for add error..." ;
    }
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug()<<"add setcontent error..." ;
            file.close();
    }

    file.close();
    QDomNodeList lists = doc.elementsByTagName("dateformat");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点 dateformat";
    }
    else {
        lists.at(0).toElement().firstChild().setNodeValue(dateformat);// 修改对应XML值。
    }
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        qDebug() << "open for add error!";
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}

/**
 * @brief XMLConfigReader::readItemnumValue 读取时间格式
 * @return
 */
QMap<QString,QString> XMLConfigReader::readDateformatValue(){
    qDebug()<<"调用 readDateformatValue 函数：";
    QString outputFilePath = "/Users/zhangxianjin/qtcode/testXml/config/config-autoid.xml";
    QMap<QString,QString> rtn_map;

    QFile file(outputFilePath);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug()<<"open for add error..." ;
    }
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug()<<"add setcontent error..." ;
            file.close();
    }
    file.close();
    QDomNodeList lists = doc.elementsByTagName("dateformat");
    if(lists.size()==0)
    {
        qDebug()<<"没有找到节点 dateformat";
    }
    else {
        qDebug()<<lists.at(0).toElement().text();
        rtn_map.insert("dateformat",lists.at(0).toElement().text());
    }
    return rtn_map;
}

/**
 * @brief XMLConfigReader::writeCommonRule 设置公共参数
 * @param delimiter
 */
void XMLConfigReader::writeCommonRuleValue(QMap<QString, QString> map){
    qDebug()<<"调用 writeCommonRule 函数：";
    QString outputFilePath = "/Users/zhangxianjin/qtcode/testXml/rule/rule-common.xml";


    QFile file(outputFilePath);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug()<<"open for add error..." ;
    }
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug()<<"add setcontent error..." ;
            file.close();
    }

    file.close();
    QDomNodeList lists;
    QMap<QString,QString>::Iterator  it;
    for(it = map.begin(); it != map.end(); ++it)
    {
//         cout<<"key:"<<it.key()<<"value:"<<it.value()<<endl;

        if("personNameLen_min"==it.key()){
            lists = doc.elementsByTagName("len-min");
            for(int i=0; i<lists.size(); i++){
                if(lists.at(i).parentNode().toElement().nodeName()=="name"&&lists.at(i).parentNode().parentNode().toElement().nodeName()=="person"){
                    lists.at(i).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
                }
            }
        }
        else if("personNameLen_max"==it.key()){
            lists = doc.elementsByTagName("len-max");
            for(int i=0; i<lists.size(); i++){
                if(lists.at(i).parentNode().toElement().nodeName()=="name"&&lists.at(i).parentNode().parentNode().toElement().nodeName()=="person"){
                    lists.at(i).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
                }
            }
        }
        else if("personNamePermit_char"==it.key()){
            lists = doc.elementsByTagName("permit-char");
            for(int i=0; i<lists.size(); i++){
                if(lists.at(i).parentNode().toElement().nodeName()=="name"&&lists.at(i).parentNode().parentNode().toElement().nodeName()=="person"){
                    lists.at(i).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
                }
            }
        }
        else if("personCardtypeTime_interval"==it.key()){
            lists = doc.elementsByTagName("time-interval");
            for(int i=0; i<lists.size(); i++){
                if(lists.at(i).parentNode().toElement().nodeName()=="cardtype"&&lists.at(i).parentNode().parentNode().toElement().nodeName()=="person"){
                    lists.at(i).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
                }
            }
        }
        else if("personCard_numLen_min"==it.key()){
            lists = doc.elementsByTagName("len-min");
            for(int i=0; i<lists.size(); i++){
                if(lists.at(i).parentNode().toElement().nodeName()=="card-num"&&lists.at(i).parentNode().parentNode().toElement().nodeName()=="person"){
                    lists.at(i).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
                }
            }
        }
        else if("personCard_numLen_max"==it.key()){
            lists = doc.elementsByTagName("len-max");
            for(int i=0; i<lists.size(); i++){
                if(lists.at(i).parentNode().toElement().nodeName()=="card-num"&&lists.at(i).parentNode().parentNode().toElement().nodeName()=="person"){
                    lists.at(i).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
                }
            }
        }
        else if("personCard_addLen_min"==it.key()){
            lists = doc.elementsByTagName("len-min");
            for(int i=0; i<lists.size(); i++){
                if(lists.at(i).parentNode().toElement().nodeName()=="card-add"&&lists.at(i).parentNode().parentNode().toElement().nodeName()=="person"){
                    lists.at(i).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
                }
            }
        }
        else if("personCard_addLen_max"==it.key()){
            lists = doc.elementsByTagName("len-max");
            for(int i=0; i<lists.size(); i++){
                if(lists.at(i).parentNode().toElement().nodeName()=="card-add"&&lists.at(i).parentNode().parentNode().toElement().nodeName()=="person"){
                    lists.at(i).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
                }
            }
        }
        else if("unitNameLen_min"==it.key()){
            lists = doc.elementsByTagName("len-min");
            for(int i=0; i<lists.size(); i++){
                if(lists.at(i).parentNode().toElement().nodeName()=="name"&&lists.at(i).parentNode().parentNode().toElement().nodeName()=="unit"){
                    lists.at(i).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
                }
            }
        }
        else if("unitNameLen_max"==it.key()){
            lists = doc.elementsByTagName("len-max");
            for(int i=0; i<lists.size(); i++){
                if(lists.at(i).parentNode().toElement().nodeName()=="name"&&lists.at(i).parentNode().parentNode().toElement().nodeName()=="unit"){
                    lists.at(i).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
                }
            }
        }
        else if("unitCardtypeTime_interval"==it.key()){
            lists = doc.elementsByTagName("time-interval");
            for(int i=0; i<lists.size(); i++){
                if(lists.at(i).parentNode().toElement().nodeName()=="cardtype"&&lists.at(i).parentNode().parentNode().toElement().nodeName()=="unit"){
                    lists.at(i).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
                }
            }
        }
        else if("unitCard_numLen_min"==it.key()){
            lists = doc.elementsByTagName("len-min");
            for(int i=0; i<lists.size(); i++){
                if(lists.at(i).parentNode().toElement().nodeName()=="card-num"&&lists.at(i).parentNode().parentNode().toElement().nodeName()=="unit"){
                    lists.at(i).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
                }
            }
        }
        else if("unitCard_numLen_max"==it.key()){
            lists = doc.elementsByTagName("len-max");
            for(int i=0; i<lists.size(); i++){
                if(lists.at(i).parentNode().toElement().nodeName()=="card-num"&&lists.at(i).parentNode().parentNode().toElement().nodeName()=="unit"){
                    lists.at(i).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
                }
            }
        }
        else if("unitCard_addLen_min"==it.key()){
            lists = doc.elementsByTagName("len-min");
            for(int i=0; i<lists.size(); i++){
                if(lists.at(i).parentNode().toElement().nodeName()=="card-add"&&lists.at(i).parentNode().parentNode().toElement().nodeName()=="unit"){
                    lists.at(i).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
                }
            }
        }
        else if("unitCard_addLen_max"==it.key()){
            lists = doc.elementsByTagName("len-max");
            for(int i=0; i<lists.size(); i++){
                if(lists.at(i).parentNode().toElement().nodeName()=="card-add"&&lists.at(i).parentNode().parentNode().toElement().nodeName()=="unit"){
                    lists.at(i).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
                }
            }
        }
        else{
            lists = doc.elementsByTagName(it.key());
            if(lists.size()==0)
            {
                qDebug()<<"没有找到节点 "<<it.key();
            }
            else {
                lists.at(0).toElement().firstChild().setNodeValue(it.value());// 修改对应XML值。
            }
        }
    }
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        qDebug() << "open for add error!";
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}

/**
 * @brief XMLConfigReader::readCommonRule 读取公共参数
 * @return
 */
QMap<QString,QString> XMLConfigReader::readCommonRuleValue(QList<QString> queryList){
    qDebug()<<"调用 readCommonRuleValue 函数：";
    QString outputFilePath = "/Users/zhangxianjin/qtcode/testXml/rule/rule-common.xml";
    QMap<QString,QString> rtn_map;

    QFile file(outputFilePath);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug()<<"open for add error..." ;
    }
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug()<<"add setcontent error..." ;
            file.close();
    }
    file.close();
    QDomNodeList lists;

    for(int i=0; i<queryList.size(); i++){
        if("personNameLen_min"==queryList.at(i)){
            lists = doc.elementsByTagName("len-min");
            qDebug()<<"personNameLen_min lists size is "<<lists.size();
            for(int j=0; j<lists.size(); j++){
//                qDebug()<<"self is"<<lists.at(j).toElement().nodeName();
//                qDebug()<<"parent is "<<lists.at(j).parentNode().toElement().nodeName();
//                qDebug()<<"Grand is "<<lists.at(j).parentNode().parentNode().toElement().nodeName();
                if(lists.at(j).toElement().parentNode().toElement().nodeName()=="name"&&lists.at(j).toElement().parentNode().parentNode().toElement().nodeName()=="person"){
                    rtn_map.insert(queryList.at(i),lists.at(j).toElement().text());
                }
            }
        }
        else if("personNameLen_max"==queryList.at(i)){
            lists = doc.elementsByTagName("len-max");
            for(int j=0; j<lists.size(); j++){
                if(lists.at(j).toElement().parentNode().toElement().nodeName()=="name"&&lists.at(j).toElement().parentNode().parentNode().toElement().nodeName()=="person"){
                    rtn_map.insert(queryList.at(i),lists.at(j).toElement().text());
                }
            }
        }
        else if("personNamePermit_char"==queryList.at(i)){
            lists = doc.elementsByTagName("permit-char");
            for(int j=0; j<lists.size(); j++){
                if(lists.at(j).toElement().parentNode().toElement().nodeName()=="name"&&lists.at(j).toElement().parentNode().parentNode().toElement().nodeName()=="person"){
                    rtn_map.insert(queryList.at(i),lists.at(j).toElement().text());
                }
            }
        }
        else if("personCardtypeTime_interval"==queryList.at(i)){
            lists = doc.elementsByTagName("time-interval");
            for(int j=0; j<lists.size(); j++){
                if(lists.at(j).toElement().parentNode().toElement().nodeName()=="cardtype"&&lists.at(j).toElement().parentNode().parentNode().toElement().nodeName()=="person"){
                    rtn_map.insert(queryList.at(i),lists.at(j).toElement().text());
                }
            }
        }
        else if("personCard_numLen_min"==queryList.at(i)){
            lists = doc.elementsByTagName("len-min");
            for(int j=0; j<lists.size(); j++){
                if(lists.at(j).toElement().parentNode().toElement().nodeName()=="card-num"&&lists.at(j).toElement().parentNode().parentNode().toElement().nodeName()=="person"){
                    rtn_map.insert(queryList.at(i),lists.at(j).toElement().text());
                }
            }
        }
        else if("personCard_numLen_max"==queryList.at(i)){
            lists = doc.elementsByTagName("len-max");
            for(int j=0; j<lists.size(); j++){
                if(lists.at(j).toElement().parentNode().toElement().nodeName()=="card-num"&&lists.at(j).toElement().parentNode().parentNode().toElement().nodeName()=="person"){
                    rtn_map.insert(queryList.at(i),lists.at(j).toElement().text());
                }
            }
        }
        else if("personCard_addLen_min"==queryList.at(i)){
            lists = doc.elementsByTagName("len-min");
            for(int j=0; j<lists.size(); j++){
                if(lists.at(j).toElement().parentNode().toElement().nodeName()=="card-add"&&lists.at(j).toElement().parentNode().parentNode().toElement().nodeName()=="person"){
                    rtn_map.insert(queryList.at(i),lists.at(j).toElement().text());
                }
            }
        }
        else if("personCard_addLen_max"==queryList.at(i)){
            lists = doc.elementsByTagName("len-max");
            for(int j=0; j<lists.size(); j++){
                if(lists.at(j).toElement().parentNode().toElement().nodeName()=="card-add"&&lists.at(j).toElement().parentNode().parentNode().toElement().nodeName()=="person"){
                    rtn_map.insert(queryList.at(i),lists.at(j).toElement().text());
                }
            }
        }
        else if("unitNameLen_min"==queryList.at(i)){
            lists = doc.elementsByTagName("len-min");
            for(int j=0; j<lists.size(); j++){
                if(lists.at(j).toElement().parentNode().toElement().nodeName()=="name"&&lists.at(j).toElement().parentNode().parentNode().toElement().nodeName()=="unit"){
                    rtn_map.insert(queryList.at(i),lists.at(j).toElement().text());
                }
            }
        }
        else if("unitNameLen_max"==queryList.at(i)){
            lists = doc.elementsByTagName("len-max");
            for(int j=0; j<lists.size(); j++){
                if(lists.at(j).toElement().parentNode().toElement().nodeName()=="name"&&lists.at(j).toElement().parentNode().parentNode().toElement().nodeName()=="unit"){
                    rtn_map.insert(queryList.at(i),lists.at(j).toElement().text());
                }
            }
        }
        else if("unitCardtypeTime_interval"==queryList.at(i)){
            lists = doc.elementsByTagName("time-interval");
            for(int j=0; j<lists.size(); j++){
                if(lists.at(j).toElement().parentNode().toElement().nodeName()=="cardtype"&&lists.at(j).toElement().parentNode().parentNode().toElement().nodeName()=="unit"){
                    rtn_map.insert(queryList.at(i),lists.at(j).toElement().text());
                }
            }
        }
        else if("unitCard_numLen_min"==queryList.at(i)){
            lists = doc.elementsByTagName("len-min");
            for(int j=0; j<lists.size(); j++){
                if(lists.at(j).toElement().parentNode().toElement().nodeName()=="card-num"&&lists.at(j).toElement().parentNode().parentNode().toElement().nodeName()=="unit"){
                    rtn_map.insert(queryList.at(i),lists.at(j).toElement().text());
                }
            }
        }
        else if("unitCard_numLen_max"==queryList.at(i)){
            lists = doc.elementsByTagName("len-max");
            for(int j=0; j<lists.size(); j++){
                if(lists.at(j).toElement().parentNode().toElement().nodeName()=="card-num"&&lists.at(j).toElement().parentNode().parentNode().toElement().nodeName()=="unit"){
                    rtn_map.insert(queryList.at(i),lists.at(j).toElement().text());
                }
            }
        }
        else if("unitCard_addLen_min"==queryList.at(i)){
            lists = doc.elementsByTagName("len-min");
            for(int j=0; j<lists.size(); j++){
                if(lists.at(j).toElement().parentNode().toElement().nodeName()=="card-add"&&lists.at(j).toElement().parentNode().parentNode().toElement().nodeName()=="unit"){
                    rtn_map.insert(queryList.at(i),lists.at(j).toElement().text());
                }
            }
        }
        else if("unitCard_addLen_max"==queryList.at(i)){
            lists = doc.elementsByTagName("len-max");
            for(int j=0; j<lists.size(); j++){
                if(lists.at(j).toElement().parentNode().toElement().nodeName()=="card-add"&&lists.at(j).toElement().parentNode().parentNode().toElement().nodeName()=="unit"){
                    rtn_map.insert(queryList.at(i),lists.at(j).toElement().text());
                }
            }
        }
        else{
            lists = doc.elementsByTagName(queryList.at(i));
            if(lists.size()==0)
            {
                qDebug()<<"没有找到节点 "<<queryList.at(i);
            }
            else {
                qDebug()<<lists.at(0).toElement().text();
                rtn_map.insert(queryList.at(i),lists.at(0).toElement().text());
            }
        }
    }
    return rtn_map;
}
