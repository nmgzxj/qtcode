#ifndef TESTSIGNAL_H
#define TESTSIGNAL_H

#include <QWidget>

namespace Ui {
class TestSignal;
}

class TestSignal : public QWidget
{
    Q_OBJECT

public:
    explicit TestSignal(QWidget *parent = 0);
    ~TestSignal();

signals:
    void ViewSig();

public slots:
    void ViewSlot();
    void TestSlot();

private:
    Ui::TestSignal *ui;
};

#endif // TESTSIGNAL_H
