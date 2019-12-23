#include "Game/GSMPHost.h"

GSMPHost::GSMPHost(VideoSettings *_videoSettings)
{
    //Setting up the connection
    status = sf::Socket::NotReady;
    setupSettings(_videoSettings);
    player = new Player;
    player->setBorders(2000.f, 2000.f);
    //client.setBlocking(false);
    listener.setBlocking(false);
    unsigned port = 2000;
    cout << "Listenning port " << port << endl;
    if(listener.listen(port) != sf::Socket::Done)
    {
        cout << "Cannot listen port " << port << endl;
    }
}

void GSMPHost::connect()
{
    unsigned port = 2000;
    sf::SocketSelector selector;
    selector.add(listener);
    cout << "Waiting for user to connect." << endl;
        if(listener.accept(client) != sf::Socket::Done)
        {
            cout << "Cannot connect client!" << endl;
        }
        else
        {
            cout << "Client connected!" << endl;
            sf::Packet readyPacket;
            client.setBlocking(false);
            client.receive(readyPacket);
            string msg;
            readyPacket >> msg;
            if(msg == "ready")
            {
                status = sf::Socket::Done;
                client.setBlocking(true);
                listener.setBlocking(true);
                cout << "Starting game!";
            }
        }
}

void GSMPHost::setupSettings(VideoSettings *_videoSettings)
{
    fieldSize = sf::IntRect(0, 0, 2000, 2000);
    videoSettings = _videoSettings;
    view.setSize(videoSettings->width, videoSettings->height);
    view.setCenter(fieldSize.width / 2, fieldSize.height / 2);
    loadResources();
    playerClient = new PlayerClient;
    background.setTexture(resources->getTexture("backgroundTile"));
    background.setTextureRect(fieldSize);
    background.setOrigin(fieldSize.width / 2, fieldSize.height / 2);
    background.setPosition(fieldSize.width / 2, fieldSize.height / 2);
    vecObstacles.reserve(20);
    vecObstacles.push_back(new Wall(200,670,0));
    vecObstacles.push_back(new Wall(200,1330,0));
    vecObstacles.push_back(new Wall(1800,670,0));
    vecObstacles.push_back(new Wall(1800,1330,0));

    vecObstacles.push_back(new Wall(500,400,2));
    vecObstacles.push_back(new Wall(500,1600,2));
    vecObstacles.push_back(new Wall(1500,400,2));
    vecObstacles.push_back(new Wall(1500,1600,2));
    vecObstacles.push_back(new Wall(1000,1000,2));
}

sf::Socket::Status GSMPHost::getStatus()
{
    return status;
}

void GSMPHost::updateView(GameObject* obj)
{
    view.setCenter(obj->getSprite().getPosition().x, obj->getSprite().getPosition().y);
    if(view.getCenter().x < window.getSize().x / 2)
        view.setCenter(window.getSize().x / 2, view.getCenter().y);
    else if(view.getCenter().x > fieldSize.width - (window.getSize().x / 2))
        view.setCenter(fieldSize.width - (window.getSize().x / 2), view.getCenter().y);
    if(view.getCenter().y < window.getSize().y / 2)
        view.setCenter(view.getCenter().x, window.getSize().y / 2);
    else if(view.getCenter().y > fieldSize.height - (window.getSize().y / 2))
        view.setCenter(view.getCenter().x, fieldSize.height - (window.getSize().y / 2));
}

GSMPHost::~GSMPHost()
{
    //dtor
}

GameStates GSMPHost::update()
{
    if(status != sf::Socket::Done)
    {
        connect();
    }
    else
    {
        ClientEvents event;
        sf::Packet incomingPacket, outgoingPacket;
        client.receive(incomingPacket);
        incomingPacket >> event;
        playerClient->update(event);
        playerClient->setOrientation(event.angle);
        player->update();
        for(unsigned int i = 0; i < vecProjectiles.size(); i++)
            vecProjectiles[i]->update();
        checkObstacles();
        outgoingPacket << playerClient->getSpritePointer()->getPosition().x << playerClient->getSpritePointer()->getPosition().y  <<
                        player->getSpritePointer()->getPosition().x << player->getSpritePointer()->getPosition().y << player->getSpritePointer()->getRotation() << sf::Mouse::isButtonPressed(sf::Mouse::Left);
        client.send(outgoingPacket);
        updateView(player);
        return GameStates::GS_GAMEMODE_MPHOST;
    }


}

void GSMPHost::handleEvents(sf::Event _event)
{

}

void GSMPHost::loadResources()
{
    //*Fonts
    resources->addFont("arial", "./data/fonts/arial.ttf");
    //*Textures
        //Background
    resources->addTexture("backgroundTile", "./data/background/tile1.png", true);
        //Obstacles
    resources->addTexture("obstacles_wall", "./data/Obstacles/Wall.png");
    resources->addTexture("obstacles_death_zone", "./data/Obstacles/Death_zone.png");
        //Projectiles
    resources->addTexture("projectile_1",   "./data/projectiles/projectile1_test.png");
    resources->addTexture("projectile_2",   "./data/projectiles/projectile2.png");
        //Enemies
    resources->addTexture("default_enemy",  "./data/enemies/default_enemy.png");
    resources->addTexture("enemy_melee",    "./data/enemies/enemy_melee.png");
    resources->addTexture("enemy_range",    "./data/enemies/enemy_range.png");
    resources->addTexture("destroyer_bar",  "./data/enemies/destroyer_bar.png", true);
        //Perks
    resources->addTexture("perk_cross",     "./data/perks/perk_cross.png");
    resources->addTexture("perk_speedup",   "./data/perks/perk_speedup.png");
    resources->addTexture("perk_frost",     "./data/perks/Blue.png");
    resources->addTexture("perk_fire",      "./data/perks/Red.png");
    resources->addTexture("perk_weapon",    "./data/perks/perk_weapon.png");
        //GUI
    resources->addTexture("healthbar_frame",           "./data/GUI/gameInterface/healthbar_frame.png");
    resources->addTexture("healthbar_cells",           "./data/GUI/gameInterface/healthbar_cells.png");
    resources->addTexture("projectiles_scale_default", "./data/GUI/gameInterface/projectiles_scale_default.png");
    resources->addTexture("projectiles_scale_fire",    "./data/GUI/gameInterface/projectiles_scale_fire.png");
    resources->addTexture("projectiles_scale_freeze",  "./data/GUI/gameInterface/projectiles_scale_freeze.png");
    resources->addTexture("projectiles_scale_double",  "./data/GUI/gameInterface/projectiles_scale_double.png");
    resources->addTexture("projectiles_edge",          "./data/GUI/gameInterface/projectiles_edge.png");
    resources->addTexture("lvlbar_frame",              "./data/GUI/gameInterface/lvlbar_frame.png");
    resources->addTexture("lvlbar_cells",              "./data/GUI/gameInterface/lvlbar_cells.png");
    resources->addTexture("lvlbar_animation",          "./data/GUI/gameInterface/lvlbar_animation.png");
    resources->addTexture("lvlbar_lvlup",              "./data/GUI/gameInterface/lvlbar_lvlup.png");
    //*Numbers
    resources->addTexture("score_number_0", "./data/GUI/gameInterface/numbers/score_number_0.png");
    resources->addTexture("score_number_1", "./data/GUI/gameInterface/numbers/score_number_1.png");
    resources->addTexture("score_number_2", "./data/GUI/gameInterface/numbers/score_number_2.png");
    resources->addTexture("score_number_3", "./data/GUI/gameInterface/numbers/score_number_3.png");
    resources->addTexture("score_number_4", "./data/GUI/gameInterface/numbers/score_number_4.png");
    resources->addTexture("score_number_5", "./data/GUI/gameInterface/numbers/score_number_5.png");
    resources->addTexture("score_number_6", "./data/GUI/gameInterface/numbers/score_number_6.png");
    resources->addTexture("score_number_7", "./data/GUI/gameInterface/numbers/score_number_7.png");
    resources->addTexture("score_number_8", "./data/GUI/gameInterface/numbers/score_number_8.png");
    resources->addTexture("score_number_9", "./data/GUI/gameInterface/numbers/score_number_9.png");
    //*For button
    resources->addTexture("buttonLVL",      "./data/GUI/perkMenu/ilvl.png");
    resources->addTexture("mainBackground", "./data/GUI/MainMenu/mainBackground.png");
    //*Sound buffers
    resources->addSoundBuffer("laser1",  "./data/sounds/laser1.wav");
    resources->addSoundBuffer("destroy", "./data/sounds/destroy.wav");
    //*Music
    resources->addMusic("GXRCH - HARD", "./data/music/act.ogg");
}
void GSMPHost::checkObstacles()
{
    for(unsigned int i = 0; i < vecObstacles.size(); i++)
    {
        if(checkCollision(player, vecObstacles[i]))
        {
            vecObstacles[i]->smash(player);
        }
        if(checkCollision(playerClient, vecObstacles[i]))
        {
            vecObstacles[i]->smash(playerClient);
        }
        for(unsigned int j = 0; j < vecProjectiles.size(); j++)
        {
            if(checkCollision(vecProjectiles[j], vecObstacles[i]) && !(vecObstacles[i]->passability))
            {
                vecProjectiles[j]->markToDelete();
                if(vecProjectiles[j]->toDelete())
                    vecProjectiles.erase(vecProjectiles.begin()+j);
            }
        }
    }
}

void GSMPHost::draw()
{
    window.setView(view);
    window.draw(background);
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
        window.draw(*vecProjectiles[i]);
    for(unsigned int i = 0; i < vecObstacles.size(); i++)
        window.draw(*vecObstacles[i]);
    window.draw(*playerClient);
    window.draw(*player);
}
