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
}

// Parameterized constructor
Order::Order(Player *player)
{
    this->player = player;
    this->isExecuted = false;
}

// Copy constructor
Order::Order(const Order &order)
{
    this->player = order.player;
    this->isExecuted = order.isExecuted;
}

// Destructor
Order::~Order()
{
    delete player;
}

// Accessor
string Order::getOrderType()
{
    return this->orderType;
}

// Methods
bool Order::validate() {
    cout << "Order is valid" << endl;
    return true;
}

void Order::execute()
{
    if(validate())
    {
        cout << "Execute order" << endl;
        this->isExecuted = true;
    }
    else
        cout << "False order" << endl;
}

// Overloading operator
Order& Order::operator=(const Order& order){
    this->player = order.player;
    this->isExecuted = order.isExecuted;
    return *this;
}

ostream &operator<<(ostream &out, const Order& order) {
    out << order.orderType;
    if(order.isExecuted)
        out << " has been executed";
    else
        out << " has not been executed";
    return out;
}


/*
 * Deploy order class
 */
// Default constructor
Deploy::Deploy() : Order()
{
    this->deployTerritory = nullptr;
    this->numOfArmies = 0;
}

// Parameterized constructor
Deploy::Deploy(Player *player, Territory *deployTerritory, int numOfArmies) : Order(player)
{
    this->deployTerritory = deployTerritory;
    this->numOfArmies = numOfArmies;
}

// Copy constructor
Deploy::Deploy(const Deploy &deploy) : Order(deploy)
{
    this->deployTerritory = deploy.deployTerritory;
    this->numOfArmies = deploy.numOfArmies;
}

// Destructor
Deploy::~Deploy()
{
    delete deployTerritory;
}

// Accessor
string Deploy::getOrderType()
{
    return this->orderType;
}

// Methods
bool Deploy::validate()
{
    cout << "Deploy order is valid" << endl;
    return true;
}

void Deploy::execute()
{
    if(validate())
    {
        cout << "Deploy army in territory" << endl;
        isExecuted = true;
    }
}

// Overloading operator
Deploy& Deploy::operator=(const Deploy& deploy){
    this->deployTerritory = deploy.deployTerritory;
    this->numOfArmies = deploy.numOfArmies;
    return *this;
}

ostream &operator<<(ostream &out, const Deploy& deploy) {
    out << deploy.orderType;
    if(deploy.isExecuted)
        out << " has been executed";
    else
        out << " has not been executed";
    return out;
}


/*
 * Advance order class
 */
// Default constructor
Advance::Advance() : Order()
{
    this->fromTerritory = nullptr;
    this->toTerritory = nullptr;
    this->numOfArmies = 0;
}

// Parameterized constructor
Advance::Advance(Player *player, Territory *fromTerritory, Territory *toTerritory, int numOfArmies) : Order(player)
{
    this->fromTerritory = fromTerritory;
    this->toTerritory = toTerritory;
    this->numOfArmies = numOfArmies;
}

// Copy constructor
Advance::Advance(const Advance &advance) : Order(advance)
{
    this->fromTerritory = advance.fromTerritory;
    this->toTerritory = advance.toTerritory;
    this->numOfArmies = advance.numOfArmies;
}

// Destructor
Advance::~Advance()
{
    delete fromTerritory;
    delete toTerritory;
}

// Accessor
string Advance::getOrderType()
{
    return this->orderType;
}

// Methods
bool Advance::validate()
{
    cout << "Advance order is valid" << endl;
    return true;
}

void Advance::execute()
{
    if(validate())
    {
        cout << "Advance to territory" << endl;
        isExecuted = true;
    }
}

// Overloading operator
Advance& Advance::operator=(const Advance& advance){
    this->fromTerritory = advance.fromTerritory;
    this->toTerritory = advance.toTerritory;
    this->numOfArmies = advance.numOfArmies;
    return *this;
}

ostream &operator<<(ostream &out, const Advance& advance) {
    out << advance.orderType;
    if(advance.isExecuted)
        out << " has been executed";
    else
        out << " has not been executed";
    return out;
}


/*
  * Bomb order class
 */
// Default constructor
Bomb::Bomb() : Order()
{
    this->fromTerritory = nullptr;
    this->toTerritory = nullptr;
}

// Parameterized constructor
Bomb::Bomb(Player *player, Territory *fromTerritory, Territory *toTerritory) : Order(player)
{
    this->fromTerritory = fromTerritory;
    this->toTerritory = toTerritory;
}

// Copy constructor
Bomb::Bomb(const Bomb &bomb) : Order(bomb)
{
    this->fromTerritory = bomb.fromTerritory;
    this->toTerritory = bomb.toTerritory;
}

// Destructor
Bomb::~Bomb()
{
    delete fromTerritory;
    delete toTerritory;
}

// Accessor
string Bomb::getOrderType()
{
    return this->orderType;
}

// Methods
bool Bomb::validate()
{
    cout << "Bomb order is valid" << endl;
    return true;
}

void Bomb::execute()
{
    if(validate())
    {
        cout << "Bomb a territory" << endl;
        isExecuted = true;
    }
}

// Overloading operator
Bomb& Bomb::operator=(const Bomb& bomb)
{
    this->fromTerritory = bomb.fromTerritory;
    this->toTerritory = bomb.toTerritory;
    return *this;
}

ostream &operator<<(ostream &out, const Bomb& bomb) {
    out << bomb.orderType;
    if(bomb.isExecuted)
        out << " has been executed";
    else
        out << " has not been executed";
    return out;
}


/*
  * Blockade order class
 */
// Default constructor
Blockade::Blockade() : Order()
{
    this->blockTerritory = nullptr;
}

// Parameterized constructor
Blockade::Blockade(Player *player, Territory *blockTerritory) : Order(player)
{
    this->blockTerritory = blockTerritory;
}

// Copy constructor
Blockade::Blockade(const Blockade &blockade) : Order(blockade)
{
    this->blockTerritory = blockade.blockTerritory;
    this->isExecuted = blockade.isExecuted;
}

// Destructor
Blockade::~Blockade()
{
    delete blockTerritory;
}

// Accessor
string Blockade::getOrderType()
{
    return this->orderType;
}

// Methods
bool Blockade::validate()
{
    cout << "Blockade order is valid" << endl;
    return true;
}

void Blockade::execute()
{
    if(validate())
    {
        cout << "Perform blockade" << endl;
        isExecuted = true;
    }
}

// Overloading operator
Blockade& Blockade::operator=(const Blockade& blockade){
    this->blockTerritory = blockade.blockTerritory;
    return *this;
}

ostream &operator<<(ostream &out, const Blockade& blockade) {
    out << blockade.orderType;
    if(blockade.isExecuted)
        out << " has been executed";
    else
        out << " has not been executed";
    return out;
}


/*
 * Airlift order class
 */
//Default constructor
Airlift::Airlift() : Order()
{
    this->fromTerritory = nullptr;
    this->toTerritory = nullptr;
    this->numOfArmies = 0;
}

// Parameterized constructor
Airlift::Airlift(Player *player, Territory *fromTerritory, Territory *toTerritory, int numOfArmies) : Order(player)
{
    this->fromTerritory = fromTerritory;
    this->toTerritory = toTerritory;
    this->numOfArmies = numOfArmies;
}

// Copy constructor
Airlift::Airlift(const Airlift &airlift) : Order(airlift)
{
    this->fromTerritory = airlift.fromTerritory;
    this->toTerritory = airlift.toTerritory;
}

// Destructor
Airlift::~Airlift()
{
    delete fromTerritory;
    delete toTerritory;
}

// Accessor
string Airlift::getOrderType()
{
    return this->orderType;
}


// Method
bool Airlift::validate()
{
    cout << "Airlift order is valid" << endl;
    return true;
}

void Airlift::execute()
{
    if(validate())
    {
        cout << "Perform airlift" << endl;
        isExecuted = true;
    }
}

// Overloading operator
Airlift& Airlift::operator=(const Airlift& airlift){
    this->fromTerritory = airlift.fromTerritory;
    this->toTerritory = airlift.toTerritory;
    this->numOfArmies = airlift.numOfArmies;
    return *this;
}

ostream &operator<<(ostream &out, const Airlift& airlift) {
    out << airlift.orderType;
    if(airlift.isExecuted)
        out << " has been executed";
    else
        out << " has not been executed";
    return out;
}


/*
 * Negotiate order class
 */
// Default constructor
Negotiate::Negotiate() : Order()
{
    this->negotiator = nullptr;
}

// Parameterized constructor
Negotiate::Negotiate(Player *player, Player *negotiator) : Order(player)
{
    this->negotiator = negotiator;
}

// Copy constructor
Negotiate::Negotiate(const Negotiate &negotiate) : Order(negotiate)
{
    this->negotiator = negotiate.negotiator;
    this->isExecuted = negotiate.isExecuted;
}

// Destructor
Negotiate::~Negotiate()
{
    delete negotiator;
}

// Accessor
string Negotiate::getOrderType()
{
    return this->orderType;
}

// Methods
bool Negotiate::validate()
{
    cout << "Negotiate order is valid" << endl;
    return true;
}

void Negotiate::execute()
{
    if(validate())
    {
        cout << "Perform negotiation" << endl;
        isExecuted = true;
    }
}

// Overloading operator
Negotiate& Negotiate::operator=(const Negotiate& negotiate){
    this->negotiator = negotiate.negotiator;
    return *this;
}

ostream &operator<<(ostream &out, const Negotiate& negotiate) {
    out << negotiate.orderType;
    if(negotiate.isExecuted)
        out << " has been executed";
    else
        out << " has not been executed";
    return out;
}


/*
 * OrdersList class
 */
// Default constructor
OrdersList::OrdersList()
{
    vector<Order*> listOrders;
}

// Copy constructor
OrdersList::OrdersList(const OrdersList &orders)
{
    this->listOrders = orders.listOrders;
}

// Destructor
OrdersList::~OrdersList()
{
    listOrders.clear();
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
OrdersList& OrdersList::operator=(const OrdersList& o){
    this->listOrders = o.listOrders;
    return *this;
}

ostream &operator<<(ostream &out, const OrdersList &ordersList)
{
    out << "List of Orders:" << endl;
    for(int i = 0; i < ordersList.listOrders.size(); i++)
        out << (i + 1) << ". " << (*ordersList.listOrders[i]).getOrderType() << endl;
    return out;
}

