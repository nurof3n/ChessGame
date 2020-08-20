#pragma once
#include "SpriteObj.h"

class Piesa : public SpriteObj
{
public:
    enum class Piese
    {
        LIBER,
        PION,
        NEBUN,
        CAL,
        TURN,
        REGINA,
        REGE
    };
    enum class Color
    {
        ALB,
        NEGRU
    };

public:
    Piesa() = delete;
    Piesa( const std::string&, sf::Vector2i, const Piese&, const Color& );
    static sf::Vector2f getPosFromCoords( const sf::Vector2i& ) noexcept;
    static sf::Vector2i getCoordsFromPos( const sf::Vector2f& ) noexcept;
    static Color        otherColor( const Color& ) noexcept;
    Piese               getType() noexcept;
    Color               getColor() noexcept;
    sf::Vector2i        getCoords() noexcept;
    void                moveOnTable( const sf::Vector2i& ) noexcept;

private:
    Piese        _type;
    Color        _color;
    sf::Vector2i _coords;
};
