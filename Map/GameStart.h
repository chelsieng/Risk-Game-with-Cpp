#include <climits>

#ifndef COMP_345_GAMESTART_H
#define COMP_345_GAMESTART_H

#include "Map.h"

Map *mapGame; // map graph to share among other compilation unit
vector<Player *> players; // vector storing all players for the game

class GameStart {
public:
    static bool selectMap(int); // Function to load selected map file
    static vector<Player *> createPlayers(int); // Function to create players for the game
    static Deck *createDeck(); //Function to create the deck of cards for the game

};


#endif //COMP_345_GAMESTART_H
