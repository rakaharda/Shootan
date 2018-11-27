#ifndef GSSURVIVAL_H
#define GSSURVIVAL_H

#include "Game/GameState.h"
#include "Game/SurvivalStates.h"

//*Field size 3840x2160 (2 times FullHD)

class GSSurvival : public GameState, public Collision
{
public:
    GSSurvival(VideoSettings *_videoSettings);
    virtual ~GSSurvival();
    GameStates update();
    void draw();
    void handleEvents(sf::Event _event);
protected:
    Player*         player;
    sf::Sprite      background;
    sf::Text        info;
    sf::IntRect     fieldSize;
    sf::View        view;
    SurvivalStates *survivalState;
    PauseMenu        *pauseMenu;
    GameOverMenu     *gameOverMenu;
    VideoSettings   *videoSettings;
    EnemyFactory    *enemyFactory;
    vector <Enemy*> vecEnemies;
    vector <EntityDestroyer> vecDestroyers;
    HealthBar       *healthBar;
    AmmoBar         *ammoBar;
    LvlBar          *lvlBar;
    PerkMenu        *perkMenu;
    void updateStats();
    void loadResources();
    void collectTrash();
    void checkProjectiles();
    void checkMelee();
    void checkPerks();
    void checkDestroyers();
    void updateView();
    void updateListener();
    int k; //need for different perks( need rewrite)
private:
    bool offanimation=0;
    float ianimation=1.f;
    void checkPerkMenu();
    float reloadAnimation=0.2f;
};

extern sf::RenderWindow     window;
extern float                frameTime;
extern vector <Projectile*> vecProjectiles;
extern vector <Perk*>       vecPerks;
extern ResourceManager      *resources;
extern AudioSettings        *audioSettings;
#endif // GSSURVIVAL_H
