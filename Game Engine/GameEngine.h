#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>
#include <unistd.h>
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"


using namespace std;

//Map *mapGame; // map graph to share among other compilation unit
//vector<Player *> *players; // vector storing all players for the game
// this is the GameEngine class, it will have number of players who will have armies. Also, territories assigned to only and only one player.


class GameEngine {
private:
    static string phase;
public:
    static Map* selectMap(int); // Function to load selected map file
    static vector<Player *> *createPlayers(int); // Function to create players for the game
    static Deck *createDeck(); //Function to create the deck of cards for the game
    static void startupPhase(vector<Player *> *, vector<Territory *> *);
    string getPhase(){return phase;}

 //   static void reinforcementPhase(vector<Player *> *, vector<Continent *> *);
 //   static void orderIssuingPhase(vector<Player*> *thePlayers, Map* theMap);
       static void reinforcementPhase(vector<Player *> *thePlayers, vector<Continent *> * theContinents);
       static void orderIssuingPhase(vector<Player*> *thePLayers, Map* theMap);
       static void orderExecutionPhase(vector<Player*> *thePlayers);
       static void mainGameLoop(vector<Player *> *thePlayers, vector<Continent *> * theContinents, Map* theMap);

};

#endif




