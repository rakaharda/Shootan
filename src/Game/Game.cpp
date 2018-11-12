#include "Game/Game.h"
#include <iostream>
Game::Game() : isPlaying(true)
{
    //Loading settings
    videoSettings = new VideoSettings;
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
    gameState = GS_GAMEMODE_SURVIVAL;
    if(gameState == GS_GAMEMODE_SURVIVAL)
        currentGameState = new GSSurvival(videoSettings);
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
        delete(currentGameState);
        gameState = updatedGameState;
        switch(gameState)
        {
            case GameStates::GS_GAMEMODE_SURVIVAL:
                currentGameState = new GSSurvival(videoSettings);
                break;
            default:
        }
    }
}

void Game::draw()
{
    window.clear();
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
}
