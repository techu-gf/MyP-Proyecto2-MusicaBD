#include <QtWidgets>
#include "Vista/Vista.hpp"

int main(int argc, char* argv[]){
    QApplication musica(argc, argv);
    
    QFile estilos("src/Vista/formatos.qss");

    if(estilos.open(QFile::ReadOnly | QFile::Text)){
	QTextStream lector(&estilos);
	musica.setStyleSheet(lector.readAll());
    }
    
    Vista ventana;
    ventana.resize(1000, 750);
    ventana.show();

    return musica.exec();
}
