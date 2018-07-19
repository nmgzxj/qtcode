#ifndef SETUP_H
#define SETUP_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QDialog>

class Setup : public QDialog
{
    Q_OBJECT
public:
//    explicit Setup(QWidget *parent = 0);
    Setup();
    QString loadXml(QString filename);


public slots:
//    void changePage(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void slotItemPressed(QTreeWidgetItem *item);


private:
    void createIcons();

    QStandardItemModel *model;
    QTreeWidget *contentsWidget;
    QStackedWidget *pagesWidget;
};

#endif // SETUP_H
