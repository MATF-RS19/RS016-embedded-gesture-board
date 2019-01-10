#ifndef TETRISIGRA_H
#define TETRISIGRA_H

#include <QBasicTimer>
#include <QFrame>
#include <QObject>
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

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    enum { BoardWidth = 10, BoardHeight = 22 };

    tetrisoblici &oblikAt(int x, int y) { return board[(y * BoardWidth) + x]; }
    int timeoutTime() { return 750; }
    int squareWidth() { return contentsRect().width() / BoardWidth; }
    int squareHeight() { return contentsRect().height() / BoardHeight; }
    void clearBoard();
    void dropDown();
    void oneLineDown();
    void pieceDropped();
    void removeFullLines();
    void newPiece();
    void showNextPiece();
    bool tryMove(const tetrisdeo &newPiece, int newX, int newY);
    void drawSquare(QPainter &painter, int x, int y, tetrisoblici oblik);

    QBasicTimer timer;
    QPointer<QLabel> nextPieceLabel;
    bool isStarted;
    bool isPaused;
    bool isWaitingAfterLine;
    tetrisdeo curPiece;
    tetrisdeo nextPiece;
    int curX;
    int curY;
    int numPiecesDropped;
    tetrisoblici board[BoardWidth * BoardHeight];
};

#endif
