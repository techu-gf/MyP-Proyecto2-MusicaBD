#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>
#include "src/Modelo/InfoCancion.hpp"
#include <QListWidget>

class QPushButton;
class QLineEdit;
class QLabel;

class Vista : public QWidget{
    Q_OBJECT

public:

    explicit Vista(QWidget *parent = 0);
    ~Vista();

    QPushButton* get_boton_minar() const{
	return minar;
    }
    
    void mostrar_mensaje(const std::string& mensaje);
    void agregar_cancion(const InfoCancion& info);
    void mostrar_info(const InfoCancion& info);
    QListWidget* get_lista_canciones() const{
	return lista_canciones;
    }

private:
    
    QWidget* crear_barra_superior();
    QWidget* crear_lista_canciones();
    QWidget* crear_cancion(const InfoCancion& info);
    QWidget* crear_info_cancion();

    QPushButton* minar;
    QListWidget* lista_canciones;
    QLabel *imagen_album;
    QLineEdit *cancion;
    QLineEdit *artista;
    QLineEdit *album;
    QLineEdit *track;
    QLineEdit *anio;
    QLineEdit *genero;
    
};

#endif
