#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>

class Graphics {
private:
	Graphics() = default;
public:
	static Graphics& GetInstance() noexcept;
	~Graphics() noexcept = default;
	Graphics( const Graphics& ) = delete;
	const Graphics& operator=( const Graphics& ) = delete;

	sf::RenderWindow& GetWindow() noexcept;
	void Setup() noexcept;
	void Draw();
	void DrawSprite( const sf::Sprite& );
	int Poll();
	void Display();
private:
	sf::RenderWindow window;
};

