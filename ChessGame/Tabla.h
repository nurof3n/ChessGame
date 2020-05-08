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

	void Setup();
	void DrawPiese( Graphics& gfx, sf::Shader* shader = nullptr );
	Piesa* GetPiesa( const sf::Vector2i& coords ) const noexcept;
	sf::Vector2i GetPosRege( const Piesa::Color& color ) const noexcept;
	void SetPointer( const sf::Vector2i& coords, Piesa* piesa ) noexcept;
	void SetPiesa( const sf::Vector2i& coords, Piesa* piesa ) noexcept;
	void Erase( const sf::Vector2i& coords ) noexcept;
	bool IsInBounds( const sf::Vector2i& coords ) const noexcept;
	int VerifyMove( const sf::Vector2i& init, const sf::Vector2i & final ) const;
	int VerifyMoveWithCheck( const sf::Vector2i& init, const sf::Vector2i & final );
	void Move( const sf::Vector2i& init, const sf::Vector2i & final ) noexcept;
	bool Scan( const sf::Vector2i& init, const sf::Vector2i & final ) const noexcept;
	bool IsInCheck( Piesa::Color defendingColor ) const;
	bool IsInCheckMate( Piesa::Color defendingColor );
	bool IsInStaleMate( Piesa::Color defendingColor );
	bool CanMove( Piesa::Color color, sf::Vector2i coords = { 0, 0 }, Piesa::Piese type = Piesa::Piese::LIBER );
	bool IsAttacking( const sf::Vector2i& init, const sf::Vector2i & final ) const;
	bool IsAttacking( Piesa::Color attackingColor, sf::Vector2i coords ) const;
	std::string GetMoveString( sf::Vector2i oldcoords, sf::Vector2i coords, int moveType );
	static std::string GetFileLetter( int x );
	static std::string GetRankLetter( int y );
private:
	Piesa* _tabla[9][9];
	sf::Vector2i posRege[2];
	bool regeMoved[2], turnleftMoved[2], turnrightMoved[2];
};

