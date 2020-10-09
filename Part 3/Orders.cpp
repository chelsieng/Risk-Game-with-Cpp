#include <iostream>
#include <vector>

#include "Orders.h"

using namespace std;
using std::vector;

/*
 * Order class
 */
Order::Order()
{

}

Order::Order(Player *player)
{
    this->player = player;
}

Order::Order(const Order &order)
{
    this->player = order.player;
    this->isExecuted = order.isExecuted;
}

Order::~Order()
{
    delete player;
}

bool Order::validate()
{
    return true;
}

void Order::execute()
{
    if(validate())
        cout << "Execute order" << endl;
    else
        cout << "False order" << endl;
}

ostream &Order::operator<<(ostream &out, const Order &order)
{
    out << "Execute order";
    if(isExecuted)
        out << "This order has been executed.";
    return out;
}


/*
  * Deploy order class
 */
Deploy::Deploy() : Order()
{

}

Deploy::Deploy(Player *player, Territory *deployTerritory, int numOfArmies) : Order(player)
{
    this->deployTerritory = deployTerritory;
    this->numOfArmies = numOfArmies;
}

Deploy::Deploy(const Deploy &deploy) : Order(deploy)
{
    this->deployTerritory = deploy.deployTerritory;
    this->numOfArmies = deploy.numOfArmies;
}

Deploy::~Deploy()
{
    delete deployTerritory;
}

bool Deploy::validate()
{
    cout << "True if order is valid" << endl;
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

ostream &Deploy::operator<<(ostream &out, const Deploy &deploy) {
    out << "Deploy armies";
    if(isExecuted)
        out << "This order has been executed.";
    return out;
}


/*
 * Advance order class
 */
Advance::Advance() : Order()
{

}

Advance::Advance(Player *player, Territory *fromTerritory, Territory *toTerritory, int numOfArmies) : Order(player)
{
    this->fromTerritory = fromTerritory;
    this->toTerritory = toTerritory;
    this->numOfArmies = numOfArmies;
}

Advance::Advance(const Advance &advance) : Order(advance)
{
    this->fromTerritory = advance.fromTerritory;
    this->toTerritory = advance.toTerritory;
    this->numOfArmies = advance.numOfArmies;
}

Advance::~Advance()
{
    delete fromTerritory;
    delete toTerritory
}

bool Advance::validate()
{
    cout << "True if order is valid" << endl;
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

ostream &Advance::operator<<(ostream &out, const Advance &advance) {
    out << "Advance armies";
    if(isExecuted)
        out << "This order has been executed.";
    return out;
}


/*
  * Bomb order class
 */
Bomb::Bomb() : Order()
{

}

Bomb::Bomb(Player *player, Territory *fromTerritory, Territory *toTerritory) : Order(player)
{
    this->fromTerritory = fromTerritory;
    this->toTerritory = toTerritory;
}

Bomb::Bomb(const Bomb &bomb) : Order(bomb)
{
    this->fromTerritory = bomb.fromTerritory;
    this->toTerritory = bomb.toTerritory;
}

Bomb::~Bomb()
{
    delete fromTerritory;
    delete toTerritory;
}

bool Bomb::validate()
{
    cout << "True if order is valid" << endl;
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

ostream &Bomb::operator<<(ostream &out, const Bomb &bomb) {
    out << "Bomb territory";
    if(isExecuted)
        out << "This order has been executed.";
    return out;
}


/*
  * Blockade order class
 */
Blockade::Blockade() : Order()
{

}

Blockade::Blockade(Player *player, Territory *blockTerritory) : Order(player)
{
    this->blockTerritory = blockTerritory;
}

Blockade::Blockade(const Blockade &blockade) : Order(blockade)
{
    this->blockTerritory = blockade.blockTerritory;
    this->isExecuted = blockade.isExecuted;
}

Blockade::~Blockade()
{
    delete blockTerritory;
}

bool Blockade::validate()
{
    cout << "True if order is valid" << endl;
    return true;
}

void Blockade::execute()
{
    if(validate())
    {
        cout << "Perform blockage" << endl;
        isExecuted = true;
    }
}

ostream &Blockade::operator<<(ostream &out, const Blockade &blockade) {
    out << "Blockade territory";
    if(isExecuted)
        out << "This order has been executed.";
    return out;
}


/*
 * Airlift order class
 */
Airlift::Airlift() : Order()
{

}

Airlift::Airlift(Player *player, Territory *fromTerritory, Territory *toTerritory, int numOfArmies) : Order(player)
{
    this->fromTerritory = fromTerritory;
    this->toTerritory = toTerritory;
    this->numOfArmies = numOfArmies;
}

Airlift::Airlift(const Airlift &airlift)
{
    this->fromTerritory = airlift.fromTerritory;
    this->toTerritory = airlift.toTerritory;
}

Airlift::~Airlift()
{
    delete fromTerritory;
    delete toTerritory;
}

bool Airlift::validate()
{
    cout << "True if order is valid" << endl;
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

ostream &Airlift::operator<<(ostream &out, const Airlift &airlift) {
    out << "Execute airlift";
    if(isExecuted)
        out << "This order has been executed.";
    return out;
}


/*
 * Negotiate order class
 */
Negotiate::Negotiate() : Order()
{

}

Negotiate::Negotiate(Player *player, Player *negotiator) : Order(player)
{
    this->negotiator = negotiator;
}

Negotiate::Negotiate(const Negotiate &negotiate) : Order(negotiate)
{

}

Negotiate::~Negotiate()
{
    delete negotiator;
}

bool Negotiate::validate()
{
    cout << "True if order is valid" << endl;
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

ostream& Negotiate::operator<<(ostream &out, const Negotiate &negotiate) {
    out << "Execute negotiation";
    if(isExecuted)
        out << "This order has been executed.";
    return out;
}


/*
 * OrdersList class
 */
OrdersList::OrdersList()
{
//    listOrders = new vector<Order*>();
}

OrdersList::OrdersList(const OrdersList &orders)
{

}

OrdersList::~OrdersList()
{

}

OrdersList& OrdersList::operator=(const OrdersList& o){
    this->listOrders = o.listOrders;
    return *this;
}

void OrdersList::add(Order *order)
{
    this->listOrders.push_back(order);
}

void OrdersList::delete(Order *order)
{
    
}

void OrdersList::move(Order *order)
{

}
