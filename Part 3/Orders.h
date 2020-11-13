#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../Part 1/Map.h"

using namespace std;
using std::vector;

// Forward declaration due to circular dependency
class Player;
class Territory;

/*
 * Quick summary of what each order does
 * Deploy:      place some armies on one of the current player’s territories
 * Advance:     move armies from one of the current player’s territories (source) to an adjacent territory (target)
 * Bomb:        destroy half of the armies on an opponent’s territory that is adjacent to the current player’s territories
 * Blockade:    triple the number of armies on one of the current player’s territories and make it a neutral territory
 * Airlift:     move some armies from one of the current player’s territories to any another territory
 * Negotiate:   prevent the current player and the target player from attacking each other until the end of the turn
 */

// Abstract parent class Order
class Order
{
protected:
    bool isExecuted;            // Indicate whether order as been executed
    string orderType;           // The type of order
    Player *player;             // Player who is making the order
public:
    // Constructors and destructor
    // Order constructors cannot be used since it is an abstract class
    Order();
    Order(Player *player);
    Order(const Order &order);
    virtual ~Order();
    // Accessor and Mutator for orderType
    string getOrderType()       { return this->orderType; };
    void setType(string type)   { this->orderType = type; };
    // Methods
    virtual bool validate();
    // pure virtual methods
    virtual void execute() = 0;
    virtual ostream& getEffect(ostream& out) const = 0;
    virtual ostream& print(ostream& out) const = 0;
    // Overloading operators
    Order& operator=(Order const& o);
    friend ostream& operator<<(ostream& out, const Order& order);
};


class Deploy : public Order
{
private:
    Territory *targetTerritory;         // Territory to deploy armies
    int numOfArmies;                    // Number of armies to deploy
public:
    // Constructors and destructor
    Deploy();
    Deploy(Player *player, Territory *targetTerritory, int numOfArmies);
    Deploy(const Deploy &deploy);
    ~Deploy();
    // Methods
    bool validate();
    void execute();
    ostream& getEffect(ostream& out) const;
    ostream& print(ostream& out) const;
    // Overloading operators
    Deploy& operator=(Deploy const& o);
    friend ostream& operator<<(ostream& out, const Deploy& deploy);
};


class Advance : public Order
{
private:
    Territory *sourceTerritory;        // Starting territory
    Territory *targetTerritory;        // Advancing territory
    int numOfArmies;                   // Number of armies to advance
public:
    // Constructors and destructor
    Advance();
    Advance(Player *player, Territory *sourceTerritory, Territory *targetTerritory, int numOfArmies);
    Advance(const Advance &advance);
    ~Advance();
    // Methods
    bool validate();
    void execute();
    ostream& getEffect(ostream& out) const;
    ostream& print(ostream& out) const;
    // Overloading operators
    Advance& operator=(Advance const& o);
    friend ostream& operator<<(ostream& out, const Advance& advance);
};


class Bomb : public Order
{
private:
    Territory *sourceTerritory;          // From territory
    Territory *targetTerritory;            // Territory to bomb
public:
    // Constructors and destructor
    Bomb();
    Bomb(Player *player, Territory *sourceTerritory, Territory *targetTerritory);
    Bomb(const Bomb &bomb);
    ~Bomb();
    // Methods
    bool validate();
    void execute();
    ostream& getEffect(ostream& out) const;
    ostream& print(ostream& out) const;
    // Overloading operators
    Bomb& operator=(Bomb const& o);
    friend ostream& operator<<(ostream& out, const Bomb& bomb);
};


class Blockade : public Order
{
private:
    Territory *targetTerritory;         // Territory to block
public:
    // Constructors and destructor
    Blockade();
    Blockade(Player *player, Territory *targetTerritory);
    Blockade(const Blockade &blockage);
    ~Blockade();
    // Methods
    bool validate();
    void execute();
    ostream& getEffect(ostream& out) const;
    ostream& print(ostream& out) const;
    // Overloading operators
    Blockade& operator=(Blockade const& o);
    friend ostream& operator<<(ostream& out, const Blockade& blockade);
};


class Airlift : public Order
{
private:
    Territory *sourceTerritory;          // Starting territory
    Territory *targetTerritory;            // Advancing territory
    int numOfArmies;                    // Number of armies to advance
public:
    // Constructors and destructor
    Airlift();
    Airlift(Player *player, Territory *sourceTerritory, Territory *targetTerritory, int numOfArmies);
    Airlift(const Airlift &airlift);
    ~Airlift();
    // Methods
    bool validate();
    void execute();
    ostream& getEffect(ostream& out) const;
    ostream& print(ostream& out) const;
    // Overloading operators
    Airlift& operator=(Airlift const& o);
    friend ostream& operator<<(ostream& out, const Airlift& airlift);
};


class Negotiate : public Order
{
private:
    Player *negotiator;         // The opponent player to be negotiated
public:
    // Constructors and destructor
    Negotiate();
    Negotiate(Player *player, Player *negotiator);
    Negotiate(const Negotiate &negotiate);
    ~Negotiate();
    // Methods
    bool validate();
    void execute();
    ostream& getEffect(ostream& out) const;
    ostream& print(ostream& out) const;
    // Overloading operators
    Negotiate& operator=(Negotiate const& o);
    friend ostream& operator<<(ostream& out, const Negotiate& negotiate);
};


class OrdersList
{
private:
    vector<Order*> listOrders;                  // vector to store Orders
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
};

