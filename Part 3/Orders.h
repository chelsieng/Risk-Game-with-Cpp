#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Map.h"

using namespace std;
using std::vector;

// Forward declaration due to circular dependency
class Player;
class Territory;

class Order
{
public:
    // Constructors and destructor
    Order();
    Order(Player *player);
    Order(const Order &order);
    ~Order();
    // Accessor
    virtual string getOrderType();
    // Methods
    virtual bool validate();
    virtual void execute();
    // Overloading operators
    Order& operator=(Order const& o);
    friend ostream& operator<<(ostream& out, const Order& order);
protected:
    bool isExecuted;            // Indicate whether order as been executed
    string orderType = "Order"; // The type of order
private:
    Player *player;             // Player who is making the order
};


class Deploy : public Order
{
public:
    // Constructors and destructor
    Deploy();
    Deploy(Player *player, Territory *deployTerritory, int numOfArmies);
    Deploy(const Deploy &deploy);
    ~Deploy();
    // Accessor
    string getOrderType()  override;
    bool validate() override;
    void execute() override;
    // Overloading operators
    Deploy& operator=(Deploy const& o);
    friend ostream& operator<<(ostream& out, const Deploy& deploy);
private:
    Territory *deployTerritory;         // Territory to deploy armies
    int numOfArmies;                    // Number of armies to deploy
    string orderType = "Deploy";
};


class Advance : public Order
{
public:
    // Constructors and destructor
    Advance();
    Advance(Player *player, Territory *fromTerritory, Territory *toTerritory, int numOfArmies);
    Advance(const Advance &advance);
    ~Advance();
    // Accessor
    string getOrderType() override;
    bool validate() override;
    void execute() override;
    // Overloading operators
    Advance& operator=(Advance const& o);
    friend ostream& operator<<(ostream& out, const Advance& advance);
private:
    Territory *fromTerritory;          // Starting territory
    Territory *toTerritory;            // Advancing territory
    int numOfArmies;                    // Number of armies to advance
    string orderType = "Advance";
};


class Bomb : public Order
{
public:
    // Constructors and destructor
    Bomb();
    Bomb(Player *player, Territory *fromTerritory, Territory *toTerritory);
    Bomb(const Bomb &bomb);
    ~Bomb();
    // Accessor
    string getOrderType() override;
    bool validate() override;
    void execute() override;
    // Overloading operators
    Bomb& operator=(Bomb const& o);
    friend ostream& operator<<(ostream& out, const Bomb& bomb);
private:
    Territory *fromTerritory;          // From territory
    Territory *toTerritory;            // Territory to bomb
    string orderType = "Bomb";
};


class Blockade : public Order
{
public:
    // Constructors and destructor
    Blockade();
    Blockade(Player *player, Territory *blockTerritory);
    Blockade(const Blockade &blockage);
    ~Blockade();
    // Accessor
    string getOrderType() override;
    bool validate() override;
    void execute() override;
    // Overloading operators
    Blockade& operator=(Blockade const& o);
    friend ostream& operator<<(ostream& out, const Blockade& blockade);
private:
    Territory *blockTerritory;         // Territory to block
    string orderType = "Blockade";
};


class Airlift : public Order
{
public:
    // Constructors and destructor
    Airlift();
    Airlift(Player *player, Territory *fromTerritory, Territory *toTerritory, int numOfArmies);
    Airlift(const Airlift &airlift);
    ~Airlift();
    // Accessor
    string getOrderType() override;
    bool validate() override;
    void execute() override;
    // Overloading operators
    Airlift& operator=(Airlift const& o);
    friend ostream& operator<<(ostream& out, const Airlift& airlift);
private:
    Territory *fromTerritory;          // Starting territory
    Territory *toTerritory;            // Advancing territory
    int numOfArmies;                    // Number of armies to advance
    string orderType = "Airlift";
};


class Negotiate : public Order
{
public:
    // Constructors and destructor
    Negotiate();
    Negotiate(Player *player, Player *negotiator);
    Negotiate(const Negotiate &negotiate);
    ~Negotiate();
    // Accessor
    string getOrderType() override;
    // Methods
    bool validate() override;
    void execute() override;
    // Overloading operators
    Negotiate& operator=(Negotiate const& o);
    friend ostream& operator<<(ostream& out, const Negotiate& negotiate);
private:
    Player *negotiator;         // The opponent player to be negotiated
    string orderType = "Negotiate";
};


class OrdersList
{
public:
    // Constructors and destructor
    OrdersList();
    OrdersList(const OrdersList &orders);
    ~OrdersList();
    // Methods
    void add(int index, Order *order);          // Adding given Order to given index in the list
    void addToLast(Order *order);               // Adding Order to the last of the list
    Order* deleteAt(int index);                 // Deleting and return Order at the given index
    void move(int indexFrom, int indexTo);      // Moving Order with given index
    // Overloading operators
    OrdersList& operator=(OrdersList const& o);
    friend ostream& operator<<(ostream& out, const OrdersList &ordersList);
private:
    vector<Order*> listOrders;                  // vector to store Orders
};