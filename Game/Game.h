#include "../Map/MapEditorCLI.h"
#include "../Character/CharUI.h"
#include "../Dice/Dice.h"
#include "../Observer/Logger.h"
#include "../Character/CharacterBuilder.cpp"
#include "../Character/Character.h"


//class Enemy; // remove when jackson makes this


class Game {
public:
    Game();
    ~Game();
    bool load(string campaign_name);
    bool save();
    void startGameLoop();
    void addCharacter();
private:
    Campaign* campaign;
    Map* map;
    std::list<Character> characters;
    //std::list<Enemy> enemies;
    void userTurn(Character* character);
    //void enemyTurn(Enemy* enemy);
    Dice d20;
};
