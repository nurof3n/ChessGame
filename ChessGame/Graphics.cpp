#include "Graphics.h"
#include "CustomExcept.h"

Graphics& Graphics::getInstance() noexcept {
	static Graphics _instance;
	return _instance;
}

sf::RenderWindow& Graphics::getWindow() noexcept {
	return window;
}

void Graphics::setup() {
	window.create( sf::VideoMode( 512, 512 ), "ChessGame" );
	sf::Image icon;
	if( !icon.loadFromFile( "Content/Icon.png" ) )
		throw EXCEPT( "Cannot load file: Content/Icon.png" );
	window.setIcon( 16, 16, icon.getPixelsPtr() );
	// disable window resize
	HWND hWnd = window.getSystemHandle();
	long dwStyle = GetWindowLong( hWnd, GWL_STYLE );
	dwStyle ^= WS_MAXIMIZEBOX | WS_SIZEBOX;
	SetWindowLong( hWnd, GWL_STYLE, dwStyle );
}

void Graphics::beginFrame() {
	window.clear();
}

void Graphics::endFrame() {
	window.display();
}

void Graphics::draw( const sf::Drawable& drawable, const sf::RenderStates& states ) {
	window.draw( drawable, states );
}

bool Graphics::isInWindow( const sf::Vector2f& pos ) {
	return (pos.x >= 0 && pos.x <= window.getSize().x - 1 && pos.y >= 0 && pos.y <= window.getSize().y - 1);
}
