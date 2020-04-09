#include "Piesa.h"

Piesa::Piesa( const std::string& filename, sf::Vector2u coords, const Piese& type, const Color& color )
	:
	SpriteObj( filename, 64.0f * sf::Vector2f( coords.y - 1.0f, 8.0f - coords.x ), sf::Vector2f( 2.0f, 2.0f ) ),
	_type( type ),
	_color( color ) {}