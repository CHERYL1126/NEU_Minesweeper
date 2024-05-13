#include "AsForUs.h"
#include "ui_AsForUs.h"

AsForUs::AsForUs(QWidget *p) :
    QMainWindow(p),
    ui(new Ui::AsForUs)
{
    ui->setupUi(this);
    ui->asopen->setStyleSheet("background:transparent;border-width:0;border-style:outset");//设置无边框且透明
    setWindowTitle("关于本游戏");
}

AsForUs::~AsForUs()
{
    delete ui;
}
