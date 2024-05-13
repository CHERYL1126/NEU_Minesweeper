#include "login.h"
#include "ui_login.h"
#include"fixpw.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    //登录界面
    //设置固定大小
    setFixedSize(500,400);
    //设置图标
    //setWindowIcon("");
    //设置标题
    setWindowTitle("登录界面");
    //退出
    connect(ui->tuichu,&QPushButton::clicked,this,&login::close);
    connect(ui->myclear,SIGNAL(clicked()),this,SLOT(reclicked()));
    connect(ui->mylogin,SIGNAL(clicked()),this,SLOT(myloginpress()));
    connect(this,SIGNAL(loginclose()),this,SLOT(close()));
    connect(ui->fix,&QPushButton::clicked,[=](){
        //pwclear();
        fixpw * a = new fixpw(this);
        a->setWindowModality(Qt::WindowModal);//Qt::WindowModal 半模态：窗口级模态对话框，阻塞父窗口、父窗口的父窗口及兄弟窗口。
        a->setAttribute(Qt::WA_DeleteOnClose);//这设置了一个属性，使得当fixpw窗口关闭时，Qt会自动删除该窗口对象。这有助于避免内存泄漏，因为你不需要手动删除这个对象。
        a->show();//通过show()方法显示这个fixpw窗口
    });

    ui->initpw->setEchoMode(QLineEdit::Password);//是将 ui 指向的 UI 类中的 initpw 文本输入框设置为密码模式，从而隐藏用户输入的文本内容。
    readInfoFile();
    //myname="fanfan";
    //myPassword="dog";
    readFile();

}


void login::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/p/start.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void login::pwclear()
{

    reclicked();
}

login::~login()
{
    delete ui;
}


void login::myloginpress()
{
    QString name = ui->initname->text();
    QString password = ui->initpw->text();
    if(name==myname&&password==myPassword)
    {
        emit(loginbegin());
        writeFile();
        emit(loginclose());
    }
    else
        QMessageBox::warning(this,"warning","账号或密码错误！");
}

void login::reclicked()
{
    ui->initpw->clear();
    ui->initname->clear();
    readInfoFile();


}
void login::readInfoFile()
{
    QFile file("D:/mycode/QTcode/minesweep/name.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Failed";
    }
    else
    {
        qDebug()<<"successfully";
    }
    myname=file.readAll();
    qDebug()<<myname;
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
void login::readFile()
{
    QFile file("D:/mycode/QTcode/minesweep/login.json");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Failed";
    }
    else
    {
        qDebug()<<"successfully";
    }
    QJsonDocument ojs(QJsonDocument::fromJson(file.readAll()));
    QJsonObject obj =ojs.object();
    QString saveNameF=obj.value("SAVE_NAME").toString();
    QString savePwF=obj.value("SAVE_PASSWORD").toString();
    //QJsonObject封装了一个JSON对象
    //QJsonDocument通过成员函数object()检索文档中的数组和对象，然后读取JSON数据，或者修改数据
    putmessage(saveNameF,savePwF);

}

void login::putmessage(QString a,QString b)
{
    qDebug()<<a<<"^^^"<<b;
    if(a=="1")
    {
        ui->initname->setText(myname);
        ui->checkName->setChecked(true);
    }
    if(b=="1")
    {
        ui->initpw->setText(myPassword);
        ui->checkPw->setChecked(true);
    }
}

void login::writeFile()
{
    QFile file("D:/mycode/QTcode/minesweep/login.json");
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"Failed";
    }
    else
    {
        qDebug()<<"successfully";
    }
    QJsonObject obj;

    bool flag1 = ui->checkName->isChecked();
    if(flag1==true)
    {
        obj["SAVE_NAME"]="1";
    }
    else
    {
        obj["SAVE_NAME"]="0";
    }
    bool flag2 = ui->checkPw->isChecked();
    if(flag2==true)
    {
        obj["SAVE_PASSWORD"]="1";
    }
    else
    {
        obj["SAVE_PASSWORD"]="0";
    }

    QJsonDocument jdo(obj);
    file.write(jdo.toJson());
    file.flush();
}

