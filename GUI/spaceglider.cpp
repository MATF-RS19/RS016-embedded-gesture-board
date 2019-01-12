#include "spaceglider.h"
#include "ui_spaceglider.h"
#include "mainwindow.h"
#include <QtCore>
#include <QBasicTimer>
#include <QtDebug>
#include <QPalette>
#include <QKeyEvent>
#include <QFrame>
#include <QLabel>
#include <QPixmap>

SpaceGlider::SpaceGlider(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpaceGlider)
{
    ui->setupUi(this);
    isPaused = true;

    ui->frejm->setStyleSheet("background-color: red");

    timer = new QTimer();

    setFocusPolicy(Qt::StrongFocus);

    //TODO: namestiti da se fokusira frejm nakon klika bilo kog dugmeta

    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));

    ui->pushButton_start->setFocusPolicy(Qt::StrongFocus);

    ui->pushButton_exit->setShortcut(QKeySequence(Qt::Key_Escape));
    ui->pushButton_start->setShortcut(QKeySequence(Qt::Key_W));
    ui->pushButton_pause->setShortcut(QKeySequence(Qt::Key_S));
}

SpaceGlider::~SpaceGlider()
{
    delete ui;
}

void SpaceGlider::init() {

    positionH = 0;
    positionV = 0;

    nextMissile =0;

    int frameHeight = ui->frejm->height();
    int frameWidth = ui->frejm->width();
    int gliderHeight = ui->label_glider->height();
    int gliderWidth = ui->label_glider->width();

    ui->label_glider->resize(frameWidth/5, frameHeight/5);

    ui->label_glider->move((frameWidth-gliderWidth)/2, frameHeight-gliderHeight);
}

void SpaceGlider::timerSlot() {
    //TODO napisati koliziju
    if(nextMissile == 0) {
        nextMissile = 150 + qrand() % 250;

        missiles.append(fireMissile());
    }

    for (int i = 0;i < missiles.length(); i++) {
        if(missiles[i]->y() > ui->frejm->height()) {
            missiles[i]->deleteLater();
            missiles.remove(i);
        }

        int x = missiles[i]->x();
        int y = missiles[i]->y();

        missiles[i]->move(x, y+2);

    }

    nextMissile--;
}

void SpaceGlider::on_pushButton_pause_clicked()
{
    if(isPaused == false) {
         timer->stop();
         isPaused = true;
    } else {
        timer->start(10);
        isPaused = false;
    }
}

void SpaceGlider::on_pushButton_start_clicked()
{
    if(isPaused == true) {
        init();
        timer->start(10);
        isPaused = false;
    }
}

void SpaceGlider::on_pushButton_exit_clicked()
{
    QApplication::activeWindow()->hide();
}

void SpaceGlider::keyPressEvent(QKeyEvent *event) {
    if(!isPaused) {
        switch(event->key()) {
        case Qt::Key_Left:
            turnLeft();
            break;
        case Qt::Key_Right:
            turnRight();
            break;
        case Qt::Key_Up:
            goForward();
            break;
        case Qt::Key_Down:
            goBackward();
            break;

        default:
            QMainWindow::keyPressEvent(event);
        }
    }
}

void SpaceGlider::turnLeft() {
    if(positionH > -2) {
        int x = ui->label_glider->x();
        int y = ui->label_glider->y();
        int vX = ui->frejm->width()/5;
        ui->label_glider->move(x - vX, y);
        positionH--;
    }
}

void SpaceGlider::turnRight() {
    if(positionH < 2) {
        int x = ui->label_glider->x();
        int y = ui->label_glider->y();
        int vX = ui->frejm->width()/5;
        ui->label_glider->move(x + vX, y);
        positionH++;
    }
}

void SpaceGlider::goForward() {
    if(positionV < 4) {
        int x = ui->label_glider->x();
        int y = ui->label_glider->y();
        int vY = ui->frejm->height()/8;
        ui->label_glider->move(x, y-vY);
        positionV++;
    }
}

void SpaceGlider::goBackward() {
    if(positionV > 0) {
        int x = ui->label_glider->x();
        int y = ui->label_glider->y();
        int vY = ui->frejm->height()/8;
        ui->label_glider->move(x, y+vY);
        positionV--;
    }
}

QLabel* SpaceGlider::fireMissile() {
    QLabel *missile_label = new QLabel(ui->frejm);
    //TODO: srediti nevidljive rakete
//    missile_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    int height = ui->frejm->height()/6;
    int width = height/3;
    int factor = qrand() % 5;

    int x = ui->frejm->height()/5 * factor;
    int y = -height;

    QPixmap pix(":/resource/img/tip_1.png");

    qDebug() << "Ispaljenja raketa: " << x << " " << y << " " << width << " " << height;

    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);

    missile_label->setAutoFillBackground(true);
    missile_label->setPalette(sample_palette);
    missile_label->setText("What ever text");

    missile_label->setGeometry(x, y, width, height);
//    missile_label->setPixmap(pix);

    return missile_label;
}
