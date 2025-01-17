#pragma once

#include <iostream>
#include <vector>

#include "Orders.h"
#include "Cards.h"
#include "PlayerStrategies.h"

using namespace std;

// Forward declaration due to circular dependency
class OrdersList;
class Territory;
class Order;
class Hand;
class Map;
class PlayerStrategy;


class Player {
private:
    static int counter;
    int pID;
    Hand* playerHand;
    OrdersList*  playerOrdersList;
    vector<Territory*>* playerTerritories;
    int reinforcementPool;
    bool hasConquered = false;              // Showing whether or this player has conquered a territory in that round
    PlayerStrategy *playerStrategy; //this has to be a pointer since PlayerStrategy is an abstract class
                                        //(and we'll be using polymorphism and changing the strategy so makes more sense)

public:
    Player(); // default Constructor
    Player(Hand* hand, OrdersList* ordersList, vector<Territory*>* territories); // parameterized Constructor
    Player(const Player &player); // copy constructor
    ~Player(); // destructor

    // Methods
    void issueOrder(Order* orderToIssue);
    vector<Territory*> toDefend(Map* theMap, Player *player);
    vector<Territory*> toAttack(Map* theMap, Player *player);
    int getId() const;
    int getReinforcementPool() const;
    void setReinforcementPool(int i);
    Hand* getHand();
    OrdersList* getOrdersList();
    vector<Territory*>* getPlayerTerritories();
    vector<Territory*> AttackAble(Map* theMap);
    bool issueOrder(Map* theMap, vector<Player*>* thePlayers, int choice, Player* player);
    void setConquered(bool status) { this->hasConquered = status; }
    bool getConquered() { return this->hasConquered; }
    void removeTerritory(Territory *t);
    void addTerritory(Territory *t) { this->playerTerritories->push_back(t); }
    void setPlayerStrategy(PlayerStrategy* p);
    PlayerStrategy* getPlayerStrategy();
    // assignment operator
    Player& operator = (const Player &player);

    // stream insertion operator (free function)
    friend ostream& operator << (ostream& ostream, const Player &player);

};