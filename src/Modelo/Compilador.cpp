#include <string>
#include <vector>
#include <sstream>
#include "ErrorCompilador.hpp"

/**
 * @brief La clase Compilador se encarga de analizar una cadena de texto
 * y, en caso de que esté escrita "correctamente", la traducirá a una
 * consulta sql. 
 */
class Compilador{

private:

    inline static const std::string ARTISTA = "artist";
    inline static const std::string ALBUM = "album";
    inline static const std::string CANCION = "song";
    inline static const std::string ANIO = "year";
    inline static const std::string GENERO = "genre";

    /**
     * @brief Estructura que guarda la info de cada token.
     */
    struct Token{
	std::string campo;
	std::string tipo_contencion;
	std::string busca;
	bool negacion;
	char conector;
    };

    std::vector<Token> tokens;

    /**
     * @brief Método que separa cada filtro que se busca de acuerdo a un delimitador.
     * Se buscó que funcione parecidamente al split de Java.
     * @param cadena Cadena de texto que se va a separar.
     * @param delimitador Caracter que se toma como separador de la cadena.
     * @return std::vector<std::string> Vector con las subcadenas obtenidas. 
     */
    std::vector<std::string> split(std::string& cadena, char delimitador){
	std::vector<std::string> resultado;
	std::stringstream ss(cadena);
	std::string subcadena;
	bool entre_comillas = false;

	for(char c : cadena){
	    if(c == '"'){
		entre_comillas = !entre_comillas;
		subcadena += c;
	    }else if(c == delimitador && !entre_comillas){
		if(!subcadena.empty()){
		    resultado.push_back(subcadena);
		    subcadena = "";
		}
	    }else{
		subcadena += c;
	    }
	}

	if(!subcadena.empty()){
	    resultado.push_back(subcadena);
	}
	
	return resultado;
    }

    /**
     * @brief Método que determina si una cadena es un número entero positivo.
     * @param cadena Cadena de texto que se va a analizar.
     * @return bool Regresa true en cado de que sea un número entero positivo,
     * regresa false en otro caso. 
     */
    bool es_numero(std::string& cadena){
        if(cadena.empty()){
	    return false;
	}

	for(char c : cadena){
	    if(c < '0' || c > '9'){
		return false;
	    }
	}

	return true;
    }

    /**
     * @brief Método que obtiene la columna de la base de datos que representa
     * una cadena.
     * @param campoDeseado Cadena que se va a analizar.
     * @return std::string Regresa la equivalencia en la base de datos. En caso
     * de que no se encuentre equivalencia, regresa una cadena vacía. 
     */
    std::string obtener_columna(std::string& campoDeseado){
	if(campoDeseado == ARTISTA){
	    return "performers.name";
        }else if(campoDeseado == ALBUM){
	    return "albums.name";
	}else if(campoDeseado == CANCION){
	    return "rolas.title";
	}else if(campoDeseado == ANIO){
	    return "rolas.year";
	}else if(campoDeseado == GENERO){
	    return "rolas.genre";
	}

	return "";
    }

    /**
     * @brief Método que dará formato a una cadena para que, en caso de tener ',
     * esta no afecte a la consulta a la base de datos. 
     * @param cadena Cadena que se va a formatear. 
     * @return std::string Regresa la cadena ya formateada. 
     */
    std::string encuentra_comilla(std::string& cadena){
	std::string cadena_segura;

	for(char c : cadena){
	    if(c == '\''){
		cadena_segura += "''";
	    }else{
		cadena_segura += c;
	    }
	}

	return cadena_segura;
    }

public:

    /**
     * @brief Método que separa la consulta original para obtener los tokens.
     * @param consulta Cadena con la consulta hecha por el cliente.
     */
    void lexer(std::string consulta){
	tokens.clear();

	std::vector<std::string> busquedas = split(consulta, ' ');

	for(std::string& busqueda : busquedas){
	    if(busqueda.empty()){
	        continue;
	    }

	    if(busqueda == "&" || busqueda == "|"){
		if(!tokens.empty()){
		    tokens.back().conector = busqueda[0];
		}
		continue;
	    }

	    Token token;
	    token.negacion = false;
	    token.conector = '\0';

	    size_t igual = busqueda.find('=');
	    size_t contiene = busqueda.find('~');
	    size_t posicion_campo = (igual != std::string::npos) ? igual : contiene;

	    if(posicion_campo == std::string::npos){
		continue;
	    }
	    
	    token.campo = busqueda.substr(0, posicion_campo);
	    token.tipo_contencion = busqueda.substr(posicion_campo, 1);

	    std::string filtro = busqueda.substr(posicion_campo + 1);
	    int posicion = 0;

	    if(!filtro.empty() && filtro[posicion] == '!'){
		token.negacion = true;
		posicion++;
	    }

	    size_t abre_comilla = filtro.find('"', posicion);
	    size_t cierra_comilla = filtro.rfind('"');

	    if(abre_comilla != std::string::npos && cierra_comilla != std::string::npos && abre_comilla < cierra_comilla){
		token.busca = filtro.substr(abre_comilla + 1, cierra_comilla - abre_comilla - 1);
	    }

	    tokens.push_back(token);
	}
    }

    /**
     * @brief Método que analiza cada token, verificando que son válidos.
     */
    void parser(){
	if(tokens.empty()){
	    throw ErrorCompilador("No se pudo procesar la consulta.");
	}

	for(Token& token : tokens){
	    if(token.campo.empty()){
		throw ErrorCompilador("Debe indicar el campo que busca.");
	    }
	    
	    if(token.campo != ARTISTA && token.campo != ALBUM && token.campo != CANCION && token.campo != ANIO && token.campo != GENERO){
		throw ErrorCompilador("No existe el campo " + token.campo);
	    }

	    if(token.tipo_contencion.empty()){
		throw ErrorCompilador("Debe indicar el tipo de contención. Campo: " + token.campo);
	    }

	    if(token.busca.empty()){
		throw ErrorCompilador("Debe indicar lo que busca. Campo: " + token.campo);
	    }

	    if(token.campo == ANIO){
		if(!es_numero(token.busca) || token.busca.size() < 1 || token.busca.size() > 4){
		    throw ErrorCompilador("Año no válido."); 
		}
	    }

	    if(token.conector != '\0' && &token == &tokens.back()){
		throw ErrorCompilador("Debe agregar otra búsqueda después de agregar un & o |.");
	    }

	    if(token.conector == '\0' && &token != &tokens.back()){
		throw ErrorCompilador("Debe agregar & o | para agregar otra condicion.");
	    }

	    if(token.conector != '\0'){
		if(token.conector != '&' && token.conector != '|'){
		    throw ErrorCompilador("Conector no válido.");
		}
	    }
	}
    }

    /**
     * @brief Método que construye la consulta SQL de acuerdo con los tokens existentes. 
     * @return std::string Regresa una cadena con la consulta construida.
     */
    std::string a_SQL(){
	std::string consulta = "SELECT rolas.title, performers.name, albums.name, rolas.track, rolas.year, rolas.genre, rolas.path, performers.id_type, persons.real_name, persons.birth_date, persons.death_date, groups.start_date, groups.end_date "
	    "FROM rolas "
	    "LEFT JOIN performers ON rolas.id_performer = performers.id_performer "
	    "LEFT JOIN albums ON rolas.id_album = albums.id_album "
	    "LEFT JOIN persons ON performers.name = persons.stage_name "
	    "LEFT JOIN groups ON performers.name = groups.name "
	    "WHERE ";

	for(Token& token : tokens){
	    std::string columna = obtener_columna(token.campo);
	    std::string filtro = encuentra_comilla(token.busca);

	    consulta += columna;

	    if(token.tipo_contencion == "="){
		if(token.negacion){
		    consulta += " != '";
		}else{
		    consulta += " = '";
		}

		consulta += filtro + "'";
	    }else if(token.tipo_contencion == "~"){
		if(token.negacion){
		    consulta += " NOT LIKE '%";
		}else{
		    consulta += " LIKE '%";
		}

		consulta += filtro + "%'";
	    }

	    if(token.conector == '&'){
		consulta += " AND ";
	    }else if(token.conector == '|'){
		consulta += " OR ";
	    }
	}

	consulta += ";";

	return consulta;
    }
};
