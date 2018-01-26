#ifndef THREADDIALOG_H
#define THREADDIALOG_H

#include <QPushButton>
#include <QDialog>
#include <QCloseEvent>
#include "thread.h"

class ThreadDialog : public QDialog
{
    Q_OBJECT

public:
    ThreadDialog(QWidget *parent=0);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void startOrStopThreadA();
    void startOrStopThreadB();
    void close();

private:
    Thread threadA;
    Thread threadB;
    QPushButton *threadAButton;
    QPushButton *threadBButton;
    QPushButton *quitButton;
};

#endif // THREADDIALOG_H
