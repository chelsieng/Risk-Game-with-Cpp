#pragma once

#include "Cards.h"
#include "Orders.h"
#include "Map.h"

class Player {
private:
    Hand* playerHand;
    std::vector<Orders*> playerOrders;
    std::vector<Territory*> playerTerritories{};

public:
    Player(); // default Constructor
    Player(Hand hand, std::vector<Orders*> orders, std::vector<Territory*> territories); // parameterized Constructor
    Player(const Player &player); // copy constructor
    ~Player(); // destructor

    void issueOrder(std::string orderType);
    std::vector<Territory*>toDefend();
    std::vector<Territory*>toAttack();

    Player& operator = (const Player &player); // assignment operator

    // stream insertion operator (free function)
    friend std::ostream& operator << (std::ostream& ostream, const Player &player);
};
