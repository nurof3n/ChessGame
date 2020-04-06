#pragma once
#include "Tabla.h"
#include <optional>

#define ALB 0
#define NEGRU 1
#define COLOR(x) (x == ALB ? "ALB" : "NEGRU")
class Game {
public:
	enum class RezMutare {
		INVALID,
		NEUTRU,
		CAPTURA,
		SAH,
		MAT
	};
private:
	Game() = default;
public:
	static Game& GetInstance();
	~Game() noexcept;
	Game( const Game& ) = delete;
	const Game& operator=( const Game& ) = delete;
	void Setup() noexcept;
	void Go();
	void Draw();
	std::optional<RezMutare> ProcesareMutare( const std::string&, const std::string& ) noexcept;
private:
	static Game* _instance;
	Tabla _tabla;
	int _player = ALB;
};

