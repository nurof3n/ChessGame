#pragma once
#include <exception>
#include <string>
#include <sstream>

class CustomExcept : public std::exception {
public:
	CustomExcept() = delete;
	CustomExcept( const char* ) noexcept;
	CustomExcept( const std::string& ) noexcept;
	virtual const char* GetType() const noexcept;
	const char* what() const noexcept override;
private:
	mutable std::string buffer;
};

