#include <iostream>
#include <string>
#include <sqlite3.h>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstdlib>

class BaseDatos{

private:
    std::string ruta_bd;
    sqlite3* BD;

    void crearBaseDeDatos(){
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
		crearBaseDeDatos();
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

    void consultar(){
	
    }

    void modificarCancion(){
	
    }

    void modificarArtista(){
	
    }

    void modificarAlbum(){
	
    }

    void agregarCancion(){
	
    }

    void agregarArtista(){
	
    }

    void agregarAlbum(){
	
    }

    void agregarIntegrante(){
	
    }
};
