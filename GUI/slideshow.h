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

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:

    void on_exitButton_clicked();

    void on_nextButton_clicked();

    void on_previousButton_clicked();

private:
    Ui::SlideShow *ui;
};

#endif // SLIDESHOW_H
