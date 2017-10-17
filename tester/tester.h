#ifndef TESTER_H
#define TESTER_H

#include <QMainWindow>

class Tester : public QMainWindow
{
    Q_OBJECT

public:
    Tester(QWidget *parent = 0);
    ~Tester();
};

#endif // TESTER_H
