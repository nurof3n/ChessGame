#include "Piesa.h"

Piesa::Piesa( const std::string& filename, sf::Vector2i coords, const Piese& type, const Color& color )
	:
	SpriteObj( filename, Piesa::getPosFromCoords( coords ), sf::Vector2f( 2.0f, 2.0f ) ),
	_coords( coords ),
	_type( type ),
	_color( color ) {}

sf::Vector2f Piesa::getPosFromCoords( const sf::Vector2i& coords ) noexcept {
	return 64.0f * sf::Vector2f( coords.x - 1, 8 - coords.y );
}

sf::Vector2i Piesa::getCoordsFromPos( const sf::Vector2f& pos ) noexcept {
	return sf::Vector2i( int( pos.x / 64.0f ) + 1.0f, 8.0f - int( pos.y / 64.0f ) );
}

Piesa::Color Piesa::otherColor( const Color& color ) noexcept {
	return (color == Color::ALB ? Color::NEGRU : Color::ALB);
}

Piesa::Piese Piesa::getType() noexcept {
	return _type;
}

Piesa::Color Piesa::getColor() noexcept {
	return _color;
}

sf::Vector2i Piesa::getCoords() noexcept {
	return _coords;
}

void Piesa::moveOnTable( const sf::Vector2i& coords ) noexcept {
	moveTo( getPosFromCoords( coords ) );
	_coords = coords;
}


