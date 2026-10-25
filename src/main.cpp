#include <iostream>
#include "Modelo/Minero.cpp"

int main(int argc, char* argv[]){

    if (argc < 1){
	std::cout << "Debe especificar la carpeta con música.\n";
	return 1;
    }

    std::string ruta_directorio = argv[1];

    try{
	Minero minero(ruta_directorio);

	minero.minar();
    }catch(const std::exception& e){
	std::cerr << "Hubo un error al minar: " << e.what() << "\n";
	return 1;
    }
    return 0;
}
