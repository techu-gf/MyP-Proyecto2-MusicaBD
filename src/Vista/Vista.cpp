#include <QtWidgets>
#include <QToolTip>
#include "Vista.hpp"

Vista::Vista(QWidget *parent) : QWidget(parent){
    QWidget *barra_superior = crear_barra_superior();
    QWidget *lista_canciones = crear_lista_canciones();
    QWidget *info_cancion = crear_info_cancion();
    
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout -> addWidget(barra_superior, 0, 0, 1, 2);
    mainLayout -> addWidget(lista_canciones, 1, 0, 1, 1);
    mainLayout -> addWidget(info_cancion, 1, 1, 1, 1);

    mainLayout -> setRowStretch(1, 1);
    mainLayout -> setColumnStretch(0, 2);
    mainLayout -> setColumnStretch(1, 1);
    mainLayout -> setSpacing(15);
    mainLayout -> setContentsMargins(15, 15, 15, 15);

    this -> setObjectName("vista");
    
    setLayout(mainLayout);
    setWindowTitle(tr("Música"));
}

Vista::~Vista(){}

QWidget* Vista::crear_barra_superior(){
    QWidget *box = new QWidget();

    minar = new QPushButton(box);
    QPushButton* agregar_artista = new QPushButton(box);
    QLineEdit* consulta = new QLineEdit(box);
    
    minar -> setIcon(QIcon("src/sources/iconos/minar.png"));
    minar -> setIconSize(QSize(33, 33));
    minar -> setObjectName("boton-barra");

    agregar_artista -> setIcon(QIcon("src/sources/iconos/agregar_artista.png"));
    agregar_artista -> setIconSize(QSize(33, 33));
    agregar_artista -> setObjectName("boton-barra");

    consulta -> setObjectName("entrada-texto");
    
    QHBoxLayout *barra = new QHBoxLayout();
    barra -> setContentsMargins(20, 10, 20, 10);
    barra -> setSpacing(15);
    barra -> addWidget(minar);
    barra -> addWidget(agregar_artista);
    barra -> addStretch();
    barra -> addWidget(consulta);

    box -> setLayout(barra);
    box -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    box -> setObjectName("seccion");

    return box;
}

QWidget* Vista::crear_lista_canciones(){
    QWidget *box = new QWidget();

    lista_canciones = new QListWidget(box);
    lista_canciones -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lista_canciones -> setObjectName("lista");
    
    QVBoxLayout *layout = new QVBoxLayout(box);
    layout -> addWidget(lista_canciones);
    layout -> setContentsMargins(0, 0, 0, 0);
    layout -> setSpacing(0);
    
    box -> setLayout(layout);
    box -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    box -> setObjectName("seccion");
    return box;
}

void Vista::agregar_cancion(const InfoCancion& info){
    QListWidgetItem *widget = new QListWidgetItem(lista_canciones);
    QWidget *cancion = crear_cancion(info);

    widget -> setData(Qt::UserRole, QVariant::fromValue(info));
    widget -> setSizeHint(cancion -> sizeHint());
    lista_canciones -> setItemWidget(widget, cancion);
}

QWidget* Vista::crear_cancion(const InfoCancion& info){
    QWidget *cancion = new QWidget();

    QPushButton* ver_mas = new QPushButton(cancion);
    QLabel *performer = new QLabel(QString::fromStdString(info.name_performer), cancion);
    QLabel *title = new QLabel(QString::fromStdString(info.title_rola), cancion);
    QLabel *year = new QLabel(QString::number(info.year), cancion);
    QLabel *genero = new QLabel(QString::fromStdString(info.genre_rola), cancion);

    QPixmap pixmap(QString::fromStdString(info.path_portada));

    if(!pixmap.isNull()){
	ver_mas -> setIcon(QIcon(pixmap));
    }else{
	ver_mas -> setIcon(QIcon("src/sources/album_predeterminado.jpg"));
    }

    ver_mas -> setIconSize(QSize(60, 60));
    ver_mas -> setFixedSize(60, 60);
    
    performer -> setObjectName("info-extra");
    title -> setObjectName("info-principal");
    year -> setObjectName("info-extra");
    genero -> setObjectName("info-extra");
    
    QVBoxLayout *cuadro_info1 = new QVBoxLayout();
    cuadro_info1 -> addWidget(performer);
    cuadro_info1 -> addWidget(title);

    QVBoxLayout *cuadro_info2 = new QVBoxLayout();
    cuadro_info2 -> addWidget(year);
    cuadro_info2 -> addWidget(genero);
    
    QHBoxLayout *info_contenedor = new QHBoxLayout(cancion);
    info_contenedor -> setContentsMargins(20, 10, 20, 10);
    info_contenedor -> setSpacing(15);
    info_contenedor -> addWidget(ver_mas);
    info_contenedor -> addLayout(cuadro_info1);
    info_contenedor -> addStretch();
    info_contenedor -> addLayout(cuadro_info2);

    cancion -> setLayout(info_contenedor);
    cancion -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    
    return cancion;
}

void Vista::actualizar_info_cancion(const InfoCancion& info){
    QListWidgetItem *item = lista_canciones -> currentItem();

    if(!item) return;

    item -> setData(Qt::UserRole, QVariant::fromValue(info));

    QWidget *nuevo_widget = crear_cancion(info);
    item -> setSizeHint(nuevo_widget -> sizeHint());
    lista_canciones -> setItemWidget(item, nuevo_widget);
}

QWidget* Vista::crear_info_cancion(){
    QWidget *box = new QWidget();

    imagen_album = new QLabel(box);
    imagen_album -> setFixedSize(180, 180);
    
    QLabel *cancionLetrero = new QLabel("Cancion:", box);
    cancionLetrero -> setObjectName("info-principal");
    cancion = new QLineEdit(box);
    cancion -> setObjectName("entrada-texto");

    QLabel *artistaLetrero = new QLabel("Artista:", box);
    artistaLetrero -> setObjectName("info-principal");
    artista = new QLineEdit(box);
    artista -> setObjectName("entrada-texto");

    QLabel *albumLetrero = new QLabel("Album:", box);
    albumLetrero -> setObjectName("info-principal"); 
    album = new QLineEdit(box);
    album -> setObjectName("entrada-texto");

    QLabel *trackLetrero = new QLabel("No. de canción:", box);
    trackLetrero -> setObjectName("info-principal");
    track = new QLineEdit(box);
    track -> setObjectName("entrada-texto");

    QLabel *anioLetrero = new QLabel("Año:", box);
    anioLetrero -> setObjectName("info-principal"); 
    anio = new QLineEdit(box);
    anio -> setObjectName("entrada-texto");

    QLabel *generoLetrero = new QLabel("Género:", box);
    generoLetrero -> setObjectName("info-principal");
    genero = new QLineEdit(box);
    genero -> setObjectName("entrada-texto"); 
    
    anio -> setValidator(new QIntValidator(box));
    track -> setValidator(new QIntValidator(box));

    QLabel *tipoLetrero = new QLabel("Tipo de performer:", box);
    tipoLetrero -> setObjectName("info-principal");
    tipo_performer = new QComboBox(box);
    tipo_performer -> addItem("Solista/Persona");
    tipo_performer -> addItem("Grupo");
    tipo_performer -> addItem("Unknown");
    tipo_performer -> setObjectName("tipo-performer");
    tipo_performer -> setFocusPolicy(Qt::ClickFocus);

    nombre_real = new QLineEdit(box);
    nombre_real -> setObjectName("entrada-texto"); 
    nacimiento = new QLineEdit(box);
    nacimiento -> setObjectName("entrada-texto"); 
    fallecimiento = new QLineEdit(box);
    fallecimiento -> setObjectName("entrada-texto");
    
    integrantes = new QLabel(box);
    integrantes -> setObjectName("info-principal");
    agregar_integrante = new QLineEdit(box);
    agregar_integrante -> setObjectName("entrada-texto");
    agregar_integrante -> setEnabled(false);
    start_date = new QLineEdit(box);
    start_date -> setObjectName("entrada-texto");
    end_date = new QLineEdit(box);
    end_date -> setObjectName("entrada-texto");

    info_canciones = new QStackedWidget(box);

    solista = crear_info_solista();
    grupo = crear_info_grupo();
    unknown = crear_info_unknown();

    info_canciones -> addWidget(solista);
    info_canciones -> addWidget(grupo);
    info_canciones -> addWidget(unknown);

    QWidget *contenedor = new QWidget(box);
    QVBoxLayout *info = new QVBoxLayout(contenedor);
    info -> setContentsMargins(20, 10, 20, 10);
    info -> setSpacing(8);
    info -> addWidget(imagen_album);
    info -> addWidget(cancionLetrero);
    info -> addWidget(cancion);
    info -> addWidget(artistaLetrero);
    info -> addWidget(artista);
    info -> addWidget(albumLetrero);
    info -> addWidget(album);
    info -> addWidget(trackLetrero);
    info -> addWidget(track);
    info -> addWidget(anioLetrero);
    info -> addWidget(anio);
    info -> addWidget(generoLetrero);
    info -> addWidget(genero);
    info -> addWidget(tipoLetrero);
    info -> addWidget(tipo_performer);
    info -> addWidget(info_canciones);
    info -> setAlignment(imagen_album, Qt::AlignCenter);
    
    contenedor -> setLayout(info);
    contenedor -> setObjectName("seccion");

    QScrollArea *desplazar = new QScrollArea(box);
    desplazar -> setContentsMargins(0, 0, 0, 0);
    desplazar -> setWidget(contenedor);
    desplazar -> setWidgetResizable(true);
    desplazar -> setObjectName("desplazamiento");

    QVBoxLayout *principal = new QVBoxLayout(box);
    principal -> setContentsMargins(0, 0, 0, 0);
    principal -> addWidget(desplazar);
    
    box -> setLayout(principal);
    box -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    box -> setObjectName("seccion");

    return box;
}

QWidget* Vista::crear_info_solista(){
    QWidget *box = new QWidget();

    QLabel *nombre_realLetrero = new QLabel("Nombre real: ", box);
    nombre_realLetrero -> setObjectName("info-principal");

    QLabel *nacimientoLetrero = new QLabel("Nacimiento: ", box);
    nacimientoLetrero -> setObjectName("info-principal");

    QLabel *fallecimientoLetrero = new QLabel("Fallecimiento: ", box);
    fallecimientoLetrero -> setObjectName("info-principal");

    QVBoxLayout *info = new QVBoxLayout(box);
    info -> setContentsMargins(0, 0, 0, 0);
    info -> addWidget(nombre_realLetrero);
    info -> addWidget(nombre_real);
    info -> addWidget(nacimientoLetrero);
    info -> addWidget(nacimiento);
    info -> addWidget(fallecimientoLetrero);
    info -> addWidget(fallecimiento);
    info -> setSpacing(8);

    box -> setLayout(info);
    box -> setObjectName("seccion");

    return box;
}

QWidget* Vista::crear_info_grupo(){
    QWidget *box = new QWidget();

    QLabel *integrantesLetrero = new QLabel("Integrantes: ", box);
    integrantesLetrero -> setObjectName("info-principal");

    QLabel *inicioLetrero = new QLabel("Debut: ", box);
    inicioLetrero -> setObjectName("info-principal");

    QLabel *finalizacionLetrero = new QLabel("Separación: ", box);
    finalizacionLetrero -> setObjectName("info-principal");

    QVBoxLayout *info = new QVBoxLayout(box);
    info -> setContentsMargins(0, 0, 0, 0);
    info -> setSpacing(8);
    info -> addWidget(integrantesLetrero);
    info -> addWidget(integrantes);
    info -> addWidget(agregar_integrante);
    info -> addWidget(inicioLetrero);
    info -> addWidget(start_date);
    info -> addWidget(finalizacionLetrero);
    info -> addWidget(end_date);
    info -> addStretch();

    box -> setLayout(info);
    box -> setObjectName("seccion");

    return box;
}

QWidget* Vista::crear_info_unknown(){
    QWidget *box = new QWidget();

    QVBoxLayout *info = new QVBoxLayout(box);
    info -> setContentsMargins(0, 0, 0, 0);
    info -> setSpacing(8);

    box -> setLayout(info);
    box -> setObjectName("seccion");

    return box;
}

void Vista::mostrar_info(const InfoCancion& info){
    int tipoP = info.type_performer;
    info_canciones -> setCurrentIndex(tipoP);
    tipo_performer -> blockSignals(true);
    tipo_performer -> setCurrentIndex(tipoP);
    tipo_performer -> blockSignals(false);
    
    if(tipoP == 0){
	nombre_real-> setText(QString::fromStdString(info.real_name));
        nacimiento -> setText(QString::fromStdString(info.birth_date));
        fallecimiento -> setText(QString::fromStdString(info.death_date));

	integrantes -> setText("");
	agregar_integrante -> clear();
    }else if(tipoP == 1){
	agregar_integrante -> setEnabled(true);

	std::string integrantes_lista = "";

	for(std::string nombre : info.integrantes){
	    integrantes_lista.append(nombre + " | ");
	}

	integrantes -> setText(QString::fromStdString(integrantes_lista));
	agregar_integrante -> setText("");
	start_date -> setText(QString::fromStdString(info.start_date));
	end_date -> setText(QString::fromStdString(info.end_date));

	nombre_real -> clear();
	nacimiento -> clear();
	fallecimiento -> clear();
    }else{
        agregar_integrante -> setEnabled(false);
	integrantes -> setText("");
	nombre_real -> clear();
	nacimiento -> clear();
	fallecimiento -> clear();
    }
    
    cancion -> setText(QString::fromStdString(info.title_rola));
    artista -> setText(QString::fromStdString(info.name_performer));
    album -> setText(QString::fromStdString(info.name_album));
    track -> setText(QString::number(info.track_rola));
    anio -> setText(QString::number(info.year));
    genero -> setText(QString::fromStdString(info.genre_rola));

    QPixmap pixmap(QString::fromStdString(info.path_portada));

    if(!pixmap.isNull()){
        imagen_album -> setPixmap(pixmap.scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }else{
        imagen_album -> setPixmap(QPixmap("src/sources/album_predeterminado.jpg").scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    
    imagen_album -> setFixedSize(180,180);
    
}

void Vista::mostrar_mensaje(const std::string& mensaje){
    QString msg = QString::fromStdString(mensaje);

    QPoint punto(this -> width()/2, this -> height() - 140);

    QToolTip::showText(punto, msg, this, QRect(), 5000);
}
