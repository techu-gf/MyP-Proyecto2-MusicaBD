#include <QtWidgets>
#include "Controlador/Controlador.hpp"

int main(int argc, char* argv[]){
    QApplication musica(argc, argv);
    
    QFile estilos("src/Vista/formatos.qss");

    if(estilos.open(QFile::ReadOnly | QFile::Text)){
	QTextStream lector(&estilos);
	musica.setStyleSheet(lector.readAll());
    }
    
    Vista ventana;
    BaseDatos base_de_datos;
    Controlador ctrl(ventana, base_de_datos);
    
    ventana.resize(1000, 750);
    ventana.show();

    return musica.exec();
}
