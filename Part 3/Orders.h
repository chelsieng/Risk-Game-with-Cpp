#pragma once
#ifndef A1_ORDERS_H
#define A1_ORDERS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using std::vector;

class Order
{
public:
    Order();
    Order(const Order &order);
    ~Order();
    std::ostream& operator<<(std::ostream& out, const Order& order);
    bool validate();
    void execute();
protected:
    bool isExecuted = false;
private:
    string name;
};

class Deploy : public Order
{
public:
    Deploy();
    Deploy(const Deploy &deploy);
    ~Deploy();
    bool validate();
    void execute();
    std::ostream& operator<<(std::ostream& out, const Deploy& deploy);
};

class Advance : public Order
{
public:
    Advance();
    Advance(const Advance &advance);
    ~Advance();
    bool validate();
    void execute();
    std::ostream& operator<<(std::ostream& out, const Advance& advance);
};

class Bomb : public Order
{
public:
    Bomb();
    Bomb(const Bomb &bomb);
    ~Bomb();
    bool validate();
    void execute();
    std::ostream& operator<<(std::ostream& out, const Bomb& bomb);
};

class Blockade : public Order
{
public:
    Blockade();
    Blockade(const Blockade &blockage);
    ~Blockade();
    bool validate();
    void execute();
    std::ostream& operator<<(std::ostream& out, const Blockade& blockade);

};

class Airlift : public Order
{
public:
    Airlift();
    Airlift(const Airlift &airlift);
    ~Airlift();
    bool validate();
    void execute();
    std::ostream& operator<<(std::ostream& out, const Airlift& airlift);
};

class Negotiate : public Order
{
public:
    Negotiate();
    Negotiate(const Negotiate &negotiate);
    ~Negotiate();
    bool validate();
    void execute();
    std::ostream& operator<<(std::ostream& out, const Negotiate& negotiate);
};

class OrdersList
{
public:
    OrdersList();
    OrdersList(const OrdersList &orders);
    ~OrdersList();
    void delete(Order *order);
    void move(Order *order);
    std::ostream& operator<<(std::ostream& out, const OrdersList& ordersList);
private:
    vector<Order*> listOrders;
};


#endif //A1_ORDERS_H
