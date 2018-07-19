#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void read_xml(QString filename);
    void create_xml(QString filename);
    void add_xmlnode(QString filename,QString rmt_name,QString ipa,QString ipb);
    void do_xml(const QString opt,QString filename);
private:
};

#endif // WIDGET_H
