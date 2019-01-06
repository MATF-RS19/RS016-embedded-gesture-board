#include "tetrisprozor.h"
#include <QtWidgets>
tetrisprozor::tetrisprozor()
{
    sledeci = new QLabel;
    sledeci->setFrameStyle(QFrame::Box | QFrame::Raised);
    sledeci->setAlignment(Qt::AlignCenter);

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

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createLabel(tr("Sledeci")), 0, 0);
    layout->addWidget(sledeci, 1, 0);
    layout->addWidget(createLabel(tr("Nivo")), 2, 0);
    layout->addWidget(level, 3, 0);
    layout->addWidget(startButton, 4, 0);

    //

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
