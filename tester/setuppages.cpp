#include "setuppages.h"


#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <set>
#include <QFile>
#include <QHeaderView>

SetupPages::SetupPages()
{

}
ColumnPage::ColumnPage(QWidget *parent): QWidget(parent)
{
    autoidInit();
    table = new QTableWidget;
    table->setColumnCount(3);
    QTableWidgetItem *item0 = new QTableWidgetItem;
    QTableWidgetItem *item1 = new QTableWidgetItem;
    QTableWidgetItem *item2 = new QTableWidgetItem;
//    QTableWidgetItem *item3 = new QTableWidgetItem;
//    item0->setText("是否显示");
    item0->setText(QStringLiteral("父列名"));
    item1->setText(QStringLiteral("列名"));
    item2->setText(QStringLiteral("列号"));
    table->setHorizontalHeaderItem(0, item0);
    table->setHorizontalHeaderItem(1, item1);
    table->setHorizontalHeaderItem(2, item2);
//    table->setHorizontalHeaderItem(3, item3);

    //////////////////////////////////////////////
        //设定标题列的宽度
    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 100);
    table->setColumnWidth(2, 100);
//    table->setColumnWidth(3, 50);

    //设置排序
    QHeaderView *headerGoods = table->horizontalHeader();
    //SortIndicator为水平标题栏文字旁边的三角指示器
    headerGoods->setSortIndicator(3, Qt::AscendingOrder);
    headerGoods->setSortIndicatorShown(true);
    connect(headerGoods, SIGNAL(sectionClicked(int)), table, SLOT (sortByColumn(int)));


        //////////////////////////////////////////////
        //设置垂直标题
    table->setRowCount(autoid.size());
    QStringList list = { "row1","row2","row3" };
        //list.push_back("col1");
    table->setVerticalHeaderLabels(list);

    //插入数据
//    bool ok=true;

    for(int i=0; i<autoid.size(); i++){
    QList<QString> line=autoid.at(i);

//        table->setItem(i, 0, new QTableWidgetItem("checkbox"));
//        qDebug()<<"line size="<<line.size();
        for(int j=0; j<line.size(); j++){
            table->setItem(i, j, new QTableWidgetItem(line[j]));
            table->setItem(i, j+1, new QTableWidgetItem(line[j]));//?
        }
    }


    table->horizontalHeader()->setVisible(true);
    table->verticalHeader()->setVisible(false);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    //增加行按钮
    QPushButton *addButton = new QPushButton;
    addButton->setText("+");
    addButton->setStyleSheet("width:30px");

    //删除行按钮
    QPushButton *delButton = new QPushButton;
    delButton->setText("-");
    delButton->setStyleSheet("width:30px");

    //保存按钮
    QPushButton *saveButton = new QPushButton;
    saveButton->setText("save");

    connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
    connect(delButton, SIGNAL(clicked()), this, SLOT(del()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(autoidSave()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(delButton);
    buttonLayout->addWidget(saveButton);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(table);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setSpacing(1);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setLayout(mainLayout);
}

void ColumnPage::add(){
    //结尾添加一行
    int row = table->rowCount();
    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem("new row"));
    table->setItem(row, 1, new QTableWidgetItem("new row"));
    table->setItem(row, 2, new QTableWidgetItem("new row"));
}

//按行删除函数
void ColumnPage::del(){

    qDebug()<<"del方法"<<table;
    //空行无法选择
        QList<QTableWidgetItem*> items = table->selectedItems();
        //选择模式器
        QItemSelectionModel *smodel = table->selectionModel();
        //获取所有的选择索引
        QModelIndexList slist = smodel->selectedIndexes();

        //获取所有被选中的行号
        std::set<int> rows;
        for (int i = 0; i < slist.size(); i++)
        {
            //重复的插入失败
            rows.insert(slist[i].row());
        }

       //给用户提示
        QString msg = QStringLiteral("您确认删除:");

        for (std::set<int>::iterator itr = rows.begin(); itr != rows.end(); itr++)
        {
            QTableWidgetItem *item = table->item(*itr, 1);
            msg += "[";
            msg += QString::number(*itr+1);
            msg += ":";
            if (item)
                msg += item->text();
            msg += "]";
        }
        int re = QMessageBox::information(this, "", msg, QStringLiteral("确认"), QStringLiteral("取消"));
        if (re != 0)
        {
            return;
        }

        //删除多行
        for (;;)
        {
            //获取所有的选择索引
            QModelIndexList s = smodel->selectedIndexes();
            if (s.size() <= 0) break;
            //每次只删除一行
            table->removeRow(s[0].row());
        }
    autoidSave();
}

void ColumnPage::autoidInit(){
    autoid.clear();
    QList<QList<QString>> lls = xmlConfig->readAutoid();
    for(int i=0; i<lls.size(); i++){
        for(int j=0; j<lls.at(i).size(); j++){
            qDebug()<<"i="<<i<<"j="<<j<<"String="<<lls.at(i).at(j);
        }
        autoid.append(lls.at(i));
    }
    qDebug()<<"autoid.size="<<autoid.size();
}

void ColumnPage::autoidSave(){
    qDebug()<<" ===================in autoidSave==================== ";
    qDebug()<<"row count is "<<table->rowCount();
    qDebug()<<"col count is "<<table->columnCount();
    autoid.clear();
    QList<QString> line;
    for(int i=0; i<table->rowCount();i++){
        for(int j=0; j<table->columnCount(); j++){
            line.append(table->item(i,j)->text());
        }
        autoid.append(line);
        line.clear();
    }
    xmlConfig->writeAutoid(autoid);
}

RulePage::RulePage(QWidget *parent) : QWidget(parent)
{
    QLabel *serverLabel = new QLabel(QStringLiteral("RulePage:"));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(serverLabel);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

SystemPage::SystemPage(QWidget *parent) : QWidget(parent)
{
    dataRangeLabel = new QLabel(QStringLiteral("数据范围:"));
    dataRangeEdit = new QLineEdit;
    compliantDateLabel = new QLabel(QStringLiteral("合规性检查日期:"));
    compliantDateEdit = new QLineEdit;
    onecard2fiveDateLabel = new QLabel(QStringLiteral("一证五号时间节点:"));
    onecard2fiveDateEdit = new QLineEdit;
    randomDateLabel = new QLabel(QStringLiteral("随机日期:"));
    randomDateEdit = new QLineEdit;
    saveButton = new QPushButton;
    saveButton->setText("save");

    QGridLayout *mainLayout = new QGridLayout;
    //数据范围
    mainLayout->addWidget(dataRangeLabel,0,0,1,1);
    mainLayout->addWidget(dataRangeEdit,0,1,1,1);
    //合规性检查日期
    mainLayout->addWidget(compliantDateLabel,1,0,1,1);
    mainLayout->addWidget(compliantDateEdit,1,1,1,1);
    //一证五号时间节点
    mainLayout->addWidget(onecard2fiveDateLabel,2,0,1,1);
    mainLayout->addWidget(onecard2fiveDateEdit,2,1,1,1);
    //随机日期
    mainLayout->addWidget(randomDateLabel,3,0,1,1);
    mainLayout->addWidget(randomDateEdit,3,1,1,1);
    //保存按钮
    mainLayout->addWidget(saveButton,4,0,2,1);
    // 设置水平间距
    mainLayout->setHorizontalSpacing(10);
    // 设置垂直间距
    mainLayout->setVerticalSpacing(10);
    // 设置外间距
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->rowStretch(0);
    mainLayout->columnStretch(0);
    setLayout(mainLayout);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
    init();
}

void SystemPage::init(){
    QMap<QString,QString> map = xmlConfig->readSystemValue();
    this->dataRangeEdit->setText(map.value("data-range"));
    this->compliantDateEdit->setText(map.value("compliant-date"));
    this->onecard2fiveDateEdit->setText(map.value("onecard2five-date"));
    this->randomDateEdit->setText(map.value("random-date"));
}

void SystemPage::save(){
    qDebug()<<" ===================in save==================== ";
    xmlConfig->writeSystemValue(dataRangeEdit->text(),compliantDateEdit->text(),onecard2fiveDateEdit->text(),randomDateEdit->text());
}

WorkPathPage::WorkPathPage(QWidget *parent) : QWidget(parent)
{
    workPathLabel = new QLabel(QStringLiteral("工作路径:"));
    workPathEdit = new QLineEdit;
    saveButton = new QPushButton;
    saveButton->setText("save");

    QGridLayout *mainLayout = new QGridLayout;
    //工作路径
    mainLayout->addWidget(workPathLabel,0,0,1,1);
    mainLayout->addWidget(workPathEdit,0,1,1,1);
    //保存按钮
    mainLayout->addWidget(saveButton,2,0,2,1);
    // 设置水平间距
    mainLayout->setHorizontalSpacing(10);
    // 设置垂直间距
    mainLayout->setVerticalSpacing(10);
    // 设置外间距
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->rowStretch(0);
    mainLayout->columnStretch(0);
    setLayout(mainLayout);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
    init();
}

void WorkPathPage::init(){
    QMap<QString,QString> map = xmlConfig->readWorkingpathValue();
    this->workPathEdit->setText(map.value("workingpath"));
}

void WorkPathPage::save(){
    qDebug()<<" ===================in save==================== ";
    xmlConfig->writeWorkingpathValue(workPathEdit->text());
}

DelimiterPage::DelimiterPage(QWidget *parent) : QWidget(parent)
{
    delimiterLabel = new QLabel(QStringLiteral("字段间分隔符:"));
    delimiterEdit = new QLineEdit;
    saveButton = new QPushButton;
    saveButton->setText("save");

    QGridLayout *mainLayout = new QGridLayout;
    //工作路径
    mainLayout->addWidget(delimiterLabel,0,0,1,1);
    mainLayout->addWidget(delimiterEdit,0,1,1,1);
    //保存按钮
    mainLayout->addWidget(saveButton,2,0,2,1);
    // 设置水平间距
    mainLayout->setHorizontalSpacing(10);
    // 设置垂直间距
    mainLayout->setVerticalSpacing(10);
    // 设置外间距
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->rowStretch(0);
    mainLayout->columnStretch(0);
    setLayout(mainLayout);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
    init();
}

void DelimiterPage::init(){
    QMap<QString,QString> map = xmlConfig->readDelimiterValue();
    this->delimiterEdit->setText(map.value("delimiter"));
}

void DelimiterPage::save(){
    qDebug()<<" ===================in save==================== ";
    xmlConfig->writeDelimiterValue(delimiterEdit->text());
}

ItemnumPage::ItemnumPage(QWidget *parent) : QWidget(parent)
{
    itemnumLabel = new QLabel(QStringLiteral("字段个数:"));
    itemnumEdit = new QLineEdit;
    saveButton = new QPushButton;
    saveButton->setText("save");

    QGridLayout *mainLayout = new QGridLayout;
    //工作路径
    mainLayout->addWidget(itemnumLabel,0,0,1,1);
    mainLayout->addWidget(itemnumEdit,0,1,1,1);
    //保存按钮
    mainLayout->addWidget(saveButton,2,0,2,1);
    // 设置水平间距
    mainLayout->setHorizontalSpacing(10);
    // 设置垂直间距
    mainLayout->setVerticalSpacing(10);
    // 设置外间距
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->rowStretch(0);
    mainLayout->columnStretch(0);
    setLayout(mainLayout);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
    init();
}

void ItemnumPage::init(){
    QMap<QString,QString> map = xmlConfig->readItemnumValue();
    this->itemnumEdit->setText(map.value("itemnum"));
}

void ItemnumPage::save(){
    qDebug()<<" ===================in save==================== ";
    xmlConfig->writeItemnumValue(itemnumEdit->text());
}

DateformatPage::DateformatPage(QWidget *parent) : QWidget(parent)
{
    dateformatLabel = new QLabel(QStringLiteral("时间格式:"));
    dateformatEdit = new QLineEdit;
    saveButton = new QPushButton;
    saveButton->setText("save");

    QGridLayout *mainLayout = new QGridLayout;
    //工作路径
    mainLayout->addWidget(dateformatLabel,0,0,1,1);
    mainLayout->addWidget(dateformatEdit,0,1,1,1);
    //保存按钮
    mainLayout->addWidget(saveButton,2,0,2,1);
    // 设置水平间距
    mainLayout->setHorizontalSpacing(10);
    // 设置垂直间距
    mainLayout->setVerticalSpacing(10);
    // 设置外间距
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->rowStretch(0);
    mainLayout->columnStretch(0);
    setLayout(mainLayout);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
    init();
}

void DateformatPage::init(){
    QMap<QString,QString> map = xmlConfig->readDateformatValue();
    this->dateformatEdit->setText(map.value("dateformat"));
}

void DateformatPage::save(){
    qDebug()<<" ===================in save==================== ";
    xmlConfig->writeDateformatValue(dateformatEdit->text());
}

CommonRulePage::CommonRulePage(QWidget *parent) : QWidget(parent)
{
//    QRegExp regnum("[0-9]+$");//只能输入数字
//    QValidator *validatorNum = new QRegExpValidator(regnum);
    QRegExp regnumdash("[0-9\-]+$");//只能输入或横线
    QValidator *validatorNumDash = new QRegExpValidator(regnumdash);
//    QRegExp regchar("[a-zA-Z]+$");//只能输入字符
//    QValidator *validatorChar = new QRegExpValidator(regchar);
//    QRegExp regcharnum("[a-zA-Z0-9]+$");//只能输入字符和数字
//    QValidator *validatorCharNum = new QRegExpValidator(regcharnum);

    maxlimitLabel = new QLabel(QStringLiteral("重号率阈值:"));
    maxlimitEdit = new QLineEdit;
    maxlimitEdit->setValidator(validatorNumDash);
    personNameLen_minLabel = new QLabel(QStringLiteral("姓名最短:"));
    personNameLen_minEdit = new QLineEdit;
    personNameLen_minEdit->setValidator(validatorNumDash);
    personNameLen_maxLabel = new QLabel(QStringLiteral("最长:"));
    personNameLen_maxEdit = new QLineEdit;
    personNameLen_maxEdit->setValidator(validatorNumDash);
    personNamePermit_charLabel = new QLabel(QStringLiteral("姓名允许字符:"));
    personNamePermit_charEdit = new QLineEdit;

    personCardtypeTime_intervalLabel = new QLabel(QStringLiteral("证件类型临界点:"));
    personCardtypeTime_intervalEdit = new QLineEdit;
    personCardtypeTime_intervalEdit->setValidator(new QIntValidator(19000101,20190101));
    personCard_numLen_minLabel = new QLabel(QStringLiteral("证件号码最短:"));
    personCard_numLen_minEdit = new QLineEdit;
    personCard_numLen_minEdit->setValidator(validatorNumDash);
    personCard_numLen_maxLabel = new QLabel(QStringLiteral("最长:"));
    personCard_numLen_maxEdit = new QLineEdit;
    personCard_numLen_maxEdit->setValidator(validatorNumDash);
    personCard_addLen_minLabel = new QLabel(QStringLiteral("证件地址最短:"));
    personCard_addLen_minEdit = new QLineEdit;
    personCard_addLen_minEdit->setValidator(validatorNumDash);
    personCard_addLen_maxLabel = new QLabel(QStringLiteral("最长:"));
    personCard_addLen_maxEdit = new QLineEdit;
    personCard_addLen_maxEdit->setValidator(validatorNumDash);

    unitNameLen_minLabel = new QLabel(QStringLiteral("名称最短:"));
    unitNameLen_minEdit = new QLineEdit;
    unitNameLen_minEdit->setValidator(validatorNumDash);
    unitNameLen_maxLabel = new QLabel(QStringLiteral("名称最长:"));
    unitNameLen_maxEdit = new QLineEdit;
    unitNameLen_maxEdit->setValidator(validatorNumDash);
    unitCardtypeTime_intervalLabel = new QLabel(QStringLiteral("证件类型临界点:"));
    unitCardtypeTime_intervalEdit = new QLineEdit;
    unitCardtypeTime_intervalEdit->setValidator(new QIntValidator(19000101,20190101));
    unitCard_numLen_minLabel = new QLabel(QStringLiteral("证件号码最短:"));
    unitCard_numLen_minEdit = new QLineEdit;
    unitCard_numLen_minEdit->setValidator(validatorNumDash);
    unitCard_numLen_maxLabel = new QLabel(QStringLiteral("最长:"));
    unitCard_numLen_maxEdit = new QLineEdit;
    unitCard_numLen_maxEdit->setValidator(validatorNumDash);
    unitCard_addLen_minLabel = new QLabel(QStringLiteral("证件地址最短:"));
    unitCard_addLen_minEdit = new QLineEdit;
    unitCard_addLen_minEdit->setValidator(validatorNumDash);
    unitCard_addLen_maxLabel = new QLabel(QStringLiteral("最长:"));
    unitCard_addLen_maxEdit = new QLineEdit;
    unitCard_addLen_maxEdit->setValidator(validatorNumDash);

    saveButton = new QPushButton;
    saveButton->setText("save");

    QGridLayout *mainLayout = new QGridLayout;
    //
    mainLayout->addWidget(maxlimitLabel,0,0,1,1);
    mainLayout->addWidget(maxlimitEdit,0,1,1,1);
    mainLayout->addWidget(new QLabel("------个人-------"),1,0,1,2);
    mainLayout->addWidget(personNameLen_minLabel,2,0,1,1);
    mainLayout->addWidget(personNameLen_minEdit,2,1,1,1);
    mainLayout->addWidget(personNameLen_maxLabel,3,0,1,1);
    mainLayout->addWidget(personNameLen_maxEdit,3,1,1,1);
    mainLayout->addWidget(personNamePermit_charLabel,4,0,1,1);
    mainLayout->addWidget(personNamePermit_charEdit,4,1,1,1);
    mainLayout->addWidget(personCardtypeTime_intervalLabel,5,0,1,1);
    mainLayout->addWidget(personCardtypeTime_intervalEdit,5,1,1,1);
    mainLayout->addWidget(personCard_numLen_minLabel,6,0,1,1);
    mainLayout->addWidget(personCard_numLen_minEdit,6,1,1,1);
    mainLayout->addWidget(personCard_numLen_maxLabel,7,0,1,1);
    mainLayout->addWidget(personCard_numLen_maxEdit,7,1,1,1);
    mainLayout->addWidget(personCard_addLen_minLabel,8,0,1,1);
    mainLayout->addWidget(personCard_addLen_minEdit,8,1,1,1);
    mainLayout->addWidget(personCard_addLen_maxLabel,9,0,1,1);
    mainLayout->addWidget(personCard_addLen_maxEdit,9,1,1,1);
    mainLayout->addWidget(new QLabel("-----单位/行业用户-----"),10,0,1,2);
    mainLayout->addWidget(unitNameLen_minLabel,11,0,1,1);
    mainLayout->addWidget(unitNameLen_minEdit,11,1,1,1);
    mainLayout->addWidget(unitNameLen_maxLabel,12,0,1,1);
    mainLayout->addWidget(unitNameLen_maxEdit,12,1,1,1);
    mainLayout->addWidget(unitCardtypeTime_intervalLabel,13,0,1,1);
    mainLayout->addWidget(unitCardtypeTime_intervalEdit,13,1,1,1);
    mainLayout->addWidget(unitCard_numLen_minLabel,14,0,1,1);
    mainLayout->addWidget(unitCard_numLen_minEdit,14,1,1,1);
    mainLayout->addWidget(unitCard_numLen_maxLabel,15,0,1,1);
    mainLayout->addWidget(unitCard_numLen_maxEdit,15,1,1,1);
    mainLayout->addWidget(unitCard_addLen_minLabel,16,0,1,1);
    mainLayout->addWidget(unitCard_addLen_minEdit,16,1,1,1);
    mainLayout->addWidget(unitCard_addLen_maxLabel,17,0,1,1);
    mainLayout->addWidget(unitCard_addLen_maxEdit,17,1,1,1);


    //保存按钮
    mainLayout->addWidget(saveButton,18,0,2,1);
    // 设置水平间距
    mainLayout->setHorizontalSpacing(10);
    // 设置垂直间距
    mainLayout->setVerticalSpacing(10);
    // 设置外间距
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->rowStretch(0);
    mainLayout->columnStretch(0);
    setLayout(mainLayout);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
    init();
}

void CommonRulePage::init(){

    QList<QString> queryList;
    queryList.append("maxlimit");
    queryList.append("personNameLen_min");
    queryList.append("personNameLen_max");
    queryList.append("personNamePermit_char");
    queryList.append("personCardtypeTime_interval");
    queryList.append("personCard_numLen_min");
    queryList.append("personCard_numLen_max");
    queryList.append("personCard_addLen_min");
    queryList.append("personCard_addLen_max");
    queryList.append("unitNameLen_min");
    queryList.append("unitNameLen_max");
    queryList.append("unitCardtypeTime_interval");
    queryList.append("unitCard_numLen_min");
    queryList.append("unitCard_numLen_max");
    queryList.append("unitCard_addLen_min");
    queryList.append("unitCard_addLen_max");

    QMap<QString,QString> map = xmlConfig->readCommonRuleValue(queryList);
    maxlimitEdit->setText(map.value("maxlimit"));
    personNameLen_minEdit->setText(map.value("personNameLen_min"));
    personNameLen_maxEdit->setText(map.value("personNameLen_max"));
    personNamePermit_charEdit->setText(map.value("personNamePermit_char"));
    personCardtypeTime_intervalEdit->setText(map.value("personCardtypeTime_interval"));
    personCard_numLen_minEdit->setText(map.value("personCard_numLen_min"));
    personCard_numLen_maxEdit->setText(map.value("personCard_numLen_max"));
    personCard_addLen_minEdit->setText(map.value("personCard_addLen_min"));
    personCard_addLen_maxEdit->setText(map.value("personCard_addLen_max"));
    unitNameLen_minEdit->setText(map.value("unitNameLen_min"));
    unitNameLen_maxEdit->setText(map.value("unitNameLen_max"));
    unitCardtypeTime_intervalEdit->setText(map.value("unitCardtypeTime_interval"));
    unitCard_numLen_minEdit->setText(map.value("unitCard_numLen_min"));
    unitCard_numLen_maxEdit->setText(map.value("unitCard_numLen_max"));
    unitCard_addLen_minEdit->setText(map.value("unitCard_addLen_min"));
    unitCard_addLen_maxEdit->setText(map.value("unitCard_addLen_max"));
}

void CommonRulePage::save(){
    qDebug()<<" ===================in save==================== ";
    QMap<QString,QString> map;
    map.insert("maxlimit", maxlimitEdit->text());
    map.insert("personNameLen_min", personNameLen_minEdit->text());
    map.insert("personNameLen_max", personNameLen_maxEdit->text());
    map.insert("personNamePermit_char", personNamePermit_charEdit->text());
    map.insert("personCardtypeTime_interval", personCardtypeTime_intervalEdit->text());
    map.insert("personCard_numLen_min", personCard_numLen_minEdit->text());
    map.insert("personCard_numLen_max", personCard_numLen_maxEdit->text());
    map.insert("personCard_addLen_min", personCard_addLen_minEdit->text());
    map.insert("personCard_addLen_max", personCard_addLen_maxEdit->text());
    map.insert("unitNameLen_min", unitNameLen_minEdit->text());
    map.insert("unitNameLen_max", unitNameLen_maxEdit->text());
    map.insert("unitCardtypeTime_interval", unitCardtypeTime_intervalEdit->text());
    map.insert("unitCard_numLen_min", unitCard_numLen_minEdit->text());
    map.insert("unitCard_numLen_max", unitCard_numLen_maxEdit->text());
    map.insert("unitCard_addLen_min", unitCard_addLen_minEdit->text());
    map.insert("unitCard_addLen_max", unitCard_addLen_maxEdit->text());
    xmlConfig->writeCommonRuleValue(map);
}


//UserTypePage::UserTypePage(QWidget *parent) : QWidget(parent)
//{
//    QLabel *serverLabel = new QLabel(QStringLiteral("用户类型:"));
//     QVBoxLayout *mainLayout = new QVBoxLayout;
//     mainLayout->addWidget(serverLabel);
//     mainLayout->addStretch(1);
//     setLayout(mainLayout);
//}

//BizTypePage::BizTypePage(QWidget *parent,QString menu): QWidget(parent)
  BizTypePage::BizTypePage(QString menu): QWidget()
{
    table = new QTableWidget;
    table->setColumnCount(1);
    QTableWidgetItem *item0 = new QTableWidgetItem;
    item0->setText("值");
    table->setHorizontalHeaderItem(0, item0);

    //////////////////////////////////////////////
        //设定标题列的宽度
    table->setColumnWidth(0, 200);

    //插入数据
    value=xmlConfig->readValue(menu);
    currnt_menu = menu;
    table->setRowCount(value.count());
//    bool ok=true;
    qDebug()<<"value count "<<value.count();
    for(int i=0; i<value.size(); i++){
        table->setItem(i, 0, new QTableWidgetItem(value.at(i)));
//        qDebug()<<"value is "<<value.at(i);
    }



    table->horizontalHeader()->setVisible(true);
    table->verticalHeader()->setVisible(false);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    //增加行按钮
    QPushButton *addButton = new QPushButton;
    addButton->setText("+");
    addButton->setStyleSheet("width:30px");

    //删除行按钮
    QPushButton *delButton = new QPushButton;
    delButton->setText("-");
    delButton->setStyleSheet("width:30px");

    //保存按钮
    QPushButton *saveButton = new QPushButton;
    saveButton->setText("save");

    connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
    connect(delButton, SIGNAL(clicked()), this, SLOT(del()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(valueSave()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(delButton);
    buttonLayout->addWidget(saveButton);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(table);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setSpacing(1);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setLayout(mainLayout);
}
void BizTypePage::add(){
    //结尾添加一行
    int row = table->rowCount();
    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem("new row"));
}
void BizTypePage::del(){
    qDebug()<<"del方法"<<table;
    //空行无法选择
        QList<QTableWidgetItem*> items = table->selectedItems();
        //选择模式器
        QItemSelectionModel *smodel = table->selectionModel();
        //获取所有的选择索引
        QModelIndexList slist = smodel->selectedIndexes();

        //获取所有被选中的行号
        std::set<int> rows;
        for (int i = 0; i < slist.size(); i++)
        {
            //重复的插入失败
            rows.insert(slist[i].row());
        }

       //给用户提示
        QString msg = QStringLiteral("您确认删除:");

        for (std::set<int>::iterator itr = rows.begin(); itr != rows.end(); itr++)
        {
            QTableWidgetItem *item = table->item(*itr, 0);
            msg += "[";
            msg += QString::number(*itr+1);
            msg += ":";
            if (item)
                msg += item->text();
            msg += "]";
        }
        int re = QMessageBox::information(this, "", msg, QStringLiteral("确认"), QStringLiteral("取消"));
        if (re != 0)
        {
            return;
        }

        //删除多行
        for (;;)
        {
            //获取所有的选择索引
            QModelIndexList s = smodel->selectedIndexes();
            if (s.size() <= 0) break;
            //每次只删除一行
            table->removeRow(s[0].row());
        }
}

void BizTypePage::valueSave(){
    qDebug()<<" ===================in valueSave==================== ";
    qDebug()<<"row count is "<<table->rowCount();
    qDebug()<<"col count is "<<table->columnCount();
    value.clear();
    for(int i=0; i<table->rowCount();i++){
        value.append(table->item(i,0)->text());
    }
    xmlConfig->writeValue(currnt_menu,value);
}
