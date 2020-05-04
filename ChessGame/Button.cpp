#include "Button.h"

Button::Button( SpriteObj spriteObj )
	:
	SpriteObj( spriteObj ) {
	_hitbox = GetSprite().getGlobalBounds();
}

Button::Button( const std::string& filename, const sf::Vector2f& pos, const sf::Vector2f& scale )
	:
	SpriteObj( filename, pos, scale ) {
	_hitbox = GetSprite().getGlobalBounds();
}

bool Button::IsPressed( sf::RenderWindow& window ) {
	if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && mouseIsOver( window ) )
		return true;
	return false;
}

bool Button::mouseIsOver( sf::RenderWindow& window ) {
	return _hitbox.contains( sf::Vector2f( sf::Mouse::getPosition( window ) ) );
}
