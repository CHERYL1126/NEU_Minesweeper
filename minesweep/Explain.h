#ifndef Explain_H
#define Explain_H

#include <QMainWindow>

namespace Ui {
class Explain;
}

class Explain : public QMainWindow
{
    Q_OBJECT

public:
    explicit Explain(QWidget *p = nullptr);
    ~Explain();

private:
    Ui::Explain *ui;
};

#endif // Explain_H
