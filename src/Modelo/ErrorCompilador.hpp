#ifndef ERROR_COMPILADOR_HPP
#define ERROR_COMPILADOR_HPP
#include <stdexcept>
#include <string>

class ErrorCompilador : public std::runtime_error{
public:
    explicit ErrorCompilador(const std::string& mensaje)
	: std::runtime_error(mensaje){}
};

#endif
