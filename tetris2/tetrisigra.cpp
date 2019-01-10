#include <QtWidgets>

#include "tetrisigra.h"


tetrisigra::tetrisigra(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    this->setGeometry(0, 0, 300, 100);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    isStarted = false;
    isPaused = false;
    clearBoard();

    nextPiece.setRandomoblik();
}

void tetrisigra::setNextPieceLabel(QLabel *label)
{
    nextPieceLabel = label;
}

QSize tetrisigra::sizeHint() const//ova i sledeca funkcije se koriste za velicine svakog QWidget-a
{
    return QSize(BoardWidth * 15 + frameWidth() * 2,
                 BoardHeight * 15 + frameWidth() * 2);
}

QSize tetrisigra::minimumSizeHint() const
{
    return QSize(BoardWidth * 5 + frameWidth() * 2,
                 BoardHeight * 5 + frameWidth() * 2);
}
void tetrisigra::start()
{
    if (isPaused)
        return;

    isStarted = true;
    isWaitingAfterLine = false;
    numPiecesDropped = 0;
    clearBoard();
    newPiece();
    timer.start(750, this);
}

void tetrisigra::pause()
{
    if (!isStarted)
        return;

    isPaused = !isPaused;
    if (isPaused) {
        timer.stop();
    } else {
        timer.start(750, this);
    }
    update();
}

void tetrisigra::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);


    QPainter painter(this);
    QRect rect = contentsRect();

    if (isPaused) {
        painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
        return;
    }
    int boardTop = rect.bottom() - BoardHeight*squareHeight();

    for (int i = 0; i < BoardHeight; ++i) {
        for (int j = 0; j < BoardWidth; ++j) {
            tetrisoblici oblik = oblikAt(j, BoardHeight - i - 1);
            if (oblik != Nooblik)
                drawSquare(painter, rect.left() + j * squareWidth(),
                           boardTop + i * squareHeight(), oblik);
        }
    }
    if (curPiece.oblik() != Nooblik) {
        for (int i = 0; i < 4; ++i) {
            int x = curX + curPiece.x(i);
            int y = curY - curPiece.y(i);
            drawSquare(painter, rect.left() + x * squareWidth(),
                       boardTop + (BoardHeight - y - 1) * squareHeight(),
                       curPiece.oblik());
        }
    }
}

void tetrisigra::keyPressEvent(QKeyEvent *event)
{
    if (!isStarted || isPaused || curPiece.oblik() == Nooblik) {
        QFrame::keyPressEvent(event);
        return;
    }

    switch (event->key()) {
    case Qt::Key_Left:
        tryMove(curPiece, curX - 1, curY);
        break;
    case Qt::Key_Right:
        tryMove(curPiece, curX + 1, curY);
        break;
    case Qt::Key_X:
        tryMove(curPiece.rotatedRight(), curX, curY);
        break;
    case Qt::Key_Z:
        tryMove(curPiece.rotatedLeft(), curX, curY);
        break;
    case Qt::Key_Down:
        dropDown();
        break;
    case Qt::Key_S:
        oneLineDown();
        break;
    default:
        QFrame::keyPressEvent(event);
    }
}

void tetrisigra::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        if (isWaitingAfterLine) {
            isWaitingAfterLine = false;
            newPiece();
            timer.start(750, this);
        } else {
            oneLineDown();
        }
    } else {
        QFrame::timerEvent(event);
    }
}
void tetrisigra::clearBoard()
{
    for (int i = 0; i < BoardHeight * BoardWidth; ++i)
        board[i] = Nooblik;
}

void tetrisigra::dropDown()
{
    int dropHeight = 0;
    int newY = curY;
    while (newY > 0) {
        if (!tryMove(curPiece, curX, newY - 1))
            break;
        --newY;
        ++dropHeight;
    }
    pieceDropped();
}

void tetrisigra::oneLineDown()
{
    if (!tryMove(curPiece, curX, curY - 1))
        pieceDropped();
}

void tetrisigra::pieceDropped()
{
    for (int i = 0; i < 4; ++i) {
        int x = curX + curPiece.x(i);
        int y = curY - curPiece.y(i);
        oblikAt(x, y) = curPiece.oblik();
    }

    ++numPiecesDropped;
    removeFullLines();

    if (!isWaitingAfterLine)
        newPiece();
}

void tetrisigra::removeFullLines()
{
    int numFullLines = 0;

    for (int i = BoardHeight - 1; i >= 0; --i) {
        bool lineIsFull = true;

        for (int j = 0; j < BoardWidth; ++j) {
            if (oblikAt(j, i) == Nooblik) {
                lineIsFull = false;
                break;
            }
        }

        if (lineIsFull) {
            ++numFullLines;
            for (int k = i; k < BoardHeight - 1; ++k) {
                for (int j = 0; j < BoardWidth; ++j)
                    oblikAt(j, k) = oblikAt(j, k + 1);
            }
            for (int j = 0; j < BoardWidth; ++j)
                oblikAt(j, BoardHeight - 1) = Nooblik;
        }
    }
    if (numFullLines > 0){
        timer.start(750, this);
        isWaitingAfterLine = true;
        curPiece.setoblik(Nooblik);
        update();
    }
}

void tetrisigra::newPiece()
{
    curPiece = nextPiece;
    nextPiece.setRandomoblik();
    showNextPiece();
    curX = BoardWidth / 2 + 1;
    curY = BoardHeight - 1 + curPiece.minY();

    if (!tryMove(curPiece, curX, curY)) {
        curPiece.setoblik(Nooblik);
        timer.stop();
        isStarted = false;
    }
}

void tetrisigra::showNextPiece()
{
    if (!nextPieceLabel)
        return;

    int dx = nextPiece.maxX() - nextPiece.minX() + 1;
    int dy = nextPiece.maxY() - nextPiece.minY() + 1;

    QPixmap pixmap(dx * squareWidth(), dy * squareHeight());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), nextPieceLabel->palette().background());

    for (int i = 0; i < 4; ++i) {
        int x = nextPiece.x(i) - nextPiece.minX();
        int y = nextPiece.y(i) - nextPiece.minY();
        drawSquare(painter, x * squareWidth(), y * squareHeight(),
                   nextPiece.oblik());
    }
    nextPieceLabel->setPixmap(pixmap);
}

bool tetrisigra::tryMove(const tetrisdeo &newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + newPiece.x(i);
        int y = newY - newPiece.y(i);
        if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
            return false;
        if (oblikAt(x, y) != Nooblik)
            return false;
    }
    curPiece = newPiece;
    curX = newX;
    curY = newY;
    update();
    return true;
}

void tetrisigra::drawSquare(QPainter &painter, int x, int y, tetrisoblici oblik)
{
    static const QRgb colorTable[8] = {
        0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
        0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
    };

    QColor color = colorTable[int(oblik)];
    painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
                     color);

    painter.setPen(color.light());
    painter.drawLine(x, y + squareHeight() - 1, x, y);
    painter.drawLine(x, y, x + squareWidth() - 1, y);

    painter.setPen(color.dark());
    painter.drawLine(x + 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + squareHeight() - 1);
    painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + 1);
}

