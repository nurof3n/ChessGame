#include "Tabla.h"

Tabla::Tabla()
    : SpriteObj( "Content/Tabla.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 2.0f, 2.0f ) )
{
    for( int i = 0; i < 9; ++i )
        for( int j = 0; j < 9; ++j )
            _tabla[i][j] = nullptr;
}

Tabla::~Tabla() noexcept
{
    for( int i = 0; i <= 8; ++i )
        for( int j = 0; j <= 8; ++j )
            if( _tabla[i][j] != nullptr )
                erase( { i, j } );
}
// switches from absolute to relative coords (and backwards)
sf::Vector2i Tabla::view( const sf::Vector2i& coords )
{
    return _viewColor == Piesa::Color::ALB ? coords : sf::Vector2i( 9 - coords.x, 9 - coords.y );
}
// put the pieces on the table for the start of the match
void Tabla::setup( const Piesa::Color& viewColor )
{
    for( int i = 0; i <= 8; ++i )
        for( int j = 0; j <= 8; ++j )
            if( _tabla[i][j] != nullptr )
                erase( { i, j } );

    _viewColor = viewColor;

    for( int j = 1; j <= 8; ++j ) {
        _tabla[j][2] = new Piesa( "Content/Piese/Pion_alb.png", sf::Vector2i( view( { j, 2 } ) ), Piesa::Piese::PION, Piesa::Color::ALB );
        _tabla[j][7] = new Piesa( "Content/Piese/Pion_negru.png", sf::Vector2i( view( { j, 7 } ) ), Piesa::Piese::PION, Piesa::Color::NEGRU );
    }
    _tabla[1][1] = new Piesa( "Content/Piese/Turn_alb.png", sf::Vector2i( view( { 1, 1 } ) ), Piesa::Piese::TURN, Piesa::Color::ALB );
    _tabla[8][1] = new Piesa( "Content/Piese/Turn_alb.png", sf::Vector2i( view( { 8, 1 } ) ), Piesa::Piese::TURN, Piesa::Color::ALB );
    _tabla[1][8] = new Piesa( "Content/Piese/Turn_negru.png", sf::Vector2i( view( { 1, 8 } ) ), Piesa::Piese::TURN, Piesa::Color::NEGRU );
    _tabla[8][8] = new Piesa( "Content/Piese/Turn_negru.png", sf::Vector2i( view( { 8, 8 } ) ), Piesa::Piese::TURN, Piesa::Color::NEGRU );

    _tabla[2][1] = new Piesa( "Content/Piese/Cal_alb.png", sf::Vector2i( view( { 2, 1 } ) ), Piesa::Piese::CAL, Piesa::Color::ALB );
    _tabla[7][1] = new Piesa( "Content/Piese/Cal_alb.png", sf::Vector2i( view( { 7, 1 } ) ), Piesa::Piese::CAL, Piesa::Color::ALB );
    _tabla[2][8] = new Piesa( "Content/Piese/Cal_negru.png", sf::Vector2i( view( { 2, 8 } ) ), Piesa::Piese::CAL, Piesa::Color::NEGRU );
    _tabla[7][8] = new Piesa( "Content/Piese/Cal_negru.png", sf::Vector2i( view( { 7, 8 } ) ), Piesa::Piese::CAL, Piesa::Color::NEGRU );

    _tabla[3][1] = new Piesa( "Content/Piese/Nebun_alb.png", sf::Vector2i( view( { 3, 1 } ) ), Piesa::Piese::NEBUN, Piesa::Color::ALB );
    _tabla[6][1] = new Piesa( "Content/Piese/Nebun_alb.png", sf::Vector2i( view( { 6, 1 } ) ), Piesa::Piese::NEBUN, Piesa::Color::ALB );
    _tabla[3][8] = new Piesa( "Content/Piese/Nebun_negru.png", sf::Vector2i( view( { 3, 8 } ) ), Piesa::Piese::NEBUN, Piesa::Color::NEGRU );
    _tabla[6][8] = new Piesa( "Content/Piese/Nebun_negru.png", sf::Vector2i( view( { 6, 8 } ) ), Piesa::Piese::NEBUN, Piesa::Color::NEGRU );

    _tabla[4][1] = new Piesa( "Content/Piese/Regina_alb.png", sf::Vector2i( view( { 4, 1 } ) ), Piesa::Piese::REGINA, Piesa::Color::ALB );
    _tabla[4][8] = new Piesa( "Content/Piese/Regina_negru.png", sf::Vector2i( view( { 4, 8 } ) ), Piesa::Piese::REGINA, Piesa::Color::NEGRU );

    _tabla[5][1] = new Piesa( "Content/Piese/Rege_alb.png", sf::Vector2i( view( { 5, 1 } ) ), Piesa::Piese::REGE, Piesa::Color::ALB );
    posRege[0]   = sf::Vector2i( 5, 1 );
    _tabla[5][8] = new Piesa( "Content/Piese/Rege_negru.png", sf::Vector2i( view( { 5, 8 } ) ), Piesa::Piese::REGE, Piesa::Color::NEGRU );
    posRege[1]   = sf::Vector2i( 5, 8 );

    regeMoved[0] = regeMoved[1] = false;
    turnleftMoved[0] = turnleftMoved[1] = false;
    turnrightMoved[0] = turnrightMoved[1] = false;
}
// draws the pieces on the table
void Tabla::drawPiese( Graphics& gfx, sf::Shader* shader )
{
    for( int i = 1; i <= 8; ++i )
        for( int j = 1; j <= 8; ++j )
            if( _tabla[i][j] != nullptr ) {
                if( shader != nullptr ) {
                    shader->setUniform( "texture", sf::Shader::CurrentTexture );
                    shader->setUniform( "blur_radius", 0.037f );
                }
                gfx.draw( _tabla[i][j]->getSprite(), shader );
            }
}

Piesa* Tabla::getPiesa( const sf::Vector2i& coords ) const noexcept
{
    return _tabla[coords.x][coords.y];
}

sf::Vector2i Tabla::getPosRege( const Piesa::Color& color ) const noexcept
{
    return posRege[(int) color];
}

void Tabla::setPointer( const sf::Vector2i& coords, Piesa* piesa ) noexcept
{
    _tabla[coords.x][coords.y] = piesa;
}

void Tabla::setPiesa( const sf::Vector2i& coords, Piesa* piesa ) noexcept
{
    erase( coords );
    setPointer( coords, piesa );
}

void Tabla::erase( const sf::Vector2i& coords ) noexcept
{
    delete _tabla[coords.x][coords.y];
    _tabla[coords.x][coords.y] = nullptr;
}

bool Tabla::isInBounds( const sf::Vector2i& pos ) const noexcept
{
    return ( pos.x > 0 && pos.x < 9 && pos.y > 0 && pos.y < 9 );
}
// returns 0 if the move is invalid. (doesn't account for Check, see VerifyMoveWithCheck)
int Tabla::verifyMove( const sf::Vector2i& init, const sf::Vector2i& final ) const
{
    int moveType = ( isAttacking( init, final ) ? MV_VALID : 0 );

    Piesa::Piese typeInit = getPiesa( init )->getType(), typeFinal = Piesa::Piese::LIBER;
    Piesa::Color colorInit = getPiesa( init )->getColor(), colorFinal;

    if( getPiesa( final ) != nullptr ) {
        typeFinal  = getPiesa( final )->getType();
        colorFinal = getPiesa( final )->getColor();
        if( colorFinal == colorInit )
            return 0;
    }

    // forward movement for extended pawn movement
    int          forward  = ( colorInit == Piesa::Color::ALB ? 1 : -1 );
    int          forward2 = 2 * forward;
    sf::Vector2i movement = final - init;
    if( typeFinal != Piesa::Piese::LIBER )
        moveType |= MV_CAPTURE;

    switch( typeInit ) {
        case Piesa::Piese::PION:
            // verificam daca este promotie
            if( ( colorInit == Piesa::Color::ALB && final.y == 8 ) || ( colorInit == Piesa::Color::NEGRU && final.y == 1 ) )
                moveType |= MV_PROMOTION;
            // daca mutarea este deja valida, inseamna ca trebuie sa fie captura
            if( moveType & MV_VALID )
                if( moveType & MV_CAPTURE )
                    return moveType;
                else
                    return 0;
            // altfel, verificam daca pionul se muta in fata
            if( movement == sf::Vector2i( 0, forward ) )
                if( typeFinal == Piesa::Piese::LIBER )
                    return moveType | MV_VALID;
                else
                    return 0;
            else if( ( colorInit == Piesa::Color::ALB && init.y == 2 ) || ( colorInit == Piesa::Color::NEGRU && init.y == 7 ) ) {
                if( movement == sf::Vector2i( 0, forward2 ) )
                    if( scan( init, final ) && typeFinal == Piesa::Piese::LIBER )
                        return moveType | MV_VALID;
                    else
                        return 0;
                else
                    return 0;
            }
            else
                return 0;
        case Piesa::Piese::REGE:
            // daca mutarea este valida, nu mai avem ce verifica
            if( moveType & MV_VALID )
                return moveType;
            // altfel, verificam daca se face rocada
            if( !regeMoved[(int) colorInit] )
                if( movement == sf::Vector2i( -2, 0 ) &&
                    !turnleftMoved[(int) colorInit] &&
                    scan( init, sf::Vector2i( 1, init.y ) ) )
                    return moveType | MV_VALID | MV_CASTLING;
                else if( movement == sf::Vector2i( 2, 0 ) &&
                         !turnrightMoved[(int) colorInit] &&
                         scan( init, sf::Vector2i( 8, init.y ) ) )
                    return moveType | MV_VALID | MV_CASTLING;
                else
                    return 0;
            else
                return 0;
        default:
            // pentru orice alta piesa, validarea mutarii este deja facuta
            return moveType;
    }
}

int Tabla::verifyMoveWithCheck( const sf::Vector2i& init, const sf::Vector2i& final )
{
    int moveType;
    if( ( moveType = verifyMove( init, final ) ) & MV_VALID ) {
        // mutare temporara, pentru a verifica sa nu ramanem in sah
        auto piesamutata = getPiesa( init );
        auto piesaluata  = getPiesa( final );
        auto type        = piesamutata->getType();
        auto color       = piesamutata->getColor();

        // daca facem rocada, verificam conditiile
        if( moveType & MV_CASTLING ) {
            if( !isAttacking( Piesa::otherColor( color ), init ) &&
                !isAttacking( Piesa::otherColor( color ), ( init + final ) / 2 ) &&
                !isAttacking( Piesa::otherColor( color ), final ) )
                return moveType;
            else
                return 0;
        }

        setPointer( init, nullptr );
        setPointer( final, piesamutata );
        if( type == Piesa::Piese::REGE )
            posRege[(int) color] = final;

        // verificam ca dupa mutare sa nu fim in sah
        if( isInCheck( color ) ) {
            setPointer( init, piesamutata );
            setPointer( final, piesaluata );
            if( type == Piesa::Piese::REGE )
                posRege[(int) color] = init;
            return 0;
        }
        else {
            setPointer( init, piesamutata );
            setPointer( final, piesaluata );
            if( type == Piesa::Piese::REGE )
                posRege[(int) color] = init;
            return moveType;
        }
    }
    else
        return 0;
}

void Tabla::move( const sf::Vector2i& init, const sf::Vector2i& final ) noexcept
{
    erase( final );
    _tabla[final.x][final.y] = _tabla[init.x][init.y];
    // move to the viewing coords
    _tabla[final.x][final.y]->moveOnTable( view( final ) );
    _tabla[init.x][init.y] = nullptr;

    auto ind = (int) _tabla[final.x][final.y]->getColor();
    if( _tabla[final.x][final.y]->getType() == Piesa::Piese::REGE ) {
        posRege[ind]   = final;
        regeMoved[ind] = true;
    }
    else if( _tabla[final.x][final.y]->getType() == Piesa::Piese::TURN )
        if( !turnleftMoved[ind] && init == sf::Vector2i( 1, ( ind == 0 ? 1 : 8 ) ) )
            turnleftMoved[ind] = true;
        else if( !turnrightMoved[ind] && init == sf::Vector2i( 8, ( ind == 0 ? 1 : 8 ) ) )
            turnrightMoved[ind] = true;
}
// returns true if the path from init to final is clear
bool Tabla::scan( const sf::Vector2i& init, const sf::Vector2i& final ) const noexcept
{
    // !! dir will always be along the file/rank, or along the diagonals !!
    auto         movement = final - init;
    sf::Vector2i dir      = { 0, 0 };
    if( init.x != final.x )
        dir.x = movement.x / abs( movement.x );
    if( init.y != final.y )
        dir.y = movement.y / abs( movement.y );

    for( sf::Vector2i crtpos = init + dir; crtpos != final; crtpos += dir )
        if( _tabla[crtpos.x][crtpos.y] != nullptr )
            return false;
    return true;
}

bool Tabla::isInCheck( Piesa::Color defendingColor ) const
{
    return isAttacking( Piesa::otherColor( defendingColor ), posRege[int( defendingColor )] );
}

bool Tabla::isInCheckMate( Piesa::Color defendingColor )
{
    return isInCheck( defendingColor ) && !canMove( defendingColor );
}

bool Tabla::isInStaleMate( Piesa::Color defendingColor )
{
    return !isInCheck( defendingColor ) && !canMove( defendingColor );
}

bool Tabla::canMove( Piesa::Color color, sf::Vector2i coords, Piesa::Piese type )
{
    for( int i = 1; i <= 8; ++i )
        for( int j = 1; j <= 8; ++j )
            if( _tabla[i][j] != nullptr && _tabla[i][j]->getColor() == color && ( type == Piesa::Piese::LIBER || _tabla[i][j]->getType() == type ) )
                if( coords == sf::Vector2i( 0, 0 ) ) {
                    for( int k = 1; k <= 8; ++k )
                        for( int l = 1; l <= 8; ++l )
                            if( verifyMoveWithCheck( { i, j }, sf::Vector2i( k, l ) ) & MV_VALID )
                                return true;
                }
                else {
                    if( verifyMoveWithCheck( { i, j }, coords ) & MV_VALID )
                        return true;
                }
    return false;
}
// returns true if the piece from init is attacking the square final (doesn't matter what piece is in final)
bool Tabla::isAttacking( const sf::Vector2i& init, const sf::Vector2i& final ) const
{
    if( !isInBounds( init ) || !isInBounds( final ) )
        return false;
    if( init == final )
        return false;
    if( getPiesa( init ) == nullptr )
        return false;

    Piesa::Piese typeInit  = getPiesa( init )->getType();
    Piesa::Color colorInit = getPiesa( init )->getColor();

    int          forward  = ( colorInit == Piesa::Color::ALB ? 1 : -1 );
    sf::Vector2i movement = final - init;

    switch( typeInit ) {
        case Piesa::Piese::PION:
            return ( movement == sf::Vector2i( 1, forward ) || movement == sf::Vector2i( -1, forward ) );
        case Piesa::Piese::CAL:
            return ( ( abs( movement.x ) == 2 && abs( movement.y ) == 1 ) || ( abs( movement.x ) == 1 && abs( movement.y ) == 2 ) );
        case Piesa::Piese::NEBUN:
            if( abs( movement.x ) == abs( movement.y ) )
                return scan( init, final );
            else
                return false;
        case Piesa::Piese::TURN:
            if( movement.x == 0 || movement.y == 0 )
                return scan( init, final );
            else
                return false;
        case Piesa::Piese::REGINA:
            if( abs( movement.x ) == abs( movement.y ) || ( movement.x == 0 || movement.y == 0 ) )
                return scan( init, final );
            else
                return false;
        case Piesa::Piese::REGE:
            return ( abs( movement.x ) <= 1 && abs( movement.y ) <= 1 );
        default:
            return false;
    }
}
// returns true if attackingColor is attacking the square coords (doesn't matter what piece is in coords)
bool Tabla::isAttacking( Piesa::Color attackingColor, sf::Vector2i coords ) const
{
    for( int i = 1; i <= 8; ++i )
        for( int j = 1; j <= 8; ++j )
            if( _tabla[i][j] != nullptr && _tabla[i][j]->getColor() == attackingColor && isAttacking( { i, j }, coords ) )
                return true;
    return false;
}
// returns move code for recording in pgn file
std::string Tabla::getMoveString( sf::Vector2i oldcoords, sf::Vector2i coords, int moveType )
{
    std::string moveString;
    if( moveType & MV_CASTLING )
        return oldcoords.x > coords.x ? "O-O-O" : "O-O";

    auto         piece = _tabla[oldcoords.x][oldcoords.y];
    Piesa::Piese type  = piece->getType();
    Piesa::Color color = piece->getColor();
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
    bool diffRank    = true,  // .y
        diffFile     = true;  // .x
    for( int i = 1; i <= 8; ++i )
        for( int j = 1; j <= 8; ++j )
            if( _tabla[i][j] != nullptr && _tabla[i][j]->getColor() == color && _tabla[i][j]->getType() == type && verifyMoveWithCheck( { i, j }, coords ) & MV_VALID )
                if( i != oldcoords.x || j != oldcoords.y ) {
                    isAmbiguous = true;
                    if( i == oldcoords.x )
                        diffFile = false;
                    if( j == oldcoords.y )
                        diffRank = false;
                }

    if( isAmbiguous )
        if( diffFile )
            moveString += getFileLetter( oldcoords.x );
        else if( diffRank )
            moveString += getRankNumber( oldcoords.y );
        else
            moveString += getFileLetter( oldcoords.x ) + getRankNumber( oldcoords.y );

    if( moveType & MV_CAPTURE ) {
        if( type == Piesa::Piese::PION )
            moveString += getFileLetter( oldcoords.x );
        moveString += "x";
    }

    moveString += getFileLetter( coords.x ) + getRankNumber( coords.y );

    if( moveType & MV_PROMOTION )
        moveString += "=Q";

    return moveString;
}
// column
std::string Tabla::getFileLetter( int x )
{
    return std::string( 1, x + 'a' - 1 );
}
// row
std::string Tabla::getRankNumber( int y )
{
    return std::string( 1, y + '0' );
}
