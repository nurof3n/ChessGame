#include "Tabla.h"

Tabla::Tabla()
	:
	SpriteObj( "Content/Tabla.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 2.0f, 2.0f ) ) {
	for( int i = 0; i < 9; ++i )
		for( int j = 0; j < 9; ++j )
			_tabla[i][j] = nullptr;
}

Tabla::~Tabla() noexcept {
	for( int i = 0; i <= 8; ++i )
		for( int j = 0; j <= 8; ++j )
			if( _tabla[i][j] != nullptr )
				delete _tabla[i][j];
}

void Tabla::Setup() noexcept {
	for( int j = 1; j <= 8; ++j ) {
		_tabla[2][j] = new Piesa( "Content/Piese/Pion_alb.png", sf::Vector2u( 2u, j ), Piesa::Piese::PION, Piesa::Color::ALB );
		_tabla[7][j] = new Piesa( "Content/Piese/Pion_negru.png", sf::Vector2u( 7u, j ), Piesa::Piese::PION, Piesa::Color::NEGRU );
	}
	_tabla[1][1] = new Piesa( "Content/Piese/Turn_alb.png", sf::Vector2u( 1u, 1u ), Piesa::Piese::TURN, Piesa::Color::ALB );
	_tabla[1][8] = new Piesa( "Content/Piese/Turn_alb.png", sf::Vector2u( 1u, 8u ), Piesa::Piese::TURN, Piesa::Color::ALB );
	_tabla[8][1] = new Piesa( "Content/Piese/Turn_negru.png", sf::Vector2u( 8u, 1u ), Piesa::Piese::TURN, Piesa::Color::NEGRU );
	_tabla[8][8] = new Piesa( "Content/Piese/Turn_negru.png", sf::Vector2u( 8u, 8u ), Piesa::Piese::TURN, Piesa::Color::NEGRU );

	_tabla[1][2] = new Piesa( "Content/Piese/Cal_alb.png", sf::Vector2u( 1u, 2u ), Piesa::Piese::CAL, Piesa::Color::ALB );
	_tabla[1][7] = new Piesa( "Content/Piese/Cal_alb.png", sf::Vector2u( 1u, 7u ), Piesa::Piese::CAL, Piesa::Color::ALB );
	_tabla[8][2] = new Piesa( "Content/Piese/Cal_negru.png", sf::Vector2u( 8u, 2u ), Piesa::Piese::CAL, Piesa::Color::NEGRU );
	_tabla[8][7] = new Piesa( "Content/Piese/Cal_negru.png", sf::Vector2u( 8u, 7u ), Piesa::Piese::CAL, Piesa::Color::NEGRU );

	_tabla[1][3] = new Piesa( "Content/Piese/Nebun_alb.png", sf::Vector2u( 1u, 3u ), Piesa::Piese::NEBUN, Piesa::Color::ALB );
	_tabla[1][6] = new Piesa( "Content/Piese/Nebun_alb.png", sf::Vector2u( 1u, 6u ), Piesa::Piese::NEBUN, Piesa::Color::ALB );
	_tabla[8][3] = new Piesa( "Content/Piese/Nebun_negru.png", sf::Vector2u( 8u, 3u ), Piesa::Piese::NEBUN, Piesa::Color::NEGRU );
	_tabla[8][6] = new Piesa( "Content/Piese/Nebun_negru.png", sf::Vector2u( 8u, 6u ), Piesa::Piese::NEBUN, Piesa::Color::NEGRU );

	_tabla[1][4] = new Piesa( "Content/Piese/Regina_alb.png", sf::Vector2u( 1u, 4u ), Piesa::Piese::REGINA, Piesa::Color::ALB );
	_tabla[8][4] = new Piesa( "Content/Piese/Regina_negru.png", sf::Vector2u( 8u, 4u ), Piesa::Piese::REGINA, Piesa::Color::NEGRU );

	_tabla[1][5] = new Piesa( "Content/Piese/Rege_alb.png", sf::Vector2u( 1u, 5u ), Piesa::Piese::REGE, Piesa::Color::ALB );
	_tabla[8][5] = new Piesa( "Content/Piese/Rege_negru.png", sf::Vector2u( 8u, 5u ), Piesa::Piese::REGE, Piesa::Color::NEGRU );
}

void Tabla::Draw( Graphics& gfx ) {
	gfx.DrawSprite( GetSprite() );
	for( int i = 1; i <= 8; ++i )
		for( int j = 1; j <= 8; ++j )
			if( _tabla[i][j] != nullptr )
				gfx.DrawSprite( _tabla[i][j]->GetSprite() );
}
