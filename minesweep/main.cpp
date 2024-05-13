#include "mainWindow.h"
#include <QApplication>//包含一个应用程序类的头文件
//main程序入口，argc命令行变量的数量，argv命令行变量的数组

int main(int argc, char *argv[])
{
    //a为应用程序对象，在QT中，应用程序对象有且只有一个
    QApplication a(argc, argv);
    //窗口对象，myMainWindow的父类QWindow
    MainWindow w;
    //窗口对象，默认不会显示，必须要用show方法显示窗口
    //w.show();
    //让应用程序对象进入消息循环
    return a.exec();
}
