#ifndef CONTROLADOR_HPP
#define CONTROLADOR_HPP

#include <QObject>
#include "src/Vista/Vista.hpp"
#include "src/Modelo/Minero.cpp"

class Controlador : public QObject{
    Q_OBJECT

private:
    Vista& vista;
    BaseDatos& BD;

public:
    explicit Controlador(Vista& _vista, BaseDatos& _BD, QObject *parent = nullptr);
    ~Controlador();

private slots:
    void consultar();
    void modificar_cancion();
    void modificar_artista();
    void modificar_album();
    void minar();
    void agregar_integrante();
    void agregar_artista();
    void cargar_bd();
};

#endif
