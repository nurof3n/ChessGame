#include "Piesa.h"

Piesa::Piesa( sf::Vector2u coords, const std::string& filename ) {
	_pos = 64.0f * sf::Vector2f( coords.x - 1, 8 - coords.y );
	_texture.loadFromFile( filename );
	_sprite.setTexture( _texture );
	_sprite.setScale( sf::Vector2f( 2.0f, 2.0f ) );
	_sprite.move( _pos );
}

sf::Vector2f Piesa::GetPos() noexcept {
	return _pos;
}

sf::Texture Piesa::GetTexture() noexcept {
	return _texture;
}

sf::Sprite Piesa::GetSprite() noexcept {
	return _sprite;
}