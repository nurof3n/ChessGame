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

bool Button::IsPressed() {
	if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && _hitbox.contains( sf::Vector2f( sf::Mouse::getPosition() ) ) )
		return true;
	return false;
}
