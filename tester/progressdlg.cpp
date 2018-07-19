#include "progressdlg.h"
#include <QProgressDialog>
#include <QFont>

ProgressDlg::ProgressDlg(QWidget *parent)
    : QDialog(parent)
{
    QFont font("ZYSong18030",12);
    setFont(font);
    setWindowTitle(QStringLiteral("Progress"));

    FileNum = new QLabel;
    FileNum->setText(QStringLiteral("文件数目："));
    FileNumLineEdit = new QLineEdit;
    FileNumLineEdit->setText(QStringLiteral("100000"));

    ProgressType = new QLabel;
    ProgressType->setText(QStringLiteral("显示类型："));
    comboBox = new QComboBox;
    comboBox->addItem(QStringLiteral("ProgressBar"));
    comboBox->addItem((QStringLiteral("progressDialog")));

    progressBar = new QProgressBar;

    startBtn = new QPushButton();
    startBtn->setText(QStringLiteral("开始"));

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(FileNum,0,0);
    mainLayout->addWidget(FileNumLineEdit,0,1);
    mainLayout->addWidget(ProgressType,1,0);
    mainLayout->addWidget(comboBox,1,1);
    mainLayout->addWidget(progressBar,2,0,1,2);
    mainLayout->addWidget(startBtn,3,1);

    mainLayout->setMargin((15));
    mainLayout->setSpacing(10);

    connect(startBtn,SIGNAL(clicked()),this,SLOT(startProgress()));

}

void ProgressDlg::startProgress()
{
    bool ok;
    int num = FileNumLineEdit->text().toInt(&ok);

    if(comboBox->currentIndex()==0)
    {
        progressBar->setRange(0,num);
        for(int i=1;i<num+1;i++)
        {
            progressBar->setValue(i);
        }
    }
    else if(comboBox->currentIndex()==1)	//采用进度对话框显示进度
    {
        //创建一个进度对话框
        QProgressDialog *progressDialog=new QProgressDialog(this);
        QFont font("ZYSong18030",12);
        progressDialog->setFont(font);
        progressDialog->setWindowModality(Qt::WindowModal);     //(d)
        progressDialog->setMinimumDuration(5);					//(e)
        progressDialog->setWindowTitle(QStringLiteral("Please Wait"));		//(f)
        progressDialog->setLabelText(QStringLiteral("Copying..."));         //(g)
        progressDialog->setCancelButtonText(QStringLiteral("Cancel"));		//(h)
        progressDialog->setRange(0,num);	  //设置进度对话框的步进范围
        for(int i=1;i<num+1;i++)
        {
            progressDialog->setValue(i);						//(i)
            if(progressDialog->wasCanceled())					//(j)
                return;
        }
    }
}
ProgressDlg::~ProgressDlg()
{

}
