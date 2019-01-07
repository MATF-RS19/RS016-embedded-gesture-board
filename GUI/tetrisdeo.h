#ifndef TETRISDEO_H
#define TETRISDEO_H

enum tetrisoblici { NoShape, ZShape, SShape, LineShape, TShape, SquareShape,
                   LShape, MirroredLShape };

class tetrisdeo
{
public:
    tetrisdeo() { setShape(NoShape); }

    void setRandomShape();
    void setShape(tetrisoblici shape);

    tetrisoblici shape() const { return pieceShape; }
    int x(int index) const { return koordirante[index][0]; }
    int y(int index) const { return koordirante[index][1]; }
    int minX() const;
    int maxX() const;
    int minY() const;
    int maxY() const;
    tetrisdeo rotatedLeft() const;
    tetrisdeo rotatedRight() const;

private:
    void setX(int index, int x) { koordirante[index][0] = x; }
    void setY(int index, int y) { koordirante[index][1] = y; }

    tetrisoblici pieceShape;
    int koordirante[4][2];
};

#endif

