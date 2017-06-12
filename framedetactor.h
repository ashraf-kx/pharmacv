#ifndef FRAMEDETACTOR_H
#define FRAMEDETACTOR_H

#include <QtCore>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QFile>
#include <QTextStream>

// QAnimate Framework
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QStateMachine>
#include <QState>
#include <QSignalTransition>

// OpenCV Framework
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#ifdef HAVE_OPENCV_NONFREE
# include "opencv2/nonfree/nonfree.hpp"
#endif

#include "toast.h"


using namespace cv;

namespace Ui {
class FrameDetactor;
}

class FrameDetactor : public QFrame
{
    Q_OBJECT

public:
    explicit FrameDetactor(QWidget *parent = 0);
    ~FrameDetactor();

public slots:
    vector<KeyPoint> _SurfDetector(const Mat &frame);
    QImage convertOpenCVMatToQtQImage(cv::Mat mat);
    Mat _FreakDescriptor();
private:
    Ui::FrameDetactor   *ui;

    SurfFeatureDetector      Detector;
    FREAK                    Descriptor_Extractor;
    // GenericDescriptorMatcher Descriptor_Matcher;

    Mat frame;
    vector<KeyPoint> mKeypoint;

    Toast *mToast;

};

#endif // FRAMEDETACTOR_H
