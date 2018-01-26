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
#include "showwidget.h"
#include "about.h"
#include "setup.h"
#include "userfile.h"
#include <iostream>
#include <QMessagebox>
#include <QDebug>

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
private:
    QMenu *fileMenu;                           		//各项菜单栏
    QMenu *runMenu;
    QMenu *helpMenu;
//    QMenu *mirrorMenu;
//    QImage img;
    QString fileName;
    ShowWidget *showWidget;
    QAction *openFileAction;                     	//文件菜单项
    QAction *NewFileAction;
    QAction *startAction;
    QAction *stopAction;
    QAction *setupAction;                          	//编辑菜单项
    QAction *aboutAction;
    QAction *exitAction;
    QAction *helpAction;
    QTableView *table;
    QSplitter *splitter;
    UserFile *userfile;


//    QAction *aboutAction;
//    QAction *zoomInAction;
//    QAction *zoomOutAction;
//    QAction *rotate90Action;                     	//旋转菜单项
//    QAction *rotate180Action;
//    QAction *rotate270Action;
//    QAction *mirrorVerticalAction;              	//镜像菜单项
//    QAction *mirrorHorizontalAction;
//    QAction *undoAction;
//    QAction *redoAction;
//    QToolBar *fileTool;                          	//工具栏
//    QToolBar *zoomTool;
//    QToolBar *rotateTool;
//    QToolBar *mirrorTool;
//    QToolBar *doToolBar;
//    QLabel *fontLabel1;                             //字体设置项
//    QFontComboBox *fontComboBox;
//    QLabel *fontLabel2;
//    QComboBox *sizeComboBox;
//    QToolButton *boldBtn;
//    QToolButton *italicBtn;
//    QToolButton *underlineBtn;
//    QToolButton *colorBtn;
//    QToolBar *fontToolBar;                          //字体工具栏
//    QLabel *listLabel;                              //排序设置项
//    QComboBox *listComboBox;
//    QActionGroup *actGrp;
//    QAction *leftAction;
//    QAction *rightAction;
//    QAction *centerAction;
//    QAction *justifyAction;
//    QToolBar *listToolBar;                          //排序工具栏
protected slots:
    void showNewFile();
    void showOpenFile();
    void startCheckFile();
    void stopCheckFile();
    void setupTester();
    void aboutTester();
    void helpTester();
    void setupView();
//    void ShowRotate270();
//    void ShowMirrorVertical();
//    void ShowMirrorHorizontal();
//    void ShowFontComboBox(QString comboStr);
//    void ShowSizeSpinBox(QString spinValue);
//    void ShowBoldBtn();
//    void ShowItalicBtn();
//    void ShowUnderlineBtn();
//    void ShowColorBtn();
//    void ShowCurrentFormatChanged(const QTextCharFormat &fmt);
//    void ShowList(int);
//    void ShowAlignment(QAction *act);
//    void ShowCursorPositionChanged();
private:
    QStandardItemModel *model;
    QString processfilename;

};

#endif // TESTER_H
