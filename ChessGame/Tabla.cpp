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
			if( _tabla[i][j] != nullptr ) {
				delete _tabla[i][j];
				_tabla[i][j] = nullptr;
			}
}

void Tabla::Setup() noexcept {
	for( int i = 0; i <= 8; ++i )
		for( int j = 0; j <= 8; ++j )
			if( _tabla[i][j] != nullptr ) {
				delete _tabla[i][j];
				_tabla[i][j] = nullptr;
			}

	for( int j = 1; j <= 8; ++j ) {
		_tabla[2][j] = new Piesa( "Content/Piese/Pion_alb.png", sf::Vector2i( 2u, j ), Piesa::Piese::PION, Piesa::Color::ALB );
		_tabla[7][j] = new Piesa( "Content/Piese/Pion_negru.png", sf::Vector2i( 7u, j ), Piesa::Piese::PION, Piesa::Color::NEGRU );
	}
	_tabla[1][1] = new Piesa( "Content/Piese/Turn_alb.png", sf::Vector2i( 1u, 1u ), Piesa::Piese::TURN, Piesa::Color::ALB );
	_tabla[1][8] = new Piesa( "Content/Piese/Turn_alb.png", sf::Vector2i( 1u, 8u ), Piesa::Piese::TURN, Piesa::Color::ALB );
	_tabla[8][1] = new Piesa( "Content/Piese/Turn_negru.png", sf::Vector2i( 8u, 1u ), Piesa::Piese::TURN, Piesa::Color::NEGRU );
	_tabla[8][8] = new Piesa( "Content/Piese/Turn_negru.png", sf::Vector2i( 8u, 8u ), Piesa::Piese::TURN, Piesa::Color::NEGRU );

	_tabla[1][2] = new Piesa( "Content/Piese/Cal_alb.png", sf::Vector2i( 1u, 2u ), Piesa::Piese::CAL, Piesa::Color::ALB );
	_tabla[1][7] = new Piesa( "Content/Piese/Cal_alb.png", sf::Vector2i( 1u, 7u ), Piesa::Piese::CAL, Piesa::Color::ALB );
	_tabla[8][2] = new Piesa( "Content/Piese/Cal_negru.png", sf::Vector2i( 8u, 2u ), Piesa::Piese::CAL, Piesa::Color::NEGRU );
	_tabla[8][7] = new Piesa( "Content/Piese/Cal_negru.png", sf::Vector2i( 8u, 7u ), Piesa::Piese::CAL, Piesa::Color::NEGRU );

	_tabla[1][3] = new Piesa( "Content/Piese/Nebun_alb.png", sf::Vector2i( 1u, 3u ), Piesa::Piese::NEBUN, Piesa::Color::ALB );
	_tabla[1][6] = new Piesa( "Content/Piese/Nebun_alb.png", sf::Vector2i( 1u, 6u ), Piesa::Piese::NEBUN, Piesa::Color::ALB );
	_tabla[8][3] = new Piesa( "Content/Piese/Nebun_negru.png", sf::Vector2i( 8u, 3u ), Piesa::Piese::NEBUN, Piesa::Color::NEGRU );
	_tabla[8][6] = new Piesa( "Content/Piese/Nebun_negru.png", sf::Vector2i( 8u, 6u ), Piesa::Piese::NEBUN, Piesa::Color::NEGRU );

	_tabla[1][4] = new Piesa( "Content/Piese/Regina_alb.png", sf::Vector2i( 1u, 4u ), Piesa::Piese::REGINA, Piesa::Color::ALB );
	_tabla[8][4] = new Piesa( "Content/Piese/Regina_negru.png", sf::Vector2i( 8u, 4u ), Piesa::Piese::REGINA, Piesa::Color::NEGRU );

	_tabla[1][5] = new Piesa( "Content/Piese/Rege_alb.png", sf::Vector2i( 1u, 5u ), Piesa::Piese::REGE, Piesa::Color::ALB );
	posRege[0] = sf::Vector2i( 1, 5 );
	_tabla[8][5] = new Piesa( "Content/Piese/Rege_negru.png", sf::Vector2i( 8u, 5u ), Piesa::Piese::REGE, Piesa::Color::NEGRU );
	posRege[1] = sf::Vector2i( 8, 5 );

	regeMoved[0] = regeMoved[1] = false;
	turnleftMoved[0] = turnleftMoved[1] = false;
	turnrightMoved[0] = turnrightMoved[1] = false;
}

void Tabla::Draw( Graphics& gfx ) {
	gfx.DrawSprite( GetSprite() );
	for( int i = 1; i <= 8; ++i )
		for( int j = 1; j <= 8; ++j )
			if( _tabla[i][j] != nullptr )
				gfx.DrawSprite( _tabla[i][j]->GetSprite() );
}

Piesa* Tabla::GetPiesa( const sf::Vector2i& coords ) const noexcept {
	return _tabla[coords.x][coords.y];
}

sf::Vector2i Tabla::GetPosRege( const Piesa::Color& color ) const noexcept {
	return posRege[( int )color];
}

void Tabla::SetPiesa( const sf::Vector2i& coords, Piesa* piesa ) noexcept {
	_tabla[coords.x][coords.y] = piesa;
}

bool Tabla::IsInBounds( const sf::Vector2i& pos ) const noexcept {
	return (pos.x > 0 && pos.x < 9 && pos.y > 0 && pos.y < 9);
}

/*
	return value: (doesn't account for Check, see VerifyMoveWithCheck)
	 -1 = invalid move
	 0 = valid move, no capture
	 1 = valid move, with capture
	 2 = valid move, pawn reached end of table, can switch
	 3 = valid move, castling
*/
int Tabla::VerifyMove( const sf::Vector2i& init, const sf::Vector2i & final ) const {
	if( !IsInBounds( final ) )
		return -1;
	if( init == final )
		return -1;

	Piesa::Piese typeInit = _tabla[init.x][init.y]->GetType(), typeFinal = Piesa::Piese::LIBER;
	Piesa::Color colorInit = _tabla[init.x][init.y]->GetColor(), colorFinal;

	if( _tabla[final.x][final.y] != nullptr ) {
		typeFinal = _tabla[final.x][final.y]->GetType();
		colorFinal = _tabla[final.x][final.y]->GetColor();
		if( colorFinal == colorInit )
			return -1;
	}

	int forward = (colorInit == Piesa::Color::ALB ? 1 : -1);
	int forward2 = 2 * forward;
	sf::Vector2i movement = final - init;
	int isHostage = (typeFinal == Piesa::Piese::LIBER ? 0 : 1);

	switch( typeInit ) {
		case Piesa::Piese::PION:
			if( (colorInit == Piesa::Color::ALB && init.x == 2) || (colorInit == Piesa::Color::NEGRU && init.x == 7) ) {  // daca pionul se poate muta 2 casute in fata
				if( movement == sf::Vector2i( forward2, 0 ) )
					if( typeFinal == Piesa::Piese::LIBER )
						return isHostage;
					else return -1;
			}
			if( movement == sf::Vector2i( forward, 0 ) )
				if( typeFinal == Piesa::Piese::LIBER )
					return isHostage;
				else return -1;
			else
				if( movement == sf::Vector2i( forward, 1 ) || movement == sf::Vector2i( forward, -1 ) )
					if( typeFinal != Piesa::Piese::LIBER )
						return isHostage;
					else return -1;
				else return -1;
			break;
		case Piesa::Piese::CAL:
			if( (abs( movement.x ) == 2 && abs( movement.y ) == 1) || (abs( movement.x ) == 1 && abs( movement.y ) == 2) )
				return isHostage;
			else return -1;
			break;
		case Piesa::Piese::NEBUN:
			if( abs( movement.x ) == abs( movement.y ) ) {
				sf::Vector2i pas = movement / abs( movement.x );
				if( !Scan( init, final, pas ) )
					return -1;
				return isHostage;
			} else return -1;
			break;
		case Piesa::Piese::TURN:
			if( movement.x == 0 || movement.y == 0 ) {
				sf::Vector2i pas = static_cast< sf::Vector2i >(sfm::getNormalized( movement ));
				if( !Scan( init, final, pas ) )
					return -1;
				return isHostage;
			} else return -1;
			break;
		case Piesa::Piese::REGINA:
			if( abs( movement.x ) == abs( movement.y ) ) {
				sf::Vector2i pas = movement / abs( movement.x );
				if( !Scan( init, final, pas ) )
					return -1;
				return isHostage;
			} else if( movement.x == 0 || movement.y == 0 ) {
				sf::Vector2i pas = static_cast< sf::Vector2i >(sfm::getNormalized( movement ));
				if( !Scan( init, final, pas ) )
					return -1;
				return isHostage;
			} else return -1;
			break;
		case Piesa::Piese::REGE:
			if( abs( movement.x ) > 1 || abs( movement.y ) > 1 )
				if( !regeMoved[( int )colorInit] )					// rocada
					if( !turnleftMoved[( int )colorInit] &&
						movement == sf::Vector2i( 0, -2 ) &&
						Scan( init, sf::Vector2i( init.x, 1 ), sf::Vector2i( 0, -1 ) ) )
						return 3;
					else if( !turnrightMoved[( int )colorInit] &&
						movement == sf::Vector2i( 0, 2 ) &&
						Scan( init, sf::Vector2i( init.x, 8 ), sf::Vector2i( 0, 1 ) ) )
						return 3;
					else return -1;
				else return -1;
			else if( abs( movement.x ) == abs( movement.y ) )
				return isHostage;
			else if( movement.x == 0 || movement.y == 0 )
				return isHostage;
			else return -1;
			break;
		default:
			return -1;
			break;
	}
}

int Tabla::VerifyMoveWithCheck( const sf::Vector2i& init, const sf::Vector2i & final ) {
	int result;
	if( (result = VerifyMove( init, final )) != -1 ) {
		auto piesamutata = GetPiesa( init );	// mutare temporara, pentru a verifica sa nu ramanem in sah
		auto piesaluata = GetPiesa( final );
		// daca facem rocada, verificam conditiile
		if( result == 3 ) {
			if( !IsCheck( Piesa::OtherColor( piesamutata->GetColor() ), init ) &&
				!IsCheck( Piesa::OtherColor( piesamutata->GetColor() ), (init + final) / 2 ) &&
				!IsCheck( Piesa::OtherColor( piesamutata->GetColor() ), final ) )
				return 3;
			else return -1;
		}

		SetPiesa( init, nullptr );
		SetPiesa( final, piesamutata );
		// verificam ca dupa mutare (daca nu mutam regele) sa nu fim in sah
		if( piesamutata->GetType() != Piesa::Piese::REGE && IsCheck( Piesa::OtherColor( piesamutata->GetColor() ), GetPosRege( piesamutata->GetColor() ) ) ) {
			SetPiesa( init, piesamutata );
			SetPiesa( final, piesaluata );
			return -1;
		} else if( piesamutata->GetType() == Piesa::Piese::REGE && IsCheck( Piesa::OtherColor( piesamutata->GetColor() ), final ) ) {
			SetPiesa( init, piesamutata );
			SetPiesa( final, piesaluata );
			return -1;
		} else {
			SetPiesa( init, piesamutata );
			SetPiesa( final, piesaluata );
			return result;
		}
	} else return -1;
}

void Tabla::Move( const sf::Vector2i& init, const sf::Vector2i & final ) noexcept {
	delete _tabla[final.x][final.y];
	_tabla[final.x][final.y] = _tabla[init.x][init.y];
	_tabla[final.x][final.y]->MoveOnTable( final );
	_tabla[init.x][init.y] = nullptr;

	auto ind = ( int )_tabla[final.x][final.y]->GetColor();
	if( _tabla[final.x][final.y]->GetType() == Piesa::Piese::REGE ) {
		posRege[ind] = final;
		regeMoved[ind] = true;
	} else if( _tabla[final.x][final.y]->GetType() == Piesa::Piese::TURN )
		if( !turnleftMoved[ind] && init == sf::Vector2i( (ind == 0 ? 1 : 8), 1 ) )
			turnleftMoved[ind] = true;
		else if( !turnrightMoved[ind] && init == sf::Vector2i( (ind == 0 ? 1 : 8), 8 ) )
			turnrightMoved[ind] = true;
}

bool Tabla::Scan( const sf::Vector2i& init, const sf::Vector2i & final, const sf::Vector2i& dir ) const noexcept {
	for( sf::Vector2i crtpos = init + dir; crtpos != final; crtpos += dir )
		if( _tabla[crtpos.x][crtpos.y] != nullptr )
			return false;
	return true;
}

bool Tabla::IsCheck( const Piesa::Color& attackingColor, const sf::Vector2i& posRege ) const noexcept {
	for( int i = 1; i <= 8; ++i )
		for( int j = 1; j <= 8; ++j )
			if( _tabla[i][j] != nullptr && _tabla[i][j]->GetColor() == attackingColor && VerifyMove( sf::Vector2i( i, j ), posRege ) != -1 )
				return true;
	return false;
}

bool Tabla::IsCheckMate( const Piesa::Color& attackingColor, const sf::Vector2i& posRege ) noexcept {
	if( IsCheck( attackingColor, posRege ) && CanBlockCheck( Piesa::OtherColor( attackingColor ) ) )
		return true;
	return false;
}

bool Tabla::IsStaleMate( const Piesa::Color& defendingColor ) noexcept {
	for( int i = 1; i <= 8; ++i )
		for( int j = 1; j <= 8; ++j )
			if( _tabla[i][j] != nullptr && _tabla[i][j]->GetColor() == defendingColor )
				for( int k = 1; k <= 8; ++k )
					for( int l = 1; l <= 8; ++l )
						if( VerifyMoveWithCheck( _tabla[i][j]->GetCoords(), sf::Vector2i( k, l ) ) != -1 )
							return false;
	return true;
}

bool Tabla::CanBlockCheck( const Piesa::Color& defendingColor ) noexcept {
	return IsStaleMate( defendingColor );
}
