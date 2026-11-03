#include <iostream>
#include "Modelo/Minero.cpp"

int main(int argc, char* argv[]){

    if (argc < 2){
	std::cout << "Debe especificar la carpeta con música.\n";
	return 1;
    }

    BaseDatos base_de_datos;

    std::string ruta_directorio = argv[1];

    try{
	Minero minero(ruta_directorio, base_de_datos);

	minero.minar();
    }catch(const std::exception& e){
	std::cerr << "Hubo un error al minar: " << e.what() << "\n";
	return 1;
    }
    return 0;
}
