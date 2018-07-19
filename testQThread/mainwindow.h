#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QDebug>
#include <QPushButton>
#include <QThread>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "workerthread.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow(){}

private slots:
    // 更新进度
    void handleResults(int value);

    // 开启线程
    void startThread();

private:
    QProgressBar *m_pProgressBar;
    WorkerThread m_workerThread;
};

#endif // MAINWINDOW_H
