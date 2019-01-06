#include "slideshow.h"
#include "ui_slideshow.h"

SlideShow::SlideShow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SlideShow)
{
    ui->setupUi(this);
}

SlideShow::~SlideShow()
{
    delete ui;
}
