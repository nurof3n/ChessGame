#include "Game.h"
#include "CustomExcept.h"

int main() {
	try {
		Game& game = Game::GetInstance();
		game.Setup();
		sf::RenderWindow& window = game.gfx.GetWindow();
		window.setVerticalSyncEnabled( true );
		while( window.isOpen() ) {
			game.Go( window );
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