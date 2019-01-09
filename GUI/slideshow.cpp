#include "slideshow.h"
#include "ui_slideshow.h"
#include "mainwindow.h"

#include <windows.h>
#include <QKeyEvent>
#include <QFrame>
#include <stdio.h>
#include <iostream>

#include "images.h"

Images images(5);

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

   // ui->image->setPixmap(QPixmap(":/new/prefix1/pic1"));

    QString s1 = images.names(0);
    QString s2 = images.names(1);
    QString s3 = images.names(2);
    QString s4 = images.names(3);
    QString s5 = images.names(4);

    ui->image->setPixmap(QPixmap(s1));
   // std::cout << s1.toStdString() << std::endl;

}

SlideShow::~SlideShow()
{
    delete ui;
}


void SlideShow::on_exitButton_clicked()
{
    QApplication::activeWindow()->hide();
}

void SlideShow::on_nextButton_clicked()
{
    keybd_event(VK_LEFT,0x25,0,0);
    ui->image->setPixmap(QPixmap(images.names(1)));
}

void SlideShow::on_previousButton_clicked()
{
    keybd_event(VK_RIGHT,0x27,0,0);

    ui->image->setPixmap(QPixmap(images.names(0)));
}

void SlideShow::keyPressEvent(QKeyEvent *event)
{

     //QFrame::keyPressEvent(event);

    switch (event->key()) {
    case Qt::Key_Left:
        QApplication::exit();
        ui->previousButton->click();
        break;
    case Qt::Key_Right:
        ui->nextButton->click();
        break;
    case Qt::Key_Down:
        ui->rotateLButton->click();
        break;
    case Qt::Key_Up:
        ui->rotateRButton->click();
        break;
    case Qt::Key_Space:

        break;
    case Qt::Key_D:

        break;
   // default:


    }
}







