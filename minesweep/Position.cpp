#include "Position.h"
#include "ui_Position.h"

Position::Position(QWidget *p) :
    QMainWindow(p),
    ui(new Ui::Position)
{
    ui->setupUi(this);
    ui->PositionList->setStyleSheet("background:transparent;border-width:0;border-style:outset");//设置无边框且透明
}

Position::~Position()
{
    delete ui;
}
