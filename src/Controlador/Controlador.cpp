#include "Controlador.hpp"
#include <iostream>
#include <QPushButton>

Controlador::Controlador(Vista& _vista, BaseDatos& _BD, QObject *parent)
	: QObject(parent), vista(_vista), BD(_BD){

	connect(vista.getBotonMinar(), &QPushButton::clicked, this, &Controlador::minar);
}

Controlador::~Controlador(){}

void Controlador::consultar(){
	
}

void Controlador::modificar_cancion(){
	
}

void Controlador::modificar_artista(){
	
}

void Controlador::modificar_album(){
	
}

void Controlador::minar(){
    std::cout << "Iniciando minado...\n\n";
    try{
	std::string ruta = "Musica/";
	Minero minero(ruta, BD);
	minero.minar();
    }catch(const std::exception& e){
	std::cerr << "Hubo un error al minar: " << e.what() << "\n";
    }

    vista.mostrarMensaje("Minado terminado");
}

void Controlador::agregar_integrante(){
	
}

void Controlador::agregar_artista(){
	
}
