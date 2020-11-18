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
#include "GameObservers.h"


using namespace std;

//Map *mapGame; // map graph to share among other compilation unit
//vector<Player *> *players; // vector storing all players for the game
// this is the GameEngine class, it will have number of players who will have armies. Also, territories assigned to only and only one player.

class GameEngine : public Subject{
private:
    string phase;
    int playerTurn;
public:
    PhaseObserver* phaseObserver;
    StatisticsObserver* statisticsObserver;
    GameEngine();
    ~GameEngine();
    string getPhase();
    Map* selectMap(int); // Function to load selected map file
    vector<Player *> *createPlayers(int); // Function to create players for the game
    Deck *createDeck(); //Function to create the deck of cards for the game
    void startupPhase(vector<Player *> *, vector<Territory *> *);


 //   static void reinforcementPhase(vector<Player *> *, vector<Continent *> *);
 //   static void orderIssuingPhase(vector<Player*> *thePlayers, Map* theMap);
       void reinforcementPhase(vector<Player *> *thePlayers, vector<Continent *> * theContinents);
       void orderIssuingPhase(vector<Player*> *thePLayers, Map* theMap);
       void orderExecutionPhase(vector<Player*> *thePlayers);
       void mainGameLoop(vector<Player *> *thePlayers, vector<Continent *> * theContinents, Map* theMap);

};




