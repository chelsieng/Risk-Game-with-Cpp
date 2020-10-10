#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include "Map.h"

#include <iostream>
#include <vector>

using namespace std;

// default constructor
Player::Player() :
        playerHand{nullptr},
        playerOrdersList{nullptr},
        playerTerritories(std::vector<Map::Territory*>{nullptr})
{}

// parameterized constructor
Player::Player(Hand* hand, OrdersList* OrdersList, vector<Map::Territory*> territories) {
    this->playerHand = hand;
    this->playerOrdersList = OrdersList;
    this->playerTerritories = territories;
}

// copy constructor
Player::Player(const Player &playerCopy) {

    // HAND
    // deallocate
    delete this->playerHand;
    this->playerHand = nullptr;

    // copy using Hand copy constructor
    this->playerHand = new Hand(*playerCopy.playerHand);

    // ORDERS LIST
    // deallocate
    delete this->playerOrdersList;
    this->playerOrdersList = nullptr;

    // copy using Hand copy constructor
    this->playerOrdersList = new OrdersList(*playerCopy.playerOrdersList);

    // TERRITORIES
    // deallocate
    for (Map::Territory* t : this->playerTerritories) {
        delete t;
        t = nullptr;
    }

    // copy using Territory copy constructor
    for (auto pt : playerCopy.playerTerritories) {
        this->playerTerritories.push_back(new Map::Territory(*pt));
    }
}

// destructor
Player::~Player() {
    // free hand
    delete playerHand;
    playerHand = nullptr;

    // free OrdersList
    delete playerOrdersList;
    playerOrdersList = nullptr;

    // free territories
    for (Map::Territory* t : playerTerritories) {
        delete t;
        t = nullptr;
    }
}

// Adding an order to the end of the player's order list
// A subclass of Order (order types) will be passed as a parameter.
void Player::issueOrder(Order* orderToIssue) {
    Order* newOrder = orderToIssue;
    this->playerOrdersList->addToLast(newOrder);
}

vector<Map::Territory*> Player::toDefend() {

    // Creating two arbitrary territories
    // TODO
    Map::Territory* terrToDefend1 = new Map::Territory();
    Map::Territory* terrToDefend2 = new Map::Territory();

    // Adding them to a list
    vector<Map::Territory*> listToDefend;
    listToDefend.push_back(terrToDefend1);
    listToDefend.push_back(terrToDefend2);

    // Returning territories to defend
    return listToDefend;
}

std::vector<Map::Territory*> Player::toAttack() {
    // Creating two arbitrary territories
    // TODO
    Map::Territory* terrToAttack1 = new Map::Territory();
    Map::Territory* terrToAttack2 = new Map::Territory();

    // Adding them to a list
    vector<Map::Territory*> listToAttack;
    listToAttack.push_back(terrToAttack1);
    listToAttack.push_back(terrToAttack2);

    // Returning territories to defend
    return listToAttack;
}

Player &Player::operator=(const Player& player) {

    // Checking for self assignment
    if (this == &player) {
        return *this;
    }

    // deleting existing pointers
    delete playerHand;
    playerHand = nullptr;

    delete playerOrdersList;
    playerOrdersList = nullptr;

    for (Map::Territory* t : playerTerritories) {
        delete t;
        t = nullptr;
    }

    playerHand = new Hand(*player.playerHand);
    playerOrdersList = new OrdersList(*player.playerOrdersList);

    // I cant implement this yet, I am missing a constructor for Territories
//    playerTerritories = new Map::Territory(player.playerTerritories);

    return *this;
}

std::ostream &operator<<(ostream& out, const Player& player) {
    out << "Player hand : " << &player.playerTerritories << endl;
    out << "Player hand : " << player.playerHand << endl;
    out << "Player hand : " << player.playerOrdersList << endl;
}
