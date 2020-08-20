#pragma once
#include "CustomExcept.h"
#include "Piesa.h"
#include "Graphics.h"
#include "AndyMath.h"
#include <vector>

constexpr auto A = 1;
constexpr auto B = 2;
constexpr auto C = 3;
constexpr auto D = 4;
constexpr auto E = 5;
constexpr auto F = 6;
constexpr auto G = 7;
constexpr auto H = 8;

#define MV_VALID		0x1
#define MV_CAPTURE		0x2
#define MV_PROMOTION	0x4
#define MV_CASTLING		0x8
#define MV_CHECK		0x10
#define MV_CHECKMATE	0x20
#define MV_STALEMATE	0x40

class Tabla : public SpriteObj {
public:
	Tabla();
	~Tabla() noexcept;

	sf::Vector2i view( const sf::Vector2i& coords );
	void setup( const Piesa::Color& viewColor );
	void drawPiese( Graphics& gfx, sf::Shader* shader = nullptr );
	Piesa* getPiesa( const sf::Vector2i& coords ) const noexcept;
	sf::Vector2i getPosRege( const Piesa::Color& color ) const noexcept;
	void setPointer( const sf::Vector2i& coords, Piesa* piesa ) noexcept;
	void setPiesa( const sf::Vector2i& coords, Piesa* piesa ) noexcept;
	void erase( const sf::Vector2i& coords ) noexcept;
	bool isInBounds( const sf::Vector2i& coords ) const noexcept;
	int verifyMove( const sf::Vector2i& init, const sf::Vector2i & final ) const;
	int verifyMoveWithCheck( const sf::Vector2i& init, const sf::Vector2i & final );
	void move( const sf::Vector2i& init, const sf::Vector2i & final ) noexcept;
	bool scan( const sf::Vector2i& init, const sf::Vector2i & final ) const noexcept;
	bool isInCheck( Piesa::Color defendingColor ) const;
	bool isInCheckMate( Piesa::Color defendingColor );
	bool isInStaleMate( Piesa::Color defendingColor );
	bool canMove( Piesa::Color color, sf::Vector2i coords = { 0, 0 }, Piesa::Piese type = Piesa::Piese::LIBER );
	bool isAttacking( const sf::Vector2i& init, const sf::Vector2i & final ) const;
	bool isAttacking( Piesa::Color attackingColor, sf::Vector2i coords ) const;
	std::string getMoveString( sf::Vector2i oldcoords, sf::Vector2i coords, int moveType );
	static std::string getFileLetter( int x );
	static std::string getRankNumber( int y );
private:
	Piesa* _tabla[9][9];
	Piesa::Color _viewColor;
	sf::Vector2i posRege[2];
	bool regeMoved[2], turnleftMoved[2], turnrightMoved[2];
};

