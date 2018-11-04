#ifndef GSSURVIVAL_H
#define GSSURVIVAL_H

#include "Game/GameState.h"


class GSSurvival : public GameState, public Collision
{
public:
    GSSurvival(VideoSettings *_videoSettings);
    virtual ~GSSurvival();
    void update();
    void draw();
    void handleEvents(sf::Event _event);
protected:
    Player*         player;
    sf::Sprite      background;
    sf::Text        info;
    sf::IntRect     fieldSize;
    sf::View        view;
    MainMenu        *menu;
    VideoSettings   *videoSettings;
    ResourceManager *resources;
    bool            openMainMenu;
    void updateStats();
    void loadResources();
    void collectTrash();
    void checkProjectiles();
    void checkEnemies();
    void checkPerks();
    void updateView();
    int k; //need for different perks( need rewrite)
private:
};

extern sf::RenderWindow     window;
extern float                frameTime;
extern vector <sf::Texture> vecTextures;
extern vector <Projectile*> vecProjectiles;
extern vector <Enemy*>      vecEnemies;
extern vector <Perk*>       vecPerks;

#endif // GSSURVIVAL_H
