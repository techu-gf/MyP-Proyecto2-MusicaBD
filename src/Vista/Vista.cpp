#include <QtWidgets>
#include "Vista.hpp"

Vista::Vista(QWidget *parent) : QWidget(parent){
    QGroupBox *barra_superior = crearBarraSuperior();
    
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout -> addWidget(barra_superior, 0, 0, 1, 2);

    this -> setStyleSheet("background-color: #121212");
    
    setLayout(mainLayout);
    setWindowTitle(tr("Música"));
}

Vista::~Vista(){}

QGroupBox* Vista::crearBarraSuperior(){
    QGroupBox *box = new QGroupBox();
    
    QPushButton* minar = new QPushButton(box);
    QPushButton* agregar_artista = new QPushButton(box);
    QLineEdit* consulta = new QLineEdit(box);
    
    minar -> setIcon(QIcon("src/sources/iconos/minar.png"));
    minar -> setIconSize(QSize(33, 33));
    minar -> setStyleSheet("border: 0px;"
	"background-color: #B0B0B0;"
	"border-radius: 20px;"
	"padding: 5px;");

    agregar_artista -> setIcon(QIcon("src/sources/iconos/agregar_artista.png"));
    agregar_artista -> setIconSize(QSize(33, 33));
    agregar_artista -> setStyleSheet("border: 0px;"
	"background-color: #B0B0B0;"
	"border-radius: 20px;"
	"padding: 5px;");

    consulta -> setStyleSheet("background-color: #B0B0B0;"
	"border-radius: 8px;"
	"padding: 6px;");
    
    QHBoxLayout *barra = new QHBoxLayout();
    barra -> setContentsMargins(20, 10, 20, 10);
    barra -> setSpacing(15);
    barra -> addWidget(minar);
    barra -> addWidget(agregar_artista);
    barra -> addStretch();
    barra -> addWidget(consulta);

    box -> setLayout(barra);
    box -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    box -> setStyleSheet("background-color: #444444;"
	"border-radius: 6px;");

    return box;
}
