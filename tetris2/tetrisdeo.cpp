#include <QtCore>

#include <stdlib.h>

#include "tetrisdeo.h"

void tetrisdeo::setRandomoblik()
{
    setoblik(tetrisoblici(QRandomGenerator::global()->bounded(7) + 1));
}

void tetrisdeo::setoblik(tetrisoblici oblik)//dodeljujemo koordinate teminima
{
    static const int coordsTable[8][4][2] = {
        { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
        { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },//Z
        { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },//S
        { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },//Linija
        { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },//T
        { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },//Kocka
        { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },//L
        { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }//neL
    };

    for (int i = 0; i < 4 ; i++) {
        for (int j = 0; j < 2; ++j)
            koordirante[i][j] = coordsTable[oblik][i][j];
    }
    oblikDela = oblik;
}

int tetrisdeo::minX() const
{
    int min = koordirante[0][0];
    for (int i = 1; i < 4; ++i)
        min = qMin(min, koordirante[i][0]);
    return min;
}

int tetrisdeo::maxX() const
{
    int max = koordirante[0][0];
    for (int i = 1; i < 4; ++i)
        max = qMax(max, koordirante[i][0]);
    return max;
}
int tetrisdeo::minY() const
{
    int min = koordirante[0][1];
    for (int i = 1; i < 4; ++i)
        min = qMin(min, koordirante[i][1]);
    return min;
}

int tetrisdeo::maxY() const
{
    int max = koordirante[0][1];
    for (int i = 1; i < 4; ++i)
        max = qMax(max, koordirante[i][1]);
    return max;
}
tetrisdeo tetrisdeo::rotatedLeft() const
{
    if (oblikDela == Squareoblik)//ako je oblik kocka onda nema okretanja
        return *this;

    tetrisdeo rez;
    rez.oblikDela = oblikDela;
    for (int i = 0; i < 4; ++i) {//za sva cetri dela puzle vrsimo pomeranje koordinata
        rez.setX(i, y(i));
        rez.setY(i, -x(i));
    }
    return rez;
}

tetrisdeo tetrisdeo::rotatedRight() const
{
    if (oblikDela == Squareoblik)
        return *this;

    tetrisdeo rez;
    rez.oblikDela = oblikDela;
    for (int i = 0; i < 4; ++i) {
        rez.setX(i, -y(i));
        rez.setY(i, x(i));
    }
    return rez;
}
