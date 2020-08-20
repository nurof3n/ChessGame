#pragma once
#include "Tabla.h"
#include "Button.h"
#include "Graphics.h"
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <fstream>


class Game
{
public:
	enum class RezMutare
	{
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
	static Game& getInstance() noexcept;
	Game( const Game& ) = delete;
	const Game& operator=( const Game& ) = delete;
	void setup();
	void restart() noexcept;
	void pressAnyKeyToReturnToMenu();
	void connectionLost();
	void closeConnection();
	void composeFrame();
	void updateModel();
	void go( sf::RenderWindow& window );
	void move( sf::Vector2i oldcoords, sf::Vector2i coords, int moveType );
	void logMove( sf::Vector2i oldcoords, sf::Vector2i coords, int moveType );
	void writeLog( std::string output );
	bool establishConnection();
	void stopSounds();
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

