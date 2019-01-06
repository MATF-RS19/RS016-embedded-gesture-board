#ifndef TETRIS_H
#define TETRIS_H

#include <QMainWindow>

namespace Ui {
class Tetris;
}

class Tetris : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tetris(QWidget *parent = nullptr);
    ~Tetris();

private:
    Ui::Tetris *ui;
};

#endif // TETRIS_H
