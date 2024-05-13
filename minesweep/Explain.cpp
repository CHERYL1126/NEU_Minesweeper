#include "Explain.h"
#include "ui_explain.h"

Explain::Explain(QWidget *p) :
    QMainWindow(p),
    ui(new Ui::Explain)
{
    ui->setupUi(this);
    ui->ruler->setStyleSheet("background:transparent;border-width:0;border-style:outset");//设置无边框且透明
    setWindowTitle("游戏介绍");
}

Explain::~Explain()
{
    delete ui;
}
