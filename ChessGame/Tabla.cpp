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
				Erase( { i, j } );
}

void Tabla::Setup() noexcept {
	for( int i = 0; i <= 8; ++i )
		for( int j = 0; j <= 8; ++j )
			if( _tabla[i][j] != nullptr )
				Erase( { i, j } );

	for( int j = 1; j <= 8; ++j ) {
		_tabla[j][2] = new Piesa( "Content/Piese/Pion_alb.png", sf::Vector2i( j, 2 ), Piesa::Piese::PION, Piesa::Color::ALB );
		_tabla[j][7] = new Piesa( "Content/Piese/Pion_negru.png", sf::Vector2i( j, 7 ), Piesa::Piese::PION, Piesa::Color::NEGRU );
	}
	_tabla[1][1] = new Piesa( "Content/Piese/Turn_alb.png", sf::Vector2i( 1, 1 ), Piesa::Piese::TURN, Piesa::Color::ALB );
	_tabla[8][1] = new Piesa( "Content/Piese/Turn_alb.png", sf::Vector2i( 8, 1 ), Piesa::Piese::TURN, Piesa::Color::ALB );
	_tabla[1][8] = new Piesa( "Content/Piese/Turn_negru.png", sf::Vector2i( 1, 8 ), Piesa::Piese::TURN, Piesa::Color::NEGRU );
	_tabla[8][8] = new Piesa( "Content/Piese/Turn_negru.png", sf::Vector2i( 8, 8 ), Piesa::Piese::TURN, Piesa::Color::NEGRU );

	_tabla[2][1] = new Piesa( "Content/Piese/Cal_alb.png", sf::Vector2i( 2, 1 ), Piesa::Piese::CAL, Piesa::Color::ALB );
	_tabla[7][1] = new Piesa( "Content/Piese/Cal_alb.png", sf::Vector2i( 7, 1 ), Piesa::Piese::CAL, Piesa::Color::ALB );
	_tabla[2][8] = new Piesa( "Content/Piese/Cal_negru.png", sf::Vector2i( 2, 8 ), Piesa::Piese::CAL, Piesa::Color::NEGRU );
	_tabla[7][8] = new Piesa( "Content/Piese/Cal_negru.png", sf::Vector2i( 7, 8 ), Piesa::Piese::CAL, Piesa::Color::NEGRU );

	_tabla[3][1] = new Piesa( "Content/Piese/Nebun_alb.png", sf::Vector2i( 3, 1 ), Piesa::Piese::NEBUN, Piesa::Color::ALB );
	_tabla[6][1] = new Piesa( "Content/Piese/Nebun_alb.png", sf::Vector2i( 6, 1 ), Piesa::Piese::NEBUN, Piesa::Color::ALB );
	_tabla[3][8] = new Piesa( "Content/Piese/Nebun_negru.png", sf::Vector2i( 3, 8 ), Piesa::Piese::NEBUN, Piesa::Color::NEGRU );
	_tabla[6][8] = new Piesa( "Content/Piese/Nebun_negru.png", sf::Vector2i( 6, 8 ), Piesa::Piese::NEBUN, Piesa::Color::NEGRU );

	_tabla[4][1] = new Piesa( "Content/Piese/Regina_alb.png", sf::Vector2i( 4, 1 ), Piesa::Piese::REGINA, Piesa::Color::ALB );
	_tabla[4][8] = new Piesa( "Content/Piese/Regina_negru.png", sf::Vector2i( 4, 8 ), Piesa::Piese::REGINA, Piesa::Color::NEGRU );

	_tabla[5][1] = new Piesa( "Content/Piese/Rege_alb.png", sf::Vector2i( 5, 1 ), Piesa::Piese::REGE, Piesa::Color::ALB );
	posRege[0] = sf::Vector2i( 5, 1 );
	_tabla[5][8] = new Piesa( "Content/Piese/Rege_negru.png", sf::Vector2i( 5, 8 ), Piesa::Piese::REGE, Piesa::Color::NEGRU );
	posRege[1] = sf::Vector2i( 5, 8 );

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

void Tabla::SetPointer( const sf::Vector2i& coords, Piesa* piesa ) noexcept {
	_tabla[coords.x][coords.y] = piesa;
}

void Tabla::SetPiesa( const sf::Vector2i& coords, Piesa* piesa ) noexcept {
	Erase( coords );
	_tabla[coords.x][coords.y] = std::move( piesa );
}

void Tabla::Erase( const sf::Vector2i& coords ) noexcept {
	delete _tabla[coords.x][coords.y];
	_tabla[coords.x][coords.y] = nullptr;
}

bool Tabla::IsInBounds( const sf::Vector2i& pos ) const noexcept {
	return (pos.x > 0 && pos.x < 9 && pos.y > 0 && pos.y < 9);
}


//	returns 0 if the move is invalid. (doesn't account for Check, see VerifyMoveWithCheck)
int Tabla::VerifyMove( const sf::Vector2i& init, const sf::Vector2i & final ) const {
	if( !IsInBounds( final ) )
		return 0;
	if( init == final )
		return 0;
	if( GetPiesa( init ) == nullptr )
		return 0;

	Piesa::Piese typeInit = _tabla[init.x][init.y]->GetType(), typeFinal = Piesa::Piese::LIBER;
	Piesa::Color colorInit = _tabla[init.x][init.y]->GetColor(), colorFinal;

	if( _tabla[final.x][final.y] != nullptr ) {
		typeFinal = _tabla[final.x][final.y]->GetType();
		colorFinal = _tabla[final.x][final.y]->GetColor();
		if( colorFinal == colorInit )
			return 0;
	}

	int forward = (colorInit == Piesa::Color::ALB ? 1 : -1);
	int forward2 = 2 * forward;
	sf::Vector2i movement = final - init;
	int captureFlag = (typeFinal == Piesa::Piese::LIBER ? 0 : MV_CAPTURE);

	switch( typeInit ) {
		case Piesa::Piese::PION:
			if( (colorInit == Piesa::Color::ALB && init.y == 2) || (colorInit == Piesa::Color::NEGRU && init.y == 7) ) {  // daca pionul se poate muta 2 casute in fata
				if( movement == sf::Vector2i( 0, forward2 ) )
					if( typeFinal == Piesa::Piese::LIBER )
						return MV_VALID | captureFlag;
					else return 0;
			}
			if( movement == sf::Vector2i( 0, forward ) )
				if( typeFinal == Piesa::Piese::LIBER )
					return MV_VALID | captureFlag;
				else return 0;
			else
				if( movement == sf::Vector2i( 1, forward ) || movement == sf::Vector2i( -1, forward ) )
					if( typeFinal != Piesa::Piese::LIBER )
						return MV_VALID | captureFlag;
					else return 0;
				else return 0;
			break;
		case Piesa::Piese::CAL:
			if( (abs( movement.x ) == 2 && abs( movement.y ) == 1) || (abs( movement.x ) == 1 && abs( movement.y ) == 2) )
				return MV_VALID | captureFlag;
			else return 0;
			break;
		case Piesa::Piese::NEBUN:
			if( abs( movement.x ) == abs( movement.y ) ) {
				sf::Vector2i pas = movement / abs( movement.x );
				if( !Scan( init, final, pas ) )
					return 0;
				return MV_VALID | captureFlag;
			} else return 0;
			break;
		case Piesa::Piese::TURN:
			if( movement.x == 0 || movement.y == 0 ) {
				sf::Vector2i pas = static_cast< sf::Vector2i >(sfm::getNormalized( movement ));
				if( !Scan( init, final, pas ) )
					return 0;
				return MV_VALID | captureFlag;
			} else return 0;
			break;
		case Piesa::Piese::REGINA:
			if( abs( movement.x ) == abs( movement.y ) ) {
				sf::Vector2i pas = movement / abs( movement.x );
				if( !Scan( init, final, pas ) )
					return 0;
				return MV_VALID | captureFlag;
			} else if( movement.x == 0 || movement.y == 0 ) {
				sf::Vector2i pas = static_cast< sf::Vector2i >(sfm::getNormalized( movement ));
				if( !Scan( init, final, pas ) )
					return 0;
				return MV_VALID | captureFlag;
			} else return 0;
			break;
		case Piesa::Piese::REGE:
			if( abs( movement.x ) > 1 || abs( movement.y ) > 1 )
				if( !regeMoved[( int )colorInit] )					// rocada
					if( movement == sf::Vector2i( -2, 0 ) &&
						!turnleftMoved[( int )colorInit] &&
						Scan( init, sf::Vector2i( 1, init.y ), sf::Vector2i( -1, 0 ) ) )
						return MV_VALID | MV_CASTLING;
					else if( movement == sf::Vector2i( 2, 0 ) &&
						!turnrightMoved[( int )colorInit] &&
						Scan( init, sf::Vector2i( 8, init.y ), sf::Vector2i( 1, 0 ) ) )
						return MV_VALID | MV_CASTLING;
					else return 0;
				else return 0;
			else if( abs( movement.x ) == abs( movement.y ) )
				return MV_VALID | captureFlag;
			else if( movement.x == 0 || movement.y == 0 )
				return MV_VALID | captureFlag;
			else return 0;
			break;
		default:
			return 0;
			break;
	}
}

int Tabla::VerifyMoveWithCheck( const sf::Vector2i& init, const sf::Vector2i & final ) {
	int moveType;
	if( (moveType = VerifyMove( init, final )) != 0 ) {
		auto piesamutata = GetPiesa( init );	// mutare temporara, pentru a verifica sa nu ramanem in sah
		auto piesaluata = GetPiesa( final );
		auto type = piesamutata->GetType();
		auto color = piesamutata->GetColor();
		// daca facem rocada, verificam conditiile
		if( moveType & MV_CASTLING ) {
			if( !IsAttacking( Piesa::OtherColor( color ), init ) &&
				!IsAttacking( Piesa::OtherColor( color ), (init + final) / 2 ) &&
				!IsAttacking( Piesa::OtherColor( color ), final ) )
				return moveType;
			else return 0;
		}

		SetPointer( init, nullptr );
		SetPointer( final, piesamutata );
		// verificam ca dupa mutare (daca nu mutam regele) sa nu fim in sah
		if( type != Piesa::Piese::REGE && IsInCheck( color ) ) {
			SetPointer( init, piesamutata );
			SetPointer( final, piesaluata );
			return 0;
		} else if( type == Piesa::Piese::REGE && IsAttacking( Piesa::OtherColor( color ), final ) ) {
			SetPointer( init, piesamutata );
			SetPointer( final, piesaluata );
			return 0;
		} else {
			SetPointer( init, piesamutata );
			SetPointer( final, piesaluata );
			// verificam daca este promotie
			if( type == Piesa::Piese::PION )
				if( color == Piesa::Color::ALB && final.y == 8 )
					return moveType | MV_PROMOTION;
				else if( color == Piesa::Color::NEGRU && final.y == 1 )
					return moveType | MV_PROMOTION;

			return moveType;
		}
	} else return 0;
}

void Tabla::Move( const sf::Vector2i& init, const sf::Vector2i & final ) noexcept {
	Erase( final );
	_tabla[final.x][final.y] = _tabla[init.x][init.y];
	_tabla[final.x][final.y]->MoveOnTable( final );
	_tabla[init.x][init.y] = nullptr;

	auto ind = ( int )_tabla[final.x][final.y]->GetColor();
	if( _tabla[final.x][final.y]->GetType() == Piesa::Piese::REGE ) {
		posRege[ind] = final;
		regeMoved[ind] = true;
	} else if( _tabla[final.x][final.y]->GetType() == Piesa::Piese::TURN )
		if( !turnleftMoved[ind] && init == sf::Vector2i( 1, (ind == 0 ? 1 : 8) ) )
			turnleftMoved[ind] = true;
		else if( !turnrightMoved[ind] && init == sf::Vector2i( 8, (ind == 0 ? 1 : 8) ) )
			turnrightMoved[ind] = true;
}

bool Tabla::Scan( const sf::Vector2i& init, const sf::Vector2i & final, const sf::Vector2i& dir ) const noexcept {
	for( sf::Vector2i crtpos = init + dir; crtpos != final; crtpos += dir )
		if( _tabla[crtpos.x][crtpos.y] != nullptr )
			return false;
	return true;
}

bool Tabla::IsInCheck( Piesa::Color defendingColor ) const {
	return IsAttacking( Piesa::OtherColor( defendingColor ), posRege[int( defendingColor )] );
}

bool Tabla::IsInCheckMate( Piesa::Color defendingColor ) {
	if( IsInCheck( defendingColor ) && !CanMove( defendingColor ) )
		return true;
	return false;
}

bool Tabla::IsInStaleMate( Piesa::Color defendingColor ) {
	return !CanMove( defendingColor );
}

bool Tabla::CanMove( Piesa::Color color, sf::Vector2i coords, Piesa::Piese type ) {
	for( int i = 1; i <= 8; ++i )
		for( int j = 1; j <= 8; ++j )
			if( _tabla[i][j] != nullptr && _tabla[i][j]->GetColor() == color && (type == Piesa::Piese::LIBER || _tabla[i][j]->GetType() == type) )
				if( coords == sf::Vector2i( 0, 0 ) ) {
					for( int k = 1; k <= 8; ++k )
						for( int l = 1; l <= 8; ++l )
							if( VerifyMoveWithCheck( _tabla[i][j]->GetCoords(), sf::Vector2i( k, l ) ) != 0 )
								return true;
				} else if( VerifyMoveWithCheck( _tabla[i][j]->GetCoords(), coords ) != 0 )
					return true;
				return false;
}

bool Tabla::IsAttacking( Piesa::Color attackingColor, sf::Vector2i coords ) const {
	for( int i = 1; i <= 8; ++i )
		for( int j = 1; j <= 8; ++j )
			if( _tabla[i][j] != nullptr && _tabla[i][j]->GetColor() == attackingColor && VerifyMove( sf::Vector2i( i, j ), coords ) != 0 )
				return true;
	return false;
}

std::string Tabla::GetMoveString( sf::Vector2i oldcoords, sf::Vector2i coords, int moveType ) {
	std::string moveString;
	if( moveType == MV_CASTLING )
		return oldcoords.x < coords.x ? "O-O-O" : "O-O";

	auto piece = _tabla[oldcoords.x][oldcoords.y];
	Piesa::Piese type = piece->GetType();
	Piesa::Color color = piece->GetColor();
	switch( type ) {
		case Piesa::Piese::CAL:
			moveString += "N";
			break;
		case Piesa::Piese::NEBUN:
			moveString += "B";
			break;
		case Piesa::Piese::TURN:
			moveString += "R";
			break;
		case Piesa::Piese::REGINA:
			moveString += "Q";
			break;
		case Piesa::Piese::REGE:
			moveString += "K";
			break;
	}

	bool isAmbiguous = false;
	bool diffRank = true,	// .y
		diffFile = true;	// .x
	for( int i = 1; i <= 8; ++i )
		for( int j = 1; j <= 8; ++j )
			if( _tabla[i][j] != nullptr && _tabla[i][j]->GetColor() == color && _tabla[i][j]->GetType() == type && VerifyMoveWithCheck( { i, j }, coords ) != 0 )
				if( i != oldcoords.x || j != oldcoords.y ) {
					isAmbiguous = true;
					if( i == oldcoords.x )
						diffFile = false;
					if( j == oldcoords.y )
						diffRank = false;
				}

	if( isAmbiguous )
		if( diffFile )
			moveString += GetFileLetter( oldcoords.x );
		else if( diffRank )
			moveString += GetRankLetter( oldcoords.y );
		else
			moveString += GetFileLetter( oldcoords.x ) + GetRankLetter( oldcoords.y );

	if( moveType & MV_CAPTURE ) {
		if( type == Piesa::Piese::PION )
			moveString += GetFileLetter( oldcoords.x );
		moveString += "x";
	}


	moveString += GetFileLetter( coords.x ) + GetRankLetter( coords.y );

	if( moveType & MV_PROMOTION )
		moveString += "=Q";

	return moveString;
}

std::string Tabla::GetFileLetter( int x ) {
	return std::string( 1, x + 'a' - 1 );
}

std::string Tabla::GetRankLetter( int y ) {
	return std::string( 1, y + '0' );
}
