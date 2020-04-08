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
}

void Graphics::Draw() {
	window.clear();
	sf::Texture Tabla_tex;
	Tabla_tex.loadFromFile( "Content/Tabla.png" );
	sf::Sprite Tabla_spr( Tabla_tex );
	window.draw( Tabla_spr );
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
