#include "tester.h"
#include "logindialog.h"
#include <QMutex>

#include <QApplication>


/*QT5日志功能（qDebug、qWarnng、qCritical、qFatal）
 * 一、基本分类：
qDebug : 调试信息提示
qWarning: 一般的警告提示
qCritical: 严重错误提示
qFatal: 致命错误提示

二、如何截获这些信息
Qt提供了qInstallMsgHandler 方法用来定制消息发生后如何来处理。
qInstallMsgHandler 是一个回调函数，主要是由qDebug、qWarnng、qCritical、qFatal这些函数进行触发，
也就是说，qDeubg这些函数处理的消息文本会被qInstallMsgHandler 所指向的回调函数截获，这样就允许用户自己来处理这些消息文本。

三、如何取消信息处理呢？
简单：
还是用qInstallMsgHandler.
只要执行qInstallMsgHandler(0) 就可以了
Qt::qInstallMsgHandler()已过时，因此建议使用Qt::qInstallMessageHandler()来代替。
*/
#define LOGFILEMAX 10000
void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;

    case QtWarningMsg:
        text = QString("Warning:");
        break;

    case QtCriticalMsg:
        text = QString("Critical:");
        break;

    case QtFatalMsg:
        text = QString("Fatal:");
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

    QDateTime dt;
    QTime time;
    QDate date;
    dt.setTime(time.currentTime());
    dt.setDate(date.currentDate());
    QString currentDate = dt.toString("yyyyMMdd");

    QFile file("log"+currentDate+".txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
#ifdef Q_OS_WIN
    a.setWindowIcon(QIcon(":/images/logo.png"));
#endif
#ifdef Q_OS_MACOS

#endif



    //注册MessageHandler写log
//        qInstallMessageHandler(outputMessage);
//    qInstallMessageHandler(0);


//    ProgressDlg w;
//    w.show();
//    return a.exec();

//    createConnection();
    Tester w;
    w.show();

    return a.exec();
//    LoginDialog dlg;
//    if(dlg.exec() == QDialog::Accepted)
//    {
//        w.show();

//        return a.exec();
//    }
//    else
//    {
//        return 0;
//    }
}
