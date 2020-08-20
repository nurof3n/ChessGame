#include "CustomExcept.h"
#include "Game.h"

int main()
{
    try {
        Game& game = Game::getInstance();
        game.setup();
        sf::RenderWindow& window = game.gfx.getWindow();
        window.setVerticalSyncEnabled( true );
        while( window.isOpen() ) {
            game.go( window );
        }
    }
    catch( const CustomExcept& e ) {
        MessageBoxA( nullptr, e.what(), e.getType(), MB_OK | MB_ICONEXCLAMATION );
    }
    catch( const std::exception& e ) {
        MessageBoxA( nullptr, e.what(), "Standard exception", MB_OK | MB_ICONEXCLAMATION );
    }
    catch( ... ) {
        MessageBoxA( nullptr, "Unknown exception.", "Unknown exception", MB_OK | MB_ICONEXCLAMATION );
    }

    return 0;
}