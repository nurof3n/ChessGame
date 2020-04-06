#include "Game.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

Game& Game::GetInstance() {
	if( _instance == nullptr )
		_instance = new Game;
	return *_instance;
}

Game::~Game() noexcept {
	if( _instance != nullptr )
		delete _instance;
}

void Game::Setup() noexcept {
	std::cout << "---WELCOME TO CHESS IN CONSOLE!---\n";
	std::cout << "\nPress any key to continue...\n";

	while( !_kbhit() );
	_getch();	//throw key away

	system( "cls" );

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

	_tabla.Setup();
}

void Game::Go() {
	system( "cls" );
	Game::Draw();
	std::cout << COLOR( _player ) << ", TU ESTI LA MUTARE!\n";

	std::optional<Game::RezMutare> result;
	do {
		std::string mutare;
		std::cin >> mutare;
		result = ProcesareMutare( mutare );
		if( !result ) {
			std::cout << "MUTARE INVALIDA, TRY AGAIN...";
			std::this_thread::sleep_for( 1s );
			std::cout << "\33[2K\r";	//erases crt line
			std::cout << "\033[F";		//goes back one line
			std::cout << "\33[2K\r";
		}

	} while( !result );

	_player = (_player == ALB ? NEGRU : ALB);
}

void Game::Draw() {}

std::optional<Game::RezMutare> Game::ProcesareMutare( const std::string& ) noexcept {

	return {};
}

