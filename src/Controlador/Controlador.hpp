#ifndef CONTROLADOR_HPP
#define CONTROLADOR_HPP

#include <QObject>
#include "src/Vista/Vista.hpp"
#include "src/Modelo/Minero.cpp"

/**
 * @brief La clase Controlador se encarga de coordinar lo que se realiza y muestra en
 * la Vista y lo que ocurre en el Modelo.
 */
class Controlador : public QObject{
    Q_OBJECT

private:
    Vista& vista;
    BaseDatos& BD;
    InfoCancion cancion_actual;

public:

    /**
     * @brief Constructor donde se vinculan las acciones de la vista a los métodos del 
     * controlador. También se encarga de cargar la base de datos en la vista. 
     * @param _vista Vista a la que controlará. 
     * @param _BD Base de datos que se usará para la Vista.
     * @param parent Objeto padre de la ventana.
     */
    explicit Controlador(Vista& _vista, BaseDatos& _BD, QObject *parent = nullptr);
    ~Controlador();

private slots:

    /**
     * @brief Método que le avisa a la base de datos que el usuario desea realizar
     * una consulta. 
     */
    void consultar();
    
    /**
     * @brief Método que actualiza la info mostrada de la canción modificada.
     */
    void modificar_info();

    /**
     * @brief Método que modifica en la base de datos la info de la canción cambiada
     * por el usuario.
     */
    void modificar_cancion();

    /**
     * @brief Método que modifica en la base de datos la info del artista cambiada
     * por el usuario.
     */
    void modificar_artista();

    /**
     * @brief Método que modifica en la base de datos la info del album cambiada por
     * el usuario.
     */
    void modificar_album();

    /**
     * @brief Método que le avisa al minero que actúe cuando lo indica el usuario. 
     */
    void minar();

    /**
     * @brief Método que le indica a la base de datos que agregue un integrante dado
     * por el usuario al grupo indicado.
     */
    void agregar_integrante();

    /**
     * @brief Método que le indica a la base de datos que cree un artista (solista o grupo)
     * con la información dada por el usuario. 
     */
    void agregar_artista();

    /**
     * @brief Método que obtiene todas las canciones de la base de datos para mostrarlas en
     * la vista. 
     */
    void cargar_bd();

    /**
     * @brief Método que le dice a la vista que muestre la información de la canción
     * seleccionada.
     * @param item Canción seleccionada.  
     */
    void mostrar_cancion(QListWidgetItem *item);

    /**
     * @brief Método que le indica a la vista que muestre el formulario para agregar un
     * artista. 
     */
    void abrir_formulario_nuevo_artista();
};

#endif
