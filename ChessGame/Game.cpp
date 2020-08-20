#include "Game.h"

#include <conio.h>
#include <windows.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <thread>

#define SKIP_INTRO

using namespace std::chrono_literals;

Graphics& Game::gfx = Graphics::getInstance();

// remember to delete the pointers!!
Game::~Game()
{
    delete patratInit;
    delete patratFinal;
    delete piesaTinuta;
}
// singleton
Game& Game::getInstance() noexcept
{
    static Game _instance;
    return _instance;
}
// intro in console
void Game::setup()
{
#ifndef SKIP_INTRO
    ShowWindow( GetConsoleWindow(), SW_SHOW );

    std::cout << "---WELCOME TO CHESS IN C++!---\n";
    std::cout << "\nPress any key to continue...\n";

    while( !_kbhit() )
        ;
    if( _getch() == 0xE0 )
        _getch();

    system( "cls" );

    std::cout << "READY? TYPE MACARENA\n";
    std::string color = "";
    do {
        std::cin >> color;
        std::transform( color.begin(), color.end(), color.begin(), tolower );
        if( color != "macarena" )
            std::cout << "\033[F"
                      << "\33[2K\r";
    } while( color != "macarena" );

    system( "cls" );

    std::cout << "JOCUL INCEPE...\n";
    std::this_thread::sleep_for( 2s );
    std::cout << "INCA PUTIN...\n";
    std::this_thread::sleep_for( 2s );
    std::cout << "ESTI SIGUR CA NU VREI SA IESI?...\n";
    std::this_thread::sleep_for( 2s );
    std::cout << "NU SUNT RESPONSABIL PENTRU VICTIME...\n";
    std::this_thread::sleep_for( 2s );
#endif

    ShowWindow( GetConsoleWindow(), SW_HIDE );

    buttonPlaySingle = Button( "Content/PlayButtonSingle.png", { 128.0f, 194.0f } );
    buttonPlayMulti  = Button( "Content/PlayButtonMulti.png", { 128.0f, 252.0f } );
    buttonWhite      = Button( "Content/Piese/Pion_alb.png", { 64.0f, 200.0f }, { 4.0, 4.0 } );
    buttonBlack      = Button( "Content/Piese/Pion_negru.png", { 320.0f, 200.0f }, { 4.0, 4.0 } );

    gfx.setup();
}
// reinitialize variables here, to restart the game
void Game::restart() noexcept
{
    stopSounds();
    _tabla.setup( multiplayerColor );
    crtColor        = Piesa::Color::ALB;
    round           = 0;
    refusedRestart  = false;
    wantsRestart    = false;
    pendingRestart  = false;
    isStarted       = true;
    isFinished      = false;
    isMenu          = false;
    isCheckMate     = false;
    isStaleMate     = false;
    isChoosingSides = false;
    delete patratInit;
    patratInit = nullptr;
    delete patratFinal;
    patratFinal = nullptr;
    delete piesaTinuta;
    piesaTinuta = nullptr;
    pgnOutput.close();
    pgnOutput.open( pgnFilename );
}
// shows the message and waits for key input to return to menu
void Game::pressAnyKeyToReturnToMenu()
{
    ShowWindow( GetConsoleWindow(), SW_SHOW );
    std::cout << "Press any key to return to menu...";
    // throw key away, and if it was a function key or arrow key, throw again !!!
    if( _getch() == 0xE0 )
        _getch();
    ShowWindow( GetConsoleWindow(), SW_HIDE );
}
// says that connection was lost and waits for input to return to menu
void Game::connectionLost()
{
    closeConnection();
    system( "cls" );
    std::cout << "Connection lost.\n";
    pressAnyKeyToReturnToMenu();
    isStarted       = false;
    isChoosingSides = false;
    isFinished      = false;
    isMenu          = true;
}
// closes the connection
void Game::closeConnection()
{
    isServer       = false;
    wantsRestart   = false;
    pendingRestart = false;
    tcpSocket.disconnect();
    tcpListener.close();
}
// draws the objects on the screen
void Game::composeFrame()
{
    static sf::Shader       blurShader;
    static sf::RenderStates renderStates;
    if( !isStarted || isFinished ) {
        if( !blurShader.loadFromFile( "Shaders/gaussblur.frag", sf::Shader::Fragment ) )
            throw EXCEPT( "Cannot load file: Shaders/gaussblur.frag" );
        blurShader.setUniform( "texture", sf::Shader::CurrentTexture );
        blurShader.setUniform( "blur_radius", 0.005f );
        renderStates = sf::RenderStates( &blurShader );
    }
    else
        renderStates = sf::RenderStates::Default;

    gfx.draw( _tabla.getSprite(), renderStates );

    if( isStarted && !isFinished ) {
        if( patratInit != nullptr )
            gfx.draw( patratInit->getSprite() );
        if( patratFinal != nullptr )
            gfx.draw( patratFinal->getSprite() );
        _tabla.drawPiese( gfx );
        if( piesaTinuta != nullptr )
            gfx.draw( piesaTinuta->getSprite() );
    }
    else if( isMenu ) {
        gfx.draw( buttonPlaySingle.getSprite() );
        gfx.draw( buttonPlayMulti.getSprite() );
    }
    else if( isChoosingSides ) {
        SpriteObj textChoose( isServer ? "Content/ChooseSide.png" : "Content/ChooseSideWait.png" );

        gfx.draw( textChoose.getSprite() );
        gfx.draw( buttonWhite.getSprite() );
        gfx.draw( buttonBlack.getSprite() );
    }
    else if( isFinished ) {
        if( patratInit != nullptr ) {
            blurShader.setUniform( "texture", sf::Shader::CurrentTexture );
            gfx.draw( patratInit->getSprite(), &blurShader );
        }
        if( patratFinal != nullptr ) {
            blurShader.setUniform( "texture", sf::Shader::CurrentTexture );
            gfx.draw( patratFinal->getSprite(), &blurShader );
        }

        // desenam piesele de pe tabla, cu shaderul de blur
        _tabla.drawPiese( gfx, &blurShader );

        if( refusedRestart ) {
            static SpriteObj refusedRematch( "Content/RefusedRematch.png" );
            gfx.draw( refusedRematch.getSprite() );
        }
        else if( wantsRestart ) {
            static SpriteObj restart( "Content/Restart.png" );
            gfx.draw( restart.getSprite() );
        }
        else if( pendingRestart ) {
            static SpriteObj pending( "Content/PendingRematch.png" );
            gfx.draw( pending.getSprite() );
        }
        else {
            static SpriteObj checkmate( isCheckMate ? "Content/CheckMate.png" : "Content/StaleMate.png" );
            gfx.draw( checkmate.getSprite() );
        }
    }
}
// updates game logic
void Game::updateModel()
{
    static auto& window = gfx.getWindow();

    sf::Event event;
    while( window.pollEvent( event ) )
        switch( event.type ) {
            case sf::Event::Closed:
                closeConnection();
                window.close();

                return;
            case sf::Event::KeyPressed:
                // go to the menu
                if( event.key.code == sf::Keyboard::M && isStarted ) {
                    isStarted       = false;
                    isFinished      = false;
                    isChoosingSides = false;
                    isMenu          = true;
                    closeConnection();
                    stopSounds();

                    return;
                }
                else
                    // restart the game
                    if( event.key.code == sf::Keyboard::R && isFinished ) {
                    if( !isSinglePlayer ) {
                        // request restart only if haven't already done so, and the other hasn't left or rejected
                        if( !wantsRestart && !refusedRestart ) {
                            wantsRestart = true;
                            // transmitem faptul ca vrem rematch
                            sf::Packet packetSent;
                            // request = 1 inseamna REMATCH
                            int request = 1;
                            packetSent << request;
                            tcpSocket.setBlocking( true );
                            if( tcpSocket.send( packetSent ) == sf::Socket::Status::Disconnected ) {
                                refusedRestart = true;
                                closeConnection();
                            }
                            // daca si celalalt voia rematch, dam rematch
                            else if( pendingRestart ) {
                                restart();

                                return;
                            }
                        }
                    }
                    // if singleplayer, just restart
                    else {
                        restart();

                        return;
                    }
                }
                break;
            case sf::Event::MouseButtonPressed:
                if( event.mouseButton.button == sf::Mouse::Left )
                    if( isMenu ) {
                        // start singleplayer game
                        if( buttonPlaySingle.mouseIsOver( window ) ) {
                            restart();
                            isSinglePlayer = true;

                            return;
                        }
                        // start multiplayer game
                        else if( buttonPlayMulti.mouseIsOver( window ) ) {
                            if( establishConnection() ) {
                                isChoosingSides = true;
                                isSinglePlayer  = false;
                                isMenu          = false;
                            }

                            return;
                        }
                    }
                    else if( isChoosingSides ) {
                        // the server chooses its side
                        if( isServer ) {
                            if( buttonWhite.mouseIsOver( window ) ) {
                                multiplayerColor = Piesa::Color::ALB;
                                sf::Packet packetSent;
                                packetSent << (int) multiplayerColor;
                                tcpSocket.setBlocking( true );
                                if( tcpSocket.send( packetSent ) != sf::Socket::Status::Done )
                                    connectionLost();
                                else
                                    restart();

                                return;
                            }
                            else if( buttonBlack.mouseIsOver( window ) ) {
                                multiplayerColor = Piesa::Color::NEGRU;
                                sf::Packet packetSent;
                                packetSent << (int) multiplayerColor;
                                tcpSocket.setBlocking( true );
                                if( tcpSocket.send( packetSent ) != sf::Socket::Status::Done )
                                    connectionLost();
                                else
                                    restart();

                                return;
                            }
                        }
                    }
        }
    // if in menu, nothing left to do
    if( isMenu )
        return;
    // if finished, play the end sound
    if( isFinished ) {
        // if multiplayer, wait for rematch
        if( !isSinglePlayer && !refusedRestart ) {
            sf::Packet packetReceived;
            tcpSocket.setBlocking( false );
            sf::Socket::Status status = tcpSocket.receive( packetReceived );
            // daca am primit pachetul, verificam daca a cerut rematch
            // response = 1 inseamna REMATCH
            if( status == sf::Socket::Status::Done ) {
                int response;
                if( packetReceived >> response && response == 1 ) {
                    pendingRestart = true;
                    // daca si noi voiam rematch, dam rematch
                    if( wantsRestart ) {
                        restart();

                        return;
                    }
                }
                else {
                    refusedRestart = true;
                    closeConnection();
                }
            }
            else if( status == sf::Socket::Status::Disconnected ) {
                refusedRestart = true;
                closeConnection();
            }
        }

        if( !endSoundPlaying ) {
            std::string audioFile2 = isCheckMate ? "Content/Audio/bomb.wav" : "Content/Audio/spayed.wav";
            if( !endSoundBuffer.loadFromFile( audioFile2 ) )
                throw EXCEPT( "Cannot load file: " + audioFile2 );
            endSound.setBuffer( endSoundBuffer );
            endSound.setVolume( 60 );
            endSound.play();
            endSoundPlaying = true;
        }

        return;
    }
    // waiting for other player to choose side if we are not the server
    if( isChoosingSides && !isServer ) {
        sf::Packet packetReceived;
        tcpSocket.setBlocking( false );
        sf::Socket::Status status = tcpSocket.receive( packetReceived );
        if( status == sf::Socket::Status::Done ) {
            int response;
            if( packetReceived >> response ) {
                auto color = static_cast<Piesa::Color>( response );
                if( response >= 0 && response <= 1 ) {
                    multiplayerColor = Piesa::otherColor( color );
                    restart();

                    return;
                }
                else {
                    connectionLost();

                    return;
                }
            }
            else {
                connectionLost();

                return;
            }
        }
        else if( status == sf::Socket::Status::Disconnected ) {
            connectionLost();

            return;
        }

        return;
    }
    // actual chess game logic
    static sf::Vector2f oldpos;
    static bool         IsLeftMouseHeld = false;
    if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && ( isSinglePlayer || multiplayerColor == crtColor ) ) {
        auto pos = sf::Vector2f( sf::Mouse::getPosition( window ) );
        if( !IsLeftMouseHeld ) {  //daca incepe o mutare cu mouseul
            IsLeftMouseHeld = true;
            if( gfx.isInWindow( pos ) ) {  //verificam sa nu fie mouseul in afara ferestrei
                // get the absolute coords
                auto coords = _tabla.view( Piesa::getCoordsFromPos( pos ) );
                // do these in absolute coords
                piesaTinuta = _tabla.getPiesa( coords );
                if( piesaTinuta != nullptr )  //daca am apasat pe o piesa, retinem vechea pozitie
                    if( piesaTinuta->getColor() == crtColor ) {
                        _tabla.setPointer( coords, nullptr );  //scoatem piesa de la locul ei
                        oldpos = piesaTinuta->getPos();
                    }
                    else
                        piesaTinuta = nullptr;
            }
        }
        if( piesaTinuta != nullptr )  //updatam pozitia piesei tinute, daca tinem vreuna
            piesaTinuta->moveTo( pos - sf::Vector2f( 32.0f, 32.0f ) );
    }
    else {
        sf::Vector2i oldcoords, coords;
        int          moveType;

        // verificam daca suntem la rand
        if( isSinglePlayer || multiplayerColor == crtColor ) {
            if( IsLeftMouseHeld ) {  // daca tocmai s-a terminat o miscare din mouse
                IsLeftMouseHeld = false;
                if( piesaTinuta != nullptr ) {  // daca am mutat o piesa
                    // get the absolute coords
                    oldcoords = _tabla.view( Piesa::getCoordsFromPos( oldpos ) );
                    coords    = _tabla.view( Piesa::getCoordsFromPos( piesaTinuta->getPos() + sf::Vector2f( 32.0f, 32.0f ) ) );

                    piesaTinuta->moveTo( oldpos );
                    _tabla.setPointer( oldcoords, piesaTinuta );
                    piesaTinuta = nullptr;

                    if( ( moveType = _tabla.verifyMoveWithCheck( oldcoords, coords ) ) & MV_VALID ) {
                        // facem mutarea
                        move( oldcoords, coords, moveType );

                        // transmitem mutarea la celalalt jucator
                        if( !isSinglePlayer ) {
                            sf::Packet packetSent;
                            packetSent << oldcoords.x << oldcoords.y << coords.x << coords.y << moveType;
                            tcpSocket.setBlocking( true );
                            // if connection is lost, return to menu
                            if( tcpSocket.send( packetSent ) == sf::Socket::Status::Disconnected )
                                connectionLost();
                        }
                    }
                }
            }
        }
        // asteptam mutare de la celalalt jucator
        else {
            sf::Packet packetReceived2;
            tcpSocket.setBlocking( false );
            sf::Socket::Status status = tcpSocket.receive( packetReceived2 );
            // daca am primit pachetul, reprezentam mutarea local
            if( status == sf::Socket::Status::Done ) {
                if( packetReceived2 >> oldcoords.x >> oldcoords.y >> coords.x >> coords.y >> moveType )
                    move( oldcoords, coords, moveType );
                // if packet is lost, return to menu
                else
                    connectionLost();
            }
            else
                // if connection is lost, return to menu
                if( status == sf::Socket::Status::Disconnected )
                connectionLost();
        }
    }
}
// main game loop
void Game::go( sf::RenderWindow& window )
{
    gfx.beginFrame();
    updateModel();
    composeFrame();
    gfx.endFrame();
}
// this should receive the real coordinates on the table (not the relative ones)
void Game::move( sf::Vector2i oldcoords, sf::Vector2i coords, int moveType )
{
    // get the relative coords
    sf::Vector2i viewoldcoords = _tabla.view( oldcoords ),
                 viewcoords    = _tabla.view( coords );

    // do these in absolute coords
    logMove( oldcoords, coords, moveType );
    _tabla.move( oldcoords, coords );

    // coloram patratele prin care se face mutarea
    if( patratInit == nullptr )
        patratInit = new SpriteObj( "Content/Patrat_initial.png", { 0, 0 }, { 2.0, 2.0 } );
    if( patratFinal == nullptr )
        patratFinal = new SpriteObj( "Content/Patrat_final.png", { 0, 0 }, { 2.0, 2.0 } );
    // do these in relative coords
    patratInit->moveTo( Piesa::getPosFromCoords( viewoldcoords ) );
    patratFinal->moveTo( Piesa::getPosFromCoords( viewcoords ) );

    // do these in absolute coords
    if( moveType & MV_CASTLING )  // rocada
        if( coords.x < 5 )        // rocada la stanga
            _tabla.move( sf::Vector2i( 1, coords.y ), sf::Vector2i( coords.x + 1, coords.y ) );
        else  // rocada la dreapta
            _tabla.move( sf::Vector2i( 8, coords.y ), sf::Vector2i( coords.x - 1, coords.y ) );
    else if( moveType & MV_PROMOTION ) {  // promotie
        _tabla.erase( coords );
        if( coords.y == 1 ) {
            Piesa* piesa = new Piesa( "Content/Piese/Regina_negru.png", viewcoords, Piesa::Piese::REGINA, Piesa::Color::NEGRU );
            _tabla.setPiesa( coords, piesa );
        }
        else {
            Piesa* piesa = new Piesa( "Content/Piese/Regina_alb.png", viewcoords, Piesa::Piese::REGINA, Piesa::Color::ALB );
            _tabla.setPiesa( coords, piesa );
        }
    }
    // play move sound
    std::string audioFile = crtColor == Piesa::Color::ALB ? "Content/Audio/whitemove.wav" : "Content/Audio/blackmove.wav";
    if( moveType & MV_CAPTURE )
        audioFile = "Content/Audio/capture.wav";
    if( !moveSoundBuffer.loadFromFile( audioFile ) )
        throw EXCEPT( "Cannot load file: " + audioFile );
    moveSound.setBuffer( moveSoundBuffer );
    moveSound.setVolume( 30 );
    moveSound.play();

    // switch turns or end the game
    if( _tabla.isInCheckMate( Piesa::otherColor( crtColor ) ) ) {
        isCheckMate = true;
        isFinished  = true;
        writeLog( crtColor == Piesa::Color::ALB ? "# 1-0" : "# 0-1" );
    }
    else if( _tabla.isInCheck( Piesa::otherColor( crtColor ) ) ) {
        writeLog( "+" );
        crtColor = Piesa::otherColor( crtColor );
    }
    else if( _tabla.isInStaleMate( Piesa::otherColor( crtColor ) ) ) {
        isStaleMate = true;
        isFinished  = true;
        writeLog( "1/2-1/2" );
    }
    else
        crtColor = Piesa::otherColor( crtColor );
}
// logs the move into pgn format
void Game::logMove( sf::Vector2i oldcoords, sf::Vector2i coords, int moveType )
{
    std::string moveString = _tabla.getMoveString( oldcoords, coords, moveType );
    auto        color      = _tabla.getPiesa( oldcoords )->getColor();

    if( color == Piesa::Color::ALB )
        pgnOutput << ' ' << ++round << '.';
    pgnOutput << ' ' << moveString;
}
// writes custom stream into the pgn file
void Game::writeLog( std::string output )
{
    pgnOutput << output;
}
// returns true if connection was established (forward port 50000 for server ok)
bool Game::establishConnection()
{
    system( "cls" );
    ShowWindow( GetConsoleWindow(), SW_SHOW );
    std::cout << "Enter IP or give the other player your IP to connect\n";
    std::cout << "To be able to receive incoming connections, you need to forward port 50000\n";
    std::cout << "Type \\connect <ip>, \\wait or \\close\n";
    std::string command, ip;
    bool        connecting = false;
    while( true ) {
        std::getline( std::cin, command );
        if( command.find( "\\connect " ) == 0 ) {
            connecting = true;
            ip         = command.substr( 9 );
            break;
        }
        else if( command == "\\wait" ) {
            break;
        }
        else if( command == "\\close" ) {
            ShowWindow( GetConsoleWindow(), SW_HIDE );

            return false;
        }
        else
            std::cout << "Unrecognized command " << command << '\n';
    }

    auto& window = gfx.getWindow();
    if( connecting ) {
        isServer = false;

        std::cout << "Connecting to host...\n";
        tcpSocket.setBlocking( true );
        sf::Socket::Status status = tcpSocket.connect( ip, 50000, sf::seconds( 5.0f ) );
        if( status != sf::Socket::Done ) {
            connectionLost();

            return false;
        }
        else {
            std::cout << "\nConnection successful! Starting game...\n";
            ShowWindow( GetConsoleWindow(), SW_HIDE );

            return true;
        }
    }
    else {
        isServer = true;

        if( tcpListener.listen( 50000 ) != sf::Socket::Status::Done ) {
            std::cout << "\nCannot listen to port 50000.\n";
            closeConnection();
            pressAnyKeyToReturnToMenu();

            return false;
        }

        std::cout << "Waiting for connection request...\nPress any key to abort and return to menu...\n";
        tcpListener.setBlocking( false );
        while( !_kbhit() )
            if( tcpListener.accept( tcpSocket ) == sf::Socket::Status::Done ) {
                std::cout << "\nConnection successful! Starting game...\n";
                ShowWindow( GetConsoleWindow(), SW_HIDE );

                return true;
            }
        // throw key away, and if it was a function key or arrow key, throw again !!!
        if( _getch() == 0xE0 )
            _getch();
        // if a key was pressed, return to menu
        ShowWindow( GetConsoleWindow(), SW_HIDE );

        return false;
    }
}
// call this to stop all the sounds
void Game::stopSounds()
{
    moveSound.stop();
    endSound.stop();
    endSoundPlaying = false;
}
