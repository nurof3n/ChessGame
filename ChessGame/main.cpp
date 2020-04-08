#include <iostream>
#include "Game.h"
#include "CustomExcept.h"
#include <SFML/Graphics.hpp>
#include <windows.h>

int main() {
	try {
		Game& game = Game::GetInstance();
		game.Setup();
		const sf::RenderWindow& window = game.gfx.GetWindow();
		while( window.isOpen() ) {
			game.Go();
		}
	} catch( const CustomExcept & e ) {
		MessageBoxA( nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION );
	} catch( const std::exception & e ) {
		MessageBoxA( nullptr, e.what(), "Standard exception", MB_OK | MB_ICONEXCLAMATION );
	} catch( ... ) {
		MessageBoxA( nullptr, "Unknown exception.", "Unknown exception", MB_OK | MB_ICONEXCLAMATION );
	}

	return 0;
}