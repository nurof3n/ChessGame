#pragma once
#include "SpriteObj.h"


class Button : public SpriteObj {
public:
	Button() = default;
	Button( SpriteObj spriteObj );
	Button( const std::string& filename, const sf::Vector2f& pos = sf::Vector2f( 0.0f, 0.0f ), const sf::Vector2f& scale = sf::Vector2f( 1.0f, 1.0f ) );
	Button& operator=( const Button& other );
	bool isPressed( sf::RenderWindow& window );
	bool mouseIsOver( sf::RenderWindow& window );
private:
	sf::FloatRect _hitbox;
};

