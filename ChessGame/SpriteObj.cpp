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

void SpriteObj::draw( Graphics& gfx ) {
	gfx.draw( getSprite() );
}

sf::Vector2f SpriteObj::getPos() const noexcept {
	return _pos;
}

void SpriteObj::setPos( const sf::Vector2f& pos ) {
	_pos = pos;
}

sf::Texture SpriteObj::getTexture() const noexcept {
	return _texture;
}

void SpriteObj::setTexture( const sf::Texture& texture ) {
	_texture = texture;
}

sf::Sprite SpriteObj::getSprite() const noexcept {
	return _sprite;
}

void SpriteObj::moveTo( const sf::Vector2f& pos ) noexcept {
	_sprite.move( pos - _pos );
	_pos = pos;
}
