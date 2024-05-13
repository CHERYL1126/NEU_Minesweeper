#ifndef MainWindow_H
#define MainWindow_H
#include "login.h"
#include "fixpw.h"
//#include "cube.h"
#include"mouseaction.h"
#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *p = nullptr);
    ~MainWindow();
    void origin();//初始化界面
    void originMine();//初始化雷
    void myaction();//按键和鼠标的联系
    int numberAcount(int,int);//计算地雷周围的数字
    void mineDfs(int,int,int);//翻开0值格子
    void judge(bool);//游戏结束判断结果
    void turn();//用于翻开格子
    void setHeight(int);
    void setWidth(int);
    void setMineNumber(int);
private:
    Ui::MainWindow *ui;
    login * mylog;
    fixpw*myfixpw;
    QTimer * timer;
    int remainder;
    QVector<QVector<mouseaction*>> map;                   //用于显示雷区布局的数组，每一个格子使用一个Button表示
    QVector<QVector<int>> mineTable;
    int mineCount;                                       //用于雷的计数：每次插旗子减少一个雷，每次取消旗子增加一个雷
    int second = 0;                                      //定义秒数，接收定时，并输出
    bool isTimeRun =false;                               //开始计时标记，设置为true才会触发计时
    int height = 10;//雷区高度
    int width = 10;//雷区宽度
    int mine = 10;//雷的数量
//QVector是封装了一个数组的模板类，内部维护数组，提供给外部一些访问方法
//QVector<类型>>名称
};

#endif // MainWindow_H
