#pragma once
#ifndef A1_ORDERS_H
#define A1_ORDERS_H

#include <iostream>
#include <vector>
#include <string>

#include "../Part 1/Map.h"
#include "../Part 4/Player.h"

using namespace std;
using std::vector;

class Order
{
public:
    Order();
    Order(Player *player);
    Order(const Order &order);
    ~Order();
    bool validate();
    void execute();
    ostream& operator<<(ostream& out, const Order* order);
protected:
    bool isExecuted = false;
private:
    Player *player;
};


class Deploy : public Order
{
public:
    Deploy();
    Deploy(Player *player, Territory *deployTerritory, int numOfArmies);
    Deploy(const Deploy &deploy);
    ~Deploy();
    bool validate();
    void execute();
    ostream& operator<<(ostream& out, const Deploy& deploy);

private:
    Territory *deployTerritory;
    int numOfArmies;
};


class Advance : public Order
{
public:
    Advance();
    Advance(Player *player, Territory *fromTerritory, Territory *toTerritory, int numOfArmies);
    Advance(const Advance &advance);
    ~Advance();
    bool validate();
    void execute();
    ostream& operator<<(ostream& out, const Advance& advance);
private:
    Territory *fromTerritory;
    Territory *toTerritory;
    int numOfArmies;

};


class Bomb : public Order
{
public:
    Bomb();
    Bomb(Player *player, Territory *fromTerritory, Territory *toTerritory);
    Bomb(const Bomb &bomb);
    ~Bomb();
    bool validate();
    void execute();
    ostream& operator<<(ostream& out, const Bomb& bomb);
private:
    Territory *fromTerritory;
    Territory *toTerritory;
};


class Blockade : public Order
{
public:
    Blockade();
    Blockade(Player *player, Territory *blockTerritory);
    Blockade(const Blockade &blockage);
    ~Blockade();
    bool validate();
    void execute();
    ostream& operator<<(ostream& out, const Blockade& blockade);
private:
    Territory *blockTerritory;
};


class Airlift : public Order
{
public:
    Airlift();
    Airlift(Player *player, Territory *fromTerritory, Territory *toTerritory, int numOfArmies);
    Airlift(const Airlift &airlift);
    ~Airlift();
    bool validate();
    void execute();
    ostream& operator<<(ostream& out, const Airlift& airlift);
private:
    Territory *fromTerritory;
    Territory *toTerritory;
    int numOfArmies;
};


class Negotiate : public Order
{
public:
    Negotiate();
    Negotiate(Player *player, Player *negotiator);
    Negotiate(const Negotiate &negotiate);
    ~Negotiate();
    bool validate();
    void execute();
    ostream& operator<<(ostream& out, const Negotiate& negotiate);
private:
    Player *negotiator;
};


class OrdersList
{
public:
    OrdersList();
    OrdersList(const OrdersList &orders);
    ~OrdersList();
    OrdersList& operator=(OrdersList const& o);
    void add(Order *order);
    void delete(int index);
    void move(int indexFrom, int indexTo);
    ostream& operator<<(ostream& out, const OrdersList& ordersList);
private:
    vector<Order*> listOrders;
};


#endif //A1_ORDERS_H
