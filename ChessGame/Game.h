#pragma once
#include "Tabla.h"
#include "Graphics.h"
#include <SFML/Audio.hpp>
#include <fstream>

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
	void Setup();
	void Restart() noexcept;
	void Go( sf::RenderWindow& );
	void LogMove( sf::Vector2i oldcoords, sf::Vector2i coords, int moveType );
	void WriteLog( std::string output );
public:
	static Graphics& gfx;
private:
	Tabla _tabla;
	Piesa::Color crtColor = Piesa::Color::ALB;
	int round = 0;
	bool IsCheck = false;
	bool IsCheckMate = false;
	bool IsStaleMate = false;
	std::string pgnFilename = "lastmatch.pgn";
	std::ofstream pgnOutput;
};

