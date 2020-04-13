#pragma once
#include "Tabla.h"
#include "Graphics.h"
#include <SFML/Audio.hpp>

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
	void Restart() noexcept;
	void Go( sf::RenderWindow& );
public:
	static Graphics& gfx;
private:
	Tabla _tabla;
	Piesa::Color crtColor;
	bool IsCheck;
	bool IsCheckMate;
	bool IsStaleMate;
};

