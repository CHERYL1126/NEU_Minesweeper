#ifndef DoAChose_H
#define DoAChose_H
//#include "cube.h"
#include"mainWindow.h"
#include <QMainWindow>

//选择游戏难度
namespace Ui {
class DoAChose;
}

class DoAChose : public QMainWindow
{
    Q_OBJECT

public:
    explicit DoAChose(MainWindow *p = nullptr)         ;//构造函数
    ~DoAChose()                                             ;//析构函数
    void saveDef(MainWindow * p)                       ;//储存玩家选择的默认的难度
    bool saveCus(MainWindow * p)                        ;//储存玩家自定义的参数并初始化，设置参数成功返回true
    int height = 10;//雷区高度
    int width = 10;//雷区宽度
    int mine = 10;//雷的数量
private:
    Ui::DoAChose *ui;
};

#endif // DoAChose_H
