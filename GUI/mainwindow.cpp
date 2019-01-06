#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/resource/img/background.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    QMainWindow::showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
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
