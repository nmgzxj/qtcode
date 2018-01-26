#include "threaddialog.h"

ThreadDialog::ThreadDialog(QWidget *parent) : QDialog(parent)
{
    threadA.setMessage("A");
    threadB.setMessage("B");

    threadAButton = new QPushButton(tr("Start A"), this);
    threadAButton->setGeometry(10, 30, 80, 30);
    threadBButton = new QPushButton(tr("Start B"),this);
    threadBButton->setGeometry(110, 30, 80, 30);
    quitButton = new QPushButton(tr("Quit"), this);
    quitButton->setGeometry(210, 30, 80, 30);
    quitButton->setDefault(true);

    connect(threadAButton, SIGNAL(clicked()), this, SLOT(startOrStopThreadA()));
    connect(threadBButton, SIGNAL(clicked()), this, SLOT(startOrStopThreadB()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
}

void ThreadDialog::startOrStopThreadA()
{
    if(threadA.isRunning())
    {
        threadAButton->setText(tr("Stop A"));
        threadA.stop();
        threadAButton->setText(tr("Start A"));
    }
    else
    {
        threadAButton->setText(tr("Start A"));
        threadA.start();
        threadAButton->setText(tr("Stop A"));
    }
}

void ThreadDialog::startOrStopThreadB()
{
    if(threadB.isRunning())
    {
        threadBButton->setText(tr("Stop B"));
        threadB.stop();
        threadBButton->setText(tr("Strat B"));
    }
    else
    {
        threadBButton->setText(tr("Start B"));
        threadB.start();
        threadBButton->setText(tr("Stop B"));
    }
}

void ThreadDialog::closeEvent(QCloseEvent *event)
{
    threadA.stop();
    threadB.stop();
    threadA.wait();
    threadB.wait();
    event->accept();
}

void ThreadDialog::close()
{
    exit(0);
}
