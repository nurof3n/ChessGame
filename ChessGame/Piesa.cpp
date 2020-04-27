#include "Piesa.h"

Piesa::Piesa( const std::string& filename, sf::Vector2i coords, const Piese& type, const Color& color )
	:
	SpriteObj( filename, Piesa::GetPosFromCoords( coords ), sf::Vector2f( 2.0f, 2.0f ) ),
	_coords( coords ),
	_type( type ),
	_color( color ) {}

sf::Vector2f Piesa::GetPosFromCoords( const sf::Vector2i& coords ) noexcept {
	return 64.0f * sf::Vector2f( coords.x - 1, 8 - coords.y );
}

sf::Vector2i Piesa::GetCoordsFromPos( const sf::Vector2f& pos ) noexcept {
	return sf::Vector2i( int( pos.x / 64.0f ) + 1.0f, 8.0f - int( pos.y / 64.0f ) );
}

Piesa::Color Piesa::OtherColor( const Color& color ) noexcept {
	return (color == Color::ALB ? Color::NEGRU : Color::ALB);
}

Piesa::Piese Piesa::GetType() noexcept {
	return _type;
}

Piesa::Color Piesa::GetColor() noexcept {
	return _color;
}

sf::Vector2i Piesa::GetCoords() noexcept {
	return _coords;
}

void Piesa::MoveOnTable( const sf::Vector2i& coords ) noexcept {
	MoveTo( GetPosFromCoords( coords ) );
	_coords = coords;
}


