#include "fixpw.h"
#include "ui_fixpw.h"
#include "ui_login.h"
fixpw::fixpw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fixpw)
{
    ui->setupUi(this);
    //设置固定大小
    setFixedSize(500,400);
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(fix()));
    connect(this,SIGNAL(fixpwclose()),this,SLOT(close()));

}
void fixpw::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/p/npc.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
fixpw::~fixpw()
{
    delete ui;
}

void fixpw::fix()
{
    QString pripw = ui->linepri->text();
    pwreadInfo();
    if(pripw==myPassword)
    {
        QString newpw = ui->linenew->text();
        QString conpw = ui->linecon->text();
        if(newpw==conpw)
        {
            pw=newpw;
            pwWriteFrom();
            //readInfoFile();
            emit(fixpwclose());

            //emit(fixpwok());
        }
        else
            QMessageBox::warning(this,"warning","两次输入的密码不相同！");
    }
    else
        QMessageBox::warning(this,"warning","原密码错误！");

}

void fixpw::pwreadInfo()
{

    QFile file1("D:/mycode/QTcode/minesweep/pw.txt");
    if(!file1.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Failed";
    }
    else
    {
        qDebug()<<"successfully";
    }
    myPassword=file1.readAll();
    qDebug()<<myPassword;

}

void fixpw::pwWriteFrom()
{

    QFile file("D:/mycode/QTcode/minesweep/pw.txt");
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"Failed";
    }
    else
    {
        qDebug()<<"successfully";
    }
    file.write(pw.toUtf8());
    file.flush();

}
