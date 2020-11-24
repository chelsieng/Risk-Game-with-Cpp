#include <iostream>
#include <vector>
#include <algorithm>

#include "Player.h"

using namespace std;

int Player::counter = -1;

// default constructor
Player::Player() :
        playerHand{nullptr},
        playerOrdersList{nullptr},
        playerTerritories{nullptr},
        pID{++counter}, // increasing player count
        reinforcementPool{0} {}

// parameterized constructor
Player::Player(Hand *hand, OrdersList *OrdersList, vector<Territory *> *territories) {
    pID = ++counter; // increasing player count
    this->playerHand = hand;
    this->playerOrdersList = OrdersList;
    this->playerTerritories = territories;
    this->reinforcementPool = 0;
    this->playerStrategy = new HumanPlayerStrategy; //sets strategy to human by default
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
    for (Territory *t : *this->playerTerritories) {
        delete t;
        t = nullptr;
    }
    delete this->playerTerritories;
    playerTerritories = nullptr;

    delete this->playerStrategy;
    playerStrategy = nullptr;

    this->setPlayerStrategy(playerCopy.playerStrategy);

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
    for (Territory *t : *playerTerritories) {
        delete t;
        t = nullptr;
    }
    delete this->playerTerritories;
    playerTerritories = nullptr;

    delete this->playerStrategy;
    playerStrategy = nullptr;
}

// Returning the player's ID
int Player::getId() const {
    return pID;
}

// Returning the player's order list
OrdersList *Player::getOrdersList() {
    return this->playerOrdersList;
}

// Returning the player's hand
Hand *Player::getHand() {
    return this->playerHand;
}

vector<Territory *> *Player::getPlayerTerritories() {
    return this->playerTerritories;
}

// Adding an order to the end of the player's order list
// A subclass of Order (order types) will be passed as a parameter.
void Player::issueOrder(Order *orderToIssue) {
    Order *newOrder = orderToIssue;
    this->playerOrdersList->addToLast(newOrder);
}



Player &Player::operator=(const Player &player) {

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

    for (Territory *t : *playerTerritories) {
        delete t;
        t = nullptr;
    }
    delete playerTerritories;
    playerTerritories = nullptr;

    // creating a deep copy
    playerHand = new Hand(*player.playerHand);
    playerOrdersList = new OrdersList(*player.playerOrdersList);
    playerTerritories = new vector<Territory *>(*player.playerTerritories);

    return *this;
}

std::ostream &operator<<(ostream &out, const Player &player) {
    out << "PLAYER " << player.getId() << " HAND: " << endl;
    out << *player.playerHand << endl;
    out << "PLAYER " << player.getId() << " TERRITORIES: " << endl;
    if (player.playerTerritories->empty()) {
        out << "Territories will be assigned later." << endl <<endl;
    } else {
        for (auto terr : *player.playerTerritories) {
            out << *terr << endl;
        }
    }
    out << "PLAYER " << player.getId() << " ORDERS: " << endl;
    out << *player.playerOrdersList << endl;
    out << "PLAYER " << player.getId() << " AVAILABLE (UNUSED) REINFORCEMENT: " << endl;
    out << player.reinforcementPool << endl;

    return out;
}

int Player::getReinforcementPool() const {
    return reinforcementPool;
}

void Player::setReinforcementPool(int i) {
    this->reinforcementPool = i;
}

///Gives all the territories that a player can attack (and returns a vector of pointers to said territories)
vector<Territory *> *Player::AttackAble(Map *theMap){
    vector<Territory *>* attackable = new vector<Territory*>;
    set<int> *IDs = new set<int>;
    for(int i = 0; i < this->getPlayerTerritories()->size(); i++){
        vector<Territory*>* yourNeighbours = theMap->getNeighbours(this->getPlayerTerritories()->at(i));
        for(int j = 0; j < yourNeighbours->size(); j++) {
            if (IDs->find(yourNeighbours->at(j)->getId()) == IDs->end()) {
                IDs->insert(yourNeighbours->at(j)->getId());
            }//end of if (add neighbours to ID list if they haven't been added)
        }//end of for (go through all neighbours)
    }//end of for (go through all the player's owned territories)

    set<int,less<int>>::iterator itr;
    for(itr = IDs->begin(); itr != IDs->end(); itr++) {
        int theNeighbourID = *itr;
        for(int i = 0; i < theMap->getTerritories()->size(); i++){
            if(theMap->getTerritories()->at(i)->getId() == theNeighbourID && theMap->getTerritories()->at(i)->getOwner() != this){
                attackable->push_back(theMap->getTerritories()->at(i));
            }//end of if (valid to attack)
        }//for each ID, check all territories to see if they have the matching ID and don't belong to the player
    }//end of for (go through all IDs in list)
    return attackable;
}//end of Attackable method

bool Player::issueOrder(Map *theMap, vector<Player *> *thePlayers, int choice, Player* player) {
   return this->playerStrategy->issueOrder(theMap,thePlayers,choice, this);
//(calls the version of the player's strategy)
}///End of issue order method

vector<Territory*>* Player::toDefend(Map* theMap, Player *player) {
    vector<Territory*>* toReturn = this->playerStrategy->toDefend(theMap, player); //calls version of toAttack depending on
    return toReturn;                                                    //the player's strategy
} ///end of toDefend() method

std::vector<Territory*>* Player::toAttack(Map* theMap, Player* player) {
    vector<Territory*>* toReturn = this->playerStrategy->toAttack(theMap, player); //calls version of toAttack depending on
    return toReturn;                                                    //the player's strategy
}
///end of toAttack method

void Player::removeTerritory(Territory *t) {
    // Remove territory from player's list of Territory
    int i = 0;
    for(Territory *c : *this->getPlayerTerritories()) {
        if (t->getId() == c->getId())
            this->getPlayerTerritories()->erase(this->getPlayerTerritories()->begin()+i);
        i++;
    }
}

void Player::setPlayerStrategy(PlayerStrategy *p) {
    this->playerStrategy = p;
}

PlayerStrategy *Player::getPlayerStrategy() {
    return this->playerStrategy;
}
///end of removeTerritory
