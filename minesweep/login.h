#ifndef LOGIN_H
#define LOGIN_H
//#include"fixpw.h"
#include <QMainWindow>
#include <QPainter>
#include <QMessageBox>
#include <QWidget>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QByteArray>
#include <QString>

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
    void paintEvent(QPaintEvent*);
    void readFile();
    void writeFile();
    void putmessage(QString a,QString b);
    void readInfoFile();
signals:

    void loginbegin();
    void loginclose();

public slots:
    void reclicked();
    void myloginpress();
    void pwclear();
private:

    Ui::login *ui;
    QString myname;
    QString myPassword;
};

#endif // LOGIN_H
