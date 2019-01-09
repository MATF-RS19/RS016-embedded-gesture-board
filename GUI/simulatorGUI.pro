#-------------------------------------------------
#
# Project created by QtCreator 2019-01-05T12:07:04
#
#-------------------------------------------------

QT       += core gui serialport widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simulatorGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    slideshow.cpp \
    subwaysurf.cpp \
    tetrisigra.cpp \
    tetrisdeo.cpp \
    tetrisprozor.cpp \
    images.cpp

HEADERS += \
        mainwindow.h \
    slideshow.h \
    subwaysurf.h \
    tetrisigra.h \
    tetrisdeo.h \
    tetrisprozor.h \
    images.h


FORMS += \
        mainwindow.ui \
    slideshow.ui \
    subwaysurf.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    img/pic1.qrc \
    img/pic2.qrc
