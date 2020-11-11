#include <iostream>
#include <vector>

#include "Player.h"

using namespace std;

int Player::counter = 0;

// default constructor
Player::Player() :
        playerHand{nullptr},
        playerOrdersList{nullptr},
        playerTerritories{nullptr},
        pID{++counter}, // increasing player count
        reinforcementPool{0}
{}

// parameterized constructor
Player::Player(Hand* hand, OrdersList* OrdersList, vector<Territory*>* territories) {
    pID = ++counter; // increasing player count
    this->playerHand = hand;
    this->playerOrdersList = OrdersList;
    this->playerTerritories = territories;
    this->reinforcementPool = 0;
}

// copy constructor
Player::Player(const Player &playerCopy) {
    pID = ++counter; // increasing player count

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
    for (Territory* t : *this->playerTerritories) {
        delete t;
        t = nullptr;
    }
    delete this->playerTerritories;
    playerTerritories = nullptr;

    // copy using Territory copy constructor
    for (auto pt : *playerCopy.playerTerritories) {
        this->playerTerritories->push_back(new Territory(*pt));
    }
}

// destructor
Player::~Player() {

    // reducing the count of players created
    --counter;

    // free hand
    delete playerHand;
    playerHand = nullptr;

    // free OrdersList
    delete playerOrdersList;
    playerOrdersList = nullptr;

    // free territories
    for (Territory* t : *playerTerritories) {
        delete t;
        t = nullptr;
    }
    delete this->playerTerritories;
    playerTerritories = nullptr;
}

// Returning the player's ID
int Player::getId() const {
    return pID;
}

// Returning the player's order list
OrdersList* Player::getOrdersList() {
    return this->playerOrdersList;
}

// Returning the player's hand
Hand* Player::getHand() {
    return this->playerHand;
}

vector<Territory*>* Player::getPlayerTerritories(){
    return this->playerTerritories;
}

// Adding an order to the end of the player's order list
// A subclass of Order (order types) will be passed as a parameter.
void Player::issueOrder(Order* orderToIssue) {
    Order* newOrder = orderToIssue;
    this->playerOrdersList->addToLast(newOrder);
}

vector<Territory*>* Player::toDefend(vector<Territory*>* listToDefend) {
    // Returning territories to defend
    return listToDefend;
}

std::vector<Territory*>* Player::toAttack(vector<Territory*>* listToAttack) {
    // Returning territories to defend
    return listToAttack;
}

Player &Player::operator=(const Player& player) {

    // Checking for self assignment
    if (this == &player) {
        return *this;
    }

    pID = ++counter; // increasing player count

    // deleting existing pointers
    delete playerHand;
    playerHand = nullptr;

    delete playerOrdersList;
    playerOrdersList = nullptr;

    for (Territory* t : *playerTerritories) {
        delete t;
        t = nullptr;
    }
    delete playerTerritories;
    playerTerritories = nullptr;

    // creating a deep copy
    playerHand = new Hand(*player.playerHand);
    playerOrdersList = new OrdersList(*player.playerOrdersList);
    playerTerritories = new vector<Territory*>(*player.playerTerritories);

    return *this;
}

std::ostream &operator<<(ostream& out, const Player& player) {
    out << "PLAYER " << player.getId() << " HAND : " << endl;
    out << *player.playerHand << endl;
    out << "PLAYER " << player.getId() <<  " TERRITORIES : " << endl;
    for (auto terr : *player.playerTerritories) {
        out << *terr << endl;
    }
    out << "PLAYER " << player.getId() << " ORDERS : " << endl;
    out << *player.playerOrdersList << endl;
    out << "PLAYER " << player.getId() << " AVAILABLE (UNUSED) REINFORCEMENT : " << endl;
    out << player.reinforcementPool << endl;

    return out;
}

int Player::getReinforcementPool() const {
    return reinforcementPool;
}

void Player::setReinforcementPool(int i) {
    this->reinforcementPool = i;
}
