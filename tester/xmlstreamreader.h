#ifndef XMLSTREAMREADER_H
#define XMLSTREAMREADER_H
#include <QTreeWidget>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QtXml>
#include <iostream>
#include <QXmlStreamReader>

class XmlStreamReader
{
public:
    XmlStreamReader();
    XmlStreamReader(QTreeWidget*tree);
    bool readFile(const QString &fileName);
    QXmlStreamReader  reader;
    QTreeWidget *treeWidget;
    void readEntryElement(QTreeWidgetItem *parent);
    void skipUnknownElement();
    void readPageElement(QTreeWidgetItem *parent);
    void readBookindexElement();
};

#endif // XMLSTREAMREADER_H
