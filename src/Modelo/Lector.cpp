#include <filesystem>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>
#include <fstream>
#include <cstdlib>
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

	datos.path_portada = "src/sources";

	TagLib::MPEG::File mpegFile(ruta_archivo.string().c_str());

	if(mpegFile.isOpen() && mpegFile.ID3v2Tag()){
	    auto marco = mpegFile.ID3v2Tag() -> frameList("APIC");

	    if(!marco.isEmpty()){
		if(auto *imagen = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame*>(marco.front())){
		    auto img = imagen -> picture();

		    if(!img.isEmpty()){
			if(const char* home = std::getenv("HOME")){
			    fs::path dir = std::string(home) + "/.local/share/musiquita/albums/";
			    fs::create_directories(dir);

			    std::string album_nombre = datos.name_album;

			    for(char &c : album_nombre){
				if(c == ' ' || c == '/' || c == '\\'){
				    c = '_';
				}
			    }

			    fs::path dir_portada = dir.string() + album_nombre + ".jpg";

			    if(!fs::exists(dir_portada)){
				std::ofstream(dir_portada, std::ios::binary).write(img.data(), img.size());
			    }

			    datos.path_portada = dir_portada.string();
			}
		    }
		}
	    }
	}

	datos.type_performer = 2;

	return datos;
    }
};
