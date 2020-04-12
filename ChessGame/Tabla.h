#pragma once
#include "CustomExcept.h"
#include "Piesa.h"
#include "Graphics.h"
#include "AndyMath.h"
#include <vector>

constexpr auto A = 1;
constexpr auto B = 2;
constexpr auto C = 3;
constexpr auto D = 4;
constexpr auto E = 5;
constexpr auto F = 6;
constexpr auto G = 7;
constexpr auto H = 8;

class Tabla : public SpriteObj {
public:
	Tabla();
	~Tabla() noexcept;

	void Setup() noexcept;
	void Draw( Graphics& );
	Piesa* GetPiesa( const sf::Vector2i& ) noexcept;
	sf::Vector2i GetPosRege( const Piesa::Color& ) noexcept;
	void SetPiesa( const sf::Vector2i&, Piesa* ) noexcept;
	bool IsInBounds( const sf::Vector2i& ) const noexcept;
	int CheckMove( const sf::Vector2i&, const sf::Vector2i&, const bool& = false ) const;
	void Move( const sf::Vector2i&, const sf::Vector2i& ) noexcept;
	bool Scan( const sf::Vector2i&, const sf::Vector2i&, const sf::Vector2i& ) const noexcept;
	bool IsCheck( const Piesa::Color&, const sf::Vector2i& ) const noexcept;
	bool IsCheckMate( const Piesa::Color&, const sf::Vector2i& ) const noexcept;
private:
	Piesa* _tabla[9][9];
	sf::Vector2i posRege[2];
};

