#include "testsignal.h"
#include "ui_testsignal.h"
#include <QDebug>

TestSignal::TestSignal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestSignal)
{
    ui->setupUi(this);
    ViewSig();
    connect(ui->tests,SIGNAL(clicked()),this,SLOT(TestSlot()));
}

TestSignal::~TestSignal()
{
    delete ui;
}

void TestSignal::TestSlot(){
    qDebug()<<"test  slot.";
}


void TestSignal::ViewSlot(){
    qDebug()<<"test view slot.";
}
