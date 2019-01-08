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
    //serial->write("ok");

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
    // TODO djole : else if(reply == QMessageBox::No)


}

void MainWindow::on_pushButtonTetris_clicked()
{
    hide();
    tetrisWindow.showFullScreen();

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

    // gesture komande
    switch(ba[0]) {

    case 0x02:
        // LEFT TO RIGHT
        keybd_event(VK_RIGHT,0x27,0,0);
        break;

   case 0x03:
        // RIGHT TO LEFT
        keybd_event(VK_LEFT,0x25,0,0);
        break;

   case 0x04:
        // BOTTOM TO TOP

        break;

   case 0x05:
        // TOP TO BOTTOM
        keybd_event(VK_SPACE,0x20,0,0);
        break;

    case 0x06:
       // TAP UP
       // ui->pushButtonSubwaySurf->click();
        break;

    case 0x07:
      // TAP DOWN
      // ui->pushButtonTetris->click();
      keybd_event(0x44, 0x44, 0, 0);
       break;

    case 0x08:
        // za odgovor no
        // TAP RIGHT
        // TODO djole
        break;

    case 0x09:
        // kad se otvori exit poruka sa pitanjem, levo je yes
        // TAP LEFT
       // QApplication::exit();
        break;

    case 0x10:
       // exit dugme
       // COUNTER-CLOCKWISE
        keybd_event(VK_DOWN,0x28,0,0);
      //  ui->pushButtonExit->click();
        break;

   case 0x11:
        // CLOCKWISE
        keybd_event(VK_UP,0x26,0,0);
        break;

   case 0xB:
        // DOUBLE TAP DOWN
        ui->pushButtonTetris->click();
        break;

   case 0xC:
        // DOUBLE TAP RIGHT
        break;

   case 0xD:
        // DOUBLE TAP UP
        ui->pushButtonSubwaySurf->click();
        break;

   case 0xE:
        // TAP CENTER
        break;

    case 0xF:
       // DOUBLE TAP CENTER\n
        ui->pushButtonSlideShow->click();
        break;
    }

   // ui->labela->setText(ba);
   // printf(ba);
    qDebug()<<ba;
}
