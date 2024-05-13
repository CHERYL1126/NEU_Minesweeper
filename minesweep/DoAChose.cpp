#include "DoAChose.h"
#include "ui_DoAChose.h"
//#include "cube.h"
#include<QRadioButton>
#include<mainWindow.h>
#include<QDebug>
#include<QMessageBox>
DoAChose:: DoAChose (MainWindow *p) :
    QMainWindow(p),
    ui(new Ui::DoAChose)
{
    ui->setupUi(this);

    setWindowTitle("游戏难度选择");


    //apply连接
    connect(ui->apply,&QPushButton::clicked,[=](){

        //保存默认的信息
        if(ui->defau->isChecked()){
            saveDef(p);
        }

        //保存用户自定义的信息，不关闭窗口
        else if(ui->custom->isChecked()){
            saveCus(p);
        }

    });
    //affirm连接
    connect(ui->affirm,&QPushButton::clicked,[=](){

        //保存默认的信息
        if(ui->defau->isChecked())
        {
            saveDef(p);
            this->close();
        }

        //保存用户自定义的信息,如果信息没出错，则关闭选择窗口
        else if(ui->custom->isChecked())
        {
            if(saveCus(p))
            this->close();
        }

    });
    //cancel连接
    connect(ui->cancel,&QPushButton::clicked,this,&QMainWindow::close);
}


DoAChose::~DoAChose()
{

    delete ui;
}

//设置游戏默认参数
void DoAChose::saveDef(MainWindow *p)
{
    if(ui->highLevel->isChecked())
    {
        p->setHeight(35);
        p->setWidth(16);
        p->setMineNumber(200);
    }
    else if(ui->midLevel->isChecked())
    {
        p->setHeight(25);
        p->setWidth(16);
        p->setMineNumber(100);
    }

    else if(ui->lowLevel->isChecked())
    {
        p->setHeight(10);
        p->setWidth(10);
        p->setMineNumber(10);
    }
    p->origin();
}

//设置游戏自定义参数
bool DoAChose::saveCus(MainWindow *p){
    int h = ui->height->text().toInt();
    int w = ui->wid->text().toInt();
    int m = ui->mineNumber->text().toInt();
    if((0<h && h<=40) && (0<w && w<= 40)&&(m<=h*w))
    {
        p->setHeight(h);
        p->setWidth(w);
        p->setMineNumber(m);
        p->origin();
        return true;
    }
    else
    {
        QMessageBox::warning(this,"error","您输入的尺寸超出选择范围（高度0-40）（宽度0-40）(雷数不超出面积），自定义失败",QMessageBox::Ok);
        return false;
    }
}
