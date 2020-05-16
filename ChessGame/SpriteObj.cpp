#include "SpriteObj.h"

SpriteObj::SpriteObj( const std::string& filename, const sf::Vector2f& pos, const sf::Vector2f& scale ) {
	_pos = pos;
	if( !_texture.loadFromFile( filename ) )
		throw EXCEPT( "Cannot load file: " + filename );
	_sprite.setTexture( _texture );
	_sprite.setScale( scale );
	_sprite.move( _pos );
}

SpriteObj& SpriteObj::operator=( const SpriteObj& other ) {
	if( this != &other ) {
		_pos = other._pos;
		_texture = other._texture;
		_sprite = other._sprite;
		_sprite.setTexture( _texture );
	}
	return *this;
}

void SpriteObj::Draw( Graphics& gfx ) {
	gfx.Draw( GetSprite() );
}

sf::Vector2f SpriteObj::GetPos() const noexcept {
	return _pos;
}

void SpriteObj::SetPos( const sf::Vector2f& pos ) {
	_pos = pos;
}

sf::Texture SpriteObj::GetTexture() const noexcept {
	return _texture;
}

void SpriteObj::SetTexture( const sf::Texture& texture ) {
	_texture = texture;
}

sf::Sprite SpriteObj::GetSprite() const noexcept {
	return _sprite;
}

void SpriteObj::MoveTo( const sf::Vector2f& pos ) noexcept {
	_sprite.move( pos - _pos );
	_pos = pos;
}
