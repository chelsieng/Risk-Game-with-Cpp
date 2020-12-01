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
    string conqTerr;
    int eliminatedPlayer;
    int issueRound;
    int issueResponse;
    bool isPhase;
    bool isStatistics;
    Player* curr_player;
    vector<Player*>* totalPlayers;
    Map *currMap;
public:
    PhaseObserver* phaseObserver;
    StatisticsObserver* statisticsObserver;
    GameEngine();
    ~GameEngine();
    string getPhase();
    int getPlayerTurn();
    string getConqTerr();
    int getEliminatedPLayer();
    Player* getCurrPlayer();
    Map* getMap();
    int getIssueRound();
    vector<Player*>* getTotalPlayers();
    int getIssueResponse();
    void setIssueResponse(int);
    void setPlayerTurn(int);
    Map* selectMap(); // Function to load selected map file
    vector<Player *> *createPlayers(); // Function to create players for the game
    Deck *createDeck(); //Function to create the deck of cards for the game
    void gameStart(GameEngine *g);
    void startupPhase(vector<Player *> *, vector<Territory *> *);
    void reinforcementPhase(vector<Player *> *thePlayers, vector<Continent *> * theContinents);
    void orderIssuingPhase(vector<Player*> *thePLayers, Map* theMap);
    void orderExecutionPhase(vector<Player*> *thePlayers);
    void mainGameLoop(vector<Player *> *thePlayers, vector<Continent *> * theContinents, Map* theMap);

};




