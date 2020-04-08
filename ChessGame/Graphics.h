#pragma once
#include <SFML/Graphics.hpp>

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
	int Poll();
	void Display();
private:
	sf::RenderWindow window;
};

