#include <QtWidgets>
#include "Vista.hpp"

Vista::Vista(QWidget *parent) : QWidget(parent){

    boton = new QPushButton(tr("Botón de prueba"));
    texto = new QTextBrowser();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout -> addWidget(boton, 0, 0);
    mainLayout -> addWidget(texto, 1, 0);
    setLayout(mainLayout);
    setWindowTitle(tr("Interfaz de prueba"));
}

Vista::~Vista(){
    delete boton;
    delete texto;
}
