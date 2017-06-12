#include "framedetactor.h"
#include "ui_framedetactor.h"

FrameDetactor::FrameDetactor(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameDetactor)
{
    ui->setupUi(this);
}

FrameDetactor::~FrameDetactor()
{
    delete ui;
}
