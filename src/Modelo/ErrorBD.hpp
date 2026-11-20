#ifndef ERROR_BD_HPP
#define ERROR_BD_HPP
#include <stdexcept>
#include <string>

/**
 * @brief La clase ErrorBD crea errores específicos localizados en la base de datos.
 */
class ErrorBD : public std::runtime_error{
public:
    explicit ErrorBD(const std::string& mensaje)
	: std::runtime_error(mensaje){}
};

#endif
