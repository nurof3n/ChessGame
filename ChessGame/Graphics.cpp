#include "Graphics.h"

Graphics& Graphics::GetInstance() noexcept {
	static Graphics _instance;
	return _instance;
}

sf::RenderWindow& Graphics::GetWindow() noexcept {
	return window;
}

void Graphics::Setup() noexcept {
	window.create( sf::VideoMode( 512, 512 ), "ChessGame" );
	sf::Image icon;
	icon.loadFromFile( "Content/Icon.png" );
	window.setIcon( 16, 16, icon.getPixelsPtr() );

	// disable window resize
	HWND hWnd = window.getSystemHandle();
	long dwStyle = GetWindowLong( hWnd, GWL_STYLE );
	dwStyle ^= WS_MAXIMIZEBOX | WS_SIZEBOX;
	SetWindowLong( hWnd, GWL_STYLE, dwStyle );
}

void Graphics::Draw() {
	window.clear();
}

void Graphics::DrawSprite( const sf::Sprite& sprite ) {
	window.draw( sprite );
}

int Graphics::Poll() {
	sf::Event event;
	while( window.pollEvent( event ) )
		if( event.type == sf::Event::Closed ) {
			window.close();
			return -1;
		}
	return 0;
}

void Graphics::Display() {
	window.display();
}
