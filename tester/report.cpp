#include "report.h"
#include "ui_report.h"
//#include "userfile.h"

Report::Report(QWidget *parent)
    :QDialog(parent),
    ui(new Ui::Report)
{
    ui->setupUi(this);
    QSqlQuery query;

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
                for(int i=1;i<100;i++){
                    ui->tableWidget->setItem(i-1, j, new QTableWidgetItem(query.value(i).toString()));
                }
                qDebug()<<QString("all:%1 ").arg(id);
            }
            qDebug()<<"get report data is over.";
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
