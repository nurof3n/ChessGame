#pragma once
#include "Tabla.h"
#include "Graphics.h"
#include <optional>

#define ALB 0
#define NEGRU 1
#define COLOR(x) (x == ALB ? "ALB" : "NEGRU")
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
	void Go();
	std::optional<RezMutare> ProcesareMutare( const sf::Vector2u&, const sf::Vector2u& ) noexcept;
public:
	static Graphics& gfx;
private:
	Tabla _tabla;
	int _player = ALB;
};

