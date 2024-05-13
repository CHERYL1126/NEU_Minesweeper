#ifndef AsForUs_H
#define AsForUs_H

#include <QMainWindow>

namespace Ui {
class AsForUs;
}

class AsForUs : public QMainWindow
{
    Q_OBJECT

public:
    explicit AsForUs(QWidget *p = nullptr);
    ~AsForUs();

private:
    Ui::AsForUs *ui;
};

#endif // AsForUs_H
