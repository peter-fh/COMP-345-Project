#include "../Map/MapEditorCLI.h"
#include "../Character/CharUI.h"
#include "../Dice/Dice.h"
#include "../Observer/Logger.h"
#include "../Character/CharacterBuilder.cpp"
#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/Combat.h"
#include "../Enemy/Corpse.h"




class Game {
public:
    Game();
    bool loadCampaign(string campaign_name);
    bool loadNextMap();
    bool save();
    void startGameLoop();
    void addCharacter();
private:

    int map_index;
    Campaign campaign; Map map;

    Character player;
    std::vector<Enemy> enemies;
    std::vector<Chest> chests;
    std::vector<Corpse> corpses;
    
    bool insertCharacters();
    bool insertEnemies(int num_enemies);
    bool insertChests(int num_chests);
    void insertCorpses();
    void userTurn(Character& character);
    void userMove(Character& character);
    void userAttack(Character& character);
    void userLoot(Chest& chest);
    void enemyTurn(Enemy& enemy);
    bool moveEnemy(Enemy& enemy);
    bool moveEnemyOneSquare(int dx, int dy, Enemy& enemy, Map& map);
    void initiativePhase();
    void movementPhase();
    void gameLoop();
    void displayCurrentMap();
    bool gameIsPlaying();
    vector<Enemy> enemiesNearby(Character& character);
    vector<Chest> chestsNearby(Character& character);
    bool moveOneSquare(int dx, int dy, Character& character, Map& map, bool& done);
    bool moveTo(int x, int y, Character& character, Map& map, int& spaces, bool& done);

    //void enemyTurn(Enemy* enemy);
    Dice d20;
    Dice d10;
    Dice d6;

    class MapMaker{
    public:
	Map makeMap1();
	Map makeMap2();
    };
};
