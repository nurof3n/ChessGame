#pragma once
#include <exception>
#include <string>
#include <sstream>

#define EXCEPT(s) (CustomExcept(__FILE__, __LINE__, s))

class CustomExcept : public std::exception {
public:
	CustomExcept() = delete;
	CustomExcept( const std::string& file, int line, const std::string& s ) noexcept;
	virtual const char* getType() const noexcept;
	const char* what() const noexcept override;
private:
	mutable std::string buffer;
	std::string _file;
	int _line;
};

