#pragma once

#include "Cards.h"
#include "Orders.h"
#include "Map.h"
#include <iostream>
#include <vector>

using namespace std;

class Player {
private:
    Hand* playerHand;
    OrdersList*  playerOrdersList;
    vector<Map::Territory*>* playerTerritories;

public:
    Player(); // default Constructor
    Player(Hand* hand, OrdersList* ordersList, vector<Map::Territory*>* territories); // parameterized Constructor
    Player(const Player &player); // copy constructor
    ~Player(); // destructor

    // Methods
    void issueOrder(Order* orderToIssue);
    vector<Map::Territory*>* toDefend();
    vector<Map::Territory*>* toAttack();

    // assignment operator
    Player& operator = (const Player &player);

    // stream insertion operator (free function)
    friend ostream& operator << (ostream& ostream, const Player &player);
};
