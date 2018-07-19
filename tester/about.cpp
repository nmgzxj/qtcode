#include "about.h"
#include <QTextEdit>

About::About(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("关于仪表");
    QTextEdit *edit=new QTextEdit;
    edit->setText("实名制检查仪表\n "
                  "Version 1.0 \n"
                  "本仪表为实名制检查工具。本仪表为实名制检查工具。本仪表为实名制检查工具。本仪表为实名制检查工具。本仪表为实名制检查工具。"
                  "本仪表为实名制检查工具。本仪表为实名制检查工具。本仪表为实名制检查工具。本仪表为实名制检查工具。本仪表为实名制检查工具。");
    setCentralWidget(edit);
    resize(500,150);
}
