#ifndef FRAMECAMERA_H
#define FRAMECAMERA_H

#include <QFrame>
#include <QGraphicsDropShadowEffect>
// QAnimate Framework
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QStateMachine>
#include <QState>
#include <QSignalTransition>

#include <QGraphicsDropShadowEffect>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <QtCore>

#include "toast.h"
#include <QFile>
#include <QTextStream>



namespace Ui {
class FrameCamera;
}

using namespace cv;
using namespace std;

class FrameCamera : public QFrame
{
    Q_OBJECT

public:
    explicit FrameCamera(QWidget *parent = 0);
    ~FrameCamera();
public slots:
    void getNewFrame();
    void stopCam();

    QImage convertOpenCVMatToQtQImage(cv::Mat mat);
    void changeResolution(const QString &Res);
    void changeFPS(int val);
    Mat getFrame();

private:
    Ui::FrameCamera *ui;
    Toast *mToast;
    Mat frame;
    cv::VideoCapture mCamera;
    QTimer *qtimer;
    QStateMachine *machineX;
    QState *stateX1;
    QState *stateX2;
    QStateMachine *machine;
    QState *S_expand_A;
    QState *S_shrink_A;
    QState *S_expand_B;
    QState *S_shrink_B;
};

#endif // FRAMECAMERA_H
