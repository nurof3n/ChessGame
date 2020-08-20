#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "CustomExcept.h"

class Graphics {
private:
	Graphics() = default;
public:
	static Graphics& getInstance() noexcept;

	~Graphics() noexcept = default;
	Graphics( const Graphics& ) = delete;
	const Graphics& operator=( const Graphics& ) = delete;

	sf::RenderWindow& getWindow() noexcept;
	void setup();
	void beginFrame();
	void endFrame();
	void draw( const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default );
	bool isInWindow( const sf::Vector2f& pos );
private:
	sf::RenderWindow window;
};

