#ifndef SLIDESHOW_H
#define SLIDESHOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtGui>


namespace Ui {
class SlideShow;
}

class SlideShow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SlideShow(QWidget *parent = nullptr);
    ~SlideShow();

    void rotate(double a);
    void zoom(double s, double f);
    void reset();
    void importImages(int type);

private slots:

    void on_exitButton_clicked();

    void on_nextButton_clicked();

    void on_previousButton_clicked();

    void on_rotateLButton_clicked();

    void on_rotateRButton_clicked();

    void on_zoomInButton_clicked();

    void on_zoomOutButton_clicked();

private:
    Ui::SlideShow *ui;

};

#endif // SLIDESHOW_H
