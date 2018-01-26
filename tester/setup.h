#ifndef SETUP_H
#define SETUP_H

#include <QMainWindow>
#include <QStandardItemModel>

class Setup : public QMainWindow
{
//    Q_OBJECT
public:
    explicit Setup(QWidget *parent = 0);
    QString loadXml(QString filename);

signals:

public slots:

private:
    QStandardItemModel *model;
};

#endif // SETUP_H
