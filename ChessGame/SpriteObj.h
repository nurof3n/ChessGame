#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"

class SpriteObj {
public:
	SpriteObj() = delete;
	SpriteObj( const std::string& filename, const sf::Vector2f& pos = sf::Vector2f( 0.0f, 0.0f ), const sf::Vector2f& scale = sf::Vector2f( 1.0f, 1.0f ) );
	void Draw( Graphics& );
	sf::Vector2f GetPos() const noexcept;
	sf::Texture GetTexture() const noexcept;
	sf::Sprite GetSprite() const noexcept;
	void MoveTo( const sf::Vector2f& pos ) noexcept;
private:
	sf::Vector2f _pos;
	sf::Texture _texture;
	sf::Sprite _sprite;
};

