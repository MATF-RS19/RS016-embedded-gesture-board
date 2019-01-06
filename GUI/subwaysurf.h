#ifndef SUBWAYSURF_H
#define SUBWAYSURF_H

#include <QMainWindow>

namespace Ui {
class SubwaySurf;
}

class SubwaySurf : public QMainWindow
{
    Q_OBJECT

public:
    explicit SubwaySurf(QWidget *parent = nullptr);
    ~SubwaySurf();

private:
    Ui::SubwaySurf *ui;
};

#endif // SUBWAYSURF_H
