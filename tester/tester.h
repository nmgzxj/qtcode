#ifndef TESTER_H
#define TESTER_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCharFormat>
#include <QStandardItemModel>
#include <QTableView>
#include <QSplitter>
#include <QTextCodec>
#include <QStatusBar>
#include <QErrorMessage>
#include "showwidget.h"
#include "setup.h"
#include "setuppages.h"
//#include "userfile.h"
#include "userdb.h"

//#include <QMessagebox>
#include <QDebug>
#include <QThread>

class Tester : public QMainWindow
{
    Q_OBJECT

public:
    Tester(QWidget *parent = 0);
    ~Tester();
    void createActions();                        	//创建动作
    void createMenus();                           	//创建菜单
    void createToolBars();                      	//创建工具栏
    void loadFile(QString filename);
    void setupModel();
    int col_num = 42; //文件列数
    int row_num = 20; //预览行数
    void startObjThread1();
    void startObjThread2();

signals:
    void startObjThreadWork1();
    void startObjThreadWork2();
private:
    QMenu *fileMenu;                           		//各项菜单栏
    QMenu *runMenu;
    QMenu *helpMenu;
//    QMenu *mirrorMenu;
//    QImage img;
    ShowWidget *showWidget;
    QAction *openFileAction;                     	//文件菜单项
    QAction *NewFileAction;
    QAction *startAction1;
    QAction *startAction2;
    QAction *stopAction;
    QAction *reportAction;
    QAction *setupAction;                          	//编辑菜单项
    QAction *aboutAction;
    QAction *exitAction;
    QAction *helpAction;
    QTableView *table;
    QSplitter *splitter;
//    UserFile *userfile;
    UserDb *userdb;


protected slots:
    void showNewFile();
    void showOpenFile();
//    void startCheckFile1();
    void startCheckFile2();
    void stopCheckFile();
    void setupTester();
    void aboutTester();
    void helpTester();
    void setupView();
    void report();
    void setStatus(QString str);

private:
    QStandardItemModel *model;
    QString processfilename;
    QThread* m_Thread1;
    QThread* m_Thread2;

};

#endif // TESTER_H
