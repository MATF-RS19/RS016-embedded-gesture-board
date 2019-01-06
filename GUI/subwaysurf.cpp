#include "subwaysurf.h"
#include "ui_subwaysurf.h"

SubwaySurf::SubwaySurf(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SubwaySurf)
{
    ui->setupUi(this);
}

SubwaySurf::~SubwaySurf()
{
    delete ui;
}
