#include <iostream>
#include "Game.h"
#include "CustomExcept.h"
#include <SFML/Graphics.hpp>

int main() {
	Game& game = Game::GetInstance();
	game.Setup();
	const sf::RenderWindow& window = game.gfx.GetWindow();
	try {
		while( window.isOpen() ) {
			game.Go();
		}
	} catch( const CustomExcept & e ) {
		std::cout << "\n\n" << e.GetType() << ' ' << e.what() << "\n\n";
	} catch( const std::exception & e ) {
		std::cout << "\n\nStandard exception: " << e.what() << "\n\n";
	} catch( ... ) {
		std::cout << "\n\nUnknown exception.\n\n";
	}

	return 0;
}