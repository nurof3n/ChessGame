#pragma once
#include <exception>
#include <string>
#include <sstream>

class CustomExcept : public std::exception {
public:
	enum class Except {
		OUT_OF_BOUNDS
	};
public:
	CustomExcept( const char* s ) noexcept {
		buffer = s;
	}
	virtual const char* GetType() const noexcept;
	const char* what() const noexcept override;
private:
	std::string buffer;
};

