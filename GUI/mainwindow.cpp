#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>

#include <QWidget>

// uart
#include <QSerialPort>
#include <QDebug>
#include <QKeyEvent>
#include <windows.h>
QSerialPort *serial;

// bajtovi koji stizu sa ploce
#define LEFT_TO_RIGHT 0x02
#define RIGHT_TO_LEFT 0x03
#define BOTTOM_TO_TOP 0x04
#define TOP_TO_BOTTOM 0x05
#define TAP_UP 0x06
#define TAP_DOWN 0x07
#define TAP_RIGHT 0x08
#define TAP_LEFT 0x09
#define COUNTER_CLOCKWISE 0x10
#define CLOCKWISE 0x11
#define DOUBLE_TAP_LEFT 0xA
#define DOUBLE_TAP_DOWN 0xB
#define DOUBLE_TAP_RIGHT 0xC
#define DOUBLE_TAP_UP 0xD
#define TAP_CENTER 0xE
#define DOUBLE_TAP_CENTER 0xF

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/resource/img/background.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    //uart
    serial = new QSerialPort(this);

    serial->setPortName("com6");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);

    connect(serial, SIGNAL(readyRead()), this, SLOT(serialRecieved()));


   QMainWindow::showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
}

void MainWindow::on_pushButtonExit_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Exit", "Are you sure you want to exit", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes)
        QApplication::exit();

}

void MainWindow::on_pushButtonTetris_clicked()
{
    hide();
    tetrisWindow.show();

}

void MainWindow::on_pushButtonSlideShow_clicked()
{
    hide();
    slideShowWindow = new SlideShow(this);
    slideShowWindow->show();
}

void MainWindow::on_pushButtonSubwaySurf_clicked()
{
    hide();
    subwaySurfWindow = new SubwaySurf(this);
    subwaySurfWindow->show();
}

// uart
void MainWindow::serialRecieved()
{
    QByteArray ba;

    // citanje serijskog porta
    ba = serial->readAll();

    // simulira se pritiskanje na tastaturi
    switch(ba[0]) {

    case LEFT_TO_RIGHT:
        keybd_event(VK_RIGHT,0x27,0,0);
        break;

   case RIGHT_TO_LEFT:
        keybd_event(VK_LEFT,0x25,0,0);
        break;

   case BOTTOM_TO_TOP:
        keybd_event(VK_UP,0x26,0,0);
        break;

   case TOP_TO_BOTTOM:
        keybd_event(VK_DOWN,0x28,0,0);
        break;

    case TAP_UP:
        keybd_event(0x57, 0x57, 0, 0);  // W key
        break;

    case TAP_DOWN:
      keybd_event(0x53, 0x53, 0, 0);  // S key
      break;

    case TAP_RIGHT:
        keybd_event(0x44, 0x44, 0, 0);  // D key
        break;

    case TAP_LEFT:
        keybd_event(0x41, 0x41, 0, 0);  // A key
        break;

    case COUNTER_CLOCKWISE:
        keybd_event(0x58, 0x58, 0, 0);  // X key
        break;

   case CLOCKWISE:
        keybd_event(0x5A,0x5A,0,0);     // Z key
        break;


   case DOUBLE_TAP_LEFT:

        break;

   case DOUBLE_TAP_DOWN:
        ui->pushButtonTetris->click();
        break;

   case DOUBLE_TAP_RIGHT:
        QApplication::exit();
        break;

   case DOUBLE_TAP_UP:
        ui->pushButtonSubwaySurf->click();
        break;

   case TAP_CENTER:

        break;

    case DOUBLE_TAP_CENTER:
        ui->pushButtonSlideShow->click();
        break;
    }

    qDebug()<<ba;

    qDebug()<<ba;
}
