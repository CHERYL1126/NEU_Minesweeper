#ifndef Position_H
#define Position_H

#include <QMainWindow>

namespace Ui {
class Position;
}

class Position : public QMainWindow
{
    Q_OBJECT

public:
    explicit Position(QWidget *p = nullptr);
    ~Position();

private:
    Ui::Position *ui;
};

#endif // Position_H
