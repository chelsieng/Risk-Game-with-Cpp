#include <iostream>
#include <vector>

#include "Orders.h"

using namespace std;
using std::vector;

/*
 * Order class
 */
// Default constructor
Order::Order()
{
    this->player = nullptr;
    this->isExecuted = false;
    this->setType(("Default Order"));
}

// Parameterized constructor
Order::Order(Player *player)
{
    this->player = (player);
    this->isExecuted = false;
    this->setType(("Default Order"));
}

// Copy constructor
Order::Order(const Order &order)
{
    this->player = (order.player);
    this->isExecuted = order.isExecuted;
    this->setType(order.orderType);
}

// Destructor
Order::~Order()
{
    delete player; player = nullptr;
}

// Methods
bool Order::validate() {
    return (!isExecuted);       // Execute only if Order hasn't been executed before
}

// Overloading operator
Order& Order::operator=(const Order& order){
    if(this == &order)
        return *this;

    // deallocate
    delete this->player;
    this->player = new Player(*order.player);
    this->isExecuted = order.isExecuted;

    return *this;
}

ostream &operator<<(ostream &out, const Order& order) {
    return order.print(out);
}


/*
 * Deploy order class
 */
// Default constructor
Deploy::Deploy() : Order()
{
    this->targetTerritory = nullptr;
    this->numOfArmies = 0;
    this->setType(("Deploy"));
}

// Parameterized constructor
Deploy::Deploy(Player *player, Territory *targetTerritory, int numOfArmies) : Order(player)
{
    this->targetTerritory = (targetTerritory);
    this->numOfArmies = numOfArmies;
    this->setType(("Deploy"));
}

// Copy constructor
Deploy::Deploy(const Deploy &deploy) : Order(deploy)
{
    this->targetTerritory = (deploy.targetTerritory);
    this->numOfArmies = deploy.numOfArmies;
    this->setType(deploy.orderType);
}

// Destructor
Deploy::~Deploy()
{
    delete targetTerritory; targetTerritory = nullptr;
}

// Methods
bool Deploy::validate()
{
    // Deploy order is valid if the target territory belongs to the player that issued the order
    return (this->player->getId() == this->targetTerritory->getOwner()->getId());
}

void Deploy::execute()
{
    if(validate())
    {
        isExecuted = true;
        // The selected number of armies is added to the number of armies on that territory
        this->player->setReinforcementPool(this->player->getReinforcementPool() - numOfArmies);
        for(int i = 0; i < numOfArmies; i++)
            this->targetTerritory->addArmy();
    }
}

ostream& Deploy::print(ostream& out) const {
    out << this->orderType;
    if(this->isExecuted) {
        out << " order has been executed. ";
        printEffect(out);
    } else
        out << " order has not been executed. ";
    return out << endl;
}

ostream& Deploy::printEffect(ostream &out) const {
    out << "Deploy " << this->numOfArmies << " armies units to " << this->targetTerritory->getTerritoryName();
    return out;
}

// Overloading operator
Deploy& Deploy::operator=(const Deploy& deploy) {
    if(this == &deploy)
        return *this;

    // deallocate
    delete this->targetTerritory;
    this->targetTerritory = new Territory(*deploy.targetTerritory);
    this->numOfArmies = deploy.numOfArmies;

    return *this;
}

ostream &operator<<(ostream &out, const Deploy& deploy) {
    return deploy.print(out);
}


/*
 * Advance order class
 */
// Default constructor
Advance::Advance() : Order()
{
    this->sourceTerritory = nullptr;
    this->targetTerritory = nullptr;
    this->numOfArmies = 0;
    this->setType(("Advance"));
}

// Parameterized constructor
Advance::Advance(Player *player, Territory *sourceTerritory, Territory *targetTerritory, int numOfArmies) : Order(player)
{
    this->sourceTerritory = (sourceTerritory);
    this->targetTerritory = (targetTerritory);
    this->numOfArmies = numOfArmies;
    this->setType(("Advance"));
}

// Copy constructor
Advance::Advance(const Advance &advance) : Order(advance)
{
    this->sourceTerritory = (advance.sourceTerritory);
    this->targetTerritory = (advance.targetTerritory);
    this->numOfArmies = advance.numOfArmies;
    this->setType(advance.orderType);
}

// Destructor
Advance::~Advance()
{
    delete sourceTerritory; sourceTerritory = nullptr;
    delete targetTerritory; targetTerritory = nullptr;
}

// Methods
bool Advance::validate()
{
    // Advance order is valid only if the source territory belongs to the player that issued the order
    return (this->player->getId() == this->sourceTerritory->getOwner()->getId());
}

void Advance::execute()
{
    if(validate())
    {
        isExecuted = true;
        // If the target territory belongs to the player that issued the order
        if(this->player->getId() == this->targetTerritory->getOwner()->getId()) {
            // The army units are moved from the source to the target territory
            for(int i = 0; i < numOfArmies; i++) {
                if(sourceTerritory->getNumberOfArmies() == 0)
                    break;          // Stop if there is no more armies unit in source territory

                this->sourceTerritory->removeArmy();        // Take one armies unit from source territory
                this->targetTerritory->addArmy();           // Move taken armies unit to target territory
            }
        } else {    // If the target territory belongs to another player, an attack is simulated
            // Until there is no more attacking armies or no more defending armies
            while(numOfArmies != 0 && this->targetTerritory->getNumberOfArmies() !=0) {
                // Each attacking army unit involved has 60% chances of killing one defending army
                if((double) rand()/RAND_MAX <= 0.6)
                    this->targetTerritory->removeArmy();
                // Each defending army unit has 70% chances of killing one attacking army unit
                if((double) rand()/RAND_MAX <= 0.7)
                    numOfArmies--;
            }

            // If all the defender's armies are eliminated
            if(this->targetTerritory->getNumberOfArmies() ==0){
                // The attacker captures the territory
                this->targetTerritory->setOwner(this->player);

                // The attacking army units that survived the battle then occupy the conquered territory.
                for(int i = 0; i < numOfArmies; i++) {
                    if(sourceTerritory->getNumberOfArmies() == 0)
                        break;          // Stop if there is no more armies unit in source territory

                    this->sourceTerritory->removeArmy();        // Take one armies unit from source territory
                    this->targetTerritory->addArmy();           // Move taken armies unit to target territory
                }
            }
        }
    }
}

ostream& Advance::print(ostream& out) const {
    out << this->orderType;
    if(this->isExecuted) {
        out << " order has been executed. ";
        this->printEffect(out);
    } else
        out << " order has not been executed.";
    return out << endl;
}

ostream& Advance::printEffect(ostream &out) const {
    out << "Advance " << this->numOfArmies << " armies units from " << this->sourceTerritory->getTerritoryName() << " to " << this->targetTerritory->getTerritoryName();
    return out;
}

// Overloading operator
Advance& Advance::operator=(const Advance& advance){
    if(this == &advance)
        return *this;

    // deallocate
    delete this->sourceTerritory;
    this->sourceTerritory = (advance.sourceTerritory);
    delete this->targetTerritory;
    this->targetTerritory = (advance.targetTerritory);
    this->numOfArmies = advance.numOfArmies;

    return *this;
}

ostream &operator<<(ostream &out, const Advance& advance) {
    return advance.print(out);
}


/*
  * Bomb order class
 */
// Default constructor
Bomb::Bomb() : Order()
{
    this->sourceTerritory = nullptr;
    this->targetTerritory = nullptr;
    this->setType(("Bomb"));
}

// Parameterized constructor
Bomb::Bomb(Player *player, Territory *sourceTerritory, Territory *targetTerritory) : Order(player)
{
    this->sourceTerritory = (sourceTerritory);
    this->targetTerritory = (targetTerritory);
    this->setType(("Bomb"));
}

// Copy constructor
Bomb::Bomb(const Bomb &bomb) : Order(bomb)
{
    this->sourceTerritory = (bomb.sourceTerritory);
    this->targetTerritory = (bomb.targetTerritory);
    this->setType(bomb.orderType);
}

// Destructor
Bomb::~Bomb()
{
    delete sourceTerritory; sourceTerritory = nullptr;
    delete targetTerritory; targetTerritory = nullptr;
}

// Methods
bool Bomb::validate()
{
    // Bomb order is valid if
    // the source territory belongs to the player that issued the order, and
    // the target territory does not belongs to the player that issued the order
    return (this->player->getId() == this->sourceTerritory->getOwner()->getId()
            && this->player->getId() != this->targetTerritory->getOwner()->getId());
}

void Bomb::execute()
{
    if(validate())
    {
        isExecuted = true;
        // Remove half of the armies from target territory
        int halfArmies = ceil(this->targetTerritory->getNumberOfArmies()/2.0);
        for(int i = 0; i < halfArmies; i++)
            this->targetTerritory->removeArmy();
    }
}

ostream& Bomb::print(ostream& out) const {
    out << this->orderType;
    if(this->isExecuted) {
        out << " order has been executed. ";
        this->printEffect(out);
    } else
        out << " order has not been executed.";
    return out << endl;
}

ostream& Bomb::printEffect(ostream &out) const {
    out << this->sourceTerritory->getTerritoryName() << " bomb " << this->targetTerritory->getTerritoryName();
    out << ". The number of armies in " << this->targetTerritory->getTerritoryName() << " is halved.";
    return out;
}

// Overloading operator
Bomb& Bomb::operator=(const Bomb& bomb)
{
    if(this == &bomb)
        return *this;

    // deallocate
    delete this->sourceTerritory;
    this->sourceTerritory = (bomb.sourceTerritory);
    delete  this->targetTerritory;
    this->targetTerritory = (bomb.targetTerritory);

    return *this;
}

ostream &operator<<(ostream &out, const Bomb& bomb) {
    return bomb.print(out);
}


/*
  * Blockade order class
 */
// Default constructor
Blockade::Blockade() : Order()
{
    this->targetTerritory = nullptr;
    this->setType(("Blockade"));
}

// Parameterized constructor
Blockade::Blockade(Player *player, Territory *targetTerritory) : Order(player)
{
    this->targetTerritory = (targetTerritory);
    this->setType(("Blockade"));
}

// Copy constructor
Blockade::Blockade(const Blockade &blockade) : Order(blockade)
{
    this->targetTerritory = (blockade.targetTerritory);
    this->isExecuted = blockade.isExecuted;
    this->setType(blockade.orderType);
}

// Destructor
Blockade::~Blockade()
{
    delete targetTerritory; targetTerritory = nullptr;
}

// Methods
bool Blockade::validate()
{
    // Blockade order is valid only if the target territory belongs to the player that issued the order
    return (this->player->getId() == this->targetTerritory->getOwner()->getId());
}

void Blockade::execute()
{
    if(validate())
    {
        isExecuted = true;
        // The ownership of the territory is transferred to the Neutral player
        // TODO
//        this->targetTerritory->setOwner(new Player());
        // The number of armies on the territory is doubled
        int doubleArmies = this->targetTerritory->getNumberOfArmies();
        for(int i = 0; i < doubleArmies; i++)
            this->targetTerritory->addArmy();
    }
}

ostream& Blockade::print(ostream& out) const {
    out << this->orderType;
    if(this->isExecuted) {
        out << " order has been executed. ";
        this->printEffect(out);
    } else
        out << " order has not been executed.";
    return out << endl;
}

ostream& Blockade::printEffect(ostream &out) const {
    out << this->targetTerritory->getTerritoryName() << " now belongs to the Neutral player. The number of armies is doubled.";
    return out;
}

// Overloading operator
Blockade& Blockade::operator=(const Blockade& blockade){
    if(this == &blockade)
        return *this;

    // deallocate
    delete this->targetTerritory;
    this->targetTerritory = (blockade.targetTerritory);
    this->isExecuted = blockade.isExecuted;

    return *this;
}

ostream &operator<<(ostream &out, const Blockade& blockade) {
    return blockade.print(out);
}


/*
 * Airlift order class
 */
//Default constructor
Airlift::Airlift() : Order()
{
    this->sourceTerritory = nullptr;
    this->targetTerritory = nullptr;
    this->numOfArmies = 0;
    this->setType(("Airlift"));
}

// Parameterized constructor
Airlift::Airlift(Player *player, Territory *sourceTerritory, Territory *targetTerritory, int numOfArmies) : Order(player)
{
    this->sourceTerritory = (sourceTerritory);
    this->targetTerritory = (targetTerritory);
    this->numOfArmies = numOfArmies;
    this->setType(("Airlift"));
}

// Copy constructor
Airlift::Airlift(const Airlift &airlift) : Order(airlift)
{
    this->sourceTerritory = (airlift.sourceTerritory);
    this->targetTerritory = (airlift.targetTerritory);
    this->numOfArmies = airlift.numOfArmies;
    this->setType(airlift.orderType);
}

// Destructor
Airlift::~Airlift()
{
    delete sourceTerritory; sourceTerritory = nullptr;
    delete targetTerritory; targetTerritory = nullptr;
}


// Methods
bool Airlift::validate()
{
    // Airlift order is valid only if the source territory belongs to the player that issued the order
    return (this->player->getId() == this->sourceTerritory->getOwner()->getId());
}

void Airlift::execute()
{
    if(validate())
    {
        isExecuted = true;
        // If the target territory belongs to the player that issued the order
        if(this->player->getId() == this->targetTerritory->getOwner()->getId()) {
            // The army units are moved from the source to the target territory
            for(int i = 0; i < numOfArmies; i++) {
                if(sourceTerritory->getNumberOfArmies() == 0)
                    break;          // Stop if there is no more armies unit in source territory

                this->sourceTerritory->removeArmy();        // Take one armies unit from source territory
                this->targetTerritory->addArmy();           // Move taken armies unit to target territory
            }
        } else {    // If the target territory belongs to another player, an attack is simulated
            // Until there is no more attacking armies or no more defending armies
            while(numOfArmies != 0 && this->targetTerritory->getNumberOfArmies() !=0) {
                // Each attacking army unit involved has 60% chances of killing one defending army
                if((double) rand()/RAND_MAX <= 0.6)
                    this->targetTerritory->removeArmy();
                // Each defending army unit has 70% chances of killing one attacking army unit
                if((double) rand()/RAND_MAX <= 0.7)
                    numOfArmies--;
            }

            // If all the defender's armies are eliminated
            if(this->targetTerritory->getNumberOfArmies() == 0){
                // The attacker captures the territory
                this->targetTerritory->setOwner(this->player);

                // The attacking army units that survived the battle then occupy the conquered territory.
                for(int i = 0; i < numOfArmies; i++) {
                    if(sourceTerritory->getNumberOfArmies() == 0)
                        break;          // Stop if there is no more armies unit in source territory

                    this->sourceTerritory->removeArmy();        // Take one armies unit from source territory
                    this->targetTerritory->addArmy();           // Move taken armies unit to target territory
                }
            }
        }
    }
}

ostream& Airlift::print(ostream& out) const {
    out << this->orderType;
    if(this->isExecuted) {
        out << " order has been executed. ";
        this->printEffect(out);
    } else
        out << " order has not been executed.";
    return out << endl;
}

ostream& Airlift::printEffect(ostream &out) const {
    out << "Airlift " << this->numOfArmies << " armies from " << this->sourceTerritory->getTerritoryName() << " to " << this->targetTerritory->getTerritoryName();
    return out;
}

// Overloading operator
Airlift& Airlift::operator=(const Airlift& airlift){
    if(this == &airlift)
        return *this;

    // deallocate
    delete this->sourceTerritory;
    this->sourceTerritory = (airlift.sourceTerritory);
    delete  this->targetTerritory;
    this->targetTerritory = (airlift.targetTerritory);
    this->numOfArmies = airlift.numOfArmies;

    return *this;
}

ostream &operator<<(ostream &out, const Airlift& airlift) {
    return airlift.print(out);
}


/*
 * Negotiate order class
 */
// Default constructor
Negotiate::Negotiate() : Order()
{
    this->negotiator = nullptr;
    this->setType(("Negotiate"));
}

// Parameterized constructor
Negotiate::Negotiate(Player *player, Player *negotiator) : Order(player)
{
    this->negotiator = (negotiator);
    this->setType(("Negotiate"));
}

// Copy constructor
Negotiate::Negotiate(const Negotiate &negotiate) : Order(negotiate)
{
    this->negotiator = (negotiate.negotiator);
    this->isExecuted = negotiate.isExecuted;
    this->setType(negotiate.orderType);
}

// Destructor
Negotiate::~Negotiate()
{
    delete negotiator; negotiator = nullptr;
}

// Methods
bool Negotiate::validate()
{
    // Negotiate order is valid only if the target player is not the player issuing the order
    return (this->player->getId() != this->negotiator->getId());
}

void Negotiate::execute()
{
    if(validate())
    {
        isExecuted = true;
        // The target player and the player issuing the order cannot attack each others’ territories for the remainder of the turn
        // TODO
    }
}

ostream& Negotiate::print(ostream& out) const {
    out << this->orderType;
    if(this->isExecuted) {
        out << " order has been executed. ";
        this->printEffect(out);
    } else
        out << " order has not been executed.";
    return out << endl;
}

ostream& Negotiate::printEffect(ostream &out) const {
    out << "Player" << this->player->getId() << " and Player" << this->negotiator->getId();
    out << " cannot attack each other's territories until the end of the turn.";
    return out;
}

// Overloading operator
Negotiate& Negotiate::operator=(const Negotiate& negotiate){
    if(this == &negotiate)
        return *this;

    // deallocate
    delete this->negotiator;
    this->negotiator = (negotiate.negotiator);
    this->isExecuted = negotiate.isExecuted;

    return *this;
}

ostream &operator<<(ostream &out, const Negotiate& negotiate) {
    return negotiate.print(out);
}


/*
 * OrdersList class
 */
// Default constructor
OrdersList::OrdersList()
{
    listOrders.clear();
}

// Copy constructor
OrdersList::OrdersList(const OrdersList &ordersList)
{
    this->listOrders.clear();

    for(Order *order : ordersList.listOrders)
    {
        // add a copy of the order into the list based on the type
        if(order->getOrderType() == ("Deploy"))
            this->addToLast(new Deploy(*dynamic_cast<Deploy*>(order)));
        else if(order->getOrderType() == ("Advance"))
            this->addToLast(new Advance(*dynamic_cast<Advance*>(order)));
        else if(order->getOrderType() == ("Bomb"))
            this->addToLast(new Bomb(*dynamic_cast<Bomb*>(order)));
        else if(order->getOrderType() == ("Blockade"))
            this->addToLast(new Blockade(*dynamic_cast<Blockade*>(order)));
        else if(order->getOrderType() == ("Airlift"))
            this->addToLast(new Airlift(*dynamic_cast<Airlift*>(order)));
        else if(order->getOrderType() == ("Negotiate"))
            this->addToLast(new Negotiate(*dynamic_cast<Negotiate*>(order)));
    }
}

// Destructor
OrdersList::~OrdersList()
{
    for(Order *order : this->listOrders)
    {
        delete order;
        order = nullptr;
    }
    this->listOrders.clear();
}

// Methods
void OrdersList::add(int index, Order *order)
{
    this->listOrders.insert((this->listOrders.begin()+index), order);
}

void OrdersList::addToLast(Order *order)
{
    this->listOrders.push_back(order);
}

Order* OrdersList::deleteAt(int index)
{
    Order *removedOrder = listOrders.at(index);
    listOrders.erase(this->listOrders.begin()+index);
    return removedOrder;
}

void OrdersList::move(int indexFrom, int indexTo)
{
    Order *movedOrder = this->deleteAt(indexFrom);
    this->add(indexTo, movedOrder);
}

// Overloading operator
OrdersList& OrdersList::operator=(const OrdersList& ordersList){
    if(this == &ordersList)
        return *this;

    // deallocate
    this->listOrders.clear();

    for(Order *order : ordersList.listOrders)
    {
        // add a copy of the order into the list based on the type
        if(order->getOrderType() == ("Deploy"))
            this->addToLast(new Deploy(*dynamic_cast<Deploy*>(order)));
        else if(order->getOrderType() == ("Advance"))
            this->addToLast(new Advance(*dynamic_cast<Advance*>(order)));
        else if(order->getOrderType() == ("Bomb"))
            this->addToLast(new Bomb(*dynamic_cast<Bomb*>(order)));
        else if(order->getOrderType() == ("Blockade"))
            this->addToLast(new Blockade(*dynamic_cast<Blockade*>(order)));
        else if(order->getOrderType() == ("Airlift"))
            this->addToLast(new Airlift(*dynamic_cast<Airlift*>(order)));
        else if(order->getOrderType() == ("Negotiate"))
            this->addToLast(new Negotiate(*dynamic_cast<Negotiate*>(order)));
    }

    return *this;
}

ostream &operator<<(ostream &out, const OrdersList &ordersList)
{
    out << "List of Orders:" << endl;
    for(int i = 0; i < ordersList.listOrders.size(); i++)
        out << (i + 1) << ". " << (*ordersList.listOrders[i]).getOrderType() << endl;

    return out;
}

