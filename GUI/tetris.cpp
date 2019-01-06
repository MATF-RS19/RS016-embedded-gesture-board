#include "tetris.h"
#include "ui_tetris.h"

Tetris::Tetris(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tetris)
{
    ui->setupUi(this);
}

Tetris::~Tetris()
{
    delete ui;
}
