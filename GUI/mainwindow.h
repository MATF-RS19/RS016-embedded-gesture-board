#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tetris.h"
#include "slideshow.h"
#include "subwaysurf.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonExit_clicked();

    void on_pushButtonTetris_clicked();

    void on_pushButtonSlideShow_clicked();

    void on_pushButtonSubwaySurf_clicked();

private:
    Ui::MainWindow *ui;
    Tetris *tetrisWindow;
    SlideShow *slideShowWindow;
    SubwaySurf *subwaySurfWindow;
};

#endif // MAINWINDOW_H
