#include "framedetactor.h"
#include "ui_framedetactor.h"

FrameDetactor::FrameDetactor(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameDetactor)
{
    ui->setupUi(this);
#ifdef HAVE_OPENCV_NONFREE
    cv::initModule_nonfree();
#else
    cout << "Warning: OpenCV is built without nonfree support SIFT, SURF and some other algorithms are not available." << endl;
#endif
    QGraphicsDropShadowEffect *sh = new QGraphicsDropShadowEffect();
    sh->setBlurRadius(8);
    sh->setOffset(2);
    sh->setColor(QColor(63, 63, 63, 180));
    this->setGraphicsEffect(sh);
    //! ******** Detectors ***********
    mKeypoint.clear();
    //! ******** Exctractor **********
    // (rotation invariance, scale invariance, pattern radius corresponding to SMALLEST_KP_SIZE,
    // number of octaves, optional vector containing the selected pairs)
    // FREAK extractor(true, true, 22, 4, std::vector<int>());

    //Extractor(true, true, 22, 4, std::vector<int>());
}

vector<KeyPoint> FrameDetactor::_SurfDetector(const Mat& frame)
{
    Mat tmpFrame;
    frame.copyTo(this->frame);
    this->frame.copyTo(tmpFrame);

    vector<KeyPoint> tmpkeyPoint;
    tmpkeyPoint.clear();

    Detector.hessianThreshold = 380.0;
    Detector.detect(tmpFrame,tmpkeyPoint);

    // draw keypoint on the Image.
    drawKeypoints(tmpFrame,tmpkeyPoint,tmpFrame);
    ui->LB_Display->setPixmap(QPixmap::fromImage(convertOpenCVMatToQtQImage(tmpFrame)));
    ui->Lb_DisplayMsg->setText(QString::number(tmpkeyPoint.size()));
    mKeypoint = tmpkeyPoint;
    return tmpkeyPoint;
}

Mat FrameDetactor::_FreakDescriptor()
{
    Mat tmpDescriptor,tmpFrame;
    this->frame.copyTo(tmpFrame);

    Descriptor_Extractor.compute(tmpFrame,mKeypoint,tmpDescriptor);
    ui->Lb_DisplayMsg->setText("Descriptor: H"+QString::number(tmpDescriptor.rows)+":"
                               ":W"+QString::number(tmpDescriptor.cols)+":"
                               "type :"+QString::number(tmpDescriptor.type()));

    ui->LB_Display->setPixmap(QPixmap::fromImage(convertOpenCVMatToQtQImage(tmpDescriptor)));
    return tmpDescriptor;
}

FrameDetactor::~FrameDetactor()
{
    delete ui;
}
//! *****************  EXTRA FUNCTIONS QT & OPENCV WORKS TOGATHER.*******************************
QImage FrameDetactor::convertOpenCVMatToQtQImage(cv::Mat mat) {
    if(mat.channels() == 1) {                                   // if 1 channel (grayscale or black and white) image
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);     // return QImage
    } else if(mat.channels() == 3) {                            // if 3 channel color image
        cv::cvtColor(mat, mat, CV_BGR2RGB);                     // flip colors
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);       // return QImage
    } else {
        mToast = new Toast(this);
        mToast->setMessage(tr("Mat 'frame' wasn't (1 or 3) Channel."));

    }
    return QImage();        // return a blank QImage if the above did not work
}
