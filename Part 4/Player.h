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
    OrderList*  playerOrderList;
    vector<Map::Territory*> playerTerritories;

public:
    Player(); // default Constructor
    Player(Hand hand, OrderList orderList, vector<Map::Territory*> territories); // parameterized Constructor
    Player(const Player &player); // copy constructor
    ~Player(); // destructor

    // Methods
    void issueOrder(Orders* orderToIssue);
    vector<Map::Territory*> toDefend();
    vector<Map::Territory*> toAttack();

    Player& operator = (const Player &player); // assignment operator

    // stream insertion operator (free function)
    friend ostream& operator << (ostream& ostream, const Player &player);
};
