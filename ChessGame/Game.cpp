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

void Game::Setup() noexcept {
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
		std::transform( color.begin(), color.end(), color.begin(), std::tolower );
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
	std::cout << "IMEDIAT TERMIN BEREA SI VIN...\n";
	std::this_thread::sleep_for( 2s );
#endif

	_tabla.Setup();

	ShowWindow( GetConsoleWindow(), SW_HIDE );
	gfx.Setup();
}

void Game::Go() {
	int result = gfx.Poll();
	if( result == -1 )
		return;
	gfx.Draw();
	gfx.Display();
}

std::optional<Game::RezMutare> Game::ProcesareMutare( const sf::Vector2u& pos, const sf::Vector2u& newpos ) noexcept {

	return {};
}

