#include "../Map/MapEditorCLI.h"
#include "../Character/CharUI.h"
#include "../Dice/Dice.h"
#include "../Observer/Logger.h"
#include "../Character/CharacterBuilder.cpp"
#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/Combat.h"
#include "../Enemy/Corpse.h"
#include "../Item/Key.h"




class Game {
public:
    Game();
    bool loadCampaign();
    bool loadCampaign(string campaign_name);
    bool loadNextMap();
    bool save();
    void startGameLoop();
    void addCharacter();

    void saveGame(string filename);
    static Game loadGame(string filename);


private:

    int map_index;
    Campaign campaign; Map map;

    Character player;
    std::vector<Enemy> enemies;
    std::vector<Chest> chests; //no chests
    std::vector<Corpse> corpses;
    void combat(Enemy& enemy);    
    bool insertCharacters();
    bool insertEnemies(int num_enemies);
    bool insertBags(int num_bags);
    void insertCorpses();
    void userTurn(Character& character);
    void userMove(Character& character, int& roll);
    void userAttack(Character& character);
    void userLoot(Chest& chest);
    void userLoot(Corpse& corpse);
    void enemyTurn(Enemy& enemy);
    bool moveEnemy(Enemy& enemy);
    void addKey();
    bool moveEnemyOneSquare(int dx, int dy, Enemy& enemy, Map& map);
    void initiativePhase();
    void movementPhase();
    void gameLoop();
    void displayCurrentMap();
    bool gameIsPlaying();
    vector<Enemy> enemiesNearby(Character& character);
    vector<Chest> chestsNearby(Character& character);
    vector<Corpse> corpseNearby();
    bool moveOneSquare(int dx, int dy, Character& character, Map& map, bool& done);
    bool moveTo(int x, int y, Character& character, Map& map, int& spaces, bool& done);


    //void enemyTurn(Enemy* enemy);
    bool hasKey;
    Dice d20;
    Dice d10;
    Dice d6;

    class MapMaker{
    public:
	Map makeMap1();
	Map makeMap2();
    };
};
