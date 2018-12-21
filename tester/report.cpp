#include "report.h"
#include <QString>
#include <QStandardItemModel>
#include <QStringList>

Report::Report(QWidget *parent)
    :QTableWidget (parent)
{
//    QTableWidget *tableWidget = new QTableWidget;
//    //ui->setupUi(this);
//    init();
    this->setWindowTitle("测试结果");
    this->resize(900, 750);
    this->setRowCount(110);
    this->setColumnCount(3);
    QStringList header;
    header.append("统计项");
    header.append("值");
    header.append("说明");
    this->setHorizontalHeaderLabels(header);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //this->resizeColumnsToContents();
    this->setColumnWidth(0,400);
    this->setColumnWidth(1,100);
    this->setColumnWidth(2,400);
//    setTableValue();


//    QSqlQuery query;

//        query.prepare("select * from report ");
//        if(!query.exec())
//        {
//            qDebug()<<query.lastError();
//        }
//        else
//        {
//            while(query.next())
//            {
////                int id = query.value(0).toInt();
//                int j=0;//i行j列
//                for(int i=0;i<100;i++){
//                    this->setItem(i, j,new QTableWidgetItem(query.value(i+1).toString()));
//                }

//            }
//            qDebug()<<"get report data is finished.";
//        }

}

void Report::init(){
    qDebug()<<"init Report vars";
    personMobileOwnerNameNotReg = 0;//个人移动用户-机主姓名未登记
    personMobileOwnerTypeNotReg = 0;//个人移动用户-机主证件类型未登记
    personMobileOwnerNumNotReg = 0;//个人移动用户机-主证件号码未登记
    personMobileOwnerAddNotReg = 0;//个人移动用户-机主证件地址未登记
    personMobileOwnerNameNumNotReg = 0;//个人移动用户-机主姓名证件号码未登记
    personMobileOwnerNameAddNotReg = 0;//个人移动用户-机主姓名证件地址未登记
    personMobileOwnerNumAddNotReg = 0;//个人移动用户-机主证件号码地址未登记
    personMobileOwnerNameNumAddNotReg = 0;//个人移动用户-机主姓名证件号码地址未登记

    personFixedOwnerNameNotReg = 0;//个人固话用户-机主姓名未登记
    personFixedOwnerTypeNotReg = 0;//个人固话用户-机主证件类型未登记
    personFixedOwnerNumNotReg = 0;//个人固话用户-机主证件号码未登记
    personFixedOwnerAddNotReg = 0;//个人固话用户-机主证件地址未登记
    personFixedOwnerNameNumNotReg = 0;//个人固话用户-机主姓名证件号码未登记
    personFixedOwnerNameAddNotReg = 0;//个人固话用户-机主姓名证件地址未登记
    personFixedOwnerNumAddNotReg = 0;//个人固话用户-机主证件号码地址未登记
    personFixedOwnerNameNumAddNotReg = 0;//个人固话用户-机主姓名证件号码地址未登记

    unitMobileOwnerNotReg = 0;//单位移动用户-使用人信息未登记
    unitMobileAgentNotReg = 0;//单位移动用户-代办人信息未登记
    unitMobileUnitNotReg = 0;//单位移动用户-单位信息未登记
    unitMobileOwnerAgentNotReg = 0;//单位移动用户-使用人代办人信息未登记
    unitMobileOwnerUnitNotReg = 0;//单位移动用户-使用人单位信息未登记
    unitMobileAgentUnitNotReg = 0;//单位移动用户-代办人单位信息未登记
    unitMobileOwnerAgentUnitAddNotReg = 0;//单位移动用户-单位信息未登记

    unitFixedOwnerNotReg = 0;//单位固话用户-使用人信息未登记
    unitFixedAgentNotReg = 0;//单位固话用户-代办人信息未登记
    unitFixedUnitNotReg = 0;//单位固话用户-单位信息未登记
    unitFixedOwnerAgentNotReg = 0;//单位固话用户-使用人代办人信息未登记
    unitFixedOwnerUnitNotReg = 0;//单位固话用户-使用人单位信息未登记
    unitFixedAgentUnitNotReg = 0;//单位固话用户-代办人单位信息未登记
    unitFixedOwnerAgentUnitNotReg = 0;//单位固话用户-单位信息未登记

    tradeMobileAgentNotReg = 0;//行业移动用户-单位信息未登记
    tradeMobileUnitNotReg = 0;//行业移动用户-单位信息未登记
    tradeMobileLiableNotReg = 0;//行业移动用户-单位信息未登记
    tradeMobileAgentUnitNotReg = 0;//行业移动用户-单位信息未登记
    tradeMobileLiableAgentNotReg = 0;//行业移动用户-单位信息未登记
    tradeMobileLiableUnitNotReg = 0;//行业移动用户-单位信息未登记
    tradeMobileLiableAgentUnitAddNotReg = 0;//行业移动用户-单位信息未登记
    tradeFixedAgentNotReg = 0;//行业移动用户-单位信息未登记
    tradeFixedUnitNotReg = 0;//行业移动用户-单位信息未登记
    tradeFixedAgentUnitNotReg = 0;//行业移动用户-单位信息未登记

    allData = 0;
    allNotReg = 0;
    allNok = 0;
    formatNok = 0;
    fieldNok = 0;
    allOk = 0;
    personMobileOk = 0;
    personMobileOwnerTypeNok = 0;
    personMobileOwnerNameNok = 0;
    personMobileOwnerNumNok = 0;
    personMobileOwnerAddNok = 0;
    personMobileOwnerNameNumNok = 0;
    personMobileOwnerNameAddNok = 0;
    personMobileOwnerNumAddNok = 0;
    personMobileOwnerNameNumAddNok = 0;
    personFixedOk = 0;
    personFixedOwnerTypeNok = 0;
    personFixedOwnerNameNok = 0;
    personFixedOwnerNumNok = 0;
    personFixedOwnerAddNok = 0;
    personFixedOwnerNameNumNok = 0;
    personFixedOwnerNameAddNok = 0;
    personFixedOwnerNumAddNok = 0;
    personFixedOwnerNameNumAddNok = 0;
    personMobileAgentNotReg = 0;
    personFixedAgentNotReg = 0;
    personMobileAgentNok = 0;
    personFixedAgentNok = 0;
    unitMobileOk = 0;
    unitMobileOwnerAgentUnitNotReg = 0;
    unitMobileOwnerNok = 0;
    unitMobileOwnerUnitNok = 0;
    unitMobileAgentNok = 0;
    unitMobileUnitNok = 0;
    unitMobileOwnerAgentNok = 0;
    unitMobileAgentUnitNok = 0;
    unitMobileOwnerAgentUnitNok = 0;
    unitFixedOk = 0;
    unitFixedAgentNok = 0;
    unitFixedUnitNok = 0;
    unitFixedAgentUnitNok = 0;
    tradeMobileOk = 0;
    tradeMobileLiableAgentUnitNotReg = 0;
    tradeMobileAgentNok = 0;
    tradeMobileAgentUnitNok = 0;
    tradeMobileLiableAgentNok = 0;
    tradeMobileLiableAgentUnitNok = 0;
    tradeMobileUnitNok = 0;
    tradeMobileLiableNok = 0;
    tradeMobileLiableUnitNok = 0;
    tradeFixedOk = 0;
    tradeFixedOwnerNotReg = 0;
    tradeFixedOwnerNok = 0;
    tradeFixedAgentNok = 0;
    tradeFixedAgentUnitNok = 0;
    tradeFixedUnitNok = 0;
    tradeFixedAgentLiableNotReg = 0;
    tradeFixedLiableUnitNotReg = 0;
    tradeFixedAgentLiableUnitNotReg = 0;
    tradeFixedAgentLiableNok = 0;
    tradeFixedLiableUnitNok = 0;
    tradeFixedAgentLiableUnitNok = 0;
    personMobileOneCard= 0;
    leaveNet = 0;
    tradeFixedLiableNotReg =0;
    unitFixedUnitLiableNotReg = 0;
    unitFixedUnitLiableNok = 0;
    unitMobileUnitLiableNotReg = 0;
    unitMobileUnitLiableNok = 0;
    tradeFixedLiableNok = 0;
    onecardMultiName = 0;
    onecardFiveCode = 0;
}

void Report::setTableValue(QString reportFileName){
    QFile file(reportFileName);
    file.open(QFile::Append);
    QTextStream out(&file);
    out.setCodec("GBK");
    out<<"统计项,数字"<<endl;
    int i=0;
    this->setItem(i, 0, new QTableWidgetItem("总量"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->allData, 10)));
    this->setItem(i, 2, new QTableWidgetItem("全部数据行数"));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;

    this->setItem(i, 0, new QTableWidgetItem("全量未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->allNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;

    this->setItem(i, 0, new QTableWidgetItem("全量不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->allNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;

    this->setItem(i, 0, new QTableWidgetItem("格式异常数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->formatNok)));
    this->setItem(i, 2, new QTableWidgetItem("列数不符"));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;

    this->setItem(i, 0, new QTableWidgetItem("字段异常数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->fieldNok)));
    this->setItem(i, 2, new QTableWidgetItem("时间等格式异常"));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;

    this->setItem(i, 0, new QTableWidgetItem("全量合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->allOk,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-形式合规数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOk,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件类型未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerTypeNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件号码未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNumNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名&证件号码未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameNumAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名&证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件号码&证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNumAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名&证件号码&证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameNumAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件类型校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerTypeNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件号码校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNumNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名&证件号码校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameNumNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名&证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-证件号码&证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNumAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-用户姓名&证件号码&证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileOwnerNameNumAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-形式合规数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOk,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件类型未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerTypeNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件号码未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNumNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名&证件号码未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameNumNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名&证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件号码&证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNumAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名&证件号码&证件地址未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameNumAddNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件类型校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerTypeNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件号码校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNumNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名&证件号码校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameNumNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名&证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-证件号码&证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNumAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-用户姓名&证件号码&证件地址校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedOwnerNameNumAddNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-代办人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileAgentNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-代办人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedAgentNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动用户-代办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personMobileAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人固话用户-代办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->personFixedAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-形式合规数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOk,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-经办人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileAgentNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人&经办人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerAgentNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-经办人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileAgentUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人&经办人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerAgentUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-经办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人&经办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-经办人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileAgentUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动用户-使用人&经办人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileOwnerAgentUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话用户-形式合规数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedOk,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话用户-单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话用户-经办人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedAgentUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话用户-经办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话用户-单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话用户-经办人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedAgentUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-形式合规数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileOk,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-经办人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileAgentNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-经办人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileAgentUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人&经办人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableAgentNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人&经办人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableAgentUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-经办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-经办人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileAgentUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人&经办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人&经办人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableAgentUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业移动应用-责任人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeMobileLiableUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-形式合规数据"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedOk,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;

    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-使用人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedOwnerNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-使用人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-责任人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedLiableNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;

    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人&责任人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentLiableNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-责任人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedLiableUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人&责任人&单位信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentLiableUnitNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人&责任人信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentLiableNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-责任人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedLiableUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-经办人&责任人&单位信息校验不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedAgentLiableUnitNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("个人移动一证五卡不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(0,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("行业固话应用-责任人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->tradeFixedLiableNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话应用-单位&责任人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedUnitLiableNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位固话应用-责任人信息不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitFixedUnitLiableNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动-责任人信息未登记"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileUnitLiableNotReg,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("单位移动应用-责任人信息不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->unitMobileUnitLiableNok,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("一证多名不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->onecardMultiName,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;
    this->setItem(i, 0, new QTableWidgetItem("一证超五号不合规"));
    this->setItem(i, 1, new QTableWidgetItem(QString::number(this->onecardFiveCode,10)));
    this->setItem(i, 2, new QTableWidgetItem(""));
    out<<this->item(i,0)->text()<<","<<this->item(i,1)->text()<<endl;
    i++;

    file.close();
}
Report::~Report()
{
   // delete ui;
}
