#include "tester.h"
#include "progressdlg.h"
#include "connection.h"
#include "logindialog.h"
#include "gencode.h"
#include "userfile.h"

#include <QApplication>

int main(int argc, char *argv[])
{

//    ///代码生成器
//////    GenCode g;
//////            g.test();

///// 命令行方式文件处理
//    UserFile* uf = new UserFile();
////    uf->insertDb("../../../test_data.txt");
////    uf->readTable("select * from file");
////    uf->readTable("delete from file");
//    uf->analysisData(uf->insertList("../../../test_data.txt"));

///    图形界面
    QApplication a(argc, argv);
//    ProgressDlg w;
    if(!createConnection()||!createXml())
    {
        return 0;
    }
    Tester w;
    LoginDialog dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        w.show();

        return a.exec();
    }
    else
    {
        return 0;
    }
}
