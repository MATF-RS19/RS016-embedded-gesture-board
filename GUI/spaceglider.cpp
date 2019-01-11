#include "spaceglider.h"
#include "ui_spaceglider.h"

#include <QtCore>
#include <QBasicTimer>
#include <QtDebug>
#include <QPalette>
#include <QKeyEvent>
#include <QFrame>

SpaceGlider::SpaceGlider(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpaceGlider)
{
    ui->setupUi(this);
//    init();

    timer = new QTimer();

    connect(timer, SIGNAL(timeout()), this, SLOT(mySlot()));

    ui->pushButton_exit->setShortcut(QKeySequence(Qt::Key_Escape));
    ui->pushButton_start->setShortcut(QKeySequence(Qt::Key_W));
    ui->pushButton_pause->setShortcut(QKeySequence(Qt::Key_S));
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
}

void SpaceGlider::on_pushButton_pause_clicked()
{
    if(isPaused == false) {
         timer->stop();
         isPaused = true;
    } else {
        timer->start();
        isPaused = false;
    }
}

void SpaceGlider::on_pushButton_start_clicked()
{
    if(isPaused == true) {
        init();
        timer->start(100);
        isPaused = false;
    }
}

void SpaceGlider::on_pushButton_exit_clicked()
{
    QApplication::activeWindow()->hide();
}

void SpaceGlider::keyPressEvent(QKeyEvent *event) {
    if (!isPaused) {
        QMainWindow::keyPressEvent(event);
        return;
    }

    switch(event->key()) {
    case Qt::Key_Left:
        qDebug() << "LIJEVA SKIJA SUADE!";
        break;
    case Qt::Key_Right:
        qDebug() << "DESNA SKIJA SUADE";
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}
