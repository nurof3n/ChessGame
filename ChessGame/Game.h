#pragma once
#include "Tabla.h"
#include "Graphics.h"

class Game {
public:
	enum class RezMutare {
		INVALID,
		OK,
		CAPTURA,
		SAH,
		MAT
	};
private:
	Game() = default;
public:
	static Game& GetInstance() noexcept;
	Game( const Game& ) = delete;
	const Game& operator=( const Game& ) = delete;
	void Setup() noexcept;
	void Go( sf::RenderWindow& );
public:
	static Graphics& gfx;
private:
	Tabla _tabla;
};

