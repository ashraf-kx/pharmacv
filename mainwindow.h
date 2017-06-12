#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//! INCLUDE OPENCV LIBS
#include "opencv2/opencv.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\features2d\features2d.hpp"
#include "opencv2\contrib\contrib.hpp"
#include "opencv2\nonfree\nonfree.hpp"
#include <vector>

#include <QFile>
#include "toast.h"
#include "framecamera.h"
#include "framedetactor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    QString QKStyle(int n);
    void Pick();
private:
    Ui::MainWindow *ui;
    FrameCamera   *mFrameCam;
    FrameDetactor *mFrameDetector;
};

#endif // MAINWINDOW_H
