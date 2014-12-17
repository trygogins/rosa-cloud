#ifndef SPINBOX_H
#define SPINBOX_H

#include <QWidget>

namespace Ui {
class Spinbox;
}

class Spinbox : public QWidget
{
    Q_OBJECT

public:
    explicit Spinbox(QWidget *parent = 0);
    ~Spinbox();

private:
    Ui::Spinbox *ui;
};

#endif // SPINBOX_H
