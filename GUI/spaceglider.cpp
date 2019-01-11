#include "spaceglider.h"
#include "ui_spaceglider.h"

#include <QtCore>
#include <QBasicTimer>
#include <QtDebug>
#include <QPalette>

SpaceGlider::SpaceGlider(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpaceGlider)
{
    ui->setupUi(this);
    init();

    timer = new QTimer();



    connect(timer, SIGNAL(timeout()), this, SLOT(mySlot()));
}

SpaceGlider::~SpaceGlider()
{
    delete ui;
}
\
void SpaceGlider::init() {
    isPaused = true;

    int frameHeight = ui->frejm->height();
    int frameWidth = ui->frejm->width();
    int gliderHeight = ui->label_glider->height();
    int gliderWidth = ui->label_glider->width();

    qDebug() << frameWidth << " " << frameHeight << " " << " " << gliderWidth << gliderHeight;

    ui->label_glider->move((frameWidth-gliderWidth)/2, frameHeight-gliderHeight);
}

void SpaceGlider::mySlot() {
  //TODO napraviti sve
    int x = ui->label_glider->x();
    int y = ui->label_glider->y();
    ui->label_glider->move(x, y-1);
    qDebug() << x;
    qDebug() << y;
}

void SpaceGlider::on_pushButton_pause_clicked()
{
    if(isPaused == false) {
         timer->stop();
         isPaused = true;
    }
}

void SpaceGlider::on_pushButton_start_clicked()
{
    if(isPaused == true) {
        timer->start(100);
        isPaused = false;
    }
}

void SpaceGlider::on_pushButton_restart_clicked()
{
    init();
    isPaused = false;
    timer->start(100);
}

void SpaceGlider::on_pushButton_exit_clicked()
{
    QApplication::activeWindow()->hide();
}
