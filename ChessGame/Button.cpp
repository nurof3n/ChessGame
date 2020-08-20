#include "Button.h"

Button::Button( SpriteObj spriteObj )
    : SpriteObj( spriteObj )
{
    _hitbox = getSprite().getGlobalBounds();
}

Button::Button( const std::string& filename, const sf::Vector2f& pos, const sf::Vector2f& scale )
    : SpriteObj( filename, pos, scale )
{
    _hitbox = getSprite().getGlobalBounds();
}

Button& Button::operator=( const Button& other )
{
    if( this != &other ) {
        _pos     = other._pos;
        _texture = other._texture;
        _sprite  = other._sprite;
        _sprite.setTexture( _texture );
        _hitbox = other._hitbox;
    }
    return *this;
}

bool Button::isPressed( sf::RenderWindow& window )
{
    if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && mouseIsOver( window ) )
        return true;
    return false;
}

bool Button::mouseIsOver( sf::RenderWindow& window )
{
    return _hitbox.contains( sf::Vector2f( sf::Mouse::getPosition( window ) ) );
}
