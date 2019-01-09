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
QString currentImageName;

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
    QString s2 = images.names(1);
    QString s3 = images.names(2);
    QString s4 = images.names(3);
    QString s5 = images.names(4);

    ui->image->setPixmap(QPixmap(s1));
    currentImageName = s1;
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

void SlideShow::keyPressEvent(QKeyEvent *event)
{

     //QFrame::keyPressEvent(event);

    switch (event->key()) {
    case Qt::Key_Left:
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







