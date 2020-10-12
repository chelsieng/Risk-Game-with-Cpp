#pragma once

#include <iostream>
#include <vector>

#include "Orders.h"
#include "Cards.h"

using namespace std;

// Forward declaration due to circular dependency
class OrdersList;
class Territory;
class Order;
class Hand;


class Player {
private:
    static int counter;
    int pID;
    Hand* playerHand;
    OrdersList*  playerOrdersList;
    vector<Territory*>* playerTerritories;

public:
    Player(); // default Constructor
    Player(Hand* hand, OrdersList* ordersList, vector<Territory*>* territories); // parameterized Constructor
    Player(const Player &player); // copy constructor
    ~Player(); // destructor

    // Methods
    void issueOrder(Order* orderToIssue);
    vector<Territory*>* toDefend(vector<Territory*>* listToDefend);
    vector<Territory*>* toAttack(vector<Territory*>* listToAttack);
    int getId() const;
    OrdersList* getOrdersList();

    // assignment operator
    Player& operator = (const Player &player);

    // stream insertion operator (free function)
    friend ostream& operator << (ostream& ostream, const Player &player);
};
