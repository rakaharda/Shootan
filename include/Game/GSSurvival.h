#ifndef GSSURVIVAL_H
#define GSSURVIVAL_H

#include "Game/GameState.h"
#include "Game/SurvivalStates.h"
#include <list>
//*Field size 3840x2160 (2 times FullHD)

class GSSurvival : public GameState, public Collision
{
public:
    GSSurvival(VideoSettings *_videoSettings);
    virtual ~GSSurvival();
    GameStates update();
    void draw();
    void handleEvents(sf::Event _event);
private:
    Player*         player;
    sf::Sprite      background;
    sf::IntRect     fieldSize;
    sf::View        view;
    SurvivalStates  *survivalState;
    PauseMenu       *pauseMenu;
    GameOverMenu    *gameOverMenu;
    VideoSettings   *videoSettings;
    EnemyFactory    *enemyFactory;
    vector <Enemy*> vecEnemies;
    vector <EntityDestroyer> vecDestroyers;
    HealthBar       *healthBar;
    AmmoBar         *ammoBar;
    LvlBar          *lvlBar;
    PerkMenu        *perkMenu;
    list<sf::Sound> sounds;
    float           bgColorRed;
    float           bgColorGreen;
    float           bgColorBlue;
    float           colorAmplifier;
    char            redModifier;
    char            greenModifier;
    char            blueModifier;
    float           scaleAmplifier;
    void updateStats();
    void updateEntities();
    void loadResources();
    void collectTrash();
    void checkProjectiles();
    void checkMelee();
    void checkPerks();
    void checkDestroyers();
    void updateView();
    void updateListener();
    void updateMusic();
    void updateFactories();
    void updateBackground();
    int k; //need for different perks( need rewrite)
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
