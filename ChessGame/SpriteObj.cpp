#include "SpriteObj.h"

SpriteObj::SpriteObj( const std::string& filename, const sf::Vector2f& coords, const sf::Vector2f& scale ) {
	_pos = coords;
	_texture.loadFromFile( filename );
	_sprite.setTexture( _texture );
	_sprite.setScale( scale );
	_sprite.move( _pos );
}

void SpriteObj::Draw( Graphics& gfx ) {
	gfx.DrawSprite( GetSprite() );
}

sf::Vector2f SpriteObj::GetPos() const noexcept {
	return _pos;
}

sf::Texture SpriteObj::GetTexture() const noexcept {
	return _texture;
}

sf::Sprite SpriteObj::GetSprite() const noexcept {
	return _sprite;
}