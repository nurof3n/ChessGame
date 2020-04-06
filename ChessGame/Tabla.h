#pragma once
#include <ctype.h>
#include "CustomExcept.h"

enum class Piese {
	LIBER = 0,
	PIONA,
	NEBUNA,
	CALA,
	TURAA,
	REGINAA,
	REGEA,
	PIONN,
	NEBUNN,
	CALN,
	TURAN,
	REGINAN,
	REGEN
};
class Tabla {
public:
	Tabla() noexcept;
	bool InBounds( int x, int y ) noexcept;
	bool InBounds( char c, int y ) noexcept;
	Piese Get( int x, int y );
	Piese Get( char c, int y );
	void Set( int x, int y, Piese piesa );
	void Set( char c, int y, Piese piesa );
	void Setup() noexcept;
private:
	Piese _tabla[8][8];	// albul e sus, negrul e jos
};

