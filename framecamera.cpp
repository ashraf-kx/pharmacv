#include "framecamera.h"
#include "ui_framecamera.h"

FrameCamera::FrameCamera(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameCamera)
{
    ui->setupUi(this);
}

FrameCamera::~FrameCamera()
{
    delete ui;
}
