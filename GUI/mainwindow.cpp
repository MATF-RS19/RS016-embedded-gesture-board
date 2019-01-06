#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>

// uart
#include <QSerialPort>
#include <QDebug>
#include <QKeyEvent>

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
    printf("Connect\n");

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
    tetrisWindow = new Tetris(this);
    tetrisWindow->show();
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

    // tap na gesture ---> klik na dugme
    switch(ba[0]) {
    case 0x06:
       // printf("TAP UP\n");
        ui->pushButtonSubwaySurf->click();
        break;

    case 0x07:
      // printf("TAP DOWN\n");
       ui->pushButtonTetris->click();
        break;

    case 0xE:
       // printf("TAP CENTER\n");
        ui->pushButtonSlideShow->click();
        break;

    case 0x10:
       // exit dugme
       // printf("CLOCKWISE\n");
        ui->pushButtonExit->click();
        break;

    case 0x09:
        // kad se otvori exit poruka sa pitanjem, levo je yes
        // printf("TAP LEFT\n");
        QApplication::exit();
        break;

    case 0x08:
        // za odgovor no
        // TAP RIGHT
        // TODO djole
        break;
    }

   // ui->labela->setText(ba);
   // printf(ba);
    qDebug()<<ba;
}
