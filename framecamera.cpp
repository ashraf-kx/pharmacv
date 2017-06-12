#include "framecamera.h"
#include "ui_framecamera.h"

FrameCamera::FrameCamera(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameCamera)
{
    ui->setupUi(this);
//!******* Start Design ***********
    QGraphicsDropShadowEffect *sh = new QGraphicsDropShadowEffect();
    sh->setBlurRadius(8);
    sh->setOffset(2);
    sh->setColor(QColor(63, 63, 63, 180));
    this->setGraphicsEffect(sh);

    QGraphicsDropShadowEffect *shDly = new QGraphicsDropShadowEffect();
    shDly->setBlurRadius(8);
    shDly->setOffset(1);
    shDly->setColor(QColor(63, 63, 63, 180)); // "#ff8c00"
    ui->LB_DisplayMat->setGraphicsEffect(shDly);

//    // machine states.
//    machine = new QStateMachine; // expand, shrink
//    machineX = new QStateMachine;
//    S_expand_A = new QState(machine);
//    S_shrink_A = new QState(machine);
//    S_expand_B = new QState(machineX);
//    S_shrink_B = new QState(machineX);

//    S_expand_A->assignProperty(ui->PB_Play, "size", QSize(100, 40));
//    S_shrink_A->assignProperty(ui->PB_Play, "size", QSize(40, 40));
//    machine->setInitialState(S_expand_A);

//    S_expand_B->assignProperty(ui->PB_Stop, "size", QSize(100, 40));
//    S_shrink_B->assignProperty(ui->PB_Stop, "size", QSize(40, 40));
//    machineX->setInitialState(S_expand_B);

//    QSignalTransition *transition1 = S_expand_A->addTransition(ui->PB_Play,
//        SIGNAL(clicked()), S_shrink_A);
//    transition1->addAnimation(new QPropertyAnimation(ui->PB_Play, "size"));

//    QSignalTransition *transition2 = S_shrink_A->addTransition(ui->PB_Stop,
//        SIGNAL(clicked()), S_expand_A);
//    transition2->addAnimation(new QPropertyAnimation(ui->PB_Play, "size"));
////!$$$$$
//    QSignalTransition *transition3 = S_expand_B->addTransition(ui->PB_Stop,
//        SIGNAL(clicked()), S_shrink_B);
//    transition3->addAnimation(new QPropertyAnimation(ui->PB_Stop, "size"));

//    QSignalTransition *transition4 = S_shrink_B->addTransition(ui->PB_Play,
//        SIGNAL(clicked()), S_expand_A);
//    transition4->addAnimation(new QPropertyAnimation(ui->PB_Stop, "size"));
//    machine->start();
//    machineX->start();

    //!********* End Design **********

    mCamera.open(0);
    mCamera.set( CV_CAP_PROP_FRAME_WIDTH, 640);
    mCamera.set( CV_CAP_PROP_FRAME_HEIGHT,480);

    qtimer = new QTimer(this);                          // instantiate timer
    connect(qtimer, SIGNAL(timeout()), this, SLOT(getNewFrame()));     // associate timer to processFrameAndUpdateGUI
    qtimer->start(50);

    connect(ui->PB_Play,SIGNAL(clicked(bool)),qtimer,SLOT(start()));
    connect(ui->PB_Stop,SIGNAL(clicked(bool)),qtimer,SLOT(stop()));
    connect(ui->CB_MatSize,SIGNAL(currentIndexChanged(QString)),
            this,SLOT(changeResolution(QString)));
    connect(ui->CB_FPS,SIGNAL(currentIndexChanged(int)),this,SLOT(changeFPS(int)));
}

FrameCamera::~FrameCamera()
{
    delete ui;
}

void FrameCamera::changeResolution(const QString& Res)
{
    if(Res == "1280x720")
    {
        mCamera.set( CV_CAP_PROP_FRAME_WIDTH, 1280);
        mCamera.set( CV_CAP_PROP_FRAME_HEIGHT,720);
    }else{
        mCamera.set( CV_CAP_PROP_FRAME_WIDTH, 640);
        mCamera.set( CV_CAP_PROP_FRAME_HEIGHT,480);
    }
}

void FrameCamera::changeFPS(int val)
{
    switch (val) {
    case 0:
        qtimer->start(100);
        break;
    case 1:
        qtimer->start(50);
        break;
    case 2:
        qtimer->start(33);
        break;
    case 3:
        qtimer->start(25);
        break;
    case 4:
        qtimer->start(20);
        break;
    case 5:
        qtimer->start(16);
        break;
    default:
        break;
    }
}

void FrameCamera::getNewFrame()
{
    if(mCamera.isOpened())
    {
       mCamera.read(frame);

        if (!frame.empty())
        {
            if(ui->CB_MatType->currentIndex()==0)
            cvtColor(frame,frame,CV_RGB2GRAY);

            ui->LB_DisplayConfig->setText(QString::number(frame.type())+":"
                                               ":"+QString::number(frame.rows)+":"
                                               ":"+QString::number(frame.cols)+"><"
                                               " "+QString::number(mCamera.get(CV_CAP_PROP_FRAME_WIDTH))+":"
                                               ":"+QString::number(mCamera.get(CV_CAP_PROP_FRAME_HEIGHT)));
            ui->LB_DisplayMat->setPixmap(QPixmap::fromImage(convertOpenCVMatToQtQImage(frame)));
        }else
        {
            mToast = new Toast(this);
            mToast->setMessage(tr("Empty MAT frame."));
        }
    }else
    {
        mToast = new Toast(this);
        mToast->setMessage(tr("Can't Open Camera."));
    }
}

void FrameCamera::stopCam()
{
    mCamera.release();
}

Mat FrameCamera::getFrame()
{
    return frame;
}

//! *****************  EXTRA FUNCTIONS QT & OPENCV WORKS TOGATHER.*******************************
QImage FrameCamera::convertOpenCVMatToQtQImage(cv::Mat mat) {
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
