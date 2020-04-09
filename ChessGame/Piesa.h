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
	Piesa( const std::string&, sf::Vector2u, const Piese&, const Color& );
	bool ProcessMove( sf::Vector2u, sf::Vector2u );
	
private:
	Piese _type;
	Color _color;
};

