#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"

class SpriteObj {
public:
	SpriteObj() = delete;
	SpriteObj( const std::string&, const sf::Vector2f & = sf::Vector2f( 0.0f, 0.0f ), const sf::Vector2f & = sf::Vector2f( 1.0f, 1.0f ) );
	void Draw( Graphics& );
	sf::Vector2f GetPos() const noexcept;
	sf::Texture GetTexture() const noexcept;
	sf::Sprite GetSprite() const noexcept;
private:
	sf::Vector2f _pos;
	sf::Texture _texture;
	sf::Sprite _sprite;
};

