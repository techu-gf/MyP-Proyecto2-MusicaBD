#include <iostream>
#include <filesystem>
#include <stack>
#include "Lector.cpp"
#include "ErrorMinado.cpp"

namespace fs = std::filesystem;

/**
 * @brief La clase Minero se encarga de minar el directorio dado, obteniendo
 * la información de cada archivo mp3 y guardándolo en la base de datos. 
 */
class Minero{

private:
  fs::path ruta_directorio, ruta_bd;

  /**
   * @brief Determina si ya existe la base de datos. En caso de no existir,
   * crea la base de datos. 
   */
  void encuentra_bd(){
    
  }

  /**
   * @brief Obtiene la información del archivo.
   * @param ruta_archivo Ruta del archivo del que se obtendrá la información
   */
  void obtener_info_cancion(const fs::path& ruta_archivo){
      std::string extension = ruta_archivo.extension().string();

      try{
	  if(extension == ".mp3" || extension == ".MP3"){
	      InfoCancion info = Lector::obtener_info(ruta_archivo);

	      std::cout << "Artista: " << info.name_performer << "\n";
	      std::cout << "Nombre: " << info.title_rola << "\n";
	      std::cout << "Álbum: " << info.name_album << "\n";
	      std::cout << "Año: " << info.year << "\n";
	      std::cout << "No. Cancion: " << info.track_rola << "\n";
	      std::cout << "Género: " << info.genre_rola << "\n";

	      std::cout << "Archivo analizado con éxito: "<< ruta_archivo.string() + "\n";
	  }
      }catch(const ErrorMinado& e){
	  std::cerr << e.what() << "\n";
      }

  }

  /**
   * @brief Determina si la canción ya existe en la base de datos. 
   */
  void ya_existe(){
    
  }

  /**
   * @brief Agrega la canción a la base de datos. 
   */
  void agregar_cancion(){
    
  }

  /**
   * @brief Agrega el artista a la base de datos.
   */
  void agregar_artista(){
    
  }

  /**
   * @brief Agrega el album a la base de datos.
   */
  void agregar_album(){
    
  }

public:
  /**
   * @brief Constructor del minero.
   * @param _ruta_directorio Ruta del directorio que se va a minar. 
   */
  Minero(std::string& _ruta_directorio)
    : ruta_directorio(_ruta_directorio){}

  /**
   * @brief Comienza a minar.
   */
  void minar(){
      //Con una cola o pila, podría ser como se hizo en el proyecto del laberinto.
      //Se crea una pila
      //se mete el directorio raíz
      //Mientras la pila no esté vacía:
      //   sacar el último elemento
      //   recorrer el directorio que acabamos de sacar y hacer lo siguiente:
      //      si el elemento en el directorio es un archivo, lo analiza
      //      si el elemento es un subdirectorio, agregarlo a la pila

      //Como que recorre un directorio y cuando ya está vacío, sigue con el
      //siguiente directorio que tenga la pila, y así hasta que esté vacía la pila
      
      if(!fs::exists(ruta_directorio) || !fs::is_directory(ruta_directorio)){
	  std::cout << "La ruta no existe o no es un directorio\n";
	  return;
      }

      std::stack<fs::path> directorios;
      directorios.push(ruta_directorio);

      while(!directorios.empty()){
	  fs::path actual = directorios.top();
	  directorios.pop();
	  
	  try{
	      for(const auto& entry : fs::directory_iterator(actual)){
		  if(fs::is_regular_file(entry.status())){
		      std::cout << "Analizando: " << entry.path().string() + "\n";
		      obtener_info_cancion(entry.path());
		  }else if(fs::is_directory(entry.status())){
		      directorios.push(entry.path());
		  }
	      }
	  }catch(const fs::filesystem_error& e){
	      std::cerr << "No se pudo acceder a la ruta " << actual << "\n";
	  }
      }

      std::cout << "Minado terminado.\n";
  }
  
};
