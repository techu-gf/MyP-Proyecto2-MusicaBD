#include <filesystem>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include "InfoCancion.hpp"

namespace fs = std::filesystem;

class Lector{

public:

    static InfoCancion obtener_info(const fs::path& ruta_archivo){
	InfoCancion datos;
	
	datos.path_rola = ruta_archivo.string();
	datos.path_album = ruta_archivo.parent_path().string();
	
	TagLib::FileRef f(ruta_archivo.string().c_str());

	if(f.isNull() || !f.tag()){
	    throw std::runtime_error("No se puede acceder al archivo " + ruta_archivo.string());
	}

	TagLib::Tag *tag = f.tag();

        datos.title_rola = ruta_archivo.filename().string();
	std::string nombre_rola = tag -> title().to8Bit(true);

	if(!nombre_rola.empty()){
	    datos.title_rola = nombre_rola;
	}
	
	datos.name_performer = "UNKNOWN";
	std::string performer = tag -> artist().to8Bit(true);

	if(!performer.empty()){
	    datos.name_performer = performer;
	}
	
	datos.genre_rola = "UNKNOWN";
	std::string genre = tag -> genre().to8Bit(true);

	if(!genre.empty()){
	    datos.genre_rola = genre;
	}
	
	datos.year = 2026;
	int year = tag -> year();

	if(year){
	    datos.year = year;
	}
	
	datos.track_rola = 0;
	int track = tag -> track();

	if(track){
	    datos.track_rola = track;
	}
	
	datos.name_album = ruta_archivo.parent_path().filename().string();
	std::string album = tag -> album().to8Bit(true);

	if(!album.empty()){
	    datos.name_album = album;
	}

	return datos;
    }
};
