#include "testsignal.h"
#include "ui_testsignal.h"

TestSignal::TestSignal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestSignal)
{
    ui->setupUi(this);
}

TestSignal::~TestSignal()
{
    delete ui;
}
