#include "CustomExcept.h"

const char* CustomExcept::GetType() const noexcept {
	return "Custom Exception:";
}

const char* CustomExcept::what() const noexcept {
	return buffer.c_str();
}
