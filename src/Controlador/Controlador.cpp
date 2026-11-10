#include "Controlador.hpp"
#include <iostream>
#include <QPushButton>

Controlador::Controlador(Vista& _vista, BaseDatos& _BD, QObject *parent)
	: QObject(parent), vista(_vista), BD(_BD){

	connect(vista.get_boton_minar(), &QPushButton::clicked, this, &Controlador::minar);
	connect(vista.get_lista_canciones(), &QListWidget::itemClicked, this, &Controlador::mostrar_cancion);
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

    if(!canciones.empty()){
	InfoCancion ultima_cancion;

	for(InfoCancion cancion : canciones){
	    vista.agregar_cancion(cancion);
	    ultima_cancion = cancion;
	}
    
	vista.mostrar_info(ultima_cancion);
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
	InfoCancion ultima_cancion;

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

	    ultima_cancion = cancion;
	}

	vista.mostrar_info(ultima_cancion);
    }
}

void Controlador::mostrar_cancion(QListWidgetItem *item){
    if(!item) return;

    InfoCancion info = item -> data(Qt::UserRole).value<InfoCancion>();

    vista.mostrar_info(info);
}
