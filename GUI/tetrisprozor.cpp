#include <QtWidgets>
#include "tetrisprozor.h"
#include "tetrisigra.h"


tetrisprozor::tetrisprozor()
{

    board = new tetrisigra;

    //funkcija tr omogucava da se niska vidi isti na svakoj platformi
    startButton = new QPushButton(tr("&tap up to Start"));
    startButton->setFocusPolicy(Qt::NoFocus);

    quitButton = new QPushButton(tr("&tap right to Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);

    pauseButton = new QPushButton(tr("&tap down to Pause/Resume"));
    pauseButton->setFocusPolicy(Qt::NoFocus);

    connect(startButton, &QPushButton::clicked, board, &tetrisigra::start);
    connect(quitButton , &QPushButton::clicked, this, &tetrisprozor::close);
    connect(pauseButton, &QPushButton::clicked, board, &tetrisigra::pause);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(board, 3, 0, 7, 1);
    layout->addWidget(startButton, 0, 0);
    layout->addWidget(quitButton, 2, 0);
    layout->addWidget(pauseButton, 1, 0);
    setLayout(layout);


    quitButton->setShortcut(QKeySequence(Qt::Key_D));
    startButton->setShortcut(QKeySequence(Qt::Key_W));
    pauseButton->setShortcut(QKeySequence(Qt::Key_S));
    setWindowTitle(tr("Tetris"));
    resize(380, 700);
}
QLabel *tetrisprozor::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}
