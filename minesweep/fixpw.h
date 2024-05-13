#ifndef FIXPW_H
#define FIXPW_H
//#include "login.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QPainter>
namespace Ui {
class fixpw;
}

class fixpw : public QMainWindow
{
    Q_OBJECT

public:
    explicit fixpw(QWidget *parent = 0);
    ~fixpw();
    void pwreadInfo();
    void pwWriteFrom();
    void paintEvent(QPaintEvent*);
    //void readInfoFile();
signals:
    //void fixpwok();
    void fixpwclose();

public slots:
    void fix();
    //void pwclear();

private:
    Ui::fixpw *ui;
    QString myPassword;
    QString pw;
};

#endif // FIXPW_H
