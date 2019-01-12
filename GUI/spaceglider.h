#ifndef SPACEGLIDER_H
#define SPACEGLIDER_H

#include <QMainWindow>
#include <QtCore>
#include <QLabel>

namespace Ui {
class SpaceGlider;
}

class SpaceGlider : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpaceGlider(QWidget *parent = nullptr);
    ~SpaceGlider() override;

    void init();

    void turnLeft();
    void turnRight();
    void goForward();
    void goBackward();

    QLabel* fireMissile();

    void create_label();


private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_pause_clicked();

    void on_pushButton_start_clicked();

    void timerSlot();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::SpaceGlider *ui;
    QTimer *timer;
    bool isPaused;

    int positionH;
    int positionV;

    int nextMissile;

    QVector<QLabel*> missiles;
};

#endif // SPACEGLIDER_H
