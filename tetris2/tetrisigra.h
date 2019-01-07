#ifndef TETRISIGRA_H
#define TETRISIGRA_H

#include <QBasicTimer>
#include <QFrame>
#include <QPointer>

#include "tetrisdeo.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class tetrisigra : public QFrame
{
    Q_OBJECT

public:
    tetrisigra(QWidget *parent = 0);

    void setNextPieceLabel(QLabel *label);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

public slots:
    void start();
    void pause();

signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void linesRemovedChanged(int numLines);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    enum { BoardWidth = 10, BoardHeight = 22 };

    tetrisoblici &shapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }
    int timeoutTime() { return 1000 / (1 + level); }
    int squareWidth() { return contentsRect().width() / BoardWidth; }
    int squareHeight() { return contentsRect().height() / BoardHeight; }
    void clearBoard();
    void dropDown();
    void oneLineDown();
    void pieceDropped(int dropHeight);
    void removeFullLines();
    void newPiece();
    void showNextPiece();
    bool tryMove(const tetrisdeo &newPiece, int newX, int newY);
    void drawSquare(QPainter &painter, int x, int y, tetrisoblici shape);

    QBasicTimer timer;
    QPointer<QLabel> nextPieceLabel;
    bool isStarted;
    bool isPaused;
    bool isWaitingAfterLine;
    tetrisdeo curPiece;
    tetrisdeo nextPiece;
    int curX;
    int curY;
    int numLinesRemoved;
    int numPiecesDropped;
    int score;
    int level;
    tetrisoblici board[BoardWidth * BoardHeight];
};

#endif
