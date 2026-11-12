#include "Controlador.hpp"
#include <iostream>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>

Controlador::Controlador(Vista& _vista, BaseDatos& _BD, QObject *parent)
	: QObject(parent), vista(_vista), BD(_BD){

	connect(vista.get_boton_minar(), &QPushButton::clicked, this, &Controlador::minar);
	
	connect(vista.get_lista_canciones(), &QListWidget::itemClicked, this, &Controlador::mostrar_cancion);
	connect(vista.get_campo_cancion(), &QLineEdit::editingFinished, this, &Controlador::modificar_cancion);
	connect(vista.get_campo_artista(), &QLineEdit::editingFinished, this, &Controlador::modificar_artista);
	connect(vista.get_campo_album(), &QLineEdit::editingFinished, this, &Controlador::modificar_album);
	connect(vista.get_campo_track(), &QLineEdit::editingFinished, this, &Controlador::modificar_cancion);
	connect(vista.get_campo_anio(), &QLineEdit::editingFinished, this, &Controlador::modificar_cancion);
	connect(vista.get_campo_genero(), &QLineEdit::editingFinished, this, &Controlador::modificar_cancion);
        cargar_bd();
	connect(vista.get_tipo_performer(), qOverload<int>(&QComboBox::currentIndexChanged), this, &Controlador::modificar_artista);
	connect(vista.get_integrante_agregado(), &QLineEdit::editingFinished, this, &Controlador::agregar_integrante);
}

Controlador::~Controlador(){}

void Controlador::consultar(){
	
}

void Controlador::modificar_info(){
    QListWidgetItem *item = vista.get_lista_canciones() -> currentItem();

    if(item){
        item -> setData(Qt::UserRole, QVariant::fromValue(cancion_actual));

	vista.actualizar_info_cancion(cancion_actual);
    }

    vista.mostrar_info(cancion_actual);
}

void Controlador::modificar_cancion(){
    QLineEdit *campo = qobject_cast<QLineEdit*>(sender());

    if(!campo) return;

    QString nueva_info = campo -> text();
    std::string columna = "";
    std::string path = cancion_actual.path_rola;

    if(campo == vista.get_campo_cancion()){
	columna = "title";
	cancion_actual.title_rola = nueva_info.toStdString();
    }else  if(campo == vista.get_campo_track()){
	columna = "track";
	cancion_actual.track_rola = nueva_info.toInt();
    }else  if(campo == vista.get_campo_anio()){
	columna = "year";
	BD.modificar_album(columna, nueva_info.toStdString(), path);
	cancion_actual.year = nueva_info.toInt();
    }else  if(campo == vista.get_campo_genero()){
	columna = "genre";
	cancion_actual.genre_rola = nueva_info.toStdString();
    }

    if(columna.empty()) return;
    
    BD.modificar_cancion(columna, nueva_info.toStdString(), path);

    modificar_info();
}

void Controlador::modificar_artista(){
    QObject *modificado = sender();

    if(!modificado) return;
    
    std::string columna = "";
    std::string path = cancion_actual.path_rola;

    if(QLineEdit *campo = qobject_cast<QLineEdit*>(modificado)){
	QString nueva_info = campo -> text();
	
        if(campo == vista.get_campo_artista()){
	    columna = "name";
	    BD.modificar_artista(columna, nueva_info.toStdString(), path);
	    cancion_actual.name_performer = nueva_info.toStdString();

	    vista.get_lista_canciones() -> clear();
	    cargar_bd();
	}
    }else if(QComboBox *tipo = qobject_cast<QComboBox*>(modificado)){
	if(tipo == vista.get_tipo_performer()){
	    columna = "id_type";
	    int tipo_performer = tipo -> currentIndex();

	    BD.modificar_artista(columna, std::to_string(tipo_performer), path);
	    cancion_actual.type_performer = tipo_performer;
	    
	    vista.get_lista_canciones() -> clear();
	    cargar_bd();
	}
    }

    if(columna.empty()) return;

    modificar_info();
}

void Controlador::modificar_album(){
    QLineEdit *campo = qobject_cast<QLineEdit*>(sender());

    if(!campo) return;

    QString nueva_info = campo -> text();
    std::string columna = "";
    std::string path = cancion_actual.path_rola;

    if(campo == vista.get_campo_album()){
	columna = "name";
	BD.modificar_album(columna, nueva_info.toStdString(), path);
	cancion_actual.name_album = nueva_info.toStdString();
    }

    if(columna.empty()) return;

    modificar_info();
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
    
    InfoCancion ultima_cancion;
    
    if(!canciones.empty()){

	for(InfoCancion cancion : canciones){
	    vista.agregar_cancion(cancion);
	    ultima_cancion = cancion;
	}
    
	vista.mostrar_info(ultima_cancion);
    }

    cancion_actual = ultima_cancion;
    vista.mostrar_mensaje("Minado terminado");
}

void Controlador::agregar_integrante(){
    QLineEdit *campo = qobject_cast<QLineEdit*>(sender());

    if(!campo) return;

    QString nueva_info = campo -> text();
    std::string integrante = nueva_info.toStdString();
    std::string nombre_grupo = cancion_actual.name_performer;
    
    if(campo == vista.get_integrante_agregado()){
	std::string integrante = nueva_info.toStdString();
	std::string nombre_grupo = cancion_actual.name_performer;

	if(!integrante.empty()){
	    try{
		BD.agregar_integrante(integrante, nombre_grupo);
		vista.mostrar_mensaje("Integrante añadido.");
		campo -> clear();

		cancion_actual.integrantes = BD.obtener_integrantes(nombre_grupo);
		
		vista.mostrar_info(cancion_actual);
	    }catch(const ErrorBD& e){
		vista.mostrar_mensaje(e.what());
	    }
	}
    }

    modificar_info();
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

	cancion_actual = ultima_cancion;
	vista.mostrar_info(ultima_cancion);
    }
}

void Controlador::mostrar_cancion(QListWidgetItem *item){
    if(!item) return;

    cancion_actual = item -> data(Qt::UserRole).value<InfoCancion>();

    if(cancion_actual.type_performer == 1){
	cancion_actual.integrantes = BD.obtener_integrantes(cancion_actual.name_performer);
    }else{
	cancion_actual.integrantes.clear();
    }

    item -> setData(Qt::UserRole, QVariant::fromValue(cancion_actual));

    vista.mostrar_info(cancion_actual);
}
