#include "slideshow.h"
#include "ui_slideshow.h"
#include "mainwindow.h"

SlideShow::SlideShow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SlideShow)
{
    ui->setupUi(this);
    ui->image->setPixmap(QPixmap(":/new/prefix1/pic1"));

}

SlideShow::~SlideShow()
{
    delete ui;
}


void SlideShow::on_exitButton_clicked()
{
    // TODO
}
