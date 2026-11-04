#include <QtWidgets>
#include "Vista/Vista.hpp"

int main(int argc, char* argv[]){
    QApplication musica(argc, argv);

    Vista ventana;
    ventana.resize(1000, 750);
    ventana.show();

    return musica.exec();
}
