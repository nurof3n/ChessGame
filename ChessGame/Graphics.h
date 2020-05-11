#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "CustomExcept.h"

class Graphics {
private:
	Graphics() = default;
public:
	static Graphics& GetInstance() noexcept;

	~Graphics() noexcept = default;
	Graphics( const Graphics& ) = delete;
	const Graphics& operator=( const Graphics& ) = delete;

	sf::RenderWindow& GetWindow() noexcept;
	void Setup();
	void BeginFrame();
	void EndFrame();
	void Draw( const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default );
	bool IsInWindow( const sf::Vector2f& pos );
private:
	sf::RenderWindow window;
};

