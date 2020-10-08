#include "Player.h"
#include "Cards.h"

// default constructor
Player::Player() :
        playerHand{nullptr},
        playerOrders(std::vector<Orders*>{nullptr}),
        playerTerritories(std::vector<Territory*>{nullptr})
{}

// parameterized constructor
Player::Player(Hand hand, std::vector<Orders> orders, std::vector<Territory> territories) : playerHand{&hand} {
    for (auto o : orders) {
        playerOrders.push_back(&o);
    }

    for (auto t : territories) {
        playerTerritories.push_back(&t);
    }
}

// copy constructor
Player::Player(const Player &source) {

    // HAND
    // deallocate
    delete this->playerHand;
    this->playerHand = nullptr;

    // copy using Hand copy constructor
    this->playerHand = new Hand(*source.playerHand);

    // ORDER
    // deallocate
    for (Orders* o : this->playerOrders) {
        delete o;
        o = nullptr;
    }

    // copy using Order copy constructor
    for (int i = 0; i < source.playerOrders.size(); i++) {
        this->playerOrders.push_back(new Orders(*source.playerOrders.at(i)));
    }

    // TERRITORIES
    // deallocate
    for (Territory* t : this->playerTerritories) {
        delete t;
        t = nullptr;
    }

    // copy using Territory copy constructor
    for (int i = 0; i < source.playerTerritories.size(); i++) {
        this->playerTerritories.push_back(new Territory(*source.playerTerritories.at(i)));
    }
}

// destructor
Player::~Player() {
    // free hand
    delete playerHand;
    playerHand = nullptr;

    // free orders
    for (Orders* o : playerOrders) {
        delete o;
        o = nullptr;
    }

    // free territories
    for (Territory* t : playerTerritories) {
        delete t;
        t = nullptr;
    }
}

Player::Player(Hand hand, std::vector<Orders *> orders, std::vector<Territory *> territories) {

}

void Player::issueOrder(std::string orderType) {

}

std::vector<Territory *> Player::toDefend() {
    return nullptr;
}

std::vector<Territory *> Player::toAttack() {
    return nullptr;
}

Player &Player::operator=(const Player &player) {
    return <#initializer#>;
}

std::ostream &operator<<(ostream &ostream, const Player &player) {
    return <#initializer#>;
}
