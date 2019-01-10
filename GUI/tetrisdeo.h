#ifndef TETRISDEO_H
#define TETRISDEO_H

enum tetrisoblici { Nooblik, Zoblik, Soblik, Lineoblik, Toblik, Squareoblik,
                   Loblik, MirroredLoblik };

class tetrisdeo
{
public:
    tetrisdeo() { setoblik(Nooblik); }

    void setRandomoblik();
    void setoblik(tetrisoblici oblik);

    tetrisoblici oblik() const { return oblikDela; }
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

    tetrisoblici oblikDela;
    int koordirante[4][2];
};

#endif

