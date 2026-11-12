#ifndef ERROR_BD_HPP
#define ERROR_BD_HPP
#include <stdexcept>
#include <string>

class ErrorBD : public std::runtime_error{
public:
    explicit ErrorBD(const std::string& mensaje)
	: std::runtime_error(mensaje){}
};

#endif
