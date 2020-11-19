#include <iostream>
#include <vector>

#include "Orders.h"

using namespace std;
using std::vector;

/*
 * Order class
 */
// Default constructor
Order::Order() {
    this->player = nullptr;
    this->isExecuted = false;
    this->setType(("Default Order"));

}

// Parameterized constructor
Order::Order(Player *player) {
    this->player = (player);
    this->isExecuted = false;
    this->setType(("Default Order"));
}

// Copy constructor
Order::Order(const Order &order) {
    this->player = (order.player);
    this->isExecuted = order.isExecuted;
    this->setType(order.orderType);
    this->priority = order.priority;
}

// Destructor
Order::~Order() {
    delete player;
    player = nullptr;
}

// Methods
bool Order::validate() {
    return (!isExecuted);       // Execute only if Order hasn't been executed before
}

ostream &Order::print(ostream &out) const {
    if (this->isExecuted)
        printEffect(out);
    return out << endl;
}

// Overloading operator
Order &Order::operator=(const Order &order) {
    if (this == &order)
        return *this;

    // deallocate
    delete this->player;
    this->player = new Player(*order.player);
    this->isExecuted = order.isExecuted;
    this->priority = order.priority;
    return *this;
}

ostream &operator<<(ostream &out, const Order &order) {
    return order.print(out);
}

int Order::getPriority() {
    return this->priority;
}


/*
 * Deploy order class
 */
// Default constructor
Deploy::Deploy() : Order() {
    this->targetTerritory = nullptr;
    this->numOfArmies = 0;
    this->setType(("Deploy"));
    this->priority = 1;
}

// Parameterized constructor
Deploy::Deploy(Player *player, Territory *targetTerritory, int numOfArmies) : Order(player) {
    this->targetTerritory = (targetTerritory);
    this->numOfArmies = numOfArmies;
    this->setType(("Deploy"));
    this->priority = 1;
}

// Copy constructor
Deploy::Deploy(const Deploy &deploy) : Order(deploy) {
    this->targetTerritory = (deploy.targetTerritory);
    this->numOfArmies = deploy.numOfArmies;
    this->setType(deploy.orderType);
    this->priority = deploy.priority;
}

// Destructor
Deploy::~Deploy() {
    delete targetTerritory;
    targetTerritory = nullptr;
}

// Methods
bool Deploy::validate() {
    // Deploy order is valid if the target territory belongs to the player that issued the order
    return (Order::validate() && this->player->getId() == this->targetTerritory->getOwner()->getId());
}

void Deploy::execute() {
    if (validate()) {
        isExecuted = true;
        cout << this->orderType << " order has been executed. ";
        // The selected number of armies is added to the number of armies on that territory
        numOfArmies = min(numOfArmies, this->player->getReinforcementPool());
        this->player->setReinforcementPool(this->player->getReinforcementPool() - numOfArmies);
        for (int i = 0; i < numOfArmies; i++)
            this->targetTerritory->addArmy();
    } else {
        cout << this->orderType << " order is invalid. Order has not been executed.";
    }
    // Print effect of order after it is executed
    cout << *this;
}

ostream &Deploy::printEffect(ostream &out) const {
    out << "Player " << this->player->getId() << " deploy " << this->numOfArmies << " armies units to " << this->targetTerritory->getTerritoryName();
    return out;
}

// Overloading operator
Deploy &Deploy::operator=(const Deploy &deploy) {
    if (this == &deploy)
        return *this;

    // deallocate
    delete this->targetTerritory;
    this->targetTerritory = new Territory(*deploy.targetTerritory);
    this->numOfArmies = deploy.numOfArmies;
    this->priority = deploy.priority;

    return *this;
}

ostream &operator<<(ostream &out, const Deploy &deploy) {
    return deploy.print(out);
}


/*
 * Advance order class
 */
// Default constructor
Advance::Advance() : Order() {
    this->sourceTerritory = nullptr;
    this->targetTerritory = nullptr;
    this->numOfArmies = 0;
    this->setType(("Advance"));
    this->priority = 4;
}

// Parameterized constructor
Advance::Advance(Player *player, Territory *sourceTerritory, Territory *targetTerritory, int numOfArmies) : Order(
        player) {
    this->sourceTerritory = (sourceTerritory);
    this->targetTerritory = (targetTerritory);
    this->numOfArmies = numOfArmies;
    this->setType(("Advance"));
    this->priority = 4;
}

// Copy constructor
Advance::Advance(const Advance &advance) : Order(advance) {
    this->sourceTerritory = (advance.sourceTerritory);
    this->targetTerritory = (advance.targetTerritory);
    this->numOfArmies = advance.numOfArmies;
    this->setType(advance.orderType);
    this->priority = 4;
}

// Destructor
Advance::~Advance() {
    delete sourceTerritory;
    sourceTerritory = nullptr;
    delete targetTerritory;
    targetTerritory = nullptr;
}

// Methods
bool Advance::validate() {
    // Advance order is valid only if the source territory belongs to the player that issued the order
    return (Order::validate() && this->player->getId() == this->sourceTerritory->getOwner()->getId());
}

void Advance::execute() {
    if (validate()) {
        isExecuted = true;
        cout << this->orderType << " order has been executed. ";
        // If the target territory belongs to the player that issued the order
        if (this->player->getId() == this->targetTerritory->getOwner()->getId()) {
            cout << "Advance to defend. ";
            // The army units are moved from the source to the target territory
            for (int i = 0; i < numOfArmies; i++) {
                if (sourceTerritory->getNumberOfArmies() == 0)
                    break;          // Stop if there is no more armies unit in source territory

                this->sourceTerritory->removeArmy();        // Take one armies unit from source territory
                this->targetTerritory->addArmy();           // Move taken armies unit to target territory
            }
        } else {    // If the target territory belongs to another player, an attack is simulated
            cout << this->sourceTerritory->getTerritoryName() << " attacks " << this->targetTerritory->getTerritoryName()
                 << " with " << numOfArmies << " armies. ";
            // Until there is no more attacking armies or no more defending armies
            while (numOfArmies > 0 && this->targetTerritory->getNumberOfArmies() > 0) {
                // Each attacking army unit involved has 60% chances of killing one defending army
                if ((double) rand() / RAND_MAX <= 0.6)
                    this->targetTerritory->removeArmy();
                // Each defending army unit has 70% chances of killing one attacking army unit
                if ((double) rand() / RAND_MAX <= 0.7) {
                    this->sourceTerritory->removeArmy();
                    numOfArmies--;
                }
            }

            // If all the defender's armies are eliminated
            if(this->targetTerritory->getNumberOfArmies() <= 0){
                cout << "The ownership of " << this->targetTerritory->getTerritoryName()
                     << " is transferred from Player " << this->targetTerritory->getOwner()->getId()
                     << " to Player " << this->player->getId() << ". ";
                // Remove the territory from the defender's vector of territory
                this->targetTerritory->getOwner()->removeTerritory(this->targetTerritory);
                // The attacker captures the territory
                this->targetTerritory->setOwner(this->player);
                this->player->addTerritory(this->targetTerritory);

                cout << "There are " << numOfArmies << " attacking armies remain. ";
                // The attacking army units that survived the battle then occupy the conquered territory.
                for (int i = 0; i < numOfArmies; i++) {
                    if (sourceTerritory->getNumberOfArmies() == 0)
                        break;          // Stop if there is no more armies unit in source territory

                    this->sourceTerritory->removeArmy();        // Take one armies unit from source territory
                    this->targetTerritory->addArmy();           // Move taken armies unit to target territory
                }

                // If this is the player has not conquered a territory in the turn before
                if(!this->player->getConquered()) {
                    cout << "Player " << player->getId() << " gets a card for conquering a territory in this turn. ";
                    this->player->setConquered(true);
                    // Draw a card
                    Card* newCard = this->player->getHand()->getDeck()->draw();
                    // If the deck is not empty, give player the card
                    if(newCard != NULL) {
                        this->player->getHand()->addToHand(newCard);
                        cout << *newCard->getDescription();
                    }
                }
            } else {
                cout << "All attacking armies are eliminated. " << this->targetTerritory->getTerritoryName()
                     << " has " << this->targetTerritory->getNumberOfArmies() << " armies remain. ";
            }
        }
    } else {
        cout << this->orderType << " order is invalid. Order has not been executed.";
    }
    // Print effect of order after it is executed
    cout << *this;
}

ostream &Advance::printEffect(ostream &out) const {
    out << "Player " << this->player->getId() << " advance " << this->numOfArmies << " armies units from "
        << this->sourceTerritory->getTerritoryName() << " to " << this->targetTerritory->getTerritoryName();
    return out;
}

// Overloading operator
Advance &Advance::operator=(const Advance &advance) {
    if (this == &advance)
        return *this;

    // deallocate
    delete this->sourceTerritory;
    this->sourceTerritory = (advance.sourceTerritory);
    delete this->targetTerritory;
    this->targetTerritory = (advance.targetTerritory);
    this->numOfArmies = advance.numOfArmies;
    this->priority = 4;

    return *this;
}

ostream &operator<<(ostream &out, const Advance &advance) {
    return advance.print(out);
}


/*
  * Bomb order class
 */
// Default constructor
Bomb::Bomb() : Order() {
    this->sourceTerritory = nullptr;
    this->targetTerritory = nullptr;
    this->setType(("Bomb"));
    this->priority = 4;
}

// Parameterized constructor
Bomb::Bomb(Player *player, Territory *sourceTerritory, Territory *targetTerritory) : Order(player) {
    this->sourceTerritory = (sourceTerritory);
    this->targetTerritory = (targetTerritory);
    this->setType(("Bomb"));
    this->priority = 4;
}

// Copy constructor
Bomb::Bomb(const Bomb &bomb) : Order(bomb) {
    this->sourceTerritory = (bomb.sourceTerritory);
    this->targetTerritory = (bomb.targetTerritory);
    this->setType(bomb.orderType);
    this->priority = 4;
}

// Destructor
Bomb::~Bomb() {
    delete sourceTerritory;
    sourceTerritory = nullptr;
    delete targetTerritory;
    targetTerritory = nullptr;
}

// Methods
bool Bomb::validate() {
    // Bomb order is valid if
    // the source territory belongs to the player that issued the order, and
    // the target territory does not belongs to the player that issued the order
    return (Order::validate() &&
            this->player->getId() == this->sourceTerritory->getOwner()->getId() &&
            this->player->getId() != this->targetTerritory->getOwner()->getId());
}

void Bomb::execute() {
    if (validate()) {
        isExecuted = true;
        cout << this->orderType << " order has been executed. ";
        // Remove half of the armies from target territory
        int halfArmies = ceil(this->targetTerritory->getNumberOfArmies() / 2.0);
        for (int i = 0; i < halfArmies; i++)
            this->targetTerritory->removeArmy();
    } else {
        cout << this->orderType << " order is invalid. Order has not been executed.";
    }
    // Print effect of order after it is executed
    cout << *this;
}

ostream &Bomb::printEffect(ostream &out) const {
    out <<  "Player " << this->player->getId() << " bomb " << this->targetTerritory->getTerritoryName();
    out << ". The number of armies in " << this->targetTerritory->getTerritoryName() << " is halved.";
    return out;
}

// Overloading operator
Bomb &Bomb::operator=(const Bomb &bomb) {
    if (this == &bomb)
        return *this;

    // deallocate
    delete this->sourceTerritory;
    this->sourceTerritory = (bomb.sourceTerritory);
    delete this->targetTerritory;
    this->targetTerritory = (bomb.targetTerritory);
    this->priority = 4;
    return *this;
}

ostream &operator<<(ostream &out, const Bomb &bomb) {
    return bomb.print(out);
}


/*
  * Blockade order class
 */
// Default constructor
Blockade::Blockade() : Order() {
    this->targetTerritory = nullptr;
    this->setType(("Blockade"));
    this->priority = 3;
}

// Parameterized constructor
Blockade::Blockade(Player *player, Territory *targetTerritory) : Order(player) {
    this->targetTerritory = (targetTerritory);
    this->setType(("Blockade"));
    this->priority = 3;
}

// Copy constructor
Blockade::Blockade(const Blockade &blockade) : Order(blockade) {
    this->targetTerritory = (blockade.targetTerritory);
    this->isExecuted = blockade.isExecuted;
    this->setType(blockade.orderType);
    this->priority = 3;
}

// Destructor
Blockade::~Blockade() {
    delete targetTerritory;
    targetTerritory = nullptr;
}

// Declare neutralPlayer static variable to store blockade territories
Player* Blockade::neutralPlayer = new Player(nullptr, nullptr, new vector<Territory *>);

// Methods
bool Blockade::validate() {
    // Blockade order is valid only if the target territory belongs to the player that issued the order
    return (Order::validate() && this->player->getId() == this->targetTerritory->getOwner()->getId());
}

void Blockade::execute() {
    if (validate()) {
        isExecuted = true;
        cout << this->orderType << " order has been executed. ";
        // Remove the territory from the defender's vector of territory
        this->targetTerritory->getOwner()->removeTerritory(this->targetTerritory);
        // The attacker captures the territory
        this->targetTerritory->setOwner(Blockade::neutralPlayer);
        Blockade::neutralPlayer->addTerritory(this->targetTerritory);

        // The number of armies on the territory is doubled
        int doubleArmies = this->targetTerritory->getNumberOfArmies();
        for (int i = 0; i < doubleArmies; i++)
            this->targetTerritory->addArmy();
    } else {
        cout << this->orderType << " order is invalid. Order has not been executed.";
    }
    // Print effect of order after it is executed
    cout << *this;
}

ostream &Blockade::printEffect(ostream &out) const {
    out << "Player " << this->player->getId() << " blockade " << this->targetTerritory->getTerritoryName()
        << ". Territory now belongs to the Neutral player. The number of armies is doubled to "
        << this->targetTerritory->getNumberOfArmies() << ". ";
    return out;
}

// Overloading operator
Blockade &Blockade::operator=(const Blockade &blockade) {
    if (this == &blockade)
        return *this;

    // deallocate
    delete this->targetTerritory;
    this->targetTerritory = (blockade.targetTerritory);
    this->isExecuted = blockade.isExecuted;
    this->priority = 3;

    return *this;
}

ostream &operator<<(ostream &out, const Blockade &blockade) {
    return blockade.print(out);
}


/*
 * Airlift order class
 */
//Default constructor
Airlift::Airlift() : Order() {
    this->sourceTerritory = nullptr;
    this->targetTerritory = nullptr;
    this->numOfArmies = 0;
    this->setType(("Airlift"));
    this->priority = 2;
}

// Parameterized constructor
Airlift::Airlift(Player *player, Territory *sourceTerritory, Territory *targetTerritory, int numOfArmies) : Order(
        player) {
    this->sourceTerritory = (sourceTerritory);
    this->targetTerritory = (targetTerritory);
    this->numOfArmies = numOfArmies;
    this->setType(("Airlift"));
    this->priority = 2;
}

// Copy constructor
Airlift::Airlift(const Airlift &airlift) : Order(airlift) {
    this->sourceTerritory = (airlift.sourceTerritory);
    this->targetTerritory = (airlift.targetTerritory);
    this->numOfArmies = airlift.numOfArmies;
    this->setType(airlift.orderType);
    this->priority = 2;
}

// Destructor
Airlift::~Airlift() {
    delete sourceTerritory;
    sourceTerritory = nullptr;
    delete targetTerritory;
    targetTerritory = nullptr;
}


// Methods
bool Airlift::validate() {
    // Airlift order is valid only if the source territory belongs to the player that issued the order
    return (Order::validate() && this->player->getId() == this->sourceTerritory->getOwner()->getId());
}

void Airlift::execute() {
    if (validate()) {
        isExecuted = true;
        cout << this->orderType << " order has been executed. ";
        // If the target territory belongs to the player that issued the order
        if (this->player->getId() == this->targetTerritory->getOwner()->getId()) {
            cout << "Airlift to defend. ";
            // The army units are moved from the source to the target territory
            for (int i = 0; i < numOfArmies; i++) {
                if (sourceTerritory->getNumberOfArmies() == 0)
                    break;          // Stop if there is no more armies unit in source territory

                this->sourceTerritory->removeArmy();        // Take one armies unit from source territory
                this->targetTerritory->addArmy();           // Move taken armies unit to target territory
            }
        } else {    // If the target territory belongs to another player, an attack is simulated
            cout << this->sourceTerritory->getTerritoryName() << " attacks " << this->targetTerritory->getTerritoryName()
                 << " with " << numOfArmies << " armies. ";
            // Until there is no more attacking armies or no more defending armies
            while (numOfArmies > 0 && this->targetTerritory->getNumberOfArmies() > 0) {
                // Each attacking army unit involved has 60% chances of killing one defending army
                if ((double) rand() / RAND_MAX <= 0.6)
                    this->targetTerritory->removeArmy();
                // Each defending army unit has 70% chances of killing one attacking army unit
                if ((double) rand() / RAND_MAX <= 0.7) {
                    this->sourceTerritory->removeArmy();
                    numOfArmies--;
                }
            }

            // If all the defender's armies are eliminated
            if(this->targetTerritory->getNumberOfArmies() <= 0) {
                cout << "The ownership of " << this->targetTerritory->getTerritoryName()
                     << " is transferred from Player " << this->targetTerritory->getOwner()->getId()
                     << " to Player " << this->player->getId() << ". ";
                // Remove the territory from the defender's vector of territory
                this->targetTerritory->getOwner()->removeTerritory(this->targetTerritory);
                // The attacker captures the territory
                this->targetTerritory->setOwner(this->player);
                this->player->addTerritory(this->targetTerritory);

                cout << "There are " << numOfArmies << " attacking armies remain. ";
                // The attacking army units that survived the battle then occupy the conquered territory.
                for (int i = 0; i < numOfArmies; i++) {
                    if (sourceTerritory->getNumberOfArmies() == 0)
                        break;          // Stop if there is no more armies unit in source territory

                    this->sourceTerritory->removeArmy();        // Take one armies unit from source territory
                    this->targetTerritory->addArmy();           // Move taken armies unit to target territory
                }

                // If this is the player has not conquered a territory in the turn before
                if(!this->player->getConquered()) {
                    cout << "Player " << player->getId() << " gets a card for conquering a territory in this turn. ";
                    this->player->setConquered(true);
                    Card* newCard = this->player->getHand()->getDeck()->draw();
                    if(newCard != NULL) {
                        this->player->getHand()->addToHand(newCard);
                        cout << *newCard->getDescription();
                    }
                }
            } else {
                cout << "All attacking armies are eliminated. " << this->targetTerritory->getTerritoryName()
                     << " has " << this->targetTerritory->getNumberOfArmies() << " armies remain. ";
            }
        }
    } else {
        cout << this->orderType << " order is invalid. Order has not been executed.";
    }
    // Print effect of order after it is executed
    cout << *this;
}

ostream &Airlift::printEffect(ostream &out) const {
    out << "Player " << this->player->getId() << " airlift " << this->numOfArmies << " armies from "
        << this->sourceTerritory->getTerritoryName() << " to " << this->targetTerritory->getTerritoryName();
    return out;
}

// Overloading operator
Airlift &Airlift::operator=(const Airlift &airlift) {
    if (this == &airlift)
        return *this;

    // deallocate
    delete this->sourceTerritory;
    this->sourceTerritory = (airlift.sourceTerritory);
    delete this->targetTerritory;
    this->targetTerritory = (airlift.targetTerritory);
    this->numOfArmies = airlift.numOfArmies;

    return *this;
}

ostream &operator<<(ostream &out, const Airlift &airlift) {
    return airlift.print(out);
}


/*
 * Negotiate order class
 */
// Default constructor
Negotiate::Negotiate() : Order() {
    this->negotiator = nullptr;
    this->setType(("Negotiate"));
    this->priority = 4;
}

// Parameterized constructor
Negotiate::Negotiate(Player *player, Player *negotiator) : Order(player) {
    this->negotiator = (negotiator);
    this->setType(("Negotiate"));
    this->priority = 4;
}

// Copy constructor
Negotiate::Negotiate(const Negotiate &negotiate) : Order(negotiate) {
    this->negotiator = (negotiate.negotiator);
    this->isExecuted = negotiate.isExecuted;
    this->setType(negotiate.orderType);
    this->priority = 4;
}

// Destructor
Negotiate::~Negotiate() {
    delete negotiator;
    negotiator = nullptr;
}

// Methods
bool Negotiate::validate() {
    // Negotiate order is valid only if the target player is not the player issuing the order
    return (Order::validate() && this->player->getId() != this->negotiator->getId());
}

void Negotiate::execute() {
    if (validate()) {
        isExecuted = true;
        cout << this->orderType << " order has been executed. ";
        // The target player and the player issuing the order cannot attack each others’ territories for the remainder of the turn
        // TODO

        // Remove orders where order issuer and negotiated player target each other
        OrdersList *ordersList1 =  this->player->getOrdersList();
        OrdersList *ordersList2 =  this->negotiator->getOrdersList();
        // If there are orders made by the negotiation issuer before the Negotiate order is issued
        for(int i = 0; i < ordersList1->getSize(); i++)
            // If the current order has a target territory
            if(ordersList1->getAt(i)->getTargetTerritory() != nullptr)
                // Delete order if it targets negotiated player
                if(this->negotiator->getId() == ordersList1->getAt(i)->getTargetTerritory()->getOwner()->getId()) {
                    ordersList1->deleteAt(i);
                    i--;
                }

        // If there are orders made by the negotiated player before the Negotiate order is issued
        for(int i = 0; i < ordersList2->getSize(); i++)
            // If the current order has a target territory
            if(ordersList2->getAt(i)->getTargetTerritory() != nullptr)
                // Delete order if it targets negotiation issuer
                if(this->player->getId() == ordersList2->getAt(i)->getTargetTerritory()->getOwner()->getId()) {
                    ordersList2->deleteAt(i);
                    i--;
                }

        // Check if the 2 players have negotiated with each other before
        bool playerAdded1 = false;
        for(Player* p : this->player->getDiplomacyPlayers())
            if(p->getId() == this->player->getId()) {
                playerAdded1 = true;
                break;
            }
        bool playerAdded2 = false;
        for(Player* p : this->player->getDiplomacyPlayers())
            if(p->getId() == this->negotiator->getId()) {
                playerAdded2 = true;
                break;
            }

        // If not then add players into each other's diplomacyPlayer list
        if(!playerAdded1)
            this->player->addDiplomacyPlayer(this->negotiator);
        if(!playerAdded2)
            this->negotiator->addDiplomacyPlayer(this->player);
    } else {
        cout << this->orderType << " order is invalid. Order has not been executed.";
    }
    // Print effect of order after it is executed
    cout << *this;
}

ostream &Negotiate::printEffect(ostream &out) const {
    out << "Player " << this->player->getId() << " and Player " << this->negotiator->getId();
    out << " cannot attack each other's territories until the end of the turn.";
    return out;
}

// Overloading operator
Negotiate &Negotiate::operator=(const Negotiate &negotiate) {
    if (this == &negotiate)
        return *this;

    // deallocate
    delete this->negotiator;
    this->negotiator = (negotiate.negotiator);
    this->isExecuted = negotiate.isExecuted;
    this->priority = 4;

    return *this;
}

ostream &operator<<(ostream &out, const Negotiate &negotiate) {
    return negotiate.print(out);
}


/*
 * OrdersList class
 */
// Default constructor
OrdersList::OrdersList() {
    listOrders.clear();
}

// Copy constructor
OrdersList::OrdersList(const OrdersList &ordersList) {
    this->listOrders.clear();

    for (Order *order : ordersList.listOrders) {
        // add a copy of the order into the list based on the type
        if (order->getOrderType() == ("Deploy"))
            this->addToLast(new Deploy(*dynamic_cast<Deploy *>(order)));
        else if (order->getOrderType() == ("Advance"))
            this->addToLast(new Advance(*dynamic_cast<Advance *>(order)));
        else if (order->getOrderType() == ("Bomb"))
            this->addToLast(new Bomb(*dynamic_cast<Bomb *>(order)));
        else if (order->getOrderType() == ("Blockade"))
            this->addToLast(new Blockade(*dynamic_cast<Blockade *>(order)));
        else if (order->getOrderType() == ("Airlift"))
            this->addToLast(new Airlift(*dynamic_cast<Airlift *>(order)));
        else if (order->getOrderType() == ("Negotiate"))
            this->addToLast(new Negotiate(*dynamic_cast<Negotiate *>(order)));
    }
}

// Destructor
OrdersList::~OrdersList() {
    for (Order *order : this->listOrders) {
        delete order;
        order = nullptr;
    }
    this->listOrders.clear();
}

// Methods
void OrdersList::add(int index, Order *order) {
    this->listOrders.insert((this->listOrders.begin() + index), order);
}

void OrdersList::addToLast(Order *order) {
    this->listOrders.push_back(order);
}

Order *OrdersList::deleteAt(int index) {
    Order *removedOrder = listOrders.at(index);
    listOrders.erase(this->listOrders.begin() + index);
    return removedOrder;
}

void OrdersList::move(int indexFrom, int indexTo) {
    Order *movedOrder = this->deleteAt(indexFrom);
    this->add(indexTo, movedOrder);
}

// Overloading operator
OrdersList &OrdersList::operator=(const OrdersList &ordersList) {
    if (this == &ordersList)
        return *this;

    // deallocate
    this->listOrders.clear();

    for (Order *order : ordersList.listOrders) {
        // add a copy of the order into the list based on the type
        if (order->getOrderType() == ("Deploy"))
            this->addToLast(new Deploy(*dynamic_cast<Deploy *>(order)));
        else if (order->getOrderType() == ("Advance"))
            this->addToLast(new Advance(*dynamic_cast<Advance *>(order)));
        else if (order->getOrderType() == ("Bomb"))
            this->addToLast(new Bomb(*dynamic_cast<Bomb *>(order)));
        else if (order->getOrderType() == ("Blockade"))
            this->addToLast(new Blockade(*dynamic_cast<Blockade *>(order)));
        else if (order->getOrderType() == ("Airlift"))
            this->addToLast(new Airlift(*dynamic_cast<Airlift *>(order)));
        else if (order->getOrderType() == ("Negotiate"))
            this->addToLast(new Negotiate(*dynamic_cast<Negotiate *>(order)));
    }

    return *this;
}

ostream &operator<<(ostream &out, const OrdersList &ordersList) {
    out << "List of Orders:" << endl;
    if (ordersList.listOrders.empty()) {
        out << "The list is empty. Orders will be assigned later." << endl;
    }
    for (int i = 0; i < ordersList.listOrders.size(); i++)
        out << (i + 1) << ". " << (*ordersList.listOrders[i]).getOrderType() << endl;

    return out;
}

int OrdersList::highestPriority() {
    int indexOfHighest = 0;
    int numberToBeat = 0;
    if(this->listOrders.size() == 0){
        cout << "No orders in list!" << endl;
    return -1;}
    else{
        numberToBeat = this->listOrders.at(0)->getPriority();
        for(int i = 1; i < this->listOrders.size(); i++){
            if(this->listOrders.at(i)->getPriority() < numberToBeat){
                numberToBeat = this->listOrders.at(i)->getPriority();
                indexOfHighest = i;
            }//end of if (found something of higher priority)
        }//end of for (go through all orders in list)

        return indexOfHighest;
    }//end of else (list not empty)
}

int OrdersList::getSize() {
    return this->listOrders.size();
}
//end of highest priority method


