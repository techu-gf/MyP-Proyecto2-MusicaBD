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

/**
 * @brief La clase Vista se encarga de la interfaz, mostrando la info indicada en
 * los lugares indicados. 
 */
class Vista : public QWidget{
    Q_OBJECT

public:

    /**
     * @brief Constructor que crea y organiza la vista principal.
     * @param parent Objeto padre de la ventana principal.
     */
    explicit Vista(QWidget *parent = 0);
    ~Vista();

    /**
     * @brief Método que obtiene el botón destinado a minar. 
     * @return QPushButton Puntero al botón de minado en la interfaz. 
     */
    QPushButton* get_boton_minar() const{
	return minar;
    }

    /**
     * @brief Método que obtiene el botón que indica que se quiere agregar un artista. 
     * @return QPushButton Puntero al botón de agregar artista en la interfaz. 
     */
    QPushButton* get_boton_agregar_artista() const{
	return agregar_artista;
    }

    /**
     * @brief Método que obtiene el botón para enviar la info para crear un artista.
     * @return QPushButton Puntero al botón para enviar la información en la interfaz. 
     */
    QPushButton* get_enviar_formulario() const{
	return enviar_formulario;
    }

    /**
     * @brief Método que obtiene el campo de texto donde se realizan las búsquedas. 
     * @return QLineEdit Puntero al campo de texto para búsquedas en la interfaz. 
     */
    QLineEdit* get_consulta() const{
	return consulta;
    }

    /**
     * @brief Método que muestra un mensaje por unos segundos. 
     * @param mensaje Mensaje que se le mostrará al usuario. 
     */
    void mostrar_mensaje(const std::string& mensaje);

    /**
     * @brief Método que agrega una canción a la lista de canciones mostrada en la interfaz.
     * @param info Estructura con la info de la canción a agregar.
     */
    void agregar_cancion(const InfoCancion& info);

    /**
     * @brief Método que muestra la información de la canción en el panel derecho de la interfaz. 
     * @param info Estructura con la info de la canción a mostrar. 
     */
    void mostrar_info(const InfoCancion& info);

    /**
     * @brief Método que actualiza la info mostrada en la lista de una canción dada. 
     * @param info Estructura con la nueva info de la canción. 
     */
    void actualizar_info_cancion(const InfoCancion& info);

    /**
     * @brief Método que crea el formulario para agregar un nuevo artista.
     */
    void formulario_agregar_artista();

    /**
     * @brief Método que muestra el formulario para agregar un nuevo artista. 
     */
    void mostrar_formulario();

    /**
     * @brief Método que obtiene la lista de canciones de la interfaz. 
     * @return QListWidget Puntero a la lista de canciones en la interfaz. 
     */
    QListWidget* get_lista_canciones() const{
	return lista_canciones;
    }

    /**
     * @brief Método que obtiene el campo de texto donde se muestra el nombre de la canción. 
     * @return QLineEdit Puntero al campo de texto con el nombre de la canción en la interfaz. 
     */
    QLineEdit* get_campo_cancion() const{
	return cancion;
    }

    /**
     * @brief Método que obtiene el campo de texto donde se muestra el nombre del artista. 
     * @return QLineEdit Puntero al campo de texto con el nombre del artista en la interfaz. 
     */
    QLineEdit* get_campo_artista() const{
	return artista;
    }

    /**
     * @brief Método que obtiene el campo de texto donde se muestra el nombre del album.
     * @return QLineEdit Puntero al campo de texto con el nombre del album en la interfaz. 
     */
    QLineEdit* get_campo_album() const{
	return album;
    }

    /**
     * @brief Método que obtiene el campo de texto donde se muestra el número de canción
     * en el álbum. 
     * @return QLineEdit Puntero al campo de texto con el número de canción en la interfaz. 
     */
    QLineEdit* get_campo_track() const{
	return track;
    }

    /**
     * @brief Método que obtiene el campo de texto donde se muestra el año de la canción. 
     * @return QLineEdit Puntero al campo de texto con el año de la canción en la interfaz. 
     */
    QLineEdit* get_campo_anio() const{
	return anio;
    }

    /**
     * @brief Método que obtiene el campo de texto donde se muestra el género de la canción. 
     * @return QLineEdit Puntero al campo de texto con el género de la canción en la interfaz. 
     */
    QLineEdit* get_campo_genero() const{
	return genero;
    }

    /**
     * @brief Método que obtiene el objeto con las opciones del tipo de performer. 
     * @return QComboBox Puntero al objeto con las opciones del tipo de performer. 
     */
    QComboBox* get_tipo_performer() const{
	return tipo_performer;
    }

    /**
     * @brief Método que obtiene el campo de texto donde se muestra el integrante a agregar
     * a un grupo. 
     * @return QLineEdit Puntero al campo de texto con el integrante a agregar en la interfaz. 
     */
    QLineEdit* get_integrante_agregado() const{
	return agregar_integrante;
    }

    /**
     * @brief Método que obtiene el campo de texto donde se muestra el nombre real de un solista. 
     * @return QLineEdit Puntero al campo de texto con el nombre real de un solista en la
     * interfaz. 
     */
    QLineEdit* get_nombre_real() const{
	return nombre_real;
    }

    /**
     * @brief Método que obtiene el campo de texto donde se muestra la fecha de nacimiento de
     * un solista. 
     * @return QLineEdit Puntero al campo de texto con la fecha de nacimiento de un solista en
     * la interfaz. 
     */
    QLineEdit* get_nacimiento() const{
	return nacimiento;
    }

    /**
     * @brief Método que obtiene el campo de texto donde se muestra la fecha de fallecimiento
     * de un solista. 
     * @return QLineEdit Puntero al campo de texto con la fecha de fallecimiento de un
     * solista en la interfaz. 
     */
    QLineEdit* get_fallecimiento() const{
	return fallecimiento;
    }

    /**
     * @brief Método que obtiene el campo de texto donde se muestra la fecha de inicio de
     * una banda. 
     * @return QLineEdit Puntero al campo de texto con la fecha de inicio de una banda en la
     * interfaz. 
     */
    QLineEdit* get_start_date() const{
	return start_date;
    }

    /**
     * @brief Método que obtiene el campo de texto donde se muestra la fecha de separación
     * de una banda. 
     * @return QLineEdit Puntero al campo de texto con la fecha de separación de una banda
     * en la interfaz. 
     */
    QLineEdit* get_end_date() const{
	return end_date;
    }

    /**
     * @brief Método que obtiene el objeto con las opciones del tipo de performer del formulario. 
     * @return QComboBox Puntero al objeto con las opciones del tipo de performer del formulario. 
     */
    QComboBox* get_tipo_performer_form() const{
	return tipo_performer_f;
    }

    /**
     * @brief Método que obtiene el campo de texto donde se muestra el nombre del artista del formulario. 
     * @return QLineEdit Puntero al campo de texto con el nombre del artista en el formulario. 
     */
    QLineEdit* get_nombre_form() const{
	return name;
    }

    /**
     * @brief Método que obtiene el campo de texto con el nombre real del artista en el
     * formulario. 
     * @return QLineEdit Puntero al campo de texto con el nombre real del artista en el
     * formulario. 
     */
    QLineEdit* get_nombre_real_form() const{
	return nombre_real_f;
    }

    /**
     * @brief Método que obtiene el campo de texto con la fecha de nacimiento del artista
     * en el formulario. 
     * @return QLineEdit Puntero al campo de texto con la fecha de nacimiento del artista
     * en el formulario. 
     */
    QLineEdit* get_nacimiento_form() const{
	return fecha_nacim;
    }
    
    /**
     * @brief Método que obtiene el campo de texto con la fecha de fallecimiento del artista
     * en el formulario. 
     * @return QLineEdit Puntero al campo de texto con la fecha de fallecimiento del artista
     * en el formulario. 
     */
    QLineEdit* get_fallecimiento_form() const{
	return fecha_fallec;
    }

    /**
     * @brief Método que obtiene el campo de texto con la fecha de inicio del grupo en el
     * formulario. 
     * @return QLineEdit Puntero al campo de texto con la fecha de inicio del grupo en el
     * formulario. 
     */
    QLineEdit* get_fecha_inicio_form() const{
	return fecha_inicio;
    }

    /**
     * @brief Método que obtiene el campo de texto con la fecha de separación del grupo en
     * el formulario. 
     * @return QLineEdit Puntero al campo de texto con la fecha de separación del grupo en
     * el formulario. 
     */
    QLineEdit* get_fecha_fin_form() const{
	return fecha_fin;
    }

private:

    /**
     * @brief Método que crea la barra superior de la interfaz. 
     */
    QWidget* crear_barra_superior();

    /**
     * @brief Método que crea la lista de las canciones (panel izquierdo).
     */
    QWidget* crear_lista_canciones();

    /**
     * @brief Método que crea el orden que se muestra al mostrar la info de una canción
     * en la lista.
     * @param info Estructura con la información de la canción. 
     */
    QWidget* crear_cancion(const InfoCancion& info);

    /**
     * @brief Método que crea la vista con la info general de alguna canción (panel derecho).
     */
    QWidget* crear_info_cancion();

    /**
     * @brief Método que crea una pequeña sección en el panel derecho para info específica para
     * solistas. 
     */
    QWidget* crear_info_solista();

    /**
     * @brief Método que crea una pequeña sección en el panel derecho para info específica para
     * grupos. 
     */
    QWidget* crear_info_grupo();

    /**
     * @brief Método que crea una pequeña sección en el panel derecho para info específica para
     * artistas de tipo unknown. 
     */
    QWidget* crear_info_unknown();

    QPushButton* minar;
    QPushButton* agregar_artista;
    QLineEdit* consulta;
    
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

    QWidget *ventana_agregar_artista = nullptr;

    /**
     * @brief Método que crea una pequeña sección en el formulario para info específica de solistas. 
     */
    QWidget* formulario_persona();

    /**
     * @brief Método que crea una pequeña sección en el formulario para info específica de grupos. 
     */
    QWidget* formulario_grupo();

    QStackedWidget *formulario;
    QLineEdit *name;
    QComboBox *tipo_performer_f;
    QLineEdit *nombre_real_f;
    QLineEdit *fecha_nacim;
    QLineEdit *fecha_fallec;
    QLineEdit *fecha_inicio;
    QLineEdit *fecha_fin;
    QPushButton *enviar_formulario;
    
};

#endif
