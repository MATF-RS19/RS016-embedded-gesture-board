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
    ui(new Ui::SpaceGlider) {
    ui->setupUi(this);
    this->setWindowTitle("Space Glider");
    isPaused = false;
    isStarted = false;

    timer = new QTimer();

    setFocusPolicy(Qt::StrongFocus);

    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));

    ui->pushButton_start->setFocusPolicy(Qt::NoFocus);
   ui->pushButton_pause->setFocusPolicy(Qt::NoFocus);
   ui->pushButton_exit->setFocusPolicy(Qt::NoFocus);
    //Povezivanje dugmica sa tasterima na tastaturi
    ui->pushButton_exit->setShortcut(QKeySequence(Qt::Key_D));
    ui->pushButton_start->setShortcut(QKeySequence(Qt::Key_W));
    ui->pushButton_pause->setShortcut(QKeySequence(Qt::Key_S));
}

SpaceGlider::~SpaceGlider() {
    delete ui;
}

//Funkcija kojom se inicijalizuje aplikacija
void SpaceGlider::init() {

    positionH = 0;
    positionV = 0;

    nextMissile =0;

    int frameHeight = ui->frejm->height();
    int frameWidth = ui->frejm->width();
    int gliderHeight = ui->label_glider->height();
    int gliderWidth = ui->label_glider->width();

    ui->label_glider->resize(frameWidth/8, frameHeight/8);
    ui->label_glider->move((frameWidth-gliderWidth)/2, frameHeight-gliderHeight);
}

//Timer funkcija
void SpaceGlider::timerSlot() {
    //na svakih sekund do tri sekunde se iskaljuje jedna nova raketa
    if(nextMissile == 0) {
        nextMissile = 100 + qrand() % 200;

        fireMissile();
    }

    bool kolizijaPrvaTraka = false, kolizijaDrugaTraka = false, kolizijaTrecaTraka = false,
            kolizijaCetvrtaTraka = false, kolizijaPetaTraka = false;

    //provera da li je raketa izletela van ekrana i da li je doslo do kolizije,
    //za svaku od 5 mogucih traka se vrsi provera
    if(lineTaken[0]) {
        if(ui->prva_traka->y() > ui->frejm->height()) {
            ui->prva_traka->move(ui->prva_traka->x(), -ui->prva_traka->height());
            lineTaken[0] = false;
        }

        ui->prva_traka->move(ui->prva_traka->x(), ui->prva_traka->y()+1);

        if(positionH == -2) {
            int gliderY = ui->label_glider->y();
            int gliderW = ui->label_glider->width();
            int raketaY = ui->prva_traka->y();
            int raketaH = ui->prva_traka->width();
            kolizijaPrvaTraka = (gliderY < raketaH + raketaY && gliderY + gliderW > raketaH + raketaY)
                    ||  (gliderY < raketaY && gliderY + gliderW > raketaY);
        }
    }
    if(lineTaken[1]) {
        if(ui->druga_traka->y() > ui->frejm->height()) {
            ui->druga_traka->move(ui->druga_traka->x(), -ui->druga_traka->height());
            lineTaken[1] = false;
        }

        ui->druga_traka->move(ui->druga_traka->x(), ui->druga_traka->y()+1);

        if(positionH == -1) {
            int gliderY = ui->label_glider->y();
            int gliderW = ui->label_glider->height();
            int raketaY = ui->druga_traka->y();
            int raketaH = ui->druga_traka->height();
            kolizijaDrugaTraka = (gliderY < raketaH + raketaY && gliderY + gliderW > raketaH + raketaY)
                    ||  (gliderY < raketaY && gliderY + gliderW > raketaY);
        }
    }
    if(lineTaken[2]) {
        if(ui->treca_traka->y() > ui->frejm->height()) {
            ui->treca_traka->move(ui->treca_traka->x(), -ui->treca_traka->height());
            lineTaken[2] = false;
        }

        ui->treca_traka->move(ui->treca_traka->x(), ui->treca_traka->y()+1);

        if(positionH == 0) {
            int gliderY = ui->label_glider->y();
            int gliderH = ui->label_glider->height();
            int raketaY = ui->treca_traka->y();
            int raketaH = ui->treca_traka->height();
            kolizijaTrecaTraka = (gliderY < raketaH + raketaY && gliderY + gliderH > raketaH + raketaY)
                    ||  (gliderY < raketaY && gliderY + gliderH > raketaY);
        }
    }
    if(lineTaken[3]) {
        if(ui->cetvrta_traka->y() > ui->frejm->height()) {
            ui->cetvrta_traka->move(ui->cetvrta_traka->x(), -ui->cetvrta_traka->height());
            lineTaken[3] = false;
        }

        ui->cetvrta_traka->move(ui->cetvrta_traka->x(), ui->cetvrta_traka->y()+1);

        if(positionH == 1) {
            int gliderY = ui->label_glider->y();
            int gliderH = ui->label_glider->height();
            int raketaY = ui->cetvrta_traka->y();
            int raketaH = ui->cetvrta_traka->height();
            kolizijaCetvrtaTraka = (gliderY < raketaH + raketaY && gliderY + gliderH > raketaH + raketaY)
                    ||  (gliderY < raketaY && gliderY + gliderH > raketaY);
        }
    }
    if(lineTaken[4]) {
        if(ui->peta_traka->y() > ui->frejm->height()) {
            ui->peta_traka->move(ui->peta_traka->x(), -ui->peta_traka->height());
            lineTaken[4] = false;
        }

        ui->peta_traka->move(ui->peta_traka->x(), ui->peta_traka->y()+1);

        if(positionH == 2) {
            int gliderY = ui->label_glider->y();
            int gliderH = ui->label_glider->height();
            int raketaY = ui->peta_traka->y();
            int raketaH = ui->peta_traka->width();
            kolizijaPetaTraka = (gliderY < raketaH + raketaY && gliderY + gliderH > raketaH + raketaY)
                    ||  (gliderY < raketaY && gliderY + gliderH > raketaY);
        }
    }

    if(kolizijaPrvaTraka || kolizijaDrugaTraka ||
            kolizijaTrecaTraka || kolizijaCetvrtaTraka || kolizijaPetaTraka) {
        gameOver();
    }


    nextMissile--;
}

//Funkcija koja se izvrsava ukoliko je nas brod pogodjen
void SpaceGlider::gameOver() {
    QPixmap pix(":/resource/img/boomBack.jpg");
    ui->Boom->setPixmap(pix);
    ui->Boom->setGeometry(0, 0, ui->frejm->width(), ui->frejm->height());
    ui->Boom->setScaledContents(true);
    timer->stop();
}

//funkcija koja se izvrsava nakon klika na dugme stop/resume
void SpaceGlider::on_pushButton_pause_clicked() {
    if(isPaused == false && isStarted) {
         timer->stop();
         isPaused = true;
    } else if(!isPaused == false && isStarted){
        timer->start(10);
        isPaused = false;
    }
}

//funkcija koja se izvrsava nakon klika na dugme start
void SpaceGlider::on_pushButton_start_clicked() {
    if(isStarted == false) {
        isStarted = true;
        init();
        timer->start(10);
    }
}

//funkcija koja se izvrsava nakon klika na dugme exit
void SpaceGlider::on_pushButton_exit_clicked() {
    QApplication::activeWindow()->close();
}

//funkcija koja ceka i prima dogadjaje pritiska na tastaturu i reaguje na njih
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

//komande upravljanja brodom

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

//Funkcija koja se poziva kada se ispaljuje nova raketa
//gde se jednoj od 5 mogucih traka, koje su predstavljene kao labele,
//dodeli raketa
void SpaceGlider::fireMissile() {
    int i = qrand() % 5;

    while(lineTaken[i])
        i = qrand() % 5;

    lineTaken[i] = true;

    int frameWidth = ui->frejm->width();
    int x = frameWidth/5;
    int y = 0;
    int missileWidth = frameWidth/20;
    int missileHeight = missileWidth*3;

    QString tip = ":/resource/img/tip_"+ QString::number(i+1) +".png";

    QPixmap pix(tip);

    switch(i) {
    case 0:
        ui->prva_traka->setGeometry(x*0+50, y, missileWidth, missileHeight);
        ui->prva_traka->setPixmap(pix);
        ui->prva_traka->setScaledContents(true);
        break;
    case 1:
        ui->druga_traka->setGeometry(x*1+50, y, missileWidth, missileHeight);
        ui->druga_traka->setPixmap(pix);
        ui->druga_traka->setScaledContents(true);
        break;
    case 2:
        ui->treca_traka->setGeometry(x*2+50, y, missileWidth, missileHeight);
        ui->treca_traka->setPixmap(pix);
        ui->treca_traka->setScaledContents(true);
        break;
    case 3:
        ui->cetvrta_traka->setGeometry(x*3+50, y, missileWidth, missileHeight);
        ui->cetvrta_traka->setPixmap(pix);
        ui->cetvrta_traka->setScaledContents(true);
        break;
    case 4:
        ui->peta_traka->setGeometry(x*4+50, y, missileWidth, missileHeight);
        ui->peta_traka->setPixmap(pix);
        ui->peta_traka->setScaledContents(true);
        break;
    default:
        break;
    }
}
