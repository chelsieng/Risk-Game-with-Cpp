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
    virtual bool validate();
    virtual void execute();
    friend ostream& operator<<(ostream& out, const Order& order);
protected:
    bool isExecuted;
private:
    Player *player;
    string name = "Order";
};


class Deploy : public Order
{
public:
    Deploy();
    Deploy(Player *player, Map::Territory *deployTerritory, int numOfArmies);
    Deploy(const Deploy &deploy);
    ~Deploy();
    bool validate() override;
    void execute() override;
    friend ostream& operator<<(ostream& out, const Deploy& deploy);
private:
    Map::Territory *deployTerritory;
    int numOfArmies;
    string name = "Deploy";
};


class Advance : public Order
{
public:
    Advance();
    Advance(Player *player, Map::Territory *fromTerritory, Map::Territory *toTerritory, int numOfArmies);
    Advance(const Advance &advance);
    ~Advance();
    bool validate() override;
    void execute() override;
    friend ostream& operator<<(ostream& out, const Advance& advance);
private:
    Map::Territory *fromTerritory;
    Map::Territory *toTerritory;
    int numOfArmies;
    string name = "Advance";

};


class Bomb : public Order
{
public:
    Bomb();
    Bomb(Player *player, Map::Territory *fromTerritory, Map::Territory *toTerritory);
    Bomb(const Bomb &bomb);
    ~Bomb();
    bool validate() override;
    void execute() override;
    friend ostream& operator<<(ostream& out, const Bomb& bomb);
private:
    Map::Territory *fromTerritory;
    Map::Territory *toTerritory;
    string name = "Bomb";
};


class Blockade : public Order
{
public:
    Blockade();
    Blockade(Player *player, Map::Territory *blockTerritory);
    Blockade(const Blockade &blockage);
    ~Blockade();
    bool validate() override;
    void execute() override;
    friend ostream& operator<<(ostream& out, const Blockade& blockade);
private:
    Map::Territory *blockTerritory;
    string name = "Blockade";
};


class Airlift : public Order
{
public:
    Airlift();
    Airlift(Player *player, Map::Territory *fromTerritory, Map::Territory *toTerritory, int numOfArmies);
    Airlift(const Airlift &airlift);
    ~Airlift();
    bool validate() override;
    void execute() override;
    friend ostream& operator<<(ostream& out, const Airlift& airlift);
private:
    Map::Territory *fromTerritory;
    Map::Territory *toTerritory;
    int numOfArmies;
    string name = "Airlift";
};


class Negotiate : public Order
{
public:
    Negotiate();
    Negotiate(Player *player, Player *negotiator);
    Negotiate(const Negotiate &negotiate);
    ~Negotiate();
    bool validate() override;
    void execute() override;
    friend ostream& operator<<(ostream& out, const Negotiate& negotiate);
private:
    Player *negotiator;
    string name = "Negotiate";
};


class OrdersList
{
public:
    OrdersList();
    OrdersList(const OrdersList &orders);
    ~OrdersList();
    OrdersList& operator=(OrdersList const& o);
    void add(int index, Order *order);
    void addToLast(Order *order);
    Order* deleteAt(int index);
    void move(int indexFrom, int indexTo);
    friend ostream& operator<<(ostream& out, const OrdersList &ordersList);
private:
    vector<Order*> listOrders;
};


#endif //A1_ORDERS_H