#include <QtWidgets>
#include <stdlib.h>

#include "tetrisprozor.h"

int main(int argc,char** argv){
    QApplication app(argc,argv);
    tetrisprozor prozor;
    prozor.show();
    return app.exec();
}
