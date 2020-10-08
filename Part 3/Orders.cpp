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

Order::Order(const Order &order)
{

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

std::ostream &Order::operator<<(ostream &out, const Order &order) {
    out << "Execute order";
    if(isExecuted)
        out << "This order has been executed.";
    return out;
}

/*
 * Deploy order class
 */
Deploy::Deploy()
{

}

Deploy::Deploy(const Deploy &deploy)
{

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

std::ostream &Deploy::operator<<(ostream &out, const Deploy &deploy) {
    out << "Deploy armies";
    if(isExecuted)
        out << "This order has been executed.";
    return out;
}

/*
 * Advance order class
 */
Advance::Advance()
{

}

Advance::Advance(const Advance &advance)
{

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

std::ostream &Advance::operator<<(ostream &out, const Advance &advance) {
    out << "Advance armies";
    if(isExecuted)
        out << "This order has been executed.";
    return out;
}

/*
 * Bomb order class
 */
Bomb::Bomb()
{

}

Bomb::Bomb(const Bomb &bomb)
{

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

std::ostream &Bomb::operator<<(ostream &out, const Bomb &bomb) {
    out << "Bomb territory";
    if(isExecuted)
        out << "This order has been executed.";
    return out;
}

/*
 * Blockade order class
 */
Blockade::Blockade()
{

}

Blockade::Blockade(const Blockade &blockade)
{

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

std::ostream &Blockade::operator<<(ostream &out, const Blockade &blockade) {
    out << "Blockade territory";
    if(isExecuted)
        out << "This order has been executed.";
    return out;
}

/*
 * Airlift order class
 */
Airlift::Airlift()
{

}

Airlift::Airlift(const Airlift &airlift)
{

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

std::ostream &Airlift::operator<<(ostream &out, const Airlift &airlift) {
    out << "Execute airlift";
    if(isExecuted)
        out << "This order has been executed.";
    return out;
}

/*
 * Negotiate order class
 */
Negotiate::Negotiate()
{

}

Negotiate::Negotiate(const Negotiate &negotiate)
{

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

std::ostream &Negotiate::operator<<(ostream &out, const Negotiate &negotiate) {
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

}

OrdersList::OrdersList(const OrdersList &orders)
{

}

void OrdersList::delete(Order* order)
{

}

void OrdersList::move(Order* order)
{

}
