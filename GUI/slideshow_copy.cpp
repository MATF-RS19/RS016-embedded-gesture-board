#include "slideshow.h"
#include "ui_slideshow.h"
#include "mainwindow.h"

#include <windows.h>
#include <QKeyEvent>
#include <QFrame>
#include <QPainter>
#include <stdio.h>
#include <iostream>

#include "images.h"

#define NUM_OF_IMAGES 6
double m_scaleFactor = 1.0;
static Images images(NUM_OF_IMAGES);
static QString currentImageName;

static int rotation = 1;

SlideShow::SlideShow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SlideShow)
{
    ui->setupUi(this);

    images.addMember(":/new/prefix1/pic1");
    images.addMember(":/new/prefix1/pic2");
    images.addMember(":/new/prefix1/pic3");
    images.addMember(":/new/prefix1/pic4");
    images.addMember(":/new/prefix1/pic5");
    images.addMember(":/new/prefix1/pic6");

    QString s1 = images.names(0);

    ui->image->setPixmap(QPixmap(s1));
    currentImageName = s1;
   // std::cout << s1.toStdString() << std::endl;


    ui->nextButton->setShortcut(QKeySequence(Qt::Key_Right));
    ui->previousButton->setShortcut(QKeySequence(Qt::Key_Left));
    ui->rotateLButton->setShortcut(QKeySequence(Qt::Key_Up));
    ui->rotateRButton->setShortcut(QKeySequence(Qt::Key_Down));
}

SlideShow::~SlideShow()
{
    delete ui;
}


void SlideShow::on_exitButton_clicked()
{
    rotation = 0;
    QApplication::activeWindow()->hide();
}

void SlideShow::on_nextButton_clicked()
{

    QString first = images.names(0);

    if(!(currentImageName.compare(first))) {
        ui->image->setPixmap(QPixmap(images.names(1)));
        currentImageName = images.names(1);
    }

    else if(!(currentImageName.compare(images.names(1)))) {
        ui->image->setPixmap(QPixmap(images.names(2)));
        currentImageName = images.names(2);
    }

    else if(!(currentImageName.compare(images.names(2)))) {
        ui->image->setPixmap(QPixmap(images.names(3)));
        currentImageName = images.names(3);
    }

    else if(!(currentImageName.compare(images.names(3)))) {
        ui->image->setPixmap(QPixmap(images.names(4)));
        currentImageName = images.names(4);
    }

    else if(!(currentImageName.compare(images.names(4)))) {
        ui->image->setPixmap(QPixmap(images.names(5)));
        currentImageName = images.names(5);
    }

    else if(!(currentImageName.compare(images.names(5)))) {
        ui->image->setPixmap(QPixmap(images.names(0)));
        currentImageName = images.names(0);
    }
}

void SlideShow::on_previousButton_clicked()
{

    if(!(currentImageName.compare(images.names(0)))) {
        ui->image->setPixmap(QPixmap(images.names(5)));
        currentImageName = images.names(5);
    }

    else if(!(currentImageName.compare(images.names(1)))) {
        ui->image->setPixmap(QPixmap(images.names(0)));
        currentImageName = images.names(0);
    }

    else if(!(currentImageName.compare(images.names(2)))) {
        ui->image->setPixmap(QPixmap(images.names(1)));
        currentImageName = images.names(1);
    }

    else if(!(currentImageName.compare(images.names(3)))) {
        ui->image->setPixmap(QPixmap(images.names(2)));
        currentImageName = images.names(2);
    }

    else if(!(currentImageName.compare(images.names(4)))) {
        ui->image->setPixmap(QPixmap(images.names(3)));
        currentImageName = images.names(3);
    }

    else if(!(currentImageName.compare(images.names(5)))) {
        ui->image->setPixmap(QPixmap(images.names(4)));
        currentImageName = images.names(4);
    }
}


void SlideShow::on_rotateLButton_clicked()
{
    QPixmap pixmap(*ui->image->pixmap());
    QMatrix rm;
    rm.rotate(-90);
    pixmap = pixmap.transformed(rm);
    if(rotation == 1) {
        ui->image->setGeometry(250, 100, 333, 500);
        ui->image->setPixmap(pixmap);
        rotation = 0;
    }

    else {
        ui->image->setGeometry(200, 100, 500, 333);
        ui->image->setPixmap(pixmap);
        rotation = 1;
    }

}

void SlideShow::on_rotateRButton_clicked()
{
    QPixmap pixmap(*ui->image->pixmap());
    QMatrix rm;
    rm.rotate(90);
    pixmap = pixmap.transformed(rm);
    if(rotation == 1) {
        ui->image->setGeometry(250, 100, 500, 333);
        ui->image->setPixmap(pixmap);
        rotation = 0;
    }

    else {
        ui->image->setGeometry(200, 100, 500, 333);
        ui->image->setPixmap(pixmap);
        rotation = 1;
    }

}


void SlideShow::on_zoomInButton_clicked()
{

    m_scaleFactor *= 1.1;

    QSize size = ui->image->pixmap()->size() * m_scaleFactor;
    ui->image->resize(size);
}

void SlideShow::on_zoomOutButton_clicked()
{

    m_scaleFactor *= 1/1.1;

    QSize size = ui->image->pixmap()->size() * m_scaleFactor;
    ui->image->resize(size);
}
