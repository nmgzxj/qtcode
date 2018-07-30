#include "showwidget.h"
#include <QHBoxLayout>

ShowWidget::ShowWidget(QWidget *parent) : QWidget(parent)
{
    text =new QTextEdit;
    QHBoxLayout *mainLayout =new QHBoxLayout(this);
    mainLayout->addWidget(text);

}
