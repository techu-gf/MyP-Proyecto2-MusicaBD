#include <iostream>
#include <filesystem>
#include <stack>
#include "Lector.cpp"
#include "BaseDatos.cpp"

namespace fs = std::filesystem;

/**
 * @brief La clase Minero se encarga de minar el directorio dado, obteniendo
 * la información de cada archivo mp3 y guardándolo en la base de datos. 
 */
class Minero{

private:
    fs::path ruta_directorio;
    BaseDatos& BD;

  /**
   * @brief Obtiene la información del archivo.
   * @param ruta_archivo Ruta del archivo del que se obtendrá la información
   */
  InfoCancion guardar_info_cancion(const fs::path& ruta_archivo){
      std::string extension = ruta_archivo.extension().string();

      if(extension == ".mp3" || extension == ".MP3"){
	  InfoCancion info = Lector::obtener_info(ruta_archivo);
	  bool agregada = BD.agregar_cancion(info);

	  if(agregada){
	      return info;
	  }
      }

      return InfoCancion{};
  }

public:
  /**
   * @brief Constructor del minero.
   * @param _ruta_directorio Ruta del directorio que se va a minar. 
   */
    Minero(std::string& _ruta_directorio, BaseDatos& _BD)
	: ruta_directorio(_ruta_directorio), BD(_BD){}

  /**
   * @brief Comienza a minar.
   */
    std::vector<InfoCancion> minar(){
	if(!fs::exists(ruta_directorio) || !fs::is_directory(ruta_directorio)){
	    std::cout << "La ruta no existe o no es un directorio\n";
	}

	std::vector<InfoCancion> canciones;
	std::stack<fs::path> directorios;
	directorios.push(ruta_directorio);

	while(!directorios.empty()){
	    fs::path actual = directorios.top();
	    directorios.pop();
	  
	    try{
		for(const auto& entry : fs::directory_iterator(actual)){
		    if(fs::is_regular_file(entry.status())){
		        InfoCancion cancion = guardar_info_cancion(entry.path());

			if(!cancion.title_rola.empty()){
			    canciones.push_back(cancion);
			}
		    }else if(fs::is_directory(entry.status())){
			directorios.push(entry.path());
		    }
		}
	    }catch(const fs::filesystem_error& e){
		std::cerr << "No se pudo acceder a la ruta " << actual << "\n";
	    }
	}

	return canciones;
    }
  
};
