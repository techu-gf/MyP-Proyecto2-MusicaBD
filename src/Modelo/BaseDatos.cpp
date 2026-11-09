#include <iostream>
#include <string>
#include <sqlite3.h>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "InfoCancion.hpp"

class BaseDatos{

private:
    std::string ruta_bd;
    sqlite3* BD;

    void crear_base_de_datos(){
	std::string sql = "src/sources/rolas.sql";
	std::ifstream archivo(sql);

	if(!archivo.is_open()){
	    std::cerr << "No se pudo abrir rolas.sql.\n";
	    return;
	}

	std::stringstream buffer;
	buffer << archivo.rdbuf();
	std::string sqlStatement = buffer.str();

	char* mensaje = nullptr;
	int ejecucion = sqlite3_exec(BD, sqlStatement.c_str(), NULL, NULL, &mensaje);

	if(ejecucion != SQLITE_OK){
	    std::cerr << "Error al ejecutar el rolas.sql.\n";
	    sqlite3_free(mensaje);
	}else{
	    std::cerr << "Base de datos creada con éxito.\n";
	}
    }

    int obtiene_id_performer(std::string nombre){
	int id = determina_id_performer(nombre);

	if(id != -1){
	    return id;
	}

	agregar_performer(2, nombre);

	return sqlite3_last_insert_rowid(BD);
    }

    int determina_id_performer(std::string nombre){
	const char* select = "SELECT id_performer FROM performers WHERE name = ?;";
	sqlite3_stmt* stmt = nullptr;
	
	int preparacion = sqlite3_prepare_v2(BD, select, -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    sqlite3_bind_text(stmt, 1, nombre.c_str(), -1, SQLITE_TRANSIENT);

	    int ejecucion = sqlite3_step(stmt);

	    if(ejecucion == SQLITE_ROW){
		int id = sqlite3_column_int(stmt, 0);

		return id;
	    }
	}

	sqlite3_finalize(stmt);

	return -1;
    }

    int obtiene_id_album(std::string ruta, std::string nombre, int anio){
	int id = determina_id_album(nombre);

	if(id != -1){
	    return id;
	}

	agregar_album(ruta, nombre, anio);

	return sqlite3_last_insert_rowid(BD);
    }

    int determina_id_album(std::string nombre){
	const char* select = "SELECT id_album FROM albums WHERE name = ?;";
	sqlite3_stmt* stmt = nullptr;
	
	int preparacion = sqlite3_prepare_v2(BD, select, -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    sqlite3_bind_text(stmt, 1, nombre.c_str(), -1, SQLITE_TRANSIENT);

	    int ejecucion = sqlite3_step(stmt);

	    if(ejecucion == SQLITE_ROW){
		int id = sqlite3_column_int(stmt, 0);

		return id;
	    }else{
		
	    }
	}

	sqlite3_finalize(stmt);

	return -1;
    }

    bool ya_existe_cancion(std::string path){
	const char* select = "SELECT id_rola FROM rolas WHERE path = ?;";
	sqlite3_stmt* stmt = nullptr;
	
	int preparacion = sqlite3_prepare_v2(BD, select, -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    sqlite3_bind_text(stmt, 1, path.c_str(), -1, SQLITE_TRANSIENT);

	    int ejecucion = sqlite3_step(stmt);

	    if(ejecucion == SQLITE_ROW){
	        return true;
	    }
	}

	return false;
    }

public:
    BaseDatos(){
	std::string home;
	const char* ruta_home = std::getenv("HOME");

	if(ruta_home != nullptr){
	    home = ruta_home;
	}else{
	    home = ".";
	}
	
	std::string ruta = home + "/.local/share/musiquita";
	std::filesystem::create_directories(ruta);
	
        ruta_bd = ruta + "/musica.db";

	bool bd_existe = std::filesystem::exists(ruta_bd);
	int conexion = sqlite3_open(ruta_bd.c_str(), &BD);

	if(conexion){
	    std::cerr << "Error al intentar abrir la base de datos\n";
	}else{
	    if(!bd_existe){
		std::cout << "Creando base de datos...\n";
		crear_base_de_datos();
	    }else{
		std::cerr << "Conexión exitosa a la base de datos.\n";
	    }
	}
    }
    
    ~BaseDatos(){
	if(BD){
	    sqlite3_close(BD);
	}
    }

    bool es_vacia(){
	const char* sql = "SELECT * FROM rolas LIMIT 1";
	sqlite3_stmt* stmt;
	bool es_vacia = true;

	int preparacion = sqlite3_prepare_v2(BD, sql, -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    int resultado = sqlite3_step(stmt);
	    es_vacia = (resultado != SQLITE_ROW);
	}

	sqlite3_finalize(stmt);
	return es_vacia;
    }

    void consultar(){
	
    }

    std::vector<InfoCancion> obtener_info_canciones(){
	std::vector<InfoCancion> canciones;
	std::string consulta = "SELECT rolas.title, performers.name, albums.name, rolas.track, rolas.year, rolas.genre "
	    "FROM rolas "
	    "LEFT JOIN performers ON rolas.id_performer = performers.id_performer "
	    "LEFT JOIN albums ON rolas.id_album = albums.id_album;";
	sqlite3_stmt* stmt = nullptr;
	
	int preparacion = sqlite3_prepare_v2(BD, consulta.c_str(), -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    while(sqlite3_step(stmt) == SQLITE_ROW){
		InfoCancion cancion;
		cancion.title_rola = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		cancion.name_performer = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		cancion.name_album = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		cancion.track_rola = sqlite3_column_int(stmt, 3);
		cancion.year = sqlite3_column_int(stmt, 4);
		cancion.genre_rola = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

		canciones.push_back(cancion);
	    }
	}

	sqlite3_finalize(stmt);
	return canciones;
    }

    void modificar_cancion(){
	
    }

    void modificar_artista(){
	
    }

    void modificar_album(){
	
    }

    bool agregar_cancion(const InfoCancion& info){
	if(ya_existe_cancion(info.path_rola)){
	    std::cout << "\n\nNo se agregó " << info.title_rola << " ya que ya está en la BD.\n\n";
	    return false;
	}
	const char* insert = "INSERT INTO rolas (id_performer, id_album, path, title, track, year, genre) VALUES (?, ?, ?, ?, ?, ?, ?);";
	sqlite3_stmt* stmt = nullptr;
	
	int preparacion = sqlite3_prepare_v2(BD, insert, -1, &stmt, NULL);

	if(preparacion != SQLITE_OK){
	    return false;
	}
        
	int performer = obtiene_id_performer(info.name_performer);
	int album = obtiene_id_album(info.path_album, info.name_album, info.year);
	    
	sqlite3_bind_int(stmt, 1, performer);
	sqlite3_bind_int(stmt, 2, album);
	sqlite3_bind_text(stmt, 3, info.path_rola.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 4, info.title_rola.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 5, info.track_rola);
	sqlite3_bind_int(stmt, 6, info.year);
	sqlite3_bind_text(stmt, 7, info.genre_rola.c_str(), -1, SQLITE_TRANSIENT);

	int ejecucion = sqlite3_step(stmt);
	bool agregado = false;

	if(ejecucion == SQLITE_DONE){
	    std::cout << "Se agregó la canción " << info.title_rola << "\n";
	    agregado = true;
	}else{
	    std::cout << "No se pudo agregar la canción " << info.title_rola << "\n";
	}
	
	sqlite3_finalize(stmt);
	return agregado;
    }

    void agregar_performer(int tipo, std::string nombre){
	const char* insert = "INSERT INTO performers (id_type, name) VALUES (?, ?);";
	sqlite3_stmt* stmt = nullptr;
	
	int preparacion = sqlite3_prepare_v2(BD, insert, -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    sqlite3_bind_int(stmt, 1, tipo);
	    sqlite3_bind_text(stmt, 2, nombre.c_str(), -1, SQLITE_TRANSIENT);

	    int ejecucion = sqlite3_step(stmt);

	    if(ejecucion == SQLITE_DONE){
		std::cout << "Se agregó al performer " << nombre << "\n";
	    }else{
		std::cout << "No se pudo agregar al performer " << nombre << "\n";
	    }
	}
	
	sqlite3_finalize(stmt);
    }

    void agregar_album(std::string ruta, std::string nombre, int anio){
	const char* insert = "INSERT INTO albums (path, name, year) VALUES (?, ?, ?);";
	sqlite3_stmt* stmt = nullptr;
	
	int preparacion = sqlite3_prepare_v2(BD, insert, -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    sqlite3_bind_text(stmt, 1, ruta.c_str(), -1, SQLITE_TRANSIENT);
	    sqlite3_bind_text(stmt, 2, nombre.c_str(), -1, SQLITE_TRANSIENT);
	    sqlite3_bind_int(stmt, 3, anio);

	    int ejecucion = sqlite3_step(stmt);

	    if(ejecucion == SQLITE_DONE){
		std::cout << "Se agregó el álbum " << nombre << "\n";
	    }else{
		std::cout << "No se pudo agregar el álbum " << nombre << "\n";
	    }
	}
	
	sqlite3_finalize(stmt);
    }

    void agregar_integrante(){
	
    }
};
