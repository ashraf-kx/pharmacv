#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showNormal();
    this->setWindowTitle(tr("PharmaCV V 0.0.1"));
    this->setStyleSheet(QKStyle(1));

    mFrameCam      = new FrameCamera();
    mFrameDetector = new FrameDetactor();

    ui->centralWidget->layout()->addWidget(mFrameCam);
    ui->centralWidget->layout()->addWidget(mFrameDetector);

    connect(ui->PB_pick,SIGNAL(pressed()),this,SLOT(Pick()));
}

void MainWindow::Pick()
{
    mFrameDetector->_SurfDetector(mFrameCam->getFrame());
    mFrameDetector->_FreakDescriptor();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//! ****************  STYLING FUNCTIONS QT ******************************************************
QString MainWindow::QKStyle(int n)
{
    switch (n) {
    case 1:
    {
        QFile MDStyle("://styles/MaterialDesign.css");
        QString MDstyle;
        if (MDStyle.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&MDStyle);
            MDstyle = in.readAll().simplified();

        }else {
            qWarning("MDStyle not in readonly OR text mode");
            return "";
        }

       return MDstyle;
    }
        break;
    case 2:
        return "0";
        break;
    case 3:
        return "1";
        break;
    default:
        break;
    }
    return "";
}
