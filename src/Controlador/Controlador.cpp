#include "Controlador.hpp"
#include <iostream>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>

Controlador::Controlador(Vista& _vista, BaseDatos& _BD, QObject *parent)
	: QObject(parent), vista(_vista), BD(_BD){

	connect(vista.get_boton_minar(), &QPushButton::clicked, this, &Controlador::minar);
	connect(vista.get_boton_agregar_artista(), &QPushButton::clicked, this, &Controlador::abrir_formulario_nuevo_artista);
	
	connect(vista.get_lista_canciones(), &QListWidget::itemClicked, this, &Controlador::mostrar_cancion);
	connect(vista.get_campo_cancion(), &QLineEdit::editingFinished, this, &Controlador::modificar_cancion);
	connect(vista.get_campo_track(), &QLineEdit::editingFinished, this, &Controlador::modificar_cancion);
	connect(vista.get_campo_anio(), &QLineEdit::editingFinished, this, &Controlador::modificar_cancion);
	connect(vista.get_campo_genero(), &QLineEdit::editingFinished, this, &Controlador::modificar_cancion);

	
	connect(vista.get_campo_artista(), &QLineEdit::editingFinished, this, &Controlador::modificar_artista);
	connect(vista.get_tipo_performer(), qOverload<int>(&QComboBox::currentIndexChanged), this, &Controlador::modificar_artista);
	connect(vista.get_nombre_real(), &QLineEdit::editingFinished, this, &Controlador::modificar_artista);
	connect(vista.get_nacimiento(), &QLineEdit::editingFinished, this, &Controlador::modificar_artista);
	connect(vista.get_fallecimiento(), &QLineEdit::editingFinished, this, &Controlador::modificar_artista);
	connect(vista.get_start_date(), &QLineEdit::editingFinished, this, &Controlador::modificar_artista);
	connect(vista.get_end_date(), &QLineEdit::editingFinished, this, &Controlador::modificar_artista);
	
	connect(vista.get_campo_album(), &QLineEdit::editingFinished, this, &Controlador::modificar_album);
	
	connect(vista.get_integrante_agregado(), &QLineEdit::editingFinished, this, &Controlador::agregar_integrante);
	
        cargar_bd();
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
	}else if(campo == vista.get_nombre_real()){
	    columna = "real_name";
	    BD.modificar_persona(columna, nueva_info.toStdString(), cancion_actual.name_performer);

	    cancion_actual.real_name = nueva_info.toStdString();
	}else if(campo == vista.get_nacimiento()){
	    columna = "birth_date";
	    BD.modificar_persona(columna, nueva_info.toStdString(), cancion_actual.name_performer);

	    cancion_actual.birth_date = nueva_info.toStdString();
	}else if(campo == vista.get_fallecimiento()){
	    columna = "death_date";
	    BD.modificar_persona(columna, nueva_info.toStdString(), cancion_actual.name_performer);

	    cancion_actual.death_date = nueva_info.toStdString();
	}else if(campo == vista.get_start_date()){
	    columna = "start_date";
	    BD.modificar_grupo(columna, nueva_info.toStdString(), cancion_actual.name_performer);

	    cancion_actual.start_date = nueva_info.toStdString();
	}else if(campo == vista.get_end_date()){
	    columna = "end_date";
	    BD.modificar_grupo(columna, nueva_info.toStdString(), cancion_actual.name_performer);

	    cancion_actual.end_date = nueva_info.toStdString();
	}
    }else if(QComboBox *tipo = qobject_cast<QComboBox*>(modificado)){
	if(tipo == vista.get_tipo_performer()){
	    columna = "id_type";
	    int tipo_performer = tipo -> currentIndex();

	    BD.modificar_artista(columna, std::to_string(tipo_performer), path);
	    cancion_actual.type_performer = tipo_performer;

	    if(tipo_performer == 0){
		BD.agregar_person(cancion_actual.name_performer);
		BD.eliminar_grupo(cancion_actual.name_performer);
		
		cancion_actual.integrantes.clear();
		cancion_actual.start_date = "";
		cancion_actual.end_date = "";
	    }else if(tipo_performer == 1){
		BD.agregar_group(cancion_actual.name_performer);
		BD.eliminar_persona(cancion_actual.name_performer);
		
		cancion_actual.real_name = "";
		cancion_actual.birth_date = "";
		cancion_actual.death_date = "";
	    }else{
		BD.eliminar_grupo(cancion_actual.name_performer);
		BD.eliminar_persona(cancion_actual.name_performer);
		
		cancion_actual.real_name = "";
		cancion_actual.birth_date = "";
		cancion_actual.death_date = "";
		cancion_actual.start_date = "";
		cancion_actual.end_date = "";
		cancion_actual.integrantes.clear();
	    }
	}
	
    }
    
    cargar_bd();

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
        minero.minar();
    }catch(const std::exception& e){
	std::cerr << "Hubo un error al minar: " << e.what() << "\n";
    }
    
    cargar_bd();
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
    std::string nombre = vista.get_nombre_form() -> text().toStdString();

    if(nombre.empty()){
	vista.mostrar_mensaje("Debes ponerle un nombre al nuevo artista.");
	return;
    }
    
    int existe = BD.artista_existe(nombre);

    if(existe != -1){
	vista.mostrar_mensaje("El artista " + nombre + " ya existe.");
	return;
    }

    int tipo = vista.get_tipo_performer_form() -> currentIndex();

    BD.agregar_performer(tipo, nombre);

    if(tipo == 0){
	BD.agregar_person(nombre);
	
	std::string nombre_real = vista.get_nombre_real_form() -> text().toStdString();
	std::string fecha_nacimiento = vista.get_nacimiento_form() -> text().toStdString();
	std::string fecha_fallecimiento = vista.get_fallecimiento_form() -> text().toStdString();

	if(!nombre_real.empty()){
	    BD.modificar_persona("real_name", nombre_real, nombre);
	}

	if(!fecha_nacimiento.empty()){
	    BD.modificar_persona("birth_date", fecha_nacimiento, nombre);
	}

	if(!fecha_fallecimiento.empty()){
	    BD.modificar_persona("death_date", fecha_fallecimiento, nombre);
	}
    }else if(tipo == 1){
	BD.agregar_group(nombre);
	
	std::string fecha_inicio = vista.get_fecha_inicio_form() -> text().toStdString();
	std::string fecha_fin = vista.get_fecha_fin_form() -> text().toStdString();

	if(!fecha_inicio.empty()){
	    BD.modificar_grupo("start_date", fecha_inicio, nombre);
	}

	if(!fecha_fin.empty()){
	    BD.modificar_grupo("end_date", fecha_fin, nombre);
	}
    }

    vista.mostrar_mensaje(nombre + " se agregó exitosamente.");
}

void Controlador::cargar_bd(){
    if(!BD.es_vacia()){
	std::string path_cancion_seleccionada = cancion_actual.path_rola;

	QListWidget *lista = vista.get_lista_canciones();
	lista -> clear();
	
	std::vector<InfoCancion> canciones = BD.obtener_info_canciones();
        QListWidgetItem *cancion_seleccionada = nullptr;

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

	    int elementos = lista -> count() - 1;
	    QListWidgetItem *creado = lista -> item(elementos);

	    if(!path_cancion_seleccionada.empty() && cancion.path_rola == path_cancion_seleccionada){
		cancion_seleccionada = creado;
	    }
	}
	
	int elementos = lista -> count();

	if(elementos > 0){
	    if(cancion_seleccionada){
		lista -> setCurrentItem(cancion_seleccionada);
		mostrar_cancion(cancion_seleccionada);
	    }else{
		QListWidgetItem *ultima = lista -> item(elementos -1);
		lista -> setCurrentItem(ultima);
		mostrar_cancion(ultima);
	    }
	}
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

void Controlador::abrir_formulario_nuevo_artista(){
    vista.formulario_agregar_artista();

    connect(vista.get_enviar_formulario(), &QPushButton::clicked, this, &Controlador::agregar_artista);
}
