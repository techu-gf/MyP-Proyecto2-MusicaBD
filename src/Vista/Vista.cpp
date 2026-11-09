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

QWidget* Vista::crear_info_cancion(){
    QWidget *box = new QWidget();
    
    QLabel *imagen_album = new QLabel(box);
    imagen_album -> setFixedSize(100, 100);

    QLabel *cancionLetrero = new QLabel("Cancion:", box);
    QLineEdit *cancion = new QLineEdit(box);
    cancionLetrero -> setObjectName("info-principal");
    cancion -> setObjectName("entrada-texto"); 
    
    QLabel *artistaLetrero = new QLabel("Artista:", box);
    QLineEdit *artista = new QLineEdit(box);
    artistaLetrero -> setObjectName("info-principal");
    artista -> setObjectName("entrada-texto"); 
    
    QLabel *albumLetrero = new QLabel("Album:", box);
    QLineEdit *album = new QLineEdit(box);
    albumLetrero -> setObjectName("info-principal"); 
    album -> setObjectName("entrada-texto"); 

    QLabel *trackLetrero = new QLabel("No. de canción:", box);
    QLineEdit *track = new QLineEdit(box);
    track -> setValidator(new QIntValidator(box));
    track -> setObjectName("entrada-texto"); 
    trackLetrero -> setObjectName("info-principal");

    QLabel *anioLetrero = new QLabel("Año:", box);
    QLineEdit *anio = new QLineEdit(box);
    anio -> setValidator(new QIntValidator(box));
    anio -> setObjectName("entrada-texto"); 
    anioLetrero -> setObjectName("info-principal"); 

    QLabel *generoLetrero = new QLabel("Género:", box);
    QLineEdit *genero = new QLineEdit(box);
    generoLetrero -> setObjectName("info-principal"); 
    genero -> setObjectName("entrada-texto"); 

    QVBoxLayout *info = new QVBoxLayout(box);
    info -> setContentsMargins(20, 10, 20, 10);
    info -> setSpacing(10);
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

    box -> setLayout(info);
    box -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    box -> setObjectName("seccion");

    return box;
}

void Vista::mostrar_mensaje(const std::string& mensaje){
    QString msg = QString::fromStdString(mensaje);

    QPoint punto(this -> width()/2, this -> height() - 140);

    QToolTip::showText(punto, msg, this, QRect(), 5000);
}
