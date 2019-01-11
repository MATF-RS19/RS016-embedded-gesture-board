#ifndef SPACEGLIDER_H
#define SPACEGLIDER_H

#include <QMainWindow>
#include <QtCore>


namespace Ui {
class SpaceGlider;
}

class SpaceGlider : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpaceGlider(QWidget *parent = nullptr);
    ~SpaceGlider();

    void init();

public slots:
    void mySlot();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_pause_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_restart_clicked();

private:
    Ui::SpaceGlider *ui;
    QTimer *timer;
    bool isPaused;
};

#endif // SPACEGLIDER_H
