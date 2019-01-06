#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include <QWidget>
#include <QFrame>

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE


class tetrisprozor : public QWidget
{
    Q_OBJECT

public:
    tetrisprozor();

private:
    //kreira labelu sa poravnanjem
    QLabel *createLabel(const QString &text);

    QLabel *sledeci;
    //QLCDNumber su samo lepsi brojevi
    QLCDNumber *skor;
    QLCDNumber *level;
    QLCDNumber *linije;
    QPushButton *startButton;
    QPushButton *quitButton;
    QPushButton *pauseButton;
};
#endif
