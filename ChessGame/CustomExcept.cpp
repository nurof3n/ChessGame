#include "CustomExcept.h"

CustomExcept::CustomExcept( const char* s ) noexcept {
	buffer = s;
}

CustomExcept::CustomExcept( const std::string& s ) noexcept {
	buffer = s;
}

const char* CustomExcept::GetType() const noexcept {
	return "Custom Exception:";
}

const char* CustomExcept::what() const noexcept {
	std::ostringstream output;
	output << "[File]: " << __FILE__ << "\n[Line]: " << __LINE__ << "\n[Exception]: " << buffer;
	buffer = output.str();
	return buffer.c_str();
}
