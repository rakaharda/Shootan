#include "Game/Game.h"
#include <iostream>
Game::Game() : isPlaying(true)
{
    //Loading settings
    videoSettings = new VideoSettings;
    audioSettings = new AudioSettings;
    resources = new ResourceManager;
    loadSettings();
    //Setting up window
    if(videoSettings->fullscreen)
        window.create(sf::VideoMode(videoSettings->width, videoSettings->height), "Shootan", sf::Style::Fullscreen);
    else
        window.create(sf::VideoMode(videoSettings->width, videoSettings->height), "Shootan");
    if (videoSettings->vsync)
        window.setVerticalSyncEnabled(true);
    else
        window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(videoSettings->framerateLimit);
    loadResources();

    //if(gameState == GS_MAINMENU)
    currentGameState = new GSMainMenu(videoSettings); //default
        //currentGameState = new GSSurvival(videoSettings);
}

Game::~Game()
{
    delete(gameClock);
    delete(videoSettings);
    delete(currentGameState);
}

void Game::play()
{
    srand(clock());
    gameClock = new sf::Clock;
    cout << "Starting main game loop"<<endl;
    while (isPlaying)
    {
        frameTime = gameClock->restart().asSeconds();
        handleEvents();
        update();
        draw();
    }
}

void Game::handleEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
    currentGameState->handleEvents(event);
        switch(event.type)
        {
        case sf::Event::Closed:
            window.close();
            isPlaying = false;
            return;
        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
            default:
                break;
            }
        default:
            break;
        }
    }
}

void Game::update()
{
    fpsCounter.update();
    GameStates updatedGameState;
    updatedGameState = currentGameState->update();
    if(updatedGameState != gameState)
    {
        gameState = updatedGameState;
        switch(gameState)
        {
            case GameStates::GS_MAINMENU:
                delete(currentGameState);
                currentGameState = new GSMainMenu(videoSettings);
                break;
            case GameStates::GS_GAMEMODE_SURVIVAL:
                delete(currentGameState);
                currentGameState = new GSSurvival(videoSettings);
                break;
            case GameStates::GS_GAMEMODE_MPHOST:
                delete(currentGameState);
                currentGameState = multiplayerState;
                break;
            case GameStates::GS_GAMEMODE_MPCLIENT:
                delete(currentGameState);
                currentGameState = multiplayerState;
                break;
            case GameStates::GS_RESTART:
                delete(currentGameState);
                currentGameState = new GSSurvival(videoSettings);
                gameState = GameStates::GS_GAMEMODE_SURVIVAL;
                break;
            case GameStates::GS_ENDGAME:
                isPlaying = false;
                window.close();
                break;
            default:
                break;
        }
    }
}

void Game::draw()
{
    window.clear();
    cout << currentGameState << endl;
    currentGameState->draw();
    //* UI
    window.setView(window.getDefaultView());
    window.draw(fpsCounter);
    window.display();
}

void Game::loadResources()
{
    font.loadFromFile("./data/fonts/arial.ttf");
}

void Game::loadSettings()
{
    videoSettings->loadSettings();
    audioSettings->loadSettings();
}
