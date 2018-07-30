#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "report.h"
#include "tester.h"


Tester::Tester(QWidget *parent)
    : QMainWindow(parent)
{
//    setWindowIcon(QIcon(":/Images/logo.icns"));
    setWindowTitle(QStringLiteral("实名制检测系统"));			//设置窗体标题
    resize(600,600);
    showWidget =new ShowWidget(this);		//设置文本显示窗体
    setCentralWidget(showWidget);

//    /* 创建动作、菜单、工具栏的函数 */
    createActions();
    createMenus();
    setupModel();
    setupView();
    userfile = new UserFile();
}

void Tester::createMenus()
{
    //文件菜单
    fileMenu =menuBar()->addMenu(QStringLiteral("文件"));			//(a)
    fileMenu->addAction(openFileAction);				//(b)
    fileMenu->addAction(NewFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(setupAction);
    fileMenu->addAction(exitAction);

    //运行菜单
    runMenu =menuBar()->addMenu(QStringLiteral("运行1"));
    runMenu->addAction(startAction1);
    runMenu->addAction(stopAction);
    runMenu =menuBar()->addMenu(QStringLiteral("运行2"));
    runMenu->addAction(startAction2);
    runMenu->addAction(stopAction);

    //帮助菜单
    helpMenu =menuBar()->addMenu(QStringLiteral("帮助"));
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
    openFileAction =new QAction(QStringLiteral("打开"),this);//QIcon(":/Images/images/open.png"), (a) /users/zhangxianjin/qtcode/build-ImageProcessor-Desktop_Qt_5_8_0_clang_64bit-Debug
    openFileAction->setShortcut(QStringLiteral("Ctrl+O"));                    //(b)
    openFileAction->setStatusTip(QStringLiteral("打开一个文件"));               //(c)
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(showOpenFile()));
    //“新建”动作
    NewFileAction =new QAction(QStringLiteral("新建"),this);//,QIcon(":/Images/images/new.png"),
    NewFileAction->setShortcut(QStringLiteral("Ctrl+N"));
    NewFileAction->setStatusTip(QStringLiteral("新建一个文件"));
    connect(NewFileAction,SIGNAL(triggered()),this,SLOT(showNewFile()));
    //“设置”动作
    setupAction =new QAction(QStringLiteral("设置"),this);//QIcon("../../../new.png"),
    setupAction->setShortcut(QStringLiteral("Ctrl+S"));
    setupAction->setStatusTip(QStringLiteral("设置运行参数"));
    connect(setupAction,SIGNAL(triggered()),this,SLOT(setupTester()));
    //“开始1”动作
    startAction1 =new QAction(QStringLiteral("开始1"),this);//QIcon("../../../new.png"),
    startAction1->setShortcut(QStringLiteral("Ctrl+R"));
    startAction1->setStatusTip(QStringLiteral("开始检查"));
    connect(startAction1,SIGNAL(triggered()),this,SLOT(startCheckFile1()));
    //“开始2”动作
    startAction2 =new QAction(QStringLiteral("开始2"),this);//QIcon("../../../new.png"),
    startAction2->setShortcut(QStringLiteral("Ctrl+R"));
    startAction2->setStatusTip(QStringLiteral("开始检查"));
    connect(startAction2,SIGNAL(triggered()),this,SLOT(startCheckFile2()));
    //“停止”动作
    stopAction =new QAction(QStringLiteral("停止"),this);//QIcon("../../../new.png"),
    stopAction->setShortcut(QStringLiteral("Ctrl+C"));
    stopAction->setStatusTip(QStringLiteral("停止检查"));
    connect(stopAction,SIGNAL(triggered()),this,SLOT(stopCheckFile()));
    //“退出”动作
    exitAction =new QAction(QStringLiteral("退出"),this);
    exitAction->setShortcut(QStringLiteral("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出程序"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
    //“帮助”动作
    helpAction =new QAction(QStringLiteral("帮助"),this);
    exitAction->setShortcut(QStringLiteral("Ctrl+H"));
    helpAction->setStatusTip("程序使用说明");
    connect(helpAction,SIGNAL(triggered()),this,SLOT(helpTester()));
    //“关于”动作
    aboutAction =new QAction(QStringLiteral("关于"),this);
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
    name = QFileDialog::getOpenFileName(this,QStringLiteral("打开"),".","histogram files (*.txt)");
    if (!name.isEmpty()){
        processfilename = name;
          loadFile(name);
    }
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
    model->setHeaderData(0,Qt::Horizontal,QStringLiteral("姓名"));
    model->setHeaderData(1,Qt::Horizontal,QStringLiteral("证件类型"));
    model->setHeaderData(2,Qt::Horizontal,QStringLiteral("证件号码"));
    model->setHeaderData(3,Qt::Horizontal,QStringLiteral("证件地址"));
    model->setHeaderData(4,Qt::Horizontal,QStringLiteral("通讯地址"));
    model->setHeaderData(5,Qt::Horizontal,QStringLiteral("装机地址"));
    //代（经）办人
    model->setHeaderData(6,Qt::Horizontal,QStringLiteral("姓名"));
    model->setHeaderData(7,Qt::Horizontal,QStringLiteral("证件类型"));
    model->setHeaderData(8,Qt::Horizontal,QStringLiteral("证件号码"));
    model->setHeaderData(9,Qt::Horizontal,QStringLiteral("证件地址"));
    model->setHeaderData(10,Qt::Horizontal,QStringLiteral("通讯地址"));
    //责任人
    model->setHeaderData(11,Qt::Horizontal,QStringLiteral("姓名"));
    model->setHeaderData(12,Qt::Horizontal,QStringLiteral("证件类型"));
    model->setHeaderData(13,Qt::Horizontal,QStringLiteral("证件号码"));
    model->setHeaderData(14,Qt::Horizontal,QStringLiteral("证件地址"));
    model->setHeaderData(15,Qt::Horizontal,QStringLiteral("通讯地址"));
    //单位或行业
    model->setHeaderData(16,Qt::Horizontal,QStringLiteral("单位名称"));
    model->setHeaderData(17,Qt::Horizontal,QStringLiteral("单位证件号码"));
    model->setHeaderData(18,Qt::Horizontal,QStringLiteral("单位证件类型"));
    model->setHeaderData(19,Qt::Horizontal,QStringLiteral("单位证件地址"));
    model->setHeaderData(20,Qt::Horizontal,QStringLiteral("单位通讯地址"));
    model->setHeaderData(21,Qt::Horizontal,QStringLiteral("单位装机地址"));
    //电话卡信息
    model->setHeaderData(22,Qt::Horizontal,QStringLiteral("MSISDN号码"));
    model->setHeaderData(23,Qt::Horizontal,QStringLiteral("登记激活时间"));
    model->setHeaderData(24,Qt::Horizontal,QStringLiteral("号码状态"));
    model->setHeaderData(25,Qt::Horizontal,QStringLiteral("用户业务类型"));
    //营业网点信息
    model->setHeaderData(26,Qt::Horizontal,QStringLiteral("网点编号"));
    model->setHeaderData(27,Qt::Horizontal,QStringLiteral("网点名称"));
    model->setHeaderData(28,Qt::Horizontal,QStringLiteral("网点地址"));
    model->setHeaderData(29,Qt::Horizontal,QStringLiteral("网点所在区县"));
    model->setHeaderData(30,Qt::Horizontal,QStringLiteral("网点类型"));
    model->setHeaderData(31,Qt::Horizontal,QStringLiteral("开通商编号"));
    //支付信息
    model->setHeaderData(32,Qt::Horizontal,QStringLiteral("交易流水账单号"));
    model->setHeaderData(33,Qt::Horizontal,QStringLiteral("交易平台用户账号"));
    model->setHeaderData(34,Qt::Horizontal,QStringLiteral("用户交易的银行卡卡号或第三方支付账号名称"));
    model->setHeaderData(35,Qt::Horizontal,QStringLiteral("支付时间"));
    model->setHeaderData(36,Qt::Horizontal,QStringLiteral("机主证件电子复印件图片名称"));
    model->setHeaderData(37,Qt::Horizontal,QStringLiteral("代办人证件电子复印件图片名称"));
    //用户类型
    model->setHeaderData(38,Qt::Horizontal,QStringLiteral("用户类型"));
    //渠道类型
    model->setHeaderData(39,Qt::Horizontal,QStringLiteral("渠道类型"));
    //使用状态
    model->setHeaderData(40,Qt::Horizontal,QStringLiteral("使用状态"));
    //预留字段
    model->setHeaderData(41,Qt::Horizontal,QStringLiteral("预留字段"));

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
         }
    }
}


//创建线程
void Tester::startObjThread()
{
//    if(m_Thread==NULL)
//    {
//        qDebug()<<"m_Thread"<<m_Thread;
//        return;
//    }
    //    QList<QList<QString>> users = userfile->insertList(processfilename);
    //    qDebug()<<"行数是："<<users.size();
    //    userfile->analysisData(users);//传统方法

    //    userfile->insertDb(processfilename);
//
     userfile->printMessage();
    userfile->setFileName(processfilename);
    qDebug()<<"processfilename is "<<processfilename;
        qDebug() << "Main Thread : " << QThread::currentThreadId();
    userfile->printMessage();
    qDebug()<<QStringLiteral("启动文件处理线程");


    m_Thread = new QThread();
    userfile->moveToThread(m_Thread);
    connect(m_Thread,&QThread::finished,m_Thread,&QObject::deleteLater);
    connect(m_Thread,&QThread::finished,userfile,&QObject::deleteLater);
    connect(this,&Tester::startObjThreadWork1,userfile,&UserFile::run);
//    connect(this,&Tester::startObjThreadWork2,userdb,&UserDb::run);
//       connect(userfile,&ThreadObject::progress,this,&Widget::progress);
//       connect(userfile,&ThreadObject::message,this,&Widget::receiveMessage);
    m_Thread->start();

//    while(isFinsh){

//    }
//    statusBar()->showMessage("all data insert table.", 3000);
//    qDebug()<<"all data insert table.";

//    QList<QString> users = userfile->readTable("select col1,col2 from file where col1= '丁泽富'");
//    QList<QString> users = userfile->readTable("select count(*),col1,col3 from file group by col1,col3");
//    for(int i=0;i<users.size();i++){
//        qDebug()<< users.at(i)<<"\\n";
//    }

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

void Tester::startCheckFile1()
{
//    QTextCodec *code = QTextCodec::codecForName("GBK");//设置文件编码
    statusBar()->showMessage("start process file", 3000);
    qDebug()<<QStringLiteral("开始处理文件")<<(NULL==m_Thread);
    if(m_Thread==NULL)
    {
       qDebug()<<QStringLiteral("开始处理文件xiancheng");
       startObjThread();
    }
//    qDebug()<<"m_Thread"<<m_Thread;

    emit startObjThreadWork1();//主线程通过信号唤起子线程的槽函数

//todo
//    Report *report = new Report;
//    report->show();
}

void Tester::startCheckFile2()
{
    statusBar()->showMessage("start process file", 3000);
    qDebug()<<QStringLiteral("开始处理文件");
    userdb->run();
//    if(m_Thread==NULL)
//    {
//       startObjThread();
//    }
////    qDebug()<<"m_Thread"<<m_Thread;

//主线程通过信号唤起子线程的槽函数
//    emit startObjThreadWork2();


    Report *report = new Report;
    report->show();
}


void Tester::stopCheckFile()
{
    statusBar()->showMessage("stop process file", 3000);
    userfile->stop();
//    m_Thread->quit();
    qDebug()<<QStringLiteral("停止处理文件");
}

void Tester::setupTester()
{
    Setup *newSetup =new Setup;
    newSetup->exec();
}

void Tester::aboutTester()
{
//    About *newAbout =new About;
//    newAbout->show();
//    label->setText(tr("About Message Box"));
    QMessageBox::about(this, QStringLiteral("About消息框"),QStringLiteral("实名制检测系统\n "
                                                  "Version 1.0 \n"
                                                  "本系统为实名制检查工具。"));
    return;
}

void Tester::helpTester()
{
    userdb->run();
}

Tester::~Tester()
{

}

