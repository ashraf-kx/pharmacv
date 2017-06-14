#-------------------------------------------------
#
# Project created by QtCreator 2017-04-30T20:23:28
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PharmaCV
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    framecamera.cpp \
    toast.cpp \
    framedetactor.cpp

HEADERS  += mainwindow.h \
    framecamera.h \
    toast.h \
    framedetactor.h

FORMS    += mainwindow.ui \
    framecamera.ui \
    toast.ui \
    framedetactor.ui


unix {

INCLUDEPATH += /usr/local/include/opencv2

LIBS += -L /usr/local/lib \
        -lopencv_calib3d \
        -lopencv_contrib \
        -lopencv_core \
        -lopencv_features2d \
        -lopencv_flann \
        -lopencv_gpu \
        -lopencv_highgui \
        -lopencv_imgproc \
        -lopencv_legacy \
        -lopencv_ml \
        -lopencv_nonfree \
        -lopencv_objdetect \
        -lopencv_ocl \
        -lopencv_photo \
        -lopencv_stitching \
        -lopencv_superres \
        -lopencv_video \
        -lopencv_videostab
}

win32 {

INCLUDEPATH+= D:\\openCV\\build\\include

    debug {
    LIBS += -LD:\\openCV\\x64\\lib\\Debug \
                -lopencv_calib3d2413d \
                -lopencv_contrib2413d \
                -lopencv_core2413d \
                -lopencv_features2d2413d \
                -lopencv_flann2413d \
                -lopencv_gpu2413d \
                -lopencv_highgui2413d \
                -lopencv_imgproc2413d \
                -lopencv_legacy2413d \
                -lopencv_ml2413d \
                -lopencv_nonfree2413d \
                -lopencv_objdetect2413d \
                -lopencv_ocl2413d \
                -lopencv_photo2413d \
                -lopencv_stitching2413d \
                -lopencv_superres2413d \
                -lopencv_video2413d \
                -lopencv_videostab2413d
    }
    release {
    LIBS += -LD:\\openCV\\x64\\lib\\Release \
                -lopencv_calib3d2413 \
                -lopencv_contrib2413 \
                -lopencv_core2413 \
                -lopencv_features2d2413 \
                -lopencv_flann2413 \
                -lopencv_gpu2413 \
                -lopencv_highgui2413 \
                -lopencv_imgproc2413 \
                -lopencv_legacy2413 \
                -lopencv_ml2413 \
                -lopencv_nonfree2413 \
                -lopencv_objdetect2413 \
                -lopencv_ocl2413 \
                -lopencv_photo2413 \
                -lopencv_stitching2413 \
                -lopencv_superres2413 \
                -lopencv_video2413 \
                -lopencv_videostab2413
    }
}
RESOURCES += \
    icons.qrc \
    styles.qrc
