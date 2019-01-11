#include "slideshow.h"
#include "ui_slideshow.h"
#include "mainwindow.h"
#include "images.h"

#include <windows.h>
#include <QKeyEvent>
#include <stdio.h>
#include <iostream>

#define NUM_OF_IMAGES 10

// makroi za prepoznavanje da li je kliknuto dugme next ili previous
#define NEXT 1
#define PREVIOUS 0

// makroi za dimenzije
#define X 480
#define Y 140
#define WIDTH 551
#define HEIGHT 391

#define IN 1.0
#define OUT 0.0

// globalna promenljiva klase Images
static Images images(NUM_OF_IMAGES);

// promenljiva u kojoj se cuva ime trenutne fotografije
static QString currentImageName;

// parametar za rotaciju (na pocetku su sve slike horizontalno postavljene)
static int rotationHorizontal = 1;

// faktor skaliranja
static double scale = 1.0;

static int counterIn = 0;
static int counterOut = 0;

SlideShow::SlideShow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SlideShow)
{
    ui->setupUi(this);
    setWindowTitle("Slideshow");

    // dodaju se fotografije u vector images
    images.addMember(":/new/prefix1/pic1");
    images.addMember(":/new/prefix1/pic2");
    images.addMember(":/new/prefix1/pic3");
    images.addMember(":/new/prefix1/pic4");
    images.addMember(":/new/prefix1/pic5");
    images.addMember(":/new/prefix1/pic6");

    QString s1 = images.names(0);

    // labela se postavlja na prvu fotografiju iz vektora
    ui->image->setPixmap(QPixmap(s1));

    // azurira se trenutna fotografija
    currentImageName = s1;

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
    // kad se ucita naredna slika, rotacija, faktor skaliranja
    // i koordinate slike se postavljaju na prvobitne
    rotationHorizontal = 1;
    scale = 1.0;
    zoom(1.0, 1.0);
    ui->image->setGeometry(X, Y, WIDTH, HEIGHT);
}


void SlideShow::importImages(int type) {

    unsigned n = images.size();
    QString first = images.names(0);
    QString last = images.names(n-1);

    // proverava se da li je ime trenutno prikazane slike
    // jednako imenu slike iz vektora i kad se poklope
    // slika se postavlja na narednu tj. prethodnu
    // i azurira se ime trenutno prikazane slike

    // ako je type 1, onda se ucitava naredna
    if(type == NEXT) {

        // ako je trenutna poslednja, naredna je prva
        if(!(currentImageName.compare(last))) {
                ui->image->setPixmap(QPixmap(first));
                currentImageName = first;
         }

        else {
            for(unsigned i = 0; i < n-1; i++) {
                if(!(currentImageName.compare(images.names(i)))) {
                        unsigned j = i;
                        ui->image->setPixmap(QPixmap(images.names(j+1)));
                        currentImageName = images.names(j+1);
                        break;
                 }
            }
        }

    }

    // ako je type 0 ucitava se prethodna slika
    else if(type == PREVIOUS) {

        // ako je trenutna prva, prethodna je poslednja
        if(!(currentImageName.compare(first))) {
            ui->image->setPixmap(QPixmap(last));
            currentImageName = last;
        }

        else {
            for(unsigned i = 1; i < n; i++) {
                if(!(currentImageName.compare(images.names(i)))) {
                        ui->image->setPixmap(QPixmap(images.names(i-1)));
                        currentImageName = images.names(i-1);
                    }
            }
        }
    }

    else return;
}

void SlideShow::on_nextButton_clicked()
{
    // pocetno stanje slike
    reset();
    importImages(NEXT);
}

void SlideShow::on_previousButton_clicked()
{
    reset();
    importImages(PREVIOUS);
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

    if(f == IN) {
        ui->image->move(x - x*0.1/2, y -y*0.1/2);
    }
    else {
        ui->image->move(x + x*0.1/2, y + y*0.1/2);
    }

    qDebug() << x - x*s/2 << " " << y - y*s/2;
//    ui->image->setGeometry(200-50*s, 100-50*s, 551/s, 391/s);
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
        zoom(1.1, IN);
        counterIn++;
    }
}

void SlideShow::on_zoomOutButton_clicked()
{
    if(counterIn > -7) {
        zoom(1/1.1, OUT);
        counterIn--;
    }

}
