#ifndef FRAMEDETACTOR_H
#define FRAMEDETACTOR_H

#include <QFrame>

namespace Ui {
class FrameDetactor;
}

class FrameDetactor : public QFrame
{
    Q_OBJECT

public:
    explicit FrameDetactor(QWidget *parent = 0);
    ~FrameDetactor();

private:
    Ui::FrameDetactor *ui;
};

#endif // FRAMEDETACTOR_H
