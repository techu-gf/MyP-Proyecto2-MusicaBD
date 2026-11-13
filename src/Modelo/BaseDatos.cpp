#include <iostream>
#include <string>
#include <sqlite3.h>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "InfoCancion.hpp"
#include "ErrorBD.hpp"

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

	sqlite3_finalize(stmt);

	return false;
    }

    int persona_existe(std::string nombre_persona){
	const char* busqueda = "SELECT id_person FROM persons WHERE stage_name = ?;";
	sqlite3_stmt* stmt = nullptr;
	int id = -1;

	int preparacion = sqlite3_prepare_v2(BD, busqueda, -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    sqlite3_bind_text(stmt, 1, nombre_persona.c_str(), -1, SQLITE_TRANSIENT);

	    int ejecucion = sqlite3_step(stmt);

	    if(ejecucion == SQLITE_ROW){
		id = sqlite3_column_int(stmt, 0);
	    }
	}

	sqlite3_finalize(stmt);
	return id;
    }

    int grupo_existe(std::string nombre_grupo){
	const char* busqueda = "SELECT id_group FROM groups WHERE name = ?;";
	sqlite3_stmt* stmt = nullptr;
	int id = -1;

	int preparacion = sqlite3_prepare_v2(BD, busqueda, -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    sqlite3_bind_text(stmt, 1, nombre_grupo.c_str(), -1, SQLITE_TRANSIENT);

	    int ejecucion = sqlite3_step(stmt);

	    if(ejecucion == SQLITE_ROW){
		id = sqlite3_column_int(stmt, 0);
	    }
	}

	sqlite3_finalize(stmt);
	return id;
    }

    int obtiene_tipo(int id_performer){
        const char* busqueda = "SELECT id_type FROM performers WHERE id_performer = ?;";
	sqlite3_stmt* stmt = nullptr;
        int id_type = 2;

	int preparacion = sqlite3_prepare_v2(BD, busqueda, -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    sqlite3_bind_int(stmt, 1, id_performer);

	    int ejecucion = sqlite3_step(stmt);

	    if(ejecucion == SQLITE_ROW){
	        id_type = sqlite3_column_int(stmt, 0);
	    }
	}

	sqlite3_finalize(stmt);
	return id_type;
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
	std::string consulta = "SELECT rolas.title, performers.name, albums.name, rolas.track, rolas.year, rolas.genre, rolas.path, performers.id_type, persons.real_name, persons.birth_date, persons.death_date, groups.start_date, groups.end_date "
	    "FROM rolas "
	    "LEFT JOIN performers ON rolas.id_performer = performers.id_performer "
	    "LEFT JOIN albums ON rolas.id_album = albums.id_album "
	    "LEFT JOIN persons ON performers.name = persons.stage_name "
	    "LEFT JOIN groups ON performers.name = groups.name;";
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
		cancion.path_rola = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
		cancion.type_performer = sqlite3_column_int(stmt, 7);
		
		cancion.integrantes = obtener_integrantes(cancion.name_performer);

	        auto nombre_real = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
		cancion.real_name = nombre_real ? nombre_real : "";
		auto nacimiento = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
		cancion.birth_date = nacimiento ? nacimiento : "";
		auto fallecimiento = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
		cancion.death_date = fallecimiento ? fallecimiento : "";
		auto inicio = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11));
		cancion.start_date = inicio ? inicio : "";
		auto finalizacion = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 12));
		cancion.end_date = finalizacion ? finalizacion : "";

		canciones.push_back(cancion);
	    }
	}

	sqlite3_finalize(stmt);
	return canciones;
    }

    void modificar_cancion(std::string campo, std::string nuevo_valor, std::string path){
	std::string modificacion = "UPDATE rolas SET " + campo +
	    " = ? WHERE path = ?;";
	sqlite3_stmt* stmt = nullptr;

	int preparacion = sqlite3_prepare_v2(BD, modificacion.c_str(), -1, &stmt, NULL);

	if(preparacion != SQLITE_OK){
	    return;
	}
	
	sqlite3_bind_text(stmt, 1, nuevo_valor.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, path.c_str(), -1, SQLITE_TRANSIENT);
	    
	int ejecucion = sqlite3_step(stmt);

	if(ejecucion == SQLITE_DONE){
	    int filas_modificadas = sqlite3_changes(BD);
	    if(filas_modificadas > 0){
		std::cout << "Se actualizó con éxito el campo " << campo << " de rolas.\n";
	    }else{
		std::cout << "Se ejecutó pero no se cambió nada.\n";
	    }
	    
	}else{
	    std::cout << "No se pudo actualizar el campo " << campo << " de rolas.\n";
	}
	
	sqlite3_finalize(stmt);
    }

    void modificar_artista(std::string campo, std::string nuevo_valor, std::string path){
	std::string modificacion = "UPDATE performers SET " + campo +
	    " = ? WHERE id_performer = (SELECT id_performer FROM rolas WHERE path = ?);";
	sqlite3_stmt* stmt = nullptr;

	int preparacion = sqlite3_prepare_v2(BD, modificacion.c_str(), -1, &stmt, NULL);

	if(preparacion != SQLITE_OK){
	    return;
	}
	
	sqlite3_bind_text(stmt, 1, nuevo_valor.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, path.c_str(), -1, SQLITE_TRANSIENT);
	    
	int ejecucion = sqlite3_step(stmt);

	if(ejecucion == SQLITE_DONE){
	    std::cout << "Se actualizó con éxito el campo " << campo << " de performer.\n";
	}else{
	    std::cout << "No se pudo actualizar el campo " << campo << " de performers.\n";
	}
	
	sqlite3_finalize(stmt);
    }

    void modificar_album(std::string campo, std::string nuevo_valor, std::string path){
	std::string modificacion = "UPDATE albums SET " + campo +
	    " = ? WHERE id_album = (SELECT id_album FROM rolas WHERE path = ?);";
	sqlite3_stmt* stmt = nullptr;

	int preparacion = sqlite3_prepare_v2(BD, modificacion.c_str(), -1, &stmt, NULL);

	if(preparacion != SQLITE_OK){
	    return;
	}
	
	sqlite3_bind_text(stmt, 1, nuevo_valor.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, path.c_str(), -1, SQLITE_TRANSIENT);
	    
	int ejecucion = sqlite3_step(stmt);

	if(ejecucion == SQLITE_DONE){
	    std::cout << "Se actualizó con éxito el campo " << campo << " de albums.\n";
	}else{
	    std::cout << "No se pudo actualizar el campo " << campo << " de albums.\n";
	}
	
	sqlite3_finalize(stmt);
    }

    void modificar_persona(std::string campo, std::string nuevo_valor, std::string nombre){
	std::string modificacion = "UPDATE persons SET " + campo +
	    " = ? WHERE stage_name = ?;";
	sqlite3_stmt* stmt = nullptr;

	int preparacion = sqlite3_prepare_v2(BD, modificacion.c_str(), -1, &stmt, NULL);

	if(preparacion != SQLITE_OK){
	    sqlite3_finalize(stmt);
	    return;
	}
	
	sqlite3_bind_text(stmt, 1, nuevo_valor.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, nombre.c_str(), -1, SQLITE_TRANSIENT);
	    
	int ejecucion = sqlite3_step(stmt);

	if(ejecucion == SQLITE_DONE){
	    std::cout << "Se actualizó con éxito el campo " << campo << " de persons.\n";
	}else{
	    std::cout << "No se pudo actualizar el campo " << campo << " de persons.\n";
	}
	
	sqlite3_finalize(stmt);
    }

    void modificar_grupo(std::string campo, std::string nuevo_valor, std::string nombre){
	std::string modificacion = "UPDATE groups SET " + campo +
	    " = ? WHERE name = ?;";
	sqlite3_stmt* stmt = nullptr;

	int preparacion = sqlite3_prepare_v2(BD, modificacion.c_str(), -1, &stmt, NULL);

	if(preparacion != SQLITE_OK){
	    sqlite3_finalize(stmt);
	    return;
	}
	
	sqlite3_bind_text(stmt, 1, nuevo_valor.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, nombre.c_str(), -1, SQLITE_TRANSIENT);
	    
	int ejecucion = sqlite3_step(stmt);

	if(ejecucion == SQLITE_DONE){
	    std::cout << "Se actualizó con éxito el campo " << campo << " de groups.\n";
	}else{
	    std::cout << "No se pudo actualizar el campo " << campo << " de groups.\n";
	}
	
	sqlite3_finalize(stmt);
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

    void agregar_integrante(std::string nombre_artista, std::string nombre_grupo){
	int id_group = grupo_existe(nombre_grupo);
	int id_person = persona_existe(nombre_artista);

	if(id_group == -1){
	    throw ErrorBD("No existe el grupo " + nombre_grupo);
	}

	if(id_person == -1){
	    throw ErrorBD("No existe el artista " + nombre_artista + " o no es persona");
	}

	const char* insert = "INSERT INTO in_group (id_person, id_group) VALUES (?, ?);";
	sqlite3_stmt* stmt = nullptr;
	
	int preparacion = sqlite3_prepare_v2(BD, insert, -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    sqlite3_bind_int(stmt, 1, id_person);
	    sqlite3_bind_int(stmt, 2, id_group);

	    int ejecucion = sqlite3_step(stmt);

	    if(ejecucion == SQLITE_DONE){
		std::cout << "Se agregó al integrante " << nombre_artista << " a " << nombre_grupo << "\n";
	    }else{
	        std::cout << "No se pudo agregar al integrante " << nombre_artista << " a " << nombre_grupo << "\n";
	    }
	}
	
	sqlite3_finalize(stmt);
    }

    std::vector<std::string> obtener_integrantes(std::string nombre_grupo){
	int id_group = grupo_existe(nombre_grupo);

	if(id_group == -1) return {};

	std::vector<std::string> integrantes;
        std::string consulta = "SELECT persons.stage_name "
	    "FROM in_group "
	    "LEFT JOIN persons ON in_group.id_person = persons.id_person "
	    "WHERE in_group.id_group = ?;";
	sqlite3_stmt* stmt = nullptr;

	int preparacion = sqlite3_prepare_v2(BD, consulta.c_str(), -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    sqlite3_bind_int(stmt, 1, id_group);

	    while(sqlite3_step(stmt) == SQLITE_ROW){
		integrantes.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
	    }
	}
	
	sqlite3_finalize(stmt);
	return integrantes;
    }

    void agregar_person(std::string nombre_person){
	if(persona_existe(nombre_person) != -1){
	    return;
	}
	
	const char* insert = "INSERT INTO persons (stage_name) VALUES (?);";
	sqlite3_stmt* stmt = nullptr;
	
	int preparacion = sqlite3_prepare_v2(BD, insert, -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    sqlite3_bind_text(stmt, 1, nombre_person.c_str(), -1, SQLITE_TRANSIENT);

	    int ejecucion = sqlite3_step(stmt);

	    if(ejecucion == SQLITE_DONE){
		std::cout << "Se agregó a la persona " << nombre_person << "\n";
	    }else{
	        std::cout << "No se pudo agregar a la persona " << nombre_person << "\n";
	    }
	}
	
	sqlite3_finalize(stmt);
    }

    void agregar_group(std::string nombre_group){
	if(grupo_existe(nombre_group) != -1){
	    return;
	}
	
	const char* insert = "INSERT INTO groups (name) VALUES (?);";
	sqlite3_stmt* stmt = nullptr;
	
	int preparacion = sqlite3_prepare_v2(BD, insert, -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    sqlite3_bind_text(stmt, 1, nombre_group.c_str(), -1, SQLITE_TRANSIENT);

	    int ejecucion = sqlite3_step(stmt);

	    if(ejecucion == SQLITE_DONE){
		std::cout << "Se agregó al grupo " << nombre_group << "\n";
	    }else{
	        std::cout << "No se pudo agregar al grupo " << nombre_group << "\n";
	    }
	}
	
	sqlite3_finalize(stmt);
    }

    void eliminar_grupo(std::string nombre){
	std::string eliminar_integrantes = "DELETE FROM in_group WHERE id_group IN (SELECT id_group FROM groups WHERE name = ?);";
	sqlite3_stmt* stmt = nullptr;

	int preparacion = sqlite3_prepare_v2(BD, eliminar_integrantes.c_str(), -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    sqlite3_bind_text(stmt, 1, nombre.c_str(), -1, SQLITE_TRANSIENT);
	    sqlite3_step(stmt);
	}
	
	sqlite3_finalize(stmt);

	std::string eliminar_grupo = "DELETE FROM groups WHERE name = ?;";
	sqlite3_stmt* stmt2 = nullptr;

	int preparacion2 = sqlite3_prepare_v2(BD, eliminar_grupo.c_str(), -1, &stmt2, NULL);

	if(preparacion2 == SQLITE_OK){
	    sqlite3_bind_text(stmt2, 1, nombre.c_str(), -1, SQLITE_TRANSIENT);
	    sqlite3_step(stmt2);
	}
	
	sqlite3_finalize(stmt2);
    }

    void eliminar_persona(std::string nombre){
	std::string eliminar = "DELETE FROM persons WHERE stage_name = ?;";
	sqlite3_stmt* stmt = nullptr;

	int preparacion = sqlite3_prepare_v2(BD, eliminar.c_str(), -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    sqlite3_bind_text(stmt, 1, nombre.c_str(), -1, SQLITE_TRANSIENT);
	    sqlite3_step(stmt);
	}
	
	sqlite3_finalize(stmt);
    }

    int artista_existe(std::string nombre_artista){
	const char* busqueda = "SELECT id_performer FROM performers WHERE name = ?;";
	sqlite3_stmt* stmt = nullptr;
	int id = -1;

	int preparacion = sqlite3_prepare_v2(BD, busqueda, -1, &stmt, NULL);

	if(preparacion == SQLITE_OK){
	    sqlite3_bind_text(stmt, 1, nombre_artista.c_str(), -1, SQLITE_TRANSIENT);

	    int ejecucion = sqlite3_step(stmt);

	    if(ejecucion == SQLITE_ROW){
		id = sqlite3_column_int(stmt, 0);
	    }
	}

	sqlite3_finalize(stmt);
	return id;
    }
};
