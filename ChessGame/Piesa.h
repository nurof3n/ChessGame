#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

class Piesa {
public:
	Piesa() = delete;
	Piesa( sf::Vector2u, const std::string& );
	virtual bool ProcessMove( sf::Vector2u, sf::Vector2u );
	sf::Vector2f GetPos() noexcept;
	sf::Texture GetTexture() noexcept;
	sf::Sprite GetSprite() noexcept;
private:
	sf::Vector2f _pos;
	sf::Texture _texture;
	sf::Sprite _sprite;
	Tabla& _tabla = Game::GetTabla();
};

