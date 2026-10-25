#include <stdexcept>
#include <string>

class ErrorMinado : public std::runtime_error{

public:
    explicit ErrorMinado(const std::string& mensaje)
	: std::runtime_error(mensaje){}
};
