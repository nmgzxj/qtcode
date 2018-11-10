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
    resize(800,600);
    showWidget =new ShowWidget(this);		//设置文本显示窗体
    setCentralWidget(showWidget);

//    /* 创建动作、菜单、工具栏的函数 */
    createActions();
    createMenus();
    setupModel();
    setupView();
    createToolBars();\
    userdb = new UserDb();
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

//    //运行菜单

    runMenu =menuBar()->addMenu(QStringLiteral("运行"));
    runMenu->addAction(startAction);
    runMenu->addAction(stopAction);
    runMenu->addAction(reportAction);

    //帮助菜单
    helpMenu =menuBar()->addMenu(QStringLiteral("帮助"));
    helpMenu->addAction(helpAction);
    helpMenu->addAction(aboutAction);
}

void Tester::createToolBars()
{
    //文件工具条

    fileTool =addToolBar("File");
    fileTool->addAction(openFileAction);
    fileTool->addAction(NewFileAction);
    fileTool->addAction(setupAction);
    fileTool->addAction(exitAction);
  //  运行工具条
    runTool =addToolBar("Run");
    runTool->addAction(startAction);
    runTool->addAction(stopAction);
    runTool->addAction(reportAction);
    runTool->addSeparator();
    runTool->addAction(helpAction);
    runTool->addAction(aboutAction);
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
    //“开始”动作
    startAction =new QAction(QStringLiteral("开始"),this);//QIcon("../../../new.png"),
    startAction->setShortcut(QStringLiteral("Ctrl+R"));
    startAction->setStatusTip(QStringLiteral("开始检查"));
    connect(startAction,SIGNAL(triggered()),this,SLOT(startCheckFile()));
    //查看报表动作
    reportAction = new QAction(QStringLiteral("查看报表"),this);
    reportAction->setStatusTip("查看运行结果报表");
    connect(reportAction,SIGNAL(triggered()),this,SLOT(report()));
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
    name = QFileDialog::getOpenFileName(this,QStringLiteral("打开"),".","histogram files (*.*)");//txt)");
    if (!name.isEmpty()){
        processfilename = name;
          loadFile(name);
    }

}

void Tester::setupModel()
{//设置列名
    model = new QStandardItemModel(10,41,this);
    XMLConfigReader *xmlConfig;
    QList<QList<QString>> lls = xmlConfig->readAutoid();
    for(int i=0; i<lls.size(); i++){
        model->setHeaderData(i,Qt::Horizontal,lls.at(i).at(1));
    }
}

void Tester::setupView()
{

    table = new QTableView;			//新建一个QTableView对象
    table->setModel(model);			//为QTableView对象设置相同的Model
    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
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
                        QStringList pieces = line.split("||");//, QString::SkipEmptyParts
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


void Tester::startObjThread()
{
    qDebug()<<"processfilename is "<<processfilename;
    if(processfilename.isEmpty()){
        QErrorMessage * dialog = new QErrorMessage(this);
        dialog -> setWindowTitle(QObject::tr("错误消息"));
        dialog -> showMessage(QObject::tr("请先打开需要检查的文件。"));
    }
    else{
        qDebug() << "Main Thread : " << QThread::currentThreadId();
        userdb = new UserDb;
        userdb->printMessage();
        userdb->filename = processfilename;
        qDebug()<<QStringLiteral("启动文件处理线程");


        m_Thread = new QThread();

        userdb->moveToThread(m_Thread);
        connect(m_Thread,&QThread::finished,m_Thread,&QObject::deleteLater,Qt::QueuedConnection);
        connect(m_Thread,&QThread::finished,userdb,&QObject::deleteLater,Qt::QueuedConnection);
        connect(this,&Tester::startObjThreadWork,userdb,&UserDb::run,Qt::QueuedConnection);
        connect(userdb,&UserDb::message,this,&Tester::setStatus,Qt::QueuedConnection);
        m_Thread->start();
       qDebug()<<"m_thread is running?"<< m_Thread->isRunning();
    }


}

void Tester::startCheckFile()
{
    statusBar()->showMessage("start process file", 3000);
    userdb->start();
    startObjThread();
    //主线程通过信号唤起子线程的槽函数
    emit startObjThreadWork();
}


void Tester::stopCheckFile()
{
    statusBar()->showMessage("stop process file", 3000);
    userdb->stop();
    if(m_Thread!=nullptr){
        m_Thread->quit();
        m_Thread->wait(2000);
//        m_Thread=NULL;
    }
    qDebug()<<QStringLiteral("停止处理文件");
}

void Tester::setupTester()
{
    Setup *newSetup =new Setup;
    newSetup->exec();
}

void Tester::aboutTester()
{
    QMessageBox::about(this, QStringLiteral("About消息框"),QStringLiteral("实名制检测系统\n "
                                                                          "Version 1.0 \n"
                                                                          "本系统为实名制检查工具。"));
    return;
}

void Tester::helpTester()
{
    userdb->run();
}

void Tester::report(){
        Report *report = new Report;
        report->show();
}

void Tester::setStatus(QString str){
     statusBar()->showMessage(str, 3000);
}
Tester::~Tester()
{
   // delete userdb;
}

