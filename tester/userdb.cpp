#include "userdb.h"

UserDb::UserDb()
{

}

void UserDb::connDb(){
    if(db1.isOpen()){
        db1.databaseName();
    }
    else{
        db1 = QSqlDatabase::addDatabase("QSQLITE");

        db1.setHostName("localhost");
        db1.setDatabaseName("data.db1");
        db1.setUserName("king");
        db1.setPassword("123456");
    }
}

void UserDb::run()
{
    qDebug()<<"run begin";
    qDebug()<<"bool UserDb::insertDb(QString filename)"<<insertDb("D:\\test.txt");//gitcode\\build-tester-Desktop_Qt_5_10_0_MSVC2015_64bit-Debug\\data\\test_data.txt");
    QSqlQuery query;
    qDebug()<<"drop report:"<<query.exec("drop table report");
    qDebug()<<"create report:"<<query.exec("create table report(id int primary key,allData int,allNotReg int,formatNotRight int,fieldNotRight int,allOk int,personMobileFormatRight int,"
                                           "personMobileOwnerTypeNotReg int,personMobileOwnerNameNotReg int,personMobileOwnerNumNotReg int,personMobileOwnerAddNotReg int,personMobileOwnerNameNumNotReg int,"
                                           "personMobileOwnerNameAddNotReg int,personMobileOwnerNumAddNotReg int,personMobileOwnerNameNumAddNotReg int,personMobileOwnerTypeIllegal int,personMobileOwnerNameIllegal int,"
                                           "personMobileOwnerNumIllegal int,personMobileOwnerAddIllegal int,personMobileOwnerNameNumIllegal int,personMobileOwnerNameAddIllegal int,personMobileOwnerNumAddIllegal int,"
                                           "personMobileOwnerNameNumAddIllegal int,personFixedLegal int,personFixedOwnerTypeNotReg int,personFixedOwnerNameNotReg int,personFixedOwnerNumNotReg int,"
                                           "personFixedOwnerAddNotReg int,personFixedOwnerNameNumNotReg int,personFixedOwnerNameAddNotReg int,personFixedOwnerNumAddNotReg int,personFixedOwnerNameNumAddNotReg int,"
                                           "personFixedOwnerTypeIllegal int,personFixedOwnerNameIllegal int,personFixedOwnerNumIllegal int,personFixedOwnerAddIllegal int,personFixedOwnerNameNumIllegal int,"
                                           "personFixedOwnerNameAddIllegal int,personFixedOwnerNumAddIllegal int,personFixedOwnerNameNumAddIllegal int,personMobileAgentNotReg int,personFixedAgentNotReg int,"
                                           "personMobileAgentIllegal int,personFixedAgentIllegal int,unitMobileLegal int,unitMobileOwnerNotReg int,unitMobileAgentNotReg int,unitMobileUnitNotReg int,"
                                           "unitMobileOwnerAgentNotReg int,unitMobileOwnerUnitNotReg int,unitMobileAgentUnitNotReg int,unitMobileOwnerAgentUnitNotReg int,unitMobileOwnerIllegal int,"
                                           "unitMobileAgentIllegal int,unitMobileUnitIllegal int,unitMobileOwnerAgentIllegal int,unitMobileAgentUnitIllegal int,unitMobileOwnerAgentUnitIllegal int,"
                                           "unitFixedLegal int,unitFixedAgentNotReg int,unitFixedUnitNotReg int,unitFixedAgentUnitNotReg int,unitFixedAgentIllegal int,unitFixedUnitIllegal int,"
                                           "unitFixedAgentUnitIllegal int,tradeMobileLegal int,tradeMobileAgentNotReg int,tradeMobileAgentUnitNotReg int,tradeMobileLiableAgentNotReg int,"
                                           "tradeMobileLiableAgentUnitNotReg int,tradeMobileUnitNotReg int,tradeMobileLiableNotReg int,tradeMobileLiableUnitNotReg int,tradeMobileAgentIllegal int,"
                                           "tradeMobileAgentUnitIllegal int,tradeMobileLiableAgentIllegal int,tradeMobileLiableAgentUnitIllegal int,tradeMobileUnitIllegal int,tradeMobileLiableIllegal int,"
                                           "tradeMobileLiableUnitIllegal int,tradeFixedLegal int, tradeFixedAgentNotReg int,tradeFixedAgentUnitNotReg int,tradeFixedUnitNotReg int,tradeFixedAgentIllegal int,"
                                           "tradeFixedAgentUnitIllegal int,tradeFixedUnitIllegal int,personMobileOneCard int)");


    qDebug()<<"update allData is:"<<query.exec("update report set allData=(select count(*) from file)");
    query.prepare("select count(*) from file where col1='丁泽富'");
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

            qDebug()<<QString("id:%1    name:%2    age:%3").arg(id);//.arg(name).arg(age);
        }
    }
}

//创建数据库表
bool UserDb::createTable(){
//    connDb();
//    db1 = QSqlDatabase::addDatabase("QSQLITE");

//    db1.setHostName("localhost");
//    db1.setDatabaseName("data.db1");
//    db1.setUserName("king");
//    db1.setPassword("123456");
    QString sql = "create table file(id varchar primary key";
    for(int i=0;i<42;i++){
        sql.append(",col").append( QString::number(i+1, 10)).append(" varchar");
    }
    sql.append(")");
//    qDebug()<<"create table";
//    if (QSqlDatabase::contains("qt_sql_default_connection"))
//    {
//        db1 = QSqlDatabase::database("qt_sql_default_connection");
//        qDebug()<<QStringLiteral("数据库已打开。");
//    }
//    else
//    {
////        connDb();
//        qDebug()<<QStringLiteral("数据库连接出错。");
//        return false;
//    }

    QSqlQuery query;
    qDebug()<<"drop table"<<query.exec("drop table file");
    qDebug()<<"createTable()"<<sql;
    bool b = query.exec(sql);
//    db1.close();
    return b;
}

QString getCol(QString str){
    if(str!="null")
        return "'"+str+"'";
    else
        return str;
}

//文件入库
bool UserDb::insertDb(QString filename){
    qDebug()<<"insertDb";
    if(!fileIsExists(filename)){
        qDebug()<<"文件不存在。\n当前路径是：";
        qDebug()<< QDir::currentPath();
        return false;
    }
    if(!createTable()){
        qDebug()<<"库表创建不成功。";
        return false;
    }
//    QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE");

//    db1.setHostName("localhost");
//    db1.setDatabaseName("data.db1");
//    db1.setUserName("king");
//    db1.setPassword("123456");
//    if(!db1.open()){
//        writeLog("创建数据库连接出错。");
//        return false;
//    }

    QSqlQuery query;
    QFile file(filename);
    QTextCodec *code = QTextCodec::codecForName("UTF-8");//设置文件编码
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
                sql.append(","+getCol(col[i])+"");
            }
            sql.append(")");
            qDebug()<<"insertDb()"<<qPrintable(sql);
            qDebug()<<query.exec(sql);
        }while(!line.isEmpty());
    }
    else{
        qDebug()<<QStringLiteral("文件打开错误。");
    }
//    db1.close();
    return true;
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


