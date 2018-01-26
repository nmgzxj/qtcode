#include "thread.h"
#include <QDebug>

Thread::Thread()
{
    stopped = false;
}

void Thread::run()
{
    while(!stopped)
    {
        printMessage();
    }
    stopped = false;
}

void Thread::stop()
{
    stopped = true;
}

void Thread::setMessage(QString message)
{
    messageStr = message;
}

void Thread::printMessage()
{
    qDebug()<<messageStr;
    sleep(1);
}
