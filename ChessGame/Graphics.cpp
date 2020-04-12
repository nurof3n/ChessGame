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
	icon.loadFromFile( "Content/Piese/Cal_negru.png" );
	window.setIcon( 32, 32, icon.getPixelsPtr() );

	// disable window resize
	HWND hWnd = window.getSystemHandle();
	long dwStyle = GetWindowLong( hWnd, GWL_STYLE );
	dwStyle ^= WS_MAXIMIZEBOX | WS_SIZEBOX;
	SetWindowLong( hWnd, GWL_STYLE, dwStyle );
}

void Graphics::Clear() noexcept {
	window.clear();
}

void Graphics::Draw( const sf::Sprite& sprite ) {
	DrawSprite( sprite );
}

void Graphics::DrawSprite( const sf::Sprite& sprite ) {
	window.draw( sprite );
}

void Graphics::Display() {
	window.display();
}

bool Graphics::IsInWindow( const sf::Vector2f& pos ) {
	return (pos.x >= 0 && pos.x <= window.getSize().x - 1 && pos.y >= 0 && pos.y <= window.getSize().y - 1);
}
