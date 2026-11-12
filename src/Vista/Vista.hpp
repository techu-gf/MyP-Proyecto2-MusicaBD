#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>
#include "src/Modelo/InfoCancion.hpp"
#include <QListWidget>

class QPushButton;
class QLineEdit;
class QLabel;
class QComboBox;
class QStackedWidget;

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
    void actualizar_info_cancion(const InfoCancion& info);

    QListWidget* get_lista_canciones() const{
	return lista_canciones;
    }

    QLineEdit* get_campo_cancion() const{
	return cancion;
    }

    QLineEdit* get_campo_artista() const{
	return artista;
    }

    QLineEdit* get_campo_album() const{
	return album;
    }

    QLineEdit* get_campo_track() const{
	return track;
    }

    QLineEdit* get_campo_anio() const{
	return anio;
    }

    QLineEdit* get_campo_genero() const{
	return genero;
    }

    QComboBox* get_tipo_performer() const{
	return tipo_performer;
    }

    QLineEdit* get_integrante_agregado() const{
	return agregar_integrante;
    }

    QLineEdit* get_nombre_real() const{
	return nombre_real;
    }

    QLineEdit* get_nacimiento() const{
	return nacimiento;
    }

    QLineEdit* get_fallecimiento() const{
	return fallecimiento;
    }

    QLineEdit* get_start_date() const{
	return start_date;
    }

    QLineEdit* get_end_date() const{
	return end_date;
    }

private:
    
    QWidget* crear_barra_superior();
    QWidget* crear_lista_canciones();
    QWidget* crear_cancion(const InfoCancion& info);
    QWidget* crear_info_cancion();
    QWidget* crear_info_solista();
    QWidget* crear_info_grupo();
    QWidget* crear_info_unknown();

    QPushButton* minar;
    QListWidget* lista_canciones;
    QLabel *imagen_album;
    QLineEdit *cancion;
    QLineEdit *artista;
    QLineEdit *album;
    QLineEdit *track;
    QLineEdit *anio;
    QLineEdit *genero;
    QComboBox *tipo_performer;

    QLineEdit *nombre_real;
    QLineEdit *nacimiento;
    QLineEdit *fallecimiento;
    
    QLabel *integrantes;
    QLineEdit *agregar_integrante;
    QLineEdit *start_date;
    QLineEdit *end_date;
    
    QStackedWidget *info_canciones;
    QWidget *solista;
    QWidget *grupo;
    QWidget *unknown;
    
};

#endif
