#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "slideshow.h"
#include "spaceglider.h"
#include "tetrisprozor.h"

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

    void on_pushButtonSpaceGlider_clicked();

    // uart
   void serialRecieved();

private:
    Ui::MainWindow *ui;
    tetrisprozor tetrisWindow;
    // Tetris *tetrisWindow;
    SlideShow *slideShowWindow;
    SpaceGlider *SpaceGliderWindow;
};

#endif // MAINWINDOW_H
