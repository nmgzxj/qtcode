#include "setup.h"
#include "setuppages.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QDebug>

Setup::Setup()
{
    setWindowTitle("参数设置");
//    QTextEdit *edit=new QTextEdit;
//    edit->setText(loadXml("../../../config/config-autoid.xml"));
//    setCentralWidget(edit);
    resize(500,300);
    contentsWidget = new QTreeWidget;
//    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMaximumWidth(200);

    contentsWidget->setHeaderItem(new QTreeWidgetItem());
    contentsWidget->clear();
    contentsWidget->headerItem()->setText(0,QStringLiteral("设置项"));
    contentsWidget->setHeaderHidden(true);
    //插入顶级节点
    int menu_index=0;
    contentsWidget->addTopLevelItem(new QTreeWidgetItem());
    contentsWidget->topLevelItem(menu_index)->setText(0, tr("autoid"));
    contentsWidget->topLevelItem(menu_index)->addChild(new QTreeWidgetItem({"Items"}));
    contentsWidget->topLevelItem(menu_index)->addChild(new QTreeWidgetItem({"字段分隔符"}));
    contentsWidget->topLevelItem(menu_index)->addChild(new QTreeWidgetItem({"字段个数"}));
    contentsWidget->topLevelItem(menu_index)->addChild(new QTreeWidgetItem({"时间格式"}));

    menu_index++;
    contentsWidget->addTopLevelItem(new QTreeWidgetItem());
    contentsWidget->topLevelItem(menu_index)->setText(0, tr("检测规则"));
    contentsWidget->topLevelItem(menu_index)->addChild(new QTreeWidgetItem({ "个人用户姓名" }));
    contentsWidget->topLevelItem(menu_index)->child(0)->addChild(new QTreeWidgetItem({ "comon-rule" }));
    contentsWidget->topLevelItem(menu_index)->child(0)->addChild(new QTreeWidgetItem({ "match-rule" }));
    contentsWidget->topLevelItem(menu_index)->addChild(new QTreeWidgetItem({ "单位/行业用户名称" }));
    contentsWidget->topLevelItem(menu_index)->child(1)->addChild(new QTreeWidgetItem({ "comon-rule" }));
    contentsWidget->topLevelItem(menu_index)->child(1)->addChild(new QTreeWidgetItem({ "match-rule" }));
    contentsWidget->topLevelItem(menu_index)->addChild(new QTreeWidgetItem({ "证件号码" }));
    contentsWidget->topLevelItem(menu_index)->child(2)->addChild(new QTreeWidgetItem({ "comon-rule" }));
    contentsWidget->topLevelItem(menu_index)->child(2)->addChild(new QTreeWidgetItem({ "match-rule" }));
    contentsWidget->topLevelItem(menu_index)->addChild(new QTreeWidgetItem({ "证件地址" }));
    contentsWidget->topLevelItem(menu_index)->child(3)->addChild(new QTreeWidgetItem({ "addr-rule" }));
    contentsWidget->topLevelItem(menu_index)->child(3)->addChild(new QTreeWidgetItem({ "match-rule" }));
    contentsWidget->topLevelItem(menu_index)->addChild(new QTreeWidgetItem({ "公共参数" }));
//    contentsWidget->topLevelItem(menu_index)->child(4)->addChild(new QTreeWidgetItem({ "重号率阈值" }));
//    contentsWidget->topLevelItem(menu_index)->child(4)->addChild(new QTreeWidgetItem({ "个人用户规则" }));
//    contentsWidget->topLevelItem(menu_index)->child(4)->addChild(new QTreeWidgetItem({ "单位/行业用户规则" }));

    menu_index++;
    contentsWidget->addTopLevelItem(new QTreeWidgetItem());
    contentsWidget->topLevelItem(menu_index)->setText(0, tr("系统参数"));

    menu_index++;
    contentsWidget->addTopLevelItem(new QTreeWidgetItem());
    contentsWidget->topLevelItem(menu_index)->setText(0, tr("用户类型"));

    menu_index++;
    contentsWidget->addTopLevelItem(new QTreeWidgetItem());
    contentsWidget->topLevelItem(menu_index)->setText(0, tr("工作路径"));

    menu_index++;
    contentsWidget->addTopLevelItem(new QTreeWidgetItem());
    contentsWidget->topLevelItem(menu_index)->setText(0, tr("业务类型"));
    contentsWidget->topLevelItem(menu_index)->addChild(new QTreeWidgetItem({ "类型" }));
    contentsWidget->topLevelItem(menu_index)->child(0)->addChild(new QTreeWidgetItem({ "移动" }));
    contentsWidget->topLevelItem(menu_index)->child(0)->addChild(new QTreeWidgetItem({ "固定" }));
    contentsWidget->topLevelItem(menu_index)->addChild(new QTreeWidgetItem({ "业务状态" }));
    contentsWidget->topLevelItem(menu_index)->child(1)->addChild(new QTreeWidgetItem({ "非实名停机" }));
    contentsWidget->topLevelItem(menu_index)->child(1)->addChild(new QTreeWidgetItem({ "不在网" }));

    menu_index++;
    contentsWidget->addTopLevelItem(new QTreeWidgetItem());
    contentsWidget->topLevelItem(menu_index)->setText(0, tr("证件类型"));
    contentsWidget->topLevelItem(menu_index)->addChild(new QTreeWidgetItem({ "个人证件" }));
    contentsWidget->topLevelItem(menu_index)->child(0)->addChild(new QTreeWidgetItem({ "居民身份证" }));
    contentsWidget->topLevelItem(menu_index)->child(0)->addChild(new QTreeWidgetItem({ "临时居民身份证" }));
    contentsWidget->topLevelItem(menu_index)->child(0)->addChild(new QTreeWidgetItem({ "户口薄" }));
    contentsWidget->topLevelItem(menu_index)->child(0)->addChild(new QTreeWidgetItem({ "中国人民解放军军人身份证件" }));
    contentsWidget->topLevelItem(menu_index)->child(0)->addChild(new QTreeWidgetItem({ "中国人民武装警察身份证件" }));
    contentsWidget->topLevelItem(menu_index)->child(0)->addChild(new QTreeWidgetItem({ "港澳居民来往内地通行证" }));
    contentsWidget->topLevelItem(menu_index)->child(0)->addChild(new QTreeWidgetItem({ "台湾居民来往大陆通行证" }));
    contentsWidget->topLevelItem(menu_index)->child(0)->addChild(new QTreeWidgetItem({ "外国公民护照" }));
    contentsWidget->topLevelItem(menu_index)->child(0)->addChild(new QTreeWidgetItem({ "法律、行政法规和国家规定的其他有效身份证件" }));
    contentsWidget->topLevelItem(menu_index)->child(0)->addChild(new QTreeWidgetItem({ "非法律、行政法规和国家规定的有效身份证件" }));
    contentsWidget->topLevelItem(menu_index)->addChild(new QTreeWidgetItem({ "单位证件" }));
    contentsWidget->topLevelItem(menu_index)->child(1)->addChild(new QTreeWidgetItem({ "组织机构代码证" }));
    contentsWidget->topLevelItem(menu_index)->child(1)->addChild(new QTreeWidgetItem({ "营业执照" }));
    contentsWidget->topLevelItem(menu_index)->child(1)->addChild(new QTreeWidgetItem({ "事业单位法人证书或者社会团体法人登记证书" }));
    contentsWidget->topLevelItem(menu_index)->child(1)->addChild(new QTreeWidgetItem({ "法律、行政法规和国家规定的其他有效证件或者证明文件" }));
    contentsWidget->topLevelItem(menu_index)->child(1)->addChild(new QTreeWidgetItem({ "非法律、行政法规和国家规定的有效身份证件" }));

//        插入孙节点
    if(contentsWidget->topLevelItem(1)->child(0)->child(0)->isSelected()){
        qDebug()<<contentsWidget->topLevelItem(1)->child(0)->child(0)<<"被选中";
    }




    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(new ColumnPage);//0 Items
    pagesWidget->addWidget(new DelimiterPage);//1 字段分隔符
    pagesWidget->addWidget(new ItemnumPage);//2 字段个数
    pagesWidget->addWidget(new DateformatPage);//3 时间格式
    pagesWidget->addWidget(new SystemPage);//4
    pagesWidget->addWidget(new BizTypePage("个人用户姓名comon-rule"));//5
    pagesWidget->addWidget(new BizTypePage("个人用户姓名match-rule"));//6
    pagesWidget->addWidget(new BizTypePage("行业用户姓名comon-rule"));//7
    pagesWidget->addWidget(new BizTypePage("行业用户姓名match-rule"));//8
    pagesWidget->addWidget(new BizTypePage("证件号码comon-rule"));//9
    pagesWidget->addWidget(new BizTypePage("证件号码match-rule"));//10
    pagesWidget->addWidget(new BizTypePage("证件地址addr-rule"));//11
    pagesWidget->addWidget(new BizTypePage("证件地址match-rule"));//12
    pagesWidget->addWidget(new CommonRulePage);//13
    pagesWidget->addWidget(new BizTypePage("个人用户规则"));//14
    pagesWidget->addWidget(new BizTypePage("单位/行业用户规则"));//15
    pagesWidget->addWidget(new SystemPage);//13
    pagesWidget->addWidget(new UserTypePage);//14
    pagesWidget->addWidget(new WorkPathPage);//15
    pagesWidget->addWidget(new BizTypePage("业务类型移动"));//16
    pagesWidget->addWidget(new BizTypePage("业务类型固定"));//17
    pagesWidget->addWidget(new BizTypePage("业务状态非实名停机"));//18
    pagesWidget->addWidget(new BizTypePage("业务状态不在网"));//19
    pagesWidget->addWidget(new BizTypePage("个人证件居民身份证"));//20
    pagesWidget->addWidget(new BizTypePage("个人证件临时居民身份证"));//21
    pagesWidget->addWidget(new BizTypePage("个人证件户口薄"));//22
    pagesWidget->addWidget(new BizTypePage("个人证件中国人民解放军军人身份证件"));
    pagesWidget->addWidget(new BizTypePage("个人证件中国人民武装警察身份证件"));
    pagesWidget->addWidget(new BizTypePage("个人证件港澳居民来往内地通行证"));
    pagesWidget->addWidget(new BizTypePage("个人证件台湾居民来往大陆通行证"));
    pagesWidget->addWidget(new BizTypePage("个人证件外国公民护照"));
    pagesWidget->addWidget(new BizTypePage("个人证件法律、行政法规和国家规定的其他有效身份证件"));
    pagesWidget->addWidget(new BizTypePage("个人证件非法律、行政法规和国家规定的有效身份证件"));
    pagesWidget->addWidget(new BizTypePage("单位证件组织机构代码证"));
    pagesWidget->addWidget(new BizTypePage("单位证件营业执照"));
    pagesWidget->addWidget(new BizTypePage("单位证件事业单位法人证书或者社会团体法人登记证书"));
    pagesWidget->addWidget(new BizTypePage("单位证件法律、行政法规和国家规定的其他有效证件或者证明文件"));
    pagesWidget->addWidget(new BizTypePage("单位证件非法律、行政法规和国家规定的有效身份证件"));
    pagesWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QPushButton *closeButton = new QPushButton(tr("Close"));

    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(contentsWidget, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(slotItemPressed(QTreeWidgetItem*)));


    //水平布局菜单和标签页
    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);


    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
//    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    setLayout(mainLayout);

    pagesWidget->setCurrentIndex(0);
}



void Setup::slotItemPressed(QTreeWidgetItem *item)
{
    // 注意关联的是itempressed，经测试：itemclicled不行，不能区分左右键。
    if (item->parent() == NULL)     // 根节点
    {
        qDebug()<<"root:"<<item->text(0);
    }
    else
    {
         qDebug()<<"child:"<<item->text(0);
//        if (qApp->mouseButtons() == Qt::RightButton)
//        {
//            QMenu menu(contentsWidget);
//            menu.addAction(m_pItemAction[DeleteChild]);
//            menu.exec(QCursor::pos());
//        }
    }

    if(item->text(0)=="Items"){
        pagesWidget->setCurrentIndex(0);
        qDebug()<<"菜单命中"<<item->text(0);
    }
    else if(item->text(0)=="字段分隔符"){
        pagesWidget->setCurrentIndex(1);
        qDebug()<<"菜单命中"<<item->text(0);
    }
    else if(item->text(0)=="字段个数"){
        pagesWidget->setCurrentIndex(2);
        qDebug()<<"菜单命中"<<item->text(0);
    }
    else if(item->text(0)=="时间格式"){
        pagesWidget->setCurrentIndex(3);
        qDebug()<<"菜单命中"<<item->text(0);
    }
//    else if(item->text(0)=="检测规则"){
//        pagesWidget->setCurrentIndex(4);
//        qDebug()<<"菜单命中"<<item->text(0);
//    }
    else if(item->text(0)=="comon-rule"&&item->parent()->text(0)=="个人用户姓名"){
        pagesWidget->setCurrentIndex(5);
        qDebug()<<"菜单命中"<<item->text(0);
    }
    else if(item->text(0)=="match-rule"&&item->parent()!=NULL&&"个人用户姓名"==item->parent()->text(0)){
        pagesWidget->setCurrentIndex(6);
        qDebug()<<"菜单命中"<<item->text(0);
    }
    else if(item->text(0)=="comon-rule"&&item->parent()->text(0)=="单位/行业用户名称"){
        pagesWidget->setCurrentIndex(7);
        qDebug()<<"菜单命中"<<item->text(0);
    }
    else if(item->text(0)=="match-rule"&&item->parent()->text(0)=="单位/行业用户名称"){
        pagesWidget->setCurrentIndex(8);
        qDebug()<<"菜单命中"<<item->text(0);
    }
    else if(item->text(0)=="comon-rule"&&item->parent()->text(0)=="证件号码"){
        pagesWidget->setCurrentIndex(9);
        qDebug()<<"菜单命中"<<item->text(0);
    }
    else if(item->text(0)=="match-rule"&&item->parent()!=NULL&&"证件号码"==item->parent()->text(0)){
        pagesWidget->setCurrentIndex(10);
        qDebug()<<"菜单命中"<<item->text(0);
    }
    else if(item->text(0)=="addr-rule"&&item->parent()->text(0)=="证件地址"){
        pagesWidget->setCurrentIndex(11);
        qDebug()<<"菜单命中"<<item->text(0);
    }
    else if(item->text(0)=="match-rule"&&item->parent()->text(0)=="证件地址"){
        pagesWidget->setCurrentIndex(12);
        qDebug()<<"菜单命中"<<item->text(0);
    }
    else if(item->text(0)=="公共参数"){
        pagesWidget->setCurrentIndex(13);
        qDebug()<<"菜单命中"<<item->text(0);
    }

    //    else if(item->text(0)=="重号率阈值"){
//        pagesWidget->setCurrentIndex(13);
//        qDebug()<<"菜单命中"<<item->text(0);
//    }
//    else if(item->text(0)=="个人用户规则"){
//        pagesWidget->setCurrentIndex(14);
//        qDebug()<<"菜单命中"<<item->text(0);
//    }
//    else if(item->text(0)=="单位/行业用户规则"){
//        pagesWidget->setCurrentIndex(15);
//        qDebug()<<"菜单命中"<<item->text(0);
//    }
    else if(item->text(0)=="系统参数"){
        pagesWidget->setCurrentIndex(16);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="用户类型"){
        pagesWidget->setCurrentIndex(17);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="工作路径"){
        pagesWidget->setCurrentIndex(18);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="移动"){//&&item->parent()->text(0)=="业务类型"
        pagesWidget->setCurrentIndex(19);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="固定"){//&&item->parent()->text(0)=="业务类型"
        pagesWidget->setCurrentIndex(20);
        qDebug()<<"菜单命中"<<item->text(0);
    }
    else if(item->text(0)=="非实名停机"&&item->parent()->text(0)=="业务状态"){
        pagesWidget->setCurrentIndex(21);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="不在网"&&item->parent()->text(0)=="业务状态"){
        pagesWidget->setCurrentIndex(22);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="居民身份证"&&item->parent()->text(0)=="个人证件"){
        pagesWidget->setCurrentIndex(23);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="临时居民身份证"&&item->parent()->text(0)=="个人证件"){
        pagesWidget->setCurrentIndex(24);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="户口薄"&&item->parent()->text(0)=="个人证件"){
        pagesWidget->setCurrentIndex(25);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="中国人民解放军军人身份证件"&&item->parent()->text(0)=="个人证件"){
        pagesWidget->setCurrentIndex(26);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="中国人民武装警察身份证件"&&item->parent()->text(0)=="个人证件"){
        pagesWidget->setCurrentIndex(27);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="港澳居民来往内地通行证"&&item->parent()->text(0)=="个人证件"){
        pagesWidget->setCurrentIndex(28);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="台湾居民来往大陆通行证"&&item->parent()->text(0)=="个人证件"){
        pagesWidget->setCurrentIndex(29);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="外国公民护照"&&item->parent()->text(0)=="个人证件"){
        pagesWidget->setCurrentIndex(30);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="法律、行政法规和国家规定的其他有效身份证件"&&item->parent()->text(0)=="个人证件"){
        pagesWidget->setCurrentIndex(31);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="非法律、行政法规和国家规定的有效身份证件"&&item->parent()->text(0)=="个人证件"){
        pagesWidget->setCurrentIndex(32);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="组织机构代码证"&&item->parent()->text(0)=="单位证件"){
        pagesWidget->setCurrentIndex(33);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="营业执照"&&item->parent()->text(0)=="单位证件"){
        pagesWidget->setCurrentIndex(34);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="事业单位法人证书或者社会团体法人登记证书"&&item->parent()->text(0)=="单位证件"){
        pagesWidget->setCurrentIndex(35);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="法律、行政法规和国家规定的其他有效证件或者证明文件"&&item->parent()->text(0)=="单位证件"){
        pagesWidget->setCurrentIndex(36);
        qDebug()<<"菜单命中"<<item->text(0);

    }
    else if(item->text(0)=="非法律、行政法规和国家规定的有效身份证件"&&item->parent()->text(0)=="单位证件"){
        pagesWidget->setCurrentIndex(37);
        qDebug()<<"菜单命中"<<item->text(0);

    }




}

