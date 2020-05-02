#include "SpriteObj.h"

SpriteObj::SpriteObj( SpriteObj&& other ) noexcept
	:
	_pos( std::move( other._pos ) ),
	_texture( std::move( other._texture ) ),
	_sprite( std::move( other._sprite ) ) {}

SpriteObj::SpriteObj( const std::string& filename, const sf::Vector2f& pos, const sf::Vector2f& scale ) {
	_pos = pos;
	if( !_texture.loadFromFile( filename ) )
		throw("Cannot load file: " + filename);
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

void SpriteObj::MoveTo( const sf::Vector2f& pos ) noexcept {
	_sprite.move( pos - _pos );
	_pos = pos;
}
