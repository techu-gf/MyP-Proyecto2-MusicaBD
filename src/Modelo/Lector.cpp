#include <filesystem>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <InfoCancion.cpp>

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

        datos.title_rola = tag -> title().to8Bit(true);
	datos.name_performer = tag -> artist().to8Bit(true);
	datos.genre_rola = tag -> genre().to8Bit(true);
	datos.year = tag -> year();
	datos.track_rola = tag -> track();
	
	datos.name_album = ruta_archivo.parent_path().filename().string();
	std::string album = tag -> album().to8Bit(true);

	if(!album.empty()){
	    datos.name_album = album;
	}

	return datos;
    }
};
