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
	void Clear() noexcept;
	void Draw( const sf::Sprite& );
	void DrawSprite( const sf::Sprite& );
	void Display();
	bool IsInWindow( const sf::Vector2f& );
private:
	sf::RenderWindow window;
};

