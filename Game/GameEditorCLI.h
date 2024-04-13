#include "Game.h"

class GameEditorCLI{
public:
    GameEditorCLI();
    void attatchGame(Game*);
    void gameEditorLoop();
    Game saveGame();
    Game loadGame();

private:
    Game game;
};
