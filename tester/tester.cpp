#include "tester.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>


Tester::Tester(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/Images/logo.icns"));
    setWindowTitle(tr("实名制检测系统"));			//设置窗体标题
    resize(600,600);
    showWidget =new ShowWidget(this);		//设置文本显示窗体
    setCentralWidget(showWidget);

//    /* 创建动作、菜单、工具栏的函数 */
    createActions();
    createMenus();
    setupModel();
    setupView();
}

void Tester::createMenus()
{
    //文件菜单
    fileMenu =menuBar()->addMenu(tr("文件"));			//(a)
    fileMenu->addAction(openFileAction);				//(b)
    fileMenu->addAction(NewFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(setupAction);
    fileMenu->addAction(exitAction);

    //运行菜单
    runMenu =menuBar()->addMenu(tr("运行"));
    runMenu->addAction(startAction);
    runMenu->addAction(stopAction);

    //帮助菜单
    helpMenu =menuBar()->addMenu(tr("帮助"));
    helpMenu->addAction(helpAction);
    helpMenu->addAction(aboutAction);
}

void Tester::createToolBars()
{
//    //文件工具条
//    fileTool =addToolBar("File");					//(a)
//    fileTool->addAction(openFileAction);			//(b)
//    fileTool->addAction(NewFileAction);
//    fileTool->addAction(PrintTextAction);
//    fileTool->addAction(PrintImageAction);
//    //编辑工具条
//    zoomTool =addToolBar("Edit");
//    zoomTool->addAction(copyAction);
//    zoomTool->addAction(cutAction);
//    zoomTool->addAction(pasteAction);
//    zoomTool->addSeparator();
//    zoomTool->addAction(zoomInAction);
//    zoomTool->addAction(zoomOutAction);
}

void Tester::createActions()
{
    //“打开”动作
    openFileAction =new QAction(tr("打开"),this);//(a) QIcon("../../../open.png"), /users/zhangxianjin/qtcode/build-ImageProcessor-Desktop_Qt_5_8_0_clang_64bit-Debug
    openFileAction->setShortcut(tr("Ctrl+O"));                    //(b)
    openFileAction->setStatusTip(tr("打开一个文件"));               //(c)
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(showOpenFile()));
    //“新建”动作
    NewFileAction =new QAction(tr("新建"),this);//QIcon("../../../new.png"),
    NewFileAction->setShortcut(tr("Ctrl+N"));
    NewFileAction->setStatusTip(tr("新建一个文件"));
    connect(NewFileAction,SIGNAL(triggered()),this,SLOT(showNewFile()));
    //“设置”动作
    setupAction =new QAction(tr("设置"),this);//QIcon("../../../new.png"),
    setupAction->setShortcut(tr("Ctrl+S"));
    setupAction->setStatusTip(tr("设置运行参数"));
    connect(setupAction,SIGNAL(triggered()),this,SLOT(setupTester()));
    //“开始”动作
    startAction =new QAction(tr("开始"),this);//QIcon("../../../new.png"),
    startAction->setShortcut(tr("Ctrl+R"));
    startAction->setStatusTip(tr("开始检查"));
    connect(startAction,SIGNAL(triggered()),this,SLOT(startCheckFile()));
    //“停止”动作
    stopAction =new QAction(tr("停止"),this);//QIcon("../../../new.png"),
    stopAction->setShortcut(tr("Ctrl+C"));
    stopAction->setStatusTip(tr("停止检查"));
    connect(stopAction,SIGNAL(triggered()),this,SLOT(stopCheckFile()));
    //“退出”动作
    exitAction =new QAction(tr("退出"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("退出程序"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
    //“帮助”动作
    helpAction =new QAction(tr("帮助"),this);
    exitAction->setShortcut(tr("Ctrl+H"));
    helpAction->setStatusTip("程序使用说明");
    connect(helpAction,SIGNAL(triggered()),this,SLOT(helpTester()));
    //“关于”动作
    aboutAction =new QAction(tr("关于"),this);
    aboutAction->setStatusTip("关于本程序");
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(aboutTester()));
}


//显示新建文件对话框
void Tester::showNewFile()
{
    Tester *newTester =new Tester;
    newTester->show();
}
//显示打开文件对话框
void Tester::showOpenFile()
{
    QString name;
    name = QFileDialog::getOpenFileName(this,"打开",".","histogram files (*.txt)");
    if (!name.isEmpty())
          loadFile(name);
//    fileName =QFileDialog::getOpenFileName(this);
//    if(!fileName.isEmpty())
//    {
//        if(showWidget->text->document()->isEmpty())
//        {
//            loadFile(fileName);
//        }
//        else
//        {
//            Tester *newTester =new Tester;
//            newTester->show();
//            newTester->loadFile(fileName);
//        }
//    }
}

void Tester::setupModel()
{//设置列名
    model = new QStandardItemModel(10,41,this);
    //机主
    model->setHeaderData(0,Qt::Horizontal,tr("姓名"));
    model->setHeaderData(1,Qt::Horizontal,tr("证件类型"));
    model->setHeaderData(2,Qt::Horizontal,tr("证件号码"));
    model->setHeaderData(3,Qt::Horizontal,tr("证件地址"));
    model->setHeaderData(4,Qt::Horizontal,tr("通讯地址"));
    model->setHeaderData(5,Qt::Horizontal,tr("装机地址"));
    //代（经）办人
    model->setHeaderData(6,Qt::Horizontal,tr("姓名"));
    model->setHeaderData(7,Qt::Horizontal,tr("证件类型"));
    model->setHeaderData(8,Qt::Horizontal,tr("证件号码"));
    model->setHeaderData(9,Qt::Horizontal,tr("证件地址"));
    model->setHeaderData(10,Qt::Horizontal,tr("通讯地址"));
    //责任人
    model->setHeaderData(11,Qt::Horizontal,tr("姓名"));
    model->setHeaderData(12,Qt::Horizontal,tr("证件类型"));
    model->setHeaderData(13,Qt::Horizontal,tr("证件号码"));
    model->setHeaderData(14,Qt::Horizontal,tr("证件地址"));
    model->setHeaderData(15,Qt::Horizontal,tr("通讯地址"));
    //单位或行业
    model->setHeaderData(16,Qt::Horizontal,tr("单位名称"));
    model->setHeaderData(17,Qt::Horizontal,tr("单位证件号码"));
    model->setHeaderData(18,Qt::Horizontal,tr("单位证件类型"));
    model->setHeaderData(19,Qt::Horizontal,tr("单位证件地址"));
    model->setHeaderData(20,Qt::Horizontal,tr("单位通讯地址"));
    model->setHeaderData(21,Qt::Horizontal,tr("单位装机地址"));
    //电话卡信息
    model->setHeaderData(22,Qt::Horizontal,tr("MSISDN号码"));
    model->setHeaderData(23,Qt::Horizontal,tr("登记激活时间"));
    model->setHeaderData(24,Qt::Horizontal,tr("号码状态"));
    model->setHeaderData(25,Qt::Horizontal,tr("用户业务类型"));
    //营业网点信息
    model->setHeaderData(26,Qt::Horizontal,tr("网点编号"));
    model->setHeaderData(27,Qt::Horizontal,tr("网点名称"));
    model->setHeaderData(28,Qt::Horizontal,tr("网点地址"));
    model->setHeaderData(29,Qt::Horizontal,tr("网点所在区县"));
    model->setHeaderData(30,Qt::Horizontal,tr("网点类型"));
    model->setHeaderData(31,Qt::Horizontal,tr("开通商编号"));
    //支付信息
    model->setHeaderData(32,Qt::Horizontal,tr("交易流水账单号"));
    model->setHeaderData(33,Qt::Horizontal,tr("交易平台用户账号"));
    model->setHeaderData(34,Qt::Horizontal,tr("用户交易的银行卡卡号或第三方支付账号名称"));
    model->setHeaderData(35,Qt::Horizontal,tr("支付时间"));
    model->setHeaderData(36,Qt::Horizontal,tr("机主证件电子复印件图片名称"));
    model->setHeaderData(37,Qt::Horizontal,tr("代办人证件电子复印件图片名称"));
    //用户类型
    model->setHeaderData(38,Qt::Horizontal,tr("用户类型"));
    //渠道类型
    model->setHeaderData(39,Qt::Horizontal,tr("渠道类型"));
    //使用状态
    model->setHeaderData(40,Qt::Horizontal,tr("使用状态"));
    //预留字段
    model->setHeaderData(41,Qt::Horizontal,tr("预留字段"));

}

void Tester::setupView()
{

    table = new QTableView;			//新建一个QTableView对象
    table->setModel(model);			//为QTableView对象设置相同的Model
    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);//(a)
    table->setSelectionModel(selectionModel);
    connect(selectionModel,SIGNAL(selectionChanged(QItemSelection, QItemSelection)),table,SLOT(selectionChanged(QItemSelection,QItemSelection)));									//(b)
    splitter = new QSplitter;
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(table);
    setCentralWidget(splitter);

}

//装载文件到容器中
void Tester::loadFile(QString filename)
{
    QTextCodec *code = QTextCodec::codecForName("GBK");//设置文件编码
    if (!filename.isEmpty())
    {
        QFile file(filename);
         if (file.open(QFile::ReadOnly | QFile::Text))
         {
             QTextStream stream(&file);
             stream.setCodec(code);
             QString line;
             model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());
             int row = 0;
             do
             {
                 line = stream.readLine();

                 if (!line.isEmpty())
                 {
                        model->insertRows(row, 1, QModelIndex());
                        QStringList pieces = line.split("||", QString::SkipEmptyParts);
                        for(int i=0; i<col_num; i++)//循环填充所有列，该值在tester.h中定义。
                        {
                            model->setData(model->index(row, i, QModelIndex()), pieces.value(i));

                        }
                        row++;//换行
                        if(row==row_num){//预览部分只加载row_num行，该值在tester.h中定义。
                            break;
                        }
                 }
             } while (!line.isEmpty());
           file.close();
           processfilename = filename;
         }
    }
}


void Tester::startCheckFile()
{
    QTextCodec *code = QTextCodec::codecForName("GBK");//设置文件编码
    statusBar()->showMessage("start process file", 3000);

//    QList<QList<QString>> users = userfile->insertList(processfilename);
//    qDebug()<<"行数是："<<users.size();
//    userfile->analysisData(users);//传统方法

    userfile->insertDb(processfilename);
    statusBar()->showMessage("all data insert table.", 3000);

//    QList<QString> users = userfile->readTable("select col1,col2 from file where col1= '丁泽富'");
    QList<QString> users = userfile->readTable("select count(*),col1,col3 from file group by col1,col3");
    for(int i=0;i<users.size();i++){
        qDebug()<< users.at(i)<<"\\n";
    }

//    printf("start process file");
//    std::cout<< processfilename.toStdString();

//    QFile file(processfilename);
//    QTextStream stream(&file);
//    stream.setCodec(code);
//    QString buffer;
//    QString cols[col_num] = new QString[col_num]{};
//    if(file.open(QIODevice::ReadOnly))
//    {
//        while(stream.readLineInto(&buffer,2048)){
//            cols = buffer.split('||');
//            qDebug()<<buffer;
//            qDebug()<<cols[1];
//        }
//    }
//    file.close();
}

void Tester::stopCheckFile()
{
    statusBar()->showMessage("stop process file", 3000);
//    printf("stop process file");
//    std::cout<< processfilename.toStdString();
}

void Tester::setupTester()
{
    Setup *newSetup =new Setup;
    newSetup->show();
}

void Tester::aboutTester()
{
//    About *newAbout =new About;
//    newAbout->show();
//    label->setText(tr("About Message Box"));
    QMessageBox::about(this, tr("About消息框"),tr("实名制检测系统\n "
                                                  "Version 1.0 \n"
                                                  "本系统为实名制检查工具。"));
//    return;
}

void Tester::helpTester()
{

}

Tester::~Tester()
{

}

