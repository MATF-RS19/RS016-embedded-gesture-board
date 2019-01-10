#include <QtWidgets>
#include "tetrisprozor.h"
#include "tetrisigra.h"


tetrisprozor::tetrisprozor()
{

    board = new tetrisigra;

    //funkcija tr omogucava da se niska vidi isti na svakoj platformi
    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);

    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);

    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setFocusPolicy(Qt::NoFocus);

    connect(startButton, &QPushButton::clicked, board, &tetrisigra::start);
    connect(quitButton , &QPushButton::clicked, qApp, &QApplication::quit);
    connect(pauseButton, &QPushButton::clicked, board, &tetrisigra::pause);


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(board, 0, 0, 6, 1);
    layout->addWidget(startButton, 1, 1);
    layout->addWidget(quitButton, 5, 1);
    layout->addWidget(pauseButton, 3, 1);
    setLayout(layout);

    setWindowTitle(tr("Tetris"));
    resize(550, 370);
}
QLabel *tetrisprozor::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}
