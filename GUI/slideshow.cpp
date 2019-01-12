#include "slideshow.h"
#include "ui_slideshow.h"
#include "mainwindow.h"
#include "images.h"

#include <windows.h>
#include <QKeyEvent>
#include <stdio.h>
#include <iostream>

// makroi za prepoznavanje da li je kliknuto dugme next ili previous
#define NEXT 1
#define PREVIOUS 0

// makroi za dimenzije
#define X 390
#define Y 220
#define WIDTH 641
#define HEIGHT 431

#define ZOOM_IN 1.0
#define ZOOM_OUT 0.0

// globalna promenljiva klase Images
static Images images;

// parametar za rotaciju (na pocetku su sve slike horizontalno postavljene)
static int rotationHorizontal = 1;

// faktor skaliranja
static double scale = 1.0;

// brojac za zoom
static int counterIn = 0;

SlideShow::SlideShow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SlideShow)
{
    ui->setupUi(this);
    setWindowTitle("Slideshow");

    // dodaju se slike u vektor m_names klase images
  //  images.addMember(":/new/prefix1/pic1");

    images.addMember(":/new/prefix1/pic2");
    images.addMember(":/new/prefix1/pic3");
    images.addMember(":/new/prefix1/pic4");
    images.addMember(":/new/prefix1/pic5");
    images.addMember(":/new/prefix1/pic6");
    images.addMember(":/new/prefix1/pic7");
    images.addMember(":/new/prefix1/pic1");
    images.addMember(":/new/prefix1/pic9");

    QString s1 = images.names(0);

    // labela se postavlja na prvu sliku iz vektora
    ui->image->setPixmap(QPixmap(s1));

    // omoguceno skaliranje labele image
    ui->image->setScaledContents(true);

    // postavljaju se precice za tastaturi za dugmice,
    // koje se povezuju sa gesture pokretima
    ui->nextButton->setShortcut(QKeySequence(Qt::Key_Right));
    ui->previousButton->setShortcut(QKeySequence(Qt::Key_Left));
    ui->rotateLButton->setShortcut(QKeySequence(Qt::Key_Z));
    ui->rotateRButton->setShortcut(QKeySequence(Qt::Key_X));
    ui->zoomInButton->setShortcut(QKeySequence(Qt::Key_Down));
    ui->zoomOutButton->setShortcut(QKeySequence(Qt::Key_Up));
    ui->exitButton->setShortcut(QKeySequence(Qt::Key_Escape));

}

SlideShow::~SlideShow()
{
    delete ui;
}


void SlideShow::on_exitButton_clicked()
{
    QApplication::activeWindow()->hide();
}

void SlideShow::reset() {
    // kad se ucita naredna slika, brojac zooma, rotacija, faktor skaliranja
    // i koordinate slike se postavljaju na prvobitne
    counterIn = 0;
    rotationHorizontal = 1;
    scale = 1.0;
    zoom(1.0, 1.0);
    ui->image->setGeometry(X, Y, WIDTH, HEIGHT);
}


void SlideShow::on_nextButton_clicked()
{
    // pocetno stanje slike
    reset();
    images.importImages(NEXT, ui->image);
}

void SlideShow::on_previousButton_clicked()
{
    reset();
    images.importImages(PREVIOUS, ui->image);
}


void SlideShow::rotate(double a) {

    QPixmap pixmap(*ui->image->pixmap());
    QMatrix rm;

    rm.rotate(a);
    pixmap = pixmap.transformed(rm);

    int height = ui->image->geometry().height();
    int width  = ui->image->geometry().width();

    // ako je horizontalno slika, menjaju se koordinate, dimenzije
    // i rotacija se postavlja na vertikalnu
    if(rotationHorizontal == 1) {

        ui->image->setGeometry(X, Y, height, width);
        ui->image->setPixmap(pixmap);
        rotationHorizontal = 0;
    }

    // isto za vertikalnu
    else {
        ui->image->setGeometry(X, Y, height, width);
        ui->image->setPixmap(pixmap);
        rotationHorizontal = 1;
    }
}

void SlideShow::zoom(double s, double f) {
    scale *= s;

    QSize size = ui->image->pixmap()->size() * scale;

    int x = ui->image->geometry().x();
    int y = ui->image->geometry().y();
    ui->image->resize(size);

    if(f == ZOOM_IN) {
        ui->image->move(x - x*0.1/2, y -y*0.1/2);
    }
    else {
        ui->image->move(x + x*0.1/2, y + y*0.1/2);
    }

//    qDebug() << x - x*s/2 << " " << y - y*s/2;

}

void SlideShow::on_rotateLButton_clicked()
{
    rotate(-90);
}

void SlideShow::on_rotateRButton_clicked()
{
    rotate(90);
}

void SlideShow::on_zoomInButton_clicked()
{
    if(counterIn < 7) {
        zoom(1.1, ZOOM_IN);
        counterIn++;
    }
}

void SlideShow::on_zoomOutButton_clicked()
{
    if(counterIn > -7) {
        zoom(1/1.1, ZOOM_OUT);
        counterIn--;
    }

}
