#pragma once
#include "Tabla.h"
#include "Graphics.h"
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
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
	void GoMenu( sf::RenderWindow& window );
	void Go( sf::RenderWindow& window );
	void Move( sf::Vector2i oldcoords, sf::Vector2i coords, int moveType );
	void LogMove( sf::Vector2i oldcoords, sf::Vector2i coords, int moveType );
	void WriteLog( std::string output );
	bool EstablishConnection();
public:
	static Graphics& gfx;
private:
	Tabla _tabla;
	Piesa::Color crtColor = Piesa::Color::ALB;
	Piesa::Color multiplayerColor;
	int round = 0;
	bool wantsRestart = false;
	bool pendingRestart = false;
	bool refusedRestart = false;
	bool isStarted = false;
	bool isCheckMate = false;
	bool isStaleMate = false;
	bool isSinglePlayer;
	bool isFinished = false;
	std::string pgnFilename = "lastmatch.pgn";
	std::ofstream pgnOutput;
	sf::SoundBuffer moveSoundBuffer;
	sf::Sound moveSound;
	SpriteObj* patratInit = nullptr;
	SpriteObj* patratFinal = nullptr;
	Piesa* piesaTinuta = nullptr;
	sf::TcpSocket tcpSocket;
	sf::TcpListener tcpListener;
};

