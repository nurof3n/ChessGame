#pragma once
#include "Tabla.h"
#include "Button.h"
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
	~Game();
	static Game& GetInstance() noexcept;
	Game( const Game& ) = delete;
	const Game& operator=( const Game& ) = delete;
	void Setup();
	void Restart() noexcept;
	void PressAnyKeyToReturnToMenu();
	void ConnectionLost();
	void CloseConnection();
	void ComposeFrame();
	void UpdateModel();
	void Go( sf::RenderWindow& window );
	void Move( sf::Vector2i oldcoords, sf::Vector2i coords, int moveType );
	void LogMove( sf::Vector2i oldcoords, sf::Vector2i coords, int moveType );
	void WriteLog( std::string output );
	bool EstablishConnection();
	void StopSounds();
public:
	static Graphics& gfx;
private:
	Tabla _tabla;
	Piesa::Color crtColor = Piesa::Color::ALB;
	Piesa::Color multiplayerColor = Piesa::Color::ALB;
	int round = 0;
	bool wantsRestart = false;
	bool pendingRestart = false;
	bool refusedRestart = false;
	bool isStarted = false;
	bool isFinished = false;
	bool isMenu = true;
	bool isChoosingSides = false;
	bool isServer = false;
	bool isCheckMate = false;
	bool isStaleMate = false;
	bool isSinglePlayer = true;
	bool endSoundPlaying = false;
	std::string pgnFilename = "lastmatch.pgn";
	std::ofstream pgnOutput;
	sf::SoundBuffer moveSoundBuffer, endSoundBuffer;
	sf::Sound moveSound, endSound;
	SpriteObj* patratInit = nullptr;
	SpriteObj* patratFinal = nullptr;
	Piesa* piesaTinuta = nullptr;
	sf::TcpSocket tcpSocket;
	sf::TcpListener tcpListener;
	Button buttonPlaySingle, buttonPlayMulti, buttonWhite, buttonBlack;
};

