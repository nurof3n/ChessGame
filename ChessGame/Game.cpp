#include "Game.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <conio.h>
#include <thread>
#include <chrono>
#include <windows.h>

#define SKIP_INTRO

using namespace std::chrono_literals;

Graphics& Game::gfx = Graphics::GetInstance();

Game& Game::GetInstance() noexcept {
	static Game _instance;
	return _instance;
}

void Game::Setup() {
	ShowWindow( GetConsoleWindow(), SW_SHOW );

	std::cout << "---WELCOME TO CHESS IN C++!---\n";
	std::cout << "\nPress any key to continue...\n";

	while( !_kbhit() );
	_getch();	//throw key away

	system( "cls" );

#ifndef SKIP_INTRO
	std::cout << "READY? TYPE MACARENA\n";
	std::string color = "";
	do {
		std::cin >> color;
		std::transform( color.begin(), color.end(), color.begin(), tolower );
		if( color != "macarena" )
			std::cout << "\033[F" << "\33[2K\r";
	} while( color != "macarena" );

	system( "cls" );

	std::cout << "JOCUL INCEPE...\n";
	std::this_thread::sleep_for( 2s );
	std::cout << "INCA PUTIN...\n";
	std::this_thread::sleep_for( 2s );
	std::cout << "ESTI SIGUR CA NU VREI SA IESI?...\n";
	std::this_thread::sleep_for( 2s );
	std::cout << "NU SUNT RESPONSABIL PENTRU VICTIME...\n";
	std::this_thread::sleep_for( 2s );
#endif

	_tabla.Setup();
	crtColor = Piesa::Color::ALB;
	round = 0;
	IsCheck = false;
	IsCheckMate = _tabla.IsCheckMate( Piesa::OtherColor( crtColor ) );
	IsStaleMate = _tabla.IsStaleMate( crtColor );
	output.open( pgnFilename );

	ShowWindow( GetConsoleWindow(), SW_HIDE );
	gfx.Setup();
}

void Game::Restart() noexcept {
	_tabla.Setup();
	crtColor = Piesa::Color::ALB;
	IsCheck = false;
	IsCheckMate = _tabla.IsCheckMate( Piesa::OtherColor( crtColor ) );
	IsStaleMate = _tabla.IsStaleMate( crtColor );
}

void Game::Go( sf::RenderWindow& window ) {
	sf::Event event;
	while( window.pollEvent( event ) )
		switch( event.type ) {
			case sf::Event::Closed:
				window.close();
				return;
		}

	static sf::Vector2f oldpos;
	static Piesa* piesa = nullptr;
	static bool IsLeftMouseHeld = false;

	IsCheck = false;
	if( !IsCheckMate && !IsStaleMate ) {
		if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) ) {
			auto pos = sf::Vector2f( sf::Mouse::getPosition( window ) );
			if( !IsLeftMouseHeld ) {			//daca incepe o mutare cu mouseul
				IsLeftMouseHeld = true;
				if( gfx.IsInWindow( pos ) ) {	//verificam sa nu fie mouseul in afara ferestrei
					auto coords = Piesa::GetCoordsFromPos( pos );
					piesa = _tabla.GetPiesa( coords );
					if( piesa != nullptr ) 				//daca am apasat pe o piesa, retinem vechea pozitie
						if( piesa->GetColor() == crtColor ) {
							_tabla.SetPointer( coords, nullptr );	//scoatem piesa de pe tabla
							oldpos = piesa->GetPos();
						} else piesa = nullptr;
				}
			}
			if( piesa != nullptr )				//updatam pozitia piesei tinute, daca tinem vreuna
				piesa->MoveTo( pos - sf::Vector2f( 32.0f, 32.0f ) );
		} else {
			if( IsLeftMouseHeld ) {			//daca tocmai s-a terminat o mutare din mouse
				IsLeftMouseHeld = false;
				if( piesa != nullptr ) {	//daca am mutat o piesa
					auto oldcoords = Piesa::GetCoordsFromPos( oldpos );
					auto coords = Piesa::GetCoordsFromPos( piesa->GetPos() + sf::Vector2f( 32.0f, 32.0f ) );
					piesa->MoveTo( oldpos );
					_tabla.SetPointer( oldcoords, piesa );
					piesa = nullptr;

					int result;
					if( (result = _tabla.VerifyMoveWithCheck( oldcoords, coords )) != 0 ) {
						_tabla.Move( oldcoords, coords );						// aici facem mutarea
						if( result & MV_CASTLING )								// rocada
							if( coords.x < 5 )		// rocada la stanga
								_tabla.Move( sf::Vector2i( 1, coords.y ), sf::Vector2i( coords.x + 1, coords.y ) );
							else					// rocada la dreapta
								_tabla.Move( sf::Vector2i( 8, coords.y ), sf::Vector2i( coords.x - 1, coords.y ) );
						else if( result & MV_PROMOTION ) {						// promotie
							_tabla.Erase( coords );
							if( coords.y == 1 ) {
								Piesa* piesa = new Piesa( "Content/Piese/Regina_negru.png", coords, Piesa::Piese::REGINA, Piesa::Color::NEGRU );
								_tabla.SetPiesa( coords, piesa );
							} else {
								Piesa* piesa = new Piesa( "Content/Piese/Regina_alb.png", coords, Piesa::Piese::REGINA, Piesa::Color::ALB );
								_tabla.SetPiesa( coords, piesa );
							}
						}

						if( _tabla.IsCheckMate( crtColor ) )	// verificam daca am dat mat
							IsCheckMate = true;
						else if( _tabla.IsStaleMate( Piesa::OtherColor( crtColor ) ) )								// verificam daca am dat pat
							IsStaleMate = true;
						else
							crtColor = Piesa::OtherColor( crtColor );												// altfel, schimbam randul si continuam jocul 
					}
				}
			}
		}
	} else return;


	gfx.Clear();
	// desenam tabla cu piesele din casute
	_tabla.Draw( gfx );
	// desenam piesa pe care o avem selectata
	if( piesa != nullptr )
		gfx.Draw( piesa->GetSprite() );
	// endgame
	if( IsCheckMate || IsStaleMate ) {
		SpriteObj checkmate( IsCheckMate ? "Content/CheckMate.png" : "Content/StaleMate.png" );
		gfx.Draw( checkmate.GetSprite() );
		sf::SoundBuffer soundBuffer;
		soundBuffer.loadFromFile( IsCheckMate ? "Content/Audio/bomb.wav" : "Content/Audio/spayed.wav" );
		sf::Sound sound( soundBuffer );
		gfx.Display();
		sound.play();
		while( true )
			while( window.pollEvent( event ) )
				switch( event.type ) {
					case sf::Event::Closed:
						window.close();
						return;
						break;
					case sf::Event::KeyPressed:
						if( event.key.code == sf::Keyboard::R ) {
							Restart();
							return;
						}
						break;
				}
	}

	gfx.Display();
}

void Game::LogMove( Piesa::Piese pieceType, sf::Vector2i oldcoords, sf::Vector2i coords, int moveType ) {
	/*std::string moveString = Tabla::GetMoveString( Piesa::Piese pieceType, sf::Vector2i oldcoords, sf::Vector2i coords, int moveType );

	switch( pieceType ) {
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
	bool ambiguu = false*/
}

