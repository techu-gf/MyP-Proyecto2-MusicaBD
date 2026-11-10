#include "Controlador.hpp"
#include <iostream>
#include <QPushButton>

Controlador::Controlador(Vista& _vista, BaseDatos& _BD, QObject *parent)
	: QObject(parent), vista(_vista), BD(_BD){

	connect(vista.getBotonMinar(), &QPushButton::clicked, this, &Controlador::minar);

        cargar_bd();
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
    std::vector<InfoCancion> canciones;
    std::cout << "Iniciando minado...\n\n";
    try{
	std::string ruta = "Musica/";
	Minero minero(ruta, BD);
        canciones = minero.minar();
    }catch(const std::exception& e){
	std::cerr << "Hubo un error al minar: " << e.what() << "\n";
    }

    for(InfoCancion cancion : canciones){
	vista.agregar_cancion(cancion);
    }

    vista.mostrar_mensaje("Minado terminado");
}

void Controlador::agregar_integrante(){
	
}

void Controlador::agregar_artista(){
	
}

void Controlador::cargar_bd(){
    if(!BD.es_vacia()){
	std::vector<InfoCancion> canciones = BD.obtener_info_canciones();

	for(InfoCancion &cancion : canciones){
	    const char* home = std::getenv("HOME");
	    std::string album_nombre = cancion.name_album;

	    for(char &c : album_nombre){
		if(c == ' ' || c == '/' || c == '\\'){
		    c = '_';
		}
	    }

	    fs::path dir_portada = std::string(home) + "/.local/share/musiquita/albums/" + album_nombre + ".jpg";

	    if(fs::exists(dir_portada)){
		cancion.path_portada = dir_portada.string();
	    }else{
		cancion.path_portada = "src/sources/album_predeterminado.jpg";
	    }
	    vista.agregar_cancion(cancion);
	}
    }
}
