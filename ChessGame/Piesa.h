#pragma once
#include "SpriteObj.h"

class Piesa : public SpriteObj {
public:
	enum class Piese {
		LIBER,
		PION,
		NEBUN,
		CAL,
		TURN,
		REGINA,
		REGE
	};
	enum class Color {
		ALB,
		NEGRU
	};
public:
	Piesa() = delete;
	Piesa( const std::string&, sf::Vector2i, const Piese&, const Color& );
	static sf::Vector2f GetPosFromCoords( const sf::Vector2i& ) noexcept;
	static sf::Vector2i GetCoordsFromPos( const sf::Vector2f& ) noexcept;
	static Color OtherColor( const Color& ) noexcept;
	Piese GetType() noexcept;
	Color GetColor() noexcept;
	sf::Vector2i GetCoords() noexcept;
	void MoveOnTable( const sf::Vector2i& ) noexcept;
private:
	Piese _type;
	Color _color;
	sf::Vector2i _coords;
};

