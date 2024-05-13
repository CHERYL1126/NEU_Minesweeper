#ifndef mouseaction_H
#define mouseaction_H
#include<QPushButton>
#include <QWidget>
#include <QMouseEvent>


class mouseaction : public QPushButton
{
    Q_OBJECT

public:
        explicit mouseaction(QWidget *p = nullptr);
        void mousePressEvent(QMouseEvent *e);                    //重载按下事件
        void mouseReleaseEvent(QMouseEvent *e);                  //重载抬起事件
        ~mouseaction(){}

signals:
    void pressright();
    void pressleft();
    void pressRandL(); // 左右键同时按下
    void releaseright();
    void releaseleft();
    void ReleaseRandL(); // 左右键同时释放

private:
    bool isleftPressed = false;
    bool isrightPressed = false;
    bool bothPressed;
    void checkBothPressed();
    void checkBothReleased();

};

#endif // mouseaction_H
