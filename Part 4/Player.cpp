#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include <iostream>
#include <vector>

using namespace std;

// default constructor
Player::Player() :
        playerHand{nullptr},
        playerOrderList{nullptr},
        playerTerritories(std::vector<Map::Territory*>{nullptr})
{}

// parameterized constructor
Player::Player(Hand hand, OrderList orderList, vector<Map::Territory*> territories) {
    this->playerHand = &hand;
    this->playerOrderList = &orderList;
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

    // ORDERLIST
    // deallocate
    delete this->playerOrderList;
    this->playerOrderList = nullptr;

    // copy using Hand copy constructor
    this->playerOrderList = new OrderList(*playerCopy.playerOrderList);

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

    // free OrderList
    delete playerOrderList;
    playerOrderList = nullptr;

    // free territories
    for (Map::Territory* t : playerTerritories) {
        delete t;
        t = nullptr;
    }
}

//TODO
//void Player::issueOrder(std::string orderType) {
//    Orders newOrder = new Orders();
//    this->playerOrderList.push_back(newOrder);
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
    delete playerOrderList;
    for (Map::Territory* t : playerTerritories) {
        delete t;
        t = nullptr;
    }

    playerHand = new Hand(*player.playerHand);
    playerOrderList = new OrderList(*player.playerOrderList);
    //TODO
    //playerTerritories = new Map::Territory();

    return *this;
}

std::ostream &operator<<(ostream& out, const Player& player) {
    out << "Player hand : " << &player.playerTerritories << endl;
    out << "Player hand : " << player.playerHand << endl;
    //TODO
//    out << "Player hand : " << player.playerOrderList << endl;
}
