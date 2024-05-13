
#include "mouseaction.h"
//鼠标事件
mouseaction::mouseaction(QWidget *p) : QPushButton(p)
{

}


void mouseaction::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::RightButton) {
        isrightPressed = true;
        emit pressright();
        checkBothPressed();
    }
    if(ev->button() == Qt::LeftButton) {
        isleftPressed = true;
        emit pressleft();
        checkBothPressed();
    }
}

void mouseaction::mouseReleaseEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::RightButton) {
        isrightPressed = false;
        emit releaseright();
        checkBothReleased();
    }
    if(ev->button() == Qt::LeftButton) {
        isleftPressed = false;
        emit releaseleft();
        checkBothReleased();
    }
}

void mouseaction::checkBothPressed() {
    if(isleftPressed && isrightPressed) {
        bothPressed = true;
        emit pressRandL();
    }
}

void mouseaction::checkBothReleased() {
    if(!isleftPressed && !isrightPressed && bothPressed) {
        bothPressed = false;
        emit ReleaseRandL();
    }
}




