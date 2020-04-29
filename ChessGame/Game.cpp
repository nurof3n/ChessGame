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
	IsCheckMate = _tabla.IsInCheckMate( crtColor );
	IsStaleMate = _tabla.IsInStaleMate( crtColor );
	pgnOutput.open( pgnFilename );

	ShowWindow( GetConsoleWindow(), SW_HIDE );
	gfx.Setup();
}

void Game::Restart() noexcept {
	_tabla.Setup();
	crtColor = Piesa::Color::ALB;
	round = 0;
	IsCheck = false;
	IsCheckMate = _tabla.IsInCheckMate( crtColor );
	IsStaleMate = _tabla.IsInStaleMate( crtColor );
	pgnOutput.close();
	pgnOutput.open( pgnFilename );
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

	static SpriteObj* patratInit = nullptr;
	static SpriteObj* patratFinal = nullptr;

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

					int moveType;
					if( (moveType = _tabla.VerifyMoveWithCheck( oldcoords, coords )) != 0 ) {
						LogMove( oldcoords, coords, moveType );					// mai intai inregistram mutarea!

						if( patratInit == nullptr )
							patratInit = new SpriteObj( "Content/Patrat_initial.png", { 0,0 }, { 2.0,2.0 } );
						if( patratFinal == nullptr )
							patratFinal = new SpriteObj( "Content/Patrat_final.png", { 0,0 }, { 2.0,2.0 } );
						patratInit->MoveTo( Piesa::GetPosFromCoords( oldcoords ) );
						patratFinal->MoveTo( Piesa::GetPosFromCoords( coords ) );

						_tabla.Move( oldcoords, coords );						// aici facem mutarea
						if( moveType & MV_CASTLING )								// rocada
							if( coords.x < 5 )		// rocada la stanga
								_tabla.Move( sf::Vector2i( 1, coords.y ), sf::Vector2i( coords.x + 1, coords.y ) );
							else					// rocada la dreapta
								_tabla.Move( sf::Vector2i( 8, coords.y ), sf::Vector2i( coords.x - 1, coords.y ) );
						else if( moveType & MV_PROMOTION ) {						// promotie
							_tabla.Erase( coords );
							if( coords.y == 1 ) {
								Piesa* piesa = new Piesa( "Content/Piese/Regina_negru.png", coords, Piesa::Piese::REGINA, Piesa::Color::NEGRU );
								_tabla.SetPiesa( coords, piesa );
							} else {
								Piesa* piesa = new Piesa( "Content/Piese/Regina_alb.png", coords, Piesa::Piese::REGINA, Piesa::Color::ALB );
								_tabla.SetPiesa( coords, piesa );
							}
						}

						if( _tabla.IsInCheckMate( Piesa::OtherColor( crtColor ) ) ) {
							IsCheckMate = true;
							WriteLog( crtColor == Piesa::Color::ALB ? "# 1-0" : "# 0-1" );
						} else if( _tabla.IsInCheck( Piesa::OtherColor( crtColor ) ) ) {
							WriteLog( "+" );
							crtColor = Piesa::OtherColor( crtColor );
						} else if( _tabla.IsInStaleMate( Piesa::OtherColor( crtColor ) ) ) {
							IsStaleMate = true;
							WriteLog( "1/2-1/2" );
						} else
							crtColor = Piesa::OtherColor( crtColor );
					}
				}
			}
		}
	} else return;


	gfx.Clear();
	// desenam tabla
	gfx.Draw( _tabla.GetSprite() );
	// coloram patratelul din care am mutat si cel in care am mutat
	if( patratInit != nullptr )
		gfx.Draw( patratInit->GetSprite() );
	if( patratFinal != nullptr )
		gfx.Draw( patratFinal->GetSprite() );
	// desenam piesele de pe tabla
	_tabla.DrawPiese( gfx );
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
							delete patratFinal;
							patratFinal = nullptr;
							delete patratInit;
							patratInit = nullptr;
							return;
						}
						break;
				}
	}

	gfx.Display();
}

void Game::LogMove( sf::Vector2i oldcoords, sf::Vector2i coords, int moveType ) {
	std::string moveString = _tabla.GetMoveString( oldcoords, coords, moveType );
	auto color = _tabla.GetPiesa( oldcoords )->GetColor();

	if( color == Piesa::Color::ALB )
		pgnOutput << ' ' << ++round << '.';
	pgnOutput << ' ' << moveString;
}

void Game::WriteLog( std::string output ) {
	pgnOutput << output;
}

