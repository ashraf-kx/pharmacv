#ifndef FRAMECAMERA_H
#define FRAMECAMERA_H

#include <QFrame>

namespace Ui {
class FrameCamera;
}

class FrameCamera : public QFrame
{
    Q_OBJECT

public:
    explicit FrameCamera(QWidget *parent = 0);
    ~FrameCamera();

private:
    Ui::FrameCamera *ui;
};

#endif // FRAMECAMERA_H
