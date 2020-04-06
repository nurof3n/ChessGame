#include "Tabla.h"

Tabla::Tabla() noexcept {
	for( int i = 0; i < 8; ++i )
		for( int j = 0; j < 8; ++j )
			_tabla[i][j] = Piese::LIBER;
}

bool Tabla::InBounds( int x, int y ) noexcept {
	return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

bool Tabla::InBounds( char c, int y ) noexcept {
	return InBounds( tolower( c ) - 'a', y );
}

Piese Tabla::Get( int x, int y ) {
	if( InBounds( x, y ) )
		return _tabla[x][y];
	throw CustomExcept::Except::OUT_OF_BOUNDS;
}

Piese Tabla::Get( char c, int y ) {
	return Get( tolower( c ) - 'a', y );
}

void Tabla::Set( int x, int y, Piese piesa ) {
	if( InBounds( x, y ) )
		_tabla[x][y] = piesa;
	else
		throw CustomExcept::Except::OUT_OF_BOUNDS;
}

void Tabla::Set( char c, int y, Piese piesa ) {
	Set( tolower( c ) - 'a', y, piesa );
}

void Tabla::Setup() noexcept {
	for( int i = 0; i < 8; ++i ) {
		Tabla::Set( 1, i, Piese::PIONA );
		Tabla::Set( 6, i, Piese::PIONN );
	}
	Tabla::Set( 0, 0, Piese::TURAA );
	Tabla::Set( 0, 7, Piese::TURAA );
	Tabla::Set( 7, 0, Piese::TURAN );
	Tabla::Set( 7, 7, Piese::TURAN );
	Tabla::Set( 0, 1, Piese::CALA );
	Tabla::Set( 0, 6, Piese::CALA );
	Tabla::Set( 7, 1, Piese::CALN );
	Tabla::Set( 7, 6, Piese::CALN );
	Tabla::Set( 0, 2, Piese::NEBUNA );
	Tabla::Set( 0, 5, Piese::NEBUNA );
	Tabla::Set( 7, 2, Piese::NEBUNN );
	Tabla::Set( 7, 5, Piese::NEBUNN );
	Tabla::Set( 0, 3, Piese::REGINAA );
	Tabla::Set( 7, 3, Piese::REGINAN );
	Tabla::Set( 0, 4, Piese::REGEA );
	Tabla::Set( 7, 4, Piese::REGEN );
}
