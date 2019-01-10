#include <QtWidgets>
#include "tetrisprozor.h"
#include "tetrisigra.h"


tetrisprozor::tetrisprozor()
{

    sledeciDeoLabela = new QLabel;
    sledeciDeoLabela->setFrameStyle(QFrame::Box | QFrame::Raised);
    sledeciDeoLabela->setAlignment(Qt::AlignCenter);
    board = new tetrisigra;
    board->setNextPieceLabel(sledeciDeoLabela);

    skor = new QLCDNumber(5);
    skor->setSegmentStyle(QLCDNumber::Filled);

    level = new QLCDNumber(2);
    level->setSegmentStyle(QLCDNumber::Filled);

    linije = new QLCDNumber(5);
    linije->setSegmentStyle(QLCDNumber::Filled);
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

    connect(board, &tetrisigra::scoreChanged,
            skor, qOverload<int>(&QLCDNumber::display));
    connect(board, &tetrisigra::levelChanged,
            level, qOverload<int>(&QLCDNumber::display));
    connect(board, &tetrisigra::linesRemovedChanged,
            linije, qOverload<int>(&QLCDNumber::display));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createLabel(tr("Sledeci")), 0, 0);
    layout->addWidget(sledeciDeoLabela, 1, 0);
    layout->addWidget(createLabel(tr("Nivo")), 2, 0);
    layout->addWidget(level, 3, 0);
    layout->addWidget(startButton, 4, 0);

    layout->addWidget(board, 0, 1, 6, 1);

    layout->addWidget(createLabel(tr("Skor")), 0, 2);
    layout->addWidget(skor, 1, 2);
    layout->addWidget(createLabel(tr("Uklonjene linija")), 2, 2);
    layout->addWidget(linije, 3, 2);
    layout->addWidget(quitButton, 4, 2);
    layout->addWidget(pauseButton, 5, 2);
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
