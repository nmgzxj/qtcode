#include "report.h"
#include "ui_report.h"
#include "connection.h"
#include "userfile.h"

Report::Report(QWidget *parent)
    :QDialog(parent),
    ui(new Ui::Report)
{
    ui->setupUi(this);
    QSqlQuery query;

//    //创建报表
//    qDebug()<<"drop report:"<<query.exec("drop table report");
//    qDebug()<<"create report:"<<query.exec("create table report(id int primary key,allData int,allNotReg int,formatNotRight int,fieldNotRight int,allOk int,personMobileFormatRight int,"
//                                           "personMobileOwnerTypeNotReg int,personMobileOwnerNameNotReg int,personMobileOwnerNumNotReg int,personMobileOwnerAddNotReg int,personMobileOwnerNameNumNotReg int,"
//                                           "personMobileOwnerNameAddNotReg int,personMobileOwnerNumAddNotReg int,personMobileOwnerNameNumAddNotReg int,personMobileOwnerTypeIllegal int,personMobileOwnerNameIllegal int,"
//                                           "personMobileOwnerNumIllegal int,personMobileOwnerAddIllegal int,personMobileOwnerNameNumIllegal int,personMobileOwnerNameAddIllegal int,personMobileOwnerNumAddIllegal int,"
//                                           "personMobileOwnerNameNumAddIllegal int,personFixedLegal int,personFixedOwnerTypeNotReg int,personFixedOwnerNameNotReg int,personFixedOwnerNumNotReg int,"
//                                           "personFixedOwnerAddNotReg int,personFixedOwnerNameNumNotReg int,personFixedOwnerNameAddNotReg int,personFixedOwnerNumAddNotReg int,personFixedOwnerNameNumAddNotReg int,"
//                                           "personFixedOwnerTypeIllegal int,personFixedOwnerNameIllegal int,personFixedOwnerNumIllegal int,personFixedOwnerAddIllegal int,personFixedOwnerNameNumIllegal int,"
//                                           "personFixedOwnerNameAddIllegal int,personFixedOwnerNumAddIllegal int,personFixedOwnerNameNumAddIllegal int,personMobileAgentNotReg int,personFixedAgentNotReg int,"
//                                           "personMobileAgentIllegal int,personFixedAgentIllegal int,unitMobileLegal int,unitMobileOwnerNotReg int,unitMobileAgentNotReg int,unitMobileUnitNotReg int,"
//                                           "unitMobileOwnerAgentNotReg int,unitMobileOwnerUnitNotReg int,unitMobileAgentUnitNotReg int,unitMobileOwnerAgentUnitNotReg int,unitMobileOwnerIllegal int,"
//                                           "unitMobileAgentIllegal int,unitMobileUnitIllegal int,unitMobileOwnerAgentIllegal int,unitMobileAgentUnitIllegal int,unitMobileOwnerAgentUnitIllegal int,"
//                                           "unitFixedLegal int,unitFixedAgentNotReg int,unitFixedUnitNotReg int,unitFixedAgentUnitNotReg int,unitFixedAgentIllegal int,unitFixedUnitIllegal int,"
//                                           "unitFixedAgentUnitIllegal int,tradeMobileLegal int,tradeMobileAgentNotReg int,tradeMobileAgentUnitNotReg int,tradeMobileLiableAgentNotReg int,"
//                                           "tradeMobileLiableAgentUnitNotReg int,tradeMobileUnitNotReg int,tradeMobileLiableNotReg int,tradeMobileLiableUnitNotReg int,tradeMobileAgentIllegal int,"
//                                           "tradeMobileAgentUnitIllegal int,tradeMobileLiableAgentIllegal int,tradeMobileLiableAgentUnitIllegal int,tradeMobileUnitIllegal int,tradeMobileLiableIllegal int,"
//                                           "tradeMobileLiableUnitIllegal int,tradeFixedLegal int, tradeFixedAgentNotReg int,tradeFixedAgentUnitNotReg int,tradeFixedUnitNotReg int,tradeFixedAgentIllegal int,"
//                                           "tradeFixedAgentUnitIllegal int,tradeFixedUnitIllegal int,personMobileOneCard int)");



//    qDebug()<<"delete report is:"<<query.exec("delete report");
//    qDebug()<<"insert report data is:"<<query.exec("insert into report(id,allData,allNotReg,formatNotRight) values (1,2,3,4)");
//    UserFile* uf;
//    uf = new UserFile;
////  todo  uf->insertDb("/Users/zhangxianjin/qtcode/test_data.txt");

//    qDebug()<<"report is:"<<query.exec("select * from report");
//    qDebug()<<"report next is:"<<query.next();
        query.prepare("select * from report ");
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }
        else
        {
            while(query.next())
            {
                int id = query.value(0).toInt();
    //            QString name = query.value(1).toString();
    //            int age = query.value(2).toInt();
                int j=0;//i行j列
                for(int i=0;i<100;i++){
                    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));
                }
                qDebug()<<QString("all:%1    personMobileOneCard:%2    age:%3").arg(id);//.arg(name).arg(age);
            }
            qDebug()<<"get data is over.";
        }

//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerTypeNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNumNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerAddNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameNumNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameAddNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNumAddNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameNumAddNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerTypeNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNumNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerAddNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameNumNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameAddNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNumAddNotReg,10)));
//    ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(i).toString()));//QString::number(personMobileOwnerNameNumAddNotReg,10)));
}

Report::~Report()
{
    delete ui;
}
